#include"vfs.h"

MyFSY::MyFSY()
{

}

void MyFSY::sys_start(std::string m_disk)
{
	//格式化
	sys_format();
	//初始化磁盘
	this->disk.vhard = m_disk;
	/*for (int i = 0; i < SIZE; i++) 
		this->disk.vhard[i] = m_disk[i];*/
	//初始化FAT表
	std::string res;
	std::stringstream ss;
	res.clear();
	disk.disk_move(1);
	disk.disk_read(res, BLOCKSIZE * 2);
	int t = 0, k = 0;
	for (int i = 0; i < res.length(); i++)
	{
		if (res[i] == ';')
		{
			fat1.state[k] = t;
			fat2.state[k] = t;
			t = 0;
			k++;
		}
		if (res[i] >= '0' && res[i] <= '9')
		{
			t *= 10;
			t += res[i] - '0';
		}
	}
	//初始化根目录
	disk.disk_move(5);
	ss.clear();
	res.clear();
	disk.disk_read(res, FILENAMESIZE);
	for (int i = 0; res[i] != '\0'; i++)
		nowDir.fcb.filename[i] = res[i];

	ss.clear();
	res.clear();
	disk.disk_read(res, EXNAMESIZE);
	for (int i = 0; res[i] != '\0'; i++)
		nowDir.fcb.exname[i] = res[i];

	ss.clear();
	res.clear();
	disk.disk_read(res, ATTRIBUTESIZE);
	nowDir.fcb.attribute = res[0];
	
	ss.clear();
	res.clear();
	disk.disk_read(res, TIMESIZE);
	for (int i = 0; i < 6; i++)
		nowDir.fcb.m_time[i] = res[i];

	ss.clear();
	res.clear();
	disk.disk_read(res, DATASIZE);
	for (int i = 0; i < 8; i++)
		nowDir.fcb.m_data[i] = res[i];

	//根目录起始盘块号固定，是已知的
	disk.disk_read(res, FIRSTSIZE);
	nowDir.fcb.first = 5;

	ss.clear();
	res.clear();
	disk.disk_read(res, FILELENGTHSIZE);
	t = 0;
	for (int i = 0; res[i]!='\0'; i++)
	{
		t *= 10;
		t += res[i] - '0';
	}
	nowDir.fcb.length = t;

	ss.clear();
	res.clear();
	disk.disk_read(res, FREESIZE);
	nowDir.fcb.free = res[0] - '0';

	ss.clear();
	res.clear();
	disk.disk_read(res, NUMSONSIZE);
	t = 0;
	for (int i = 0; res[i] != '\0'; i++)
	{
		t *= 10;
		t += res[i] - '0';
	}
	nowDir.fcb.num_son = t;

	ss.clear();
	res.clear();
	disk.disk_read(res, SONSIZE);
	t = 0, k = 0;
	for (int i = 0; i < res.length(); i++)
	{
		if (res[i] == '\0')
		{
			nowDir.fcb.son[k++] = t;
			if (k == nowDir.fcb.num_son) break;
			while (i < res.length() && res[i++] == '\0');
			i--;
			t = 0;
		}
		if (res[i] >= '0' && res[i] <= '9')
		{
			t *= 10;
			t += res[i] - '0';
		}
	}
}

void MyFSY::sys_format()
{
	//清空磁盘
	disk.disk_format();

	//格式化化引导块
	strcpy_s(initblock.information, "10101010");
	initblock.root = 5;
	initblock.startblock = 5;

	std::stringstream ss;
	std::string res;
	//写入引导区
	ss << initblock.information;
	ss << ';';
	ss >> res;
	disk.disk_write(res, 10);
	ss.clear();
	res.clear();
	ss << initblock.root;
	ss << ';';
	ss >> res;
	disk.disk_write(res, 4);
	ss.clear();
	res.clear();
	ss << initblock.startblock;
	ss << ';';
	ss >> res;
	disk.disk_write(res, 4);

	//格式化FAT表
	fat1.state[0] = END;
	fat1.state[1] = 2;
	fat1.state[2] = END;
	fat1.state[3] = 4;
	fat1.state[4] = END;
	fat2.state[0] = END;
	fat2.state[1] = 2;
	fat2.state[2] = END;
	fat2.state[3] = 4;
	fat2.state[4] = END;
	//写入FAT
	update_fat();

	//格式化当前目录并作为根目录
	nowDir.fcb.Init("root", '0', 5, FCBSIZE);
	nowDir.dir_ser = 0;
	nowDir.dir_first[0] = 5;
	for (int i = 0; i < nowDir.fcb.num_son; i++)
		nowDir.fcb.son[i] = nowDir.fcb.son[i];

	//写入根目录fcb
	fat1.state[nowDir.fcb.first] = END;
	fat2.state[nowDir.fcb.first] = END;
	write_fcb(nowDir.fcb);
}

void MyFSY::update_fat()
{
	std::stringstream ss;
	std::string res;
	//写入FAT1, 数字之间用';'分开
	ss.clear();
	res.clear();
	disk.disk_move(1);
	for (int i = 0; i < BLOCKNUM; i++)
	{
		ss << fat1.state[i];
		ss << ';';
	}
	ss >> res;
	disk.disk_write(res, BLOCKSIZE * 2);

	//写入FAT2
	ss.clear();
	res.clear();
	disk.disk_move(3);
	for (int i = 0; i < BLOCKNUM; i++)
	{
		ss << fat2.state[i];
		ss << ';';
	}
	ss >> res;
	disk.disk_write(res, BLOCKSIZE * 2);
}

void MyFSY::write_fcb(FCB fcb)
{
	//一个fcb写到同一个块的连续字节中
	disk.disk_move(fcb.first);
	std::stringstream ss;
	std::string res;
	ss.clear();
	res.clear();
	for (int i = 0; fcb.filename[i] != '\0'; i++)
		ss << fcb.filename[i];
	ss >> res;
	disk.disk_write(res, FILENAMESIZE);

	ss.clear();
	res.clear();
	for (int i = 0; fcb.exname[i] != '\0'; i++)
		ss << fcb.exname[i];
	ss >> res;
	disk.disk_write(res, EXNAMESIZE);

	ss.clear();
	res.clear();
	ss << fcb.attribute;
	ss >> res;
	disk.disk_write(res, ATTRIBUTESIZE);

	ss.clear();
	res.clear();
	for (int i = 0; i < 6; i++)
		ss << fcb.m_time[i];
	ss >> res;
	disk.disk_write(res, TIMESIZE);

	ss.clear();
	res.clear();
	for (int i = 0; i < 8; i++)
		ss << fcb.m_data[i];
	ss >> res;
	disk.disk_write(res, DATASIZE);

	ss.clear();
	res.clear();
	ss << fcb.first;
	ss >> res;
	disk.disk_write(res, FIRSTSIZE);

	ss.clear();
	res.clear();
	ss << fcb.length;
	ss >> res;
	disk.disk_write(res, FILELENGTHSIZE);

	ss.clear();
	res.clear();
	ss << fcb.free;
	ss >> res;
	disk.disk_write(res, FREESIZE);

	ss.clear();
	res.clear();
	ss << fcb.num_son;
	ss >> res;
	disk.disk_write(res, NUMSONSIZE);

	res.clear();
	std::string str;
	for (int i = 0; i < SONSIZE; i++)
		str.push_back('\0');
	for (int i = 0; i < fcb.num_son; i++)
	{
		ss.clear();
		ss << fcb.son[i];
		ss >> res;
		for (int j = 0; j < res.length(); j++)
			str[i * 4 + j] = res[j];
	}
	disk.disk_write(str, SONSIZE);
	update_fat();
}

void MyFSY::get_fcb(int start, FCB& fcb)
{
	disk.disk_move(start);
	std::string res;
	res.clear();
	disk.disk_read(res, FILENAMESIZE);
	strcpy_s(fcb.filename, res.c_str());

	res.clear();
	disk.disk_read(res, EXNAMESIZE);
	strcpy_s(fcb.exname, res.c_str());

	res.clear();
	disk.disk_read(res, ATTRIBUTESIZE);
	fcb.attribute = res[0];

	res.clear();
	disk.disk_read(res, TIMESIZE);
	for (int i = 0; i < 6; i++)
		fcb.m_time[i] = res[i];

	res.clear();
	disk.disk_read(res, DATASIZE);
	for (int i = 0; i < 8; i++)
		fcb.m_data[i] = res[i];

	res.clear();
	disk.disk_read(res, FIRSTSIZE);
	int i = 0, num = 0;
	while (res[i])
		num = num * 10 + (res[i++] - '0');
	fcb.first = num;

	res.clear();
	disk.disk_read(res, FILELENGTHSIZE);
	i = 0, num = 0;
	while (res[i])
		num = num * 10 + (res[i++] - '0');
	fcb.length = num;

	res.clear();
	disk.disk_read(res, FREESIZE);
	i = 0, num = 0;
	while (res[i])
		num = num * 10 + (res[i++] - '0');
	fcb.free = num;

	res.clear();
	disk.disk_read(res, NUMSONSIZE);
	i = 0, num = 0;
	while (res[i])
		num = num * 10 + (res[i++] - '0');
	fcb.num_son = num;

	res.clear();
	disk.disk_read(res, SONSIZE);
	std::string str;
	int mm = 0;
	for (int ii = 0; ii < MAXSON; ii++)
	{
		str.clear();
		i = 0;
		num = 0;
		for (int j = 0; j < 4; j++)
			str.push_back(res[ii * 4 + j]);
		while (str[i])
			num = num * 10 + (res[i++] - '0');
		if (num != 0)
			fcb.son[mm++] = num;
		if (mm == fcb.num_son)
			break;
	}
}

int MyFSY::sys_mkdir(std::string dirname)
{
	if (nowDir.fcb.num_son == MAXSON)
		return 0;
	for (int i = 0; i < nowDir.fcb.num_son; i++)
	{
		FCB tfcb;
		get_fcb(nowDir.fcb.son[i], tfcb);
		if (tfcb.attribute == '0' && strcmp(tfcb.filename, dirname.c_str()) == 0)
			return -1;
	}
	int first = -1;
	for (int i = 0; i < BLOCKNUM; i++) //找一个空的盘块
	{
		if (fat1.state[i] == FREE)
		{
			first = i;
			break;
		}
	}
	if (first == -1)
		return 3; //空间不足分配失败
	FCB fcb;
	fcb.Init(dirname, '0', first, FCBSIZE);
	fat1.state[fcb.first] = END;
	fat2.state[fcb.first] = END;
	write_fcb(fcb);
	nowDir.fcb.son[nowDir.fcb.num_son++] = fcb.first;
	write_fcb(nowDir.fcb);//更新磁盘的fcb
	return 1;
}

void MyFSY::sys_delete(FCB fcb) //只删除fcb和更新fat表
{
	int n = fcb.first, next;
	std::string s;
	bool end = false;
	while(!end)
	{
		if (fat1.state[n] == END)
			end = true;
		next = fat1.state[n];
		disk.disk_move(n);
		disk.disk_write(s, BLOCKSIZE);
		fat1.state[n] = FREE;
		fat2.state[n] = FREE;
		n = next;
	}
	for (int i = 0; i < nowDir.fcb.num_son; i++)
	{
		if (fcb.first == nowDir.fcb.son[i])
		{
			for (int j = i; j < nowDir.fcb.num_son - 1; j++)
				nowDir.fcb.son[j] = nowDir.fcb.son[j + 1];
			nowDir.fcb.num_son--;
			break;
		}
	}
	write_fcb(nowDir.fcb);
	update_fat();
}

int MyFSY::sys_opendir(FCB fcb)
{
	if (fcb.free == 0)
		return 0;
	nowDir.dir_first[++nowDir.dir_ser] = fcb.first;
	nowDir.fcb = fcb;
	for (int i = 0; i < fcb.num_son; i++)
		nowDir.fcb.son[i] = fcb.son[i];
	return 1;
}

int MyFSY::sys_closedir()
{
	if (nowDir.dir_ser == 0)
		return -1;
	get_fcb(nowDir.dir_first[--nowDir.dir_ser], nowDir.fcb);
	return 1;
}

int MyFSY::sys_mkfile(std::string filename)
{
	//创建文件时只新建一个fcb，要写入文件内容就调用sys_write_file
	if (nowDir.fcb.num_son == MAXSON)
		return 0;
	for (int i = 0; i < nowDir.fcb.num_son; i++)
	{
		FCB tfcb;
		get_fcb(nowDir.fcb.son[i], tfcb);
		if (tfcb.attribute == '1' && strcmp(tfcb.filename, filename.c_str()) == 0)
			return -1;
	}
	//分配块，更新FAT表
	int first = -1;
	for (int i = 0; i < BLOCKNUM; i++)
	{
		if (fat1.state[i] == FREE)
		{
			first = i;
			break;
		}
	}
	if (first == -1)
		return 3; //空间不足分配失败
	FCB fcb;
	fcb.Init(filename, '1', first, FCBSIZE);
	fat1.state[fcb.first] = END;
	fat2.state[fcb.first] = END;
	write_fcb(fcb);
	nowDir.fcb.son[nowDir.fcb.num_son++] = fcb.first;
	write_fcb(nowDir.fcb);//更新磁盘的fcb
	return 1;
}

int MyFSY::sys_write_file(FCB& fcb, std::string content)
{
	if (fcb.attribute == '0')
		return -1;
	int len = content.length() + 1;//预留'\0'，计算所需空间大小
	int m;
	if (len % BLOCKSIZE == 0)
		m = len / BLOCKSIZE;
	else
		m = len / BLOCKSIZE + 1;
	//分配块，更新FAT表
	int j = fcb.first;
	int temp = j;
	bool flag = true;
	for (int i = 0; i < m;)
	{
		j++;
		if (j >= BLOCKNUM - 1)//块不够了
		{
			flag = false;
			break;
		}
		if (fat1.state[j] == FREE)
		{
			fat1.state[temp] = j;
			temp = j;
			i++;
		}
	}
	if (flag)//分配fat成功，备份到fat2并写入磁盘
	{
		fat1.state[j] = END;
		for (int i = 0; i < BLOCKNUM; i++)
			fat2.state[i] = fat1.state[i];
		fcb.length += content.length();
		update_fat();
		write_fcb(fcb);
		write_byFAT(fcb.first, content);//根据fat表写入磁盘
		return 1;
	}
	else//分配fat失败，回到原来的备份
	{
		for (int i = 0; i < BLOCKNUM; i++)
			fat1.state[i] = fat2.state[i];
		return 0;
	}
}

int MyFSY::sys_read_file(FCB fcb, std::string& s)
{
	if (fcb.attribute == '0')//不是数据文件
		return -1;
	read_byFAT(fcb.first, s);//按FAT表读入到s
	return 1;
}

void MyFSY::write_byFAT(unsigned short first, std::string content)
{
	std::string buf;  //缓冲区
	int next = fat1.state[first]; //第一个块是FCB，下一个就是数据文件
	for (int i = 0; i < content.size(); i++)
	{
		buf.push_back(content[i]);//写入到缓冲区
		if (buf.size() == BLOCKSIZE || i == content.size() - 1) //缓冲区满（写了一个块的字节）或者写完了
		{
			disk.disk_move(next); //移动到下一个块
			disk.disk_write(buf, BLOCKSIZE);//按块写入
			buf.clear();//清空缓冲
			if (next == END)
				break;
			next = fat1.state[next];//更新下一个块号
		}
	}
}

void MyFSY::read_byFAT(unsigned short first, std::string& content)
{
	content.clear();
	std::string buf;  //缓冲区
	int next = fat1.state[first]; //第一个块是FCB，下一个就是数据文件
	while (true)
	{
		if (next == END)
			break;
		disk.disk_move(next); //移动到下一个块
		disk.disk_read(buf, BLOCKSIZE);//按块读入
		content += buf;//从缓冲区写入到content
		buf.clear();//清空缓冲
		next = fat1.state[next];//更新下一个块号
	}
}
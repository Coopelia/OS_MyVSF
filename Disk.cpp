#include"Disk.h"

Disk::Disk()
{
	this->nowPtr = 0;
	this->maxsize = SIZE;
	this->restsize = SIZE;
	this->vhard.resize(SIZE);
}

Disk::~Disk()
{

}

int Disk::disk_write(std::string s, int length)
{
	int temp = nowPtr;
	bool flag = true;
	for (int i = 0; i < length; i++)
	{
		if (nowPtr >= SIZE)
		{
			flag = false;
			break;
		}
		if (i < s.length())
			vhard[nowPtr++] = s[i];
		else
			vhard[nowPtr++] = '\0';
	}
	if (flag)
	{
		restsize -= length;
		return 1;
	}
	else
	{
		for (int i = temp; i <nowPtr; i++)
			vhard[i] = '\0';
		nowPtr = temp;
		return 0;
	}
}

bool Disk::disk_read(std::string& s, int length)
{
	bool flag = true;
	for (int i = 0; i < length; i++)
	{
		if (nowPtr >= SIZE)
		{
			flag = false;
			break;
		}
		s.push_back(vhard[nowPtr++]);
	}
	return flag;
}

int Disk::disk_remove(int start, int end)
{
	if (start > end || end >= SIZE - 1)
		return 0;
	for (int i = start; i <= end; i++)
		vhard[i] = '\0';
	restsize += end - start + 1;
	return 1;
}

int Disk::disk_next(int flag)
{
	if (flag == 0)
	{
		if (nowPtr >= SIZE-1)
			return 0;
		if (nowPtr % BLOCKSIZE != 0)
			nowPtr = (nowPtr / 1024 + 1) * 1024;
	}
	else
	{
		if (nowPtr >= SIZE - 1)
			return 0;
		nowPtr = (nowPtr / 1024 + 1) * 1024;
	}
	return 1;
}

void Disk::disk_format()
{
	this->nowPtr = 0;
	this->maxsize = SIZE;
	this->restsize = SIZE;
	this->vhard.resize(SIZE);
}

int Disk::disk_move(int m)
{
	if (m > BLOCKNUM - 1)
		return 0;
	nowPtr = m * 1024;
	return 1;
}
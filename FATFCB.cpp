#include"FATFCB.h"

FCB::FCB()
{
    this->attribute = 0;
    for (int i = 0; i < EXNAMESIZE; i++)
        this->exname[i] = '\0';
    for (int i = 0; i < FILENAMESIZE; i++)
        this->filename[i] = '\0';
    this->first = 0;
    this->free = 0;
    this->length = 0;
    memset(m_data, 0, sizeof(m_data));
    memset(m_time, 0, sizeof(m_time));
    this->num_son = 0;
    for (int i = 0; i < MAXSON; i++)
        this->son[i] = 0;
}

FCB::FCB(const FCB& e)
{
    this->attribute = e.attribute;
    for (int i = 0; i < 8; i++)
        this->m_data[i] = e.m_data[i];
    for (int i = 0; i < 6; i++)
        this->m_time[i] = e.m_time[i];
    for (int i = 0; i < EXNAMESIZE; i++)
        this->exname[i] = e.exname[i];
    for (int i = 0; i < FILENAMESIZE; i++)
        this->filename[i] = e.filename[i];
    this->first = e.first;
    this->free = e.free;
    this->length = e.length;
    this->num_son = e.num_son;
    for (int i = 0; i < MAXSON; i++)
        this->son[i] = e.son[i];
}

void FCB::Init(std::string filename, unsigned char attribute, unsigned short first, unsigned long length)
{
    this->attribute = attribute;
    strcpy_s(this->filename, filename.c_str());
    if(attribute=='0')
        strcpy_s(this->exname, "");
    else 
        strcpy_s(this->exname, "txt");
    std::stringstream ss;
    int ret = get_now_data();
    ss << ret;
    for (int i = 0; i < 8; i++)
        ss >> this->m_data[i];
    ret = get_now_time();
    ss.clear();
    if (ret == 0)
    {
        ss << "000000";
        for (int i = 0; i < 6; i++)
            ss >> this->m_time[i];
    }
    else
    {
        if (ret / 100000 == 0)
            ss << "0";
        ss << ret;
        for (int i = 0; i < 6; i++)
            ss >> this->m_time[i];
    }
    this->first = first;
    this->length = length;
    this->free = 1;
    this->num_son = 0;
}

int FCB::get_now_data()
{
    time_t tt = time(NULL);
    struct tm t;
    localtime_s(&t, &tt);
    int data = 0;
    data += (t.tm_year + 1900) * 10000;
    data += (t.tm_mon + 1) * 100;
    data += t.tm_mday;
    return data;
}

int FCB::get_now_time()
{
    time_t tt = time(NULL);
    struct tm t;
    localtime_s(&t, &tt);
    int ttime = 0;
    ttime += (t.tm_hour) * 10000;
    ttime += (t.tm_min) * 100;
    ttime += t.tm_sec;
    return ttime;
}

void FCB::remove(int a)
{
    int j = 0;
    for (int i = 0; i < num_son; i++)
    {
        if (son[i] == a)
        {
            j = i;
            break;
        }
    }
    for (int i = j; i < MAXSON-1; i++)
        son[i] = son[i + 1];
    son[MAXSON - 1] = 0;
    num_son--;
    this->length -= FCBSIZE;
}

void FCB::add(int a)
{
    this->son[num_son++] = a;
    this->length += FCBSIZE;
}
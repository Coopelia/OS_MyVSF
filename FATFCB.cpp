#include"FATFCB.h"

FCB::FCB()
{
    this->attribute = 0;
    this->m_data = 0;
    for (int i = 0; i < EXNAMESIZE; i++)
        this->exname[i] = '\0';
    for (int i = 0; i < FILENAMESIZE; i++)
        this->filename[i] = '\0';
    this->first = 0;
    this->free = 0;
    this->length = 0;
    this->m_time = 0;
    this->num_son = 0;
    for (int i = 0; i < MAXSON; i++)
        this->son[i] = 0;
}

FCB::FCB(const FCB& e)
{
    this->attribute = e.attribute;
    this->m_data = e.m_data;
    for (int i = 0; i < EXNAMESIZE; i++)
        this->exname[i] = e.exname[i];
    for (int i = 0; i < FILENAMESIZE; i++)
        this->filename[i] = e.filename[i];
    this->first = e.first;
    this->free = e.free;
    this->length = e.length;
    this->m_time = e.m_time;
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
    this->m_data = get_now_data();
    this->m_time = get_now_time();
    this->first = first;
    this->length = length;
    this->free = 1;
    this->num_son = 0;
}

unsigned short FCB::get_now_data()
{
    time_t tt = time(NULL);
    struct tm t;
    localtime_s(&t, &tt);
    int data = 0;
    data += (t.tm_year + 1900) * 10000;
    data += (t.tm_mon + 1) * 100;
    data += t.tm_mday;
    return (unsigned short)data;
}

unsigned short FCB::get_now_time()
{
    time_t tt = time(NULL);
    struct tm t;
    localtime_s(&t, &tt);
    int ttime = 0;
    ttime += (t.tm_hour) * 10000;
    ttime += (t.tm_min) * 100;
    ttime += t.tm_sec;
    return (unsigned short)ttime;
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
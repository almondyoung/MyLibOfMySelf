#ifndef __MYTIME__
#define __MYTIME__

#include "windows.h"
#include "stdio.h"
#include "time.h"
#include "MyString.h"

#define MAX_TIMESTR_LEN  40

class CMyTime  
{
public:
	CMyTime();
	CMyTime(SYSTEMTIME time);
	virtual ~CMyTime();
	
	CMyString	GetDateString();  //��ȡ����ʱ��	
	CMyString	GetWeekString(bool EnOrCn=true);  //��ȡ����ʱ��
	CMyString	GetHourString();  //��ȡСʱʱ��
	CMyString	GetTimeString(bool EnOrCn=true);  //��ȡ����Сʱʱ��

	unsigned	GetDay(){return m_Time.wDay;}
	unsigned	GetYear(){return m_Time.wYear;}
	unsigned	GetMonth(){return m_Time.wMonth;}
	unsigned	GetHour(){return m_Time.wHour;}
	unsigned	GetMinute(){return m_Time.wMinute;}
	unsigned	GetSecond(){return m_Time.wSecond;}
	unsigned	GetWeek(){return m_Time.wDayOfWeek;}
	unsigned	GetMilliseconds(){return m_Time.wMilliseconds;}
	unsigned	GetTotalSecond(){time_t t;return time(&t);}//��1700��Ԫ�������ھ���������

	static CMyTime	GetCurrentTime(); //���ص�ǰʱ��
private:
	int				InitalTime(SYSTEMTIME time);

	static CMyString	m_WeekStrCN[];
	static CMyString	m_WeekStrEN[];
private:
	SYSTEMTIME	m_Time;
};

#endif
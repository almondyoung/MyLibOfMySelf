#ifndef __MYTIME__
#define __MYTIME__

#include "windows.h"
#include "stdio.h"
#include "time.h"
#include "MyString.h"

#define MAX_TIMESTR_LEN  40

class CMyTimeInterval
{
public:
	CMyTimeInterval();
	//����ʱ�������밴��λ��С��λ�������ã����������ܴ���(���簳˳�� �� Сʱ ���� ���� ����)

	void	SetDays(int days);
	void	SetHours(int hours);
	void	SetMinutes(int minutes);
	void	SetSeconds(int seconds);
	void	SetMilliseconds(int milliseconds);

	void    SetSingal(bool plus){m_Singal=plus;}

	int		GetDays(){return m_TimeInterval.wDay;}
	int		GetHours(){return m_TimeInterval.wHour;}
	int		GetMinutes(){return m_TimeInterval.wMinute;}
	int		GetSeconds(){return m_TimeInterval.wSecond;}
	int		GetMilliseconds(){return m_TimeInterval.wMilliseconds;}
	int		GetSingal(){return m_Singal;}
	
	int		Reset(){memset(&m_TimeInterval,0,sizeof(m_TimeInterval));}

	friend class CMyTime;

	void	HoursAdd(int inc);
	void	MinuteAdd(int inc);
	void	SecondAdd(int inc);
private:
	SYSTEMTIME	m_TimeInterval;
	bool		m_Singal;
};


class CMyCalendar
{
public:
	enum Week
	{
		MONDAY=0,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};

public:
	CMyCalendar();
	CMyCalendar(int year,int month,int day);

	static bool		IsLeapYear(int year);
	static Week		GetWeek(int year,int month,int day);
	static int		MonthDays(int year,int month);
	static int		YearDays(int year);
	static int		YearDaysLess(int year,int month,int day);
	//daysΪ�µ�һ�꿪ʼ�����ڵ�����,������һ��ļ��¼���
	static int		MonthDayInYear(int year,int days,int& day);

	

	unsigned	GetDay(){return m_Time.wDay;}
	unsigned	GetYear(){return m_Time.wYear;}
	unsigned	GetMonth(){return m_Time.wMonth;}
	Week		GetWeek(){return (Week)m_Time.wDayOfWeek;}

	CMyString	GetDateInArab();//������д��  yy-mm-dd

	CMyString	GetWeekEN();		//��ȡ����
	CMyString	GetWeekCN();

	CMyString   GetDateInEN();
	CMyString	GetDateInEnSimple();//Ӣ�ļ�д
	CMyString	GetDateInCN();

	CMyCalendar&	operator-=(CMyTimeInterval& timeInterval);
	CMyCalendar&	operator+=(CMyTimeInterval& timeInterval);
	CMyTimeInterval operator-(CMyCalendar time);
	bool			operator<(CMyCalendar& time);
	bool			operator>(CMyCalendar& time);
	bool			operator==(CMyCalendar& time);
	bool			operator>=(CMyCalendar& time);
	bool			operator!=(CMyCalendar& time);

	friend class CMyTime;

	static char*	sWeekEn[];
	static char*	sWeekCn[];
	static char*	sWeekEnS[];
	static char  	sMonthDays[13];
	static char*	sMonth[];
	static char*	sMonthS[];
private:
	
	int			InitalTime(SYSTEMTIME time);
	
private:
	SYSTEMTIME	m_Time;	
};

class CMyTime  
{
public:
	CMyTime();
	CMyTime(int year,int month,int day,int hour=0,int minute=0,int second=0,int milliseconds=0);
	CMyTime(SYSTEMTIME time);
	virtual ~CMyTime();

	 //��ȡСʱʱ��
	CMyString	GetHourString(); 

	//��ʽ��Ϊ�ַ���
	CMyString	ToStringEn();
	CMyString	ToStringCn();

	unsigned	GetDay(){return m_Calendar.m_Time.wDay;}
	unsigned	GetYear(){return m_Calendar.m_Time.wYear;}
	unsigned	GetMonth(){return m_Calendar.m_Time.wMonth;}
	unsigned	GetHour(){return m_Calendar.m_Time.wHour;}
	unsigned	GetMinute(){return m_Calendar.m_Time.wMinute;}
	unsigned	GetSecond(){return m_Calendar.m_Time.wSecond;}
	unsigned	GetWeek(){return m_Calendar.m_Time.wDayOfWeek;}
	unsigned	GetMilliseconds(){return m_Calendar.m_Time.wMilliseconds;}

	//��1700��Ԫ�������ھ���������
	unsigned	GetTotalSecond(){time_t t;return time(&t);}
	
	//������д��  yy-mm-dd
	CMyString	GetDateInArab(){return m_Calendar.GetDateInArab();}

	//��ȡ����
	CMyString	GetWeekEN(){return m_Calendar.GetWeekEN();}		
	CMyString	GetWeekCN(){return m_Calendar.GetWeekCN();}

	CMyString   GetDateInEN(){return m_Calendar.GetDateInEN();}
	//Ӣ�ļ�д
	CMyString	GetDateInEnSimple(){return m_Calendar.GetDateInEnSimple();}
	CMyString	GetDateInCN(){return m_Calendar.GetDateInCN();}

	//���ص�ǰʱ��
	static CMyTime	GetCurrentTime(); 

	//��ȷ�����뼶��
	bool		operator<(CMyTime& time);
	bool		operator>(CMyTime& time);
	bool		operator==(CMyTime& time);
	bool		operator>=(CMyTime& time);

	CMyTime& 	operator-=(CMyTimeInterval& timeInterval);
	CMyTime&	operator+=(CMyTimeInterval& timeInterval);
	CMyTimeInterval operator-(CMyTime time);
	CMyCalendar	GetCalendar();

private:
	static unsigned	GetTotalSecond(unsigned hour,unsigned minute,unsigned second);

private:
	CMyCalendar	m_Calendar;
};

#endif
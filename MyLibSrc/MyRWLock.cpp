#include "MyRWLock.h"
#include "common.h"

CMyRWLock::CMyRWLock()
{
	InitializeCriticalSection(&m_CS);
	m_Active	=0;
	m_WaitWriter=0;
	m_WaitReader=0;
	m_WriteSemaphore=CreateSemaphore(0,1,NULL);
	m_ReadSemaphore =CreateSemaphore(0,0X7FFFFFFF,NULL);
}

CMyRWLock::~CMyRWLock()
{
	DeleteCriticalSection(&m_CS);
	DeleteSemaphore(m_WriteSemaphore);
	DeleteSemaphore(m_ReadSemaphore);
}

void CMyRWLock::WaitRead()
{
	bool needWait=true;
	EnterCriticalSection(&m_CS);
	//�����ʱ��д�ߵȴ�����ô�����Ķ���Ҳת��ȴ�״̬����ֹд�߶���
	needWait=m_WaitWriter||(m_Active<0);
	if(needWait)
	{
		m_WaitReader++;
	}
	else
	{
		m_Active++;
	}
	LeaveCriticalSection(&m_CS);
	if(needWait)
	{
		GetSemaphore(m_ReadSemaphore,-1);
	}
}

void CMyRWLock::WaitWrite()
{
	bool needWait=true;
	EnterCriticalSection(&m_CS);
	if(m_Active==0)
	{
		needWait=false;
	}
	if(needWait)
	{
		m_WaitWriter++;
	}
	else
	{
		m_Active=-1;
	}
	LeaveCriticalSection(&m_CS);
	if(needWait)
	{
		GetSemaphore(m_WriteSemaphore,-1);
	}
}

void CMyRWLock::Done()
{
	HANDLE tempHander=NULL;
	int    counter=1;
	EnterCriticalSection(&m_CS);
	if(m_Active>0)
	{
		//�����ڷ�����Դ
		m_Active--;
	}
	else
	{
		m_Active++;
	}
	if(m_Active==0)
	{
		if(m_WaitWriter>0)
		{
			//д�����ȴ���
			m_Active=-1;
			m_WaitWriter--;
			tempHander=m_WriteSemaphore;
		}
		else if(m_WaitReader>0)
		{
			m_Active=m_WaitReader;
			m_WaitReader=0;
			tempHander=m_ReadSemaphore;
			counter=m_Active;
		}
	}
	LeaveCriticalSection(&m_CS);
	if(tempHander)
	{
		ReleaseSemaphore(tempHander,counter);
	}
}

int CMyRWLock::GetReaderNum()
{
	int r;
	EnterCriticalSection(&m_CS);
	r	=m_WaitReader;
	LeaveCriticalSection(&m_CS);
	return r;
}

int CMyRWLock::GetWriterNum()
{
	int r;
	EnterCriticalSection(&m_CS);
	r	=m_WaitWriter;
	LeaveCriticalSection(&m_CS);
	return r;
}
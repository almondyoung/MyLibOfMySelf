#ifndef __MYTHREAD__
#define __MYTHREAD__
#include <windows.h>
#include "common.h"
#include "process.h"

typedef unsigned int (__stdcall *_beginthreadex_type)( void * );

class CMyThread  
{
public:
	struct ThreadInfo
	{
		CMyThread*  m_Obj;			//�߳�ʹ����
		void*		m_Param;       //�̺߳�������
		DWORD		m_ThreadID;
		int			m_RunVaule;    //run�ķ���ֵ
	};

public:
	CMyThread();
	virtual ~CMyThread();

	virtual HANDLE Start(void *param)
	{
		if(!isStop())return m_ThreadHandle;
		m_Info.m_Obj=this;
		m_Info.m_Param=param;
		m_ThreadHandle= (HANDLE)_beginthreadex(NULL,0,(_beginthreadex_type)(ThreadProc),(void*)&m_Info,0,(unsigned int *)&m_Info.m_ThreadID);
		m_State	=RUNNING;
		return m_ThreadHandle;
	}

	virtual int			Run(void *param){return 1;}
	virtual void		OnThreadBeforeTerminate(){}//���̱߳�ǿ����ֹǰ����

	bool	isRun(){return m_State==RUNNING;}
	bool	isSuspend(){return m_State==SUSPEND;}
	bool	isStop(){return m_State==STOP;}
	long	SuspendThread();
	long	ResumeThread();
	
	void	Sleep(int time){::Sleep(time);}

	DWORD	GetThreadID(){return m_Info.m_ThreadID;}
	HANDLE	GetThreadHandle(){return m_ThreadHandle;}
	int		GetRunValue(){return m_Info.m_RunVaule;}
	
	static int ThreadProc(void *param);
private:
	//�˺������ڲ�����
	void ExitThread();
private:
	//�߳�״̬
	typedef enum 
	{
		SUSPEND,       //����
		RUNNING,	   //����
		STOP
	} THREAD_STATE;

	THREAD_STATE				m_State; 
	ThreadInfo			    	m_Info;
	HANDLE						m_ThreadHandle;
protected:
	
};

#endif
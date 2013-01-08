#ifndef __MY_TASK__
#define __MY_TASK__

#include "MyThread.h"
#include "MyDebug.h"
#include <queue>

using namespace std;

class CMyTask
{
public:
	CMyTask():m_ThreadOutWhenFinish(false)
	{}
	virtual ~CMyTask()
	{}

	virtual int		Excute(void *threadArg,void* taskArg){return -1;}

	void			SetThreadOutWhenTaskFinish(bool out=false){m_ThreadOutWhenFinish=out;}
	bool			GetThreadOutWhenTaskFinish(){return m_ThreadOutWhenFinish;}
private:
	bool			m_ThreadOutWhenFinish;  //���������Ƿ���ִ������߳��˳�
};


class CMyTaskThread :public CMyThread
{
public:
	typedef struct _TASK_INFO
	{
		CMyTask*	iTask;
		void*		iTaskArg;
	}TASK_INFO;

	typedef enum TASK_THREAD_STATE
	{
		WAITTING,
		BUSYING
	};

public:
	CMyTaskThread();
	virtual ~CMyTaskThread();
	
	virtual int		Run(void *param);
	virtual HANDLE	Start(void *param);
	//���߳̽�Ҫ��ǿ����ֹǰ�����������߳�
	virtual	void	OnThreadBeforeTerminate(){ExitThreadDirect();}
	void			AssignTask(CMyTask& task,void* taskArg);
	
	//����ģʽ
	void			ExitThread();   //�����˳��̣߳���������������������ִ���������˳�
	void			ExitThreadDirect(); //ִ���굱ǰ������˳�
	//������ģʽ
	void			WillExitThread();

	bool			IsBusy(){return m_State==BUSYING;}
	int				GetTaskCount();

private:
	bool		IsSelfThread();

private:
	std::queue<_TASK_INFO>		m_TaskList;
	HANDLE					m_Mutex;   //����m_TaskList
	HANDLE					m_Notify;  //��ָ�ɵ������ʱ��ᴥ��
	bool					m_ExitDirect;  //�Ƿ�ֱ���˳�
	bool					m_Exit;			//�߳̽�Ҫ�˳�
	CMyTask					m_ExitTask;     //�ڲ������˳��õ�����

	int						m_State;        //�������״̬					
};

#endif
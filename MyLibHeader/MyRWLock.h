#include "windows.h"
#ifndef __MY_RWLOCK__
#define __MY_RWLOCK__

#define MAX_READER (20)
class CMyRWLock  
{
public:
	CMyRWLock();
	virtual ~CMyRWLock();
	void	WaitRead();
	void	WaitWrite();
	void	Done();
	int		GetReaderNum();
	int		GetWriterNum();
private:
	int m_Active;            //��>0����ʾ��ǰ��������<0��д���ߣ�0����
	int m_WaitReader;        //��ǰ�ȴ��Ķ�����Ŀ
	int m_WaitWriter;        //��ǰ�ȴ���д����Ŀ
	HANDLE m_WriteSemaphore; //д�ȴ��ź�
	HANDLE m_ReadSemaphore;  //���ȴ��ź�
	CRITICAL_SECTION m_CS;   //�ٽ��
};

#endif
#ifndef __COMMON__
#define __COMMON__
#include "windows.h"

#include "winbase.h"
#include "process.h"


#pragma   comment   (lib,"ws2_32.lib")
#define MAX_FILE_PATH (300)
#define START_DEBUG
//�¼�������
HANDLE CreateEvent(bool bManualReset,bool bInitialState,LPCTSTR pName);
bool   DeleteEvent(HANDLE hEvent);
DWORD	WaitEvent(HANDLE hEvent,long tWait);

//��������غ���
HANDLE CreateMutex(bool bInitialOwner,LPCTSTR pName);
bool   DeleteMutex(HANDLE hMutex);
DWORD  GetMutex(HANDLE hMutex);

//�ź�����غ���
HANDLE CreateSemaphore(LONG lInitialCount,LONG lMaximumCount,LPCTSTR pName);
DWORD  GetSemaphore(HANDLE hSemaphore,long tWait);
bool   ReleaseSemaphore(HANDLE hSemaphore);
bool   ReleaseSemaphore(HANDLE hSemaphore,int count);
int    ReleaseSemaphoreWithPrev(HANDLE hSemaphore,int count); //������ǰ��countֵ
int    ReleaseSemaphoreWithPrev(HANDLE hSemaphore);			  //������ǰ��countֵ
bool   DeleteSemaphore(HANDLE hSemaphore);

//��ȡ���������ļ�·��
int	   GetSlefPath(LPCTSTR fpath,int bufSize);

int	   WaitForMultiGroupHander(int groups,HANDLE *groupHanders,int tWait);

//��������ӵ�е���Ȩ��
bool   DebugPrivilegeEnable(bool Enable=true);

//����ڴ��ַ����
bool   AddProtect(void *addr,int memSize);
bool   AddProtect(HANDLE processHandle,void *addr,unsigned long &proctect);
//ȥ���ڴ��ַ������ʹ�ڴ�����ɶ�����д����ִ��
bool   RemoveProtect(void *addr,int memSize);
bool   RemoveProtect(HANDLE processHandle,void *addr,unsigned long &oldProctect);
//Զ��ע�뺯��,proHandleԶ�̽��̾��
void* InjectProcess(char *dllName,HANDLE proHandle);
#endif
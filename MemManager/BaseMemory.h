#ifndef __BASE_MEMORY__
#define __BASE_MEMORY__

#include "windows.h"

#define GET_MEM_ITEM_DATA(_INDEX)	((void*)((char*)m_MemArea+(_INDEX)*(m_ItemSize+8)))

#define Mem_Item_Prev(_index) (*((int*)((char*)m_MemArea+(_index)*(m_ItemSize+8)+m_ItemSize)))
#define Mem_Item_Next(_index) (*((int*)((char*)m_MemArea+(_index)*(m_ItemSize+8)+m_ItemSize+4)))

class CBaseMemory  
{
public:
	CBaseMemory()
	{
		m_LockMark	=0x00000001;
	}

	virtual ~CBaseMemory(){}
	
	virtual void	InitalMemory(void* mem,unsigned long memLen,unsigned long itemLen)=0;

	virtual void*	Alloc()=0;
	virtual void	Free(void* memItem)=0;

	void*	AllocMem()
	{
		void *p=0;
		if(m_LockMark&1)Lock();
		p=Alloc();
		if(m_LockMark&1)UnLock();
		return p;
	}

	void	FreeMem(void *memItem)
	{
		if(m_LockMark&1)Lock();
		Free(memItem);
		if(m_LockMark&1)UnLock();
	}

	void	ClearLockMark()
	{
		m_LockMark	=0x00000000;
	}

private:

	virtual	void	Lock()
	{
	}

	virtual void	UnLock()
	{
	}

private:
	virtual bool	IsEmpty()=0;
	virtual bool	IsFull()=0;	

protected:
	int				m_LockMark;
};

class CBaseMemLock
{
public:
	CBaseMemLock(){}
	virtual ~CBaseMemLock(){}

	virtual	void	Lock()=0;
	virtual void	UnLock()=0;
};

class CLinKMemory:public CBaseMemory
{
public:
	CLinKMemory();
	virtual ~CLinKMemory();
	virtual void	InitalMemory(void* mem,unsigned long memLen,unsigned long itemLen);
	virtual void*	Alloc();
	virtual void	Free(void *memItem);
private:
	virtual bool	IsEmpty(){return (m_ItemCount==0);}
	virtual bool	IsFull(){return (m_MaxItem==m_ItemCount);}	

	virtual	void	Lock();
	virtual void	UnLock();
private:
	void*				m_MemArea; //�ڴ�������
	unsigned long		m_MemSize; //��������д	
	
	unsigned long		m_MaxItem; //����_T����,����������д�����������item��	
	unsigned long		m_ItemCount;
	unsigned long		m_ItemSize;
	
	unsigned long		m_DataHeader;  //��ͷ
	unsigned long		m_DataEnd;
	unsigned long		m_FreeHeader;  //���пռ���ͷ
	
	CBaseMemLock*		m_Lock;
};

class CMemLock:public CBaseMemLock
{
public:
	CMemLock()
	{
		m_Lock	=::CreateMutex(NULL,false,NULL);
	}

	virtual	void	Lock()
	{
		if(m_Lock)WaitForSingleObject(m_Lock,-1);
	}

	virtual void	UnLock()
	{
		if(m_Lock)ReleaseMutex(m_Lock);
	}

private:
	HANDLE			m_Lock;
};
#endif
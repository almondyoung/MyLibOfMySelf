#ifndef __MY_ARRAYLIST__
#define	__MY_ARRAYLIST__
//����ģ�������

#include "MyDebug.h"
template<class _T>
class CMyArrayList  
{
	struct _Item
	{
		_T		iData;
		int		iNext;
	};

	public:
		CMyArrayList(){};
		virtual ~CMyArrayList(){};
		
		//����һ���Ѿ������������ڴ�
		int	AttachMem(void *mem,int memSize,int dataHead,int dataEnd,int freeHead,int itemCount)
		{
			m_MemData	=(_Item*)mem;
			m_MemSize	=memSize;
			m_MaxItem	=memSize/sizeof(_Item);
			m_ItemCount	=itemCount;
			m_DataHeader=dataHead;
			m_FreeHeader=freeHead;
			m_DataEnd	=dataEnd;
			return 1;
		}

		int	ExportArrayListInfo(int &dataHead,int &dataEnd,int &freeHead,int &itemCount)
		{
			dataHead	=m_DataHeader;
			dataEnd		=m_DataEnd;
			freeHead	=m_FreeHeader;
			itemCount	=m_ItemCount;
			return 1;
		}

		void SetMem(void *mem,int memSize)
		{
			m_MemData	=(_Item*)mem;
			m_MemSize	=memSize;
			m_MaxItem	=memSize/sizeof(_Item);
			m_ItemCount	=0;
			m_DataHeader=-1;
			m_FreeHeader=0;
			m_DataEnd	=-1;
			for(int i=0;i<m_MaxItem-1;i++)
				m_MemData[i].iNext=i+1;
			m_MemData[m_MaxItem-1].iNext=-1;
		}
		
		int	AddItem(_T &item)   //�������ڵ�����
		{
			if(IsFull())return -1;
			if(m_DataHeader==-1)
			{
				m_DataHeader	=m_FreeHeader;
				m_DataEnd		=m_DataHeader;
			}
			else
			{
				m_MemData[m_DataEnd].iNext	=m_FreeHeader;
			}
			int pos	=m_FreeHeader;
			m_FreeHeader	=m_MemData[m_FreeHeader].iNext;
			m_MemData[pos].iNext	=-1;
			m_MemData[pos].iData	=item;
			m_DataEnd				=pos;
			m_ItemCount++;
			return m_ItemCount-1;
			
		}

		int	DelItem(int index)
		{
			if(index>=m_ItemCount)return -1;
			int pos=m_DataHeader,pre;
			while(index)
			{
				pre		=pos;
				pos		=m_MemData[pos].iNext;
				index--;
			}
			if(pos==m_DataHeader)
				m_DataHeader=m_MemData[pos].iNext;
			else
				m_MemData[pre].iNext	=m_MemData[pos].iNext;

			if(pos==m_DataEnd)
				m_DataEnd	=pre;

			m_MemData[pos].iNext	=m_FreeHeader;
			m_FreeHeader			=pos;
			m_ItemCount--;
			if(!m_ItemCount)m_DataEnd	=-1;
			return 1;
		}

		int	InsertItem(_T &item,int index)  //���뵽index���ڵ�λ��
		{
			if(IsFull())return -1;
			if(index>=m_ItemCount)return -1;
			int pos=m_DataHeader,pre;
			while(index)
			{
				pre		=pos;
				pos		=m_MemData[pos].iNext;
				index--;
			}
			
			m_MemData[m_FreeHeader].iNext	=pos;
			if(pos==m_DataHeader)
				m_DataHeader	=m_FreeHeader;
			else
				m_MemData[pre].iNext	=m_FreeHeader;
			
			m_MemData[m_FreeHeader].iData	=item;
			m_FreeHeader	=m_MemData[m_FreeHeader].iNext;
			m_ItemCount++;
			return m_ItemCount-1;
		}
		
		int	GetItem(int index,_T &item)
		{
			if(index>=m_ItemCount)return -1;
			int pos=m_DataHeader;
			while(index)
			{
				pos		=m_MemData[pos].iNext;
				index--;
			}
			item=m_MemData[pos].iData;
			return 1;
		}

		int			GetItemCount(){return m_ItemCount;}	  //�����Ѵ洢��item��
		int			GetListSpace(){return m_MaxItem;}   //��������洢����
		bool		IsEmpty(){return (m_ItemCount==0);}
		bool		IsFull(){return (m_MaxItem==m_ItemCount);}

		int	Clear()
		{
			m_ItemCount	=0;
			m_DataHeader=-1;
			m_FreeHeader=0;
			m_DataEnd	=-1;
			_Item*	array=(_Item*)m_MemData;
			for(int i=0;i<m_MaxItem-1;i++)
				array[i].iNext=i+1;
			array[m_MaxItem-1].iNext=-1;
			return 1;
		}

		int	SetItem(int index,_T &item)
		{
			if(index>=m_ItemCount)return -1;
			int pos=m_DataHeader;
			while(index)
			{
				pos		=m_MemData[pos].iNext;
				index--;
			}
			m_MemData[pos].iData=item;
			return 1;
		}
private:

	_Item*		m_MemData; //�ڴ�������
	int			m_MemSize; //��������д	
	
	int			m_MaxItem; //����_T����,����������д�����������item��	
	int			m_ItemCount;
	
	int			m_DataHeader;  //��ͷ
	int			m_DataEnd;
	int			m_FreeHeader;  //���пռ���ͷ	
};

#endif
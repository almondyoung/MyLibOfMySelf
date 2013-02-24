#ifndef __SPIDER_CONFIG__
#define __SPIDER_CONFIG__

#include "SpiderVirtualClass.h"
#include "SpiderFetchUrl.h"

class SpiderInterfaceConfig  
{
public:
	SpiderInterfaceConfig();
	virtual ~SpiderInterfaceConfig();
	
	int		AddUrlFilter(ISpiderUrlFilter *urlFilter);//���url���˹���
	int		SetErrorNotify(ISpiderErrorNotify* errorNotify); //���ô������Ѵ�����
	int		SetPageProcessMethod(ISpiderPageProcess* processMethod);//�������ݴ�����
	int		SetFileProcessMethod(ISpiderFileProcess* processMethod);//�������ݴ�����
	int		SetUrlModifyRule(ISpiderUrlModify* urlModify);//����url�޸���

	friend class SpiderThread;

private:
	void	Lock(){m_IsLock	=true;}
	void	UnLock(){m_IsLock=false;}

private:
	ISpiderErrorNotify*	m_ErrorNotify;
	ISpiderPageProcess*	m_PageProcess;
	ISpiderFileProcess*	m_FileProcess;
	ISpiderUrlModify*	m_UrlModify;
	ISpiderFetchUrl*	m_FetchUrl;
	std::vector<ISpiderUrlFilter*>	m_UrlFilterList;

	ISpiderFetchUrl		m_InnerFetchUrl;
	bool				m_IsLock;
};

#endif
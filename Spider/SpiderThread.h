#include "../MyLib.h"
#include "SpiderVirtualClass.h"

#define MAX_SPIDER_THREAD (30)
#define DEFAULT_SPIDER_THREAD (20)

class SpiderThread : public CMyThread  
{
public:
	typedef enum
	{
		SPIDER_DEPTH,
		SPIDER_BREAD
	}SpiderMode;

private:
	typedef struct
	{
		CMyString	iParentUrl;  //���ĸ���ҳ����ȡ��url
		CMyString	iUrl;        
	}FailUrlInfo;

public:
	SpiderThread();
	virtual ~SpiderThread();
	virtual int Run(void *param);

	int			SetSpiderMode(SpiderMode mode);          //������ȡģʽ����Ȼ��ȣ�
	int			AddUrlFilter(SpiderUrlFilter *urlFilter);//���url���˹���
	int			SetErrorNotify(SpiderErrorNotify* errorNotify); //���ô������Ѵ�����
	int			SetPageProcessMethod(SpiderPageProcess* processMethod);//�������ݴ�����
	int			SetFileProcessMethod(SpiderFileProcess* processMethod);//�������ݴ�����
	int			SetUrlModifyRule(SpiderUrlModify* urlModify);//����url�޸���
	int			SetPageUrlSort(SpiderUrlListSort* urlListSort);//���ö�ҳ��url�����������
	int			SetMaxThread(int count);
	void		End();

private:
	typedef CMyHashMap<CMyString,void*> FirstHashMap;
	typedef CMyHashMap<CMyString,CMyString> SecondHashMap;
private:

	SpiderMode			m_SpiderMode;
	SpiderErrorNotify*	m_ErrorNotify;
	SpiderPageProcess*	m_PageProcess;
	SpiderFileProcess*	m_FileProcess;
	SpiderUrlModify*	m_UrlModify;
	SpiderUrlListSort*	m_UrlListSort;
	std::vector<SpiderUrlFilter*>	m_UrlFilterList;

	CMyAsyncHttp		m_Http[MAX_SPIDER_THREAD];
	FirstHashMap		m_MainHashMap;
	CMyThreadPool		m_ThreadPool;

	std::vector<FailUrlInfo>	m_FailList;  //����ʧ��url��Ϣ��,���ڽ����ٴγ���
};

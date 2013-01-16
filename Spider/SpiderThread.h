#include "../MyLib.h"
#include "SpiderVirtualClass.h"
#include "Url.h"
#include "SpiderHttp.h"

#define MAX_SPIDER_THREAD (30)
#define DEFAULT_SPIDER_THREAD (20)

typedef bool (*UrlCmpFunc)(CMyString *str1,CMyString *str2);

static bool DefaultUrlSortCmpFun(CMyString *str1,CMyString *str2)
{
	return strcmp(str1->GetBuffer(),str2->GetBuffer())>0;
}

class SpiderThread : public CMyThread  
{
public:
	typedef enum
	{
		SPIDER_DEPTH,
		SPIDER_BREAD
	}SpiderMode;

	class HashCode
	{
	public:
		unsigned operator()(const CMyString &obj)
		{
			return ((CMyString&)obj).HashCode();
		}
	};

private:
	typedef struct
	{
		CMyString	iParentUrl;  //���ĸ���ҳ����ȡ��url
		CMyString	iUrl;        
	}UrlInfo;

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
	int			SetPageUrlSortFunc(UrlCmpFunc urlSortFunc);//���ö�ҳ��url�����������
	int			SetMaxThread(int count);
	void		End();

public:
	bool		GetNextUrl();
	void		AnalysisData(SpiderHttp* spiderHttp);
	bool		ErrorProcess(SpiderHttp* spiderHttp);
	void		AddHashMap(CMyString &host,CMyString &url);
	//����ֵ��ʾbuf���Ƿ����url
	bool		InitalFetchEngine(char *buf,int bufLen);
	void		ReBuildUrlIfNeed(CMyString &parentUrl,CMyString &url,CMyString &host);
	bool		HaveAcess(CMyString &host,CMyString &url);
	void		AddTempUrlList(CMyString &url);
	void		SortTempUrlList();
	void		AddAllUrlToUrlList(CMyString &host);
	bool		FetchUrl(CMyString &url);
	void		ClearUrlList();

	typedef CMyHashMap<CMyString,void*,HashCode> FirstHashMap;
	typedef FirstHashMap SecondHashMap;
private:

	SpiderMode			m_SpiderMode;
	SpiderErrorNotify*	m_ErrorNotify;
	SpiderPageProcess*	m_PageProcess;
	SpiderFileProcess*	m_FileProcess;
	SpiderUrlModify*	m_UrlModify;
	std::vector<SpiderUrlFilter*>	m_UrlFilterList;

	SpiderHttp			m_Http[MAX_SPIDER_THREAD];
	unsigned			m_HttpCount;
	FirstHashMap		m_MainHashMap;
	CMyThreadPool		m_ThreadPool;

	std::vector<UrlInfo*>	m_FailList;  //����ʧ��url��Ϣ��,���ڽ����ٴγ���
	std::vector<UrlInfo*>	m_UrlList;
	UrlInfo*				m_CurrentUrl;

	HANDLE				m_EndEvent;

	CMyRegex			m_Regex;
	char*				m_CurrentP;
	std::vector<CMyString*> m_TempList;
	UrlCmpFunc			m_UrlCmp;
};

#ifndef __SPIDER_THREAD__
#define	__SPIDER_THREAD__

#include "../MyLib.h"
#include "SpiderVirtualClass.h"
#include "Url.h"
#include "SpiderHttp.h"
#include "SpiderFetchUrl.h"
#include "SpiderConfig.h"

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

	SpiderInterfaceConfig*	GetSpiderInterfaceConfig(){return &m_InterfaceConfig;}

	int			SetSpiderMode(SpiderMode mode);          //������ȡģʽ����Ȼ��ȣ�
	int			SetPageUrlSortFunc(UrlCmpFunc urlSortFunc);//���ö�ҳ��url�����������
	int			SetFecthUrlRegex(char* regex);//������ȡurl��������ʽ
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
	void		RelocateUrl(SpiderHttp* spiderHttp);

	typedef CMyHashMap<CMyString,void*,HashCode> FirstHashMap;
	typedef FirstHashMap SecondHashMap;
private:

	SpiderMode			m_SpiderMode;
	CMyString			m_UrlRegex;
	CMyThreadPool		m_ThreadPool;
	SpiderHttp			m_Http[MAX_SPIDER_THREAD];
	unsigned			m_HttpCount;
	FirstHashMap		m_MainHashMap;

	std::vector<UrlInfo*>	m_FailList;  //����ʧ��url��Ϣ��,���ڽ����ٴγ���
	std::vector<UrlInfo*>	m_UrlList;
	UrlInfo*				m_CurrentUrl;

	HANDLE				m_EndEvent;
	CMyRegex			m_Regex;
	char*				m_CurrentP;
	std::vector<CMyString*> m_TempList;
	UrlCmpFunc			m_UrlCmp;

	static char*		TAG;

	SpiderInterfaceConfig	m_InterfaceConfig;
	bool				m_SameRegex;
};
#endif
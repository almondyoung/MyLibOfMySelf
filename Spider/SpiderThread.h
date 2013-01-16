#include "../MyLib.h"
#include "SpiderVirtualClass.h"
#include "Url.h"
#include "SpiderHttp.h"

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
	int			SetPageUrlSort(SpiderUrlListSort* urlListSort);//���ö�ҳ��url�����������
	int			SetMaxThread(int count);
	void		End();

public:
	void		GetNextUrl();
	void		AnalysisData(SpiderHttp* spiderHttp);
	bool		ErrorProcess(SpiderHttp* spiderHttp);
	static void		AddHashMap(CMyString &host,CMyString &url);
	//����ֵ��ʾbuf���Ƿ����url
	bool		InitalFetchEngine(char *buf,int bufLen);
	static void		ReBuildUrlIfNeed(CMyString &parentUrl,CMyString &url,CMyString &host);
	static bool		HaveAcess(CMyString &host,CMyString &url);
	void		AddTempUrlList(CMyString &url);
	void		SortTempUrlList();
	void		AddAllUrlToUrlList(CMyString &host);
	bool		FetchUrl(CMyString &url);

	static bool CompareUrl(const CMyString *url1,const CMyString *url2);

	typedef CMyHashMap<CMyString,void*,HashCode> FirstHashMap;
	typedef FirstHashMap SecondHashMap;
private:

	SpiderMode			m_SpiderMode;
	SpiderErrorNotify*	m_ErrorNotify;
	SpiderPageProcess*	m_PageProcess;
	SpiderFileProcess*	m_FileProcess;
	SpiderUrlModify*	m_UrlModify;
	SpiderUrlListSort*	m_UrlListSort;
	std::vector<SpiderUrlFilter*>	m_UrlFilterList;

	SpiderHttp			m_Http[MAX_SPIDER_THREAD];
	unsigned			m_HttpCount;
	static FirstHashMap		m_MainHashMap;
	CMyThreadPool		m_ThreadPool;

	std::vector<UrlInfo*>	m_FailList;  //����ʧ��url��Ϣ��,���ڽ����ٴγ���
	std::vector<UrlInfo*>	m_UrlList;
	UrlInfo*				m_CurrentUrl;

	HANDLE				m_EndEvent;

	CMyRegex			m_Regex;
	char*				m_CurrentP;
	std::vector<CMyString*> m_TempList;
};

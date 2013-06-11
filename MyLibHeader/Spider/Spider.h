#include "SpiderThread.h"
#include "SpiderVirtualClass.h"
#define  HTTP_REGEX "(href=|src=)\".*?[\",;]"

class Spider  
{
public:
	typedef enum
	{
		SPIDER_DEPTH,
		SPIDER_BREAD
	}SpiderMode;

	Spider();
	virtual ~Spider();

	SpiderInterfaceConfig*	GetSpiderInterfaceConfig();
	int 	SetSpiderMode(SpiderMode mode);          //������ȡģʽ����Ȼ��ȣ�
	int		SetPageUrlSortFunc(UrlCmpFunc urlSortFunc);//���ö�ҳ��url�����������
	int		SetMaxThread(int count);

	//urlΪ��ʼץȡ��ҳUrl,regexΪ��ȡ��ҳurl��������ʽ
	//(�������ݴ�������ʽ��ȡ�����ݣ�������ȡ��Ч�Ϸ�url)
	void	StartSpider(char *url,char* regex=HTTP_REGEX);
	void    EndSpider();

private:
	SpiderThread		m_SpiderThread;
};

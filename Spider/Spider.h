#include "../MyLib.h"
#include "SpiderThread.h"
#include "SpiderVirtualClass.h"
#define  HTTP_REGEX "(href=|src=)\".*?[\",;]"

class Spider  
{
public:
	Spider();
	virtual ~Spider();

	int 	SetSpiderMode(SpiderThread::SpiderMode mode);          //������ȡģʽ����Ȼ��ȣ�
	int		AddUrlFilter(ISpiderUrlFilter *urlFilter);//���url���˹���
	int		SetErrorNotify(ISpiderErrorNotify* errorNotify); //���ô������Ѵ�����
	int		SetPageProcessMethod(ISpiderPageProcess* processMethod);//�������ݴ�����
	int		SetFileProcessMethod(ISpiderFileProcess* processMethod);//�������ݴ�����
	int		SetUrlModifyRule(ISpiderUrlModify* urlModify);//����url�޸���
	int		SetPageUrlSortFunc(UrlCmpFunc urlSortFunc);//���ö�ҳ��url�����������
	int		SetMaxThread(int count);

	//urlΪ��ʼץȡ��ҳUrl,regexΪ��ȡ��ҳurl��������ʽ
	//(�������ݴ�������ʽ��ȡ�����ݣ�������ȡ��Ч�Ϸ�url)
	void	StartSpider(char *url,char* regex=HTTP_REGEX);
	void    EndSpider();

private:
	SpiderThread		m_SpiderThread;
};

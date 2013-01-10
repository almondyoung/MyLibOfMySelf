#include "../MyLib.h"
#include "SpiderThread.h"
#include "SpiderVirtualClass.h"

class Spider  
{
public:
	Spider();
	virtual ~Spider();

	int 	SetSpiderMode(SpiderThread::SpiderMode mode);          //������ȡģʽ����Ȼ��ȣ�
	int		AddUrlFilter(SpiderUrlFilter *urlFilter);//���url���˹���
	int		SetErrorNotify(SpiderErrorNotify* errorNotify); //���ô������Ѵ�����
	int		SetPageProcessMethod(SpiderPageProcess* processMethod);//�������ݴ�����
	int		SetFileProcessMethod(SpiderFileProcess* processMethod);//�������ݴ�����
	int		SetUrlModifyRule(SpiderUrlModify* urlModify);//����url�޸���
	int		SetPageUrlSort(SpiderUrlListSort* urlListSort);//���ö�ҳ��url�����������
	int		SetMaxThread(int count);

	void	StartSpider(char *url);
	void    EndSpider();

private:
	SpiderThread		m_SpiderThread;
};

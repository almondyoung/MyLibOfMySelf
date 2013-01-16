#ifndef __SPIDER_VIRTUAL_CLASS__
#define __SPIDER_VIRTUAL_CLASS__
#include "../MyLib.h"
class SpiderPageProcess  
{
public:
	SpiderPageProcess();
	virtual ~SpiderPageProcess();
	virtual	void PageProcess(const char *parentUrl,const char* url,const char* data,int dataLen);
};

class SpiderFileProcess  
{
public:
	SpiderFileProcess();
	virtual ~SpiderFileProcess();
	virtual	void FileProcess(const char *parentUrl,const char* url,CMyFile *file);
};

class SpiderErrorNotify  
{
public:
	SpiderErrorNotify();
	virtual ~SpiderErrorNotify();
	//����ֵ�����쳣�����Ƿ��������error ����0������˷�������С��0�����ڲ�����
	virtual	bool ErrorProcess(const char *parentUrl,const char* url,int error);
};

class SpiderUrlFilter  
{
public:
	SpiderUrlFilter();
	virtual ~SpiderUrlFilter();
	virtual bool FilterCheck(const char *parentUrl,const char *url)=0;
};

class SpiderUrlListSort
{
public:
	SpiderUrlListSort();
	virtual ~SpiderUrlListSort();
	virtual bool CompareUrl(const char *parentUrl,const char *url1,const char *url2);
};

class SpiderUrlModify  
{
public:
	SpiderUrlModify();
	virtual ~SpiderUrlModify();
	virtual bool ModifyUrl(const char *parent,CMyString &url)=0;
};

#endif
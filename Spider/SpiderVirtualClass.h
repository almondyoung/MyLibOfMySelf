#ifndef __SPIDER_VIRTUAL_CLASS__
#define __SPIDER_VIRTUAL_CLASS__
#include "../MyLib.h"
class ISpiderPageProcess  
{
public:
	ISpiderPageProcess(){}
	virtual ~ISpiderPageProcess(){}
	//������ȡ��url��ҳ�����ݴ���
	virtual	void PageProcess(const char *parentUrl,const char* url,const char* data,int dataLen)=0;
};

class ISpiderFileProcess  
{
public:
	ISpiderFileProcess(){}
	virtual ~ISpiderFileProcess(){}
	//������ȡ��url�ļ������ļ�����
	virtual	void FileProcess(const char *parentUrl,const char* url,const char* fileData,int dataLen)=0;
};

class ISpiderErrorNotify  
{
public:
	ISpiderErrorNotify(){}
	virtual ~ISpiderErrorNotify(){}
	//����ֵ�����쳣�����Ƿ��������error ����0������˷�������С��0�����ڲ�����
	virtual	bool ErrorProcess(const char *parentUrl,const char* url,int error,char *data,int dataLen)=0;
};

class ISpiderUrlFilter  
{
public:
	ISpiderUrlFilter(){}
	virtual ~ISpiderUrlFilter(){}
	virtual bool FilterCheck(const char *parentUrl,const char *url)=0;
};

class ISpiderUrlModify  
{
public:
	ISpiderUrlModify(){}
	virtual ~ISpiderUrlModify(){}
	virtual bool ModifyUrl(const char *parent,CMyString &url)=0;
};

class ISpiderFinish
{
public:
	ISpiderFinish(){}
	virtual ~ISpiderFinish(){}
	virtual void OnFinish()=0;
};
#endif
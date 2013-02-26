#ifndef __SPIDER_FETCHURL__
#define __SPIDER_FETCHURL__
#include "../MyLib.h"

class ISpiderFetchUrl  
{
public:
	ISpiderFetchUrl();
	virtual ~ISpiderFetchUrl();
	int			 FetchUrl(char* context,int contextLen,bool regexSame=false);
	int			 GetUrlCount();
	CMyString*	 GetUrl(int index);

private:
	//urlΪ����������ʽ��ȡ������Чurl
	//contextΪspider��ָ����ȡurl������ʽ��ȡ��������
	//����ֵ�����Ƿ����һurl���н�һ������(����url��ȫ(�������url),�Դ�url���й���
	//�Դ�url������ҳ��ȡ����)
	virtual bool onFetchUrl(const char* url,const char* context,int contextLen){return true;}
	bool		 GetUrl();
	void		 AddUrl();
	void		 InitalRegex(char* data,int dataLen);

private:
	CMyString		m_TempUrl;
	char*			m_CurrentP;
	char*			m_Context;
	int				m_ContextLen;
	int				m_UrlCount;
	std::vector<CMyString*>	m_TempList;
	CMyRegex		m_Regex;
};
#endif
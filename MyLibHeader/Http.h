#ifndef __HTTP__
#define __HTTP__
#include "windows.h"
#include "MyString.h"
#include "MyDebug.h"
#include "MyTempFile.h"
#include "wininet.h"

#include "zlib.h"


class CHttp  
{
public:
	CHttp();
	virtual ~CHttp();

	int			Get(char *uri,char *page);
	int			Post(char *uri,char *page,char *postData,int dataLen);

	void		SetUserInfo(char *userName,char *password);
	void		AddHttpHeader(char *header);
	void		SetAcceptType(char *type);
	void		SetRefer(char *refer);
	//���صĻ��岻�ܽ����޸ģ���������޷�Ԥ�ں��
	char*		GetReceiveData(){return m_Data.GetMapping();}
	int			GetReceiveDataLen(){return m_DataLen;}
	int			GetStatusCode(){return m_StatusCode;}    //�ڵ�����Get����Post��ʹ��
	//�����ַ�������ֻ�ܶ�ȡ������д��
	const char*	GetDataCharset(){return m_Charset.GetBuffer();};


	static void InitalHttp();
	static void UInitalHttp();

public:
	bool		m_StopGetOrPost;     //�����������߳���ֹͣGet��Post����

private:
	HINTERNET HttpConnect(char* uri);
	HINTERNET HttpOpenRequest(HINTERNET connect,char *verb,char *htmlPath);
	bool	  HttpSendRequest(HINTERNET request,void *extralData,int extralDataLen);
	int	      HttpAddHeader(HINTERNET request);
	int		  HttpGetContentLen(HINTERNET request);
	int		  HttpReadData(HINTERNET);
	void	  AnalysisUri(char *uri,CMyString &lastUri,CMyString &lastHtmlPath);
	int		  HttpGetCharset(HINTERNET request,CMyString &charset);
	int	      HttpGetEncode(HINTERNET request,CMyString &encode);
	int		  HttpGetStatusCode(HINTERNET request,int &code);
	int       HttpQueryInfo(HINTERNET request,CMyString &info,int code);

	int       GetOrPost(char *uri,char *page,char *postData,int dataLen);
private:
	CMyString m_Cookie;       //cookie
	CMyString m_HttpHeader;	  //httpͷ
	CMyString m_UserName;	  //����ʱ����û���
	CMyString m_Password;	  //����ʱ����û�����
	CMyString m_AcceptType;   //ָ������ʱ��Ľ����������ͣ�Ĭ���ı�
	CMyString m_Refer;        //���ĸ�uriλ�����õ�������ַ
	HINTERNET m_Session;      //�Ự���

	int				m_DataLen;
	CMyTempFile		m_Data;       //�������ݵ��ļ�

	CMyString m_Charset;         //���ܵ��������ַ���
	CMyString m_Encode;          //���ܵ�������ѹ����ʽ��Ϊ�մ����ʾûѹ��
	int		  m_StatusCode;      //��ȡGet����Post���״̬��
	static char*  TAG;
};

#endif

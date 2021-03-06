#ifndef __MY_POP3__
#define __MY_POP3__

#include "MyString.h"
#include "Windows.h"

#include "Mail.h"

#include <vector>

using namespace std;

#define DEFAULT_POP3_PORT  (110)
#define BUFFER_LEN			(513)

class CMyPOP3  
{
public:
	CMyPOP3();
	virtual ~CMyPOP3();

	void	SetLoginInfo(char* user,char* password);
	void	SetPOP3Server(char* url);
	void	SetPOP3Port(int port);

	int		GetMailCount();
	int		GetMailSize(int index);
	int		GetMailTotalSize(){return m_MailTotalSize;}

	char*	getErrorMessage(){return m_Buffer;}
	//返回值:  0  连接失败  -1 授权失败 1登入成功
	int		Login();
	void	Quit();
	bool	List();
	bool	Dele(int index);
	bool	Retr(int index,CMailRecord &mail);
	bool	Reset();
	bool    Top(int index,int lineCount,CMailRecord &mail);   
	bool	Stat();
	

private:
	bool	ConnectServer();
	bool	User();
	bool	Pass();

	int		RecvData();
	bool    CheckRecvState();
	bool	ExcuteCmd(CMyString& cmd);

	bool	FetchListResult(CMyString& data);
	bool	FetchTopResult(CMyString& data,CMailRecord &mail);
	bool	FetchRetrResult(CMyString& data,CMailRecord &mail);
	bool    FetchMailData();
	bool	RecvCmdResult(CMyString& data);

	CMyString	m_UserName;
	CMyString	m_Password;
	CMyString	m_POP3Server;
	int			m_ServerPort;
	int			m_Socket;

	char		m_Buffer[BUFFER_LEN];

	std::vector<int>	m_MailSizeList;
	unsigned long		m_MailTotalSize;
	unsigned long		m_MailCount;
};

#endif
#ifndef __MYDEBUG__
#define __MYDEBUG__
#include "windows.h"
#include <iostream>
#include <fstream>
#include "common.h"

using namespace std;
#define MAX_LOG_FILE  (10)		  //���log�ļ�
#define MAX_LOG_LEN   (1000)		  //�log
#define MAX_TAG_LEN   (100)         //����
#define DEFAULT_TAG   "DEBUG"

class CMyDebug  
{
public:
	enum DEBUG_MODE
	{
		WATCH_LOG,        //�۲촰��log
		FILE_LOG,         //д���ļ�log
		MESSAGE_BOX       //��������ʾ
	};

	CMyDebug();
	virtual ~CMyDebug();
	static void			Log(const char *format,...);
	static void			Log(const char *tag,const char *format,...);
	//fnumΪ�ļ��ţ��ļ�������ܴ��ڵ���MAX_LOG_FILE
	static void			Log(int mode,int fnum,const char *format,...);
	static void			Log(const char *tag,int mode,int fnum,const char *format,...);
	//��logд���ļ�ģʽʱ��������log�ļ���
	static bool			SetFileLogName(int fnum,char *fileName);

	bool				SetFileLogNameIn(int fnum,char *fileName);
	void				LogOut(const char *tag,int mode,int fnum,char *log);

	
	void				ResetLog();

	char			m_TagMark[MAX_TAG_LEN];      //Ĭ�ϵ�tag���
	DEBUG_MODE		m_Mode;

private:
	void				OutputFileLog(int fnum,char *log);
	void				UpdateTime(char* buf);   //����ʱ���ַ���

	ofstream*       m_pStreamOut[MAX_LOG_FILE];  //Ĭ��LOG������ļ�������
	char*			m_LogFileName[MAX_LOG_FILE];
//	char			m_TimeStr[30];
//	char			m_LogStr[MAX_LOG_LEN+1+MAX_TAG_LEN+40];
	
	HANDLE			m_Mutex;
};

#define LOG CMyDebug::Log

#endif
#ifndef __MY_STRING__
#define __MY_STRING__

#define MAX_SIZE (50)
#define ADD_STEP (50)
#define MAX_FORMATE_LEN (1000)
#include "MyRegex.h"
#include "common.h"
#include <vector>

using namespace std;

class CMyString;

CMyString operator +(char * str1,CMyString& str2);

class CMyString  
{
private:
	typedef struct
	{
		int iIndex;
		int iLen;
	}SplitInfo;

public:
	CMyString();
	CMyString(char *str);
	CMyString(int number);
	CMyString(double number);
	CMyString(const CMyString& str);
	virtual ~CMyString();

	//��ȡ����󲻿�ֱ���޸��ַ������ģ�����ᵼ��δ֪���
	char*		GetBuffer(){return m_Buffer;}

	int			GetBufferSize(){return m_BufLen;}
	int			GetStrLen();
	void		ToLowerCase();
	void		ToUpcase();
	CMyString	GetSubStr(int start);
	CMyString	GetSubStr(int start,int end);
	void		Resize(int size);
	int			ToInt();
	int			ToDouble();
	//���Դ�Сд�ȽϺ���
	int			CompareI(char *str); 
	int			CompareI(CMyString &str);
	int			Erase(int start,int count);
	int 		EraseFromRight(int count);
	void		SetAt(int index,char c);
	char		GetAt(int index);
	int			Trim();
	unsigned	HashCode();

	//�滻ʧ�ܷ���-1
	int 		Replace(char *str,char *newStr ,int startOffset =0);
	int 		ReplaceAll(char *str,char *newStr);

	//ƥ��ʧ��-1
	int			Match(char *regex,CMyString *outStr,bool ignoreCareLess=false,int option=0);
	int			MatchNext(CMyString *outStr,int option=0);

	int			FindChar(char c);
	int			FindString(char *str);

	CMyString&	operator =(char* str);
	CMyString&	operator =(int	number);
	CMyString&	operator =(double	number);
	CMyString&	operator =(const CMyString& str);
	CMyString&	operator +=(char* str);
	CMyString&	operator +=(char c);
	CMyString&	operator +=(CMyString& str);
	bool		operator ==(char* str);
	bool		operator ==(CMyString& str);
	bool		operator !=(CMyString& str);
	bool		operator !=(char* str);
	CMyString	operator +(CMyString& str);
	CMyString	operator +(char* str);
	char		operator [](int index);
	
	//�ȵ���split����ͳ�Ʒָ�Ķ�����splitTxt�ָ����������һ���ַ��������ַ���
	int			Split(char* splitTxt);
	int			GetSplitString(int index,CMyString& subString);

				operator char*();

				bool		IsValid(){return m_Buffer==NULL;}
	friend CMyString operator +(char * str1,CMyString& str2);
	
	

	static CMyString	StringFromMem(char *str,int start,int len);
	static CMyString	Format(const char *format,...);
	static CMyString	FromUnicode(char *unicodeBuf);
	static CMyString	GetSlefPath();
	
private:
	void Inital();
	void UInital();
	void append(char* str);
	void copy(char *str);

	void setStringLenInvalid(){mNeedUpdateLen=true;}
private:
	char *m_Buffer;
	int	  m_StrLen;
	int	  m_BufLen;
	
	bool  mNeedUpdateLen;

	std::vector<SplitInfo>	m_SplitIndex;

	CMyRegex   m_Regex;
};


#endif
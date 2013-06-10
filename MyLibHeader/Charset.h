#ifndef __MY_CHARSET__
#define __MY_CHARSET__

class CCharset
{
private:
	static int UTF_8ToUnicode(unsigned short& outC,char *pText); // ��UTF-8ת����Unicode
	static int UnicodeToUTF_8(char* pOut,unsigned short c); //Unicode ת����UTF-8	

	static int UnicodeToGB2312(char* pOut,unsigned short uData); // ��Unicode ת���� GB2312 
	static int Gb2312ToUnicode(char* pOut,char *gbBuffer);// GB2312 ת���ɡ�Unicode

	static char* TAG;
public:
	
	//����д�����������ֽ���

	static int UnicodeToGB2312(char* pOut,char* pText,int pTextLen); 
	static int Gb2312ToUnicode(char* pOut,char* pText,int pTextLen);
	static int GB2312ToUTF_8(char* pOut,char *pText, int pLen);//GB2312 תΪ UTF-8
	static int UTF_8ToGB2312(char* pOut, char *pText, int pLen);//UTF-8 תΪ GB2312
};

#endif
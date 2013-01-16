#ifndef __MY_TEMPFILE__
#define __MY_TEMPFILE__
#include "MyFile.h"
#include "MyString.h"
#include "windows.h"

class CMyTempFile : public CMyFile
{
public:
	CMyTempFile();
	virtual ~CMyTempFile();
	virtual int		Open(char *filePath,FILE_MODE mode){return -1;}

	bool		IsUsable(){return m_Inital;}  //�ж���ʱ�ļ��Ƿ�ɹ�����
	void		ReCreate();                   //����ʱ�ļ�����ʧ�ܺ󣬿��Ե��ôκ����ؽ�
};

#endif
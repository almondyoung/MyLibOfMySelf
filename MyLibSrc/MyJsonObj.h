#ifndef __MY_JSON__
#define __MY_JSON__

#include "MyString.h"

#define JUMP_INVALID_C(_STR,_LEN,_P)  \
	{\
	int _l=_LEN;\
	while(*(_P)&&(*(_P)=='\r'||*(_P)==' '||*(_P)=='\n'||*(_P)=='\t')&&((_P)-(_STR))<(_l))(_P)++;\
	if(!(*(_P))||((_P)-(_STR))>=(_l))return NULL;\
	}

#define CAN_PUT_KEY_VALUE(_KEYVALUE,_TYPE)  (!(_KEYVALUE)||(_KEYVALUE)->m_Type==(_TYPE))

class CMyJsonObj;

typedef enum
	{
		TYPE_DIGTAL,
		TYPE_JSONARRAY,
		TYPE_JSONOBJ,
		TYPE_NULL,
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_INVALID
	} Value_Type;

class CMyJsonArray
{
	typedef struct _Array_Item
	{
		Value_Type	m_Type;
		union
		{
			CMyString*		m_String;
			CMyJsonObj*		m_JsonObj;
			CMyJsonArray*	m_JsonArray;
		}	m_Value;
		_Array_Item()
		{
			m_Value.m_String=NULL;
		}
	} Array_Item;

	typedef struct _Json_Array
	{
		Array_Item*    m_Obj;
		_Json_Array*   m_Next;
	} Json_Array;

public:
	CMyJsonArray();
	virtual ~CMyJsonArray();
	friend  class CMyJsonObj;
	
public:
	int			GetJsonArraySize(){return m_ValueLen;}

	CMyString	ToString();
	//����json�����ַ���,���json�����ַ������Ϸ����򷵻�NULL��
	//���򷵻غϷ�json�����ĵ�һ���ַ�ָ��
	char*		SetJsonArrayStr(char *str,int len);
	//��ȡjson�ַ���,��bufΪNULLʱ�򣬷�������buf��С
	int			GetJsonArrayStr(char* buf,int bufLen);

	int			AddStringItem(char *value);
	int			AddNumberItem(int value);
	int			AddNumberItem(double value);
	int			AddNullItem();
	int			AddBoolItem(bool value);
	int			AddJsonObjItem(CMyJsonObj *jsonObj);
	int			AddJsonArrayItem(CMyJsonArray *jsonArray);
	
	int			DeleteItem(int index);
	int			DeleteAll();
	//ʧ�ܷ���NULL
	CMyJsonObj* GetJsonObj(int index);
	CMyJsonArray*	GetJsonArray(int index);
	//ʧ�ܷ���-1
	int			GetDouble(int index,double &value);
	int			GetInt(int index,int &value);
	int			GetBool(int index,bool &value);
	int			GetString(int index,CMyString &value);
	int			GetString(int index,char* buf,int bufLen);
private:
	CMyString	ArrayItemToString(Array_Item *item);
	void		FreeArrayItem(Array_Item *item);
	void		FreeAll();

	int			AddItem(Array_Item *item);
	Array_Item *GetItem(int index);
	CMyJsonArray* CopyData();
private:
	Json_Array    m_Value;
	int			  m_ValueLen;
};


class CMyJsonObj  
{
private:

	typedef struct _Key_Value
	{
		CMyString  m_Key;
		Value_Type m_Type;
		union
		{
			CMyString*		m_String;
			CMyJsonObj*		m_JsonObj;
			CMyJsonArray*	m_JsonArray;
		}	m_Value;

		CMyString ToString()
		{
			CMyString rStr;
			rStr	+="\"";
			rStr	+=m_Key;
			rStr	+="\":";
			switch(m_Type)
			{
			case TYPE_DIGTAL:
			case TYPE_BOOL:
				rStr	+=*(m_Value.m_String);
				break;
			case TYPE_STRING:
				rStr	+="\"";
				rStr	+=*(m_Value.m_String);
				rStr	+="\"";
				break;
			case TYPE_JSONARRAY:
				rStr	+=m_Value.m_JsonArray->ToString();
				break;
			case TYPE_JSONOBJ:
				rStr	+=m_Value.m_JsonObj->ToString();
				break;
			case TYPE_NULL:
			default:
				rStr	+="null";
			}
			return rStr;
		}
		_Key_Value()
		{
			m_Value.m_String=NULL;
		}

		~_Key_Value()
		{
			switch(m_Type)
			{
			case TYPE_DIGTAL:
			case TYPE_STRING:
			case TYPE_BOOL:
				if(m_Value.m_String)
					delete m_Value.m_String;
				break;
			case TYPE_JSONARRAY:
				if(m_Value.m_JsonArray)
					delete m_Value.m_JsonArray;
				break;
			case TYPE_JSONOBJ:
				if(m_Value.m_JsonObj)
					delete m_Value.m_JsonObj;
				break;
			}
		}
	} Key_Value;


	typedef struct _Json_KeyValue_List
	{
		Key_Value*					m_KeyValue;
		_Json_KeyValue_List*		m_Next;
		_Json_KeyValue_List()
		{
			m_KeyValue	=NULL;
			m_Next		=NULL;
		}
		~_Json_KeyValue_List()
		{
			if(m_KeyValue)
				delete m_KeyValue;
		}
	} Json_KeyValue_List;

public:
	CMyJsonObj();
	CMyJsonObj(const CMyJsonObj &jsonObj);
	virtual ~CMyJsonObj();
	friend  class CMyJsonArray;

public:

	//����json�ַ������������ΪNULL����ʾ�ַ������Ϸ���
	//�Ϸ��ַ������غϷ�json�ַ����һ��֧��ָ��
	char*		SetJsonStr(char *str,int len);
	//��ȡjson�ַ���,��bufΪNULLʱ�򣬷�������buf��С
	int			GetJsonStr(char* buf,int bufLen);
	CMyString	ToString();

	int			PutStringKeyValue(char* key,char* value);
	int			PutNumberKeyValue(char* key,double value);
	int			PutNumberKeyValue(char* key,int value);
	int			PutBoolKeyValue(char *key,bool value);
	int			PutNullKeyValue(char *key);
	int			PutJsonObjKeyValue(char *key,CMyJsonObj *jsonObj);
	int			PutJsonArrayKeyValue(char*key,CMyJsonArray *jsonArray);

	int			GetDoubleValue(char *key,double &value);
	int			GetIntValue(char *key,int &value);
	int			GetBoolValue(char *key,bool &value);
	CMyJsonObj*	GetJsonValue(char *key);
	CMyJsonArray*	GetJsonArrayValue(char* key);

	//bufLen�����������buf��д�����������������buf��С��
	//��ȡ����buf��Сʱ�򣬰�buf����NULL
	int			GetStringValue(char *key,char *buf,int &bufLen);
	int			GetStringValue(char *key,CMyString &str);

	int			DeleteKeyValue(char* key);
private:
	//���ص�ǰ�������ַ�
	char*		GetKey(char *str,int len,CMyString &key);
	char*		GetValue(char* str,int len,Key_Value &keyValue);

	//ȡ�÷���startC����Է���
	char*		GetBound(char *str,int len,char startC);
	char*		IsString(char *str,int len,CMyString &outStr);
	char*		IsDigtal(char *str,int len,CMyString &outStr);	
	
	void		FreeAll();

	int			AddKeyValue(Key_Value *keyValue,bool withCheck);
	Key_Value*	CanAddOrModify(char *key,Value_Type type);

	CMyJsonObj*	CopyData();
private:
	Json_KeyValue_List		m_KeyValueList;
	int						m_KeyValueListSize;
};

#endif
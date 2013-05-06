#include "Encrypt.h"

CEncrypt::CEncrypt()
{

}

CEncrypt::~CEncrypt()
{

}


int CEncrypt::EncodeBase64(const unsigned char* Data,int DataByte,CMyBuffer& outBuffer)
{
    //����ֵ
	int encodeLen=0;
    CMyString strEncode;
    //�����
    const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned char Tmp[4]={0};
    int LineLength=0;
    for(int i=0;i<(int)(DataByte / 3);i++)
    {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        Tmp[3] = *Data++;
		outBuffer.write((char*)&EncodeTable[Tmp[1] >> 2],1);
		encodeLen++;
        outBuffer.write((char*)&EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F],1);
		encodeLen++;
        outBuffer.write((char*)&EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F],1);
		encodeLen++;
        outBuffer.write((char*)&EncodeTable[Tmp[3] & 0x3F],1);
		encodeLen++;
        if(LineLength+=4,LineLength==76)
		{
			outBuffer.write("\r\n",2);
			encodeLen+=2;
			LineLength=0;
		}
    }
    //��ʣ�����ݽ��б���
    int Mod=DataByte % 3;
    if(Mod==1)
    {
        Tmp[1] = *Data++;
        outBuffer.write((char*)&EncodeTable[(Tmp[1] & 0xFC) >> 2],1);
        outBuffer.write((char*)&EncodeTable[((Tmp[1] & 0x03) << 4)],1);
        outBuffer.write("==",2);
		encodeLen+=4;
    }
    else if(Mod==2)
    {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        outBuffer.write((char*)&EncodeTable[(Tmp[1] & 0xFC) >> 2],1);
        outBuffer.write((char*)&EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)],1);
        outBuffer.write((char*)&EncodeTable[((Tmp[2] & 0x0F) << 2)],1);
		outBuffer.write("=",1);
        encodeLen+=4;
    }
    return encodeLen; 
}

int CEncrypt::DecodeBase64(const char* Data,int DataByte,CMyBuffer& outBuffer)
{
	//����ֵ
	int decodeLen=0;
	//�����
    const char DecodeTable[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        62, // '+'
        0, 0, 0,
        63, // '/'
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
        0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
        0, 0, 0, 0, 0, 0,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
    };

    int nValue;
    int i= 0;
	char c;
    while (i < DataByte)
    {
        if (*Data != '\r' && *Data!='\n')
        {
            nValue = DecodeTable[*Data++] << 18;
            nValue += DecodeTable[*Data++] << 12;
			c=(nValue & 0x00FF0000) >> 16;
            outBuffer.write(&c,1);
			decodeLen++;
            if (*Data != '=')
            {
                nValue += DecodeTable[*Data++] << 6;
                c=(nValue & 0x0000FF00) >> 8;
				outBuffer.write(&c,1);
				decodeLen++;
                if (*Data != '=')
                {
                    nValue += DecodeTable[*Data++];
                    c=nValue & 0x000000FF;
					outBuffer.write(&c,1);
					decodeLen++;
                }
            }
            i += 4;
        }
        else// �س�����,����
        {
            Data++;
            i++;
        }
     }
    return decodeLen;
}

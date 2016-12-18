#include "StdAfx.h"
#include "HttpDownloader.h"
#include <afxinet.h>
#include "CSpreadSheet.h"

#define RECVPACK_SIZE 2048

HttpDownloader::HttpDownloader(void)
{
}

HttpDownloader::~HttpDownloader(void)
{
}

bool HttpDownloader::download(const char* lpszUrl, const char* strSaveFile)
{
    bool ret=false;

	/*
    CInternetSession Sess("lpload");
    Sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT     , 2000); //2������ӳ�ʱ
    Sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT        , 2000); //2��ķ��ͳ�ʱ
    Sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT     , 2000); //2��Ľ��ճ�ʱ
    Sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT   , 2000); //2��ķ��ͳ�ʱ
    Sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 2000); //2��Ľ��ճ�ʱ
    DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD ;

    CHttpFile* cFile   = NULL;
    char      *pBuf    = NULL;
    int        nBufLen = 0   ;
    do 
	{
        try
		{
            cFile = (CHttpFile*)Sess.OpenURL(lpszUrl, 1, dwFlag);
            
			DWORD dwStatusCode;
            
			cFile->QueryInfoStatusCode(dwStatusCode);
            
			if (dwStatusCode == HTTP_STATUS_OK) 
			{
                //��ѯ�ļ�����
                DWORD nLen=0;
                cFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, nLen);
                //CString strFilename = GetFileName(url,TRUE);
                nBufLen=nLen;
                if (nLen <= 0) break;//

                //����������ݻ���
                pBuf = (char*)malloc(nLen+8);
                ZeroMemory(pBuf,nLen+8);

                char *p=pBuf;
                while (nLen>0) 
				{
                    //ÿ������8K
                    int n = cFile->Read(p,(nLen<RECVPACK_SIZE)?nLen:RECVPACK_SIZE);
                    //��������˳�ѭ��
                    if (n <= 0) break;//
                    //���ջ������
                    p+= n ;
                    //ʣ�೤�ȵݼ�
                    nLen -= n ;
                }

                //���δ�������ж��˳�
                if (nLen != 0) break;

                //���ճɹ����浽�ļ�

                CFile file(strSaveFile, CFile::modeCreate | CFile::modeWrite);
                file.Write(pBuf,nBufLen);
                file.Close();
                ret = true;
            }
        } 
		catch(...) 
		{
            break;//
        }
    } while(0);

    //�ͷŻ���
    if (pBuf) {
        free(pBuf);
        pBuf=NULL;
        nBufLen = 0 ;
    }

    //�ر���������
    if (cFile) {
        cFile->Close();
        Sess.Close();
        delete cFile;
    }
	*/

	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;

	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //����֮��ĵȴ���ʱ
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //���Դ���
	char* pszBuffer = NULL;  

	try
	{
		AfxParseURL(lpszUrl, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort);
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
		if(pHttpFile->SendRequest() == FALSE)
			return false;
		DWORD dwStateCode;

		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if(dwStateCode == HTTP_STATUS_OK)
		{
			HANDLE hFile = CreateFile(strSaveFile, GENERIC_WRITE,
				FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
				NULL);  //���������ļ�
			if(hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				return false;
			}

			char szInfoBuffer[1000];  //������Ϣ
			DWORD dwFileSize = 0;   //�ļ�����
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				(void*)szInfoBuffer,&dwInfoBufferSize,NULL);

			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //��ȡ�ļ��Ļ���
			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //��ȡ������������

			while(nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //д�������ļ�
				dwTotalWrite += dwWrite;
				nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
			}

			delete[]pszBuffer;
			pszBuffer = NULL;
			CloseHandle(hFile);
		}
		else
		{
			delete[]pszBuffer;
			pszBuffer = NULL;
			if(pHttpFile != NULL)
			{
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if(pHttpConnection != NULL)
			{
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			return false;
		}
	}
	catch(CInternetException& e)
	{
		char buf[256] = {0};
		e.GetErrorMessage(buf, 255);
		AfxMessageBox(buf);

		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if(pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		return false;
	}
	catch(...)
	{
		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if(pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		return false;
	}

	if(pHttpFile != NULL)
		pHttpFile->Close();
	if(pHttpConnection != NULL)
		pHttpConnection->Close();
	session.Close();

	return true;


}
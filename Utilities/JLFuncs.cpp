/*******************************************************************************
* (C) Copyright 2008  
* 
*
* Project:      IViewer 
* File Name:	JLFuncs.cpp 
* Programer(s):	Jerry Lee 
* Created:      20080310 
* Description:	implement the global variants and methods of the application
* History: 
* 2008.3.26, Jerry Lee, Fixed the bug of DrawThumbImage
* July 8 2008, Jerry Lee, added the function that converts the pubdate time into GMT 
* July 11 2008, Jerry Lee, fixed the bug of ConvertTimeByTimeZone, notice the UInt32x32To64 macro
* July 25 2008, Jerry Lee, added the function of DrawBitmap
* Aug 5 2008, Jerry Lee, fixed the bug of SetStringValue
* Aug 14 2008, Jerry Lee, fixed the bug of DrawCircle, the handle leak
* Sep 18 2008, Jerry Lee, improve the GetFileTimeSpan function for supporting more compare modes of time.
*******************************************************************************/

#include "afxwin.h"
#include "JLFuncs.h"
#include <tlhelp32.h>
#include "objbase.h"
/*
#include <INITGUID.H>
#include <imaging.h>
*/


//#pragma comment(lib, "Toolhelp.lib")
//#pragma comment(lib, "imaging.lib")
/*
*/
void ProcessMessages()
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message != WM_QUIT)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

// if pWnd have valid window handle then Invalidate
void SafeInvalidate(CWnd *pWnd, BOOL bEraseBkgnd)
{
    if (pWnd->GetSafeHwnd())
    {
        pWnd->Invalidate(bEraseBkgnd);
    }
}

// if pWnd have valid window handle then UnsubclassWindow
void SafeUnsubclassWindow(CWnd &wnd)
{
    if (wnd.GetSafeHwnd())
    {
        wnd.UnsubclassWindow();
    }
}

// get the background brush based on window
HBRUSH GetBkBrushFromWnd(HWND hWnd, UINT nID, HBITMAP hBmBk)
{
	HWND hWndCtrl;

	hWndCtrl = ::GetDlgItem(hWnd, nID);
	
	HBRUSH	hBrushCtrl = NULL;

	if (NULL != hWndCtrl)
	{
		RECT rcCtrl;

		::GetWindowRect(hWndCtrl, &rcCtrl);
		::ScreenToClient(hWnd, (LPPOINT)&rcCtrl);
		::ScreenToClient(hWnd, ((LPPOINT)&rcCtrl)+1);

		HDC hDC = ::GetDC(hWnd);

        HDC hMemDCBk = ::CreateCompatibleDC(hDC);
        HDC hMemDCCtrl = ::CreateCompatibleDC(hDC);

        HBITMAP hBmCtrl = ::CreateCompatibleBitmap(hDC, _W(rcCtrl), _H(rcCtrl));

		HBITMAP hBmOldBk = (HBITMAP)::SelectObject(hMemDCBk, hBmBk);
		HBITMAP hBmOldCtrl = (HBITMAP)::SelectObject(hMemDCCtrl, hBmCtrl);

		::BitBlt(hMemDCCtrl, 0, 0, _W(rcCtrl), _H(rcCtrl), hMemDCBk, 
            _X(rcCtrl), _Y(rcCtrl), SRCCOPY);

		::SelectObject(hMemDCCtrl, hBmOldCtrl);
		::SelectObject(hMemDCBk, hBmOldBk);
		
		hBrushCtrl = ::CreatePatternBrush(hBmCtrl);
        //
        ::DeleteObject(hBmCtrl);
        //
		::DeleteDC(hMemDCBk);
		::DeleteDC(hMemDCCtrl);
		::ReleaseDC(hWnd, hDC);
	}
    //
	return hBrushCtrl;
}

// get the background brush based on hDC
// point parameter specifies left and top coordinates for the background brush 
HBRUSH GetBkBrushByPos(HWND hWnd, UINT nID, HBITMAP hBmBk, const POINT &point,
                       int nWidth, int nHeight)
{
	HWND hWndCtrl = ::GetDlgItem(hWnd, nID);

    if (NULL == hWndCtrl)
    {
        return NULL;
    }

    HBRUSH hBrushCtrl = NULL;
    //
    HDC hDC = ::GetDC(hWnd);
    //
    HDC hMemDCBk = ::CreateCompatibleDC(hDC);
    HBITMAP hBmOldBk = (HBITMAP)::SelectObject(hMemDCBk, hBmBk);
    //
    HDC hMemDCCtrl = ::CreateCompatibleDC(hDC);
    HBITMAP hBmCtrl = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
    HBITMAP hBmOldCtrl = (HBITMAP)::SelectObject(hMemDCCtrl, hBmCtrl);
    //
    ::BitBlt(hMemDCCtrl, 0, 0, nWidth, nHeight, hMemDCBk, 
        point.x, point.y, SRCCOPY);
    //
    ::SelectObject(hMemDCCtrl, hBmOldCtrl);
    ::SelectObject(hMemDCBk, hBmOldBk);
    //
    hBrushCtrl = ::CreatePatternBrush(hBmCtrl);
    //
    ::DeleteObject(hBmCtrl);
    //
    ::DeleteDC(hMemDCBk);
    ::DeleteDC(hMemDCCtrl);
    ::ReleaseDC(hWndCtrl, hDC);
    //
	return hBrushCtrl;
}

void DrawThumbImage(HDC hDC, HBITMAP hBitmap, const RECT &rect)
{
    BITMAP bitmap;
    ::GetObject(hBitmap, sizeof(bitmap), &bitmap);

    int nDestWidth, nDestHeight;
    int XDest, YDest;

    if (bitmap.bmHeight > _H(rect) || bitmap.bmWidth > _W(rect))
    {
        const float fFrmRatio = (float)_H(rect) / _W(rect);
        const float fImgRatio = (float)bitmap.bmHeight / bitmap.bmWidth;
        
        if (fImgRatio > fFrmRatio)
        {
            nDestWidth = _H(rect)/fImgRatio;
            nDestHeight = _H(rect);
            XDest = (_W(rect) - nDestWidth) >> 1;
            YDest = 0;
        }
        else
        {
            XDest = 0;
            nDestWidth = _W(rect);
            nDestHeight = _W(rect)*fImgRatio;
            YDest = (_H(rect) - nDestHeight) >> 1;
        }
    }
    else
    {
        XDest = (_W(rect) - bitmap.bmWidth) >> 1; 
        YDest = (_H(rect) - bitmap.bmHeight) >> 1;
        nDestWidth = bitmap.bmWidth;
        nDestHeight = bitmap.bmHeight;
    }

    HDC hDCMem = ::CreateCompatibleDC(hDC);
    HBITMAP hOldBm = (HBITMAP)::SelectObject(hDCMem, hBitmap);
    ::StretchBlt(hDC, XDest + rect.left, YDest + rect.top, nDestWidth, 
        nDestHeight, hDCMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
    //
    ::SelectObject(hDCMem, hOldBm);
    DeleteDC(hDCMem);
}

void SetStringValue(LPTSTR lpszDesc, int nDescLen, LPCTSTR lpszSrc)
{
    memset(lpszDesc, 0, nDescLen);
    _tcsncpy(lpszDesc, lpszSrc, min(nDescLen - 1, _tcslen(lpszSrc)));
}

void SafePostMessage(CWnd *pWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (NULL != pWnd)
    {
        pWnd->PostMessage(Msg, wParam, lParam);
    }
}

BOOL PasrePageURL(TCHAR *data)
{

	TCHAR *pos=data, *pos1=0, *pos2=0; 
    TCHAR aurl[256];

	while(TRUE)
    {
		pos1 = _tcsstr(pos, _T("href="));
		TCHAR *ps = _tcsstr(pos, _T("href "));

		if (ps!=0 && ps<pos1)
        {
			pos1=ps;
        }

		if(pos1)
        {
			pos2 = _tcsstr(pos1, _T(">"));
			if (pos2 == 0)
            {
				break;
            }

			TCHAR* pos3 = _tcsstr(pos1, _T(" "));
			if (pos3!=0 && pos3<pos2)
            {
				pos2=pos3;
            }
		}
		else
        {
			break;
		}

		if (pos1==0 || pos2==0)
        {
			break;
        }
		memset(aurl,0,256);
		memcpy(aurl,pos1+5,pos2-pos1-5);
				
		if (_tcsstr(aurl, _T("List.Aspx")))
        {
				int pageno=0;
				pos1 = _tcsstr(pos1,_T(">"));
				if( pos1==0 ) break;
				pos2= _tcsstr(pos1,_T("<"));
				if( pos2==0 ) break;
				TCHAR cp[16];
				memset(cp,0,16);
				memcpy(cp,pos1+1,pos2-pos1-1);

				pageno = _ttoi(cp);
				if( pageno>=0 && pageno<256 )
                {
// 					if (pageurls[pageno][0] == 1) 
//                     {
// 						pos=pos2;
// 						continue;
// 					}
// 					strcpy(pageurls[pageno]+1, aurl);					
				}				
		}

		pos=pos2;
	}
	return TRUE;
}

BOOL PasreHTMLURL(TCHAR* data)
{
	TCHAR *pos=data, *pos1=0, *pos2=0; 
    TCHAR aurl[256];
	while(TRUE)
    {
		pos1=_tcsstr(pos,_T("href="));
		TCHAR* ps=_tcsstr(pos,_T("href "));
		if (ps!=0 && ps<pos1)
			pos1=ps;
		if(pos1)
        {
			pos2=_tcsstr(pos1,_T(">"));
			if( pos2==0 )
				break;
		}
		else
        {
			break;
		}

		if( pos1==0 || pos2==0)
			break;
		memset(aurl,0,256);
		memcpy(aurl,pos1+6,pos2-pos1-7);
		
		if (_tcsstr(aurl,_T(".htm")))
        {			
			TCHAR* data = 0;
			int   len = 0;

// 			if(!getFile(aurl,data, len)) 
//             {
// 				delete []data;
// 				return false;
// 			}
			
//			PasreJPGURL(data);
			delete [] data;
			
		}		

		pos=pos2;
	}
	return TRUE;
}

LPTSTR PasreJPGURL(LPTSTR lpszDesc, int nLen, LPCTSTR lpszSrc)
{
	TCHAR *pSrc = (LPTSTR)lpszSrc, *pHdr = NULL, *pJPG = NULL; 

    // finds the "IMG" or "img" mark, exits if it's not be found
    pHdr = (TCHAR *)_tcsstr(lpszSrc, _T("IMG "));
    if (NULL == pHdr) 
    { 
        pHdr = (TCHAR *)_tcsstr(lpszSrc, _T("img "));
        if (NULL == pHdr)
        {
            return NULL;
        }
    }
    
    // finds the "src" mark, exits if it's not be found
    pHdr = _tcsstr(pHdr, _T(" src="));
    if (NULL == pHdr) 
    {
        return NULL;
    }
    
    // finds the file url 
    int nExt = 0;
    pHdr += _tcslen(_T(" src="));
    
    // increases 1 for skiping a quotation mark
    if (_T('"') == *pHdr)
    {
        pHdr++;
    }
    
    // finds the jpg
    pJPG = _tcsstr(pHdr, _T(".jpg"));
    if (NULL == pJPG)
    {
        pJPG = _tcsstr(pHdr, _T(".jpeg"));
        nExt = 5;
    }
    else
    {
        nExt = 4;
    }
    
    // exits if can not find "jpg" or pHdr equals pJPG
    if (pJPG != NULL && pJPG > pHdr) 
    {
        _tcsncpy(lpszDesc, pHdr, min(nLen, pJPG - pHdr + nExt));
    	return pJPG + nExt;
    }
    else
    {
        return NULL;
    }
}

void GetLocalFullFilePath(LPTSTR lpszPath, int nSize, LPCTSTR lpszFile)
{
    TCHAR buf[256] = {0};
    GetModuleFileName(NULL, buf, nSize);
    TCHAR *p = _tcsrchr(buf, _T('\\'));
    if (p) 
    {
        p[1] = 0;
    }
    _tcscpy(lpszPath, buf);
    _tcscat(lpszPath, lpszFile);
}

void ExtractFileName(LPTSTR lpszFileName, int nSize, LPCTSTR lpszPath)
{
    LPTSTR p = (LPTSTR)lpszPath + _tcslen(lpszPath) - 1;

    while (p > lpszPath)
    {
        if ((_T('\\') == *p) || (_T('/') == *p)) 
        {
            _tcsncpy(lpszFileName, p + 1, min(nSize, _tcslen(p + 1)));
            return;
        }
        p--;
    }

    if (p == (LPTSTR)lpszPath) 
    {
        _tcsncpy(lpszFileName, lpszPath, min(nSize, _tcslen(lpszPath)));
    }
}

BOOL CopyFileToDir(LPTSTR lpszNew, int nSize, LPCTSTR lpszDir, LPCTSTR lpszOld)
{
    TCHAR szFileName[256] = {0};

    // extracts the file name from file path
    ::ExtractFileName(szFileName, _LEN(szFileName), lpszOld);
    
    // 
    if (_tcslen(lpszDir) >= (nSize - 2))
    {
        return FALSE;
    }
    _tcscpy(lpszNew, lpszDir);

    //
    *(lpszNew + _tcslen(lpszDir)) = _T('\\');
    if (_tcslen(lpszNew) >= nSize) 
    {
        return FALSE;
    }

    //
    int nRemain = nSize - _tcslen(lpszNew);
    if (_tcslen(szFileName) > nRemain) 
    {
        return FALSE;
    }
    _tcscpy(lpszNew + _tcslen(lpszDir) + 1, szFileName);

    //
    return ::CopyFile(lpszOld, lpszNew, FALSE);
}

BOOL FileExists(LPCTSTR lpszFile)
{
    WIN32_FIND_DATA wfd;
    HANDLE hFile = FindFirstFile(lpszFile, &wfd);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFile);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int GetFileTimeSpan(LPCTSTR lpszFile, DWORD dwMode)
{
    WIN32_FIND_DATA wfd;
    HANDLE hFile = FindFirstFile(lpszFile, &wfd);
    if (hFile != NULL) 
    {
        SYSTEMTIME stBegin, stEnd;
        switch(dwMode) 
        {
        case 0:
            FileTimeToSystemTime(&(wfd.ftCreationTime), &stBegin);
            break;
        case 1:
            FileTimeToSystemTime(&(wfd.ftLastAccessTime), &stBegin);
            break;
        case 2:
            FileTimeToSystemTime(&(wfd.ftLastWriteTime), &stBegin);
            break;
        default:
            GetSystemTime(&stBegin);
            break;
        }
        GetSystemTime(&stEnd);
        CTime t1(stBegin);
        CTime t2(stEnd);
        if (t2 > t1) 
        {
            CTimeSpan span = t2 - t1;
            FindClose(hFile);
            return span.GetDays();
        }
    }
    return -1;
}


/* Time zone of around the world
NZDT +13:00 ����������ʱ�䣨��ʱ�ƣ� 
IDLE +12:00 �������ڱ���ߣ����� 
NZST +12:00 ��������׼ʱ�� 
NZT +12:00 ������ʱ�� 
AESST +11:00 �Ĵ����Ƕ�����׼��ʱ�� 
ACSST +10:30 �аĴ����Ǳ�׼��ʱ�� 
CADT +10:30 �аĴ�������ʱ�� 
SADT +10:30 �ϰĴ�������ʱ�� 
AEST +10:00 �Ĵ����Ƕ�����׼ʱ�� 
EAST +10:00 ���Ĵ����Ǳ�׼ʱ�� 
GST +10:00 �ص���׼ʱ�䣬��USSR Zone 9���� 
LIGT +10:00 �Ĵ�����ī���� 
ACST +09:30 �аĴ����Ǳ�׼ʱ�� 
CAST +09:30 �аĴ����Ǳ�׼ʱ�� 
SAT +9:30 �ϰĴ����Ǳ�׼ʱ�� 
AWSST +9:00 �Ĵ�����������׼��ʱ�� 
JST +9:00 �ձ���׼ʱ�䣬��USSR Zone 8�� 
KST +9:00 ������׼ʱ�� 
WDT +9:00 ���Ĵ�������ʱ�� 
MT +8:30 ë����˹ʱ�䣨���� 
AWST +8:00 �Ĵ�����������׼ʱ�� 
CCT +8:00 �й��غ�ʱ�� 
WADT +8:00 ���Ĵ�������ʱ�� 
WST +8:00 ���Ĵ�����ʱ�� 
JT +7:30 צ��ʱ�䣨��ע������� Java �ɲ������ԣ� 
WAST +7:00 ���Ĵ����Ǳ�׼ʱ�� 
IT +3:30 ����ʱ�� 
BT +3:00 �͸��ʱ�� 
EETDST +3:00 ��ŷ��ʱ�� 
CETDST +2:00 ��ŷ��ʱ�� 
EET +2:00 ��ŷ����USSR Zone 1�� 
FWT +2:00 ������ʱ�� 
IST +2:00 ��ɫ�б�׼ʱ�� 
MEST +2:00 ��ŷ��ʱ�� 
METDST +2:00 ��ŷ����ʱ�� 
SST +2:00 �����ʱ�� 
BST +1:00 Ӣ����ʱ�� 
CET +1:00 ��ŷʱ�� 
DNT +1:00 Dansk Normal Tid������ 
DST +1:00 Dansk Standard Time ������ 
FST +1:00 ������ʱ�� 
MET +1:00 ��ŷʱ�� 
MEWT +1:00 ��ŷ��ʱ�� 
MEZ +1:00 ��ŷʱ�� 
NOR +1:00 Ų����׼ʱ�� 
SET +1:00 Seychelles Time������ 
SWT +1:00 ��䶬ʱ�� 
WETDST +1:00 ��ŷ��������ʱ�䣨��ʱ�ƣ� 
GMT 0:00 ��������ƽ��ʱ�� 
WET 0:00 ��ŷ 
WAT -1:00 ����ʱ�� 
NDT -2:30 Ŧ�������´�½������ʱ�� 
ADT -03:00 ���������ʱ�� 
NFT -3:30 Ŧ�������´�½����׼ʱ�� 
NST -3:30 Ŧ�������´�½����׼ʱ�� 
AST -4:00 �������׼ʱ�䣨���ô� 
EDT -4:00 ��������ʱ�� 
ZP4 -4:00 GMT +4 Сʱ 
CDT -5:00 �в�����ʱ�� 
EST -5:00 ������׼ʱ�� 
ZP5 -5:00 GMT +5 Сʱ 
CST -6:00 �в���׼ʱ�� 
MDT -6:00 ɽ������ʱ�䣨��ע��Mountain Daylight Time��λ֪����ô�룿�� 
ZP6 -6:00 GMT +6 Сʱ 
MST -7:00 ɽ����׼ʱ�� 
PDT -7:00 ̫ƽ�����ʱ�� 
PST -8:00 ̫ƽ���׼ʱ�� 
YDT -8:00 Yukon ����ʱ�� 
HDT -9:00 ������/����˹�Ӱ���ʱ�� 
YST -9:00 Yukon ��׼ʱ�� 
AHST -10:00 ������-����˹�ӱ�׼ʱ�� 
CAT -10:00 �а���˹��ʱ�� 
NT -11:00 ��ʱ�䣨Nome Time�� 
IDLW -12:00 �������ڱ���ߣ����� 
*/
typedef struct tagTimeZone
{
    TCHAR szZone[8];
    int nHours;
    int nMinutes;
} S_TimeZone;

const S_TimeZone TIMEZONEs[] = 
{
    {_T("NZDT"),  13, 0}, //+13:00  //����������ʱ�䣨��ʱ�ƣ� 
    {_T("IDLE"),  12, 0}, //+12:00 �������ڱ���ߣ����� 
    {_T("NZST"),  12, 0}, // +12:00 ��������׼ʱ�� 
    {_T("NZT"),   12, 0}, //+12:00 ������ʱ�� 
    {_T("AESST"), 11, 0}, //+11:00 �Ĵ����Ƕ�����׼��ʱ�� 
    {_T("ACSST"), 10, 30},//+10:30 �аĴ����Ǳ�׼��ʱ�� 
    {_T("CADT"),  10, 30}, //+10:30 �аĴ�������ʱ�� 
    {_T("SADT"),  10, 30}, //+10:30 �ϰĴ�������ʱ�� 
    {_T("AEST"),  10, 0},//+10:00 �Ĵ����Ƕ�����׼ʱ�� 
    {_T("EAST"),  10, 0}, //+10:00 ���Ĵ����Ǳ�׼ʱ�� 
    {_T("GST"),   10, 0}, //+10:00 �ص���׼ʱ�䣬��USSR Zone 9���� 
    {_T("LIGT"),  10, 0}, //+10:00 �Ĵ�����ī���� 
    {_T("ACST"),  9, 30}, //+09:30 �аĴ����Ǳ�׼ʱ�� 
    {_T("CAST"),  9, 30}, //+09:30 �аĴ����Ǳ�׼ʱ�� 
    {_T("SAT"),   9, 30}, //+9:30 �ϰĴ����Ǳ�׼ʱ�� 
    {_T("AWSST"), 9, 0}, //+9:00 �Ĵ�����������׼��ʱ�� 
    {_T("JST"),   9, 0}, //+9:00 �ձ���׼ʱ�䣬��USSR Zone 8�� 
    {_T("KST"),   9, 0}, //+9:00 ������׼ʱ�� 
    {_T("WDT"),   9, 0}, //+9:00 ���Ĵ�������ʱ�� 
    {_T("MT"),    8, 30}, //+8:30 ë����˹ʱ�䣨���� 
    {_T("AWST"),  8, 0}, //+8:00 �Ĵ�����������׼ʱ�� 
    {_T("CCT"),   8, 0}, //+8:00 �й��غ�ʱ�� 
    {_T("WADT"),  8, 0}, //+8:00 ���Ĵ�������ʱ�� 
    {_T("WST"),   8, 0}, //+8:00 ���Ĵ�����ʱ�� 
    {_T("JT"),    7, 30}, //+7:30 צ��ʱ�䣨��ע������� Java �ɲ������ԣ� 
    {_T("WAST"),  7, 0}, //+7:00 ���Ĵ����Ǳ�׼ʱ�� 
    {_T("IT"),    3, 30}, //+3:30 ����ʱ�� 
    {_T("BT"),    3, 0}, //+3:00 �͸��ʱ�� 
    {_T("EETDST"), 3, 0}, //+3:00 ��ŷ��ʱ�� 
    {_T("CETDST"), 2, 0}, //+2:00 ��ŷ��ʱ�� 
    {_T("EET"), 2, 0}, //+2:00 ��ŷ����USSR Zone 1�� 
    {_T("FWT"), 2, 0}, //+2:00 ������ʱ�� 
    {_T("IST"), 2, 0}, //+2:00 ��ɫ�б�׼ʱ�� 
    {_T("MEST"), 2, 0}, //+2:00 ��ŷ��ʱ�� 
    {_T("METDST"), 2, 0}, //+2:00 ��ŷ����ʱ�� 
    {_T("SST"), 2, 0}, //+2:00 �����ʱ�� 
    {_T("BST"), 1, 0}, //+1:00 Ӣ����ʱ�� 
    {_T("CET"), 1, 0}, //+1:00 ��ŷʱ�� 
    {_T("DNT"), 1, 0}, //+1:00 Dansk Normal Tid������ 
    {_T("DST"), 1, 0}, //+1:00 Dansk Standard Time ������ 
    {_T("FST"), 1, 0}, //+1:00 ������ʱ�� 
    {_T("MET"), 1, 0}, //+1:00 ��ŷʱ�� 
    {_T("MEWT"), 1, 0}, //+1:00 ��ŷ��ʱ�� 
    {_T("MEZ"), 1, 0}, //+1:00 ��ŷʱ�� 
    {_T("NOR"), 1, 0}, //+1:00 Ų����׼ʱ�� 
    {_T("SET"), 1, 0}, //+1:00 Seychelles Time������ 
    {_T("SWT"), 1, 0}, //+1:00 ��䶬ʱ�� 
    {_T("WETDST"), 1, 0}, //+1:00 ��ŷ��������ʱ�䣨��ʱ�ƣ� 
    {_T("GMT"), 0, 0}, //0:00 ��������ƽ��ʱ�� 
    {_T("WET"), 0, 0}, //0:00 ��ŷ 
    {_T("WAT"), -1, 0}, //-1:00 ����ʱ�� 
    {_T("NDT"), -2, -30}, //-2:30 Ŧ�������´�½������ʱ�� 
    {_T("ADT"), -3, 0}, //-03:00 ���������ʱ�� 
    {_T("NFT"), -3, -30}, //-3:30 Ŧ�������´�½����׼ʱ�� 
    {_T("NST"), -3, -30}, //-3:30 Ŧ�������´�½����׼ʱ�� 
    {_T("AST"), -4, 0}, //-4:00 �������׼ʱ�䣨���ô� 
    {_T("EDT"), -4, 0}, //-4:00 ��������ʱ�� 
    {_T("ZP4"), -4, 0}, //-4:00 GMT +4 Сʱ 
    {_T("CDT"), -5, 0}, //-5:00 �в�����ʱ�� 
    {_T("EST"), -5, 0}, //-5:00 ������׼ʱ�� 
    {_T("ZP5"), -5, 0}, //-5:00 GMT +5 Сʱ 
    {_T("CST"), -6, 0}, //-6:00 �в���׼ʱ�� 
    {_T("MDT"), -6, 0}, //-6:00 ɽ������ʱ�䣨��ע��Mountain Daylight Time��λ֪����ô�룿�� 
    {_T("ZP6"), -6, 0}, //-6:00 GMT +6 Сʱ 
    {_T("MST"), -7, 0}, //-7:00 ɽ����׼ʱ�� 
    {_T("PDT"), -7, 0}, //-7:00 ̫ƽ�����ʱ�� 
    {_T("PST"), -8, 0}, //-8:00 ̫ƽ���׼ʱ�� 
    {_T("YDT"), -8, 0}, //-8:00 Yukon ����ʱ�� 
    {_T("HDT"), -9, 0}, //-9:00 ������/����˹�Ӱ���ʱ�� 
    {_T("YST"), -9, 0}, //-9:00 Yukon ��׼ʱ�� 
    {_T("AHST"), -10, 0}, //-10:00 ������-����˹�ӱ�׼ʱ�� 
    {_T("CAT"), -10, 0}, //-10:00 �а���˹��ʱ�� 
    {_T("NT"), -11, 0}, //-11:00 ��ʱ�䣨Nome Time�� 
    {_T("IDLW"), -12, 0}, //-12:00 �������ڱ���ߣ����� 
};

// retrieves the gmt time according to the time zone specified by lpszZone
SYSTEMTIME ConvertTimeByTimeZone(SYSTEMTIME &st, LPCTSTR lpszZone)
{
    union 
    {
        FILETIME ft;
        ULONGLONG ut;
    } t;
    
    int nSeconds = 0;
    
    SYSTEMTIME stRet = st;
    
    CString str = lpszZone;
    int nPos = str.Find(_T('0'));
    if (nPos > 0) 
    {
        // the time zone as "-0700"
        TCHAR ch = str.GetAt(0);
        int nHour = 0;
        int nMin = 0;
        CString strHour = str.Mid(1, 2);
        if (!strHour.IsEmpty()) 
        {
            nHour = _ttoi(strHour);
        }

        CString strMin = str.Mid(3, 2);
        if (!strMin.IsEmpty()) 
        {
            nMin = _ttoi(strMin);
        }
        
        nSeconds = nHour*60*60 + nMin*60;
        if (_T('-') == ch) 
        {
            nSeconds = 0 - nSeconds;
        }
    }
    else
    {
        // the time zone as "GMT"
        for(int i = 0; i < _LEN(TIMEZONEs); i++)
        {
            if (_tcscmp(lpszZone, TIMEZONEs[i].szZone) == 0) 
            {
                nSeconds = TIMEZONEs[i].nHours*60*60 + TIMEZONEs[i].nMinutes*60;
                break;
            }
        }
    }

    SystemTimeToFileTime(&stRet, &t.ft);
    
    BOOL bDec = (nSeconds >= 0);
    DWORD dwSecs = (DWORD)abs(nSeconds);
    if (bDec) 
    {
        t.ut -= UInt32x32To64(dwSecs, 10000000);
    }
    else
    {
        t.ut += UInt32x32To64(dwSecs, 10000000);
    }
    
    FileTimeToSystemTime(&t.ft, &stRet);

    return stRet;
}

// draws the 12 circle 
void DrawCircle(HDC hDC, const POINT &point, HINSTANCE hRes, UINT uID)
{
    static int s_index = 0;
    HBITMAP hBMP = ::LoadBitmap(hRes, MAKEINTRESOURCE(uID));
    HDC hMemDC = ::CreateCompatibleDC(hDC);
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, hBMP);
    ::BitBlt(hDC, point.x, point.y, 40, 40, hMemDC, 40*s_index, 0, SRCCOPY);
    ::SelectObject(hMemDC, hOldBmp);
    ::DeleteObject(hBMP);
    ::DeleteDC(hMemDC);
    s_index++;
    if (s_index >= 12) 
    {
        s_index = 0;
    }
}

// draws the text with custom font
void DrawCustomText(HDC hDC, LOGFONT *lpFont, LPCTSTR lpszText, LPRECT lpRect, 
                    COLORREF crText, UINT uFormat, int nBkMode)
{
    HFONT hFont = ::CreateFontIndirect(lpFont);
    HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);
    int nOld = ::SetBkMode(hDC, nBkMode);
    COLORREF crOld = ::SetTextColor(hDC, crText);
    ::DrawText(hDC, lpszText, _tcslen(lpszText), lpRect, uFormat);
    ::SetBkMode(hDC, nOld);
    ::SetTextColor(hDC, crOld);
    ::SelectObject(hDC, hOldFont);
    ::DeleteObject(hFont);
}


//added by Jerry Lee, 2008.7.15
// this function will retrieve the process id by the specified process file name.
DWORD FindProcess(LPCTSTR lpszProcess)
{
    DWORD dwRet = 0;
    HANDLE hThs = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hThs != INVALID_HANDLE_VALUE) 
    {
        PROCESSENTRY32 pe32;
        memset(&pe32, 0, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (Process32First(hThs, &pe32)) 
        {
            do 
            {
                if (_tcscspn(pe32.szExeFile, lpszProcess) > 0)
                {
                    dwRet = pe32.th32ProcessID;
                    break;
                }                
            	
            } while(Process32Next(hThs, &pe32));
        }
        //CloseToolhelp32Snapshot(hThs);
    }
    //
    return dwRet;
}

//added by Jerry Lee, 2008.7.15
// this function will retrieve the thread id by the specified process id.
DWORD FindMainThread(DWORD dwProcessID)
{
    DWORD dwRet = 0;
    HANDLE hThs = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessID);
    if (hThs != INVALID_HANDLE_VALUE) 
    {
        THREADENTRY32 te32;
        memset(&te32, 0, sizeof(te32));
        te32.dwSize = sizeof(te32);
        if (Thread32First(hThs, &te32)) 
        {
            do 
            {
                if (te32.th32OwnerProcessID == dwProcessID) 
                {
                    dwRet = te32.th32ThreadID;
                    break;
                }    
            } while(Thread32Next(hThs, &te32));
        }
        //CloseToolhelp32Snapshot(hThs);
    }
    //
    return dwRet;
}

//added by Jerry Lee, 2008.7.15
// suspend the threads of current process
void SuspendAllThreads(BOOL bSuspend)
{
    DWORD dwProcess = GetCurrentProcessId();
    DWORD dwThread = GetCurrentThreadId();
    HANDLE hThs = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcess);
    if (hThs != INVALID_HANDLE_VALUE) 
    {
        THREADENTRY32 te32;
        memset(&te32, 0, sizeof(te32));
        te32.dwSize = sizeof(te32);
        if (Thread32First(hThs, &te32)) 
        {
            do 
            {
                if ((te32.th32OwnerProcessID == dwProcess)
                    && (te32.th32ThreadID != dwThread)) 
                {
                    if (bSuspend) 
                    {
                        ::SuspendThread((HANDLE)te32.th32ThreadID);
                    }
                    else
                    {
                        ::ResumeThread((HANDLE)te32.th32ThreadID);
                    }
                }    
            } while(Thread32Next(hThs, &te32));
        }
        //CloseToolhelp32Snapshot(hThs);
    }
}

// suspends the process by specified process id of dwProcessID
void SuspendProcess(DWORD dwProcessID)
{
    DWORD dwThread = FindMainThread(dwProcessID);
    if (dwThread > 0) 
    {
        ::SuspendThread((HANDLE)dwThread);
    }
}

int ConvertMonth(LPCTSTR lpszMon)
{
    // Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    const LPTSTR MONTHS_ABBR[12] = 
    {
        _T("Jan"), _T("Feb"), _T("Mar"), _T("Apr"), 
        _T("May"), _T("Jun"), _T("Jul"), _T("Aug"), 
        _T("Sep"), _T("Oct"), _T("Nov"), _T("Dec"), 
    };

    const LPTSTR MONTHS[12] = 
    {
        _T("January"), _T("February"), _T("March"), _T("April"), 
        _T("May"), _T("June"), _T("July"), _T("August"), 
        _T("September"), _T("October"), _T("November"), _T("December"), 
    };

    int nRes = 1;
    for (int i = 0; i < 12; i++)
    {
        if ((_tcscmp(MONTHS[i], lpszMon) == 0) 
            || (_tcscmp(MONTHS_ABBR[i], lpszMon) == 0))
        {
            nRes = i + 1;
            break;
        }
    }
    //
    return nRes;
}

SYSTEMTIME ConvertTime(LPCTSTR lpszStr)
{
    //Tue, 11 Mar 2008 00:34:37 GMT
    LPTSTR p = (LPTSTR)lpszStr;
    TCHAR bufYear[5] = {0}; 
    TCHAR bufMon[4] = {0};
    TCHAR bufDay[3] = {0};
    TCHAR bufHour[3] = {0};
    TCHAR bufMin[3] = {0};
    TCHAR bufSec[3] = {0};
    TCHAR bufLoc[4] = {0};
    SYSTEMTIME st;
    ::GetLocalTime(&st);

    CString str = lpszStr;
    int nPos = str.Find(_T(", "));
    
    if (nPos <= 0) 
    {
        return st;
    }

    // retrieves day
    nPos += 2;
    CString strDay = str.Mid(nPos, 2);
    if (!strDay.IsEmpty()) 
    {
        st.wDay = _ttoi(strDay);
    }
    else
    {
        return st;
    }

    // retrieves month
    nPos += 3;
    int nPosMon = str.Find(_T(' '), nPos);
    if (nPosMon > 0) 
    {
        CString strMonth = str.Mid(nPos, nPosMon - nPos);
        if (!strMonth.IsEmpty()) 
        {
            st.wMonth = ConvertMonth(strMonth);
        }
        else
        {
            return st;
        }
    }

    // retrieves year
    nPos = nPosMon + 1;
    int nPosYear = str.Find(_T(' '), nPos);
    if (nPosYear > 0) 
    {
        CString strYear = str.Mid(nPos, nPosYear - nPos);
        if (!strYear.IsEmpty()) 
        {
            st.wYear = _ttoi(strYear);
        }
        else
        {
            return st;
        }
    }
    // retrieves hour
    nPos = nPosYear + 1;
    CString strHour = str.Mid(nPos, 2);
    st.wHour = _ttoi(strHour);
    
    // retrieves minutes
    nPos += 3;
    CString strMin = str.Mid(nPos, 2);
    st.wMinute = _ttoi(strMin);

    // retrieves seconds
    nPos += 3;
    CString strSec = str.Mid(nPos, 2);
    st.wSecond = _ttoi(strSec);

    // retrieves time zone
    nPos += 3;
    CString strZone = str.Mid(nPos, str.GetLength() - nPos);

    // converts the time to GMT time
    st = ConvertTimeByTimeZone(st, strZone);
    
    FILETIME ftGMT, ftLoc;
    SystemTimeToFileTime(&st, &ftGMT);
    FileTimeToLocalFileTime(&ftGMT, &ftLoc);
    FileTimeToSystemTime(&ftLoc, &st);

    //
    return st;
}

void DrawBitmap(HDC hDC, const RECT &rect, HBITMAP hBitmap)
{
    HDC hMemDC = ::CreateCompatibleDC(hDC);
    HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);
    ::BitBlt(hDC, _X(rect), _Y(rect), _W(rect), _H(rect), hMemDC, 0, 0, SRCCOPY);
    ::SelectObject(hMemDC, hOldBitmap);
    ::DeleteDC(hMemDC);
}

void DrawTextInFixedRect(HDC hDC, LOGFONT *lpFont, LPCTSTR lpszText, LPRECT lpRect, 
                         COLORREF crText, UINT uFormat, int nBkMode)
{
    HFONT hFont = ::CreateFontIndirect(lpFont);
    DrawTextInFixedRectEx(hDC, hFont, lpszText, lpRect, crText, 
        uFormat, nBkMode);
    ::DeleteObject(hFont);
}

void DrawTextInFixedRectEx(HDC hDC, HFONT hFont, LPCTSTR lpszText, 
                           LPRECT lpRect, COLORREF crText, 
                           UINT uFormat, int nBkMode)
{
    ::SetTextColor(hDC, crText);
    ::SetBkMode(hDC, nBkMode);
    HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);
    int nFit = 0;
    SIZE size;
    ::GetTextExtentExPoint(hDC, lpszText, _tcslen(lpszText),
        lpRect->right-lpRect->left, &nFit, NULL, &size);
    if (nFit < _tcslen(lpszText))
    {
        TCHAR *lpStr = new TCHAR[nFit+1];
        memset(lpStr, 0, nFit+1);
        _tcsncpy(lpStr, lpszText, nFit);
        _tcscpy(&lpStr[nFit - 3], _T("..."));
        ::DrawText(hDC, lpStr, nFit, lpRect, uFormat);
        delete [] lpStr;
    }
    else
    {
        ::DrawText(hDC, lpszText, _tcslen(lpszText), lpRect, uFormat);
    }
    //
    ::SelectObject(hDC, hOldFont);
}

void SleepEx(BOOL *pTerminate, DWORD dwMilliseconds)
{
    DWORD dwBegin = GetTickCount();
    while (!(*pTerminate) && (abs(GetTickCount() - dwBegin) < dwMilliseconds))
    {
        Sleep(1);
    }
}

/*
void LoadImageFromRes(HDC hDC, DWORD dwImgID, HINSTANCE hInstance)
{
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    
    IImagingFactory *g_pImgFactory; 
    
    //COM��ʼ��ʡ�� 
    IImage *pImage;
    
    SUCCEEDED(CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, 
        IID_IImagingFactory, (void **)&g_pImgFactory));

    //װ����Դ 
    HRSRC hr = FindResource(hInstance, MAKEINTRESOURCE(dwImgID), _T("PNG")); 
    HGLOBAL hGlobal = LoadResource(hInstance, hr); 
    LPVOID lpVoid = LockResource(hGlobal); 
    int nSize = (int)SizeofResource(hInstance, hr); 
    if(nSize > 0)
    {
        HRESULT ret1 = g_pImgFactory->CreateImageFromBuffer((BYTE*)hGlobal, nSize, 
            BufferDisposalFlagNone, &pImage);
    }
}
*/

int GetWeekDay(int year, int month, int day)
{
    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900) 
    {
        return 1;
    }

    int temp_year = 1900, temp_month = 1, temp_day = 1;// �ο�������1900��1��1�ոպ�������һ��
    int large_years = 0, small_years = 0;              // large_years�������꣬small_years����ƽ�ꣻ
    int large_months = 0, small_months = 0;            // large_months������£�small_months����С�£�
    long total_days = 0;                                   // �������ڣ��ο�����֮�����������
    
    //�����������Ͳο���1900��֮�����꣦ƽ��ĸ���
    for (int i = temp_year; i < year; i++)
    {
        if ((i%4 == 0 && i%100 != 0) || i%400 == 0)
        {
            large_years++;
        }
        else
        {
            small_years++;
        }
    }
    
    //����������ºͲο���1��֮����£�С�µĸ���
    for (int j = temp_month; j < month; j++)
    {
        if (j == 1 || j == 3 || j == 5 || j == 7 || j == 8 
            || j == 10 || j == 12)
        {
            total_days += 31;
        }
        else if (j == 4 || j == 6 || j == 9 || j == 11)
        {
            total_days += 30;
        }
        else 
        {
            if ((year%4 == 0 && year%100 != 0) || year%400 == 0) 
            {
                total_days += 29;
            }
            else
            { 
                total_days += 28;
            }
        }
    }
    
    //�����ܵ�����
    total_days += 366*large_years + 365*small_years + (day - temp_day) + 1;

    //���ظ����ڶ�Ӧ�����ڣ�0������,1����һ,2���ܶ�
    return (int)(total_days % 7);  
} 

bool Convert24HTo12H(UINT uHour, UINT &uRetHour, DWORD &dwAMPM)
{
    bool bRet = false;

    if (uHour < 24) 
    {
        uRetHour = uHour;
        if (uHour > 12 && uHour < 24)
        {
            uRetHour -= 12;
            dwAMPM = 1;
        }
        else if (uHour < 12)
        {
            if (0 == uHour)
            {
                uRetHour = 12; 
            }
            dwAMPM = 0;
        } 
        else
        {
            dwAMPM = 1;
        }
    }

    return bRet;
}

bool Convert12HTo24H(UINT uHour, DWORD dwAMPM, UINT &uRetHour)
{
    bool bRet = false;

    if (uHour < 13) 
    {
        uRetHour = uHour;
        if (1 == dwAMPM)
        {
            if (uHour < 12) 
            {
                uRetHour += 12;
            }
        }
        else if (12 == uHour)
        {
            uRetHour = 0;   
        }
    }
    
    return bRet;
}

const TCHAR* newGUID()
{
    static TCHAR buf[64] = {0};
/*
    GUID guid;
    if (S_OK == ::CoCreateGuid(&guid))
    {
        _stprintf(buf, _T("{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}")
            , guid.Data1
            , guid.Data2
            , guid.Data3
            , guid.Data4[0], guid.Data4[1]
            , guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
            , guid.Data4[6], guid.Data4[7]
            );
    }
*/
    return (const TCHAR*)buf;
}

/*
typedef void (*LPFNTOUCHPANELDISABLE)();

void CancelTouchCalibrate()
{
    // Load dll
    HINSTANCE  hinstance = LoadLibrary(_T("coredll.dll")); 
    if(hinstance == NULL)  
    {  
        return; 
    }  
    
    // Get calibrate function address
    LPFNTOUCHPANELDISABLE TouchDisable = NULL; 
    TouchDisable = (LPFNTOUCHPANELDISABLE)GetProcAddress(hinstance , _T("TouchPanelDisable") ); 
    if(TouchDisable == NULL)  
    {  
        RETAILMSG(1, (_T("TouchDisable: %d"), GetLastError()));
        return; 
    }  
    
    // Display calibrate window
    TouchDisable(); 
        
    // Free the dll
    FreeLibrary(hinstance);
    
}
*/

LONGLONG GetInterval(SYSTEMTIME st1, SYSTEMTIME st2)
{
    union 
    {
        FILETIME ft;
        ULONGLONG ut;
    } t1, t2;

    SystemTimeToFileTime(&st1, &t1.ft);
    SystemTimeToFileTime(&st2, &t2.ft);
    
	LONGLONG n1 = t1.ut/10000000;
	LONGLONG n2 = t2.ut/10000000;

	return n2 - n1;

//     if (n2 > n1) 
//     {
//         return (t2.ut - t1.ut)/10000000;
//     }
//     else
//     {
//         return 0 - abs(t1.ut - t2.ut)/10000000;
//     }
}









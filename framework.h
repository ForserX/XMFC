#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

#include <afxwin.h>         // основные и стандартные компоненты MFC
#include <afxext.h>         // Расширения MFC
#include <afxrich.h>         // Расширения MFC


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // поддержка MFC для типовых элементов управления Internet Explorer 4
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // поддержка MFC для типовых элементов управления Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // поддержка MFC для лент и панелей управления
#include <afxsock.h>            // расширения сокетов MFC
#include <afxcmn.h>			// MFC support for Windows Common Controls
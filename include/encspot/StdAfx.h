#ifndef ENCSPOT_STDAFX_H
#define ENCSPOT_STDAFX_H

#include <string>

#ifdef _WIN32

#define NOMINMAX
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
#include <atlconv.h>

#else

typedef char TCHAR;

#define MAX_PATH          260
#define MessageBox(a,b,c,d) printf(b)

#define _T(x) x
#define USES_CONVERSION
#define A2T(x) x

#define lstrcpyn        strncpy
#define _tremove        remove
#define _trename        rename
#define _tfopen         fopen
#define _sntprintf      snprintf
#define _tprintf        printf
#define _ftprintf       fprintf
#define _tmain          main

#endif

#define MYASSERT(expr) 
#define LOG(expr) 

typedef std::basic_string<TCHAR> tstring;
tstring itoa10(int value);

#endif

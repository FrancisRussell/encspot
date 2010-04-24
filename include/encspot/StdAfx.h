#ifndef ENCSPOT_STDAFX_H
#define ENCSPOT_STDAFX_H

#include <string>


///FIXME: check to see if this actually works under windows
#ifdef _WIN32

#define NOMINMAX
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
#include <atlconv.h>

#else
#include <stdint.h>

typedef unsigned short WORD;
typedef char TCHAR;
typedef char CHAR;
typedef bool BOOL;
static const BOOL TRUE = true;
static const BOOL FALSE = false;
typedef unsigned char BYTE;
typedef uint16_t UINT16;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef unsigned long DWORD;

#define MAX_PATH          260
#define MessageBox(a,b,c,d) printf(b)

#define _T(x) x
#define USES_CONVERSION
#define A2T(x) x

#define lstrcpyn	strncpy
#define	_tremove	remove
#define _trename	rename
#define	_tfopen		fopen
#define _sntprintf	snprintf
#define _tprintf	printf
#define _tmain          main

#endif

#define MYASSERT(expr) 
#define LOG(expr) 

TCHAR* itot10(const int value, TCHAR* const string, const std::size_t size);
typedef std::basic_string<TCHAR> tstring ;

#endif

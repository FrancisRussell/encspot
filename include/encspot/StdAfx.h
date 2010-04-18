#ifndef ENCSPOT_STDAFX_H
#define ENCSPOT_STDAFX_H

#include <string>
#include <stdint.h>

typedef unsigned short WORD;
typedef char TCHAR;
typedef char CHAR;
typedef int BOOL;
static const BOOL TRUE=1;
static const BOOL FALSE=0;
typedef unsigned char BYTE;
typedef uint16_t UINT16;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef unsigned long DWORD;

#define MAX_PATH          260
#define MessageBox(a,b,c,d) printf(b)
#define MYASSERT(expr) 
#define LOG(expr) 

#define _T(x) x
#define USES_CONVERSION
#define A2T(x) x

#define lstrcpyn	strncpy
#define	_tremove	remove
#define _trename	rename
#define	_tfopen		fopen
#define _sntprintf	snprintf

TCHAR* itot10(const int value, TCHAR* const string, const std::size_t size);
typedef std::basic_string<TCHAR> tstring ;

#endif

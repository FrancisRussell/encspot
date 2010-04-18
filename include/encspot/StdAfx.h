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
#define _T(x) x

#define MAX_PATH          260

#define lstrcpyn	strncpy

#define USES_CONVERSION

#define MessageBox(a,b,c,d) printf(b)

#define	_tremove	remove
#define _trename	rename
#define	_tfopen		fopen
#define _stprintf	sprintf

char* itoa10(const int value, char* const string);
typedef std::basic_string<TCHAR> tstring ;

#define MYASSERT(expr) 
#define LOG(expr) 

#define A2T(x) x

#endif

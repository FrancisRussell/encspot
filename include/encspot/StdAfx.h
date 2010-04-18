// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6C893E15_3FDF_4A64_99B9_8D50619090FE__INCLUDED_)
#define AFX_STDAFX_H__6C893E15_3FDF_4A64_99B9_8D50619090FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma once
#pragma warning(disable : 4786 )

#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <stdint.h>

using namespace std;


typedef unsigned short      WORD;
#define TCHAR	char
#define CHAR	char
#define BOOL	int
#define FALSE	0
#define TRUE	1
#define BYTE	unsigned char
#define UINT16	uint16_t
#define INT16	int16_t
#define INT32	int32_t
#define INT64	int64_t
#define DWORD	unsigned long
#define _T(x) x

#define MAX_PATH          260

#define lstrcpy		strcpy
#define lstrcat		strcat

#define USES_CONVERSION

#define MessageBox(a,b,c,d) printf(b)


#define	_tremove	remove
#define _trename	rename
#define	_tfopen		fopen
#define _itot		itoa
#define _stprintf	sprintf

char* itoa10(const int value, char* const string);

typedef basic_string<TCHAR> tstring ;
typedef	pair<tstring, tstring> tstring_pair;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif




#define MYASSERT(expr) 
#define LOG(expr) 

#define A2T(x) x






// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6C893E15_3FDF_4A64_99B9_8D50619090FE__INCLUDED_)

// EncSpot.h
#ifndef ENCSPOT_ENCSPOT_H
#define ENCSPOT_ENCSPOT_H

#include "mp3structs.h"


//#define MYFUNCTION (void (__cdecl *)(struct mp3data &,struct HWND__ *))

extern const long freqs[9];
extern TCHAR g_version[256];
extern tstring g_filedir;
extern BOOL g_reg;

tstring convert_time(const double secs);
tstring GetFormatTime(INT64 nMilli, INT64 nStart, INT64 nStop);
tstring get_long_version();
tstring get_desktop_path();
tstring get_mydocs_path();
tstring get_lower_extension(const tstring &path);
tstring get_human_readable_path(tstring display_string);
BOOL hide_extensions_enabled();
BOOL file_exists(tstring fname);
BOOL FileOp(string o, string n, WORD op);
void MakeLower(tstring &s);
void MakeUpper(tstring &s);

LPCTSTR MyPathFindExtension(LPCTSTR path);
LPTSTR MyPathFindExtension(LPTSTR path);
BOOL MyPathIsDirectory(LPCTSTR path);


#define ID_NAME			0
#define ID_ENCODER		1 
#define ID_BITRATE		2
#define ID_MODE			3
#define ID_LENGTH		4
#define ID_SIZE			5
#define ID_CUT			6 
#define ID_QUALITY		7
#define ID_FREQ			8
#define ID_FRAMES		9

#define ID_TYPE			11
#define ID_VBR			12
#define ID_CUE			13
#define ID_SYNC			14


#define ID_MAXRES		16
#define ID_AVRES		17

#define ID_PROFILE		58
#define ID_SVERSION		59

#define ID_LAMETAG		100
#define ID_QUALIND		101
#define ID_TAGREV		102
#define	ID_VBRMETHOD	103
#define	ID_LOWPASS		104
#define	ID_NSPSYTUNE	105
#define	ID_NSSAFEJOINT	106
#define	ID_NGCONTINUA	107
#define	ID_NGCONTINUED	108
#define	ID_ATHTYPE		109
#define	ID_ABRBITRATE	110
#define	ID_ARCHIVAL		111
#define	ID_INFREQ		112


#define ID_ID3_ALBUM	200
#define ID_ID3_ARTIST	201
#define ID_ID3_TITLE	202
#define ID_ID3_YEAR		203
#define ID_ID3_TRACK	204
#define ID_ID3_COMMENT	205
#define ID_ID3_GENRE	206

#endif

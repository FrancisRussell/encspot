// MppFile.h: interface for the CMppFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPPFILE_H__C6A5B6D6_3E7B_467E_A3BB_AADA8D427B71__INCLUDED_)
#define AFX_MPPFILE_H__C6A5B6D6_3E7B_467E_A3BB_AADA8D427B71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mp3structs.h"
#include "MediaFile.h"

typedef struct
{
	unsigned int StreamVersion;
	unsigned int Bitrate;
	unsigned int Frames;
	unsigned int MS;
	unsigned int ByteLength;
	unsigned int Profile;
	INT64		 Duration;		//in milliseconds

} mpp_info;



class CMppFile  : public CMediaFile
{

	int ReadFileHeader(mpp_info *Info);
	
public:
	BOOL Parse(mp3data &data);

	CMppFile();
	virtual ~CMppFile();

};

#endif // !defined(AFX_MPPFILE_H__C6A5B6D6_3E7B_467E_A3BB_AADA8D427B71__INCLUDED_)

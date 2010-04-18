// OggFile.h: interface for the COggFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGGFILE_H__8BF719B5_E39C_4204_90A5_BE6F9AD579B9__INCLUDED_)
#define AFX_OGGFILE_H__8BF719B5_E39C_4204_90A5_BE6F9AD579B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <encspot/MediaFile.h>

class COggFile : public CMediaFile 
{
public:
	COggFile();
	virtual ~COggFile();

};

#endif // !defined(AFX_OGGFILE_H__8BF719B5_E39C_4204_90A5_BE6F9AD579B9__INCLUDED_)

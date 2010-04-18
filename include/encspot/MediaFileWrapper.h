// MediaFileWrapper.h: interface for the CMediaFileWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILEWRAPPER_H__99BD8C07_9B2A_4A12_B8A8_931C07C5706F__INCLUDED_)
#define AFX_MEDIAFILEWRAPPER_H__99BD8C07_9B2A_4A12_B8A8_931C07C5706F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMediaFile;

class CMediaFileWrapper  
{
private: 
	CMediaFile *pMediaFile;

public:
	BOOL Open(tstring fname);

	CMediaFileWrapper();
	virtual ~CMediaFileWrapper();

};

#endif // !defined(AFX_MEDIAFILEWRAPPER_H__99BD8C07_9B2A_4A12_B8A8_931C07C5706F__INCLUDED_)

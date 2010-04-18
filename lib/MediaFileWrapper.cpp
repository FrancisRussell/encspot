// MediaFileWrapper.cpp: implementation of the CMediaFileWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include <encspot/StdAfx.h>
#include <encspot/MediaFileWrapper.h>
#include <encspot/MediaFile.h>
#include <encspot/Mp3File.h>
#include <encspot/MppFile.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaFileWrapper::CMediaFileWrapper() : pMediaFile(NULL)
{


}



CMediaFileWrapper::~CMediaFileWrapper()
{

}

BOOL CMediaFileWrapper::Open(tstring fname)
{
	if (CMp3File::IsThisType(fname))
		pMediaFile = new CMp3File;


	return pMediaFile != NULL;

}

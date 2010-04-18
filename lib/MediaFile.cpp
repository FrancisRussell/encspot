// MediaFile.cpp: implementation of the CMediaFile class.
//
//////////////////////////////////////////////////////////////////////

#include <encspot/StdAfx.h>
#include <encspot/MediaFile.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaFile::CMediaFile() : m_pFile(NULL),m_nFilesize(0)
{

}

CMediaFile::~CMediaFile()
{
	if (m_pFile)
		fclose(m_pFile);

}



BOOL CMediaFile::Open(tstring fname, tstring mode)
{
	m_tsFname = fname;
	

	//open for reading only
	m_pFile = fopen(fname.c_str(),mode.c_str());

	if (m_pFile)
	{
		fseek(m_pFile,0,SEEK_END);
		m_nFilesize = ftell(m_pFile);
		fseek(m_pFile,0,SEEK_SET);
	}
	
	return (m_pFile!=NULL);
}

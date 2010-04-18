#ifndef ENCSPOT_MEDIAFILE_H
#define ENCSPOT_MEDIAFILE_H

#include <encspot/StdAfx.h>
#include <cstdio>

class CMediaFile  
{


protected:

	FILE *		m_pFile;
	tstring		m_tsFname; 
	int			m_nFilesize;


public:

	BOOL	Open(tstring fname, tstring mode = _T("rb"));	
	
	void	Close() 
	{	
		fclose(m_pFile); 
		m_pFile = NULL;
	}

	CMediaFile();
	virtual ~CMediaFile();

};

#endif

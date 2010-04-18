// MediaFile.h: interface for the CMediaFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILE_H__66ACAE63_4E3D_44F9_8F46_F1D232178AD3__INCLUDED_)
#define AFX_MEDIAFILE_H__66ACAE63_4E3D_44F9_8F46_F1D232178AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_MEDIAFILE_H__66ACAE63_4E3D_44F9_8F46_F1D232178AD3__INCLUDED_)

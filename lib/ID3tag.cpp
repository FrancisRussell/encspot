#include <cstring>
#include <cstdio>
#include <string>
#include <encspot/StdAfx.h>
#include <encspot/ID3tag.h>

CID3Tag::CID3Tag() :
										 m_nVersionMajor(3),
										 m_nVersionRevision(0),
										 m_nFlags(0),
										 m_nSize(0),
										 m_bExtendedHeader(FALSE),
										 m_bExists(FALSE)
{

}

CID3Tag::~CID3Tag()
{

}

//open and parse
BOOL CID3Tag::Load(const TCHAR *szFname)
{
	m_bExists = FALSE;
	
	const int MAX_TAG_SIZE = 100000;
	m_sFname = szFname;


	m_frames.clear();
	m_nSize = 0;

	if (m_sFname=="")
		return FALSE;

	FILE *pFile = fopen(m_sFname.c_str(), "rb");
	if (pFile==NULL)
		return FALSE;

	//assume id3 tag less than MAX_TAG_SIZE (excluding padding).
	BYTE buff[MAX_TAG_SIZE];
	fread(buff,1,sizeof(buff), pFile);
	fclose(pFile);
	
	if ( (buff[0] == 'I') &&
		 (buff[1] == 'D') &&
		 (buff[2] == '3'))
	{
		//id tag exists...
		m_bExists = TRUE;
		m_nVersionMajor		= buff[3];
		m_nVersionRevision	= buff[4];
		m_nFlags			= buff[5];
		m_bExtendedHeader   = (m_nFlags >> 6) % 2;

		m_nSize = Read7Int(buff + 6);

		//probably bad format if m_nSize too large...:)
		//in any case we're not gonna handle it.
		if (m_nSize > MAX_TAG_SIZE)
		{
			m_nSize = 0;
			return FALSE;
		}

		BYTE *pFrame = buff + 10;
		int exheadersize = 0;
		if (m_bExtendedHeader)
		{
			exheadersize = ReadInt(buff + 10) + 4;
			pFrame+=exheadersize;
		}

		int frameslength = m_nSize - exheadersize;

		CFrame frame;
		int total = 0;
		for(;;)
		{
			int offset = frame.Load(pFrame, frameslength);
			pFrame+=offset;
			total+=offset;

			if (offset==-1)
				break;

			m_frames.push_back(frame);

			if (total >= frameslength)
				break;
			
		}
		
		return TRUE;
	}
	else
		return FALSE;


	

	
}

BOOL CID3Tag::Save()
{

	int total_size = 0;

	total_size = m_nSize+10;

	BYTE *pBuff = new BYTE[total_size];
	
	BYTE *pBuffPtr = pBuff;
	memcpy(pBuff, "ID3", 3);
	pBuffPtr+=3;

	*pBuffPtr			= m_nVersionMajor;
	*(pBuffPtr + 1)		= m_nVersionRevision;

	*(pBuffPtr + 2)		= 0;	//no flags! :)

	pBuffPtr+=3;
	Write7Int(pBuffPtr, total_size - 10);
	pBuffPtr+=4;

	for (int i = 0;i<m_frames.size();i++)
	{
		m_frames[i].Save(pBuffPtr);
		pBuffPtr+=m_frames[i].size();
	}

	memset(pBuffPtr, 0, (pBuff + total_size - pBuffPtr));

	FILE *pFile = fopen(m_sFname.c_str(), "r+b");
	if (pFile==NULL)
	{
		delete[] pBuff;
		return FALSE;  
	}

	fseek(pFile, 0, SEEK_SET);
	fwrite(pBuff, 1, total_size, pFile);

	fclose(pFile);
	return TRUE;
}


int CID3Tag::Read7Int(const BYTE *pBuff)
{

	BYTE size_a= *(pBuff + 0);
	BYTE size_b= *(pBuff + 1);
	BYTE size_c= *(pBuff + 2);
	BYTE size_d= *(pBuff + 3);

	int ret = size_d + (size_c << 7) + (size_b << 14) + (size_a << 21);

	return ret;

}



int CID3Tag::ReadInt(const BYTE *pBuff)
{

	BYTE size_a= *(pBuff + 0);
	BYTE size_b= *(pBuff + 1);
	BYTE size_c= *(pBuff + 2);
	BYTE size_d= *(pBuff + 3);

	int ret = size_d + (size_c << 8) + (size_b << 16) + (size_a << 24);

	return ret;

}


void CID3Tag::Write7Int(BYTE *pBuff, int nVal)
{
	*(pBuff + 3) = nVal % 128;
	*(pBuff + 2) = (nVal >> 7)  % 128;
	*(pBuff + 1) = (nVal >> 14) % 128;
	*(pBuff + 0) = (nVal >> 21) % 128;
}



void CID3Tag::WriteInt(BYTE *pBuff, int nVal)
{
	*(pBuff + 3) = nVal % 256;
	*(pBuff + 2) = (nVal >> 8)  % 256;
	*(pBuff + 1) = (nVal >> 16) % 256;
	*(pBuff + 0) = (nVal >> 24) % 256;
}

int CID3Tag::GetCueFrameNumber(tstring *pString)
{
        int i;
	for (i = 0;i<m_frames.size();i++)
	{
		tstring id = m_frames[i].id;
		if (id == "GEOB")
			break;
	}


	if (i==m_frames.size())
		return -1;
	else
	{
		if (pString)
			*pString = "GEOB";
	}
		
	std::string contents = m_frames[i].buffer;
	if (contents.find("CUESHEET")!=std::string::npos)
		return i;
	else
		return -1;		
}


void CID3Tag::MakeCueSheetFrame(const char *szCuesheet, const char *szVersion, const char *szInfo)
{
	int frame_num = GetCueFrameNumber();
	

	if (frame_num==-1)
	{
		CFrame frame;
		lstrcpy(frame.id, "GEOB");
		m_frames.push_back(frame);
		frame_num = m_frames.size()-1;
	}


	CFrame &frame = m_frames[frame_num];

	std::string text;
	text+="CUESHEET\r\n"	+ std::string(szCuesheet)+ "ENDCUESHEET";
	text+="CUEVERSION\r\n"	+ std::string(szVersion)	+ "ENDCUEVERSION";
	text+="CUEINFO\r\n"		+ std::string(szInfo)	+ "ENDCUEINFO";

	
	frame.buffer+='\0';  //encoding as ascii
	frame.buffer+="text"; //mime
	frame.buffer+='\0';
	frame.buffer+="mp3cue CueSheet";//filename
	frame.buffer+='\0';
	frame.buffer+='Q';	//descriptor
	frame.buffer += text;

}

BOOL CID3Tag::RemoveTagFromFile()
{
	if (m_nSize==0)
		return FALSE;

	FILE *pFile = fopen(m_sFname.c_str(), "r+b");
	if (pFile==NULL)
		return FALSE;  

	BYTE *pBuff = new BYTE[m_nSize+10];
	memset(pBuff,0,m_nSize+10);

	fseek(pFile, 0, SEEK_SET);
	fwrite(pBuff, 1, m_nSize+10, pFile);
	fclose(pFile);

	return TRUE;
}

BOOL CID3Tag::GetCueFrame(tstring &data)
{
	int i = GetCueFrameNumber();
	if (i==-1)
		return FALSE;


	CFrame &frame = m_frames[i];
	if (frame.buffer.size() < 20)
		data = "";
	else 
	{
		const TCHAR *szBuff = frame.buffer.c_str();
		if (*szBuff == 0 && *(szBuff + 1)==0)
			data = frame.buffer.c_str()+4;
		else if (*szBuff==0x01)
		{
			MessageBox(GetActiveWindow(), "UNICODE not supported in this version.",0,0);
			return FALSE;
		}
		else if (*szBuff==0x00)//not unicode
		{
			tstring mime = szBuff + 1;
			tstring filename = szBuff + 1 + mime.size()+1;
			data = szBuff + 1 + mime.size() + 1 + filename.size() + 1 + 1;
		}
		else //non conforming early version.
			data = szBuff;
		

			

	}	

	return TRUE;
}

BOOL CID3Tag::GetTextFrame(const std::string szID, std::string &data)
{
	int frame_num = GetFrameNumber(szID);

	if (frame_num==-1)
		return FALSE;

	CFrame &frame = m_frames[frame_num];

	data = frame.buffer.empty()?"":frame.buffer.c_str()+1;
	return TRUE;
}


void CID3Tag::MakeTextFrame(const std::string szID, const std::string &data)
{

	int frame_num = GetFrameNumber(szID);

	if (frame_num==-1)
	{
		CFrame frame;
		lstrcpy(frame.id, szID.c_str());
		m_frames.push_back(frame);
		frame_num = m_frames.size()-1;
	}


	CFrame &frame = m_frames[frame_num];
	
	frame.buffer = "";
	frame.buffer+='\0';
	frame.buffer+=data;
}

int CID3Tag::GetFrameNumber(const std::string id)
{
	for (int i = 0;i<m_frames.size();i++)
	{
		if (m_frames[i].id==id)
			return i;
	}

	return -1;

}

BOOL CID3Tag::CreateNewSpace(int nSpace, iProgCallback *pCallback)
{

	char tpath[MAX_PATH];
	lstrcpy(tpath,m_sFname.c_str());
	lstrcat(tpath,"_tmp");
	FILE *pTfile = NULL;
	pTfile = _tfopen(tpath,"wb");
	if (pTfile == NULL) 
	{
		MessageBox(GetActiveWindow(), "Unable to open temp file for writing",NULL,NULL);
		return FALSE;
	 
	}
	BYTE *pZero = new BYTE[nSpace];
	memset(pZero,0,nSpace);
	fwrite(pZero,1,nSpace,pTfile);
	delete[]pZero;

	//1MB at a time
	const int nBlockSize = 1000000;
	BYTE data[nBlockSize];
	FILE *pOld = _tfopen(m_sFname.c_str(),"rb");
	if (pOld == NULL)
	{
		MessageBox(GetActiveWindow(),"Unable to open file for reading",NULL,NULL);
		return FALSE;
	}

	fseek(pOld, 0, SEEK_END);
	int nOldSize = ftell(pOld);
	fseek(pOld, 0, SEEK_SET);

	int nCount = 0;
	while (!feof(pOld))
	{
		int read = fread(&data,1,sizeof(data),pOld);
		fwrite(&data,1,read,pTfile);

		++nCount; 
		if (pCallback && nOldSize)
		{
			
			if (!pCallback->Report((100 * (float)nBlockSize * nCount)/nOldSize))
			{

				//aborted.
				fclose(pOld);
				fclose(pTfile);

				//delete temp file
				_tremove(tpath);
				return FALSE;
			}
		}

	}

	fclose(pOld);
	fclose(pTfile);

	if (_tremove(m_sFname.c_str())!=0 || _trename(tpath,m_sFname.c_str())!=0)
		MessageBox(GetActiveWindow(), _T("Failed to add new space to file for some reason..."),_T("Error"), 0);
//	FileOp(tpath, m_sFname.c_str(),FO_RENAME);

	//by adding this space we've increased the size of the 
	//tag.
	if (m_nSize==0)
		m_nSize = nSpace - 10;
	else
		m_nSize+=nSpace;

	return TRUE;

}

int CID3Tag::size()
{
	return m_nSize;

}

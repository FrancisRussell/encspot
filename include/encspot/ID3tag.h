#ifndef ENCSPOT_ID3TAG_H
#define ENCSPOT_ID3TAG_H

#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include "Callbacks.h"
#include "StdAfx.h"

class CID3Tag  
{
private:
  static UINT32 Read7Int(const BYTE *pBuff);
  static UINT32 ReadInt(const BYTE *pBuff);

  static void WriteInt(BYTE *pBuff, UINT32 nVal);
  static void Write7Int(BYTE *pBuff, UINT32 nVal);

  struct CFrame
  {
    std::string buffer;
    char id[5];

    BYTE m_flags_high;
    BYTE m_flags_low;

    CFrame() : m_flags_high(0), m_flags_low(0)
    {
      memset(id, 0, sizeof(id));
    }

    int size() const 
    { 
      return 10+buffer.size(); 
    }

    int Load(const BYTE *pFrame, const UINT32 nMaxSize)
    {
      memcpy(id, pFrame, 4);
      id[4] = 0;

      if (id[0]==0)
        return -1;

      pFrame+=4;
      const UINT32 size = ReadInt(pFrame);

      //limit to 100KB to help spot errors...
      if (abs(size) > nMaxSize)
        return -1;

      pFrame+=4;
      m_flags_high = pFrame[0];
      m_flags_low  = pFrame[1];
      buffer.assign(reinterpret_cast<const char *>(pFrame)+2, size);
      
      return (size + 10);    
    }

    void Save(BYTE *pBuff) const
    {
      memcpy(pBuff, id, 4);
      pBuff+=4;
      WriteInt(pBuff, buffer.size());
      pBuff+=4;
      pBuff[0] = m_flags_high;
      pBuff[1] = m_flags_low;
      pBuff+=2;
      memcpy(pBuff, buffer.data(), buffer.size());
    }
  };

  friend struct CFrame;

  tstring m_sFname;
  BYTE    m_nVersionMajor;
  BYTE    m_nVersionRevision;
  BYTE    m_nFlags;
  int     m_nSize;

  BOOL m_bExtendedHeader;

  std::vector<CFrame> m_frames;

public:
  int size() const;

  BOOL    m_bExists;

  BOOL    CreateNewSpace(int nSpace, iProgCallback *pCallback = NULL);
  BOOL    GetTextFrame(const std::string &szID, std::string &data) const;
  int     GetFrameNumber(const std::string &id) const;
  void    MakeTextFrame(const std::string szID, const std::string &data);
  BOOL    RemoveTagFromFile();
  void    MakeCueSheetFrame(const char *szCuesheet, const char *szVersion, const char *szInfo);
  int     GetCueFrameNumber(tstring *pString = NULL) const;
  BOOL    GetCueFrame(tstring &data) const;
  
  BOOL    Load(const TCHAR *szFname);
  BOOL    Save();
  CID3Tag();
  virtual ~CID3Tag();
};

#endif

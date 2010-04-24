#ifndef ENCSPOT_ID3TAG_H
#define ENCSPOT_ID3TAG_H

#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include "Callbacks.h"

class CID3Tag  
{
private:
  static int Read7Int(const BYTE *pBuff);
  static int ReadInt(const BYTE *pBuff);

  static void WriteInt(BYTE *pBuff, int nVal);
  static void Write7Int(BYTE *pBuff, int nVal);

  struct CFrame
  {
    std::string buffer;
    char id[5];

    BYTE m_flags_high;
    BYTE m_flags_low;

    CFrame()
    {
        memset(id, 0, sizeof(id));
        m_flags_high = 0;
        m_flags_low  = 0;
    }

    int size() { return (10 + buffer.size()); }

    int Load(BYTE *pFrame, int nMaxSize)
    {
      memcpy(id,pFrame, 4);
      id[4] = 0;

      if (id[0]==0)
          return -1;

      pFrame+=4;
      int size = ReadInt(pFrame);

      //limit to 100KB to help spot errors...
      if (abs(size) > nMaxSize)
          return -1;

      pFrame+=4;
      m_flags_high = *(pFrame + 0);
      m_flags_low  = *(pFrame + 1);
      buffer.assign((const char *)(pFrame)+2, size);
      
      return (size + 10);    
    }

    void Save(BYTE *pBuff)
    {
      memcpy(pBuff, id, 4);
      pBuff+=4;
      WriteInt(pBuff, buffer.size());
      pBuff+=4;
      *(pBuff + 0) = m_flags_high;
      *(pBuff + 1) = m_flags_low;
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
  int size();

  BOOL    m_bExists;

  BOOL    CreateNewSpace(int nSpace, iProgCallback *pCallback = NULL);
  BOOL    GetTextFrame(const std::string szID, std::string &data);
  int     GetFrameNumber(const std::string id);
  void    MakeTextFrame(const std::string szID, const std::string &data);
  BOOL    RemoveTagFromFile();
  void    MakeCueSheetFrame(const char *szCuesheet, const char *szVersion, const char *szInfo);
  int     GetCueFrameNumber(tstring *pString = NULL);
  BOOL    GetCueFrame(tstring &data);
  
  BOOL    Load(const TCHAR *szFname);
  BOOL    Save();
  CID3Tag();
  virtual ~CID3Tag();
};

#endif

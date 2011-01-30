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
  static uint32_t Read7Int(const uint8_t *pBuff);
  static uint32_t ReadInt(const uint8_t *pBuff);

  static void WriteInt(uint8_t *pBuff, uint32_t nVal);
  static void Write7Int(uint8_t *pBuff, uint32_t nVal);

  struct CFrame
  {
    std::string buffer;
    char id[5];

    uint8_t m_flags_high;
    uint8_t m_flags_low;

    CFrame() : m_flags_high(0), m_flags_low(0)
    {
      memset(id, 0, sizeof(id));
    }

    int size() const 
    { 
      return 10+buffer.size(); 
    }

    int Load(const uint8_t *pFrame, const uint32_t nMaxSize)
    {
      memcpy(id, pFrame, 4);
      id[4] = 0;

      if (id[0]==0)
        return -1;

      pFrame+=4;
      const uint32_t size = ReadInt(pFrame);

      //limit to 100KB to help spot errors...
      if (size > nMaxSize)
        return -1;

      pFrame+=4;
      m_flags_high = pFrame[0];
      m_flags_low  = pFrame[1];
      buffer.assign(reinterpret_cast<const char *>(pFrame)+2, size);
      
      return (size + 10);    
    }

    void Save(uint8_t *pBuff) const
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
  uint8_t    m_nVersionMajor;
  uint8_t    m_nVersionRevision;
  uint8_t    m_nFlags;
  int     m_nSize;

  bool m_bExtendedHeader;

  std::vector<CFrame> m_frames;

public:
  int size() const;

  bool    m_bExists;

  bool    CreateNewSpace(int nSpace, iProgCallback *pCallback = NULL);
  bool    GetTextFrame(const std::string &szID, std::string &data) const;
  int     GetFrameNumber(const std::string &id) const;
  void    MakeTextFrame(const std::string szID, const std::string &data);
  bool    RemoveTagFromFile();
  void    MakeCueSheetFrame(const char *szCuesheet, const char *szVersion, const char *szInfo);
  int     GetCueFrameNumber(tstring *pString = NULL) const;
  bool    GetCueFrame(tstring &data) const;
  
  bool    Load(const TCHAR *szFname);
  bool    Save();
  CID3Tag();
  virtual ~CID3Tag();
};

#endif

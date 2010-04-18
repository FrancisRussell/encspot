#include <cstring>
#include <encspot/StdAfx.h>
#include <encspot/MppFile.h>

CMppFile::CMppFile() 
{
}

CMppFile::~CMppFile()
{
}


//_must_ be valid mpp file, or will give garbage.
int CMppFile::ReadFileHeader(mpp_info *Info)
{
  MYASSERT(m_pFile);
  memset(Info, 0, sizeof(Info));

  unsigned int HeaderData[3];
  char Tag[4] = {0,0,0,0};

  Info->ByteLength = m_nFilesize;
  fseek(m_pFile, 0, SEEK_SET);
  fread((void*)HeaderData, sizeof(int), 3, m_pFile);

  // search for id3-tag
  memcpy(Tag, HeaderData, 3);
  if (!strcmp(Tag,"MP+")) 
    Info->StreamVersion = HeaderData[0]>>24;
  
  if (Info->StreamVersion>=7)
  {
    // read the file-header (SV7 and above)
    Info->Bitrate = 0;
    Info->Frames  =  HeaderData[1];
    Info->MS      = (HeaderData[2]<<1)>>31;
    if ( (HeaderData[2]<<8)>>31 ) Info->Profile = (HeaderData[2]<<9)>>29;
    else                          Info->Profile = 6;
  }
  else
  {
    // read the file-header (SV6 and below)
    Info->Bitrate       =  (HeaderData[0]>>23);
    Info->MS            = ((HeaderData[0]<<10)>>31);
    Info->StreamVersion = ((HeaderData[0]<<11)>>22);
    Info->Profile = 6;
    if (Info->StreamVersion>=5) 
      Info->Frames =  HeaderData[1];
    else
      Info->Frames = (HeaderData[1]>>16);
  }

  // Bugfix: last frame was invalid for up to SV5
  if (Info->StreamVersion<6) Info->Frames -= 1;

  Info->Duration = (INT64)(Info->Frames*1152/44.1f+0.5f); 

  return 0;
}

BOOL CMppFile::Parse(mp3data &data)
{

  mpp_info info;

  ReadFileHeader(&info);

  data.length    = info.Duration / 1000;      //length in seconds.
  data.frameCount = info.Frames;
  data.fsize    = m_nFilesize;

  data.mpp_stream_version = info.StreamVersion;
  data.mpp_stream_profile = info.Profile;
  data.mode        = info.MS?MPG_MD_JOINT_STEREO:MPG_MD_STEREO;
  data.base_freq      = 44100;
  data.vbr        = TRUE;

  float fLen    = info.Duration;
  data.bitrate  = (m_nFilesize * 8) / fLen;
  data.all_read  = TRUE;

  return TRUE;
}
 

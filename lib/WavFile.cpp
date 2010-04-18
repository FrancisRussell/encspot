#include <cstring>
#include <encspot/StdAfx.h>
#include <encspot/WavFile.h>

CWavFile::CWavFile()
{
}

CWavFile::~CWavFile()
{
}



//never scan full.....
BOOL CWavFile::ProcessFrames(BOOL bFull, mp3data &data_out, int nFrameLimit)
{
  MYASSERT(m_pFile);

  //Prelims...
  lstrcpy(data_out.path, m_tsFname.c_str());
  

  //read data.
  WAVDATA wavdata;
  int read = fread(&wavdata, 1, sizeof(WAVDATA), m_pFile);
  if (read!=sizeof(WAVDATA))
    return FALSE;

  data_out.base_freq = wavdata.frequency;
  data_out.nch     = wavdata.channels;
  double len = wavdata.data_length / wavdata.av_bytes_per_sec;

  data_out.length    = len;
  data_out.bitrate  = (wavdata.av_bytes_per_sec * 8) / 1000;

  return TRUE;
}

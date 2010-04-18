#ifndef ENCSPOT_MPPFILE_H
#define ENCSPOT_MPPFILE_H

#include "mp3structs.h"
#include "MediaFile.h"

struct mpp_info
{
  unsigned int StreamVersion;
  unsigned int Bitrate;
  unsigned int Frames;
  unsigned int MS;
  unsigned int ByteLength;
  unsigned int Profile;
  INT64     Duration;    //in milliseconds
};

class CMppFile : public CMediaFile
{
  int ReadFileHeader(mpp_info *Info);
  
public:
  BOOL Parse(mp3data &data);

  CMppFile();
  virtual ~CMppFile();
};

#endif

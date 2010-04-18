#ifndef ENCSPOT_MEDIAFILEWRAPPER_H
#define ENCSPOT_MEDIAFILEWRAPPER_H

class CMediaFile;

class CMediaFileWrapper  
{
private: 
  CMediaFile *pMediaFile;

public:
  BOOL Open(tstring fname);

  CMediaFileWrapper();
  virtual ~CMediaFileWrapper();
};

#endif

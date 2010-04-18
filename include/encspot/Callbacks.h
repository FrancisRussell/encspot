#ifndef ENCSPOT_CALLBACKS_H
#define ENCSPOT_CALLBACKS_H

struct iProgCallback
{
  virtual BOOL Report(int nProg) = 0;
};

#endif

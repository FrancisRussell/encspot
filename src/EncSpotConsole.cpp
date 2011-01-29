#include <vector>
#include <string>
#include <exception>
#include <cstdio>
#include <encspot/StdAfx.h>
#include <encspot/Mp3File.h>

// Is this really needed, even under Windows?
static tstring trim(const tstring& arg)
{
  if (arg.size()>=2 && arg[0]==_T('\"') && arg[arg.size()-1]==_T('\"'))
  {
    return tstring(arg.begin()+1, arg.end()-1);
  }
  else
  {
    return arg;
  }
}

int _tmain(int argc, TCHAR* argv[])
{
  std::vector<tstring> list;
  for (int i=1; i<argc; ++i)
    list.push_back(trim(argv[i]));

  for (unsigned i=0; i<list.size(); ++i)
  {
    const tstring item = list[i];
    CMp3File mp3;

    if (mp3.Open(item))
    {
      try
      {
        mp3data data;
        memset(&data,0,sizeof(data));
        mp3data_string data_string;
        data_string.path = item;

        mp3.ProcessFrames(TRUE, data, -1, NULL, TRUE /*DisableCache*/, NULL);
        data.quality = data_string.update(data, FALSE);
        const tstring out_string = data_string.get_report(data, _T("EncSpot Console 2.0"));
        _tprintf((out_string + _T("\n\n\n\n")).c_str());
      }
      catch (const std::exception& e)
      {
        USES_CONVERSION;
        _tprintf(A2T("An exception was thrown: %s\n"), e.what());
      }
    }
    else
    {
      _tprintf(_T("File not found : \n\n%s\n\n\n\n"), item.c_str());
    }
  }

  return 0;
}

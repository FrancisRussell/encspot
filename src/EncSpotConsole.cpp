#include <vector>
#include <string>
#include <encspot/StdAfx.h>
#include <encspot/Mp3File.h>

static tstring Trim(tstring arg)
{
  if (arg[0]==_T('\"'))
    arg.erase(arg.begin());

  if (arg[arg.size()-1]==_T('\"'))
    arg.erase(arg.end()-1);

  return arg;
}


int _tmain(int argc, TCHAR* argv[])
{
  std::vector<tstring> list;
  for (int i = 1;i<argc;i++)
    list.push_back(Trim(argv[i]));

  for (int i = 0;i<list.size();i++)
  {
    tstring item = list[i];
    CMp3File mp3;
    if (mp3.Open(item))
    {
    
      mp3data data;
      memset(&data,0,sizeof(data));
      mp3data_string data_string;
      data_string.path = item;

      mp3.ProcessFrames(TRUE, data, -1, NULL, TRUE /*DisableCache*/, NULL);
      data.quality = data_string.update(data,FALSE);

      tstring out_string = data_string.get_report(data,_T("EncSpot Console 2.0"));
      _tprintf((out_string + _T("\n\n\n\n")).c_str());
    }
    else
    {
      _tprintf(_T("File not found : \n\n%s\n\n\n\n"), item.c_str());
    }
  }

  return 0;
}


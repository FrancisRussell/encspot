// stdafx.cpp : source file that includes just the standard includes
// EncSpotStaticLib.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include <string>
#include <sstream>
#include <encspot/StdAfx.h>

tstring itoa10(const int value)
{
  std::basic_ostringstream<TCHAR> stream;
  stream << value;
  return stream.str();
}


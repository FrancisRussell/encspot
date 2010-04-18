// stdafx.cpp : source file that includes just the standard includes
//	EncSpotStaticLib.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include <encspot/StdAfx.h>

char* itoa10(const int value, char* const string)
{
  sprintf(string, "%d", value);
  return string;
}


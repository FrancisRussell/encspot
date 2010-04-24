// stdafx.cpp : source file that includes just the standard includes
// EncSpotStaticLib.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include <cstdio>
#include <encspot/StdAfx.h>

TCHAR* itot10(const int value, TCHAR* const string, const std::size_t size)
{
  _sntprintf(string, size, _T("%d"), value);
  return string;
}


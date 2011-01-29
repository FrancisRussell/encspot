add_library(libencspot STATIC ID3tag.cpp MediaFile.cpp
Mp3File.cpp mp3structs.cpp StdAfx.cpp)
set_target_properties(libencspot PROPERTIES OUTPUT_NAME encspot)

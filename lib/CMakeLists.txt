add_library(libencspot STATIC ID3tag.cpp MediaFile.cpp MediaFileWrapper.cpp
Mp3File.cpp mp3structs.cpp MppFile.cpp OggFile.cpp StdAfx.cpp WavFile.cpp)
set_target_properties(libencspot PROPERTIES OUTPUT_NAME encspot)

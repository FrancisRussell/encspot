#ifndef ENCSPOT_WAVFILE_H
#define ENCSPOT_WAVFILE_H

#include <encspot/MediaFile.h>
#include <encspot/mp3structs.h>

struct WAVDATA
{
	//RIFF Header
	char	label[4];			//should be RIFF, else FAIL
	INT32	length;				//length of format chunk to follow (including data...)

	//FORMAT CHUNK
	char	format[4];			//should be WAVE, else unknown
	char	fmt[4];				//should be 'fmt '
	INT32 format_length;		//length of format data = 16
	INT16 format_tag;			//0x01 = PCM
	INT16 channels;			//1 or 2
	
	INT32 frequency;			//in Hz
	INT32 av_bytes_per_sec;	//nChannels * nSamplesPerSec * (nBitsPerSample/8)
	
	INT16 block_align;		//nChannels * (nBitsPerSAmple / 8)
	INT16 bits_per_sample;	//8 or 16 (or 24?)

	//DATA CHUNK
	char	data_label[4];		//should say 'data'
	INT32   data_length;		//length of sample data
	
	
	
};

class CWavFile  : public CMediaFile
{
public:
	CWavFile();
	virtual ~CWavFile();


	BOOL	ProcessFrames(BOOL bFull, mp3data &data_out, int nFrameLimit);


};

#endif

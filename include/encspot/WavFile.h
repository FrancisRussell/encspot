// WavFile.h: interface for the CWavFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVFILE_H__29400D4E_76A7_43B5_AA24_D6F1C35F650B__INCLUDED_)
#define AFX_WAVFILE_H__29400D4E_76A7_43B5_AA24_D6F1C35F650B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_WAVFILE_H__29400D4E_76A7_43B5_AA24_D6F1C35F650B__INCLUDED_)

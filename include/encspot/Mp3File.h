#ifndef ENCSPOT_MP3FILE_H
#define ENCSPOT_MP3FILE_H

#include "ID3tag.h"
#include "mp3structs.h"

#define MPG_MD_STEREO       0
#define MPG_MD_JOINT_STEREO 1
#define MPG_MD_DUAL_CHANNEL 2
#define MPG_MD_MONO         3

extern const char *const genre_names[];


#define MPEGID_1			0x0		//MPEG Version 1 (ISO/IEC 11172-3) 	
#define MPEGID_2			0x1		//MPEG Version 2 (ISO/IEC 13818-3)

#include "MediaFile.h"

struct mp3header
{
	int id;							//e.g. MPEG version 1, unless idex = 1
	int idex;						//1 = MPEG 2.5
	int bitrate_idx;				//between 0 and 15
	int mode;						//e.g. joint stereo
	int modeex;						//e.g. joint stereo usage
	int padding;					//0 or 1
	int freq;						//e.g. 44100
	int channels;					//e.g. 1 = mono, 2 = stereo
	int layer;						//1,2 or 3	
	int protection;					//crc protection bit

	int copyright;
	int emphasis;
	int original;
};
 
struct mp3data;
struct xing;
struct thread_helper;



class CMp3File  : public CMediaFile
{
	
	int			m_nLastBits;
	int			m_lastBits;

public:	

	static bool IsThisType(tstring fname)
	{
		CMp3File afile;
		return(afile.IsMp3File(fname));
	}
	


	BOOL UpdateID3v1(id3v1 tag, int track);
	
	struct sink
	{
		virtual BOOL Fire(const mp3data &data) const = 0;
	};

	struct sink_mini
	{
		virtual BOOL Fire(INT64 nCurr, INT64 nTotal) const = 0;
	};


	BOOL	Open(tstring fname, tstring mode = _T("rb"))
	{
		m_tag.Load(fname.c_str());
		return CMediaFile::Open(fname, mode);	
	}

	
	CID3Tag	m_tag;
	
	int		GetFilesize() { return m_nFilesize;	}
	float	GetAverageBitrate(const mp3data &data);
	BOOL	ProcessFrames(BOOL bFull, mp3data &data_out, int nFrameLimit,info_lists *pInfoLists,BOOL bDisableCache,CMp3File::sink *pHelp = NULL);
	BOOL	Trim(INT64 nStart, INT64 nStop,const mp3data &data,const vector<int> &byte_locations,tstring newpath,BOOL bNewXing,BOOL bID3, CMp3File::sink_mini *pSink = NULL);
	BOOL	ExtractRegion(INT64 nStart, INT64 nStop,const mp3data &data,const vector<int> &byte_locations,tstring newpath,BOOL bNewXing,BOOL bID3, CMp3File::sink_mini *pSink = NULL);
	BOOL	AppendMP3(mp3data datain1, tstring path2, tstring pathout, BOOL bID1, BOOL bID2, CMp3File::sink_mini *pHelp);
	CMp3File();
	virtual ~CMp3File();

	
	
	tstring TranslateLabel(tstring label);
	int	GetMusicCRC(mp3data &data, const CMp3File::sink_mini *pHelp=NULL);

private:

	bool	IsMp3File(tstring fname);

	BOOL	FullProcessFrames(mp3data &data_out, int nFrameLimit,info_lists *pInfoLists,BOOL bDisableCache, int id3v1pos, int initpos,CMp3File::sink *pHelp = NULL);
	
	void	CreateI2(BYTE *buf, int nValue);
	void	CreateI4(BYTE *buf, int nValue);
	BOOL	copy_file_data(FILE *new_file, FILE *old_file, int nStart, int nSize = -1, CMp3File::sink_mini *pSink = NULL);
	BOOL	DetectVBR(mp3data &data_out);
	BOOL	ReportProgress(mp3data &data, const sink *pHelp);
	int		UpdateInfoFromHeader(mp3data &out_data, const mp3header &hHeader);

	int		SeekNextHeader(int safety_max = 5);
	int		SeekLastHeader(BYTE *final10 = NULL);
	
	BOOL	GetVBRIHeader(mp3data &data, unsigned char *buf);
	int		GetXingHeader(mp3data &data, unsigned char *buf);
	
	
	int			GuessFrameLength();
	BOOL		ProcessNextFrame(mp3data &data_out,info_lists *pInfoLists);
	tstring		GetLabelsFromBuffer(const char *buff, int len);
	tstring		ReportOutOfSyncError(mp3data &main_data, const mp3header &hHeader);
	BOOL		CheckDone(mp3data &data, int pos);
	void		SetBaseInfo(mp3data &data, const mp3header &header);

	
	tstring GetLabels(const XHEADDATA &xing);

	int ReadInt();
	int ReadInt(BYTE *pBuffer);

	//used to be head_check2
	int MakeHeader(unsigned long head, mp3header &mhHead);

	BOOL		GetVBRTags(mp3data &data);
	BOOL		GetID3v2(mp3data &data);
	int			GetID3v1(mp3data &data);

	unsigned long int readBits(int n);


};

#endif

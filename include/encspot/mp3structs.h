#ifndef ENCSPOT_MP3STRUCTS_H
#define ENCSPOT_MP3STRUCTS_H

#include <vector>
#include <map>

extern const char *const genre_names[];
extern const int tabsel_123[2][3][16];
extern const int genre_count;

#define MAX_SYNC_ERRORS  21

#define FRAMES_FLAG     0x0001
#define BYTES_FLAG      0x0002
#define TOC_FLAG        0x0004
#define VBR_SCALE_FLAG  0x0008

#define FRAMES_AND_BYTES (FRAMES_FLAG | BYTES_FLAG)

// structure to receive extracted header
// toc may be NULL
// AUGMENTED VERSION: contains extra LAME info.
struct XHEADDATA {
  int h_id;       // from MPEG header, 0=MPEG2, 1=MPEG1
  int samprate;   // determined from MPEG header
  int flags;      // from Xing header data
  int frames;     // total bit stream frames from Xing header data
  int bytes;      // total bit stream bytes from Xing header data
  int vbr_scale;  // encoded vbr scale from Xing header data
  unsigned char *toc;  // pointer to unsigned char toc_buffer[100]
                         // may be NULL if toc not desired

  //lame stuff...
  
  char encoder[12];
  BOOL bValidLame;
  BOOL bValidMusic;    //music_crc
  BYTE tag_revision;
  BYTE vbr_method;
  int  lowpass;
  BYTE replay_gain[8];
  BYTE encoding_flags;
  BYTE ath_type;
  BYTE abr_bitrate;
  BYTE encoder_delays[3];
  BYTE unused[3];
  int   nFirstFrameSize;
  
  //misc
  BYTE noise_shaping;
  BYTE stereo_mode;
  BOOL unwise;
  BYTE input_freq;
  
  int    music_length;
  UINT16  music_crc;
  BOOL  music_crc_calculated;

  UINT16  tag_crc;
};

//layout of VBRI tag frame:

//-- -- -- -- AA AA AA AA BB BB XX XX CC CC DD DD
//DD DD EE EE EE EE FF FF GG GG HH HH YY YY  ZZ ZZ
//ZZ ZZ .........

//AA AA AA AA    =  VBRI
//BB BB XX XX    =  magic number 00 01 09 31 ..probably flags for options that can't be changed!
//CC             =  vbr_scale.
//DD DD DD DD    =  filesize
//EE EE EE EE    =  number of frames...(seems to be slightly wrong??)
//FF FF          =  size of table of contents in 16 bit words (number of ZZ ZZs)
//GG GG HH HH    =  unknown... always 00 01 00 02            
            
//YY YY          =  multiplier: each entry in the TOC refers to this many frames. 
//                  Hence YY * FF = EE (more or less: remainder term).
//ZZ ...         =  TOC. 16 bit values. Each word ZZ ZZ has value equal to the
//                  total number of bytes encoding n frames, where n is the 'multiplier'
//                  in YY YY.


/*  Now, the size of TOC is a function only of the number of frames.
  
  claim : value is number of bytes required for that secion of the file.


  TOC Size          32kbps constant during period (silence)
  ---------          ---------------

  8D = 141            0x01A0
  8E = 142              


  BB * 10

  141 sections, about 14s
  142 sections, 7.4


  useful info.

  Mpeg 1 Layer III 32kbps frame      framesize = 0x68  (no padding)
  
*/


#define MAX_TOC_SIZE 0x200

struct VBRIDATA 
{
  UINT16 unknown1;
  UINT16 unknown2;
  UINT16 vbr_scale;        //e.g. -vbr 80 implies vbr_scale == 80
  INT32 bitstream_bytes;
  INT32 frames;
  UINT16 toc_size;
  UINT16 unknown3;
  UINT16 unknown4;
  UINT16 toc_mult;
  UINT16 toc[MAX_TOC_SIZE];
};


#define XING_FRAMES_FLAG  1
#define XING_BYTES_FLAG    2
#define XING_TOC_FLAG    4
#define XING_VBR_SCALE_FLAG  8

struct info_lists
{
  std::vector<int>    bigvalues;
  std::vector<BOOL>  scalefac;
  std::vector<BYTE>  bitlist;
  std::vector<int>    reslist;
  std::vector<BOOL>  modelist;
  std::vector<BOOL>  blocklist;
  std::vector<int>    byte_location;    //location of frame in file.
};

/*struct xing
{
  char    header_sync[4];    //"Xing"
  int      flags;        //see above...
  int      frames;        //number of frames
  BYTE      toc[100];      //table of contents
  int      scale;        //?
};
*/

//in order: memcpy ok
//note: strings are _not_necessarily null terminated.
struct id3v1
{

  char tag_id[3];      //should be TAG
  char title[30];      
  char artist[30];
  char album[30];
  char year[4];
  char comment[30];
  BYTE genre;
};


#define MEDIATYPE_MP3      0x01
#define MEDIATYPE_VORBIS    0x02
#define MEDIATYPE_WAV      0x03
#define MEDIATYPE_MPP      0x04
#define MEDIATYPE_UNKNOWN    0x00


//contains information about a media file. 
struct mp3data
{

  DWORD type;

  //common stuff.....

  id3v1  id3v1tag;
  int    id3v1_track;
  BOOL  bId3v1Tag;
  BOOL  bId3v2Tag;

  int quality;


  TCHAR label[32];
  
  int bitrateCount[16];
  int blockCount[3];
  int modeCount[4];
  int frameCount;
  float length;      //in seconds
  
  int  fsize;
  int   base_freq;
  int   id;
  int   idex;
  int   nch;
  int  layer; 
  
  int mode;

  int max_reservoir;
  int av_reservoir;
  INT64 total_reservoir;


  int sync_errors;
  INT64 sync_errors_pos[MAX_SYNC_ERRORS];      //position in milliseconds

  BOOL padding;
  BOOL scfsi;
  BOOL scalefac;
  BOOL copyright;
  BOOL original;

  BOOL vbr;
  BOOL cue;

  BOOL complete2;

  BOOL    all_read;
  int      first_frame_pos;

  int emphasis;
  int bitrate;

  BYTE final10[10];

  BOOL xing_present;
  XHEADDATA xing_header;

  BOOL vbri_present;
  VBRIDATA  vbri_header;


  //mpeg_plus

  int mpp_stream_version;
  int  mpp_stream_profile;
};



class mp3data_string
{
public:
  tstring get_header_report(const mp3data &data);
  tstring null;

  tstring path;
  tstring encoder;
  tstring length;
  tstring mode;
  tstring scalefac;
  tstring emphasis;
  tstring bitrate;
  tstring type;
  tstring fsize;
  tstring frames;
  tstring freq;
  
  tstring max_reservoir;
  tstring av_reservoir;

  tstring bad_last_frame;
  tstring vbr;
  tstring vbr_lame;
  tstring cue;
  tstring sync_errors;


  //id3v1 stuff

  tstring id3v1_title;
  tstring id3v1_album;
  tstring id3v1_artist;
  tstring id3v1_genre;
  tstring id3v1_year;
  tstring id3v1_comment;
  tstring id3v1_track;

  //mp+ stuff

  tstring mpp_stream_version;
  tstring  mpp_stream_profile;
  
  tstring quality_str;
  
  
  //Lame Tag stuff....

  tstring lame_vbr_scale;
  tstring lame_tag_revision;
  tstring lame_vbr_method;
  tstring lame_lowpass;
  tstring lame_nspsytune;
  tstring lame_nssafejoint;
  tstring lame_nogapcontinued;
  tstring lame_nogapcontinuation;
  tstring lame_athtype;
  tstring lame_abr_bitrate;
  tstring lame_noise_shaping;
  tstring lame_unwise;
  tstring lame_input_freq;
  tstring lame_stereo_mode;

  mp3data_string(){}
  int    update(const mp3data &data, BOOL monoquality);
  tstring  get_report(mp3data data, tstring version = _T(""));

private:
  void  update_lame(const mp3data &data);
  int    update_mpp(const mp3data &data,BOOL monoquality);
  void  update_id3v1(const mp3data &data);

  tstring id3trim(const char *, int nLen);
  tstring get_complete(const mp3data &data);
  tstring get_mode(int mode);
  tstring convert_time(const double secs);
  tstring guessenc(const mp3data &data);
  int    get_quality(const mp3data &data, BOOL monoquality );
  int    get_final_sum(const mp3data &data);
};


struct COLUMNDATA
{
  tstring name;
  tstring description;
  tstring group;  
  tstring alignment;
  int    offset_int;
  int    offset_string;
  int    list_col_width;
  int    html_col_width;
  BOOL  full_scan;

  COLUMNDATA(tstring n, tstring d, tstring g, int oi, int ois, int lcw, int hcw,tstring align,BOOL bfs) :
    name(n), description(d), group(g), alignment(align), offset_int(oi), offset_string(ois),
    list_col_width(lcw), html_col_width(hcw), full_scan(bfs) {}


  COLUMNDATA() : offset_int(-1),offset_string(-1), list_col_width(-1), html_col_width(-1), full_scan(TRUE) {}
};


typedef std::map<DWORD, COLUMNDATA> column_map_type;
typedef column_map_type::iterator column_iterator;
extern column_map_type g_column_map;


#define MPG_MD_STEREO       0
#define MPG_MD_JOINT_STEREO 1
#define MPG_MD_DUAL_CHANNEL 2
#define MPG_MD_MONO         3

#endif

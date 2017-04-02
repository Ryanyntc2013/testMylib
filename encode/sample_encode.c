#include "sample_comm.h"
#include "proconH264.h"
#include "debug.h"
#include "sample_encode.h"

static uint g_proconH264Fd[REAL_CHANNEL_NUM] = {0};

static int GetChnProconH264Fd( int channel )
{
    return g_proconH264Fd[channel];
}

//获取各个通道的H264的生产者消费者对象的句柄
static void InitProconH264Fd()
{
    int i;
    for( i = 0; i < REAL_CHANNEL_NUM; ++i )
    {
        g_proconH264Fd[i] = ProconH264Open( i, OPEN_WRONLY );
        if( 0 == g_proconH264Fd[i] )
        {
            SVPrint( "~~~~~~~~~~ ch(%d) ProconH264Open failed! \n", i );
        }
    }
}

static void DeinitProconH264Fd()
{
    int i;
    for( i = 0; i < REAL_CHANNEL_NUM; ++i )
    {
        ProconH264Close( g_proconH264Fd[i] );
        g_proconH264Fd[i] = 0;
    }
}

static uint GetFrameSeq( int channel )
{
    static uint seq[MAX_CHANNEL_NUM];
    return seq[channel]++;
}

HI_S32 HisiPutH264DataToBuffer(VENC_STREAM_S *pstStream)
{
    int                 channel = 0;
    uint             	i,ret = -1;
    int	            	len, index = 0;
    unsigned long     	frameLen = 0;
    uint             	proconH264Fd;
    STREAM_HEAD_T     	vFrameHead; // 视频帧头
    DATA_PIECE_T     	proDataInfo;
    H264E_NALU_TYPE_E   unal_type;
    VENC_STREAM_S *vEncStream = (VENC_STREAM_S *)pstStream;
    uchar frameType;
    struct timeval tv;
    HI_U8* pstr;
    //ShowFps( "FiStreamSendFrameToStreamBuf", channel );
//    char c;

    proconH264Fd = GetChnProconH264Fd( channel );
    if( 0 == proconH264Fd ) {
        printf("no proc ========================== \n");
        return -1;
    }

    if( NULL != vEncStream ) {
        proDataInfo.count         = index + 1;
        proDataInfo.buf[index]    = (char *)&vFrameHead;
        proDataInfo.len[index]    = sizeof(vFrameHead);
        index++;
        /////////
        proDataInfo.nalInfo.nalNum 		= vEncStream->u32PackCount;
        proDataInfo.nalInfo.nalStartOff = sizeof(vFrameHead);
        ////////
        for( i = 0; i < vEncStream->u32PackCount; ++i ) {
            ////////////////////////
            proDataInfo.nalInfo.nalSize[i] = vEncStream->pstPack[i].u32Len - vEncStream->pstPack[i].u32Offset;
            len = vEncStream->pstPack[i].u32Len  - vEncStream->pstPack[i].u32Offset;

            pstr = vEncStream->pstPack[i].pu8Addr + vEncStream->pstPack[i].u32Offset;
            unal_type = pstStream->pstPack[i].DataType.enH264EType;
            if (unal_type == H264E_NALU_SPS) {
                set_h264SeqParam(channel, 0, &pstr[4], len - 4, 0);
            } else if (unal_type == H264E_NALU_PPS) {
                set_h264PicParam(channel, 0, &pstr[4], len - 4, 0);
            }

            //////////////////////////

            if ( len > 0 ) {
                proDataInfo.count         = index + 1;
                proDataInfo.buf[index]     = (char *)pstr;
                proDataInfo.len[index]    = len;
                frameLen += len;
                index++;
            }
            if ( index >= MAX_DATA_PIECE_SIZE ) {
                break;
            }
        }


        vFrameHead.packHead.packType	    = PACK_TYPE_VIDEO;
        vFrameHead.packHead.frameHeadLen	= sizeof( vFrameHead.frameHead );

        vFrameHead.frameHead.frameLen	        = frameLen;
        vFrameHead.frameHead.frameNo	        = GetFrameSeq( channel );
        //printf("frame no is %d\n",vFrameHead.frameHead.frameNo);
//        vFrameHead.frameHead.videoStandard	    = (uchar)VencParamEasyGetVideoStandard();
        vFrameHead.frameHead.videoStandard	    = 0;
        vFrameHead.frameHead.videoResolution	= 3;
//        vFrameHead.frameHead.videoResolution	= (uchar)VencParamEasyGetResolution( channel );
        vFrameHead.frameHead.frameRate	        = 28;
//        vFrameHead.frameHead.frameRate	        = (uchar)VencParamEasyGetFramerate( channel );
        frameType = (uchar)vEncStream->pstPack[0].DataType.enH264EType;
        frameType = H264E_NALU_PSLICE == frameType ?  H264E_NALU_PSLICE : H264E_NALU_IDRSLICE;
        vFrameHead.frameHead.frameType	        = frameType;
        gettimeofday(&tv, NULL );
        vFrameHead.frameHead.sec	            = tv.tv_sec;
        vFrameHead.frameHead.usec	            = tv.tv_usec;

        ret = ProconH264Write( proconH264Fd, proDataInfo );
//        printf("write a frame to buff %d \n", ret);
    }

    return ret;
}

void encode_service_start()
{
    InitProconH264Fd();
}

void encode_service_stop()
{
    DeinitProconH264Fd();
}

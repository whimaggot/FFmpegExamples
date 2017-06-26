//
// Created by whiMaggot on 2017/6/19.
//
extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/time.h>

}
#include <jni.h>
#include "ffmpeg_decode.h"
#include <android/log.h>
#include <stdint.h>

jboolean play = false,pause = false;


extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegDecodeActivity_decode(JNIEnv *jniEnv, jobject,jstring j_input_str,jstring j_output_str){
    AVFormatContext *pFormatContext;
    int l,videoIndex;
    AVCodecContext *pCodecContext;
    AVCodec *pCodec;
    AVFrame *pFrame,*pFrameYuv;
    uint8_t *out_buffer;
    AVPacket *pPacket;
    int y_size;
    int ret,got_picture;
    struct SwsContext *img_convert_context;
    FILE *fp_yuv;
    int frame_count;
    clock_t time_start,time_finish;
    double time_duration = 0.0;
    char input_str[500] = {0};
    char output_str[500]={0};
    char info[1000]={0};
    sprintf(input_str,"%s",jniEnv->GetStringUTFChars(j_input_str,NULL));
    sprintf(output_str,"%s",jniEnv->GetStringUTFChars(j_output_str,NULL));
    av_log_set_callback(custom_log);

    av_register_all();
    avformat_network_init();
    pFormatContext = avformat_alloc_context();

    if(avformat_open_input(&pFormatContext,input_str,NULL,NULL)!=0){
        LOGD("Couldn't open input stream.\n");
        return -1;
    }
    if(avformat_find_stream_info(pFormatContext,NULL)<0){
        LOGD("Couldn't find stream information.\n");
        return -1;
    }
    videoIndex=-1;
    for(int i=0;i<pFormatContext->nb_streams;i++){
        if(pFormatContext->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoIndex=i;
            break;
        }
    }
    if(videoIndex==-1){
        LOGD("Couldn't find a video stream.\n");
        return -1;
    }
    pCodecContext = pFormatContext->streams[videoIndex]->codec;
    pCodec = avcodec_find_decoder(pCodecContext->codec_id);
    if(pCodec==NULL){
        LOGD("Couldn't find Codec.\n");
        return -1;
    }
    if(avcodec_open2(pCodecContext,pCodec,NULL)<0){
        LOGD("Couldn't open codec.\n");
        return -1;
    }
    pFrame = av_frame_alloc();
    pFrameYuv = av_frame_alloc();
    out_buffer = (unsigned char *) av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecContext->width, pCodecContext->height, 1));
    av_image_fill_arrays(pFrameYuv->data,pFrameYuv->linesize,out_buffer,AV_PIX_FMT_YUV420P,pCodecContext->width,pCodecContext->height,1);
    pPacket = (AVPacket *) av_malloc(sizeof(AVPacket));
    img_convert_context = sws_getContext(pCodecContext->width,pCodecContext->height,pCodecContext->pix_fmt,pCodecContext->width,pCodecContext->height,AV_PIX_FMT_YUV420P,SWS_BICUBIC,NULL,NULL,NULL);

    sprintf(info,"[Input     ]%s\n",input_str);
    sprintf(info,"%s[Output    ]%s\n",output_str);
    sprintf(info,"%s[Format    ]%s\n",pFormatContext->iformat->name);
    sprintf(info,"%s[Codec    ]%s\n",pCodecContext->codec->name);
    sprintf(info,"%s[Resolution]%dx%d\n",info, pCodecContext->width,pCodecContext->height);

    fp_yuv = fopen(output_str,"wb+");
    if(fp_yuv==NULL){
        LOGD("Cannot open output file.\n");
        return -1;
    }
    frame_count = 0;
    time_start = clock();
    while (av_read_frame(pFormatContext,pPacket)>=0){
        if(pPacket->stream_index==videoIndex){
            ret = avcodec_decode_video2(pCodecContext,pFrame,&got_picture,pPacket);

            if(ret<0){
                LOGD("Decode Error\n");
                return -1;
            }
            if(got_picture){
                sws_scale(img_convert_context, (const uint8_t *const *) pFrame->data, pFrame->linesize, 0, pCodecContext->height, pFrameYuv->data, pFrameYuv->linesize);
                y_size = pCodecContext->width*pCodecContext->height;
                fwrite(pFrame->data[0],1,y_size,fp_yuv);//Y
                fwrite(pFrame->data[1],1,y_size,fp_yuv);//U
                fwrite(pFrame->data[2],1,y_size,fp_yuv);//V

                char pict_type_str[10]={0};
                switch(pFrame->pict_type){
                    case AV_PICTURE_TYPE_I:
                        sprintf(pict_type_str,"I");
                        break;
                    case AV_PICTURE_TYPE_P:
                        sprintf(pict_type_str,"P");
                        break;
                    case AV_PICTURE_TYPE_B:
                        sprintf(pict_type_str,"B");
                        break;
                    default:
                        sprintf(pict_type_str,"other");
                        break;
                }
                LOGD("Frame Index: %5d. Type:%s",frame_count,pict_type_str);
                frame_count++;

            }
        }
        av_free_packet(pPacket);
    }
    while (l){
        ret = avcodec_decode_video2(pCodecContext,pFrame,&got_picture,pPacket);
        if(ret<0){
            break;
        }
        if(!got_picture){
            break;
        }
        sws_scale(img_convert_context, (const uint8_t *const *) pFrame->data, pFrame->linesize, 0, pCodecContext->height, pFrameYuv->data, pFrameYuv->linesize);
        int y_size= pCodecContext->width*pCodecContext->height;
        fwrite(pFrame->data[0],1,y_size,fp_yuv);//Y
        fwrite(pFrame->data[1],1,y_size,fp_yuv);//U
        fwrite(pFrame->data[2],1,y_size,fp_yuv);//V
        char pict_type_str[10]={0};
        switch(pFrame->pict_type){
            case AV_PICTURE_TYPE_I:
                sprintf(pict_type_str,"I");
                break;
            case AV_PICTURE_TYPE_P:
                sprintf(pict_type_str,"P");
                break;
            case AV_PICTURE_TYPE_B:
                sprintf(pict_type_str,"B");
                break;
            default:
                sprintf(pict_type_str,"other");
                break;
        }
        LOGD("Frame Index: %5d. Type:%s",frame_count,pict_type_str);
        frame_count++;
    }

    time_finish = clock();
    time_duration = time_finish-time_start;
    sprintf(info, "%s[Time      ]%fms\n",info,time_duration);
    sprintf(info, "%s[Count     ]%d\n",info,frame_count);
    sws_freeContext(img_convert_context);
    fclose(fp_yuv);
    av_frame_free(&pFrame);
    av_frame_free(&pFrameYuv);
    avcodec_close(pCodecContext);
    avformat_close_input(&pFormatContext);
    return 0;

}
extern "C" void custom_log(void *ptr,int level,const char *fmt,va_list vl){
    FILE *fp = fopen("/storage/emulated/0/av_log.text","a+");
    if(fp){
        vfprintf(fp,fmt,vl);
        fflush(fp);
        fclose(fp);
    }
}
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_rtmp(JNIEnv *jniEnv,jobject obj,jstring j_input_str,jstring j_output_str){
    LOGE("开始准备播放");
    AVOutputFormat *ofmt = NULL;
    AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
    AVPacket pkt;

    int ret, i;
    char input_str[500]={0};
    char output_str[500]={0};
    char info[1000]={0};
    int frame_index=0;
    int videoindex=-1;

    int64_t start_time=av_gettime();
    sprintf(input_str,"%s",jniEnv->GetStringUTFChars(j_input_str, NULL));
    sprintf(output_str,"%s",jniEnv->GetStringUTFChars(j_output_str, NULL));

    //input_str  = "cuc_ieschool.flv";
    //output_str = "rtmp://localhost/publishlive/livestream";
    //output_str = "rtp://233.233.233.233:6666";

    //FFmpeg av_log() callback
    av_log_set_callback(custom_log);

    av_register_all();
    //Network
    avformat_network_init();

    //Input
    if ((ret = avformat_open_input(&ifmt_ctx, input_str, 0, 0)) < 0) {
        LOGE( "Could not open input file.");
        goto end;
    }
    LOGE("打开输入文件成功");
    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
        LOGE( "Failed to retrieve input stream information");
        goto end;
    }

    for(i=0; i<ifmt_ctx->nb_streams; i++)
        if(ifmt_ctx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoindex=i;
            break;
        }
    //Output
    avformat_alloc_output_context2(&ofmt_ctx, NULL, "flv",output_str); //RTMP
    //avformat_alloc_output_context2(&ofmt_ctx, NULL, "mpegts", output_str);//UDP
    LOGE("创建输出成功");
    if (!ofmt_ctx) {
        LOGE( "Could not create output context\n");
        ret = AVERROR_UNKNOWN;
        goto end;
    }
    ofmt = ofmt_ctx->oformat;
    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        //Create output AVStream according to input AVStream
        AVStream *in_stream = ifmt_ctx->streams[i];
        AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
        if (!out_stream) {
            LOGE( "Failed allocating output stream\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        //Copy the settings of AVCodecContext
        ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
        if (ret < 0) {
            LOGE( "Failed to copy context from input to output stream codec context\n");
            goto end;
        }
        out_stream->codec->codec_tag = 0;
        if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
            out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }
    LOGE("解码成功");
    //Open output URL
    if (!(ofmt->flags & AVFMT_NOFILE)) {
        ret = avio_open(&ofmt_ctx->pb, output_str, AVIO_FLAG_WRITE);
        if (ret < 0) {
            LOGE( "Could not open output URL '%s'", output_str);
            goto end;
        }
    }
    //Write file header
    ret = avformat_write_header(ofmt_ctx, NULL);
    if (ret < 0) {
        LOGE( "Error occurred when opening output URL\n");
        goto end;
    }
    LOGE("连接推流服务器成功");

    LOGE("开始推流");
    while (1) {
        if(pause== true){
            play = false;
            continue;
        }
        play = true;
        AVStream *in_stream, *out_stream;
        //Get an AVPacket
        ret = av_read_frame(ifmt_ctx, &pkt);
        if (ret < 0)
            break;
        //FIX：No PTS (Example: Raw H.264)
        //Simple Write PTS
        if(pkt.pts==AV_NOPTS_VALUE){
            //Write PTS
            AVRational time_base1=ifmt_ctx->streams[videoindex]->time_base;
            //Duration between 2 frames (us)
            int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(ifmt_ctx->streams[videoindex]->r_frame_rate);
            //Parameters
            pkt.pts=(double)(frame_index*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
            pkt.dts=pkt.pts;
            pkt.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
        }
        //Important:Delay
        if(pkt.stream_index==videoindex){
            AVRational time_base=ifmt_ctx->streams[videoindex]->time_base;
            AVRational time_base_q={1,AV_TIME_BASE};
            int64_t pts_time = av_rescale_q(pkt.dts, time_base, time_base_q);
            int64_t now_time = av_gettime() - start_time;
            if (pts_time > now_time)
                av_usleep(pts_time - now_time);

        }

        in_stream  = ifmt_ctx->streams[pkt.stream_index];
        out_stream = ofmt_ctx->streams[pkt.stream_index];
        /* copy packet */
        //Convert PTS/DTS
        pkt.pts = av_rescale_q(pkt.pts, in_stream->time_base, out_stream->time_base);
        pkt.dts = av_rescale_q(pkt.dts, in_stream->time_base, out_stream->time_base);
        pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
        pkt.pos = -1;
        //Print to Screen
        if(pkt.stream_index==videoindex){
            LOGE("Send %8d video frames to output URL\n",frame_index);
            frame_index++;
        }
        //ret = av_write_frame(ofmt_ctx, &pkt);
        ret = av_interleaved_write_frame(ofmt_ctx, &pkt);

        if (ret < 0) {
            LOGE( "Error muxing packet\n");
            break;
        }
        av_free_packet(&pkt);

    }
    //Write file trailer
    av_write_trailer(ofmt_ctx);
    end:
    avformat_close_input(&ifmt_ctx);
    /* close output */
    if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
        avio_close(ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);
    if (ret < 0 && ret != AVERROR_EOF) {
        LOGE( "Error occurred.\n");
        return -1;
    }
    return 0;
}
extern "C" jboolean Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_pause(JNIEnv *jniEnv,jobject obj,jboolean data){
    pause = data;
    return 1;
}
extern "C" jboolean Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_isPlay(JNIEnv *jniEnv,jobject obj){
    return play;
}
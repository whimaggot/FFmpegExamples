//
// Created by whiMaggot on 2017/6/14.
//
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avio.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
}

#include "ffmpeg_info.h"



extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_urlprotocolinfo(JNIEnv *jniEnv,jobject){
    char info[4000]={0};
    avcodec_register_all();
    struct URLProtocol *pup = NULL;
    struct URLProtocol **p_temp= &pup;
    avio_enum_protocols((void **) p_temp, 0);
    while (*p_temp !=NULL){
        sprintf(info,"%s[In ][%10s]\n",info,avio_enum_protocols((void **) p_temp, 0));
    }
    pup = NULL;
    avio_enum_protocols((void **) p_temp, 1);
    while (*p_temp!=NULL){
        sprintf(info,"%s[Out ][%10s]\n",info,avio_enum_protocols((void **) p_temp, 1));
    }
    return jniEnv->NewStringUTF(info);

}

extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avformatinfo(JNIEnv *jniEnv,jobject){
    char info[40000]={0};
    av_register_all();
    AVInputFormat *informat_temp = av_iformat_next(NULL);
    AVOutputFormat *outformat_temp = av_oformat_next(NULL);
    while (informat_temp!=NULL){
        sprintf(info,"%s[In ][%10s]\n",info,informat_temp->name);
        informat_temp = informat_temp->next;
    }
    while (outformat_temp!=NULL){
        sprintf(info,"%s[Out ][%10s]\n",info,outformat_temp->name);
        outformat_temp = outformat_temp->next;
    }

    return jniEnv->NewStringUTF(info);
}

extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avcodecinfo(JNIEnv *jniEnv,jobject){
    char info[40000] = { 0 };

    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        }
        else{
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);
        c_temp=c_temp->next;
    }
    return jniEnv->NewStringUTF(info);

}
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avfilterinfo(JNIEnv *jniEnv,jobject){

    char info[40000] = { 0 };
    avfilter_register_all();
    AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);
    while (f_temp != NULL){
        sprintf(info, "%s[%10s]\n", info, f_temp->name);
    }

    return jniEnv->NewStringUTF(info);
}
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_configurationinfo(JNIEnv *jniEnv,jobject){
    char info[10000] = {0};
    av_register_all();
    sprintf(info,"%s\n",avcodec_configuration());
    return jniEnv->NewStringUTF(info);
}



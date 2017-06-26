//
// Created by whiMaggot on 2017/6/26.
//

#include <stdio.h>
extern "C" {
    #include <libavutil/log.h>
    #include <ffmpeg.h>
}
#include "ffmpeg_core.h"

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegCoreActivity_core(JNIEnv *jniEnv,jobject obj,jint cmdnum,jobjectArray cmdline){
    av_log_set_callback(custom_log);

    int argc = cmdnum;
    char ** argv = (char **) malloc(sizeof(char*) * argc);

    int i=0;
    for(i=0;i<argc;i++){
        jstring  string = (jstring) jniEnv->GetObjectArrayElement(cmdline, i);
        const char *tmp = jniEnv->GetStringUTFChars(string,0);
        argv[i] = (char*)malloc(sizeof(char)*1024);
        strcpy(argv[i],tmp);
    }
    int result = ffmpegmain(argc,argv);
    for(int i=0;i<argc;i++){
        free(argv[i]);
    }
    free(argv);
    return result;

}
void custom_log(void *ptr,int level, const  char *fmt,va_list vl){
    FILE *fp = fopen("/storage/emulated/0/av_log.txt","a+");
    if(fp){
        vfprintf(fp,fmt,vl);
        fflush(fp);
        fclose(fp);
    }
}


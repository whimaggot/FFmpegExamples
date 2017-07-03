//
// Created by whiMaggot on 2017/6/27.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <android/log.h>
#include "ffmpeg_tool.h"

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV420(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl, NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *fp_y = fopen("/sdcard/output_420_y.yuv","wb+");
    FILE *fp_u = fopen("/sdcard/output_420_u.yuv","wb+");
    FILE *fp_v = fopen("/sdcard/output_420_v.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        fwrite(pic,1,w*h,fp_y);
        fwrite(pic+w*h,1,w*h/4,fp_u);
        fwrite(pic+w*h*5/4,1,w*h/4,fp_v);
    }
    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);
    return 0;
}

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV444(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *fp_y = fopen("/sdcard/output_444_y.yuv","wb+");
    FILE *fp_u = fopen("/sdcard/output_444_u.yuv","wb+");
    FILE *fp_v = fopen("/sdcard/output_444_v.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3,fp);
        fwrite(pic,1,w*h,fp_y);
        fwrite(pic+w*h,1,w*h,fp_u);
        fwrite(pic+w*h*2,1,w*h,fp_v);
    }
    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);

    return 0;

}

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420Gray(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);

    FILE *fp = fopen(url,"rb+");
    FILE *op = fopen("/sdcard/output_420_gray.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        memset(pic+w*h,128,w*h/2);
        fwrite(pic,1,w*h*3/2,op);
    }
    free(pic);
    fclose(fp);
    fclose(op);

    return 0;
}

extern "C" jint  Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420HalfY(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const  char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *op = fopen("/sdcard/output_420_halfY.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        for(int j=0;j<w*h;j++){
            unsigned char temp = pic[j]/2;
            pic[j] = temp;
        }
        fwrite(pic,1,w*h*3/2,op);
    }
    free(pic);
    fclose(fp);
    fclose(op);

    return 0;
}

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420GrayBar(JNIEnv *jniEnv,jobject obj,jint w,jint h,jint yMin,jint yMax,jint barNum,jstring outputUrl){
    const char *url = jniEnv->GetStringUTFChars(outputUrl,NULL);
    int barWidth;
    float lum_inc;
    unsigned char  lum_temp;
    int uvWidth,uvHeight;
    FILE *fp = NULL;
    unsigned char *data_y = NULL;
    unsigned char *data_u = NULL;
    unsigned char *data_v = NULL;
    int t = 0,i=0,j=0;

    barWidth = w/barNum;

    lum_inc = (yMax-yMin)/(barNum-1);

    uvWidth = w/2;

    uvHeight = h/2;

    data_y = (unsigned char *) malloc(w * h);
    data_u = (unsigned char *) malloc(uvWidth * uvHeight);
    data_v = (unsigned char *) malloc(uvWidth * uvHeight);

    if((fp = fopen(url,"wb+"))==NULL){
        LOGE("Error: Cannot create file!");
        return -1;
    }

    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            t = j/barWidth;
            lum_temp = yMin+(t*lum_inc);
            data_y[i*w+j] = lum_temp;
        }
    }
    for (i = 0; i < uvHeight; ++i) {
        for (j = 0; j < uvWidth; ++j) {
            data_u[i*uvWidth+j] = 128;
        }
    }
    for (i = 0; i < uvHeight; ++i) {
        for (j = 0; j < uvWidth; ++j) {
            data_v[i*uvWidth+j] = 128;
        }
    }

    fwrite(data_y,w*h,1,fp);
    fwrite(data_u,uvWidth*uvHeight,1,fp);
    fwrite(data_v,uvWidth*uvHeight,1,fp);
    free(data_y);
    free(data_u);
    free(data_v);
    fclose(fp);

    return 0;

}
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltPCM16(JNIEnv *jniEnv,jobject obj,jstring inputUrl){
    const char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);

    FILE *fp = fopen(url,"rb+");
    FILE *lf = fopen("/sdcard/output_16_pcm_left.pcm","wb+");
    FILE *rf = fopen("/sdcard/output_16_pcm_right.pcm","wb+");

    unsigned char *sample  = (unsigned char *) malloc(4);

    while (!feof(fp)){
        fread(sample,1,4,fp);
        fwrite(sample,1,2,lf);
        fwrite(sample+2,1,3,rf);
    }
    free(sample);
    fclose(fp);
    fclose(lf);
    fclose(rf);

    return 0;

}



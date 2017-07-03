package com.whimaggot.os.ffmpegtest;

import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import com.whimaggot.os.ffmpegtest.utils.ToastHelper;

/**
 * Created by whiMaggot on 2017/6/27.
 */

public class FFmpegToolsActivity extends AppCompatActivity {
    private EditText etInput;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tool);
        etInput = (EditText) findViewById(R.id.et_input);
    }




    /**
     * 把一个YUV420文件按Y,U,V切割成三个文件
     * */
    public void onSpiltYUV420(View pView){
        String folderUrl= Environment.getExternalStorageDirectory().getPath();
        String inputUrl = folderUrl+"/"+etInput.getText().toString();
        int ret= spiltYUV420(inputUrl,640,360,20);
        if(ret==0){
            ToastHelper.tips(getApplicationContext(),"成功");
        }else{
            ToastHelper.tips(getApplicationContext(),"失败");
        }
    }


    /**
     * 把一个YUV444文件按Y,U,V切割成三个文件
     * */
    public void onSpiltYUV444(View pView){
        String folderUrl= Environment.getExternalStorageDirectory().getPath();
        String inputUrl = folderUrl+"/"+etInput.getText().toString();
        int ret= spiltYUV444(inputUrl,640,360,20);
        if(ret==0){
            ToastHelper.tips(getApplicationContext(),"成功");
        }else{
            ToastHelper.tips(getApplicationContext(),"失败");
        }
    }

    /**
     * 将一个YUV文件变灰
     * */
    public void onYUV420Gray(View pView){
        String folderUrl= Environment.getExternalStorageDirectory().getPath();
        String inputUrl = folderUrl+"/"+etInput.getText().toString();
        int ret= yuv420Gray(inputUrl,640,360,20);
        if(ret==0){
            ToastHelper.tips(getApplicationContext(),"成功");
        }else{
            ToastHelper.tips(getApplicationContext(),"失败");
        }
    }

    public void onYUV420HalfY(View pView){
        String folderUrl= Environment.getExternalStorageDirectory().getPath();
        String inputUrl = folderUrl+"/"+etInput.getText().toString();
        int ret= yuv420HalfY(inputUrl,640,360,20);
        if(ret==0){
            ToastHelper.tips(getApplicationContext(),"成功");
        }else{
            ToastHelper.tips(getApplicationContext(),"失败");
        }
    }

    public void onYUV420GrayBar(View pView){
        int ret= yuv420GrayBar(640,360,0,255,10,"/sdcard/output_420_gray_bar.yuv");
        if(ret==0){
            ToastHelper.tips(getApplicationContext(),"成功");
        }else{
            ToastHelper.tips(getApplicationContext(),"失败");
        }
    }


    /**
     * params:url 本地文件地址，w 视频宽度，h 视频高度，num 视频帧数
     * */
    public native int spiltYUV420(String url,int w,int h,int num);
    public native int spiltYUV444(String url,int w,int h,int num);
    public native int yuv420Gray(String url,int w,int h,int num);
    public native int yuv420HalfY(String url,int w,int h,int num);
    public native int yuv420GrayBar(int w,int h,int yMin,int yMax,int barNum,String outputUrl);

    static {
        System.loadLibrary("ffmpeg-info");
    }
}

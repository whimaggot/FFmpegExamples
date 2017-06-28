package com.whimaggot.os.ffmpegtest;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import com.whimaggot.os.ffmpegtest.utils.ToastHelper;

import java.io.File;

/**
 * Created by whiMaggot on 2017/6/26.
 */

public class FFmpegCoreActivity extends AppCompatActivity {
    private EditText etCommand;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_core);
        etCommand = (EditText) findViewById(R.id.et_input);

    }


    /**
     * 执行FFmpeg 命令
     * */
    public void onCore(View pView){
        String[] command = etCommand.getText().toString().split(" ");
        int line = command.length;
        String output = command[command.length-1];
        File outputFile = new File(output);
        if(outputFile!=null && outputFile.exists()){
            outputFile.delete();
        }
        String input = command[command.length-2];
        File inputFile = new File(input);
        if(inputFile==null || !inputFile.exists()){
            ToastHelper.tips(getApplicationContext(),"待文件不存在");
            return;
        }
        int result = core(line, command);

        if(result<0){
            ToastHelper.tips(getApplicationContext(),"转码失败");
        }else{
            ToastHelper.tips(getApplicationContext(),"转码成功");
        }
    }




    public native int core(int argc,String[] argv);
    static {
        System.loadLibrary("ffmpeg-decode");
    }
}

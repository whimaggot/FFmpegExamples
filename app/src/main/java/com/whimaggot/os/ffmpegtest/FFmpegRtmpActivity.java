package com.whimaggot.os.ffmpegtest;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.v4.content.PermissionChecker;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.whimaggot.os.ffmpegtest.utils.ToastHelper;

import static android.R.attr.targetSdkVersion;

/**
 * Created by whiMaggot on 2017/6/26.
 */

public class FFmpegRtmpActivity extends AppCompatActivity {
    private EditText etInput;
    private EditText etOutput;
    private Button btnState;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rtmp);
        etInput = (EditText) findViewById(R.id.et_input);
        etOutput = (EditText) findViewById(R.id.tv_output);
        btnState = (Button) findViewById(R.id.btn_state);

    }



    @Override
    protected void onResume() {
        super.onResume();
        if(!selfPermissionGranted(Manifest.permission.READ_EXTERNAL_STORAGE)){
            if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M) {
                requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
            }
        }
        if(!selfPermissionGranted(Manifest.permission.WRITE_EXTERNAL_STORAGE)){
            if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
            }
        }
    }

    public boolean selfPermissionGranted(String permission) {
        // For Android < Android M, self permissions are always granted.
        boolean result = true;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {

            if (targetSdkVersion >= Build.VERSION_CODES.M) {
                // targetSdkVersion >= Android M, we can
                // use Context#checkSelfPermission
                result = checkSelfPermission(permission)
                        == PackageManager.PERMISSION_GRANTED;
            } else {
                // targetSdkVersion < Android M, we have to use PermissionChecker
                result = PermissionChecker.checkSelfPermission(this, permission)
                        == PermissionChecker.PERMISSION_GRANTED;
            }
        }

        return result;
    }

    /**
     * 推流，两个Edittext控制分别是输入源跟推流至的地址
     * */
    public void onRtmp(View pView){
        String folderUrl= Environment.getExternalStorageDirectory().getPath();

        String input=etInput.getText().toString();
        final String inputUrl=folderUrl+"/"+input;
        new Thread(new Runnable() {
            @Override
            public void run() {
                Looper.prepare();
                ToastHelper.tips(getApplicationContext(),"准备播放中");
                rtmp(inputUrl,etOutput.getText().toString());
                ToastHelper.tips(getApplicationContext(),"播放结束");
            }
        }).start();
        btnState.setText("pause");
        btnState.setVisibility(View.VISIBLE);

    }




    public void play(View pView){
        if(isPlay()){
            pause(true);
            btnState.setText("play");

        }else{
            pause(false);
            btnState.setText("pause");
        }
    }

    public native int rtmp(String input,String output);
    static {
        System.loadLibrary("ffmpeg-decode");
    }
    public native boolean pause(boolean data);

    public native boolean isPlay();
}

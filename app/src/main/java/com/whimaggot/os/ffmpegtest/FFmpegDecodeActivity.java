package com.whimaggot.os.ffmpegtest;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.content.PermissionChecker;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import com.whimaggot.os.ffmpegtest.utils.ToastHelper;

import static android.R.attr.targetSdkVersion;

/**
 * Created by whiMaggot on 2017/6/19.
 */

public class FFmpegDecodeActivity extends AppCompatActivity{
    private EditText etInput;
    private EditText etOutput;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_decode);
        etInput = (EditText) findViewById(R.id.et_input);
        etOutput = (EditText) findViewById(R.id.tv_output);
    }

    /**
     * 将一个视频转换成YUV420文件，体积会很大
     * */
    public void onDecode(View pView){
        String folderUrl=Environment.getExternalStorageDirectory().getPath();

        String input=etInput.getText().toString();
        String inputUrl=folderUrl+"/"+input;

        String outputUrl=inputUrl.substring(0,inputUrl.length()-3)+"yuv";
        etOutput.setText(outputUrl);
        int result = decode(inputUrl,outputUrl);
        if(result!=0){
            ToastHelper.tips(getApplicationContext(),"转码失败");
        }else{
            ToastHelper.tips(getApplicationContext(),"转码成功");
        }
    }


    public native int decode(String input,String output);

    static {
        System.loadLibrary("ffmpeg-decode");
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
}

package com.whimaggot.os.ffmpegtest;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.content.PermissionChecker;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

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

    public void onDecode(View pView){
        String folderurl=Environment.getExternalStorageDirectory().getPath();

        String input=etInput.getText().toString();
        String inputurl=folderurl+"/"+input;

        String outputurl=inputurl.substring(0,inputurl.length()-3)+"yuv";
        etOutput.setText(outputurl);
        Log.i("ffmpeg-decode",inputurl);
        Log.i("ffmpeg-decode",outputurl);
        int result = decode(inputurl,outputurl);
        if(result!=0){
            Toast.makeText(this,"转码失败",Toast.LENGTH_SHORT).show();
        }else{
            Toast.makeText(this,"转码成功", Toast.LENGTH_SHORT).show();
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

package com.whimaggot.os.ffmpegtest;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
    }
    public void info(View pView){
        startActivity(FFmpegInfoActivity.class);
    }
    public void decode(View pView){
        startActivity(FFmpegDecodeActivity.class);
    }
    public void rtmp(View pView){
        startActivity(FFmpegRtmpActivity.class);
    }

    public void tool(View pView){
        startActivity(FFmpegToolsActivity.class);
    }

    public void core(View pView){
        startActivity(FFmpegCoreActivity.class);
    }

    public void startActivity(Class<?> pClass){
        Intent lIntent = new Intent(MainActivity.this,pClass);
        startActivity(lIntent);
    }

}

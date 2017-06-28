package com.whimaggot.os.ffmpegtest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

/**
 * Created by whiMaggot on 2017/6/19.
 */

public class FFmpegInfoActivity extends AppCompatActivity {
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_info);

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
    }
    public void urlProtocol(View view){
        tv.setText(urlprotocolinfo());
    }
    public void avformat(View view){
        tv.setText(avformatinfo());
    }
    public void avcodec(View pView){
        tv.setText(avcodecinfo());
    }
    public void avfilter(View pView){
        tv.setText(avfilterinfo());
    }
    public void configuration(View pView){
        tv.setText(configurationinfo());
    }


    /**
     *读取FFmpeg配置信息
     * */
    public native String urlprotocolinfo();
    public native String avformatinfo();

    public native String avfilterinfo();
    public native String configurationinfo();

    public native String avcodecinfo();
    static {
        System.loadLibrary("ffmpeg-info");
    }
}

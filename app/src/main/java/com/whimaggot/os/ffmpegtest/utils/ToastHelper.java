package com.whimaggot.os.ffmpegtest.utils;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by whiMaggot on 2017/6/28.
 */

public  class ToastHelper {
    public static void tips(Context pContext,String tips){
        Toast.makeText(pContext,tips,Toast.LENGTH_SHORT).show();
    }

}

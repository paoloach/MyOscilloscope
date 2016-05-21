package com.achdjian.MyOscilloscope.myoscilloscope.customView;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.os.Handler;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

import com.achdjian.MyOscilloscope.myoscilloscope.Data;

/**
 * Created by paolo on 22/03/16.
 */
public class GraphView extends View implements Data.Subscriber{
    private static String TAG=GraphView.class.getName();
    private long previousUpdate=0;
    private Paint line = new Paint(Paint.ANTI_ALIAS_FLAG);

    public GraphView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    public GraphView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        line.setColor(Color.argb(0xFF,0,0,0));
    }

    @Override
    protected void onMeasure (int widthMeasureSpec, int heightMeasureSpec) {
        setMeasuredDimension(measureWidth(widthMeasureSpec), measureHeight(heightMeasureSpec));
    }

    private int measureHeight(int heightMeasureSpec) {
        return resolveSizeAndState(1000, heightMeasureSpec,0);
    }

    private int measureWidth(int widthMeasureSpec) {
        return resolveSizeAndState(1000, widthMeasureSpec,0);
    }

    @Override
    protected void onDraw(Canvas canvas){
        Data data = Data.getInstance();
        int bufferSize = data.buffer.size();
        if (bufferSize>0) {
            float width = getWidth() - getPaddingLeft() - getPaddingRight();

            float height = getHeight() - getPaddingTop() - getPaddingBottom();
            float dx = width / bufferSize;
            float zoomY = height/255;
            float x;
            float previousX=0;
            float previousY=0;
            float y;
            data.lock.lock();
            try {
                for (Integer value : data.buffer) {
                    y = value * zoomY;
                    x = previousX + dx;
                    canvas.drawLine(previousX, previousY, x, y, line);
                    previousX = x;
                    previousY = y;
                }
            } finally {
                data.lock.unlock();
            }
        }
    }

    @Override
    public void newData() {
        long now = System.currentTimeMillis();
        if (now-previousUpdate > 1000) {
            previousUpdate=now;
            Handler handler = getHandler();
            if (handler != null) {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        invalidate();
                    }
                });
            }
        }
    }
}

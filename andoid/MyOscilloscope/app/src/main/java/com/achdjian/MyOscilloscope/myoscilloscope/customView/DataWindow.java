package com.achdjian.MyOscilloscope.myoscilloscope.customView;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

import com.achdjian.MyOscilloscope.myoscilloscope.Data;
import com.achdjian.MyOscilloscope.myoscilloscope.R;
import com.google.common.collect.EvictingQueue;

/**
 * Created by paolo on 24/03/16.
 */
class DataWindow extends View implements Data.Subscriber {
    private static final String TAG = DataWindow.class.getName();
    private static final int BOTTOM_PAD = 10;
    int lineHeightHidden;
    int lineHeightVisible;
    private Paint paintLineHidden;
    private Paint paintLineVisible;
    private Paint paintText;
    private Rect bound0;
    private Rect boundMax;
    private double perc;

    public DataWindow(Context context) {
        super(context);
        init();
    }

    public DataWindow(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public DataWindow(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        perc = 1;

        lineHeightHidden = getResources().getDimensionPixelSize(R.dimen.line_hidden);
        lineHeightVisible = getResources().getDimensionPixelSize(R.dimen.line_visible);

        paintLineHidden = new Paint(Paint.ANTI_ALIAS_FLAG);
        paintLineHidden.setColor(Color.argb(0xFF, 32, 32, 32));
        paintLineHidden.setStrokeWidth(lineHeightHidden);
        paintLineHidden.setStrokeCap(Paint.Cap.BUTT);

        paintLineVisible = new Paint(Paint.ANTI_ALIAS_FLAG);
        paintLineVisible.setColor(Color.argb(0xFF, 0, 0, 0));
        paintLineVisible.setStrokeWidth(lineHeightVisible);
        paintLineVisible.setStrokeCap(Paint.Cap.BUTT);


        paintText = new Paint(Paint.ANTI_ALIAS_FLAG);
        paintText.setColor(Color.argb(0xFF, 0, 0, 0));
        paintText.setTextSize(getResources().getDimensionPixelSize(R.dimen.text_size));

        bound0 = new Rect();
        paintText.getTextBounds("0", 0, 1, bound0);

        boundMax = new Rect();
        paintText.getTextBounds("100000", 0, 6, boundMax);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        setMeasuredDimension(measureWidth(widthMeasureSpec), measureHeight(heightMeasureSpec));
    }

    private int measureHeight(int heightMeasureSpec) {
        int desiderateMeasure = Math.max(bound0.height(), 30);
        return resolveSizeAndState(desiderateMeasure, heightMeasureSpec, 0);
    }

    private int measureWidth(int widthMeasureSpec) {
        return resolveSizeAndState(10000, widthMeasureSpec, 0);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        int width = getWidth() - getPaddingLeft() - getPaddingRight();
        int height = getHeight() - getPaddingTop() - getPaddingBottom();
        int lineXStart = bound0.width() + 1;
        int lineXEnd = width - boundMax.width() - 1;
        int lineXVisibleEnd = (int) (lineXStart+(lineXEnd-lineXStart)*perc);
        int lineY = height - BOTTOM_PAD - lineHeightHidden / 2;
        canvas.drawLine(lineXStart, lineY, lineXVisibleEnd, lineY, paintLineVisible);
        canvas.drawLine(lineXVisibleEnd+1, lineY, lineXEnd, lineY, paintLineHidden);
        canvas.drawText("0", 0, height, paintText);
        EvictingQueue<Integer> buffer = Data.getInstance().buffer;
        String max = Integer.toString(buffer.size());
        canvas.drawText(max, lineXEnd + 1, height, paintText);
    }


    @Override
    public void newData() {
        getHandler().post(new Runnable() {
            @Override
            public void run() {
                Log.d(TAG, "invalidate");
                invalidate();
            }
        });
    }
}
package com.achdjian.MyOscilloscope.myoscilloscope.runnable;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

import com.achdjian.MyOscilloscope.myoscilloscope.Constants;
import com.achdjian.MyOscilloscope.myoscilloscope.Data;
import com.achdjian.MyOscilloscope.myoscilloscope.MainActivity;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

/**
 * Created by paolo on 20/03/16.
 */
public class Connection implements Runnable {
        private static final String TAG = Connection.class.getName();
    final private MainActivity mainActivity;
    private Socket clientSocket = null;
    InputStream inputStream;

    public Connection(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }

    @Override
    public void run() {
        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(mainActivity);
        Data data = Data.getInstance();
        byte tmpData[] = new byte[1024];
        inputStream=null;
        while (true) {
            if (inputStream == null) {
                try {
                    String address = settings.getString(Constants.SERVER_ADDRESS, "");
                    Log.d(TAG, "try to connect at " + address);
                    clientSocket = new Socket(address, Constants.SERVER_PORT);
                    inputStream = clientSocket.getInputStream();
                    mainActivity.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            mainActivity.enable();
                        }
                    });
                } catch (IOException e) {
                    closeSocket();
                    mainActivity.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            mainActivity.disable();
                        }
                    });
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e2) {
                    }
                }
            }

            if (inputStream != null) {
                try {
                    int r = inputStream.read(tmpData);
                    if (r >= 0) {
                        data.lock.lock();
                        try {
                            data.add(tmpData);
                        } finally {
                            data.lock.unlock();
                        }
                        Log.d(TAG, "Read 1024 bytes");
                    } else {
                        closeSocket();
                    }
                } catch (IOException e) {
                    closeSocket();
                }
            }
        }
    }

    private void closeSocket() {
        try {
            if (clientSocket != null)
                clientSocket.close();
        } catch (Exception e1) {

        } finally {
            clientSocket=null;
            inputStream=null;
        }
    }
}

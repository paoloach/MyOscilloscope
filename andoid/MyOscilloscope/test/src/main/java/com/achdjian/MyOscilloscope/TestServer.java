package com.achdjian.MyOscilloscope;

import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TestServer {
    public static void main(String argv[]) throws Exception {
        ServerSocket welcomeSocket = new ServerSocket(3456);
        byte data[] = new byte[1024];
        for (int i = 0; i < 1024; i++) {
            data[i] = (byte) i;
        }
        while(true) {
            Socket connectionSocket = welcomeSocket.accept();
            OutputStream outputStream = connectionSocket.getOutputStream();

            for(int i=0; i < 20; i++) {
                System.out.println("send 1024 bytes");
                outputStream.write(data);
                Thread.sleep(100);
            }

        }
    }
}
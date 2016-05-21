package com.achdjian.MyOscilloscope.myoscilloscope;

import com.google.common.collect.EvictingQueue;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by paolo on 22/03/16.
 */
public class Data {
    public void removeSubscriber(Subscriber subscriber) {
        subscribers.remove(subscriber);
    }

    public interface Subscriber {
        void newData();
    }
    private static Data instance;
    public EvictingQueue<Integer> buffer = EvictingQueue.create(100000);
    public Lock lock = new ReentrantLock();
    public List<Subscriber> subscribers = new ArrayList<>();

    public synchronized void add(byte[] data){
        for (byte a : data) {
            if (a>=0)
                buffer.add((int) a);
            else
                buffer.add(256+a);
        }
        notifySubscribers();
    }

    private void notifySubscribers() {
        for (Subscriber subscriber : subscribers) {
            subscriber.newData();
        }
    }

    public void addSubscriber(Subscriber subscriber){
        subscribers.add(subscriber);
    }


    public static Data getInstance() {
        if(instance==null){
            instance = new Data();
        }
        return instance;
    }
}

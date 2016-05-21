package com.achdjian.MyOscilloscope.myoscilloscope;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;

import com.achdjian.MyOscilloscope.myoscilloscope.runnable.Connection;

public class MainActivity extends AppCompatActivity {
    private static final String PREF_FILE = "PrefsFile";
    private Connection connect;
    private boolean connected=false;
    private Toolbar myToolbar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myToolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(myToolbar);

        getFragmentManager().beginTransaction()
                .add(R.id.mainContent, MainFragment.newInstance())
                .commit();

        connect = new Connection(this);
        new Thread(connect).start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public void onBackPressed() {
        if(getFragmentManager().getBackStackEntryCount() == 0) {
            super.onBackPressed();
        }
        else {
            getFragmentManager().popBackStack();
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.preferences: {
                getFragmentManager().beginTransaction()
                        .replace(R.id.mainContent, new Settings())
                        .addToBackStack(null)
                        .commit();
                return true;
            }
        }
        return true;
    }

    public void enable() {
        connected=true;
        int color = getResources().getColor(android.R.color.holo_green_light);
        myToolbar.setBackgroundColor(color);
    }

    public void disable() {
        connected=false;
        int color = getResources().getColor(android.R.color.holo_green_dark);
        myToolbar.setBackgroundColor(color);

    }
}

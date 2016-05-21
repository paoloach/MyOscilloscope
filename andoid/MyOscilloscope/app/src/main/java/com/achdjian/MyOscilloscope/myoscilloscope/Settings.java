package com.achdjian.MyOscilloscope.myoscilloscope;

import android.os.Bundle;
import android.preference.PreferenceFragment;

/**
 * Created by paolo on 18/03/16.
 */
public class Settings extends PreferenceFragment {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Load the preferences from an XML resource
        addPreferencesFromResource(R.xml.preferences);
    }
}

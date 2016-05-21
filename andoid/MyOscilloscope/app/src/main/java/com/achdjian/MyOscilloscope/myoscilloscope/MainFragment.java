package com.achdjian.MyOscilloscope.myoscilloscope;

import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.achdjian.MyOscilloscope.myoscilloscope.customView.GraphView;


public class MainFragment extends Fragment implements Data.Subscriber {
    private GraphView graphView;
    private TextView dataLength;

    public MainFragment() {
    }

    public static MainFragment newInstance() {
        MainFragment fragment = new MainFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_main, container, false);

        graphView = (GraphView)view.findViewById(R.id.graphView);
        dataLength = (TextView)view.findViewById(R.id.data_length_text);
        Data.getInstance().addSubscriber(graphView);
        Data.getInstance().addSubscriber(this);
        return view;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

    }

    @Override
    public void onDetach() {
        super.onDetach();
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        Data.getInstance().removeSubscriber(graphView);
    }

    @Override
    public void newData() {
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                String len = Integer.toString(Data.getInstance().buffer.size());
                dataLength.setText(len);
            }
        });
    }
}

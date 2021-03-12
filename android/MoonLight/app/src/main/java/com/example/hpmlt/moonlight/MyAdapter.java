package com.example.hpmlt.moonlight;

import android.content.Context;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import static com.example.hpmlt.moonlight.MainActivity.db;
import static com.example.hpmlt.moonlight.MainActivity.mSocket;
import static com.example.hpmlt.moonlight.MainActivity.no_arr;
import static com.example.hpmlt.moonlight.MainActivity.tb_arr;
import static java.lang.Integer.parseInt;


/**
 * Created by hpmlt on 2017-11-09.
 */

public class MyAdapter extends ArrayAdapter<MyItem> {
    int flag = 0;
    int new_flag = 0;
    public List<MyItem> mItems;
    private ListView mListView;
    public MyAdapter(@NonNull Context context, @LayoutRes int resource, @NonNull ArrayList<MyItem> objects, ListView listView) {
        super(context, resource, objects);
        this.mItems = objects;
        this.mListView = listView;

    }
    public class SenderThread extends Thread {

        private String msg;
        BufferedWriter mOut;
        PrintWriter Out;
        Socket socket;

        SenderThread(String msg, Socket socket1) {
            try {
                this.msg = msg;
                this.socket = socket1;
                Log.d(this.getClass().getName(), "init" );
                if(socket == null)
                    Log.d(this.getClass().getName(), "null fuck" );
                mOut = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(),"UTF-8"));
                //Out = new PrintWriter(mOut, true);

                Log.d(this.getClass().getName(), "init2" );
            }
            catch(IOException e){
                Log.d(this.getClass().getName(), "init0" );
                //Toast.makeText(getApplicationContext(), "can't send", Toast.LENGTH_SHORT).show();

            }
        }
        public void send(String str1){
            try {
                String str = str1;

                mOut.write(str);
                //Out.flush();

                mOut.flush();
                //mOut.close();
                Log.d(this.getClass().getName(), "send success" );


            }
            catch(IOException e){
                Log.d(this.getClass().getName(), "send fail" );
                //Toast.makeText(getApplicationContext(), "fail send", Toast.LENGTH_SHORT).show();
            }

        }

        @Override
        public void run() {
            Log.d(this.getClass().getName(), "run init" );
            send(msg);
            /*runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d(TAG, "send message: " + msg);

                }
            });*/
        }
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent){
        final Context context = parent.getContext();
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.listview_custom, parent, false);
        }

        TextView name = (TextView) convertView.findViewById(R.id.name) ;
        TextView time = (TextView) convertView.findViewById(R.id.time) ;

        final MyItem myItem = getItem(position);
        String temp = myItem.getTime();
        String ret;
        if(temp.length() == 3)
            temp = "0"+temp;
        if(temp.charAt(0) == '0'){
            ret = "am "+(temp.charAt(0)-'0')+(temp.charAt(1)-'0') + ":" + (temp.charAt(2)-'0')+(temp.charAt(3)-'0');
        }
        else{
            if(temp.charAt(1) == '1' || temp.charAt(1) == '2'){
                ret = "am "+(temp.charAt(0)-'0')+(temp.charAt(1)-'0') + ":" + (temp.charAt(2)-'0')+(temp.charAt(3)-'0');
            }
            else{
                int hour = (temp.charAt(0)-'0')*10+(temp.charAt(1) - '0')-12;
                ret = "pm "+hour+ ":" + (temp.charAt(2)-'0')+(temp.charAt(3)-'0');


            }
        }


        name.setText(myItem.getName());
        time.setText(ret);


        final CheckBox cb1 = (CheckBox) convertView.findViewById(R.id.checkBox1);
        cb1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                mListView.setItemChecked(position,cb1.isChecked());
            }
        });





        final ToggleButton tb1 = (ToggleButton) convertView.findViewById(R.id.toggleButton3);

        Log.d(this.getClass().getName(),"fck-1 getView inite");
        //if(new_flag == 1){
            if(tb_arr.get(position) == "1"){
                tb1.setChecked(false);
                tb1.setBackgroundDrawable(ContextCompat.getDrawable(getContext(),R.drawable.on));
                //tb_arr.set(position,"1");
                Log.d(this.getClass().getName(),"fck1 " + String.valueOf(position));
            }
            else if(tb_arr.get(position) == "0"){
                tb1.setChecked(true);
                tb1.setBackgroundDrawable(ContextCompat.getDrawable(getContext(),R.drawable.off));
                //tb_arr.set(position,"-1");
                Log.d(this.getClass().getName(),"fck0 " + String.valueOf(position));
            }
            else
                Log.d(this.getClass().getName(),"fck2 " + String.valueOf(position));
            //new_flag = 0;
        //}
        tb1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                    if (tb1.isChecked()) {
                        int count = mItems.size();
                        Log.d(this.getClass().getName(), String.valueOf(position) + "change to 0");
                        tb_arr.set(position,"0");
                        int id = Integer.parseInt((String) no_arr.get(position));
                        tb1.setBackgroundDrawable(ContextCompat.getDrawable(getContext(),R.drawable.off));
                        db.execSQL("UPDATE alarms SET onoff = '0' WHERE no = "+id+";");


                        Socket mSocket1 = mSocket;
                        String msg = "0"+myItem.getTime() +myItem.getTimer()+myItem.getColor();
                        if(mSocket1 != null){
                            SenderThread st = new SenderThread(msg,mSocket1);
                            st.start();
                        }

                        ////////////////////////
                    }
                    else {
                        Log.d(this.getClass().getName(), String.valueOf(position) +"change to 1");
                        tb1.setBackgroundDrawable(ContextCompat.getDrawable(getContext(),R.drawable.on));
                        ///////////////////////////
                        tb_arr.set(position,"1");
                        Socket mSocket1 = mSocket;
                        int id = Integer.parseInt((String) no_arr.get(position));
                        db.execSQL("UPDATE alarms SET onoff = '1' WHERE no = "+id+";");
                        String msg = "1"+myItem.getTime() +myItem.getTimer()+myItem.getColor();
                        if(mSocket1 != null){
                            SenderThread st = new SenderThread(msg,mSocket1);
                            st.start();
                        }

                        //////////////////////////
                    }
            }
        });


        final LinearLayout layout_parent = (LinearLayout)convertView.findViewById(R.id.layout_parent);
        layout_parent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                cb1.setChecked(!cb1.isChecked());
                //Log.d(this.getClass().getName(), "positionis "+String.valueOf(position));
                mListView.setItemChecked(position,cb1.isChecked());
            }
        });

        if(flag == 1) { // show
            CheckBox cb = (CheckBox) convertView.findViewById(R.id.checkBox1);
            ToggleButton tb = (ToggleButton) convertView.findViewById(R.id.toggleButton3);

            tb.setVisibility(View.GONE);
            cb.setVisibility(View.VISIBLE); // show checkbox
        }
        else{
            CheckBox cb = (CheckBox) convertView.findViewById(R.id.checkBox1);
            ToggleButton tb = (ToggleButton) convertView.findViewById(R.id.toggleButton3);

            cb.setChecked(false);

            tb.setVisibility(View.VISIBLE);
            cb.setVisibility(View.GONE); // show checkbox

        }

        return convertView;
    }


    public void addItem( String name, String date,  String timer,String color, String time) {
        MyItem mItem = new MyItem();
        mItem.isChecked = false;
        mItem.setName(name);
        mItem.setDate(date);
        mItem.setTimer(timer);
        mItem.setColor(color);
        mItem.setTime(time);
        mItems.add(mItem);
    }



}

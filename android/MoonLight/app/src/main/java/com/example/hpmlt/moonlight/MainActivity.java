package com.example.hpmlt.moonlight;


import android.content.ContentValues;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Color;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.*;
import android.util.Log;
import android.util.SparseBooleanArray;

import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Thread.sleep;

public class MainActivity extends AppCompatActivity {
    public static final int REQUEST_CODE_ANOTHER  = 1001;
    ListView mListView;
    MyAdapter mMyAdapter;
    ArrayList<MyItem> mItem = new ArrayList<MyItem>();
    private static final String TAG = "TcpClient";
    String ret_name;
    String ret_time;
    String ret_date;
    String ret_timer;
    String ret_color;
    AlertDialog.Builder n;
    EditText et;
    String ip;
    int setting_count;
    static SQLiteDatabase db;
    //SQLiteOpenHelper helper;
    static ArrayList no_arr = new ArrayList();
    static ArrayList tb_arr = new ArrayList();

    int now_position = 0;








    private boolean isConnected = false;
    //private String mServerIP = null;
    static public Socket mSocket = null;


    public String getMsg(){
        String msg;

        msg = ret_time+ret_timer+ret_color;
        return msg;
    }

    AdapterView.OnItemClickListener listener= new AdapterView.OnItemClickListener() {

        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Log.d(this.getClass().getName(),"1111");
            // TODO Auto-generated method stub
            MyItem m = (MyItem) parent.getItemAtPosition(position);
            if(m.isChecked() == false){
                //Toast.makeText(getApplicationContext(), "turn true", Toast.LENGTH_SHORT).show();
                m.setChecked(true);
            } else {
                //Toast.makeText(getApplicationContext(), "turn false", Toast.LENGTH_SHORT).show();
                m.setChecked(false);
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    mMyAdapter.notifyDataSetChanged();
                }
            });
            mMyAdapter.notifyDataSetChanged();
        }

    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mListView = (ListView)findViewById(R.id.listView1);
        //mListView.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);
        mMyAdapter = new MyAdapter(this,android.R.layout.simple_list_item_multiple_choice,mItem, mListView);
        mListView.setChoiceMode(mListView.CHOICE_MODE_MULTIPLE);

        mListView.setAdapter(mMyAdapter);
        mListView.setOnItemClickListener(listener);

        Log.d(this.getClass().getName(), "fuck1" );
        db = init_db();
        Log.d(this.getClass().getName(), "fuck2" );
        init_tables();
        Log.d(this.getClass().getName(), "fuck3" );
        addItem();
        Log.d(this.getClass().getName(), "fuck4" );


    }

    public SQLiteDatabase init_db(){
        SQLiteDatabase data = null ;
        File file = new File(getFilesDir(), "moonlight.db") ;
        try {
            data = SQLiteDatabase.openOrCreateDatabase(file, null) ;
        } catch (SQLiteException e) {
            Log.d(this.getClass().getName(), "sqlexception" );
        }
        if(data == null)
            Log.d(this.getClass().getName(), "fucking man" );
        return data;



    }
    public void init_tables() {
        if (db != null) {
            db.execSQL("CREATE TABLE IF NOT EXISTS alarms (" +                    // 'alarms' 는 테이블 이름
                    "no INTEGER PRIMARY KEY autoincrement," +
                    "time INTEGER, " +
                    "timer INTEGER, " +
                    "name TEXT, " +
                    "color TEXT, " +
                    "onoff TEXT, " +
                    "date TEXT);");
        }
    }
    public int getId(){
        int recordCount = -1;
        String SQL = "SELECT * FROM alarms";                    // 'alarms' 는 테이블 이름
        Cursor outCursor = db.rawQuery(SQL, null);
        if(outCursor != null) {
            recordCount = outCursor.getCount();
            for (int i = 0; i < recordCount; i++) {
                outCursor.moveToNext();     // 다음 레코드를 가리킨다.
            }
            int no = outCursor.getInt(0);

            outCursor.close();
            return no;
        }
        return -1;
    }
    public void addItem(){
        int recordCount = -1;
        String SQL = "SELECT * FROM alarms";                    // 'alarms' 는 테이블 이름
        Log.d(this.getClass().getName(), "fuck11" );
        no_arr.clear();
        tb_arr.clear();

        //"(time, timer, name, onoff, color, date) " +

        Cursor outCursor = db.rawQuery(SQL, null);  // Cursor 객체를 얻는다.
        Log.d(this.getClass().getName(), "fuck22" );
        if(outCursor != null) {
            recordCount = outCursor.getCount();  // 레코드 개수를 리턴
            Log.d(this.getClass().getName(), "fuck33" );
            // 레코드 숫자 만큼 데이터를 가져 온다.
            for (int i = 0; i < recordCount; i++) {
                Log.d(this.getClass().getName(), "fuck111" );
                outCursor.moveToNext();     // 다음 레코드를 가리킨다.
                int no = outCursor.getInt(0);
                no_arr.add(String.valueOf(no));

                Log.d(this.getClass().getName(), "no is " + no + "i is "+ i );
                String time = outCursor.getString(1);
                if(time.length() == 3)
                    time = "0" + time;
                Log.d(this.getClass().getName(), "timeis " + time );
                String timer = outCursor.getString(2);
                if(timer.length() == 3)
                    timer = "0" + timer;
                Log.d(this.getClass().getName(), "timer is " + timer );

                String name = outCursor.getString(3);
                Log.d(this.getClass().getName(), "nameis " + name );
                String onoff = outCursor.getString(5);
                Log.d(this.getClass().getName(), "onoff " + onoff );
                //tb_arr.add(String.valueOf(onoff));
                if(onoff.equals("0")){
                    Log.d(this.getClass().getName(), "onoff " + onoff + "0" );
                    tb_arr.add("0");
                }
                else{
                    Log.d(this.getClass().getName(), "onoff " + onoff + "1" );
                    tb_arr.add("1");
                }

                String color = outCursor.getString(4);
                String date = outCursor.getString(6);
                Log.d(this.getClass().getName(), "fuck222" );
                MyItem m = new MyItem();
                m.setName(name);
                m.setTime(time);
                m.setColor(color);
                m.setTimer(timer);
                m.setDate(date);
                mItem.add( m);
                mMyAdapter.notifyDataSetChanged();
                //mListView.setAdapter(mMyAdapter);
                Log.d(this.getClass().getName(), "fuck333" );

            }
            //now_position++;
            outCursor.close();
        }




    }





    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu,menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        switch(item.getItemId()){
            case R.id.action_add:
                Intent intent = new Intent(getBaseContext(), SettingActivity.class);
                startActivityForResult(intent,REQUEST_CODE_ANOTHER);


                // send msg for arduino

                //
                return true;
            case R.id.action_delete:
                int count = mMyAdapter.getCount();

                if(count > 0){
                    Button b = (Button) findViewById(R.id.delete_button);
                    b.setVisibility(View.VISIBLE);

                    mMyAdapter.flag = 1;
                    mMyAdapter.notifyDataSetChanged();

                }

                return true;
            case R.id.action_ip:


                n = new AlertDialog.Builder(MainActivity.this);
                n.setTitle("IP 주소 입력");

                et = new EditText(MainActivity.this);



                n.setView(et)
                        .setPositiveButton ("확인", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {

                                ip = et.getText().toString();
                                //Toast.makeText(getApplicationContext(), ip, Toast.LENGTH_SHORT).show();
                                new Thread(new ConnectThread(ip, 8081)).start();


                                //t1.start();
                                dialog.dismiss();     //닫기

                            }
                        })
                        .setNegativeButton("취소", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();     //닫기
                            }
                        }).show();


                return true;


            default:
                return super.onOptionsItemSelected(item);

        }

    }
    @Override
    protected  void onDestroy(){
        super.onDestroy();
        isConnected = false;
    }

    public void deleteButton(View v){
        int i,count;
        count = mMyAdapter.mItems.size();
        SparseBooleanArray checked = mListView.getCheckedItemPositions();


        if(checked.size() != 0){
            //Toast.makeText(getApplicationContext(), "toast 3", Toast.LENGTH_SHORT).show();
            for(i=count-1;i>=0;i--){
                if(checked.get(i)){
                    mMyAdapter.mItems.remove(i);
                    db.execSQL("DELETE FROM alarms WHERE no = "+ no_arr.get(i) +";");
                    no_arr.remove(i);
                    tb_arr.remove(i);
                }
            }

            mMyAdapter.flag = 0;
            Button b = (Button) findViewById(R.id.delete_button);
            b.setVisibility(View.INVISIBLE);
            mListView.clearChoices();
            mMyAdapter.notifyDataSetChanged();
            
        }
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent){
        super.onActivityResult(requestCode,resultCode,intent);
        if(resultCode == RESULT_OK){
            ret_name = intent.getStringExtra("name");
            ret_date = intent.getStringExtra("date");
            ret_timer = intent.getStringExtra("timer");
            ret_color = intent.getStringExtra("color");
            ret_time = intent.getStringExtra("time");

            String msg;
            msg = "1"+this.getMsg();
            //Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();
            if(mSocket != null){
                SenderThread st = new SenderThread(msg,mSocket);
                st.start();
            }
            else{
                Toast.makeText(getApplicationContext(), "Wifi disconnected", Toast.LENGTH_SHORT).show();
            }

            String str = "insert into alarms (time, timer, name, color, onoff, date) values ('" + ret_time + "', '" + ret_timer+ "', '" + ret_name + "', '"+ret_color+  "', '1', '" + ret_date +"');";
            Log.d(this.getClass().getName(), str );

            Log.d(this.getClass().getName(),"2222");

            db.execSQL(str);
            no_arr.add(String.valueOf(getId()));
            tb_arr.add("-1");



            MyItem m = new MyItem();
            m.setName(ret_name);
            m.setTime(ret_time);
            m.setColor(ret_color);
            m.setTimer(ret_timer);
            m.setDate(ret_date);
            mItem.add( m);
            Log.d(this.getClass().getName(),"3333");
            mMyAdapter.notifyDataSetChanged();
            //mListView.setAdapter(mMyAdapter);
            Log.d(this.getClass().getName(),"4444");

        }

    }
    private class ConnectThread implements Runnable {

        private String serverIP;
        private int serverPort;
        ConnectThread(String ip, int port) {
        serverIP = ip;
        serverPort = port;
        }

        @Override
        public void run() {
            try {


                mSocket = new Socket(serverIP, serverPort);



            } catch( UnknownHostException e ) {
                Log.d(TAG,"ConnectThread: can't find host");
            }
            catch( SocketTimeoutException e ) {
                Log.d(TAG, "ConnectThread: timeout");
            }
            catch (Exception e) {
                Log.e(TAG, ("ConnectThread:" + e.getMessage()));
            }
            if (mSocket != null) {
                isConnected = true;
            }
            else{
                //Toast.makeText(getApplicationContext(), "no Socket", Toast.LENGTH_SHORT).show();
            }


            runOnUiThread(new Runnable() {

                @Override
                public void run() {
                    if (isConnected) {
                        Log.d(TAG, "connected to " + serverIP);
                        Toast.makeText(getApplicationContext(), "connected to "+ip, Toast.LENGTH_SHORT).show();

                        //for test

                        new Handler().postDelayed(new Runnable() {
                            @Override
                            public void run() {
                            Log.d(TAG, "wait success" + serverIP);
                            }
                        }, 1000);


                        //for test
                    }else{

                        Log.d(TAG, "failed to connect to server " + serverIP);
                        Toast.makeText(getApplicationContext(), "failed connect to "+ip, Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }
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

        }
    }


    /*private class ReceiverThread implements Runnable {

        @Override
        public void run() {

            try {

                while (isConnected) {
                    if ( mIn ==null) {
                        Log.d(TAG, "ReceiverThread: mIn is null");
                        break;
                    }

                    final String recvMessage =  mIn.readLine();
                    if (recvMessage != null) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Log.d(TAG, "recv message: "+recvMessage);

                            }
                        });
                    }
                }

                Log.d(TAG, "ReceiverThread: thread has exited");
                if (mOut != null) {
                    mOut.flush();
                    mOut.close();
                }

                mIn = null;
                mOut = null;

                if (mSocket != null) {
                    try {
                        mSocket.close();
                    } catch (IOException e) {
                    e.printStackTrace();
                    }
                }
            }
            catch (IOException e) {
                Log.e(TAG, "ReceiverThread: "+ e);
            }
        }

    }*/


}

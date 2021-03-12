package com.example.hpmlt.moonlight;

import android.app.Activity;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Typeface;
import android.media.Image;
import android.os.Bundle;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.File;
import java.net.Socket;
import java.util.ArrayList;


/**
 * Created by hpmlt on 2017-11-05.
 */

public class SettingActivity extends AppCompatActivity  {


    int time_flag = 0;
    int index = 0;

    String ret_time = "0600";
    String ret_name = "name";
    String ret_date = "2017-11-05";
    String ret_timer = "1000";
    String ret_color = "jms";


    private Integer[] mThumbIds = {R.drawable.joyful, R.drawable.meditation,
            R.drawable.stability, R.drawable.vitality,
            R.drawable.inspiration, R.drawable.creativity
    };
    private String[] mThumbInfos = {"joyful", "meditation", "stability", "vitality", "inspiration", " creativity"};
    public int[] color_check = {0, 0, 0, 0, 0, 0};
    public String[] color_set = {"j", "m", "s", "v", "i", "c"};
    public int[] image_id = {R.drawable.ck_0,R.drawable.ck_1,R.drawable.ck_2,R.drawable.ck_3,R.drawable.ck_4,R.drawable.ck_5,R.drawable.ck_6};
    public boolean[] check = {false,false,false,false,false,false};




    TimePickerDialog t;
    TimePicker tp;
    AlertDialog.Builder n;
    EditText et;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setting2);

        final ArrayList<String> items = new ArrayList<String>();
        final ArrayAdapter adapter = new ArrayAdapter(this, R.layout.simplelist, items);


        final ListView listview = (ListView) findViewById(R.id.listView2);
        listview.setAdapter(adapter);
        items.add("이름");
        items.add("시작 시간");
        items.add("종료 시간");


        listview.setAdapter(adapter);
        final CheckBox cb1 = (CheckBox) findViewById(R.id.ckb_1);
        final CheckBox cb2 = (CheckBox) findViewById(R.id.ckb_2);
        final CheckBox cb3 = (CheckBox) findViewById(R.id.ckb_3);
        final CheckBox cb4 = (CheckBox) findViewById(R.id.ckb_4);
        final CheckBox cb5 = (CheckBox) findViewById(R.id.ckb_5);
        final CheckBox cb6 = (CheckBox) findViewById(R.id.ckb_6);
        final TextView tv1_1 = (TextView) findViewById(R.id.j1_1);
        final TextView tv1_2 = (TextView) findViewById(R.id.j1_2);
        final TextView tv2_1 = (TextView) findViewById(R.id.j2_1);
        final TextView tv2_2 = (TextView) findViewById(R.id.j2_2);
        final TextView tv3_1 = (TextView) findViewById(R.id.j3_1);
        final TextView tv3_2 = (TextView) findViewById(R.id.j3_2);
        final TextView tv4_1 = (TextView) findViewById(R.id.j4_1);
        final TextView tv4_2 = (TextView) findViewById(R.id.j4_2);
        final TextView tv5_1 = (TextView) findViewById(R.id.j5_1);
        final TextView tv5_2 = (TextView) findViewById(R.id.j5_2);
        final TextView tv6_1 = (TextView) findViewById(R.id.j6_1);
        final TextView tv6_2 = (TextView) findViewById(R.id.j6_2);
        tv1_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv1_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));
        tv2_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv2_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));
        tv3_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv3_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));
        tv4_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv4_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));
        tv5_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv5_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));
        tv6_1.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/eng.ttf"));
        tv6_2.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/kor.ttf"));









        final CheckBox[] buttons = {cb1,cb2,cb3,cb4,cb5,cb6};
        listview.setOnItemClickListener(itemClickListenerOfSettingList);
        final ImageButton bt1 = (ImageButton)findViewById(R.id.joyful);

        bt1.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "joyful", Toast.LENGTH_SHORT).show();

                check[0] = !(check[0]);
                if(check[0]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[0] = 3;
                                buttons[0].setBackground(getDrawable(image_id[color_check[0]]));
                                //check[0] = !(check[0]);
                                break;
                            }
                        }
                        cb1.setBackground(getDrawable(image_id[index]));
                        color_check[0] = index;

                    }
                    else{
                        cb1.setBackground(getDrawable(image_id[index+1]));
                        color_check[0] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb1.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[0]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[0] = 0;
                    if(index >0)
                        index--;

                }


            }
        });
        final ImageButton bt2 = (ImageButton)findViewById(R.id.meditation);
        bt2.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "meditation", Toast.LENGTH_SHORT).show();
                check[1] = !(check[1]);
                if(check[1]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[1] = 3;
                                buttons[1].setBackground(getDrawable(image_id[color_check[1]]));
                                //check[1] = !(check[1]);
                                break;
                            }
                        }
                        cb2.setBackground(getDrawable(image_id[index]));
                        color_check[1] = index;

                    }
                    else{
                        cb2.setBackground(getDrawable(image_id[index+1]));
                        color_check[1] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb2.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[1]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[1] = 0;
                    if(index >0)
                        index--;

                }


            }
        });
        final ImageButton bt3 = (ImageButton)findViewById(R.id.stability);
        bt3.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "stability", Toast.LENGTH_SHORT).show();
                check[2] = !(check[2]);
                if(check[2]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[2] = 3;
                                buttons[2].setBackground(getDrawable(image_id[color_check[2]]));
                                //check[2] = !(check[2]);
                                break;
                            }
                        }
                        cb3.setBackground(getDrawable(image_id[index]));
                        color_check[2] = index;

                    }
                    else{
                        cb3.setBackground(getDrawable(image_id[index+1]));
                        color_check[2] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb3.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[2]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[2] = 0;
                    if(index >0)
                        index--;

                }

            }
        });
        final ImageButton bt4 = (ImageButton)findViewById(R.id.vitality);
        bt4.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "vitality", Toast.LENGTH_SHORT).show();
                check[3] = !(check[3]);

                if(check[3]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[3] = 3;
                                buttons[3].setBackground(getDrawable(image_id[color_check[3]]));
                                //check[3] = !(check[3]);
                                break;
                            }
                        }
                        cb4.setBackground(getDrawable(image_id[index]));
                        color_check[3] = index;

                    }
                    else{
                        cb4.setBackground(getDrawable(image_id[index+1]));
                        color_check[3] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb4.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[3]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[3] = 0;
                    if(index >0)
                        index--;

                }


            }
        });
        final ImageButton bt5 = (ImageButton)findViewById(R.id.inspiration);
        bt5.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "inspiration", Toast.LENGTH_SHORT).show();
                check[4] = !(check[4]);
                if(check[4]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[4] = 3;
                                buttons[4].setBackground(getDrawable(image_id[color_check[4]]));
                                //check[4] = !(check[4]);
                                break;
                            }
                        }
                        cb5.setBackground(getDrawable(image_id[index]));
                        color_check[4] = index;

                    }
                    else{
                        cb5.setBackground(getDrawable(image_id[index+1]));
                        color_check[4] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb5.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[4]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[4] = 0;
                    if(index >0)
                        index--;
                }
            }
        });
        final ImageButton bt6 = (ImageButton)findViewById(R.id.creativity);
        bt6.setOnClickListener(new ImageButton.OnClickListener() { //

            public void onClick(View v) {
                // TODO Auto-generated method stub
                //Toast.makeText(getApplicationContext(), "creativity", Toast.LENGTH_SHORT).show();
                check[5] = !(check[5]);
                if(check[5]){
                    if(index == 3){
                        for(int i = 0;i<6;i++){
                            if(color_check[i] ==3){
                                color_check[i] = 0;
                                buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                                check[i] = !(check[i]);
                                color_check[5] = 3;
                                buttons[5].setBackground(getDrawable(image_id[color_check[5]]));
                                //check[5] = !(check[5]);
                                break;
                            }
                        }
                        cb6.setBackground(getDrawable(image_id[index]));
                        color_check[5] = index;

                    }
                    else{
                        cb6.setBackground(getDrawable(image_id[index+1]));
                        color_check[5] = index+1;
                    }
                    if(index < 3)
                        index++;

                }
                else{
                    cb6.setBackground(getDrawable(image_id[0]));
                    for(int i = 0;i<6;i++){
                        if(color_check[i] > color_check[5]){
                            color_check[i]--;
                            buttons[i].setBackground(getDrawable(image_id[color_check[i]]));
                        }
                    }
                    color_check[5] = 0;
                    if(index >0)
                        index--;

                }

            }
        });
    }
    public String convert() {
        String str = "";
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(color_check[j] == i+1){
                    str = str+color_set[j];
                    break;
                }
            }
        }
        if(str == "")
            str = "jms";

        return str;
    }
















    private TimePickerDialog.OnTimeSetListener listener = new TimePickerDialog.OnTimeSetListener() {
        @Override
        public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
            int h,a;
            String m = String.valueOf(minute);
            if(m.length() == 1){
                m = "0" + m;
            }
            String hour = String.valueOf(hourOfDay);
            if(hour.length() == 1){
                hour = "0" + hour;
            }

            if(time_flag == 1){
                ret_time = hour+m;
                Toast.makeText(getApplicationContext(), ret_time, Toast.LENGTH_SHORT).show();
            }
            else{
                ret_timer = hour + m;
                Toast.makeText(getApplicationContext(), ret_timer, Toast.LENGTH_SHORT).show();
            }

        }
    };




    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu2,menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        switch(item.getItemId()){
            case R.id.action_save:
                Intent retIntent = new Intent();
                ret_color = convert();
                //Toast.makeText(getApplicationContext(), ret_color, Toast.LENGTH_SHORT).show();
                retIntent.putExtra("color",ret_color);
                retIntent.putExtra("time",ret_time);
                retIntent.putExtra("name",ret_name);
                retIntent.putExtra("date",ret_date);///////////////////////repeated setting
                retIntent.putExtra("timer",ret_timer);
                setResult(RESULT_OK,retIntent);
                Log.d(this.getClass().getName(),"5555");
                index = 0;
                finish();
                return true;


            default:
                return super.onOptionsItemSelected(item);

        }

    }
    private AdapterView.OnItemClickListener itemClickListenerOfSettingList = new AdapterView.OnItemClickListener()
    {
        public void onItemClick(AdapterView<?> adapterView, View clickedView, int pos, long id)
        {
            String command =  ((TextView)clickedView).getText().toString();
            //Toast.makeText(getApplicationContext(), command, Toast.LENGTH_SHORT).show();

            switch(command){
                case "시작 시간":
                    time_flag = 1;
                    t = new TimePickerDialog(SettingActivity.this, listener, 15, 24, false);
                    //t = new TimePickerDialog(SettingActivity.this, android.R.style.Theme_Holo_Light_Dialog, listener, 15, 24, false);
                    t.show();



                    return;

                case "종료 시간":
                    time_flag = 2;
                    t = new TimePickerDialog(SettingActivity.this, listener, 16, 24, false);
                    //t = new TimePickerDialog(SettingActivity.this, android.R.style.Theme_Holo_Light_Dialog, listener, 15, 24, false);
                    t.show();
                    return;

                case "이름":
                    //Toast.makeText(getApplicationContext(), "savebutton clicked", Toast.LENGTH_SHORT).show();
                    n = new AlertDialog.Builder(SettingActivity.this);
                    n.setTitle("알람 이름");       // 제목 설정

                    et = new EditText(SettingActivity.this);
                    n.setView(et)
                    .setPositiveButton ("확인", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            ret_name = et.getText().toString();
                            dialog.dismiss();     //닫기
                        }
                    })
                    .setNegativeButton("취소", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();     //닫기
                        }
                    }).show();
                    return;



                //case "기본 설정":
                //case "색 설정":


            }



        }
    };




}

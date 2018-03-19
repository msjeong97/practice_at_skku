package com.example.hpmlt.moonlight;

/**
 * Created by hpmlt on 2017-11-09.
 */


public class MyItem {


    private String name;
    private String date;
    private String timer;
    private String time;
    private String color;
    public boolean isChecked;


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getTime(){return time;}
    public void setTime(String time) {this.time = time;}
    public void setChecked(boolean c){
        this.isChecked = c;
    }
    public boolean isChecked(){
        return this.isChecked;
    }



    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTimer() {
        return timer;
    }

    public void setTimer(String timer) {
        this.timer = timer;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }




}
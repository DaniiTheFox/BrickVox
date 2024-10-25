package com.BoniiKwiiDz.plugin;

import java.io.IOException;

import com.brickvox.plugin.*;

public class Main {
	public static void main(String[] args){
		Bricks server = new Bricks("test plugin 1");
		System.out.println("hello from plugin inside logs version 6.0");
		server.sendChat("HELLO BRICKVOX FROM JAVA", 65);
		server.item_register("java_coffe","",0,"http://www.bonisoft.slpmx.com/test.bmp");
	}
}

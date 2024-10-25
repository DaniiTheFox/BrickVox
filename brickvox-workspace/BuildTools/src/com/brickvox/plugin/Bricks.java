package com.brickvox.plugin;

import java.io.*;
import java.sql.*;
import java.util.Scanner;

public class Bricks{
	String SRVR = "";
	String USER = "";
	String PASW = "";
	String CTDB = "";
	public int debug = 1;
	Connection server_conn = null;
	
	public Bricks(String pluginName) {
		/*
		 * ------------------------------
		 * - FETCH THE AUTH CREDENTIALS -
		 * ------------------------------
		 * */
		System.out.println("Build tools version: 0.1");
		File credentials = new File("loginCredentials.auth");
		if(!credentials.exists()) {
			System.out.println("Could not find file");
			System.exit(-1);
		}
		// - READ THE LOGINCREDENTIALS.AUTH FILE
		Scanner rdf;
		try {
			rdf = new Scanner(credentials);
			while (rdf.hasNextLine()) {
				// -------------------------------
				String blockr = rdf.nextLine();   
				String[] cmdr = blockr.split(" ");
				// -------------------------------
				if(cmdr[0].equalsIgnoreCase("h")) {SRVR = cmdr[1];}
				if(cmdr[0].equalsIgnoreCase("u")) {USER = cmdr[1];}
				if(cmdr[0].equalsIgnoreCase("p")) {PASW = cmdr[1];}
				if(cmdr[0].equalsIgnoreCase("d")) {CTDB = cmdr[1];}
			}
			if(debug==1) {System.out.println("logged in with credentials: " + SRVR + ", " + USER + ", " + PASW + ", "+ CTDB);}
			// - CLOSE THE FILES
			rdf.close();
			try {
				Class.forName("com.mysql.cj.jdbc.Driver");
				server_conn = DriverManager.getConnection("jdbc:mysql://"+SRVR+":3306/"+CTDB,USER,PASW);
			}catch(Exception e) {
				System.out.println("SERVER CONNECTION FAILED: " + e);
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// - AUTHENTICATE CREDENTIALS
	}
	
	public void sendChat(String label, int session) {
		Statement statement;
        try {
			statement = server_conn.createStatement();
			String msg = "INSERT INTO chat_data (Msg_Data,User_Sent,Session) VALUES (\'< SYSTEM >>"+label+"\',\'SERVER\',"+session+");";
	        if(debug==1) {System.out.println("packet sent: " + msg);}
			statement.execute(msg);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void item_register(String name, String code, int session /* 0 - for all*/, String _url ) {
		Statement statement;
        try {
        	String msg = "";
			statement = server_conn.createStatement();
			ResultSet res = statement.executeQuery("SELECT * FROM custom_object WHERE Nameob=\'"+name+"\' ");
			if(!res.next()) {
				System.out.println("Object Is new object generating for script....");
				msg = "INSERT INTO custom_object (Nameob,obCode,Sesion,img_ul) VALUES (\'"+name+"\',\'"+code+"\',"+session+",\'"+_url+"\');";
			}else {
				System.out.println("Object was created already updating...");
				msg = "UPDATE custom_object SET obCode = \'"+code+"\',Sesion="+session+",img_ul=\'"+_url+"\' WHERE Nameob=\'"+name+"\';";
			}
	        if(debug==1) {System.out.println("packet sent: " + msg);}
			statement.execute(msg);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}

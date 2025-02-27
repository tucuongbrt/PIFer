package com.example.pifwrobot;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;

import com.MAVLink.MAVLinkPacket;
import com.MAVLink.protocol.msg_cmd_velocity;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

import androidx.appcompat.app.AppCompatActivity;

import android.preference.PreferenceManager;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import io.github.controlwear.virtual.joystick.android.JoystickView;

import static android.app.PendingIntent.getActivity;
import static android.view.View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

public class MainActivity extends AppCompatActivity {

    Dialog dialog;
    Button btnAccept;
    Button btnClose;
    EditText edtIP0;
    EditText edtIP1;
    EditText edtIP2;
    EditText edtIP3;
    EditText edtPort;

    private Socket socket;
    Thread socketClientThread = null;
    String serverIP;
    Integer serverPort;

    JoystickView joystickLeft;
    JoystickView joystickRight;

    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;

    ProgressBar pgbConnecting;
    TextView tvConnecting;

    TextView tvX;
    TextView tvY;

    msg_cmd_velocity msg_cmd_velocity;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final int flags = View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;

        this.getWindow().setFlags(flags,flags);

        if (getSupportActionBar() != null) {
            getSupportActionBar().hide();
        }

        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        editor = sharedPreferences.edit();

        pgbConnecting = findViewById(R.id.pgbConnecting);
        tvConnecting = findViewById(R.id.tvConnecting);

        tvX = findViewById(R.id.tvX);
        tvY = findViewById(R.id.tvY);

        serverIP = sharedPreferences.getString("serverIP", "192.168.4.1");
        serverPort = sharedPreferences.getInt("serverPort", 8888);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                dialog.show();
            }
        });

        socketClientThread = new Thread(new SocketClientThread());
        socketClientThread.start();

        joystickLeft = findViewById(R.id.joystickView_left);
        joystickLeft.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                int yi = joystickLeft.getNormalizedY();
                yi = Math.min(yi, 100);
                yi = Math.max(yi, 0);
                yi -= 50;
                float yf = (float)yi /50.0f;
                tvY.setText(String.valueOf(yf));
            }
        });
        joystickLeft.setFixedCenter(false);

        joystickRight = findViewById(R.id.joystickView_right);
        joystickRight.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                int xi = joystickRight.getNormalizedX();
                xi = Math.min(xi, 100);
                xi = Math.max(xi, 0);
                xi -= 50;
                float xf = (float)xi /50.0f;
                tvX.setText(String.valueOf(xf));
            }
        });
        joystickRight.setFixedCenter(false);

        dialogInit();

        msg_cmd_velocity = new msg_cmd_velocity();
    }

    public void dialogInit(){
        dialog = new Dialog(this);
        dialog.setContentView(R.layout.dialog);
        dialog.setOnDismissListener(new DialogInterface.OnDismissListener(){
            @Override
            public void onDismiss(DialogInterface dialog) {
                Toast.makeText(MainActivity.this,
                        "Server: " + serverIP + ":" + serverPort, Toast.LENGTH_LONG).show();
            }
        });

        edtIP0 = dialog.findViewById(R.id.edtIP0);
        edtIP1 = dialog.findViewById(R.id.edtIP1);
        edtIP2 = dialog.findViewById(R.id.edtIP2);
        edtIP3 = dialog.findViewById(R.id.edtIP3);
        edtPort = dialog.findViewById(R.id.edtPort);

        String[] ip = serverIP.split("\\.", 4);
        edtIP0.setText(ip[0]);
        edtIP1.setText(ip[1]);
        edtIP2.setText(ip[2]);
        edtIP3.setText(ip[3]);
        edtPort.setText(serverPort.toString());

        btnAccept = dialog.findViewById(R.id.btnAccept);
        btnAccept.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                serverIP = edtIP0.getText().toString() + "." + edtIP1.getText().toString() + "." +
                        edtIP2.getText().toString() + "." + edtIP3.getText().toString();
                serverPort = Integer.parseInt(edtPort.getText().toString());
                editor.putString("serverIP", serverIP);
                editor.putInt("serverPort", serverPort);
                editor.commit();
                dialog.dismiss();
                if(socket!= null) {
                    try {
                        socket.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        btnClose = dialog.findViewById(R.id.btnClose);
        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });
    }

    class SocketClientThread implements Runnable {

        void connect(){
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    tvConnecting.setText("Connecting");
                    pgbConnecting.setVisibility(View.VISIBLE);
                }
            });

            socket = null;
            while(socket==null || !socket.isConnected()){
                try {
                    Thread.sleep(500);
                    Log.d("SocketClientThread", "run: Connecting to: " + serverIP + ":" + serverPort.toString());
                    InetAddress serverAddress = InetAddress.getByName(serverIP);
                    socket = new Socket();
                    InetSocketAddress sockAdr = new InetSocketAddress(serverAddress, serverPort);
                    socket.connect(sockAdr, 1000);
                } catch (InterruptedException e) {
                    Log.d("SocketClientThread", "run: UnknownHostException: " + e.toString());
                    e.printStackTrace();
                }
                catch (UnknownHostException e) {
                    Log.d("SocketClientThread", "run: UnknownHostException: " + e.toString());
                    e.printStackTrace();
                } catch (IOException e) {
                    Log.d("SocketClientThread", "run: IOException: " + e.toString());
                    e.printStackTrace();
                }
            }
            Log.d("SocketClientThread", "run: Connected to: " + serverIP + ":" + serverPort.toString());

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    tvConnecting.setText("Connected");
                    pgbConnecting.setVisibility(View.INVISIBLE);
                }
            });
        }

        @Override
        public void run() {
            while (true) {
                connect();
                DataOutputStream dOut = null;
                try {
                    dOut = new DataOutputStream(socket.getOutputStream());
                } catch (IOException e) {
                    e.printStackTrace();
                }
                while (true) {
                    try {
                        Thread.sleep(100);

                        int xi = joystickRight.getNormalizedX();
                        int yi = joystickLeft.getNormalizedY();
                        xi = Math.min(xi, 100);
                        xi = Math.max(xi, 0);
                        yi = Math.min(yi, 100);
                        yi = Math.max(yi, 0);
                        xi -= 50;
                        yi -= 50;
                        float xf = -(float)xi /50.0f;
                        float yf = (float)yi /50.0f;

                        msg_cmd_velocity.v = yf;
                        msg_cmd_velocity.omega = xf;
                        MAVLinkPacket mavLinkPacket = msg_cmd_velocity.pack();

                        @SuppressLint("DefaultLocale") String str = String.format("%03d:%03d\n", xi, yi);
                        dOut.write(mavLinkPacket.encodePacket());
                    } catch (InterruptedException | IOException e) {
                        Log.d("SocketClientThread", "run: Socket closed");
                        e.printStackTrace();
                        break;
                    }
                }
                Log.d("SocketClientThread", "run: Reconnect");
            }
        }
    }
}
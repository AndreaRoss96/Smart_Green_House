package unibo.btclient;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.support.v7.app.AppCompatActivity;
import java.lang.String;
import android.text.method.ScrollingMovementMethod;

import org.w3c.dom.Text;

import java.util.UUID;

import unibo.btclient.utils.C;
import unibo.btlib.BluetoothChannel;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public class MainActivity extends AppCompatActivity {

    private BluetoothChannel btChannel;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView = (TextView) findViewById(R.id.chatLabel);
        textView.setMovementMethod(new ScrollingMovementMethod());

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }

        initUI();
    }

    private void initUI() {
        findViewById(R.id.connectBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    connectToBTServer();
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    bluetoothDeviceNotFound.printStackTrace();
                }
            }
        });

        /*findViewById(R.id.sendBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = ((EditText)findViewById(R.id.editText)).getText().toString();
                btChannel.sendMessage(message);
                ((EditText)findViewById(R.id.editText)).setText("");

            }
        });*/
        findViewById(R.id.toogle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btChannel.sendMessage("t");         //cliccando sul pulsante automatic invia la stringa 't' di toggle
               /* TextView m = (TextView)findViewById(R.id.textMode);
                mode = !mode;
                final RadioGroup rg1 = (RadioGroup)findViewById(R.id.radio);
                if(!mode){
                    for(int i = 0; i < rg1.getChildCount(); i++){
                        ((RadioButton)rg1.getChildAt(i)).setEnabled(false);
                        ((RadioButton)rg1.getChildAt(i)).setChecked(false);
                    }
                }else{
                    for(int i = 0; i < rg1.getChildCount(); i++){
                        ((RadioButton)rg1.getChildAt(i)).setEnabled(true);
                        ((RadioButton)rg1.getChildAt(i)).setChecked(false);
                    }
                }
                m.setText("Mode: ".concat(mode ? "manual" : "automatic"));*/
            }
        });
        findViewById(R.id.low).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btChannel.sendMessage("l");         //cliccando sul pulsante low invia la stringa 'l'
            }
        });
        findViewById(R.id.medium).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btChannel.sendMessage("m");         //cliccando sul pulsante medium invia la stringa 'm'
            }
        });
        findViewById(R.id.high).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btChannel.sendMessage("h");         //cliccando sul pulsante high invia la stringa 'h'
            }
        });
        findViewById(R.id.close).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btChannel.sendMessage("z");         //cliccando sul pulsante close invia la stringa 'z' di zero
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        btChannel.close();
    }

    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, @Nullable final Intent data) {
        if(requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_OK){
            Log.d(C.APP_LOG_TAG, "Bluetooth enabled!");
        }

        if(requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_CANCELED){
            Log.d(C.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();//.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        AsyncTask<Void, Void, Integer> execute = new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                ((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                findViewById(R.id.connectBtn).setEnabled(false);

                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                         TextView hum = (TextView)findViewById(R.id.humidity);
                         final TextView m = (TextView)findViewById(R.id.textMode);
                         final Button toogle = (Button) findViewById(R.id.toogle);
                         String value="";
                         final RadioGroup rg1 = (RadioGroup)findViewById(R.id.radio);
                         for(int i=0;i<receivedMessage.indexOf("-");i++){
                             value = value.concat(receivedMessage.charAt(i)+"");
                             m.setText("Mode:".concat(value));
                             if(receivedMessage.substring(receivedMessage.indexOf("-")+1,receivedMessage.length()-1).equals("a")){
                                 m.setText("Mode: ".concat("automatic"));
                                 toogle.setText("MANUAL");
                                 for(int j = 0; j < rg1.getChildCount(); j++){
                                     ((RadioButton)rg1.getChildAt(j)).setEnabled(false);
                                     ((RadioButton)rg1.getChildAt(j)).setChecked(false);
                                 }
                             }else{
                                 m.setText("Mode: ".concat("manual"));
                                 toogle.setText("AUTOMATIC");
                                 for(int j = 0; j < rg1.getChildCount(); j++){
                                     ((RadioButton)rg1.getChildAt(j)).setEnabled(true);
                                 }
                             }
                         }

                         hum.setText(value.concat("% humidity"));
                        ((TextView) findViewById(R.id.chatLabel)).append(String.format("> [RECEIVED from %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                receivedMessage));
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        ((TextView) findViewById(R.id.chatLabel)).append(String.format("> [SENT to %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                sentMessage));
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                ((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : unable to connect, device %s not found!",
                        C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));
            }
        }).execute();
    }
}
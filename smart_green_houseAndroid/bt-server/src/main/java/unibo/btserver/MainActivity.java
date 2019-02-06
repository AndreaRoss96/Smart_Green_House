package unibo.btserver;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import unibo.btlib.CommChannel;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.BluetoothServer;
import unibo.btserver.utils.C;

public class MainActivity extends AppCompatActivity {

    private BluetoothServer btServer;
    private BluetoothServerListener btServerListener = new BluetoothServerListener();

    private List<RealBluetoothChannel> bluetoothChannelList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }

        initUI();
    }

    private void initUI() {
        findViewById(R.id.startButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startBluetoothServer();
            }
        });

        findViewById(R.id.sendBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String messageToBeSent = ((EditText)findViewById(R.id.editText)).getText().toString();

                for(RealBluetoothChannel channel : bluetoothChannelList){
                    channel.sendMessage(messageToBeSent);
                }

                ((EditText)findViewById(R.id.editText)).setText("");
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        btServer.terminate();
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

    private void startBluetoothServer(){
        bluetoothChannelList = new ArrayList<>();

        btServer = new BluetoothServer(C.bluetooth.BT_SERVER_UUID, C.bluetooth.BT_SERVER_NAME, btServerListener);
        btServer.start();
    }

    /**
     *
     */
    class BluetoothServerListener implements BluetoothServer.Listener {

        @Override
        public void onServerActive() {
            ((TextView) findViewById(R.id.statusLabel)).setText("Status : server started...");
            findViewById(R.id.startButton).setEnabled(false);
        }

        @Override
        public void onConnectionAccepted(final CommChannel btChannel) {
            ((TextView) findViewById(R.id.statusLabel)).setText("Status : client connected");

            btChannel.registerListener(new RealBluetoothChannel.Listener() {
                @Override
                public void onMessageReceived(String receivedMessage) {
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

            bluetoothChannelList.add((RealBluetoothChannel) btChannel);
        }
    }
}

package modulo_lab_2_2.jssc;

import java.io.IOException;

import jssc.*;

public class ShowSerialPorts {

	public static void main(String[] args) {
		
		/* detect serial ports */
		String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}

	}

}

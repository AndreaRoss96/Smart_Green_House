package main;

import common.CommChannel;
import common.SerialCommChannel;
import communication.DataService;
import io.vertx.core.Vertx;
import operation.IrrigationAgent;

public class Main {
	
	private static final int RATE = 9600;
	private static final String ARDUINO_PORT = "COM5"; // PORT where Arduino is plugged
	private static final int DATA_PORT = 800;

	public static void main(String[] args) throws Exception {
		final CommChannel serialComm = new SerialCommChannel(ARDUINO_PORT, RATE);
		
		final IrrigationAgent irrigation = new IrrigationAgent();
		irrigation.init(serialComm);
		irrigation.start();
		
		final DataService dataService = new DataService(DATA_PORT, irrigation, irrigation.getHistory());
		
		final Vertx vertx = Vertx.vertx();
		vertx.deployVerticle(dataService);
	}

}

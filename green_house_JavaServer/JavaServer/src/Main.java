
import java.io.IOException;

import controller.DataService;
import controller.EventLoopControllerImpl;
import controller.MsgService;
import controller.ObservableHumidityAgent;
import controller.PumpImpl;
import io.vertx.core.Vertx;

public class Main {

	public static void main(String[] args) throws IOException {
		final EventLoopControllerImpl eventLoopController;
		final ObservableHumidityAgent hAgent = new ObservableHumidityAgent();
		final PumpImpl pump = new PumpImpl();
		final MsgService msgService;
		final Vertx vertx = Vertx.vertx();
		final String port = "COM7"; /* replace with the name of the serial port */

		msgService = new MsgService(port, 9600);

		DataService service = new DataService(8085, hAgent);

		eventLoopController = new EventLoopControllerImpl(msgService, pump, hAgent);

		msgService.init();
		eventLoopController.start();
		vertx.deployVerticle(service);

		while (true) {
		}
	}
}
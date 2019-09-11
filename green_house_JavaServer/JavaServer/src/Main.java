
import java.io.IOException;

import io.vertx.core.Vertx;

public class Main {

    public static void main(String[] args) throws IOException {
    	final EventLoopControllerImpl gh;
//        final GreenHouseController ghc;
        final HumidityAgent hAgent = new HumidityAgent();
        ObservablePump pump = new ObservablePump();
        MsgService msgService;
		
		String port = "COM7"; /* replace with the name of the serial port */
		
        msgService = new MsgService(port,9600);


		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8085,hAgent);

        gh = new EventLoopControllerImpl(msgService,pump,hAgent);
//        ghc = new GreenHouseController(msgService,pump,hAgent);
        
        msgService.init();
        gh.start();
//        ghc.start();
        vertx.deployVerticle(service);
        
        while(true){            
        }
    }
}
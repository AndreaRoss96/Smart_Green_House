package communication;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import operation.BasicEventLoopController;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import utilities.Pair;
import event.MsgEvent;
import history.DataHistory;

/*
 * Data Service as a vertx event-loop - LAB 4.1
 *
 * --> Vertx  create an HttpServer, where is possible to read all the useful
 * information: humidity (get the humidity and reads informationsended by post method), 
 * pump action (close/open), with the date of action.
 * 
 */
public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	private final BasicEventLoopController IrrigationAgent;
	private final DataHistory dh;
	
	public DataService(int port, BasicEventLoopController IrrigationAgent, DataHistory dh) {	
		this.port = port;
		this.IrrigationAgent = IrrigationAgent;
		this.dh = dh;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/humidity").handler(this::handleDataHumidityReading);
		router.post("/api/humidity").handler(this::handleGetHumidityHistory);
		router.get("/api/pump").handler(this::handleGetPumpHistory);		
		vertx
			.createHttpServer()
			.requestHandler(router::accept)
			.listen(port);

		log("Service ready.");
	}
	
	// Reads the humidty values sended by ESP to server (POST)
	private void handleDataHumidityReading (RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			float humidity = res.getFloat("Humidity"); //Get the float value with the specified key
			MsgEvent msg = new MsgEvent(String.valueOf(humidity));
			this.IrrigationAgent.notifyEvent(msg);
			log("DataHumidityReading -- humidity value: " + humidity);
		}
	}
	
	// Reads huimdity history
	private void handleGetHumidityHistory(RoutingContext routingContext) {
		JsonArray jArr = new JsonArray();
		final ArrayList<Pair<Float, Date>> humidityHistory = this.dh.getHumidityHistory();
		for (Pair<Float, Date> p: humidityHistory) {
			JsonObject data = new JsonObject();
			data.put("Humidity", p.getFirst().toString());
			data.put("Date", p.getSecond());
			jArr.add(data);
		}
		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(jArr.encodePrettily());
	}
	
	//Reads pump history
	private void handleGetPumpHistory(RoutingContext routingContext) {
		JsonArray jArr = new JsonArray();
		final ArrayList<Pair<String, Date>> pumpHistory = this.dh.getPumpHistory();
		for (Pair<String, Date> p: pumpHistory) {
			JsonObject data = new JsonObject();
			data.put("Action", p.getFirst());
			data.put("Date", p.getSecond());
			jArr.add(data);
		}
		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(jArr.encodePrettily());
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}
}
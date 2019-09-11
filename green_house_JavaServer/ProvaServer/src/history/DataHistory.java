package history;

import java.util.ArrayList;
import java.util.Date;
import utilities.Pair;

public interface DataHistory {
	void insertHumidity(float humidity);	// Store information about humidity
	
	void insertPumpAction(String action);	// to know if the pump is been open or closed
	
	ArrayList<Pair<Float, Date>> getHumidityHistory();	// Get humidity information
	
	ArrayList<Pair<String, Date>> getPumpHistory();	// Get pump information
	
}

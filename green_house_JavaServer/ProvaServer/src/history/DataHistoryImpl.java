package history;

import java.util.ArrayList;
import java.util.Date;

import utilities.Pair;

public class DataHistoryImpl implements DataHistory {
	private static final int BUFFER = 50;
	private final ArrayList<Pair<Float, Date>> humidityHistory;
	private final ArrayList<Pair<String, Date>> irrigationHistory;
	
	public DataHistoryImpl() {
		this.humidityHistory = new ArrayList<Pair<Float,Date>>();
		this.irrigationHistory = new ArrayList<Pair<String,Date>>();
	}
	
	@Override
	public void insertHumidity(float humidity) {
        if(humidityHistory.size() >= BUFFER) {
            humidityHistory.remove(0);
        }
        this.humidityHistory.add(new Pair<Float, Date>(humidity, new Date()));
	}

	@Override
	public void insertPumpAction(String action) {
        if(irrigationHistory.size() >= BUFFER) {
        	irrigationHistory.remove(0);
        }
        this.irrigationHistory.add(new Pair<String, Date>(action, new Date()));
	}

	@Override
	public ArrayList<Pair<Float, Date>> getHumidityHistory() {
		return this.humidityHistory;
	}

	@Override
	public ArrayList<Pair<String, Date>> getPumpHistory() {
		return this.irrigationHistory;
	}

}

package events;

/*Generated in case of low humidity*/
public class LowHumidity implements Event {
	private int humidity;
	
	public LowHumidity(int humidity) {
		this.humidity = humidity;
	}
	
	public int getU() {
		return humidity;
	}
}

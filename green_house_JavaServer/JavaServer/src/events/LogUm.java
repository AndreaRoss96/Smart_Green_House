package events;

/*Generated when the server has to send a message to the actuator with the humidity*/
public class LogUm implements Event {
	private int humidity;
	
	public LogUm(int humidity) {
		this.humidity = humidity;
	}
	
	public int getUm() {
		return humidity;
	}
}

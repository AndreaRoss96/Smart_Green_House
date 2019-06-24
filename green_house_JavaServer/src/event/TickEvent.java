package event;

/*
 * Useful in observer's notify fuction
 * 
 * lab_3.2
 */
public class TickEvent implements Event {
	private long time;
	
	public TickEvent(long time) {
		this.time = time;
	}
	
	public long getTime(){
		return time;
	}
}

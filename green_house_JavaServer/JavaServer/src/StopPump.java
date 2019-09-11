

public class StopPump implements Event {
	private Pump source;
	
	public StopPump(Pump source) {
		this.source = source;
	}
	
	public Pump getSourcePump() {
		return source;
	}
}

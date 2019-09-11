

public class StartPump implements Event {
	private Pump source;
	private String message;
	
	public StartPump(Pump source,int umidita) {
		this.source = source;
		this.message = "Start";
		if(umidita < 10) {
			message += "2";
		} else if (umidita >= 10 && umidita < 20) {
			message += "1";
		} else {
			message += "0";
		}
	}
	
	public Pump getSourcePump() {
		return source;
	}
	
	public String getMessage() {
		return message;
	}
}

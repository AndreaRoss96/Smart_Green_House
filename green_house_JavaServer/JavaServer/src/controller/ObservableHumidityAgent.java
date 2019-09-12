package controller;
import events.LowHumidity;
import events.DonePump;
import events.LogUm;

public class ObservableHumidityAgent extends Observable {
	private enum State{REGULAR,IRRIGATION,MANUALE};
	private State state;
	private final int Umin = 30;
	private final int delta = 5;
	
	public ObservableHumidityAgent() {
		state = State.REGULAR;
	}
	
	public void checkMin(int U) {
		log("CHECKING VALUE");
		switch(state) {
		case REGULAR:
			if(U < Umin) {
				this.notifyEvent(new LowHumidity(U));
				state = State.IRRIGATION;
				log("VALUE UNDER MINIMUM LEVEL");
			}
			break;
		case IRRIGATION:
			if(U > (Umin+delta)) {
				this.notifyEvent(new DonePump());
				state = State.REGULAR;
				log("VALUE OK");
			}
			break;
		case MANUALE:
			break;
		}
	}
	
	public void setRegular() {
		this.state = State.REGULAR;
	}
	
	public void setManual() {
		this.state = State.MANUALE;
	}
	
	public void sendUmMsg(int um) {
		this.notifyEvent(new LogUm(um));
	}
	
	private void log(String msg) {
		System.out.println("[ESP] "+msg);
	}
}

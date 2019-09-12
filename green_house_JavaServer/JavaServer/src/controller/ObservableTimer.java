package controller;
import events.OvertimePump;

public class ObservableTimer extends Observable {
	private final PumpImpl pump;

	public ObservableTimer(final PumpImpl pump) {
		this.pump = pump;
	}
	
	void init() {
		new Thread(() -> {
			try {
				/*Wait five seconds and check if the pump is overtime*/
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(this.pump.isOpen()) {
				this.notifyEvent(new OvertimePump());
			}
		});
	}

}

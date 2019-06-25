package operation;

import java.util.concurrent.ScheduledFuture;

import common.CommChannel;
import event.Event;
import history.DataHistory;
import history.DataHistoryImpl;
import event.*;

public class IrrigationAgent extends BasicEventLoopController {

	private static final int U_min = 30; 	// Minimum humidity percentage threshold   
	private static final int DELTA_U = 5; 	// Stop irrigation when Humidity level > U_min + DELTA_U
	// Pump flow level (low, medium, high)
	private static final int HIGH = 30;
	private static final int MED = 20;
	private static final int LOW = 10;
	
	private static final int T_max = 5000; // Watchdog to terminate pump flow
	private static final boolean False = false;
	//messages
	private static final String OPEN_PUMP = "The pump has been opened";
	private static final String CLOSE_PUMP = "The pump has been closed";
	private static final String HUMIDITY_LEVEL = ", the humidity level is:";
	
	private ScheduledFuture<?> currentTimer;
	private ObservableDelay delay;
	private DataHistory dh = new DataHistoryImpl();
	private CommChannel serialChannel;
	private boolean isOpen = False;
	
	public void init(CommChannel serialChannel) {
		this.serialChannel = serialChannel;
		this.delay = new ObservableDelay(); 
		this.delay.addObserver(this);
	}
	
	@Override
	protected void processEvent(Event ev) {
		if (ev instanceof MsgEvent) {
			float uLevel = Float.parseFloat(((MsgEvent) ev).getMsg()); // humidity level
			dh.insertHumidity(uLevel);			
			if(uLevel <= U_min && !isOpen) {
				//humidity under recommended level --> open pump with Y l/min
				if (uLevel < LOW) {
					//P_max
					this.serialChannel.sendMsg(PumpFlow.Pmax.getValue());
				} else if(uLevel >= LOW && uLevel < MED) {
					//P_med
					this.serialChannel.sendMsg(PumpFlow.Pmed.getValue());
				} else if (uLevel >= MED && uLevel < HIGH) {
					//P_min
					this.serialChannel.sendMsg(PumpFlow.Pmin.getValue());
				}
				this.currentTimer = this.delay.scheduleTick(T_max);
				this.isOpen = true;
				this.dh.insertPumpAction(OPEN_PUMP + HUMIDITY_LEVEL + "uLevel");
			} else if (uLevel > U_min + DELTA_U && isOpen) {
				this.serialChannel.sendMsg(PumpFlow.Zero.getValue());
				this.isOpen = false;
				this.dh.insertPumpAction(CLOSE_PUMP + HUMIDITY_LEVEL + "uLevel");
				this.currentTimer.cancel(true);
			}
			this.serialChannel.sendMsg("H" + uLevel);
		} else if (ev instanceof TickEvent) {
			//watchdog timer expired, irrigation time ended
			this.serialChannel.sendMsg(PumpFlow.Zero.getValue());
			this.isOpen = false;
			this.dh.insertPumpAction(CLOSE_PUMP + "watchdog expired");
		}
	}
}

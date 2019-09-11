
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.time.Instant;

/**
 * Manages all messages recieved by classes and contains saves.
 */
public class EventLoopControllerImpl extends BasicEventLoopController {
	private enum State {
		AUTO, MANUAL
	};

	private State state;
	private MsgService monitor;
	private ObservablePump pump;
	private HumidityAgent hAgent;

	/**
	 * Costruttore che inizializza il radar allo stato di IDLE.
	 * 
	 * @throws IOException
	 */
	public EventLoopControllerImpl(final MsgService monitor, final ObservablePump pump, final HumidityAgent hAgent)
			throws IOException {
		save("[TURNING ON]");
		this.pump = pump;
		this.monitor = monitor;
		this.hAgent = hAgent;

		monitor.addObserver(this);
		pump.addObserver(this);
		hAgent.addObserver(this);
	}

	@Override
	protected void processEvent(Event ev) {
		try {
			if (ev instanceof MsgEvent) {
				if (((MsgEvent) ev).getMsg().equals("Start")) {
					save("START PUMP -> ARDUINO");
				} else if (((MsgEvent) ev).getMsg().equals("Stop")) {
					save("CLOSE PUMP -> ARDUINO");
				} else if (((MsgEvent) ev).getMsg().equals("StopT")) {
					save("OVERTIME PUMP -> ARDUINO");
					monitor.notifyEvent(new OvertimePump());
				} else if (((MsgEvent) ev).getMsg().equals("ManIn")) {
					save("MANUAL MODE -> ARDUINO");
					monitor.notifyEvent(new ManualMode());
				} else if (((MsgEvent) ev).getMsg().equals("ManOut")) {
					save("AUTO MODE -> ARDUINO");
					monitor.notifyEvent(new AutoMode());
				}
			} else if (ev instanceof StartPump) {
				monitor.sendMsg(((StartPump) ev).getMessage());
			} else if (ev instanceof StopPump) {
				monitor.sendMsg("Stop");
			} else if (ev instanceof LogUm) {
				monitor.sendMsg("Umidita:" + ((LogUm) ev).getUm());
			} else {
				switch (state) {
				case MANUAL:
					if (ev instanceof AutoMode && state != State.AUTO) {
						state = State.AUTO;
						hAgent.setRegular();
						log("AUTO MODE");
					}
					break;
				case AUTO:
					if (ev instanceof ManualMode && state != State.MANUAL) {
						state = State.MANUAL;
						hAgent.setManual();
						log("MANUAL MODE");
					} else if (ev instanceof AlarmPump) {
						pump.setOpen(((AlarmPump) ev).getU());
						log("Pump Open");
					} else if (ev instanceof DonePump) {
						pump.setClose();
						log("Pump Close");
					} else if (ev instanceof OvertimePump) {
						pump.overtimeClose();
						hAgent.setRegular();
						log("Overtime Pump Close");
					}
					break;
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	private void log(String msg) {
		System.out.println("GreenHouse log: " + msg);
	}

	private void save(String msg) throws IOException {
		final BufferedWriter bw = new BufferedWriter(new FileWriter(new File("output/log.txt"), true));
		bw.append(Instant.now() + " " + msg + "\n");
		bw.close();
	}

}

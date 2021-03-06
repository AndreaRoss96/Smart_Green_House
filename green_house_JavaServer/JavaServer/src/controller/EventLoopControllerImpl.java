package controller;
import events.*;
import java.io.BufferedWriter;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.time.Instant;

/**
 * Manages all messages received by classes and contains saves.
 */
public class EventLoopControllerImpl extends BasicEventLoopController {
	private enum State {
		AUTO, MANUAL
	};

	private State state;
	private MsgService msgService;
	private PumpImpl pump;
	private ObservableHumidityAgent hAgent;
	private ObservableTimer timer;

	/**
	 * Costruttore che inizializza il radar allo stato di IDLE.
	 * 
	 * @throws IOException
	 */
	public EventLoopControllerImpl(final MsgService monitor, final PumpImpl pump, final ObservableHumidityAgent hAgent)
			throws IOException {
		save("[TURNING ON]");
		this.pump = pump;
		this.msgService = monitor;
		this.hAgent = hAgent;
		this.timer = new ObservableTimer(this.pump);

		this.msgService.addObserver(this);
		this.hAgent.addObserver(this);
		this.timer.addObserver(this);
	}

	@Override
	protected void processEvent(Event ev) {
		System.out.println("Process Event");
		try {
			/*
			 * manda un messaggio all'arduino in caso di modifica dell'umidità con lo schema
			 * Hxx dove xx è il numero percentuale dell'umidità
			 */
			if (ev instanceof LogUm) {
				msgService.sendMsg("H" + ((LogUm) ev).getUm());
			} else {
				/* 
				 * altrimenti in caso di modalitàmanuale esegue dei controlli ed in caso di
				 * modalità automatica ne esegue altri
				 */
				switch (state) {
				case MANUAL:
					if (ev instanceof MsgEvent) {
						if (((MsgEvent) ev).getMsg().equals("o")) {
							//memorizza l'apertura della pompa
							save("START PUMP -> ARDUINO");
							log("arduino opened the pomp");
							pump.setOpen();
						} else if (((MsgEvent) ev).getMsg().equals("c")) {
							//memorizza la chiusura della pompa
							save("CLOSE PUMP -> ARDUINO");
							log("arduino closed the pomp");
							pump.setClose();
						} else if (((MsgEvent) ev).getMsg().equals("0")) {
							//memorizza il cambio di modalità da manuale ad automatico
							save("AUTO MODE -> ARDUINO");
							log("AUTO MODE");
							hAgent.setRegular();
							state = State.AUTO;
						}
					}
					break;
				case AUTO:
					if (ev instanceof MsgEvent && ((MsgEvent) ev).getMsg().equals("1")) {
						//memorizza il cambio di modalità da automatico a manuale
						save("MANUAL MODE -> ARDUINO");
						state = State.MANUAL;
						hAgent.setManual();
						log("MANUAL MODE");
					} else if (ev instanceof LowHumidity) {
						//apre la pompa
						this.openPump(((LowHumidity) ev).getU());
					} else if (ev instanceof DonePump) {
						//chiude la pompa
						this.closePump();
						log("Pump Close");
					} else if (ev instanceof OvertimePump) {
						//chiude la pompa in overtime
						pump.setClose();
						hAgent.setRegular();
						log("Overtime Pump Close");
						closePump();
					}
					break;
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	/*chiude la pompa e invia il messaggio ad arduino*/
	private void closePump() {
		pump.setClose();		
		msgService.sendMsg("z");
	}

	/*apre la pompa e invia il messaggio ad arduino*/
	private void openPump(int humidity) {
		pump.setOpen();
		log("Pump Open");
		String msg = new String();
		if(humidity < 10) {
			msg += "h";
		} else if (humidity >= 10 && humidity < 20) {
			msg += "m";
		} else {
			msg += "l";
		}
		msgService.sendMsg(msg);
		/*Parte il thread per il controlle dell'overtime*/
		timer.init();
		
		
		
	}

	private void log(String msg) {
		System.out.println("GreenHouse log: " + msg);
	}

	private void save(String msg) throws IOException {
		final BufferedWriter bw = new BufferedWriter(new FileWriter(new File("log.txt"), true));
		bw.append(Instant.now() + " " + msg + "\n");
		bw.close();
	}

}

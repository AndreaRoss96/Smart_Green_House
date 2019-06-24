package provaEventLoop;

import modulo_lab_2_2.msg.jssc.SerialCommChannel;
import javafx.application.Platform;


public class MessageManager implements Runnable {
	private CommChannel channel;
	private Gui gui;

	public MessageManager(Gui gui) {
		this.gui = gui;
		try {
			channel = new SerialCommChannel("COM5", 9600);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	@Override
	public void run() {

		try {

			/* attesa necessaria per fare in modo che Arduino completi il reboot */
			System.out.println("Waiting Arduino for rebooting...");
			Thread.sleep(4000);
			System.out.println("Ready.");

			while (true) {
				String msg = channel.receiveMsg().replaceAll("\r", "");	
				Platform.runLater(new Runnable() {
					public void run() {
						gui.printMessage(msg);
					}
				});
			
			Thread.sleep(100);
			}
		} catch (Exception e) {	
			System.out.println("ciaooooo");
		}
	}
	public void send(String msg) {
		channel.sendMsg(msg);
		System.out.println(msg);
	}

}

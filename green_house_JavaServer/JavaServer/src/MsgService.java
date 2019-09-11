
public class MsgService extends Observable {
	private CommChannel channel;
	private String port;
	private int rate;
	
	public MsgService(String port, int rate){
		this.port = port;
		this.rate = rate;
	}
	
	void init(){
		try {
			channel = new ExtendedSerialCommChannel(port, rate);	
			// channel = new SerialCommChannel(port, rate);	
			System.out.println("Waiting Arduino for rebooting...");		
			Thread.sleep(4000);
			System.out.println("Ready.");		
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		new Thread(() -> {
			while (true) {
				try {
					if(channel.isMsgAvailable()) {
						String msg = channel.receiveMsg();
						System.out.println("[Received] "+msg);
						this.notifyEvent(new MsgEvent(msg));
					}
				} catch (Exception ex) {
					ex.printStackTrace();
				}
			}
		}).start();
	}
	
	public void sendMsg(String msg) {
		channel.sendMsg(msg);
		System.out.println("[MSGSERVICE] sent "+msg);
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}

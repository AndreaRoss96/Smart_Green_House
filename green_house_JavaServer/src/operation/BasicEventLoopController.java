package operation;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import common.Observable;
import common.Observer;
//internal packages
import event.Event;
/*
 * Controller of basic events, executing by looping 
 */
public abstract class BasicEventLoopController extends Thread implements Observer {
	
	public static final int defaultEventQueueSize = 50;
	protected BlockingQueue<Event> eventQueue;
	
	protected BasicEventLoopController(int size){
		eventQueue = new ArrayBlockingQueue<Event>(size);
	}

	protected BasicEventLoopController(){
		this(defaultEventQueueSize);
	}
	
	/*
	 * Implements all the logic of an event inside the main loop 
	 */
	abstract protected void processEvent(Event ev);
	
	public void run(){
		while (true){
			try {
				Event ev = this.waitForNextEvent();
				this.processEvent(ev);
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	/*protected methods are not inherited*/
	protected void startObserving(Observable object){
		object.addObserver(this);
	}

	protected void stopObserving(Observable object){
		object.removeObserver(this);
	}
	
	protected Event waitForNextEvent() throws InterruptedException {
		return eventQueue.take();
	}

	protected Event pickNextEventIfAvail() throws InterruptedException {
		return eventQueue.poll();
	}
	
	public boolean notifyEvent(Event ev){
		return eventQueue.offer(ev);
	}
}

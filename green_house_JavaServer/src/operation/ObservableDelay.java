package operation;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import common.Observable;
import event.TickEvent;

public class ObservableDelay extends Observable {

	private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
	private Runnable tickThread;

	/*
	 * Runnable interface is the primary template for any object that is intended\\
	 * to be executed by a thread. It defines a single method run(), which is\\
	 * meant to contain the code that is executed by the thread.
	 */
	public ObservableDelay() {
		tickThread = () -> { // code to be executed in run()
			TickEvent tk = new TickEvent(System.currentTimeMillis());
			notifyEvent(tk);
		};
	}

	/**
	 * Generate a tick event after a deltaT milliseconds
	 * 
	 * @param deltaTime
	 * 
	 * @return a ScheduledFuture representing pending completion ofthe task and
	 *         whose get() method will return null upon completion
	 */
	public synchronized ScheduledFuture<?> scheduleTick(long deltaT) {
		return scheduler.schedule(tickThread, deltaT, TimeUnit.MILLISECONDS);
	}
}

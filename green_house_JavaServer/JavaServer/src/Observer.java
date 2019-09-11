import events.Event;

public interface Observer {
	boolean notifyEvent(Event ev);
}

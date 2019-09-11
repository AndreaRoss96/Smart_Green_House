package common;

import event.Event;

public interface Observer {

	boolean notifyEvent(Event ev);
}

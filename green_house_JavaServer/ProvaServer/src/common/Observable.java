package common;

import java.util.LinkedList;

import event.Event;

public class Observable {
	
	private LinkedList<Observer> observers;
	
	protected Observable(){
		observers = new LinkedList<Observer>();
	}
	
	/*
	 * I metodi synchronized sono utilizzati per fornire un meccanismo di sincronizzazione tra vari metodi.
	 * 
	 * Quando un thread ichima un metodo synchornized su di un oggetto, allora gli altri thread //
	 * che richiamano lo stesso metodo sospendono la loro esecuzione fino al termine dell'esecuzione //
	 * del metodo chiamato dal primo thread.
	 */
	protected void notifyEvent(Event ev){
		synchronized (observers){
			for (Observer obs: observers){
				obs.notifyEvent(ev);
			}
		}
	}

	public void addObserver(Observer obs){
		synchronized (observers){
			observers.add(obs);
		}
	}

	public void removeObserver(Observer obs){
		synchronized (observers){
			observers.remove(obs);
		}
	}

}

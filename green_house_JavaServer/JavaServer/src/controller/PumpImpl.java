package controller;
public class PumpImpl implements Pump {

	private boolean isOpen;
	
	public PumpImpl(){
		this.isOpen = false;
	}
	
	@Override
	public synchronized boolean isOpen() {
		return isOpen;
	}
	
	@Override
	public void setOpen() {
		isOpen = true;
	}
	
	@Override
	public void setClose() {
		isOpen = false;
	}
}

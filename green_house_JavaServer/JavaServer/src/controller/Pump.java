package controller;

import java.io.IOException;

public interface Pump {
	boolean isOpen();
	void setOpen() throws IOException;
	void setClose() throws IOException;
}

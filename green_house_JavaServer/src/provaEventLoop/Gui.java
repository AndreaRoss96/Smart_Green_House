package provaEventLoop;

import java.awt.Toolkit;
import java.net.URL;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class Gui extends Application {
	final double HEIGHT = Toolkit.getDefaultToolkit().getScreenSize().getHeight() / 2;
	final double WIDTH = Toolkit.getDefaultToolkit().getScreenSize().getWidth() / 3;
	private Scene scene;
	private AnchorPane layout;
	private Button h,l,m,z; 
	private Label messages = new Label("  ");
	private MessageManager myManager;
	
	@Override
	public void start(final Stage stage) throws Exception {		
		createForm(stage);
		myManager = new MessageManager(this);
		Thread t = new Thread(myManager);
		t.start();		
	}
	
	private void createForm(final Stage stage) {
		layout = new AnchorPane();		
		final Label title = new Label("Green House controllerino");
		title.getStyleClass().add("title");
		
		h = new Button("portata alta");
		h.setOnAction(e->{
			Platform.runLater(new Runnable() {
				public void run() {
					myManager.send("h\n");
				}
			});
		});
		m = new Button("portata media");
		m.setOnAction(e->{
			Platform.runLater(new Runnable() {
				public void run() {
					myManager.send("m\n");
				}
			});
		});
		l = new Button("portata bassa");
		l.setOnAction(e->{
			Platform.runLater(new Runnable() {
				public void run() {
					myManager.send("l\n");
				}
			});
		});
		z = new Button("chiusura");
		z.setOnAction(e->{
			Platform.runLater(new Runnable() {
				public void run() {
					myManager.send("z\n");
				}
			});
		});
		
		AnchorPane.setTopAnchor(title, HEIGHT/20);
		AnchorPane.setLeftAnchor(title, WIDTH/4);
		AnchorPane.setTopAnchor(h, HEIGHT/6);
		AnchorPane.setLeftAnchor(h, WIDTH/18);
		AnchorPane.setTopAnchor(m, HEIGHT/6);
		AnchorPane.setLeftAnchor(m, WIDTH/1.5);

		AnchorPane.setTopAnchor(l, HEIGHT/3.5);
		AnchorPane.setLeftAnchor(l, WIDTH/1.5);
		AnchorPane.setTopAnchor(z, HEIGHT/3.5);
		AnchorPane.setLeftAnchor(z, WIDTH/18);
		AnchorPane.setTopAnchor(messages, HEIGHT/1.5);
		AnchorPane.setLeftAnchor(messages, WIDTH/18);

		
		
		layout.getChildren().addAll(title,z,m,l,h, messages);

		scene = new Scene(layout, WIDTH, HEIGHT);
		URL url = this.getClass().getResource("style.css");
	    if (url == null) {
	        System.out.println("Resource not found. Aborting.");
	        System.exit(-1);
	    }
	    String css = url.toExternalForm(); 
	    scene.getStylesheets().add(css);
		stage.setScene(scene);
		
		stage.setOnCloseRequest((e) -> {
			System.exit(0);
		});
		stage.setResizable(false);
		stage.show();
	}

	public void printMessage(String msg) {
		messages.setText(msg);
	}
	/*
	public void maintenance() {
		but.setDisable(false);
	}
	
	public void setSugar(int value) {
		sugarValue.setText("" + value);
	}*/
}

	

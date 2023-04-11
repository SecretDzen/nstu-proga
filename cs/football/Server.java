package football;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Server extends Application {
  private final int WIDTH_ = 900;
  private final int HEIGHT_ = 600;
  private boolean isConnected_ = false;

  private TextArea messageArea;
  private TextField messageField;
  private Button sendButton;
  private Button toggleButton;
  private Button createClient_;
  private Middleware serverSocket_;

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage rootStage) {
    serverSocket_ = new Middleware(true);
    serverSocket_.addServer(this);
    serverSocket_.start();

    messageArea = new TextArea();
    messageArea.setEditable(false);
    VBox root = new VBox(messageArea);
    HBox.setHgrow(root, Priority.ALWAYS);

    messageField = new TextField();
    sendButton = new Button("Send");
    sendButton.setOnAction(event -> sendMessage());

    toggleButton = new Button("Start");
    toggleButton.setOnAction(event -> {
      if (isConnected_) {
        changeConnectionStatus();
        serverSocket_.disconnect();
      } else {
        changeConnectionStatus();
        serverSocket_.connect();
      }
    });

    createClient_ = new Button("Start Client");
    createClient_.setOnAction(e -> {
      Middleware client = new Middleware(false, new Client(), this);
      client.runClient();
    });

    HBox inputBox = new HBox(messageField, sendButton);
    HBox buttonBox = new HBox(toggleButton, createClient_);
    root.getChildren().add(new VBox(inputBox, buttonBox));

    Scene scene = new Scene(root, WIDTH_, HEIGHT_);
    rootStage.setScene(scene);
    rootStage.setTitle("Football Server");
    rootStage.show();
  }

  public void changeConnectionStatus() {
    this.isConnected_ = !this.isConnected_;

    if (this.isConnected_)
      toggleButton.setText("Stop server");
    else
      toggleButton.setText("Start server");
  }

  private void sendMessage() {
    String msg = "Server: " + messageField.getText();
    appendLog(msg);

    serverSocket_.getWriter().println(msg);

    messageField.clear();
  }

  public void appendLog(String msg) {
    messageArea.appendText(msg + "\n");
  }
}
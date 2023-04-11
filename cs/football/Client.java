package football;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Client extends Application {
  private final int WIDTH_ = 900;
  private final int HEIGHT_ = 600;
  private boolean isConnected_ = false;

  private TextArea logs_;
  private TextField messageField;
  private Button sendButton;
  private Button toggleButton;

  private Middleware clienSocket_;

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage rootStage) {
    clienSocket_ = new Middleware(false);
    clienSocket_.addClient(this);
    clienSocket_.start();

    logs_ = new TextArea();
    logs_.setEditable(false);

    VBox root = new VBox(logs_);

    messageField = new TextField();

    sendButton = new Button("Send");
    sendButton.setOnAction(event -> sendMessage());

    toggleButton = new Button("Connect");
    toggleButton.setOnAction(event -> {
      if (isConnected_) {
        changeConnectionStatus();
        clienSocket_.disconnect();
      } else {
        changeConnectionStatus();
        clienSocket_.connect();
      }
    });

    HBox inputBox = new HBox(messageField, sendButton);
    HBox buttonBox = new HBox(toggleButton);
    root.getChildren().add(new VBox(inputBox, buttonBox));

    Scene scene = new Scene(root, WIDTH_, HEIGHT_);
    rootStage.setScene(scene);
    rootStage.setTitle("Football client");
    rootStage.show();
  }

  public void appendLog(String msg) {
    logs_.appendText(msg + "\n");
  }

  private void changeConnectionStatus() {
    this.isConnected_ = !this.isConnected_;

    if (this.isConnected_)
      toggleButton.setText("Disconnect");
    else
      toggleButton.setText("Connect");
  }

  private void sendMessage() {
    if (clienSocket_.getWriter() != null) {
      String msg = "Client: " + messageField.getText();
      clienSocket_.getWriter().println(msg);
      appendLog(msg);
      messageField.setText("");
    }
  }
}
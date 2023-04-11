package football;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

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
    clienSocket_ = new Middleware();

    logs_ = new TextArea();
    logs_.setEditable(false);

    VBox root = new VBox(logs_);

    messageField = new TextField();

    sendButton = new Button("Send");
    sendButton.setOnAction(event -> sendMessage());

    toggleButton = new Button("Connect");
    toggleButton.setOnAction(event -> {
      handleClientStatus();
    });

    HBox inputBox = new HBox(messageField, sendButton);
    HBox buttonBox = new HBox(toggleButton);
    root.getChildren().add(new VBox(inputBox, buttonBox));

    Scene scene = new Scene(root, WIDTH_, HEIGHT_);
    rootStage.setScene(scene);
    rootStage.setTitle("Football client");
    rootStage.show();
  }

  private void handleClientStatus() {
    int status = clienSocket_.manageConnection();
    if (status == 1) {
      changeConnectionStatus();
      appendLog("Connected to server\n");
      createThread();
    } else if (status == 2) {
      changeConnectionStatus();
      appendLog("Disconnected from server\n");
    } else {
      appendLog("Wild Error: " + status + "\n");
    }
  }

  private void createThread() {
    new Thread(() -> {
      try {
        while (true) {
          String message = clienSocket_.getReader().readLine();
          if (message == null)
            break;
          Platform.runLater(() -> appendLog(message));
        }
      } catch (IOException err) {
        if (clienSocket_.getClientSocket() != null) {
          Platform.runLater(() -> appendLog("Error receiving message\n"));
          System.err.println("Error receiving message: " + err.getMessage());
        }
      }
    }).start();
  }

  private void appendLog(String msg) {
    logs_.appendText(msg);
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
      clienSocket_.getWriter().println(messageField.getText() + "\n");
      messageField.setText("");
    }
  }
}
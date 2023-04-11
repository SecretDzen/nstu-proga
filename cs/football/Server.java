package football;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

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
  public List<Middleware> clients_ = new ArrayList<>();

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage rootStage) {
    serverSocket_ = new Middleware(null, this);

    messageArea = new TextArea();
    messageArea.setEditable(false);
    VBox root = new VBox(messageArea);
    HBox.setHgrow(root, Priority.ALWAYS);

    messageField = new TextField();
    messageField.setOnAction(event -> sendMessage());

    sendButton = new Button("Send");
    sendButton.setOnAction(event -> sendMessage());

    toggleButton = new Button("Start");
    toggleButton.setOnAction(event -> {
      handleServerStatus();
    });

    createClient_ = new Button("Start Client");
    createClient_.setOnAction(e -> {
      Client client = new Client();
      client.start(new Stage());
    });

    HBox inputBox = new HBox(messageField, sendButton);
    HBox buttonBox = new HBox(toggleButton, createClient_);
    root.getChildren().add(new VBox(inputBox, buttonBox));

    Scene scene = new Scene(root, WIDTH_, HEIGHT_);
    rootStage.setScene(scene);
    rootStage.setTitle("Football Server");
    rootStage.show();
  }

  private void handleServerStatus() {
    int status = serverSocket_.manageConnection();
    if (status == 3) {
      changeConnectionStatus();
      appendLog("Server started!\n");
      runThread();
    } else if (status == 4) {
      changeConnectionStatus();
      appendLog("Server stopped!\n");

      for (Middleware client : clients_) {
        client.disconnect();
      }
      clients_.clear();

    } else {
      appendLog("Wild error appear: " + status + "\n");
    }
  }

  public void changeConnectionStatus() {
    this.isConnected_ = !this.isConnected_;

    if (this.isConnected_)
      toggleButton.setText("Stop server");
    else
      toggleButton.setText("Start server");
  }

  private void runThread() {
    new Thread(() -> {
      while (true) {
        Socket clientSocket = serverSocket_.accept();
        if (clientSocket == null)
          break;
        Middleware clientHandler = new Middleware(clientSocket, this);
        clients_.add(clientHandler);
        clientHandler.start();
      }
    }).start();
  }

  private void sendMessage() {
    String message = "Server: " + messageField.getText() + "\n";
    appendLog(message);

    for (Middleware client : clients_) {
      client.getWriter().println(message);
    }

    messageField.clear();
  }

  public void appendLog(String msg) {
    messageArea.appendText(msg);
  }

  public void broadcastMessage(String message) {
    Platform.runLater(() -> appendLog(message));

    for (Middleware client : clients_) {
      client.getWriter().println(message);
    }
  }
}
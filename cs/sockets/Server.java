package sockets;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Vector;

import elements.CatImg;
import elements.CatText;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import ui.CommonButtons;

public class Server extends Application {
  private int WIDTH_;
  private int HEIGHT_;
  private boolean isConnected_ = false;

  private TextArea logs_;
  private TextField messageField;
  private Button sendButton;
  private Button toggleButton_;
  private Button createClient_;
  private Middleware serverSocket_;

  private CommonButtons commonButtons_;
  private Vector<CatText> texts_;
  private Vector<CatImg> images_;

  public Server(int w, int h) {
    this.WIDTH_ = w;
    this.HEIGHT_ = h;
  }

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage rootStage) {
    serverSocket_ = new Middleware(true);
    serverSocket_.addServer(this);
    serverSocket_.start();

    texts_ = new Vector<CatText>();
    images_ = new Vector<CatImg>();

    Pane root = new Pane();
    VBox buttons = new VBox();
    buttons.setSpacing(4);
    Group view = new Group();

    commonButtons_ = new CommonButtons(WIDTH_, HEIGHT_, texts_, images_);
    commonButtons_.createClientButtons(view, buttons);

    logs_ = new TextArea();
    logs_.setMaxWidth(300);
    logs_.setEditable(false);

    messageField = new TextField();
    sendButton = new Button("Send");
    sendButton.setOnAction(event -> sendMessage());

    toggleButton_ = new Button("Start server");
    toggleButton_.setMinSize(150, 25);
    toggleButton_.setOnAction(event -> {
      if (isConnected_) {
        changeConnectionStatus();
        serverSocket_.disconnect();
      } else {
        changeConnectionStatus();
        serverSocket_.connect();
      }
    });

    createClient_ = new Button("Run Client");
    createClient_.setMinSize(150, 25);
    createClient_.setOnAction(e -> {
      Middleware client = new Middleware(false, new Client(), this);
      client.runClient();
    });

    HBox inputBox = new HBox(messageField, sendButton);

    Button exit = new Button("Exit");
    exit.setOnAction(e -> {
      Platform.exit();
    });
    exit.setMinSize(300, 40);

    VBox lineOne = new VBox(buttons, toggleButton_, createClient_);
    lineOne.setSpacing(2);

    VBox lineTwo = new VBox();
    createServerButtons(lineTwo);
    lineTwo.setSpacing(4);

    HBox userButtons = new HBox(lineOne, lineTwo);
    userButtons.setSpacing(2);

    VBox userInterface = new VBox(userButtons, logs_, inputBox, exit);
    userInterface.setStyle("-fx-background-color: rgba(100, 100, 100, 0.75);");
    userInterface.setVgrow(logs_, Priority.ALWAYS);
    userInterface.setSpacing(2);
    userInterface.setPadding(new Insets(4));
    userInterface.setMinHeight(HEIGHT_);

    try {
      root.setBackground(createBackground());
    } catch (Exception err) {
      err.printStackTrace();
    }

    EventHandler<MouseEvent> eventHandler = new EventHandler<MouseEvent>() {
      @Override
      public void handle(MouseEvent e) {
        double x = e.getX();
        double y = e.getY();

        for (CatImg item : images_) {
          if (item.contains(x, y)) {
            item.selectItem();
          }
        }

        for (CatText item : texts_) {
          if (item.contains(x, y)) {
            item.selectItem();
          }
        }
      }
    };
    view.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);
   
    root.getChildren().addAll(view, userInterface);
    Scene scene = new Scene(root, WIDTH_, HEIGHT_);
    rootStage.setScene(scene);
    rootStage.setTitle("Football Server");
    rootStage.show();
  }

  public void changeConnectionStatus() {
    this.isConnected_ = !this.isConnected_;

    if (this.isConnected_)
      toggleButton_.setText("Stop server");
    else
      toggleButton_.setText("Start server");
  }

  public void appendLog(String msg) {
    logs_.appendText(msg + "\n");
  }

  private void createServerButtons(VBox vbox) {
    Button closeConnect = new Button("Close connection");
    Button clearVectors = new Button("Clear vectors");
    Button sendObject = new Button("Send object");
    Button requestObject = new Button("Request object");
    Button sendList = new Button("Send list");
    Button requestSize = new Button("Request size");
    Button requestByIndex = new Button("Request by index");

    closeConnect.setMinSize(150, 25);
    clearVectors.setMinSize(150, 25);
    sendObject.setMinSize(150, 25);
    requestObject.setMinSize(150, 25);
    sendList.setMinSize(150, 25);
    requestSize.setMinSize(150, 25);
    requestByIndex.setMinSize(150, 25);

    vbox.getChildren().addAll(closeConnect, clearVectors, sendObject, requestObject, sendList, requestSize,
        requestByIndex);
  }

  private Background createBackground() throws FileNotFoundException {
    Image bgImg = new Image(new FileInputStream("/home/desolaye/dev/nstu-works/cs/home.png"));
    BackgroundSize bgSize = new BackgroundSize(WIDTH_, HEIGHT_, false, false, false, false);
    BackgroundImage bgImgView = new BackgroundImage(bgImg, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT,
        BackgroundPosition.CENTER, bgSize);
    Background bg = new Background(bgImgView);
    return bg;
  }

  private void sendMessage() {
    String msg = "Server: " + messageField.getText();
    appendLog(msg);

    serverSocket_.getWriter().println(msg);

    messageField.clear();
  }
}
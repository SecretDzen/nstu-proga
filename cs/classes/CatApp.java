package classes;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Vector;

import elements.*;
import ui.*;
import sockets.Middleware;

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
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class CatApp extends Application {
  private int WIDTH_;
  private int HEIGHT_;
  private boolean isServer_;
  private boolean isConnected_ = false;

  private Middleware socket_;

  private Vector<CatText> texts_;
  private Vector<CatImg> images_;

  private CommonButtons commonButtons_;
  private SpecialButtons specialButtons_;

  private Stage root_;
  private Pane ui_;
  private Group view_;
  private VBox userPanel_;
  private TextArea logs_;
  private TextField index_;
  private Button connectButton_;

  public CatApp(int w, int h, boolean isServer) {
    this.WIDTH_ = w;
    this.HEIGHT_ = h;
    this.isServer_ = isServer;
  }

  public CatApp(boolean isServer) {
    this.isServer_ = isServer;
  }

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage rootStage) {
    setupSocket();
    setupUI(rootStage);

    if (this.isServer_) {
      setTitle("Server");
    } else {
      setTitle("Client");
    }

    runScene();
  }

  public void setTitle(String msg) {
    this.root_.setTitle(msg);
  }

  public void appendLog(String msg) {
    logs_.appendText(msg + "\n");
  }

  public void handleCommand(String command) {
    if (command == "clear") {
      deleteVectors();
      this.socket_.sendCommand(command);
    } else if (command == "sendObject") {
      sendObject();
    } else if (command == "sendList") {
      sendList();
    } else if (command == "size") {
      sendSize();
    } else if (command == "indexI") {
      requestImage();
    } else if (command == "indexT") {
      requestText();
    } else {
      appendLog("Unknown command: " + command);
    }
  }

  public void deleteVectors() {
    this.commonButtons_.deleteAll(view_, images_, texts_);
  }

  public void sendObject() {
    for (CatImg item : images_) {
      if (item.isSelected()) {
        String command = "obj " + "img " + item.getX() + " " + item.getY();
        this.socket_.sendCommand(command);
      }
    }

    for (CatText item : texts_) {
      if (item.isSelected()) {
        String command = "obj " + "text " + item.getX() + " " + item.getY();
        this.socket_.sendCommand(command);
      }
    }
  }

  public void sendList() {
    int idx = 0;
    for (CatImg item : images_) {
      String command = "list " + idx + " img " + item.getX() + " " + item.getY();
      this.socket_.sendCommand(command);
      idx++;
    }

    idx = 0;
    for (CatText item : texts_) {
      String command = "list " + idx + " text " + item.getX() + " " + item.getY();
      this.socket_.sendCommand(command);
      idx++;
    }
  }

  public void sendSize() {
    String command = "size img " + images_.size();
    this.socket_.sendCommand(command);

    command = "size text " + texts_.size();
    this.socket_.sendCommand(command);
  }

  public void addObject(String command) {
    String[] byCommand = command.split(" ");

    if ("img".equals(byCommand[1])) {
      this.commonButtons_.createImg(this.view_, this.images_, Integer.parseInt(byCommand[2]),
          Integer.parseInt(byCommand[3]));
    }

    if ("text".equals(byCommand[1])) {
      this.commonButtons_.createText(this.view_, this.texts_, Integer.parseInt(byCommand[2]),
          Integer.parseInt(byCommand[3]));
    }
  }

  public void requestImage() {
    String idx = this.index_.getText();
    String command = "index img " + idx;
    this.socket_.sendCommand(command);
  }

  public void getByIndex(String command) {
    String[] byCommand = command.split(" ");
    String retCommand = "obj ";

    if ("img".equals(byCommand[1])) {
      retCommand += "img ";
      CatImg img = images_.get(Integer.parseInt(byCommand[2]));
      retCommand += img.getX() + " " + img.getY();
    }

    if ("text".equals(byCommand[1])) {
      retCommand += "text ";
      CatText text = texts_.get(Integer.parseInt(byCommand[2]));
      retCommand += text.getX() + " " + text.getY();
    }

    this.socket_.sendCommand(retCommand);
  }

  public void requestText() {
    String idx = this.index_.getText();
    String command = "index text " + idx;
    this.socket_.sendCommand(command);
  }

  private void setupSocket() {
    if (this.isServer_) {
      socket_ = new Middleware(true);
      socket_.addServer(this);
    } else {
      socket_ = new Middleware(false);
      socket_.addClient(this);
    }
    socket_.start();
  }

  private void setupUI(Stage rootStage) {
    this.root_ = rootStage;

    this.texts_ = new Vector<CatText>();
    this.images_ = new Vector<CatImg>();

    this.logs_ = new TextArea();
    this.logs_.setMaxWidth(300);
    this.logs_.setEditable(false);

    this.index_ = new TextField();
    this.index_.setMaxWidth(150);

    this.ui_ = new Pane();
    this.view_ = new Group();

    VBox common = new VBox();
    common.setSpacing(4);

    VBox special = new VBox();
    special.setSpacing(4);

    HBox userButtons = new HBox(common, special);
    userButtons.setSpacing(2);

    Button exit = new Button("Exit");
    exit.setOnAction(e -> {
      Platform.exit();
    });
    exit.setMinSize(300, 40);

    HBox socketButtons = new HBox();
    socketButtons.setSpacing(2);

    if (this.isServer_) {
      this.connectButton_ = new Button("Open socket");
      this.connectButton_.setMinSize(150, 25);
    } else {
      this.connectButton_ = new Button("Connect");
      this.connectButton_.setMinSize(300, 25);
    }

    this.connectButton_.setOnAction(e -> handleConnection());
    socketButtons.getChildren().add(this.connectButton_);

    if (this.isServer_) {
      Button createClient = new Button("Run client");
      createClient.setMinSize(150, 25);

      createClient.setOnAction(e -> {
        CatApp client = new CatApp(this.WIDTH_, this.HEIGHT_, false);
        client.start(new Stage());
      });

      socketButtons.getChildren().add(createClient);
    }

    this.commonButtons_ = new CommonButtons(this.WIDTH_, this.HEIGHT_, this.texts_, this.images_);
    this.commonButtons_.createClientButtons(this.view_, common);

    this.specialButtons_ = new SpecialButtons(this);
    this.specialButtons_.createServerButtons(special);
    special.getChildren().add(index_);

    this.userPanel_ = new VBox(exit, socketButtons, userButtons, logs_);
    this.userPanel_.setStyle("-fx-background-color: rgba(100, 100, 100, 0.75);");
    this.userPanel_.setSpacing(8);
    this.userPanel_.setPadding(new Insets(4));
    this.userPanel_.setMinHeight(this.HEIGHT_);

    this.ui_.getChildren().addAll(this.view_, this.userPanel_);

    try {
      this.ui_.setBackground(createBackground());
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

    view_.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);
  }

  private void runScene() {
    Scene scene = new Scene(this.ui_, this.WIDTH_, this.HEIGHT_);
    this.root_.setScene(scene);
    this.root_.show();
  }

  private void handleConnection() {
    if (isConnected_) {
      socket_.disconnect();
      handleStatusConnection();
    } else {
      socket_.connect();
      handleStatusConnection();
    }
  }

  private void handleStatusConnection() {
    this.isConnected_ = !this.isConnected_;

    if (this.isConnected_) {
      if (this.isServer_) {
        this.connectButton_.setText("Close socket");
      } else {
        this.connectButton_.setText("Disconnect");
      }
    } else {
      if (this.isServer_) {
        this.connectButton_.setText("Open socket");
      } else {
        this.connectButton_.setText("Connect");
      }
    }
  }

  private Background createBackground() throws FileNotFoundException {
    Image bgImg = new Image(new FileInputStream("/home/desolaye/dev/nstu-works/cs/home.png"));
    BackgroundSize bgSize = new BackgroundSize(this.WIDTH_, this.HEIGHT_, false, false, false, false);
    BackgroundImage bgImgView = new BackgroundImage(bgImg, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT,
        BackgroundPosition.CENTER, bgSize);
    Background bg = new Background(bgImgView);

    return bg;
  }

}

package ui;

import classes.CatApp;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;

public class SpecialButtons {
  private CatApp app_;

  public SpecialButtons(CatApp app) {
    this.app_ = app;
  }

  public void createServerButtons(VBox vbox) {
    Button clearVectors = new Button("Clear vectors");
    Button sendObject = new Button("Send object");
    Button sendList = new Button("Send list");
    Button requestSize = new Button("Request size");
    Button requestImage = new Button("Request Img by index");
    Button requestText = new Button("Request Text by index");

    clearVectors.setMinSize(150, 25);
    sendObject.setMinSize(150, 25);
    sendList.setMinSize(150, 25);
    requestSize.setMinSize(150, 25);
    requestImage.setMinSize(150, 25);
    requestText.setMinSize(150, 25);

    clearVectors.setOnAction(e -> this.app_.handleCommand("clear"));
    sendObject.setOnAction(e -> this.app_.handleCommand("sendObject"));
    sendList.setOnAction(e -> this.app_.handleCommand("sendList"));
    requestSize.setOnAction(e -> this.app_.handleCommand("size"));
    requestImage.setOnAction(e -> this.app_.handleCommand("indexI"));
    requestText.setOnAction(e -> this.app_.handleCommand("indexT"));

    vbox.getChildren().addAll(clearVectors, sendObject, sendList, requestSize, requestImage, requestText);
  }

}

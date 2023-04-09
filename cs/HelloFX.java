import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;
import java.util.Vector;

public class HelloFX extends Application {
  final int WIDTH = 900;
  final int HEIGHT = 600;
  Vector<CatText> texts;
  Vector<CatImg> images;

  @Override
  public void start(Stage stage) throws IOException {
    Pane root = new Pane();
    Scene scene = new Scene(root, WIDTH, HEIGHT);
    HBox sceneBox = new HBox();
    Group view = new Group();

    VBox userVbox = new VBox();
    VBox serverVbox = new VBox();
    Insets vboxInsets = new Insets(6, 6, 6, 6);

    sceneBox.setPrefSize(WIDTH, HEIGHT);

    userVbox.setPadding(vboxInsets);
    userVbox.setSpacing(6);
    userVbox.setMaxSize(210, HEIGHT);
    userVbox.setStyle("-fx-background-color: #777");

    serverVbox.setPadding(vboxInsets);
    serverVbox.setSpacing(6);
    serverVbox.setMaxSize(210, HEIGHT);
    serverVbox.setStyle("-fx-background-color: #777");
    serverVbox.setAlignment(Pos.BASELINE_RIGHT);

    this.texts = new Vector<>();
    this.images = new Vector<>();

    createClientButtons(view, userVbox);

    var spacer = new Region();
    spacer.setPrefHeight(40);
    userVbox.getChildren().add(spacer);
    userVbox.setAlignment(Pos.BASELINE_LEFT);

    createSettingButtons(userVbox);
    createServerButtons(serverVbox);

    EventHandler<MouseEvent> eventHandler = new EventHandler<MouseEvent>() {
      @Override
      public void handle(MouseEvent e) {
        double x = e.getX();
        double y = e.getY();

        for (CatImg item : images) {
          if (item.contains(x, y)) {
            item.selectItem();
          }
        }

        for (CatText item : texts) {
          if (item.contains(x, y)) {
            item.selectItem();
          }
        }
      }
    };

    view.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);


    var sceneSpacer = new Region();
    sceneSpacer.setPrefSize(682, HEIGHT);
    sceneBox.getChildren().addAll(userVbox, sceneSpacer, serverVbox);

    root.setBackground(createBackground());
    root.getChildren().addAll(sceneBox, view);

    stage.setTitle("lab 1");
    stage.setScene(scene);
    stage.show();
  }

  private void createClientButtons(Group view, VBox vbox) {
    Button btnText = new Button("Create Text");
    Button btnImg = new Button("Create Image");
    Button btnDeleteAll = new Button("Delete All");
    Button btnStopAll = new Button("Stop All");
    Button btnStartAll = new Button("Start All");
    Button btnStart = new Button("Start Selected");
    Button btnDelete = new Button("Delete Selected");
    Button btnStop = new Button("Stop Selected");

    btnText.setMaxSize(150, 200);
    btnImg.setMaxSize(150, 200);
    btnDeleteAll.setMaxSize(150, 200);
    btnStopAll.setMaxSize(150, 200);
    btnStartAll.setMaxSize(150, 200);
    btnStart.setMaxSize(150, 200);
    btnStop.setMaxSize(150, 200);
    btnDelete.setMaxSize(150, 200);

    vbox.getChildren().addAll(btnImg, btnText, btnDeleteAll, btnStopAll, btnStartAll, btnDelete, btnStop, btnStart);

    btnText.setOnAction(e -> {
      Random random = new Random();
      CatText catText = new CatText(random.nextInt(WIDTH - 350) + 125, random.nextInt(HEIGHT - 175) + 50,
          Color.CRIMSON);
      texts.add(catText);
      view.getChildren().add(catText.getElement());
    });

    btnImg.setOnAction(e -> {
      try {
        Random random = new Random();
        CatImg catImg = new CatImg(random.nextInt(WIDTH - 325) + 125, random.nextInt(HEIGHT - 175) + 50);
        images.add(catImg);
        view.getChildren().add(catImg.getElement());
      } catch (FileNotFoundException err) {
        System.out.println(err);
      }
    });

    btnDeleteAll.setOnAction(e -> {
      for (CatImg item : images) {
        view.getChildren().remove(item.getElement());
      }
      images.clear();

      for (CatText item : texts) {
        view.getChildren().remove(item.getElement());
      }
      texts.clear();
    });

    btnStopAll.setOnAction(e -> {
      for (CatImg item : images)
        item.stopAnimation();

      for (CatText item : texts)
        item.stopAnimation();
    });

    btnStartAll.setOnAction(e -> {
      for (CatImg item : images)
        item.startAnimation();

      for (CatText item : texts)
        item.startAnimation();
    });

    btnDelete.setOnAction(e -> {
      boolean clear = false;

      while (!clear) {
        boolean broken = false;

        for (CatImg item : images) {
          if (item.isSelected()) {
            view.getChildren().remove(item.getElement());
            images.remove(item);
            broken = true;
            break;
          }
        }

        if (!broken) {
          clear = true;
        }
      }

      clear = false;

      while (!clear) {
        boolean broken = false;

        for (CatText item : texts) {
          if (item.isSelected()) {
            view.getChildren().remove(item.getElement());
            texts.remove(item);
            broken = true;
            break;
          }
        }

        if (!broken) {
          clear = true;
        }
      }

    });

    btnStop.setOnAction(e -> {
      for (CatImg item : images) {
        if (item.isSelected()) {
          item.stopAnimation();
        }
      }

      for (CatText item : texts) {
        if (item.isSelected()) {
          item.stopAnimation();
        }
      }
    });

    btnStart.setOnAction(e -> {
      for (CatImg item : images) {
        if (item.isSelected()) {
          item.startAnimation();
        }
      }

      for (CatText item : texts) {
        if (item.isSelected()) {
          item.startAnimation();
        }
      }
    });
  }

  private void createSettingButtons(VBox vbox) {
    Button quitProgram = new Button("Exit");
    quitProgram.setMaxSize(150, 200);
    vbox.getChildren().add(quitProgram);

    quitProgram.setOnAction(e -> {
      Platform.exit();
    });

  }

  private void createServerButtons(VBox vbox) {
    Button startServer = new Button("Start Server");

    vbox.getChildren().add(startServer);
  }

  private Background createBackground() throws FileNotFoundException {
    Image bgImg = new Image(new FileInputStream("/home/desolaye/dev/nstu-works/cs/home.png"));
    BackgroundSize bgSize = new BackgroundSize(WIDTH, HEIGHT, false, false, false, false);
    BackgroundImage bgImgView = new BackgroundImage(bgImg, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT,
        BackgroundPosition.CENTER, bgSize);
    Background bg = new Background(bgImgView);
    return bg;
  }

  public static void main(String[] args) {
    launch();
  }
}
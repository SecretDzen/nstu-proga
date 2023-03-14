import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

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
    Group view = new Group();
    HBox hbox = new HBox();

    this.texts = new Vector<>();
    this.images = new Vector<>();

    createButtons(view, hbox);
    root.getChildren().add(hbox);

    EventHandler<MouseEvent> eventHandler = new EventHandler<MouseEvent>() {
      @Override
      public void handle(MouseEvent e) {
        double x = e.getSceneX();
        double y = e.getSceneY();

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

    root.getChildren().add(view);
    stage.setTitle("lab 1");
    stage.setScene(scene);
    stage.show();
  }

  private void createButtons(Group view, HBox hbox) {
    Button btnText = new Button("Create Text");
    Button btnImg = new Button("Create Image");
    Button btnDeleteAll = new Button("Delete All");
    Button btnStopAll = new Button("Stop All");
    Button btnStartAll = new Button("Start All");
    Button btnStart = new Button("Start Element");
    Button btnDelete = new Button("Delete Element");
    Button btnStop = new Button("Stop Element");
    hbox.getChildren().addAll(btnImg, btnText, btnDeleteAll, btnStopAll, btnStartAll, btnDelete, btnStop, btnStart);

    btnText.setOnAction(e -> {
      Random random = new Random();
      CatText catText = new CatText(random.nextInt(WIDTH - 150) + 75, random.nextInt(HEIGHT - 150) + 75, Color.BROWN);
      texts.add(catText);
      view.getChildren().add(catText.getElement());
    });

    btnImg.setOnAction(e -> {
      try {
        Random random = new Random();
        CatImg catImg = new CatImg(random.nextInt(WIDTH - 150) + 75, random.nextInt(HEIGHT - 150) + 75);
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
      for (CatImg item : images) {
        item.stopAnimation();
      }
      for (CatText item : texts) {
        item.stopAnimation();
      }
    });

    btnStartAll.setOnAction(e -> {
      for (CatImg item : images) {
        item.startAnimation();
      }
      for (CatText item : texts) {
        item.startAnimation();
      }
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

    btnStop.setOnAction(e ->

    {
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

  public static void main(String[] args) {
    launch();
  }
}
package ui;

import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Vector;

import elements.*;
import javafx.scene.Group;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;

public class CommonButtons {
  final int WIDTH_;
  final int HEIGHT_;
  Vector<CatText> texts_;
  Vector<CatImg> images_;

  public CommonButtons(int w, int h, Vector<CatText> texts, Vector<CatImg> images) {
    this.WIDTH_ = w;
    this.HEIGHT_ = h;
    this.texts_ = texts;
    this.images_ = images;
  }

  public void createClientButtons(Group view, VBox vbox) {
    Button btnText = new Button("Create Text");
    Button btnImg = new Button("Create Image");
    Button btnDeleteAll = new Button("Delete All");
    Button btnStopAll = new Button("Stop All");
    Button btnStartAll = new Button("Start All");
    Button btnStart = new Button("Start Selected");
    Button btnDelete = new Button("Delete Selected");
    Button btnStop = new Button("Stop Selected");

    btnText.setMinSize(150, 25);
    btnImg.setMinSize(150, 25);
    btnDeleteAll.setMinSize(150, 25);
    btnStopAll.setMinSize(150, 25);
    btnStartAll.setMinSize(150, 25);
    btnStart.setMinSize(150, 25);
    btnStop.setMinSize(150, 25);
    btnDelete.setMinSize(150, 25);

    vbox.getChildren().addAll(btnImg, btnText, btnDeleteAll, btnStopAll, btnStartAll, btnDelete, btnStop, btnStart);

    btnText.setOnAction(e -> {
      Random random = new Random();
      CatText catText = new CatText(random.nextInt(WIDTH_ - 450) + 320, random.nextInt(HEIGHT_ - 175) + 50,
          Color.CRIMSON);
      texts_.add(catText);
      view.getChildren().add(catText.getElement());
    });

    btnImg.setOnAction(e -> {
      try {
        Random random = new Random();
        CatImg catImg = new CatImg(random.nextInt(WIDTH_ - 425) + 320, random.nextInt(HEIGHT_ - 175) + 50);
        images_.add(catImg);
        view.getChildren().add(catImg.getElement());
      } catch (FileNotFoundException err) {
        System.out.println(err);
      }
    });

    btnDeleteAll.setOnAction(e -> {
      for (CatImg item : images_) {
        view.getChildren().remove(item.getElement());
      }
      images_.clear();

      for (CatText item : texts_) {
        view.getChildren().remove(item.getElement());
      }
      texts_.clear();
    });

    btnStopAll.setOnAction(e -> {
      for (CatImg item : images_)
        item.stopAnimation();

      for (CatText item : texts_)
        item.stopAnimation();
    });

    btnStartAll.setOnAction(e -> {
      for (CatImg item : images_)
        item.startAnimation();

      for (CatText item : texts_)
        item.startAnimation();
    });

    btnDelete.setOnAction(e -> {
      boolean clear = false;

      while (!clear) {
        boolean broken = false;

        for (CatImg item : images_) {
          if (item.isSelected()) {
            view.getChildren().remove(item.getElement());
            images_.remove(item);
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

        for (CatText item : texts_) {
          if (item.isSelected()) {
            view.getChildren().remove(item.getElement());
            texts_.remove(item);
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
      for (CatImg item : images_) {
        if (item.isSelected()) {
          item.stopAnimation();
        }
      }

      for (CatText item : texts_) {
        if (item.isSelected()) {
          item.stopAnimation();
        }
      }
    });

    btnStart.setOnAction(e -> {
      for (CatImg item : images_) {
        if (item.isSelected()) {
          item.startAnimation();
        }
      }

      for (CatText item : texts_) {
        if (item.isSelected()) {
          item.startAnimation();
        }
      }
    });
  }

}

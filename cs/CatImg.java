import java.io.FileInputStream;
import java.io.FileNotFoundException;

import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.util.Duration;

public class CatImg {
  private Image img;
  private ImageView imgView;
  private BorderPane bpane;
  private Timeline timeline;
  private boolean selected = false;

  public CatImg(int x, int y) throws FileNotFoundException {
    this.img = new Image(new FileInputStream("/home/ex4to/dev/nstu-works/cs/cat.png"));
    this.imgView = new ImageView(this.img);
    imgView.setFitWidth(100);
    imgView.setPreserveRatio(true);

    this.bpane = new BorderPane(imgView);
    this.bpane.setCenter(imgView);
    this.bpane.setLayoutX(x);
    this.bpane.setLayoutY(y);

    setupAnimation();
  }

  public BorderPane getElement() {
    return bpane;
  }

  public boolean isSelected() {
    return this.selected;
  }

  public void startAnimation() {
    this.timeline.play();
  }

  public void stopAnimation() {
    this.timeline.pause();
  }

  public boolean contains(double x, double y) {
    return this.bpane.getBoundsInParent().contains(x, y);
  }

  public void selectItem() {
    this.selected = !this.selected;

    if (this.selected) {
      this.bpane.setStyle("-fx-border-color: black;");
    } else {
      this.bpane.setStyle("-fx-border-color: none;");
    }
  }

  private void setupAnimation() {
    KeyValue initRotate = new KeyValue(this.bpane.rotateProperty(), 0);
    KeyFrame initFrame = new KeyFrame(Duration.ZERO, initRotate);
    KeyValue endRotate = new KeyValue(this.bpane.rotateProperty(), 360);
    KeyFrame endFrame = new KeyFrame(Duration.seconds(5), endRotate);

    this.timeline = new Timeline(initFrame, endFrame);
    this.timeline.setCycleCount(Timeline.INDEFINITE);
    startAnimation();
  }
}

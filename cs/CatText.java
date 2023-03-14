import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;
import javafx.util.Duration;

public class CatText {
  private Label label;
  private BorderPane bpane;
  private Timeline timeline;
  private boolean selected = false;

  public CatText(int x, int y, Color color) {

    this.label = new Label("Meow");
    this.label.setTextAlignment(TextAlignment.CENTER);
    this.label.setFont(Font.font(24));
    this.label.setTextFill(color);

    this.bpane = new BorderPane(label);
    this.bpane.setLayoutX(x);
    this.bpane.setLayoutY(y);

    setupAnimation();
  }

  public BorderPane getElement() {
    return bpane;
  }

  public boolean contains(double x, double y) {
    return this.bpane.getBoundsInParent().contains(x, y);
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

  public void selectItem() {
    this.selected = !this.selected;

    if (this.selected) {
      this.bpane.setStyle("-fx-border-color: black;");
    } else {
      this.bpane.setStyle("-fx-border-color: none;");
    }
  }

  private void setupAnimation() {
    KeyValue initXValue = new KeyValue(this.bpane.translateXProperty(), 0);
    KeyValue initYValue = new KeyValue(this.bpane.translateYProperty(), 0);
    KeyFrame initFrame = new KeyFrame(Duration.ZERO, initXValue, initYValue);

    KeyValue topLeftXValue = new KeyValue(this.bpane.translateXProperty(), 50);
    KeyValue topLeftYValue = new KeyValue(this.bpane.translateYProperty(), 0);
    KeyFrame topLeftFrame = new KeyFrame(Duration.seconds(1), topLeftXValue, topLeftYValue);

    KeyValue bottomLeftXValue = new KeyValue(this.bpane.translateXProperty(), 50);
    KeyValue bottomLeftYValue = new KeyValue(this.bpane.translateYProperty(), 50);
    KeyFrame bottomLeftFrame = new KeyFrame(Duration.seconds(2), bottomLeftXValue, bottomLeftYValue);

    KeyValue bottomRightXValue = new KeyValue(this.bpane.translateXProperty(), 0);
    KeyValue bottomRightYValue = new KeyValue(this.bpane.translateYProperty(), 50);
    KeyFrame bottomRightFrame = new KeyFrame(Duration.seconds(3), bottomRightXValue, bottomRightYValue);
    KeyFrame endFrame = new KeyFrame(Duration.seconds(4), initXValue, initYValue);

    this.timeline = new Timeline(initFrame, topLeftFrame, bottomLeftFrame, bottomRightFrame, endFrame);
    this.timeline.setCycleCount(Timeline.INDEFINITE);
    startAnimation();
  }
}

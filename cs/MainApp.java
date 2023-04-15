import classes.CatApp;
import javafx.application.Application;
import javafx.stage.Stage;

public class MainApp extends Application {
  private final int WIDTH_ = 900;
  private final int HEIGHT_ = 600;

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage root) {
    new CatApp(this.WIDTH_, this.HEIGHT_, true, true).start(new Stage());
  }
}

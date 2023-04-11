import javafx.application.Application;
import javafx.stage.Stage;
import sockets.Server;

public class MainApp extends Application {
  private Server server_;
  private final int WIDTH_ = 900;
  private final int HEIGHT_ = 600;
  
  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage root) {
    server_ = new Server(WIDTH_, HEIGHT_);
    server_.start(new Stage());
  }

}

package com.labscs;

import java.util.Scanner;

import javafx.application.Application;
import javafx.stage.Stage;

public class App extends Application {

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage root) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Available commands:");
    System.out.println("1) Run a server");
    System.out.println("2) Run a client");

    String command = scanner.nextLine();
    scanner.close();

    if ("1".equals(command)) {
      System.out.println("Starting server...");
      new AppServer().run();
    } else {
      System.out.println("Starting client...");
      new AppClient().start(new Stage());
    }
  }
}

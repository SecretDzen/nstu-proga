package sockets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import classes.CatApp;
import javafx.application.Platform;
import javafx.stage.Stage;

public class Middleware extends Thread {
  private final int PORT_ = 5000;
  private final String HOST_ = "localhost";

  private boolean isServer_;

  private ServerSocket serverSocket_;
  private Socket clientSocket_;
  private CatApp server_;
  private CatApp client_;

  private PrintWriter out_;
  private BufferedReader in_;

  public Middleware(boolean isServer) {
    this.isServer_ = isServer;
  }

  public Middleware(boolean isServer, CatApp client, CatApp server) {
    this.isServer_ = isServer;
    this.client_ = client;
    this.server_ = server;
  }

  @Override
  public void run() {
  }

  public void connect() {
    if (isServer_) {
      connectServer();
    } else {
      connectClient();
    }
  }

  private void connectServer() {
    try {
      runSocket();

      new Thread(() -> {
        while (true) {
          try {
            clientSocket_ = serverSocket_.accept();
            if (clientSocket_ == null)
              break;

            InputStream inStream = clientSocket_.getInputStream();
            OutputStream outStream = clientSocket_.getOutputStream();

            out_ = new PrintWriter(outStream, true);
            in_ = new BufferedReader(new InputStreamReader(inStream));

            this.server_.appendLog("Client connected");
            handleEvents();
          } catch (Exception err) {
            if (serverSocket_ != null && !serverSocket_.isClosed()) {
              System.out.println("=== Error in Middleware.connectServer() ===\n");
              err.printStackTrace();
            }
            break;
          }
        }
      }).start();

    } catch (Exception err) {
      System.out.println("=== Error in Middleware.connectServer() ===\n");
      err.printStackTrace();
    }

  }

  private void connectClient() {
    try {
      runSocket();

      new Thread(() -> {
        try {
          InputStream inStream = clientSocket_.getInputStream();
          OutputStream outStream = clientSocket_.getOutputStream();

          out_ = new PrintWriter(outStream, true);
          in_ = new BufferedReader(new InputStreamReader(inStream));
          handleEvents();
        } catch (Exception err) {
          System.out.println("=== Error in Middleware.connectClient() ===\n");
          err.printStackTrace();
        }
      }).start();

    } catch (Exception err) {
      if (("Connection refused").equals(err.getMessage())) {
        this.client_.appendLog("Error: " + err.getMessage());
      } else {
        System.out.println("=== Error in Middleware.connect() ===\n");
        err.printStackTrace();
      }
    }

  }

  public void runSocket() throws Exception {
    try {
      if (isServer_) {
        serverSocket_ = new ServerSocket(PORT_);
        this.server_.appendLog("Server started");
      } else {
        clientSocket_ = new Socket(HOST_, PORT_);
        this.client_.appendLog("Client created");
      }
    } catch (Exception err) {
      throw new Exception(err.getMessage());
    }
  }

  public void addServer(CatApp server) {
    this.server_ = server;
  }

  public void addClient(CatApp client) {
    this.client_ = client;
  }

  private void handleEvents() {
    while (true) {
      try {
        String msg = in_.readLine();
        if (msg == null)
          break;

        if (this.server_ != null) {
          handleCommand(msg);
          this.server_.appendLog("Client: " + msg);
        }

        if (this.client_ != null) {
          handleCommand(msg);
          this.client_.appendLog("Server: " + msg);
        }

      } catch (Exception err) {
        System.out.println("=== Error in Middleware.handleEvents() ===\n");
        err.printStackTrace();
      }
    }
  }

  private void handleCommand(String command) {
    Platform.runLater(new Runnable() {
      @Override
      public void run() {
        String[] byCommand = command.split(" ");

        if (server_ != null) {
          if ("clear".equals(byCommand[0])) {
            server_.deleteVectors();
          } else if ("obj".equals(byCommand[0])) {
            server_.addObject(command);
          } else if ("list".equals(byCommand[0])) {
          } else if ("size".equals(byCommand[0])) {
          } else if ("index".equals(byCommand[0])) {
            server_.getByIndex(command);
          }
        }

        if (client_ != null) {
          if ("clear".equals(byCommand[0])) {
            client_.deleteVectors();
          } else if ("obj".equals(byCommand[0])) {
            client_.addObject(command);
          } else if ("list".equals(byCommand[0])) {
          } else if ("size".equals(byCommand[0])) {
          } else if ("index".equals(byCommand[0])) {
            client_.getByIndex(command);
          }
        }

      }
    });
  }

  public void disconnect() {
    try {
      if (clientSocket_ != null) {
        clientSocket_.close();
        clientSocket_ = null;
        this.client_.appendLog("Disconnected from server");
      }

      if (serverSocket_ != null) {
        serverSocket_.close();
        serverSocket_ = null;
        this.server_.appendLog("Server stopped");
      }
    } catch (IOException err) {
      System.out.println("=== Error in Middleware.disconnect() ===\n");
      err.printStackTrace();
    }
  }

  public PrintWriter getWriter() {
    return this.out_;
  }

  public void sendCommand(String msg) {
    this.out_.println(msg);
  }

  public void runClient() {
    this.client_.start(new Stage());
  }

}

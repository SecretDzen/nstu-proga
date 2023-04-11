package football;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import javafx.stage.Stage;

public class Middleware extends Thread {
  private final int PORT_ = 5000;
  private final String HOST_ = "localhost";

  private boolean isServer_;

  private ServerSocket serverSocket_;
  private Server server_;
  private Client client_;
  private Socket clientSocket_;

  private PrintWriter out_;
  private BufferedReader in_;

  public Middleware(boolean isServer) {
    this.isServer_ = isServer;
  }

  public Middleware(boolean isServer, Client client, Server server) {
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
  }

  private void connectClient() {
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
  }

  public void runSocket() {
    try {
      if (isServer_) {
        serverSocket_ = new ServerSocket(PORT_);
        this.server_.appendLog("Server started");
      } else {
        clientSocket_ = new Socket(HOST_, PORT_);
        this.client_.appendLog("Client created");
      }
    } catch (Exception err) {
      System.out.println("=== Error in Middleware.connect() ===\n");
      err.printStackTrace();
    }
  }

  public void addServer(Server server) {
    this.server_ = server;
  }

  public void addClient(Client client) {
    this.client_ = client;
  }

  private void handleEvents() {
    while (true) {
      try {
        String msg = in_.readLine();
        if (msg == null)
          break;

        if (this.server_ != null)
          this.server_.appendLog(msg);

        if (this.client_ != null)
          this.client_.appendLog(msg);

      } catch (Exception err) {
        System.out.println("=== Error in Middleware.handleEvents() ===\n");
        err.printStackTrace();
      }
    }
  }

  public void disconnect() {
    try {
      if (clientSocket_ != null) {
        clientSocket_.close();
        clientSocket_ = null;
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
    return out_;
  }

  public void runClient() {
    client_.start(new Stage());
  }

}

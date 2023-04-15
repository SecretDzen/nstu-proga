package sockets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.net.*;

import classes.CatApp;
import javafx.application.Platform;
import javafx.stage.Stage;

public class Middleware extends Thread {
  private final int PORT_ = 5000;
  private final String HOST_ = "localhost";

  private boolean isServer_;
  private boolean isUDP_;

  private ServerSocket serverSocket_;
  private Socket clientSocket_;
  private CatApp server_;
  private CatApp client_;

  DatagramSocket socketUDP_;
  InetAddress IPAddr_;
  int sendPort_;
  byte[] receiveData_;
  byte[] sendData_;

  private PrintWriter out_;
  private BufferedReader in_;

  public Middleware(boolean isServer, boolean isUDP) {
    this.isServer_ = isServer;
    this.isUDP_ = isUDP;
  }

  public Middleware(boolean isServer, boolean isUDP, CatApp client, CatApp server) {
    this.isServer_ = isServer;
    this.isUDP_ = isUDP;
    this.client_ = client;
    this.server_ = server;
  }

  @Override
  public void run() {
  }

  public void connect() {
    if (this.isUDP_) {
      connectUDP();
    } else {
      if (isServer_) {
        connectServer();
      } else {
        connectClient();
      }
    }
  }

  public void runSocket() throws Exception {
    if (this.isUDP_) {
      runSocketUDP();
    } else {
      runSocketTCP();
    }
  }

  public void addServer(CatApp server) {
    this.server_ = server;
  }

  public void addClient(CatApp client) {
    this.client_ = client;
  }

  public void disconnect() {
    if (this.isUDP_) {
      disconnectUDP();
    } else {
      disconnectTCP();
    }
  }

  public void sendCommand(String msg) {
    if (this.isUDP_) {
      msg += " ";
      try {
        this.sendData_ = msg.getBytes();
        DatagramPacket sendPacket;
        if (this.isServer_) {
          sendPacket = new DatagramPacket(sendData_, sendData_.length, this.IPAddr_, this.sendPort_);
        } else {
          sendPacket = new DatagramPacket(sendData_, sendData_.length, this.IPAddr_, PORT_);
        }
        socketUDP_.send(sendPacket);
      } catch (Exception err) {
        err.printStackTrace();
      }
    } else {
      this.out_.println(msg);
    }
  }

  public void runClient() {
    this.client_.start(new Stage());
  }

  private void connectUDP() {
    try {
      runSocket();

      new Thread(() -> {
        try {
          while (true) {
            this.receiveData_ = new byte[1024];
            this.sendData_ = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData_, receiveData_.length);

            socketUDP_.receive(receivePacket);
            if (this.isServer_) {
              this.IPAddr_ = receivePacket.getAddress();
              this.sendPort_ = receivePacket.getPort();
            }
            String sentence = new String(receivePacket.getData(), StandardCharsets.UTF_8);
            handleCommand(sentence);
          }
        } catch (IOException err) {
          err.printStackTrace();
          disconnect();
        }
      }).start();
    } catch (Exception err) {
      err.printStackTrace();
    }
  }

  private void runSocketTCP() throws Exception {
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

  private void runSocketUDP() throws Exception {
    try {
      if (this.isServer_) {
        this.socketUDP_ = new DatagramSocket(PORT_);
        this.server_.appendLog("Server started");
      } else {
        this.socketUDP_ = new DatagramSocket();
        this.IPAddr_ = InetAddress.getByName(HOST_);
        socketUDP_.connect(IPAddr_, PORT_);
        this.client_.appendLog("Client created");
      }
    } catch (Exception err) {
      err.printStackTrace();
    }
  }

  private void disconnectUDP() {
    try {
      if (socketUDP_ != null) {
        socketUDP_.close();
        socketUDP_ = null;
      }

      if (this.client_ != null)
        this.client_.appendLog("Client stopped");
      if (this.server_ != null)
        this.server_.appendLog("Server stopped");

    } catch (Exception err) {
      System.out.println("=== Error in Middleware.disconnect() ===\n");
      err.printStackTrace();
    }
  }

  private void disconnectTCP() {
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

  private void handleEvents() {
    while (true) {
      try {
        String msg = in_.readLine();
        if (msg == null)
          break;

        if (this.server_ != null)
          handleCommand(msg);

        if (this.client_ != null)
          handleCommand(msg);

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
          } else if ("connect".equals(byCommand[0])) {

          }
          server_.appendLog("Client: " + command);
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
          client_.appendLog("Server: " + command);
        }

      }
    });
  }
}

package football;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Middleware extends Thread {
  private final int PORT_ = 5000;
  private final String HOST_ = "localhost";

  private boolean isServer_;
  private boolean isConnected_;

  private ServerSocket serverSocket_;
  private Server server_;
  private Socket clientSocket_;

  private PrintWriter out_;
  private BufferedReader in_;

  public Middleware() {
    this.isServer_ = false;
  }

  public Middleware(Socket socket, Server server) {
    this.isServer_ = true;
    this.clientSocket_ = socket;
    this.server_ = server;
  }

  @Override
  public void run() {
    try {
      this.out_ = new PrintWriter(this.clientSocket_.getOutputStream(), true);
      this.in_ = new BufferedReader(new InputStreamReader(this.clientSocket_.getInputStream()));
      this.isConnected_ = true;
      this.server_.appendLog("New Client connected\n");

      while (true) {
        String message = in_.readLine();
        if (message == null)
          break;
        broadcastMessage(message);
      }
    } catch (IOException err) {
      if (this.isConnected_) {
        System.err.println("Error handling client: " + err.getMessage());
      }
    } finally {
      disconnect();
    }
  }

  public void broadcastMessage(String msg) {
    this.server_.broadcastMessage("Client: " + msg + "\n");
  }

  public void disconnect() {
    try {
      clientSocket_.close();
      this.isConnected_ = false;
      this.server_.clients_.remove(this);
      this.server_.broadcastMessage("Client disconnected\n");
    } catch (IOException err) {
      System.err.println("Error disconnecting client: " + err.getMessage());
    }
  }

  public Socket accept() {
    try {
      return serverSocket_.accept();
    } catch (Exception err) {
      System.err.println("Error accepting client: " + err.getMessage());
    }
    return null;
  }

  public Socket getClientSocket() {
    return clientSocket_;
  }

  public ServerSocket getServerSocket() {
    return serverSocket_;
  }

  public BufferedReader getReader() {
    return in_;
  }

  public PrintWriter getWriter() {
    return out_;
  }

  public int manageConnection() {
    if (isServer_) {
      return handleServer();
    } else {
      return handleClient();
    }
  }

  private int handleServer() {
    return (serverSocket_ == null) ? serverCreate() : serverDestroy();
  }

  private int serverCreate() {
    try {
      serverSocket_ = new ServerSocket(PORT_);

      return 3;
    } catch (Exception err) {
      System.err.println("Error starting server: " + err.getMessage());
      return -3;
    }
  }

  private int serverDestroy() {
    try {
      serverSocket_.close();
      serverSocket_ = null;
      return 4;
    } catch (Exception err) {
      System.err.println("Error stopping server: " + err.getMessage());
      return -4;
    }
  }

  private int handleClient() {
    return (clientSocket_ == null) ? clientCreate() : clientDestroy();
  }

  private int clientCreate() {
    try {
      clientSocket_ = new Socket(HOST_, PORT_);
      out_ = new PrintWriter(clientSocket_.getOutputStream(), true);
      in_ = new BufferedReader(new InputStreamReader(clientSocket_.getInputStream()));

      return 1;
    } catch (Exception err) {
      System.err.println("Error receiving message: " + err.getMessage());
      return -1;
    }
  }

  private int clientDestroy() {
    try {
      clientSocket_.close();
      clientSocket_ = null;
      out_.close();
      in_.close();
      return 2;
    } catch (Exception err) {
      System.err.println("Error disconnecting from server: " + err.getMessage());
      return -2;
    }
  }

}

package sparkServ;

import spark.Spark;

public class SparkServer {
  public static void main(String[] args) {
    Spark.port(4545);
    Spark.get("/hello", (req, res) -> "Hello world!");
  }
}

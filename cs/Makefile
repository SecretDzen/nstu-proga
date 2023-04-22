PATH_TO_FX=/lib64/javafx-sdk-20/lib
PATH_TO_SPARK=lib/spark-2.9.4.jar
PATH_TO_SLF4J=lib/slf4j-api-2.0.7.jar
PATH_TO_SLF4J_SIMPLE=lib/slf4j-simple-2.0.7.jar
PATH_TO_JETTY=/lib64/jetty-home-11.0.14/lib

all: clear
	@echo "Compile java files..."
	@javac --module-path $(PATH_TO_FX) --add-modules javafx.controls MainApp.java
	@echo "Trying to run a program..."
	@java --module-path $(PATH_TO_FX) --add-modules javafx.controls MainApp

clear:
	@echo "Removing classes..."
	@rm -rf ./*.class
	@rm -rf ./**/*.class

spark: clear
	@echo "Compile java files..."
# @javac --module-path $(PATH_TO_LIB) --add-modules spark SparkApp.java
	@javac -cp .:$(PATH_TO_SPARK):$(PATH_TO_SLF4J):$(PATH_TO_SLF4J_SIMPLE)\
	:/lib64/jetty-home-11.0.14/lib/websockets/websocket-servlet-11.0.14.jar \
	MyApp.java

	@echo "Trying to run a program..."
# @java --module-path $(PATH_TO_LIB) --add-modules spark SparkApp
	@java -cp .:$(PATH_TO_SPARK):$(PATH_TO_SLF4J):$(PATH_TO_SLF4J_SIMPLE)\
	:/lib64/jetty-home-11.0.14/lib/websockets/websocket-servlet-11.0.14.jar \
	MyApp

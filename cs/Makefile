PATH_TO_FX=/lib64/javafx-sdk-20/lib

all: clear
	@echo "Compile java files..."
	@javac --module-path $(PATH_TO_FX) --add-modules javafx.controls HelloFX.java CatText.java CatImg.java AbstractClass.java
	@echo "Trying to run a program..."
	@java --module-path $(PATH_TO_FX) --add-modules javafx.controls HelloFX
	@echo "Removing classes..."

football: clear
	@echo "Compile java files..."
	@javac -d . --module-path $(PATH_TO_FX) --add-modules javafx.controls football/Server.java football/Client.java
	@echo "Trying to run a program..."
	@java --module-path $(PATH_TO_FX) --add-modules javafx.controls football.Server

clear:
	@echo "Removing classes..."
	@rm -rf *.class
	@rm -rf football/*.class

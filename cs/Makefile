PATH_TO_FX=/lib64/javafx-sdk-20/lib

all: clear
	@echo "Compile java files..."
	@javac --module-path $(PATH_TO_FX) --add-modules javafx.controls MainApp.java
	@echo "Trying to run a program..."
	@java --module-path $(PATH_TO_FX) --add-modules javafx.controls MainApp

clear:
	@echo "Removing classes..."
	@rm -rf ./*.class
	@rm -rf ./**/*.class

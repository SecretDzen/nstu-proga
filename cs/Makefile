PATH_TO_FX=/lib64/javafx-sdk-20/lib

all:
	@echo "Compile java files..."
	@javac --module-path $(PATH_TO_FX) --add-modules javafx.controls HelloFX.java CatText.java CatImg.java AbstractClass.java
	@echo "Trying to run a program..."
	@java --module-path $(PATH_TO_FX) --add-modules javafx.controls HelloFX CatText CatImg AbstractClass
	@echo "Removing classes..."
	@rm -rf *.class

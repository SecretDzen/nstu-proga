#!/bin/bash

export PATH_TO_FX=/lib64/javafx-sdk-19.0.2.1/lib
rm -rf *.class
javac --module-path $PATH_TO_FX --add-modules javafx.controls HelloFX.java CatText.java CatImg.java
java --module-path $PATH_TO_FX --add-modules javafx.controls HelloFX CatText CatImg

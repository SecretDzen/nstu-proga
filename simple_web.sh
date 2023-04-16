#!/bin/bash

rm -rf /www-data/web
mkdir /www-data/web
cp -r web/* /www-data/web
#rm -rf web
#mkdir web
#cp -r /www-data/web/* web

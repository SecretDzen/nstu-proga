#!/bin/bash

rm -rf /www-data/web
cp -r web/ /www-data
chown www-data /www-data/web/lab1/logs.txt

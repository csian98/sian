#!/bin/bash

if [ "$#" -ne 3 ]; then
	echo "Usage: $0 <JAVA> <INPUT> <OUTPUT>"
	exit
fi

FILE="${1%.*}"

hadoop com.sun.tools.javac.Main $1
jar cf $FILE.jar $FILE*.class
hadoop jar $FILE.jar $FILE $2 $3

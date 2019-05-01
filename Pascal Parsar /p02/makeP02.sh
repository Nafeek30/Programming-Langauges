#!/bin/bash

if [ "$1" == "--clean" ] || [ "$1" == "-c" ]; then
	make -f p02make clean
elif [ -z "$1" ]; then
	make -f p02make clean	
	make -f p02make
fi

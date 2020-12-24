#!/bin/bash

if [ -z "$1" ]; then
	echo "App not specified"
	exit 1
fi

app="bin/$1"
debug=$2

if [ ! -e "$app" ]; then
	echo "App $app not found"
	exit 1
fi

if [ -z "$debug" ]; then
	LD_LIBRARY_PATH=lib $app
else
	LD_LIBRARY_PATH=lib gdb $app
fi

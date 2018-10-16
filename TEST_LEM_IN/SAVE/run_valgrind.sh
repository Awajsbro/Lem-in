#!/bin/bash

if [ -e trace_valgrind ]
then
	rm trace_valgrind
fi

for file in _maps/*
do
	echo "Run ./lem-in $1 < $file"
	echo "\nFile: $file" >> trace_valgrind
	valgrind ../../lem-in $1 < $file >> trace_valgrind 2>&1
done

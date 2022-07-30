#!/bin/bash

NAME="cpparser"
LIBRARY_NAME="lib${NAME}.a"


function main() {
    mkdir ./lib

    g++ -c ./cpparser.cpp
    ar cr "${LIBRARY_NAME}" *.o
    mv "${LIBRARY_NAME}" lib/
}


main

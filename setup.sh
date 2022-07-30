#!/bin/bash

NAME="cpparser"
LIBRARY_NAME="lib${LIBRARY_NAME}.a"


function main() {
    g++ -c ./cpparser.cpp
    ar cr "${LIBRARY_NAME}" *.o
    mv "${LIBRARY_NAME}" lib/
}


main

#!/bin/bash

NAME="cpparser"
LIBRARY_NAME="lib${NAME}.a"

function main() {
    if [[ ! -d lib ]]; then
        mkdir ./lib
    fi

    g++ -c ./cpparser.cpp
    ar cr "${LIBRARY_NAME}" *.o
    mv "${LIBRARY_NAME}" lib/
}


main

#!/bin/bash

NAME="cpparser"
LIBRARY_NAME="lib${NAME}.a"

function compile_to_object_file {
    g++ -c ./cpparser.cpp
}


function link_object_files {
    ar cr "${LIBRARY_NAME}" *.o
}


function main() {
    if [[ ! -d lib ]]; then
        mkdir ./lib
    fi

    compile_to_object_file
    link_object_files
    
    mv "${LIBRARY_NAME}" lib/
}


main

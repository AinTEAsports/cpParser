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
		echo -e "\n[ /!\\ ] 'lib/' folder not found, creating it..."
        mkdir ./lib
    fi

	echo "[*] Compiling to object files..."
    compile_to_object_file
    
	echo "[*] Linking object files..."
	link_object_files
    
	echo "[*] Last step, moving lib files into right folder..."
    mv "${LIBRARY_NAME}" lib/


	echo -e "\n[+] Done !\n"
}


main

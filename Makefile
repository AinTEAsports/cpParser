CC=g++
FLAGS=-std=c++11 -lcpparser -I include -L lib
TARGET=cpparser_example
SOURCE_FILE=examples/example_complete.cpp

demo:
	$(CC) $(SOURCE_FILE) -o $(TARGET) $(FLAGS)

clean:
	rm $(TARGET)

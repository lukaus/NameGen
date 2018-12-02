all : nameGen

nameGen : name_test.cpp nameGen.cpp
	g++ name_test.cpp nameGen.cpp -o nameGen
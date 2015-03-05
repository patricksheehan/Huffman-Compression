huffman : huff.o main.o  
	g++ -Wall -g -O3 -o huffman huff.o main.o  

huff.o : huff.cpp huff.h 
	g++ -Wall -g -O3 -c huff.cpp

main.o : main.cpp 
	g++ -Wall -g -O3 -c main.cpp

clean : 
	rm -f huffman huff.o  main.o   

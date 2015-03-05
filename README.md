# Huffman

Takes input and provides compressed output via the Huffman encoding algorithm.

To build:
	- Open a terminal
	- Go to folder with files & makefile
	- type "make"
To run:
	- In terminal
		- to compress
			- type: huffman < notcompressed.txt > compressed.txt
		- to decompress
			- type: huffman -d < compressed.txt > decompressed.txt

example:
------
$ huffman < Huckleberry.txt > Huckleberry_compressed.txt
-----


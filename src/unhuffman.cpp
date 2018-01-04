// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       unhuffman.cpp
// Tab stops:  8

	//** 	This program takes a binary file compressed by huffman.cpp and uncompresses its contents into another file.  	**\\
	//** 	Takes 2 command line arguments, the binary file name, followed by the file name to uncompress to.		**\\

#include "trace.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include "tree.h"
#include "pqueue.h"
#include <string.h>
#include "binary.h"

// readTree(binFile) reads and returns a
// huffman tree from binary file binFile.

Node* readTree(BFILE* binFile)
{
	int b = readBit(binFile);
	if (b == 1)
	{
		char c = readByte(binFile);
		return new Node(c);
	}
	else if (b == 0)
	{
		Node* left = readTree(binFile);
		Node* right = readTree(binFile);
		return new Node(left, right);
	}
}

// readSingleCharacter(tree, binaryFile) reads a single
// character path from tree in binaryFile and returns
// that character as an integer.

int readSingleCharacter(Node* tree, BFILE* binaryFile)
{
	Node* temp = tree;
	int c = readBit(binaryFile);
	{
		while (true)
		{
			if (c == EOF)
			{
				return EOF;
			}
			if (c == 0)
			{
				temp = temp->left;
			}
			else if (c == 1)
			{
				temp = temp->right;
			}
			if (temp->kind == leaf)
			{
				return temp->ch;
			}
			c = readBit(binaryFile);
		}
	}
}

// uncompress(bineFile, t, fileName) uncompresses binary file
// bineFile using huffman tree t, and outputs the uncompression
// into file fileName.

void uncompress(BFILE* bineFile, Node* t, FILE* fileName)
{
	int read = readSingleCharacter(t, bineFile);
	while (read != EOF)
	{
		putc(read, fileName);
		read = readSingleCharacter(t, bineFile);
	}
}

int main(int argc, char** argv)
{
	if (argc <= 2 || argc > 4)
	{
		printf("Error. Improper number of command line arguments.");
		exit(1);
	}
	if (argv[argc - 3] != NULL && strcmp(argv[argc - 3], "-t") == 0)
	{
		tracelevel = 1;
		printf("tracing is on\n\n");
	}
	BFILE* binaryFile = openBinaryFileRead(argv[argc - 2]);
	if (binaryFile == NULL)
	{
		printf("Could not open file %s\n", argv[argc - 2]);
		exit(1);
	}
	Node* unhuffmanTree = readTree(binaryFile);
	if (tracelevel > 0)
	{
		printf("A huffman tree is as follows:\n\n");
	}
	printTree(unhuffmanTree);
	printf("\n\n");
	FILE* inf = fopen(argv[argc - 1], "w");
	if (inf == NULL)
	{
		printf("Could not open file %s\n", argv[argc - 1]);
		exit(1);
	}
	uncompress(binaryFile, unhuffmanTree, inf);
	closeBinaryFileRead(binaryFile);
	fclose(inf);
	return 0;
}

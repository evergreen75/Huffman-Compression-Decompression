// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       huffman.cpp
// Tab stops:  8

	//** 	This program takes a file and compresses the characters/information in the file into a binary file. 	**\\
	//** 	Takes 2 command line arguments, the file name, followed by the binary file name.			**\\

#include "trace.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include "tree.h"
#include "pqueue.h"
#include <string.h>
#include "binary.h"
#include <iostream>

// getFrequencies(count, inFile) gets the number of
// occurences of each character in file Infile and
// then stores these numbers in array count.

void getFrequencies(int* count, const char* inFile)
{
	FILE* inf = fopen(inFile, "r");
	if (inf == NULL)
	{
		printf("could not open file %s\n", inFile);
		exit(1);
	}
	for (int i = 0; i < 256; i++)
		{
			count[i] = 0;
		}
	int c = getc(inf);
	while (c != EOF)
	{
		count[c]++;
		c = getc(inf);
	}
	fclose(inf);
}

// makeTree(count) takes an array count
// which holds frequency counts for characters
// and returns a tree of these characters.

Node* makeTree(int* count)
{
	PriorityQueue p;
	for (int i = 0; i < 256; i++)
	{
		if (count[i] != 0)
		{
			Node* t = new Node((char)i);
			insert(t, count[i], p);
		}
	}
	if (isEmpty(p))
	{
		printf("file has no characters");
		exit(1);
	}
	PQItemType tree1, tree2;
	PQPriorityType freq1, freq2;
	while (true)
	{
		remove(tree1, freq1, p);
		Node* g = tree1;
		if (isEmpty(p))
		{
			return g;
		}
		else
		{
			remove(tree2, freq2, p);
			g = new Node(tree1, tree2);
			insert(g, freq1 + freq2, p);
		}
	}
}

const int MAX_PATH_LENGTH = 40;

// buildCode(tree, codes, path) takes a tree
// and fills a codes array of size 256 with
// their paths in the tree using array path.

void buildCode(Node* tree, char** codes, char* path)
{
	if (tree->kind == leaf)
	{
		codes[(unsigned char)(tree->ch)] = strcpy(new char[MAX_PATH_LENGTH], path);
	}
	else
	{
		char leftpath[MAX_PATH_LENGTH];
		char rightpath[MAX_PATH_LENGTH];
		strcpy(leftpath, path);
		strcat(leftpath, "0");
		buildCode(tree->left, codes, leftpath);
		strcpy(rightpath, path);
		strcat(rightpath, "1");
		buildCode(tree->right, codes, rightpath);
	}
}

// writeTreeBinary(t, bineFile) writes a description
// of a huffman tree into binary file bineFile.

void writeTreeBinary(Node* t, BFILE* bineFile)
{
	if (t->kind == leaf)
	{
		writeBit(bineFile, 1);
		writeByte(bineFile, t->ch);
	}
	else if (t->kind == nonleaf)
	{
		writeBit(bineFile, 0);
		writeTreeBinary(t->left, bineFile);
		writeTreeBinary(t->right, bineFile);
	}
}

// writeCode(c, code, bineFile) reads the code
// for character c in the code array and writes
// this code into binary file bineFile.

void writeCode(char c, char** code, BFILE* bineFile)
{
	const char* str = code[(unsigned char)c];
	for (int i = 0; str[i]!= '\0'; i++)
	{
		writeBit(bineFile, (str[i] - '0'));
	}
}

// writeEncodedCharacters(codes, binaryFile, fileName) writes
// the encoded characters from fileName into binaryFile
// using the codes array to fetch these codes.

void writeEncodedCharacters(char** codes, BFILE* binaryFile, const char* fileName)
{
	FILE* inf = fopen(fileName, "r");
	int c = getc(inf);
	while (true)
	{
		if (c == EOF)
		{
			break;
		}
		writeCode(c, codes, binaryFile);
		c = getc(inf);
	}
	fclose(inf);
}

int main(int argc, char** argv)
{
	if (argc <= 2 || argc > 4)
	{
		printf("Error. Improper number of command line arguments.\n");
		exit(1);
	}
	if (argv[argc - 3] != NULL && strcmp(argv[argc - 3], "-t") == 0)
	{
		tracelevel = 1;
		printf("tracing is on\n");
	}
	int freq[256];
	char* code[256];
	for (int i = 0; i < 256; i++)
	{
		code[i] = NULL;
	}
	char* pref = new char[MAX_PATH_LENGTH];

	getFrequencies(freq, argv[argc - 2]);
	Node* huffmanTree = makeTree(freq);
	buildCode(huffmanTree, code, pref);
	BFILE * binaryFile = openBinaryFileWrite(argv[argc - 1]);
	if (binaryFile == NULL)
	{
		printf("Could not open file %s\n", argv[argc - 1]);
		exit(1);
	}
	writeTreeBinary(huffmanTree, binaryFile);
	writeEncodedCharacters(code, binaryFile, argv[argc - 2]);
	closeBinaryFileWrite(binaryFile);

	// for tracing purposes, if first command line argument is -t
	printFrequencies(freq);
	printCharacterCounts(freq);
	if (tracelevel > 0)
	{
		printf("A huffman tree is as follows:\n\n");
	}
	printTree(huffmanTree);
	printCode(code);
	printf("\n");
	return 0;
}

// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       trace.h
// Tab stops:  8

				//** This program is a tracing program for huffman.cpp and unhuffman.cpp **\\

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include "tree.h"

int tracelevel = 0;

// printFrequencies(Frequencies) prints the
// frequencies of each character in array Frequencies.

void printFrequencies(int* Frequencies)
{
	if (tracelevel > 0)
	{
		printf("\nFrequencies Array: ");
		for (int i = 0; i < 256; i++)
		{
			if (Frequencies[i] != 0)
			{
				printf("%d | ", Frequencies[i]);
			}
		}
		printf("\n");
	}
}

// displayCharacter(c) prints the character value
// for c.

void displayCharacter(int c)
{
	if (tracelevel > 0)
	{
		if (c == 9)
		{
			printf("tab");
		}
		else if (c == 10)
		{
			printf("newline");
		}
		else if (c == 32)
		{
			printf("space");
		}
		else if (!isprint(c))
		{
			printf("\%d", c);
		}
		else
		{
			printf("%c", c);
		}
	}
}

// printCharacterCounts(count) takes array count
// and prints each character and the
// number of occurrences of each character.

void printCharacterCounts(int* count)
{
	if (tracelevel > 0)
	{
		printf("\n\nThe character frequencies are:\n\n");
		for (int c = 0; c < 256; c++)
		{
			if (count[c] != 0)
			{
				displayCharacter(c);
				printf(" %d\n", count[c]);
			}
		}
	}
	printf("\n");
}

// printTree(T) prints tree T.

void printTree(Node* T)
{
	if (tracelevel > 0)
	{
		if (T->kind == leaf)
		{
			displayCharacter(T->ch);
		}
		else
		{
			printf("(");
			printTree(T->left);
			printf(",");
			printTree(T->right);
			printf(")");
		}
	}
}

// printCode(codes) prints out the
// array of codes.

void printCode(char** codes)
{
	if (tracelevel > 0)
	{
		printf("\n\nA huffman code is as follows:\n\n");
		for (int i = 0; i < 256; i++)
		{
			if (codes[i] != NULL)
			{
				displayCharacter(i);
				printf(" %s\n", codes[i]);
			}
		}
	}
}

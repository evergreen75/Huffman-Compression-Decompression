// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       trace.h
// Tab stops:  8

#ifndef TRACE_H_
#define TRACE_H_

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include "tree.h"

extern int tracelevel;

void printFrequencies(int* Frequencies);
void displayCharacter(int c);
void printCharacterCounts(int* count);
void printTree(Node* T);
void printCode(char** code);

#endif /* TRACE_H_ */

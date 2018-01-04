// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       pqueue.h
// Tab stops:  8

#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <cstdlib>
#include <cstdio>
#include <stdio.h>

struct PQCell;
struct Node;
typedef Node* PQItemType;
typedef int PQPriorityType;

// structure to represent a priority queue
// by pointing to a linked list of events.

struct PriorityQueue
{
	PQCell* pointy;
	PriorityQueue()
	{
		pointy = NULL;
	}
};
bool isEmpty(const PriorityQueue &q);
void remove(PQItemType& item, PQPriorityType& pri, PriorityQueue& q);
void insert(const PQItemType& item, PQPriorityType pri, PriorityQueue& q);
typedef void (ItemPrinter)(PQItemType);
typedef void (PriorityPrinter)(PQPriorityType);
void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi,
		PriorityPrinter pp);




#endif /* PQUEUE_H_ */

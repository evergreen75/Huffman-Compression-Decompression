// CSCI 3300
// Assignment: 5
// Author:     Joshua Bowen
// File:       pqueue.cpp
// Tab stops:  8

// **	This program is a Priority Queue module which can perform an insert, isEmpty, and remove function.	**\\

#include "pqueue.h"
#include <cstdlib>
#include <cstdio>
#include <stdio.h>

// structure to represent an event in/Users/admin/Google Drive/Linux/huffman.cpp
// the priority queue.

struct PQCell
{
	PQItemType item;
	PQPriorityType Priority;
	PQCell* next;
	PQCell(PQItemType ite, PQPriorityType pri, PQCell* nxt)
	{
		item = ite;
		Priority = pri;
		next = nxt;
	}
};

void insertCell(const PQItemType& item, PQPriorityType pri, PQCell*& p);

// isEmpty(q) checks as to whether or not q is empty
// and if it is, returns true. Else, returns false.

bool isEmpty(const PriorityQueue &q)
{
	if (q.pointy == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// insert(item, pri, q) inserts an item and priority into Priority Queue q.

void insert(const PQItemType& item, PQPriorityType pri, PriorityQueue& q)
{
	insertCell(item, pri, q.pointy);
}

// insertCell(item, pri, p) inserts an item and priority into a linked
// list pointed to by p.

void insertCell(const PQItemType& item, PQPriorityType pri, PQCell*& p)
{
	if (p == NULL)
	{
		p = new PQCell(item, pri, NULL);
	}
	else if (pri < p->Priority)
	{
		p = new PQCell(item, pri, p);
	}
	else
	{
		insertCell(item, pri, p->next);
	}
}

// remove(item, pri, q) removes an item and priority from Priority Queue q.

void remove(PQItemType& item, PQPriorityType& pri, PriorityQueue& q)
{
	PQCell* g = q.pointy;
	q.pointy = q.pointy->next;
	item = g->item;
	pri = g->Priority;
	delete g;
}

// PrintPriorityQueue(q, pi, pp) prints Priority Queue q.

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
	printf("\nITEM      ");
	printf("PRIORITY\n");
	for (PQCell* g = q.pointy; g != NULL; g = g->next)
	{
		pi(g->item);
		printf("       ");
		pp(g->Priority);
		printf("\n");
	}
	printf("\n");
}

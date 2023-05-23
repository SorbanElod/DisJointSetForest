#pragma once
#ifndef _DISJOINT_SET_TPP_
#define _DISJOINT_SET_TPP_

#include "disjoint_set.h"
#include <vector>
#include <iostream>

using namespace std;

template <class TYPE>
node<TYPE>::node(TYPE t, node<TYPE>* par) : data(t), parent(par), rank(0) {}

template <class TYPE>
node<TYPE>::node(TYPE t) : node(t, this) {}

template <class TYPE>
node<TYPE>::node() : node(NULL, this) {}

template <class TYPE>
DisjointSetForest<TYPE>::DisjointSetForest() : size(0), numberofsets(0) {}

template <class TYPE>
DisjointSetForest<TYPE>::DisjointSetForest(vector <node<TYPE>>& v, bool validate) : numberofsets(0)
{
	for (int i = 0; i < v.size(); i++)
	{
		make_set(&v[i], validate);
	}
}

template <class TYPE>
unsigned long DisjointSetForest<TYPE>::num_set()
{
	return numberofsets;
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::make_set(node<TYPE>* x, bool validate)
{
	// this has LINEAR time complexity
	if (validate)
	{
		node <TYPE>* ptr = search(x);
		// item already in a set
		if (ptr == nullptr)
		{
			elements.push_back(x);
			x->parent = x;
			x->rank = 0;
			size++;
			numberofsets++;
		}
		return ptr;
	}
	// this has constant time complexity
	elements.push_back(x);
	x->parent = x;
	x->rank = 0;
	numberofsets++;
	size++;
	return x->parent;
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::search(node<TYPE>* x) const
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == x)
		{
			return x;
		}
	}
	return nullptr;
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::search(node<TYPE> x) const
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->data == x.data)
		{
			return elements[i];
		}
	}
	return nullptr;
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::find_set(node<TYPE>* x, bool compress)
{
	if (compress)
	{
		// find with compression
		if (x != x->parent)
		{
			x->parent = find_set(x->parent, compress);
		}
		return x->parent;
	}
	else
	{
		// regular find without compresion
		if (x->parent == x)
		{
			return x;
		}
		return find_set(x->parent, compress);
	}
}


template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::link(node<TYPE>* x, node<TYPE>* y, bool by_rank)
{
	if (x != y)
	{
		numberofsets--;
	}
	if (by_rank)
	{
		if (x->rank > y->rank)
		{
			y->parent = x;
			return y->parent;
		}
		else
		{
			x->parent = y;
			if (x->rank == y->rank)
			{
				y->rank = y->rank + 1;
			}
			return x->parent;
		}
	}
	else
	{
		// regular union
		// doesn't change the rank so once used the union_by_rank heuristic becomes unusable because it requieres the rank of nodes to be up to date
		x->parent = y;
		return x->parent;

	}
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::union_set(node<TYPE>* x, node<TYPE>* y, bool by_rank, bool compress)
{
	return link(find_set(x, compress), find_set(y, compress), by_rank);
}

template <class TYPE>
void DisjointSetForest<TYPE>::write_all() const
{
	for (int i = 0; i < elements.size(); i++)
	{
		node<TYPE>* current = elements[i];
		printf("%i: ", current->data);
		while (current != current->parent)
		{
			current = current->parent;
			printf("%i ", current->data);
		}
		printf("\n");
	}
	cout << endl;
}

template <class TYPE>
void DisjointSetForest<TYPE>::compress_all()
{
	for (int i = 0; i < elements.size(); i++)
	{
		find_set(elements[i]);
	}
}

#endif
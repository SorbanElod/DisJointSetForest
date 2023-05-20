#pragma once
#ifndef _DISJOINT_SET_TPP_
#define _DISJOINT_SET_TPP_

#include "disjoint_set.h"
#include <iostream>

using namespace std;

template <class TYPE>
node<TYPE>::node(TYPE t, node<TYPE>* par) : data(t), parent(par), rank(0) {}

template <class TYPE>
node<TYPE>::node(TYPE t) : node(t, this) {}

template <class TYPE>
node<TYPE>::node() : node(NULL, this) {}

template <class TYPE>
DisJointSetForest<TYPE>::DisJointSetForest() : size(0) {}

template <class TYPE>
DisJointSetForest<TYPE>::DisJointSetForest(vector <node<TYPE>>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		DisJointSetForest<TYPE>::make_set(&v[i]);
	}
}

template <class TYPE>
DisJointSetForest<TYPE>::~DisJointSetForest()
{
	// because all pointers are in a vector they are automagically destoyed at the end
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::make_set(node<TYPE>* x)
{
	elements.push_back(x);
	x->parent = x;
	x->rank = 0;
	return x->parent;
	size++;
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::search(node<TYPE>* x)
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
node<TYPE>* DisJointSetForest<TYPE>::search(node<TYPE> x)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (*elements[i] == x)
		{
			return &elements[i];
		}
	}
	return nullptr;
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::find_set(node<TYPE>* x, bool compress)
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
node<TYPE>* DisJointSetForest<TYPE>::link(node<TYPE>* x, node<TYPE>* y, bool by_rank)
{
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
node<TYPE>* DisJointSetForest<TYPE>::union_set(node<TYPE>* x, node<TYPE>* y, bool by_rank, bool compress)
{
	return DisJointSetForest<TYPE>::link(find_set(x, compress), find_set(y, compress), by_rank);
}

template <class TYPE>
void DisJointSetForest<TYPE>::write_all()
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

#endif
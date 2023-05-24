#pragma once
#ifndef _DISJOINT_SET_TPP_
#define _DISJOINT_SET_TPP_

#include "disjoint_set.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

template <class TYPE>
node<TYPE>::node() : rank(0), parent(this) {}

template <class TYPE>
DisjointSetForest<TYPE>::DisjointSetForest() : size(0), numberofsets(0) {}

template <class TYPE>
DisjointSetForest<TYPE>::DisjointSetForest(vector <TYPE>& v, bool validate) : numberofsets(0)
{
	for (int i = 0; i < v.size(); i++)
	{
		make_set(v[i], validate);
	}
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::make_set(TYPE x, bool validate)
{
	// this has LINEAR time complexity
	if (validate)
	{
		node <TYPE>* ptr = search(x);
		// item not found in a set
		if (ptr != nullptr)
		{
			elements[x] = new node<TYPE>;
			size++;
			numberofsets++;
		}
		return ptr;
	}
	// this has constant time complexity
	elements[x] = nullptr;
	elements[x] = new node<TYPE>;
	size++;
	numberofsets++;
	return elements[x];
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::search(TYPE x)
{
	auto tmp = elements.find(x);
	if (tmp == elements.end())
	{
		return nullptr;
	}
	return elements[x];
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
			return x->parent;
		}
		return find_set(x->parent, compress);
	}
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::find_set(TYPE x, bool compress)
{
	if (compress)
	{
		// find with compression
		if (elements[x] != elements[x]->parent)
		{
			elements[x]->parent = find_set(elements[x]->parent, compress);
		}
		return elements[x]->parent;
	}
	else
	{
		// regular find without compresion
		if (elements[x]->parent == elements[x])
		{
			return elements[x]->parent;
		}
		return find_set(elements[x]->parent, compress);
	}
}

template <class TYPE>
node<TYPE>* DisjointSetForest<TYPE>::link(node<TYPE>* x, node<TYPE >* y, bool by_rank)
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
node<TYPE>* DisjointSetForest<TYPE>::union_set(TYPE x, TYPE y, bool by_rank, bool compress)
{
	return link(find_set(x, compress), find_set(y, compress), by_rank);
}

template <class TYPE>
TYPE DisjointSetForest<TYPE>::get_data(node<TYPE>* x)
{
	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		if (it->second == x)
		{
			return it->first;
		}
	}
	return NULL;
}

template <class TYPE>
unsigned long DisjointSetForest<TYPE>::num_set()
{
	return numberofsets;
}

template <class TYPE>
void DisjointSetForest<TYPE>::compress_all()
{
	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		find_set(it->first);
	}
}

template <class TYPE>
void DisjointSetForest<TYPE>::write_all()
{
	for (auto it = elements.begin(); it != elements.end(); it++)
	{
		node<TYPE>* current = it->second;
		//cout << get_data(current) << " - " << current->rank << ": ";
		cout << get_data(current) << ": ";
		while (current != current->parent)
		{
			current = current->parent;
			cout << get_data(current) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

#endif
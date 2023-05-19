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
DisJointSetForest<TYPE>::DisJointSetForest() : size(0) {}

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
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::make_set(node<TYPE> x)
{
	return DisJointSetForest<TYPE>::make_set(&x);
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::make_set(TYPE x)
{
	return DisJointSetForest<TYPE>::make_set(node<TYPE>::node(x));
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::find_set(node<TYPE>* x, bool compress)
{
	if (compress)
	{
		//cout << "compressed" << endl;
		// find with compression
		if (x != x->parent)
		{
			x->parent = find_set(x->parent);
		}
		return x->parent;
	}
	else
	{
		//cout << "regular" << endl;
		// regular find without compresion
		if (x->parent == x)
		{
			return x;
		}
		return find_set(x);
	}
}


template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::link(node<TYPE>* x, node<TYPE>* y, bool by_rank)
{
	if (by_rank)
	{
		//cout << "by_rank" << endl;
		if (x->rank < y->rank)
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
		//cout << "link_by_rank" << endl;
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
ostream& operator<<(ostream& os, const node<TYPE>* n)
{
	return os << n->data << " ";
}

template <class TYPE>
void DisJointSetForest<TYPE>::write_all()
{
	for (int i = 0; i < elements.size(); i++)
	{
		node<TYPE>* current = elements[i];
		cout << current << ": ";
		while (current != current->parent)
		{
			current = current->parent;
			cout << current << " ";
		}
		cout << endl;
	}
}



#endif
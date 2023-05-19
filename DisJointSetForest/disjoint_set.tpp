#pragma once
#ifndef _DISJOINT_SET_TPP_
#define _DISJOINT_SET_TPP_

#include "disjoint_set.h"

using namespace std;

template <class TYPE>
node<TYPE>::node(TYPE t, node<TYPE>* par) : data(t), parent(par), rank(0) {}

template <class TYPE>
node<TYPE>::node(TYPE t) : node(t, this) {}

template <class TYPE>
DisJointSetForest<TYPE>::DisJointSetForest() : size(0) {}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::make_set(node<TYPE>* x)
{
	elements.push_back(x);
	x->parent = x;
	x->rank = 0;
	return x->parent;
}

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::union_set(node<TYPE>* x, node<TYPE>* y);

template <class TYPE>
node<TYPE>* DisJointSetForest<TYPE>::find_set(node<TYPE>* x);


#endif
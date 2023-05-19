#pragma once
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

template <class TYPE>
struct node
{
	TYPE data;
	node* parent;
	unsigned long rank;
	node(TYPE data);
	node(TYPE data, node* parent);

};

template <class TYPE>
class DisJointSetForest
{
private:
	std::vector <node <TYPE>*> elements;
	unsigned long size;
public:
	DisJointSetForest();
	~DisJointSetForest();
	node<TYPE>* make_set(node<TYPE>* x);
	node<TYPE>* union_set(node<TYPE>* x, node<TYPE>* y, bool by_rank = true, bool compress = true);
	node<TYPE>* find_set(node<TYPE>* x, bool compress = true);
	node<TYPE>* link(node<TYPE>* x, node<TYPE>* y, bool by_rank = true);
};

#include "disjoint_set.tpp"

#endif
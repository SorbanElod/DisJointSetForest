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
	node();
	node(TYPE data);
	node(TYPE data, node* parent);
};

template <class TYPE>
class DisjointSetForest
{
private:
	std::vector <node <TYPE>*> elements;
	unsigned long size, numberofsets;
	node<TYPE>* link(node<TYPE>* x, node<TYPE>* y, bool by_rank = true);
public:
	DisjointSetForest();
	DisjointSetForest(std::vector <node<TYPE>>& v, bool validate = false);
	node<TYPE>* make_set(node<TYPE>* x, bool validate = false);
	node<TYPE>* search(node<TYPE>* x) const;
	node<TYPE>* search(node<TYPE> x) const;
	node<TYPE>* union_set(node<TYPE>* x, node<TYPE>* y, bool by_rank = true, bool compress = true);
	node<TYPE>* find_set(node<TYPE>* x, bool compress = true);
	unsigned long num_set();
	void compress_all();
	void write_all() const;
};

#include "disjoint_set.tpp"

#endif
#pragma once
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>
#include <unordered_map>

template <class TYPE>
struct node
{
	node* parent;
	unsigned long rank;
	node();
};

template <class TYPE>
class DisjointSetForest
{
private:
	std::unordered_map <TYPE, node <TYPE>*> elements;
	unsigned long size, numberofsets;
	TYPE get_data(node<TYPE>* x);
	node<TYPE>* link(node<TYPE >* x, node<TYPE >* y, bool by_rank = true);
	void write_all();
public:
	DisjointSetForest();
	DisjointSetForest(std::vector <TYPE>& v, bool validate = false);
	node<TYPE>* make_set(TYPE x, bool validate = false);
	node<TYPE>* search(TYPE x);
	node<TYPE>* find_set(TYPE x, bool compress = true);
	node<TYPE>* find_set(node<TYPE>* x, bool compress = true);
	node<TYPE>* union_set(TYPE x, TYPE y, bool by_rank = true, bool compress = true);
	unsigned long num_set();
	void compress_all();
};

#include "disjoint_set.tpp"

#endif
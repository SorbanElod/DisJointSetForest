#include <iostream>
#include "disjoint_set.h"

using namespace std;

int main()
{
	int n = 8;
	vector <node<int>> v(n);
	node<int> no(100);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = node<int>(i);
	}
	DisJointSetForest<int> set(v);
	set.write_all();
	set.find_set(&no);
	set.write_all();
}

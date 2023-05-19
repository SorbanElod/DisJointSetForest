#include <iostream>
#include "disjoint_set.h"

using namespace std;

int main()
{
	node<int> n(5);
	node<int> m(3);
	node<int> o(2);
	DisJointSetForest<int> set;
	set.make_set(&n);
	set.make_set(m);
	set.make_set(&o);
	set.make_set(1);
	set.find_set(&n);
	set.union_set(&n, &m);
	set.union_set(&m, &o);
	set.write_all();
}

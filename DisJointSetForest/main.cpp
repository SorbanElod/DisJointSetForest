#include <iostream>
#include "disjoint_set.h"

using namespace std;

int main()
{
	
	DisJointSetForest<int> set;
	
	set.write_all();
	set.union_set(&n, &m);
	set.union_set(&m, &o);
	set.write_all();
}

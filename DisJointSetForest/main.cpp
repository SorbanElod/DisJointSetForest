#include <iostream>
#include "disjoint_set.h"

using namespace std;

int main()
{
	node<int> n(5);
	DisJointSetForest<int> set;
	set.make_set(&n);
	set.find_set(&n);
}

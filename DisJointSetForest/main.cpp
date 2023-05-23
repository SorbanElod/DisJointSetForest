#include <iostream>
#include <fstream>
#include <algorithm>
#include "disjoint_set.h"

using namespace std;

struct el
{
	unsigned long kezdet = ULONG_MAX, veg = ULONG_MAX;
	long suly = LONG_MAX;
	void kiir()
	{
		cout << kezdet << " -> " << veg << " = " << suly << "\n";
	}
};

bool cmp(el a, el b)
{
	return(a.suly < b.suly);
}

void beolvas(vector <el>& elek, int& n, int& m)
{
	ifstream fin("input.txt");
	fin >> n >> m;
	int cs1, cs2, suly;
	for (int i = 0; i < m; i++)
	{
		el tmp;
		fin >> tmp.kezdet >> tmp.veg >> tmp.suly;
		elek.push_back(tmp);
	}
}


template <class TYPE>
vector<node<TYPE>> convert_to_nodes(vector<TYPE>& v)
{
	vector <node<TYPE>> res;
	for (int i = 0; i < v.size(); i++)
	{
		res.push_back(node<TYPE>(v[i]));
	}
	return res;
}

void kruskal(vector <el>& elek, int n, vector <el>& ffa)
{
	vector <node<int>> csomok;
	for (int i = 0; i < n; i++)
	{
		csomok.push_back(node<int>(i));
	}
	DisjointSetForest<int> halmaz(csomok);
	int i = 0;
	while (halmaz.num_set() > 1)
	{
		if (halmaz.find_set(&csomok[elek[i].kezdet - 1]) != halmaz.find_set(&csomok[elek[i].veg - 1]))
		{
			ffa.push_back(elek[i]);
		}
		halmaz.union_set(&csomok[elek[i].kezdet - 1], &csomok[elek[i].veg - 1]);
		i++;
	}
}

int main()
{
	//int n = 8;
	//vector <node<int>> v(n);
	//node<int> no(100);
	//for (int i = 0; i < v.size(); i++)
	//{
	//	v[i] = node<int>(i);
	//}
	//DisjointSetForest<int> forest(v);
	//unsigned long sets = forest.num_set();
	//forest.write_all();
	//for (int i = 1; i < n; i++)
	//{
	//	forest.union_set(&v[0], &v[i]);
	//	sets = forest.num_set();
	//	forest.write_all();
	//}
	////forest.compress_all();
	//forest.write_all();
	ofstream fout("output.txt");
	vector <el> ffa;
	vector <el> elek;
	int n, m;
	beolvas(elek, n, m);
	sort(elek.begin(), elek.end(), cmp);
	kruskal(elek, n, ffa);
	long sum = 0;
	for (int i = 0; i < ffa.size(); i++)
	{
		sum += ffa[i].suly;
	}
	fout << sum << endl;
	for (int i = 0; i < ffa.size(); i++)
	{
		fout << ffa[i].kezdet << ' ' << ffa[i].veg << endl;
	}
}

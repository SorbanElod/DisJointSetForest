#include <iostream>
#include <fstream>
#include <algorithm>
#include "disjoint_set.h"

using namespace std;

struct kapcsolat
{
	unsigned long kezdet = ULONG_MAX, veg = ULONG_MAX;
	unsigned long ido = LONG_MAX;
	bool kritikus = false;
	void kiir()
	{
		cout << kezdet << " -> " << veg << " = " << ido << "\n";
	}
};

bool cmp(kapcsolat a, kapcsolat b)
{
	return(a.ido < b.ido);
}

void beolvas(vector <kapcsolat>& elek, unsigned long& n, unsigned long& m)
{
	ifstream fin("input.txt");
	fin >> n >> m;
	unsigned long cs1, cs2, suly;
	for (int i = 0; i < m; i++)
	{
		kapcsolat tmp;
		fin >> tmp.kezdet >> tmp.veg >> tmp.ido;
		elek.push_back(tmp);
	}
}

void halozat_optim(vector <kapcsolat>& elek, unsigned long n, unsigned long &krit)
{
	DisjointSetForest<int> halmaz;
	for (int i = 1; i <= n; i++)
	{
		halmaz.make_set(i);
	}
	unsigned long i = 0;
	while (halmaz.num_set() > 1)
	{
		if (halmaz.find_set(elek[i].kezdet) != halmaz.find_set(elek[i].veg))
		{
			elek[i].kritikus = true;
			krit++;
		}
		halmaz.union_set(elek[i].kezdet, elek[i].veg);
		i++;
	}
}

int main()
{
	ofstream fout("output.txt");
	vector <kapcsolat> elek;
	unsigned long n, m;
	beolvas(elek, n, m);
	unsigned long krit_kapcs = 0, felesleges_kapcs = 0;
	sort(elek.begin(), elek.end(), cmp);
	halozat_optim(elek, n,krit_kapcs);
	felesleges_kapcs = m - krit_kapcs;
	fout << "Kritikus utak szama: " << krit_kapcs << endl << "Kritikus utak: " << endl;
	for (unsigned long i = 0; i < m; i++)
	{
		if (elek[i].kritikus)
		{
			fout << elek[i].kezdet << " - " << elek[i].veg << " : " << elek[i].ido << endl;
		}
	}
	fout <<endl<< "Felesleges utak szama: " << felesleges_kapcs << endl << "Felesleges utak: " << endl;
	for (unsigned long i = 0; i < m; i++)
	{
		if (!elek[i].kritikus)
		{
			fout << elek[i].kezdet << " - " << elek[i].veg << " : " << elek[i].ido << endl;
		}
	}
}

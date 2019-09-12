#include <iostream>
#include "matriz.h"
#include "star.h"
using namespace std;

int main() {

	
	Matrix m("TGTTGTCACTTATGCGTGCTGGGCAGGCTGAGATAGATCCGACAC","TGATGTATTAGGACCTCAACACAAGAAGGAAATTATTCGATATTTGTATAATCATCAGAACGAAGATGGGGGTTGGGGATTCC");

	m.local();
	
	//m.print();
	//cout << endl;
	//m.print2();
	m.caminoL();
	m.pr_camino();

	//cout << m.data[m.data.size() - 1][m.data[0].size() - 1].first << endl;

	/*
	
	vector<string> doc;

	doc.push_back("ATTGCCATT");
	doc.push_back("ATGGCCATT");
	doc.push_back("ATCCAATTTT");
	doc.push_back("ATCTTCTT");
	doc.push_back("ACTGACC");

	Star c(doc);
	c.full_m();

	c.print();
	*/

	system("pause");
	return 0;
}
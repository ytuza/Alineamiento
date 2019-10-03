#pragma once
#include <iostream>
#include "matriz.h"
#include <string>
#include <iomanip>
using namespace std;

typedef vector<vector<float>> m_fl;




float dist(string a, string b) {

	if (a.size() != b.size()) {
		cout << "ERROR: tamaño" << endl;
		return -1;
	}

	int p_d = 0, p_a = 0;

	for (int i = 0; i < a.size(); i++) {
		if (a[i] != '-' and b[i] != '-') {
			if (a[i] == b[i]) {
				p_a++;
			}
			else {
				p_d++;
			}

		}
	}
	if (p_a == 0) {
		cout << "error div0" << endl;
		return 0.0;
	}
	return p_d / p_a;

}

float dist(pair<string, string> a) {

	//cout << ">" <<a.first << endl;
	//cout << ">" << a.second << endl;

	if (a.first.size() != a.second.size()) {
		cout << "ERROR: tamaño" << endl;
		return -1;
	}

	int p_d = 0, p_a = 0;

	for (int i = 0; i < a.first.size(); i++) {

		if (a.first[i] == '-' or a.second[i] == '-') {
			p_d++;
		}
		else {
			p_a++;

		}
	}

	cout << "P_d " << p_d << "p_a" << p_a << endl;
	if (p_a == 0) {
		cout << "error div0" << endl;
		return 0.0;
	}
	float t = float(p_d) / float(p_a);

	return t;

}

class Prog
{
public:
	Prog(vector<string> vc);
	~Prog();


	void mat_dist();
	void print();
	void print2(m_fl a);
	void ejemplo();

	m_fl gen_q(m_fl input);


	pair<int, int> min(m_fl input);

	m_fl red(m_fl input, pair<int, int> p);

	int n_str;
	vector<string> stv;
	vector<vector<float>> mats;
	vector<vector<float>> ejem;

	vector<string> clus;

	void c_mod(pair<int, int>a);

	void prog_total();

private:

};

Prog::Prog(vector<string> vc)
{
	stv = vc;

	n_str = vc.size();

	for (int i = 0; i < n_str; i++) {

		mats.push_back(vector<float>(n_str, 0.0));

	}
}

Prog::~Prog()
{
}

void Prog::mat_dist()
{
	vector<vector<pair<string, string>>> val_tem(n_str, vector<pair<string, string>>(n_str, { "","" }));


	for (int i = 0; i < n_str; i++) {

		for (int j = i + 1; j < n_str; j++) {
			Matrix tem(stv[i], stv[j]);
			int tem_s = tem.global();

			val_tem[i][j] = tem.caminoGol();
			val_tem[j][i] = val_tem[i][j];
		}
	}

	for (int i = 0; i < mats.size(); i++) {
		for (int j = 0; j < mats[0].size(); j++) {
			if (i != j) {
				mats[i][j] = dist(val_tem[i][j]);

				//cout << dist(val_tem[i][j]) << endl;
			}

		}
		//cout << "++" << endl;
	}



}

void Prog::print() {

	for (int i = 0; i < n_str; i++) {
		for (int j = 0; j < n_str; j++) {

			cout << " " << mats[i][j] << "|";
		}
		cout << endl;
	}
}

void Prog::print2(m_fl a) {
	cout << fixed << setprecision(2) << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {

			cout << " " << a[i][j] << "|";
		}
		cout << endl;
	}
}

inline void Prog::ejemplo()
{
	ejem.push_back({ 0,5,4,7,6,8 });
	ejem.push_back({ 5,0,7,10,9,11 });
	ejem.push_back({ 4,7,0,7,6,8 });
	ejem.push_back({ 7,10,7,0,5,9 });
	ejem.push_back({ 6,9,6,5,0,8 });
	ejem.push_back({ 8,11,8,9,8,0 });

	clus.push_back("0");
	clus.push_back("1");
	clus.push_back("2");
	clus.push_back("3");
	clus.push_back("4");
	clus.push_back("5");
	//clus.push_back("6");


}

inline m_fl Prog::gen_q(m_fl input)
{

	m_fl rpta;
	int n = input.size();
	for (int i = 0; i < n; i++) {

		rpta.push_back(vector<float>(n, 0.0));

	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			float s_f = 0.0, s_s = 0.0;
			for (int y = 0; y < n; y++) {
				if (y != i) {
					s_f = s_f + input[i][y];
				}
				if (y != j) {
					s_s = s_s + input[y][j];
				}
			}

			//cout << "[" << i << "]" << "[" << j << "] " << s_f << "::" << s_s << endl;

			rpta[i][j] = input[i][j] - float(1) / float(n - 2) * (s_f + s_s);
			rpta[j][i] = rpta[i][j];

		}

	}


	return rpta;
}

inline pair<int, int> Prog::min(m_fl input)
{
	int n = input.size();
	//cout << n << endl;
	int i_m = 0, j_m = 0;
	float min = 99;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (input[i][j] < min) {
				min = input[i][j];
				i_m = i;
				j_m = j;
				//cout << "entro" << min << endl;
			}
		}
	}


	return { i_m,j_m };
}

inline m_fl Prog::red(m_fl input, pair<int, int> p)
{
	m_fl rpta;
	int n = input.size() - 1;
	for (int i = 0; i < n; i++) {

		rpta.push_back(vector<float>(n, 0.0));

	}

	for (int i = 0; i < n; i++) {

		for (int j = i + 1; j < n; j++) {
			if (i != p.first) {
				int v_i = i, v_j = j;
				if (i > p.first) v_i++;
				if (j > p.first) v_j++;

				rpta[i][j] = input[v_i][v_j];

			}
			else {
				int v_i = i, v_j = j;
				if (i > p.first) v_i++;

				if (j > p.first) v_j++;
				float f1 = input[p.first][v_j];
				float f2 = input[p.second][v_j];
				float f3 = input[p.first][p.second];

				rpta[i][j] = (input[p.first][v_j] + input[p.second][v_j] - input[p.first][p.second]) * 0.5;

				//cout << "[" << i << "]" << "[" << j << "] " << rpta[i][j] << " f1>" << f1 << " f2>" << f2 << " f3>" << f3 << endl;

			}

			rpta[j][i] = rpta[i][j];

			//cout << v_i << "+" << v_j << endl;
		}
	}

	//cout << ">>> " << n << endl;

	print2(rpta);
	return rpta;
}

inline void Prog::c_mod(pair<int, int> a)
{

	cout << endl;

	clus[a.first] = clus[a.first] + clus[a.second];

	clus.erase(clus.begin() + a.second);

	for (int i = 0; i < clus.size(); i++) {
		cout << clus[i] << " + ";
	}

	cout << endl;
}

inline void Prog::prog_total()
{
	ejemplo();
	mat_dist();

	//print2(mats);
	m_fl in = ejem;


	m_fl q;

	while (in.size() > 2) {

		q = gen_q(in);

		cout << "Q" << endl;
		//print2(q);


		pair<int, int> m_val = min(q);

		c_mod(m_val);

		in = red(in, m_val);

		//cout << in.size() << endl;
	}

	//print2(q);

}
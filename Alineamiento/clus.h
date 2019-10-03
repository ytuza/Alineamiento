#pragma once
#include <iostream>
#include "matriz.h"
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<vector<float>> m_fl;




class Clus
{
public:
	Clus(vector<string> vc);
	Clus(int n);
	~Clus();

	void mat_dist();
	void print();
	void print2(m_fl a);
	void print2(vector<float> a);
	void ejemplo();
	void s_clus(int n);

	vector<string> clus;

	int n_str;
	vector<string> stv;
	vector<vector<float>> mats;
	vector<vector<float>> ejem;

	m_fl red(m_fl input, pair<int, int> p, int opc);
	pair<int, int> min(m_fl input);
	void c_mod(pair<int, int>a);
	void d_mod(pair<int, int>a);
	void prog_total(int opc);
	void c_clus(int n);

	void prog_dis();

	vector<float> dis_min(m_fl in);


private:

};

Clus::Clus(vector<string> vc)
{
	stv = vc;

	n_str = vc.size();

	for (int i = 0; i < n_str; i++) {

		mats.push_back(vector<float>(n_str, 0.0));

	}
}

Clus::Clus(int n)
{
	n_str = n;

}

Clus::~Clus()
{
}

void Clus::print() {

	for (int i = 0; i < n_str; i++) {
		for (int j = 0; j < n_str; j++) {

			cout << " " << mats[i][j] << "|";
		}
		cout << endl;
	}
}

void Clus::print2(m_fl a) {
	cout << fixed << setprecision(2) << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {

			cout << " " << a[i][j] << "|";
		}
		cout << endl;
	}
}

void Clus::print2(vector<float> a) {
	cout << fixed << setprecision(2) << endl;
	for (int i = 0; i < a.size(); i++) {

		cout << " " << a[i]<< "|" << endl;
	}
}

void Clus::ejemplo()
{
	ejem.push_back({ 0   , 2.15,  0.7, 1.07, 0.85, 1.16, 1.56});
	ejem.push_back({ 2.15,    0, 1.53, 1.14, 1.38, 1.01, 2.83});
	ejem.push_back({  0.7, 1.53,    0, 0.43, 0.21, 0.55, 1.86});
	ejem.push_back({ 1.07, 1.14, 0.43,    0, 0.29, 0.22, 2.04});
	ejem.push_back({ 0.85, 1.38, 0.21, 0.29,    0, 0.41, 2.02});
	ejem.push_back({ 1.16, 1.01, 0.55, 0.22, 0.41,    0, 2.05});
	ejem.push_back({ 1.56, 2.83, 1.86, 2.04, 2.02, 2.05,    0});
}

inline void Clus::s_clus(int n )
{
	for (int i = 0; i < n; i++) {
		clus.push_back(to_string(i));
	}
}

inline void Clus::c_clus(int n)
{
	clus.push_back("");
	for (int i = 0; i < n; i++) {
		clus[0].push_back(to_string(i)[0]);
	}
}

void Clus::mat_dist()
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

inline pair<int, int> Clus::min(m_fl input)
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


float min_f(float a, float b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

float max_f(float a, float b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

float prom_f(float a, float b) {
	float r = float(a+b)/2.0;

	return r;
}

inline m_fl Clus::red(m_fl input, pair<int, int> p, int opc)
{
	m_fl rpta;
	int n = input.size() - 1;
	for (int i = 0; i < n; i++) {

		rpta.push_back(vector<float>(n, 0.0));

	}

	cout << "PAR>>" << p.first << " :: " << p.second << endl;

	for (int i = 0; i < n; i++) {

		for (int j = i + 1; j < n; j++) {

			int v_i = i, v_j = j;
			if (i >= p.second) v_i++;

			if (j >= p.second) v_j++;

			if (i != p.first and j != p.first) {
				rpta[i][j] = input[v_i][v_j];
			}else {
				float f1, f2;
				if (j != p.first) {
					//cout << "fila" << endl;
					f1 = input[p.first][v_j];
					f2 = input[p.second][v_j];
				}
				else {
					//cout << "columna" << endl;
					f1 = input[v_i][p.first];
					f2 = input[v_i][p.second];
				}
				
				
				if (opc == 0) {
					rpta[i][j] = min_f(f1,f2);
				}
				else if(opc == 1){ 
					rpta[i][j] = max_f(f1, f2);
				}
				else if (opc == 2) {
					rpta[i][j] = prom_f(f1, f2);
				}

				cout << "[" << v_i << "]" << "[" << v_j << "] " << endl;
				cout << "[" << i << "]" << "[" << j << "] " << rpta[i][j] << " f1>" << f1 << " f2>" << f2 <<  endl;

			}

			rpta[j][i] = rpta[i][j];

			//cout << v_i << "+" << v_j << endl;
		}
	}

	//cout << ">>> " << n << endl;

	//print2(rpta);
	return rpta;
}

inline void Clus::c_mod(pair<int, int> a)
{

	cout << endl;

	clus[a.first] = clus[a.first] + clus[a.second];

	clus.erase(clus.begin() + a.second);

	for (int i = 0; i < clus.size(); i++) {
		cout << clus[i] << " + ";
	}

	cout << endl;
}


inline void Clus::d_mod(pair<int, int> a)
{

	cout << endl;



	clus[a.first] = clus[a.first] + clus[a.second];

	clus.erase(clus.begin() + a.second);

	for (int i = 0; i < clus.size(); i++) {
		cout << clus[i] << " + ";
	}

	cout << endl;
}

//clustering min, max y prom 
void Clus::prog_total(int opc)
{
	ejemplo();
	s_clus(n_str);

	//mat_dist();

	//print2(mats);

	m_fl in = ejem;

	while (in.size() > 2) {

		pair<int, int> m_val = min(in);

		c_mod(m_val);

		// con el ultimo parametro se escoge 0 min 1 max 2 prom 
		in = red(in, m_val,0);

		print2(in);
	}


}

//disociativo
void Clus::prog_dis()
{
	ejemplo();
	s_clus(n_str);

	m_fl in = ejem;

	vector<float> m = dis_min(in);

	print2(m);
	float tem = -999;
	int t = 0;
	for (int i = 0; i < m.size(); i++) {
		if (m[i] > tem) {
			tem = m[i];
			t = i;
		} 
	}
	vector<float> res;
	for (int i = 0; i < in.size(); i++) {
		//cout << in[t][i] << "><"<<endl;
		if(i != t) res.push_back(m[i]-in[t][i]);
	}

	print2(res);


}

inline vector<float> Clus::dis_min(m_fl in)
{
	vector<float> rpta;
	for (int i = 0; i < in.size(); i++) {
		float m = 9999;
		for (int j = 0; j < in.size(); j++) {
			
			if (in[i][j] < m and i != j) {
				m = in[i][j];
			}
		}

		rpta.push_back(m);

	}
	return rpta;
}

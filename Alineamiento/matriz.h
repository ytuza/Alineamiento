#pragma once
#include <iostream>
#include <utility>  
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

typedef pair<int, int> pair_i;
typedef vector<vector<pair_i>> m_vec;


void swapS(string &str) {
	string rpta;

	for (int i = str.size()-1; i >=0 ; i--) {
		rpta.push_back(str[i]);
	}
	str = rpta;
}

class Matrix
{
public:
	Matrix(string a, string b);
	~Matrix();
	
	m_vec data;

	//first value
	//second direction
	// 0 sin camino
	// 1 < izquierda
	// 2 ^ arriba
	// 3 \ centro
	// 4 \^ centro y arriba
	// 5 <\ izquierda y centro
	// 6 <^ izquierda y arriba 

	void print();
	void print2();

	void pr_camino();

	int f, c;
	string s1, s2;

	int global();
	int local();
	void caminoG();

	pair<string, string> caminoGol();

	void caminoL();

	vector<pair<string,string>> res;
	
	int i_max, j_max, max;

	
private:

};

Matrix::Matrix(string a, string b)
{
	/*
	if (a.size() < b.size()) {
		string tem = a;
		a = b;
		b = tem;
	}
	*/

	s1 = a;
	s2 = b;

	f = a.size()+1;
	c = b.size()+1;



	for (int i = 0; i < f; i++) {

		data.push_back(vector<pair_i>(c, {0,0}));

	}
}

Matrix::~Matrix()
{
}

void Matrix::print() {

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			if (data[i][j].first < 0) {
				if (data[i][j].first > -10) {
					cout << " " << data[i][j].first << "|";
				}
				else {
					cout << data[i][j].first << "|";
				}
			}
			else {
				if (data[i][j].first < 10) {
					cout << "  " << data[i][j].first << "|";
				}
				else {
					cout << "   " << data[i][j].first << "|";
				}
				
			}
		}
		cout << endl;
	}
}

void Matrix::print2() {

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			if (data[i][j].second < 0) {
				if (data[i][j].second > -10) {
					cout << " " << data[i][j].second << "|";
				}
				else {
					cout << data[i][j].second << "|";
				}
			}
			else {
				if (data[i][j].first < 10) {
					cout << "  " << data[i][j].second << "|";
				}
				else {
					cout << "   " << data[i][j].second << "|";
				}

			}
		}
		cout << endl;
	}
}

inline void Matrix::pr_camino()
{
	for (int i = 0; i < res.size();i++) {
		cout << res[i].first << endl;
		cout << res[i].second << endl;
		cout << "---------------" << endl;

	}

}

inline int Matrix::global()
{
	for (int j = 0; j < c; j++) {
		data[0][j].first = -2 * j;
	}

	for (int i = 0; i < f; i++) {		
		data[i][0].first = -2 * i;
	}

	for (int i = 1; i < f; i++) {
		for (int j = 1; j < c; j++) {

			int iz = data[i][j - 1].first - 2;
			int ar = data[i - 1][j].first - 2; 
			int ce;
			if (s1[i - 1] == s2[j - 1]) {
				ce = data[i - 1][j - 1].first + 1;
			}
			else {
				ce = data[i - 1][j - 1].first - 1;
			}

			if(iz > ar){
				if (iz > ce) {
					data[i][j].first = iz;
					data[i][j].second = 1;
				}
				else {
					if (iz == ce) {
						data[i][j].second = 5;
					}
					else {
						data[i][j].second = 3;
					}
					data[i][j].first = ce;
				}
			}
			else {
				if (ar > ce) {
					if (iz == ar) {						
						data[i][j].second = 2;
					}
					else {
						data[i][j].second = 2;
					}
					data[i][j].first = ar;
				}
				else {
					if (ar == ce) {
						data[i][j].second = 4;
					}
					else {
						data[i][j].second = 3;
					}
					data[i][j].first = ce;
				}

			}

		}
	}
	return data[data.size() - 1][data[0].size() - 1].first;


}

inline void Matrix::caminoG()
{
	res.push_back({"",""});
	
	cout << s1 << "<+>" << s2 << endl;
	cout << s1.size() << "<+>" << s2.size() << endl;

	for (int cad = 0; cad < res.size() ; cad++) {
		int i = f - 1 + count(res[cad].first.begin(), res[cad].first.end(), '-') - res[cad].first.size();
		
		int j = c - 1 + count(res[cad].second.begin(), res[cad].second.end(), '-') - res[cad].first.size();
		

		while (i > 0 && j > 0) {

			//cout << "[" << i << "," << j << "]";

			switch (data[i][j].second)
			{
			case 1:
				j--;
				res[cad].first.push_back('-');
				res[cad].second.push_back(s2[j]);	
				 
				break;
			case 2:
				i--;
				res[cad].first.push_back(s1[i]);
				res[cad].second.push_back( '-' );
				
				break;
			case 3:
				i--;
				j--;
				res[cad].first.push_back(s1[i]);
				res[cad].second.push_back(s2[j]);
				
				break;
			case 4:
				i--;
				j--;
				res[cad].first.push_back(s1[i]);
				res.push_back({ res[cad].first, res[cad].second +'-' });
				res[cad].second.push_back(s2[j]);
				
				break;
			case 5:
				i--;
				j--;
				res[cad].second.push_back(s2[j]);
				res.push_back({ res[cad].first + '-', res[cad].second});
				res[cad].first.push_back(s1[i]);
				
				break;
			case 6:
				j--;
				res.push_back({ res[cad].first + s1[i-1], res[cad].second +  '-' });
				res[cad].first.push_back('-');
				res[cad].second.push_back(s2[j]);
				
				break;
			default:
				break;
			}
		}
		
		while (i > 0) {
			i--;
			res[cad].first.push_back(s1[i]);
			res[cad].second.push_back('-');	
		}
		while (j > 0) {
			j--;
			res[cad].first.push_back('-');
			res[cad].second.push_back(s2[j]);	
		}
		
		

		swapS(res[cad].first);
		swapS(res[cad].second);
		
	}

	cout << res.size() << " n de caminos " << endl;
	

}

inline void Matrix::caminoL()
{

	res.clear();

	res.push_back({ "","" });

	cout << s1 << "<+>" << s2 << endl;
	cout << s1.size() << "<+>" << s2.size() << endl;

	int i = f, j = c;


	while (i > i_max && j > j_max) {
		i--;
		//res[0].first.push_back(s1[i]);
		j--;
		//res[0].second.push_back(s2[j]);
	}

	while (j > j_max) {
		j--;
		//res[0].second.push_back(s2[j]);
		//res[0].first.push_back('-');
	}

	while (i > i_max) {
		i--;
		//res[0].first.push_back(s1[i]);
		//res[0].second.push_back('-');
	}

	int cad = 0;

	while (data[i][j].first>0) {

		//cout << "[" << i << "," << j << "]";

		switch (data[i][j].second)
		{
		case 1:
			j--;
			res[cad].first.push_back('-');
			res[cad].second.push_back(s2[j]);

			break;
		case 2:
			i--;
			res[cad].first.push_back(s1[i]);
			res[cad].second.push_back('-');

			break;
		case 3:
			i--;
			j--;
			res[cad].first.push_back(s1[i]);
			res[cad].second.push_back(s2[j]);

			break;
		case 4:
			i--;
			j--;
			res[cad].first.push_back(s1[i]);
			res.push_back({ res[cad].first, res[cad].second + '-' });
			res[cad].second.push_back(s2[j]);

			break;
		case 5:
			i--;
			j--;
			res[cad].second.push_back(s2[j]);
			res.push_back({ res[cad].first + '-', res[cad].second });
			res[cad].first.push_back(s1[i]);

			break;
		case 6:
			j--;
			res.push_back({ res[cad].first + s1[i - 1], res[cad].second + '-' });
			res[cad].first.push_back('-');
			res[cad].second.push_back(s2[j]);

			break;
		default:
			break;
		}
	}


	while (i > 0 && j > 0) {
		i--;
		//res[0].first.push_back(s1[i]);
		j--;
		//res[0].second.push_back(s2[j]);
	}

	while (j > 0) {
		j--;
		//res[0].second.push_back(s2[j]);
		//res[0].first.push_back('-');
	}

	while (i > 0) {
		i--;
		//res[0].first.push_back(s1[i]);
		//res[0].second.push_back('-');
	}


	swapS(res[cad].first);
	swapS(res[cad].second);

	cout << "pu "<< max << endl;

}


inline int Matrix::local()
{


	for (int i = 1; i < f; i++) {
		for (int j = 1; j < c; j++) {

			int iz = data[i][j - 1].first - 2;
			int ar = data[i - 1][j].first - 2;
			int ce;
			if (s1[i - 1] == s2[j - 1]) {
				ce = data[i - 1][j - 1].first + 1;
			}
			else {
				ce = data[i - 1][j - 1].first - 1;
			}

			if (iz > ar) {
				if (iz > ce) {
					data[i][j].first = iz;
					data[i][j].second = 1;
				}
				else {
					if (iz == ce) {
						data[i][j].second = 5;
					}
					else {
						data[i][j].second = 3;
					}
					data[i][j].first = ce;
				}
			}
			else {
				if (ar > ce) {
					if (iz == ar) {
						data[i][j].second = 2;
					}
					else {
						data[i][j].second = 2;
					}
					data[i][j].first = ar;
				}
				else {
					if (ar == ce) {
						data[i][j].second = 4;
					}
					else {
						data[i][j].second = 3;
					}
					data[i][j].first = ce;
				}

			}
			//cout << "[" << i << "," << j << "]" << ar << "," << ce << endl;
			if (data[i][j].first < 0) {
				data[i][j].second = 0;
				data[i][j].first = 0;
			}
			
			if (max < data[i][j].first) {
				i_max = i;
				j_max = j;
				max = data[i][j].first;
			}

		}
	}

	return max;


}



inline pair<string, string> Matrix::caminoGol()
{
	pair<string, string> rpta({"",""});


	cout << s1 << "<+>" << s2 << endl;
	cout << s1.size() << "<+>" << s2.size() << endl;

	int i = f - 1;

	int j = c - 1;

		while (i > 0 && j > 0) {

			//cout << "[" << i << "," << j << "]";

			switch (data[i][j].second)
			{
			case 1:
				j--;
				rpta.first.push_back('-');
				rpta.second.push_back(s2[j]);

				break;
			case 2:
				i--;
				rpta.first.push_back(s1[i]);
				rpta.second.push_back('-');

				break;
			case 3:
				i--;
				j--;
				rpta.first.push_back(s1[i]);
				rpta.second.push_back(s2[j]);

				break;
			case 4:
				i--;
				j--;
				rpta.first.push_back(s1[i]);
				rpta.second.push_back(s2[j]);

				break;
			case 5:
				j--;
				rpta.first.push_back('-');
				rpta.second.push_back(s2[j]);

				break;
			case 6:
				j--;
				rpta.first.push_back('-');
				rpta.second.push_back(s2[j]);

				break;
			default:
				break;
			}
		}

		while (i > 0) {
			i--;
			rpta.first.push_back(s1[i]);
			rpta.second.push_back('-');
		}
		while (j > 0) {
			j--;
			rpta.first.push_back('-');
			rpta.second.push_back(s2[j]);
		}



		swapS(rpta.first);
		swapS(rpta.second);

		res.push_back(rpta);
		return rpta;

}
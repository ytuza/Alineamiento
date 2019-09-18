#pragma once
#include <iostream>
#include "matriz.h"
#include <string>

class Star
{
public:
	Star(vector<string> vc);
	~Star();

	void full_m();
	void print();

private:
	int n_str;
	vector<string> stv;
	vector<string> rpta_s;
	vector<vector<int>> mats;
};

Star::Star(vector<string> vc)
{
	stv = vc;

	n_str = vc.size();

	for (int i = 0; i < n_str; i++) {

		mats.push_back(vector<int>(n_str + 1 , 0));

	}
}

Star::~Star()
{
}

inline void Star::full_m()
{
	vector<vector<pair<string, string>>> val_tem(n_str, vector<pair<string, string>>(n_str, {"",""}));


	for (int i = 0; i < n_str; i++) {

		for (int j = i + 1; j < n_str; j++) {
			Matrix tem(stv[i],stv[j]);
			int tem_s = tem.global();

			val_tem[i][j] = tem.caminoGol();
			val_tem[j][i] = val_tem[i][j];

			mats[i][j] = tem_s;
			mats[j][i] = tem_s;
		}
	}


	
	for (int i = 0; i < n_str; i++) {
		int sum = 0;
		for (int j = 0; j < n_str; j++) {
			sum = mats[i][j] + sum;
		}
		mats[i][n_str] = sum;
	}

	int dc = mats[0][n_str], i_g = 0;
	for (int i = 1; i < n_str; i++) {
		if (dc < mats[i][n_str]) {
			dc = mats[i][n_str];
			i_g = i;
		}
	}

	cout << "cadena principal " << i_g << " : " << stv[i_g] << endl;

	cout << val_tem[i_g][1].first << endl << val_tem[i_g][1].second << endl;
	cout << val_tem[i_g][2].first << endl << val_tem[i_g][2].second << endl;
	cout << val_tem[i_g][3].first << endl << val_tem[i_g][3].second << endl;
	
	//rpta_s.push_back();

	for(int i = 0;i<n_str;i++){
		if (i != i_g) {
			


		}
	}
	

}

void Star::print() {

	for (int i = 0; i < n_str; i++) {
		for (int j = 0; j < n_str +1; j++) {
			if (mats[i][j] < 0) {
				if (mats[i][j] > -10) {
					cout << " " << mats[i][j] << "|";
				}
				else {
					cout << mats[i][j] << "|";
				}
			}
			else {
				if (mats[i][j] < 10) {
					cout << "  " << mats[i][j] << "|";
				}
				else {
					cout << "   " << mats[i][j]<< "|";
				}

			}
		}
		cout << endl;
	}
}
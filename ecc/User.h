#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "Elliptic.hpp"
using namespace std;

class User {
public:

	User();
	User(int a, int b, int p);
	~User();
	pair<int, int>				generateG();
	pair<int, int>				generateQ();
	pair<int, int>				generateC1();
	pair<int, int>				generateC2();
	int							generateR();
	Elliptic*					sendCurve();
	pair<int,int>				codeIntoCurve(char ch);
	pair<int, int>				calculateM();
	void						getC1AndC2(pair<int,int>& C1,pair<int,int>& C2);
	char						decode(pair<int,int> M);

	void						getEQG(Elliptic* e, pair<int, int> Q, pair<int, int> G);

private:
	int							r;
	int							k;
	Elliptic*					e;
	pair<int, int>				M;
	pair<int, int>				G;
	pair<int, int>				Q;
	pair<int, int>				C1;
	pair<int, int>				C2;
};

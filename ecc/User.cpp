#include "User.h"


User::User()
{
	
}
User::User(int a, int b, int p)
{
	this->e = new Elliptic(0, -4, 211);
}

User::~User()
{
	delete e;
}

int User::generateR()
{
	srand(time(NULL));
	this->r = rand() % 50;
	return r;
}

pair<int, int> User::generateG()
{
	this->G = e->getGenerator();
	return G;
}

pair<int, int> User::generateC1()
{
	pair<int, int> temp;
	pair<int, int> C1;
	temp = e->multiplyPointBy(this->Q, this->r);
	C1 = e->addTwoPoints(temp, this->M);
	return C1;
}

pair<int, int> User::generateC2()
{
	pair<int, int> C2;
	C2 = e->GMultiplyBy(this->r);
	return C2;
}

pair<int, int> User::generateQ()
{
	cout << "Please Enter k:" << endl;
	cin >> k;
	this->k = k;
	this->Q = e->GMultiplyBy(this->k);
	return Q;
}

Elliptic* User::sendCurve()
{
	return e;
}

pair<int, int> User::codeIntoCurve(char ch)
{
	this->M = e->getPointByChar(ch);
	return M;
}

void User::getC1AndC2(pair<int,int>& C1,pair<int,int>& C2)
{
	this->C1 = C1;
	this->C2 = C2;
}

pair<int, int> User::calculateM()
{
	this->M = e->subtractTwoPoints(this->C1, e->multiplyPointBy(this->C2, this->k));
	return M;
}

char User::decode(pair<int, int> M)
{
	return e->getCharByPoint(M);
}

void User::getEQG(Elliptic* e, pair<int, int> Q, pair<int, int> G)
{
	this->e = e;
	this->Q = Q;
	this->G = G;
}
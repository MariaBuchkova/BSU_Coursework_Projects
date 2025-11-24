#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

int NOD(int a, int b);
int NOK(int a, int b);

class fraction {
private:
	int num_, den_;
public:
	fraction();
	fraction(int num);
	fraction(int num, int den);

	fraction operator * (const fraction&) const;
	fraction operator / (const fraction&) const;
	fraction operator + (const fraction&) const;
	fraction operator - (const fraction&) const;
	fraction operator - ();

	fraction& operator *= (const fraction&);
	fraction& operator /= (const fraction&);
	fraction& operator += (const fraction&);
	fraction& operator -= (const fraction&);

	fraction& operator ++ ();
	fraction& operator -- ();
	fraction operator ++ (int);
	fraction operator -- (int);

	bool operator == (const fraction&) const;
	bool operator > (const fraction&) const;
	bool operator < (const fraction&) const;
	bool operator >= (const fraction&) const;
	bool operator <= (const fraction&) const;
	bool operator != (const fraction&) const;

	void print() const;
};

#endif
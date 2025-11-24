#include "fraction.h"
#include <iostream>
int NOD(int a, int b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	if (a == 0)
	{ return 1; }
	return a;
}
int NOK(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	int nod = NOD(a, b);
	return (a / nod) * b;
}

fraction::fraction() {
	num_ = 0;
	den_ = 1;
}
fraction::fraction(int num) {
	num_ = num;
	den_ = 1;
}
fraction::fraction(int num, int den) {
	if (den == 0) throw "Error! denominator cannot be 0";
	if (den < 0) {
		num = -num;
		den = -den;
	}
	num_ = num / NOD(num, den);
	den_ = den / NOD(num, den);
}

fraction fraction::operator * (const fraction& drob) const {
	return fraction(num_ * drob.num_, den_ * drob.den_);
}
fraction fraction::operator / (const fraction& drob) const {
	fraction sopr(drob.den_, drob.num_);
	return fraction(num_ * sopr.num_, den_ * sopr.den_);
}
fraction fraction::operator + (const fraction& drob) const {
	long nok = NOK(drob.den_, den_);
	return fraction(num_ * (nok / den_) + drob.num_ * (nok / drob.den_), nok);
}
fraction fraction::operator - () {
	return fraction(-num_, den_);
}
fraction fraction::operator - (const fraction& drob) const {
	long nok = NOK(drob.den_, den_);
	return fraction(num_ * (nok / den_) - drob.num_ * (nok / drob.den_), nok);
}

fraction& fraction::operator += (const fraction& drob) {
	*this = *this + drob;
	return *this;
}
fraction& fraction::operator -= (const fraction& drob) {
	*this = *this - drob;
	return *this;
}
fraction& fraction::operator *= (const fraction& drob) {
	*this = *this * drob;
	return *this;
}
fraction& fraction::operator /= (const fraction& drob) {
	*this = *this / drob;
	return *this;
}

fraction& fraction::operator ++ () {
	num_ += den_;
	return *this;
}
fraction& fraction::operator -- () {
	num_ -= den_;
	return *this;
}
fraction fraction::operator ++ (int a) {
	fraction temp = *this;
	++(*this);
	return temp;
}
fraction fraction::operator -- (int a) {
	fraction temp = *this;
	--(*this);
	return temp;
}

bool fraction::operator == (const fraction& drob) const {
	return (num_ == drob.num_) && (den_ == drob.den_);
}
bool fraction::operator > (const fraction& drob) const {
	int nok = NOK(den_, drob.den_);
	return num_ * (nok / den_) > drob.num_ * (nok / drob.den_);
}
bool fraction::operator < (const fraction& drob) const {
	int nok = NOK(den_, drob.den_);
	return num_ * (nok / den_) < drob.num_ * (nok / drob.den_);
}
bool fraction::operator != (const fraction& drob) const {
	return (num_ != drob.num_) && (den_ != drob.den_);
}
bool fraction::operator >= (const fraction& drob) const {
	return !(*this==drob);
}
bool fraction::operator <= (const fraction& drob) const {
	return (drob == *this) || (*this < drob);
}
void fraction::print() const {
	std::cout << num_ << "\n" << "-\n" << den_ << "\n";
}

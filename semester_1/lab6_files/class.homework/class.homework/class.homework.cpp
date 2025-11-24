#include <iostream>
int NOD(int a, int b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	if (a == 0) { return 1; }
	return a;
}
int NOK(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	int nod = NOD(a, b);
	return (a / nod) * b;
}
class fraction {
private:
	int num_;
	int den_;
public:
	fraction() {
		num_ = 0;
		den_ = 1;
	}
	fraction(int num) {
		num_ = num;
		den_ = 1;
	}
	fraction(int num, int den) {
		if (den == 0) throw "Error! the numerator cannot be 0";
		num_ = num / NOD(num, den);
		den_ = den / NOD(num, den);
		if (den_ < 0) {
			num_ = -num_;
			den_ = -den_;
		}
	}
	fraction operator * (const fraction& drob) const {
		return fraction(num_ * drob.num_, den_ * drob.den_);
	}
	fraction operator / (const fraction& drob) const {
		fraction sopr(drob.den_, drob.num_);
		return fraction(num_ * sopr.num_, den_ * sopr.den_);
	}
	fraction operator + (const fraction& drob) const {
		long nok = NOK(drob.den_, den_);
		return fraction(num_ * (nok / den_) + drob.num_ * (nok / drob.den_), nok);
	}
	fraction operator - () {
		return fraction(-num_, den_);
	}
	fraction operator - (const fraction& drob) const {
		long nok = NOK(drob.den_, den_);
		return fraction(num_ * (nok / den_) - drob.num_ * (nok / drob.den_), nok);
	}
	bool operator == (const fraction& drob) const {
		return (num_ == drob.num_) && (den_ == drob.den_);
	}
	bool operator > (const fraction& drob) const {
		int nok = NOK(den_, drob.den_);
		return num_ * (nok / den_) > drob.num_ * (nok / drob.den_);
	}
	bool operator < (const fraction& drob) const {
		int nok = NOK(den_, drob.den_);
		return num_ * (nok / den_) < drob.num_ * (nok / drob.den_);
	}
	bool operator != (const fraction& drob) const {
		return (num_ != drob.num_) && (den_ != drob.den_);
	}
	bool operator >= (const fraction& drob) const {
		return (drob == *this) || (*this > drob);
	}
	bool operator <= (const fraction& drob) const {
		return (drob == *this) || (*this < drob);
	}
	void print() const {
		std::cout << num_ << "\n" << "-\n" << den_ << "\n";
	}
};
int main() {
	try {
		fraction drob1(15, -5);
		fraction drob2(4, 3);
		fraction rez = drob1 + drob2;
		rez.print();
		if (drob1 < rez) std::cout << "yes";
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}
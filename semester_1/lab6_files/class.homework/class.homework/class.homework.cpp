#include <iostream>
long NOD(long a, long b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	while (b != 0) {
		long t = b;
		b = a % b;
		a = t;
	}
	if (a == 0) { return 1; }
	return a;
}
long NOK(long a, long b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	long nod = NOD(a, b);
	return (a / nod) * b;
}

class fraction {
private:
	long num_;
	long den_;
public:
	fraction() {
		num_ = 0;
		den_ = 1;
	}
	fraction(long num) {
		num_ = num;
		den_ = 1;
	}
	fraction(long num, long den) {
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
	void print() {
		std::cout << num_ << "\n" << "-\n" << den_ << "\n";
	}
};
int main() {
	fraction drob(15,-5);
	fraction dr(4, 3);
	fraction rez = dr + drob;
	rez.print();
	return 0;
}
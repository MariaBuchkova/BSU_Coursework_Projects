#include <iostream>
class StackArr {
private:
	int* info;
	int top;
	int size;
public:
	StackArr() :size(1000), top(0) {
		info = new int[size];
	}
	~StackArr() {
		delete[] info;
	}
	bool isEmpty() const { return top == 0; }
	bool isFull() const { return top >= size; }
	void push(int value) {
		if (!isFull()) {
			info[top++] = value;
		}
		else {
			throw"Error! stack is isFull (push)";
		}
	}
	int pop() {
		if (!isEmpty()) {
			return info[--top];
		}
		else {
			throw"Error! stack is empty (pop)";
		}
	}
	int getSize() const { return top; }
	int getMaxSize() const { return size; }
	int getTop() const { 
		if (!isEmpty()) {
			return info[top - 1];
		}
		else {
			throw"Error (getTop) ! stack is full ";
		}
	}
	void clear() {
		top = 0;
	}
	void print() {
		for (int i = 0; i < top; ++i) {
			std::cout << info[i] << "\n";
		}
	}
};
class stackList {
private:
	struct list {
		int info;
		list* next;
		list(int value):info(value),next(nullptr){}
	};
	int size;
	list* top;
public:
	stackList():top(nullptr),size(0){}
	~stackList() { clear(); }
	bool isEmpty() { return size == 0; }
	void push(int value) {
		list* newList = new list(value);
		newList->next = top;
		top = newList;
		++size;
	}
	int pop() {
		if (isEmpty()) { throw""; }
		int x = top->info;
		list* temp = top;
		top = top->next;
		delete temp;
		--size;
		return x;
	}
	void clear() { while (!isEmpty()) { pop(); } }
};

class CyclicQueueArr {
private:
	int* info;
	int begin, end, size;
	const int maxsize;
public:
	CyclicQueueArr() :maxsize(100), begin(0), end(-1), size(0) { info = new int[maxsize]; }
	~CyclicQueueArr() { delete[] info; }
	bool empty() const { return size == 0; }
	bool full() const { return size >= maxsize; }
	void push(int value) {
		if (!full()) {
			end = (end + 1) % maxsize;
			info[end] = value;
			++size;
		}
		else {
			throw"push error! queue is isFull.";
		}
	}
	int pop() {
		if (!empty()) {
			int bufer = info[begin];
			begin = (begin + 1) % maxsize;
			--size;
			return bufer;
		}
		else {
			throw "pop error! queue is empty.";
		}
	}
	int front() const {
		if (!empty()) { return info[begin]; }
		else { throw "pop error! queue is empty."; }
	}
	int back() const {
		if (!empty()) { return info[end]; }
		else { throw "pop error! queue is empty."; }
	}
	void clear() {
		size = 0;
		begin = 0;
		end = -1;
	}
	int getBegin()const { return begin; }
	int getEnd()const { return end; }
	int getSize()const { return size; }
	int getMaxSize() const { return maxsize; }
	void print() {
		if (empty()) {
			std::cout << "Queue is empty\n";
			return;
		}
		for (int i = begin, count = 0; count < size; ++count) {
			std::cout << info[i] << "\n";
			i = (i + 1) % maxsize;
		}
	}
};
class LinearQueueArr {
private:
	int* info;
	int begin, end;
	const int size;
public:
	LinearQueueArr() :size(100), begin(0), end(-1) { info = new int[size]; }
	~LinearQueueArr() { delete[] info; }
	bool empty() const { return begin > end; }
	bool full() const { return end >= size - 1; }
	void push(int value) {
		if (!full()) {
			info[++end] = value;
		}
		else {
			throw"push error! queue is isFull.";
		}
	}
	int pop() {
		if (!empty()) {
			int bufer = info[begin++];
			return bufer;
		}
		else {
			throw "pop error! queue is empty.";
		}
	}
	int front () const {
		if (!empty()) { return info[begin]; }
		else { throw "pop error! queue is empty."; }
	}
	int back() const {
		if (!empty()) { return info[end]; }
		else { throw "pop error! queue is empty."; }
	}
	void clear() {
		begin = 0;
		end = -1;
	}
	int getBegin()const { return begin; }
	int getEnd()const { return end; }
	int getMaxSize() const { return size; }
	int getSize() const { return end - begin + 1; }
	void print() {
		if (empty()) {
			std::cout << "Queue is empty\n";
			return;
		}
		for (int i = begin; i < end + 1; ++i) {
			std::cout << info[i] << "\n";
		}
	}
};



int main() {
	try {
		
	}
	catch (const char* msg) {
		std::cerr << msg;
	}
	return 0;
}
/*void setElement(int index, int value) {
	if (index < top) {
		info[index] = value;
	}
	else {
		throw"Error! index beyond stack bounds";
	}
}*/
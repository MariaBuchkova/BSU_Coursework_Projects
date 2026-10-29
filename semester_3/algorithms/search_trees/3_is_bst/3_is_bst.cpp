#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

struct Node {
    long long key;
    long long lo;
    long long hi;

    Node(long long k, long long l, long long h) : key(k), lo(l), hi(h) {}
};

int main() {
    std::ifstream in("bst.in");

    int n;
    in >> n;

    std::vector<Node*> a(n);

    long long m;
    in >> m;
    a[0] = new Node(m, LLONG_MIN, LLONG_MAX);

    bool ok = true;

    for (int i = 1; i < n; ++i) {
        int p;
        char c;
        in >> m >> p >> c;

        Node* par = a[p - 1];
        if (c == 'L') a[i] = new Node(m, par->lo, par->key - 1);
        else a[i] = new Node(m, par->key, par->hi);

        if (m < a[i]->lo || m > a[i]->hi) ok = false;
    }
    in.close();

    std::ofstream out("bst.out");
    if (ok) out << "YES" << std::endl;
    else out << "NO" << std::endl;
    out.close();

    return 0;
}
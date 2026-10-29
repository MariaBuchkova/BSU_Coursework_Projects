#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

struct Node {
    int key;
    int diff;
    Node* l;
    Node* r;
};

Node* add(Node* v, int x) {
    if (v == nullptr) {
        Node* n = new Node;
        n->key = x;
        n->l = nullptr;
        n->r = nullptr;
        return n;
    }
    if (x < v->key) v->l = add(v->l, x);
    else if (x > v->key) v->r = add(v->r, x);
    return v;
}

Node* del(Node* v, int x) {
    if (v == nullptr) return nullptr;
    if (x < v->key) {
        v->l = del(v->l, x);
        return v;
    }
    else if (x > v->key) {
        v->r = del(v->r, x);
        return v;
    }

    if (v->l == nullptr) {
        Node* t = v->r;
        delete v;
        return t;
    }
    else if (v->r == nullptr) {
        Node* t = v->l;
        delete v;
        return t;
    }
    else {
        Node* m = v->r;
        while (m->l != nullptr) {
            m = m->l;
        }
        v->key = m->key;
        v->r = del(v->r, m->key);
        return v;
    }
}

int maxDiff = -1;

int height(Node* v) {
    if (v == nullptr) return -1;
    int hl = height(v->l);
    int hr = height(v->r);
    v->diff = std::abs(hl - hr);
    if (v->diff > maxDiff) maxDiff = v->diff;
    return (hl > hr ? hl : hr) + 1;
}

void collect(Node* v, std::vector<int>& res) {
    if (v == nullptr) return;
    collect(v->l, res);
    if (v->diff == maxDiff) res.push_back(v->key);
    collect(v->r, res);
}

void preOrder(Node* v, std::ofstream& out) {
    if (v == nullptr) return;
    out << v->key << std::endl;
    preOrder(v->l, out);
    preOrder(v->r, out);
}

int main() {
    std::ifstream in("in.txt");
    Node* root = nullptr;

    int x;
    while (in >> x) {
        root = add(root, x);
    }
    in.close();

    height(root);

    std::vector<int> a;
    collect(root, a);

    int m = a.size();
    if (m % 2 == 1) {
        root = del(root, a[m / 2]);
    }

    std::ofstream out("out.txt");
    preOrder(root, out);
    out.close();

    return 0;
}
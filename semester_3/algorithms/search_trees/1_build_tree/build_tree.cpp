#include <iostream>
#include <fstream>

struct Node {
    int key;
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

void preOrder(Node* v, std::ofstream& out) {
    if (v == nullptr) return;
    out << v->key << std::endl;
    preOrder(v->l, out);
    preOrder(v->r, out);
}

int main() {
    std::ifstream in("input.txt");
    Node* root = nullptr;

    int x;
    while (in >> x) {
        root = add(root, x);
    }
    in.close();

    std::ofstream out("output.txt");
    preOrder(root, out);
    out.close();

    return 0;
}
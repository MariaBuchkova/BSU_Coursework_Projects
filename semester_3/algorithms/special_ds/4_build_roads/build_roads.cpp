#include <iostream>
#include <fstream>
#include <vector>

int findpar (int x, std::vector<int>& par ){
    if (par[x - 1] < 0) { return x; }
    return findpar(par[x - 1], par);
}

int main() {

    //std::ios_base::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    std::ifstream in("input.txt");
    int n, q;
    in >> n; in >> q;
    std::vector <int> par(n, -1);

    std::ofstream out("output.txt");
    int v, u, pu, pv;

    int count = n;

    while (q != 0) {
        in >> u; in >> v;
        pu = findpar(u, par);
        pv = findpar(v, par);

        if (pu != pv) {
            --count;
            if (par[pu - 1] <= par[pv - 1]) {
                par[pu - 1] += par[pv - 1];
                par[pv - 1] = pu;
            }
            else if (par[pu - 1] > par[pv - 1]) {
                par[pv - 1] += par[pu - 1];
                par[pu - 1] = pv;
            }
        }

        out << count << "\n";
        --q;
    }


    out.close();

    return 0;
}
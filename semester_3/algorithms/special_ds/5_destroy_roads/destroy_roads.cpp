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
    int n, m,q;
    in >> n; in >>m; in >> q;

    std::vector<int> eu(m), ev(m);
    for (int i = 0; i < m; ++i) {
        in >> eu[i]; in >> ev[i];
    }

    std::vector<int> ides(q);
    std::vector<bool> des(m, false);
    for (int i = 0; i < q; ++i) {
        in >> ides[i];
        des[ides[i]-1] = true;
    }

    std::vector <int> par(n, -1);
    int count = n;
    int pu, pv;

    for (int i = 0; i < m; ++i) {
        if (des[i]) continue;

        pu = findpar(eu[i], par);
        pv = findpar(ev[i], par);

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
    }

    std::ofstream out("output.txt");
    std::string res(q, '0');


    for (int i = q - 1; i >= 0; --i) {
        if (count == 1) res[i] = '1';

        pu = findpar(eu[ides[i]-1], par);
        pv = findpar(ev[ides[i]-1], par);

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
    }
    out << res << "\n";
    out.close();

    return 0;
}
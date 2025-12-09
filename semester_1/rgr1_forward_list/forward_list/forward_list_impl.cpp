#include "forward_list_impl.h"

ForwardList::ForwardList(){}


int main() {
    try {
        ForwardList l;
        l.begin();

    } catch (const char* msg) {
        std::cout << "\n" << msg;
    }
    return 0;
}

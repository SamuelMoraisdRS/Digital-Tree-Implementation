#include "digital_tree.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<char> alfabeto = {'a', 'b', 'c', 'd', 'e'};
    std::vector<std::string> keys = {"cade", "bace", "eba", "deca"};
    digital_tree test1(alfabeto, keys);
    std::cout << "Main: Construiu\n";
    if (test1.search("cade")) {
        std::cout << "Main: Busca funciona\n";
    } else {
        std::cout << "Main: Busca não funciona\n";
    }
    std::cout << "Main: inserindo\n";
    test1.insert("cabe");
     if (test1.search("cabe")) {
        std::cout << "Main: segunda busca funciona\n";
    } else {
        std::cout << "Main: segunda busca não funciona\n";
    }
    return 0;
}
#include "digital_tree.h"
#include <iostream>
#include <vector>
#include <string>

#define _LOG_

#ifdef _LOG_
    #define LOG(str) { std::cout << str << std::endl; } while (false)
#else
    #define LOG(str) {} while (false)
#endif

int main() {
    std::vector<char> alfabeto = {'a', 'b', 'c', 'd', 'e'};
    std::vector<std::string> keys = {"cade", "bace", "eba", "deca"};
    digital_tree test1(alfabeto, keys);
    test1.print();
    LOG("Main: Construiu");
    if (test1.search("cade")) {
        LOG("Main: Busca funciona");
    } else {
        LOG("Main: Busca não funciona");
    }
    LOG("Main: inserindo");
    test1.insert("cabe");
     if (test1.search("cabe")) {
        LOG("Main: segunda busca funciona");
    } else {
        LOG("Main: segunda busca não funciona");
    }
    LOG("Testando Remove");
    test1.remove("cade");
    if (test1.search("cade")) {
        LOG("Remove falhou");       
    } else {
        LOG("Remove Funciona");
    }

   for (auto key : keys) {
        test1.remove(key);
    }
    if (test1.is_empty()) {
        LOG("is_empty funciona.");
    } else {
        LOG("is_empty não funciona.");
    }
    return 0;
}
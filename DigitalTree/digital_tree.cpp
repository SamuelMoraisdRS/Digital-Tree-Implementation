
#include "digital_tree.h"

#ifdef DEBUG
    #define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
    #define DEBUG_MSG(str) do { } while( false )
#endif

digital_tree::digital_tree(std::vector<char> a, std::vector<std::string> keys) {
    alphabet = a;
    for (std::string e : keys) {
        key_bank.push_back(e);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
    std::cout << "Teve segfault\n";
    for (auto e : key_bank) {
        std::cout << "Insere elementos\n";
        insert(e);
    }
}

std::size_t digital_tree::digit_idx(char c) {
    for (std::size_t i {0}; i < alphabet.size(); i++) {
        if (alphabet[i] == c) {
            return i;
        }
    } return -1;    // TODO: replace with an exception
}

std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> digital_tree::search2(const std::string & key) {
    auto ptr = root;
    std::cout << "segfault\n";
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        std::cout << "search2: iteração do loop\n";
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } else {
            std::cout << "chegou no break\n";
            break;
        }  
    }
    std::cout << "Fim do search2\n";
    return std::make_pair(prefix_sz, ptr->get_pointers()[prefix_sz]);
}



bool digital_tree::search(const std::string & key) {
    std::cout << "entra search\n";
    auto ptr = root;
    std::cout << "1\n";
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
    std::cout << "itera while\n";
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        std::cout << "pos = " << pointer_pos << std::endl;
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
        std::cout << "entra if\n";
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } return false;
    }
    std::cout << "sai if\n";
    if (ptr->get_terminal()) {
        return true;
    } return false;
}



void digital_tree::insert(const std::string & key) {
    if (not search(key)) {
        std::cout << "entra insert\n";
        auto prefix_sz {search2(key)};
        auto char_runner {prefix_sz.first};
        auto ptr = prefix_sz.second;
        while (char_runner < key.size()) {
            auto pointer_pos {digit_idx(key.at(char_runner))};
            // Checks if we have a terminal Node
            bool is_terminal {char_runner != key.size() - 1 ? true : false};
            ptr->get_pointers()[pointer_pos] = std::make_shared<Node>(is_terminal, alphabet.size());
        }
    } std::cerr << "Chave ja existente\n";
}



#include "digital_tree.h"
#include <algorithm>    // std::sort

//  Comment the line below if you don't want to print the debug msgs
// #define DEBUG

#ifdef DEBUG
    #define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
    #define DEBUG_MSG(str) do {/* Nothing */} while( false )
#endif

digital_tree::digital_tree(std::vector<char> a, std::vector<std::string> keys) {
    std::sort(a.begin(), a.end());
    alphabet = a;
    for (std::string e : keys) {
        DEBUG_MSG("Ctro: Keys -> " << e);
        key_bank.push_back(e);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
    for (auto e : key_bank) {
        DEBUG_MSG("Ctro: Inserted key -> " << e);
        insert(e);
    }
    DEBUG_MSG("\n\n");
}

std::size_t digital_tree::digit_idx(char c) {
    // TODO : replace with a binary search
    for (std::size_t i {0}; i < alphabet.size(); i++) {
        if (alphabet[i] == c) {
            return i;
        }
    } return -1;    // TODO: replace with an exception
}

std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> digital_tree::__search(const std::string & key) {
    auto ptr = root;
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } else {
            break;
        }  
    }
    return std::make_pair(prefix_sz, ptr);
}

bool digital_tree::search(const std::string & key) {
    auto ptr = root;
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } else {
            return false;
        }
    }
    return ptr->get_terminal();
}

void digital_tree::insert(const std::string & key) {
    if (not search(key)) {
        auto prefix_sz {__search(key)};
        auto char_runner {prefix_sz.first};
        auto ptr = prefix_sz.second;
        while (char_runner < key.size()) {
            auto pointer_pos {digit_idx(key.at(char_runner))};
            ptr->get_pointers()[pointer_pos] = std::make_shared<Node>(false, alphabet.size());
            ptr = ptr->get_pointers()[pointer_pos];
            char_runner++;
        }
        // Sets the last node's terminal bit
        ptr->set_terminal();
        return;
    } std::cerr << "Key already exists: \"" << key << "\"" << std::endl; // TODO: replace with an exception
}


bool digital_tree::is_prefix(std::shared_ptr<digital_tree::Node> n, std::size_t char_idx) const {
    for (std::size_t i {0}; i < n->get_pointers().size(); i++) {
        if (i == char_idx && n->get_pointers()[i] != nullptr) {
            return true;
        }
    } return false;
}

std::shared_ptr<digital_tree::Node> digital_tree::__rem_search(const std::string & key) {
    // We´ll return the last node with more than one not-null child
    auto ptr {root};
    auto prefix_node {ptr}; // the last Node which is a prefix to another key
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        // We already know the key is in the tree, no need to check
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (is_prefix(ptr, pointer_pos)) {
            prefix_node = ptr;
        }
        prefix_sz++;
        ptr = ptr->get_pointers()[pointer_pos];
    }
    return prefix_node;
}

void digital_tree::remove(const std::string & key) {
/*
 Casos:
    1. A chave não tem nenhum prefixo comum a outra chave -> apaga todos os nós
    2. A chave tem prefixo em comum com alguma outra chave -> apaga todos os nós após maior prefixo
    3. A chave é prefixo válido de alguma chave -> Desliga o bit terminal do último nó
*/
   if (search(key)) {
    
   } else {
    std::cerr << "Key not found." << std::endl; // TODO: Replace with an exception
   }
}



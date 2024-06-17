
#include "digital_tree.h"
#include <algorithm>    // std::sort
#include <tuple>    
#include <sstream>

// Comment this line if you don't want the debug msgs to be shown
// #define DEBUG

#ifdef DEBUG
    #define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
    #define DEBUG_MSG(str) do { } while( false )
#endif

// TODO: replace the 'std::cout' debugs for the debug function

digital_tree::digital_tree(std::vector<char> a, std::vector<std::string> keys) {
    alphabet = a;
    for (std::string e : keys) {
        DEBUG_MSG("Ctro: Keys -> " << e);
        key_bank.push_back(e);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
    // std::cout << "Teve segfault\n";
    for (auto e : key_bank) {
        DEBUG_MSG("Ctro: Inserted key -> " << e);
        insert(e);
    }
}

// Suposing the list is sorted already
std::size_t bin_search(const std::vector<char> & list, char c) {
    std::size_t left {0};
    std::size_t right {list.size() - 1};
    while (left < right) {
        std::size_t mid {(left + right) / 2};
        if (list[mid] == c) {
            return mid;
        } else if (list[mid] < c) {
            right = mid;
        } else {
            left = mid;
        }
    } 
    ///TODO: replace with an exception
    return -1;     
}


std::size_t digital_tree::digit_idx(char c) {
    ///TODO: replace with a binary search
    for (std::size_t i {0}; i < alphabet.size(); i++) {
        if (alphabet[i] == c) {
            return i;
        }
     }  return -1;
}    

///TODO: there must be a way to use the 'prefix_sz' size reference parameter instead of returning a pair
std::pair<std::size_t, digital_tree::NodePtr> digital_tree::__search(const std::string & key) {
    auto ptr = root;
    // DEBUG_MSG("segfault\n");
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        DEBUG_MSG("__search: iteração do loop");;
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
            DEBUG_MSG("__search: chegou no normal");
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } else {
            DEBUG_MSG("__search: chegou no break");
            break;
        }  
    }
    DEBUG_MSG("Fim do __search");
    return std::make_pair(prefix_sz, ptr);
}



bool digital_tree::search(const std::string & key) {
    // std::cout << "entra search\n";
    auto ptr = root;
    // std::cout << "1\n";
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
    // std::cout << "itera while\n";
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        // std::cout << "pos = " << pointer_pos << std::endl;
        if (ptr->get_pointers()[pointer_pos].get() != nullptr) {
        // std::cout << "entra if\n";
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } else {
            // std::cout << "Encontrou caractere que não esta na string\n";
            return false;
        }
    } return ptr->get_terminal();
}



void digital_tree::insert(const std::string & key) {
    DEBUG_MSG("Insert : MENSAGEM A SER INSERIDA -> " << key);
    if (not search(key)) {
        // std::cout << "entra insert\n";
        auto prefix_sz {__search(key)};
        auto char_runner {prefix_sz.first};
        auto ptr = prefix_sz.second;
        DEBUG_MSG("Insert: Char_runner sz: " << char_runner);
        while (char_runner < key.size()) {
            DEBUG_MSG("Insert: Itera loop");
            // Encontra a posicao do proximo digito no alfabeto
            auto pointer_pos {digit_idx(key.at(char_runner))};
            DEBUG_MSG("Insert: valor do pointer position: " << pointer_pos);

            // Checks if we have a terminal Node
            bool is_terminal {char_runner != key.size() - 1 ? true : false};
            DEBUG_MSG("Insert: Vai fazer a atribuicao");
            ptr->get_pointers()[pointer_pos] = std::make_shared<Node>(is_terminal, alphabet.size());
            DEBUG_MSG("Insert: Checando se o ponteiro do proximo é null: " << ptr->get_pointers()[pointer_pos].get());
            ptr = ptr->get_pointers()[pointer_pos];
            DEBUG_MSG("Insert: Checando se o o novo valor de 'ptr' é null: " << ptr.get());
            char_runner++;
        }
        // Sets the last node as a terminal bit
        ptr->set_terminal(true);
        return;
    } std::cerr << "Key already exists: \"" << key << "\"" << std::endl; // TODO: replace with an exception
}


bool digital_tree::is_prefix(digital_tree::NodePtr n, std::size_t char_idx) const {
    for (std::size_t i {0}; i < n->get_pointers().size(); i++) {
        if (i == char_idx && n->get_pointers()[i] != nullptr) {
            return true;
        }
    } return false;
}
bool digital_tree::is_prefix(digital_tree::NodePtr n) const {
    for (std::size_t i {0}; i < n->get_pointers().size(); i++) {
        if (n->get_pointers()[i] != nullptr) {
            return true;
        }
    } return false;
}

void digital_tree::__rem(digital_tree::NodePtr & ptr, const std::string & key, std::size_t key_idx,
                         digital_tree::NodePtr prefix_ptr) {
    if (key_idx != key.size()) {
        auto pointer_pos {digit_idx(key.at(key_idx))};
        auto is_p = is_prefix(ptr, key_idx);
        prefix_ptr = is_p ? ptr : prefix_ptr;
        __rem(ptr->get_pointers()[pointer_pos], key, key_idx + 1, prefix_ptr);
    }
    if (key_idx == key.size() - 1 and is_prefix(ptr)) {
        ptr->set_terminal(false);
        return;
    } else if (ptr != prefix_ptr) {
        ptr.reset();
        return;
    } else {
        return;
    }
}

void digital_tree::remove(const std::string & key) {
    if (search(key)) {
    __rem(root, key, 0, root);
    } else {
        ///TODO: Replace with an exception
        std::cerr << "Key \"" << key << "\" not found" << std::endl;
    }
}

void digital_tree::print_rec(digital_tree::NodePtr ptr, std::string & curr_str, std::size_t curr_digit
                             , std::stringstream & return_str) const {
    curr_str += alphabet[curr_digit];
    if (ptr->get_terminal()) {
        return_str << "\"" <<curr_str << "\";" << std::endl;
    }
    bool end_of_path {false};
    for (auto i {0}; i < alphabet.size(); i++) {
        if (ptr->get_pointers()[i] != nullptr) {
            end_of_path = true;
            print_rec(ptr->get_pointers()[i], curr_str, i, return_str);
        }
    }
    curr_str = end_of_path ? "" : curr_str;
}

void digital_tree::print() const {
    std::stringstream return_str;
    return_str << "Strings:\n";
    std::string str {""};
    for (std::size_t i {0}; i < alphabet.size(); i++) {
        if (root->get_pointers()[i] != nullptr) {
            print_rec(root->get_pointers()[i], str, i, return_str);
        }
    } std::cout << return_str.str();
}



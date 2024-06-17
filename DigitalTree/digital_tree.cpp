#include "digital_tree.h"
#include <algorithm>    // std::sort
#include <tuple>    
#include <sstream>

//  Comment the line below if you don't want to print the debug msgs
#define DEBUG

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
        DEBUG_MSG("Ctro: Keys -> " << e);
        key_bank.push_back(e);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
    for (auto e : key_bank) {
        DEBUG_MSG("Ctro: Inserted key -> " << e);
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
    } return ptr->get_terminal();
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



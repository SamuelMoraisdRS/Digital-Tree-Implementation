#include "digital_tree.h"

digital_tree::digital_tree(std::vector<char> a, std::string keys [], std::size_t bank_sz) {
    alphabet = a;
    for (std::size_t i {0}; i < bank_sz; i++) {
        key_bank.push_back(keys[i]);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
}

std::size_t digital_tree::digit_idx(char c) {
    std::size_t idx {0};
    for (char e : alphabet) {
        if (e == c) {
            return idx;
        }
    }
}

std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> digital_tree::search2(const std::string & key) {
    auto ptr = root;
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        prefix_sz++;
        ptr = ptr->get_pointers()[pointer_pos];
    }
    return std::make_pair(prefix_sz, ptr->get_pointers()[prefix_sz]);
}

bool digital_tree::search(const std::string & key) {
    auto ptr = root;
    std::size_t prefix_sz {0};
    while (prefix_sz != key.size()) {
        auto pointer_pos {digit_idx(key.at(prefix_sz))};
        if (ptr->get_pointers()[pointer_pos] != nullptr) {
            prefix_sz++;
            ptr = ptr->get_pointers()[pointer_pos];
        } return false;
    }
    if (ptr->get_terminal()) {
        return true;
    } return false;
}

void digital_tree::insert(const std::string & key) {
    if (not search(key)) {
        auto prefix_sz {search2(key)};
        auto remaining_chars {key.size() - prefix_sz.first};
        auto ptr = prefix_sz.second;
        while 

    } std::cerr << "Chave ja existente\n";
}

#ifndef __DIGITAL__
#define __DIGITAL__
#include "digital_tree.h"
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <utility>
#include <iostream>

class digital_tree
{
    struct Node {
        bool terminal_bit = false;
        // const size_t parent_pos;   // POsition in relation to its parent node
        std::vector<std::shared_ptr<Node>> pointer_vec;
        Node(bool t, std::size_t alphabet_sz) : terminal_bit {t}, pointer_vec(alphabet_sz, nullptr) {}
        std::vector<std::shared_ptr<Node>> & get_pointers() { return pointer_vec; }
        bool get_terminal() { return terminal_bit; }
        void set_terminal() { terminal_bit = true; }
    };
private:
    std::vector<char> alphabet; //!< Char array representing the alphabet 
    std::vector<std::string> key_bank; //!< String bank
    std::shared_ptr<Node> root = nullptr;
public:
    digital_tree(std::vector<char> a, std::vector<std::string> keys);
    bool search(const std::string & key);
    void insert(const std::string & key);
    void remove(const std::string & key);
    void print() const;
private:
    std::size_t digit_idx(char c);
    std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> __search(const std::string & key);
    std::shared_ptr<digital_tree::Node> __rem_search(const std::string & key);
    bool is_prefix(std::shared_ptr<digital_tree::Node> n, std::size_t char_idx) const;
};
#endif // __DIGITAL__




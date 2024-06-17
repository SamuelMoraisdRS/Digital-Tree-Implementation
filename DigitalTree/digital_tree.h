#ifndef __DIGITAL__
#define __DIGITAL__

#include <string>   /// std::string
#include <vector>   /// std::vector
#include <memory>   /// std::unique_pointer
#include <utility>  /// std::pair
#include <iostream> /// std::cout

class digital_tree
{
    struct Node {
        bool terminal_bit = false;
        std::vector<std::shared_ptr<Node>> pointer_vec;
        Node(bool t, std::size_t alphabet_sz) : terminal_bit {t}, pointer_vec(alphabet_sz, nullptr){}
        std::vector<std::shared_ptr<Node>> & get_pointers() { return pointer_vec; }
        bool get_terminal() { return terminal_bit; }
        void set_terminal(bool t) { terminal_bit = t; }

    };
    /// alias
    using NodePtr = std::shared_ptr<digital_tree::Node>;
private:
    std::vector<char> alphabet;             //!< Char array representing the alphabet 
    std::vector<std::string> key_bank;      //!< String bank
    std::shared_ptr<Node> root = nullptr;   //!< Root node
public:
    /// @brief Constructor
    /// @param a Char vector corresponding to the alphabet. 
    /// @param keys Keys stored in the tree
    digital_tree(std::vector<char> a, std::vector<std::string> keys);

    /// @brief Searches for the 'key' string in the tree.
    /// @param key The string to be searched
    /// @return 'true' if the string's been found, 'false' otherwise
    bool search(const std::string & key);

    /// @brief Inserts the given key in the tree
    /// @param key 
    void insert(const std::string & key);
    void remove(const std::string & key);
    /// @brief Prints the strings in the respective alphabetical order
    void print() const;
    /// @return 'true' if the tree is empty, 'false' otherwise
    bool is_empty() const { return is_prefix(root); }
private:
    /// @brief Finds the input char's position within the alphabet vector
    /// @param c 
    std::size_t digit_idx(char c);

    /// @brief Private search method used during 'insertion'
    /// @param key 
    /// @return 
    std::pair<std::size_t, NodePtr> __search(const std::string & key);
    void __rem(NodePtr & ptr ,const std::string & key, std::size_t key_idx,
               NodePtr prefix_ptr);

    bool is_prefix(NodePtr n, std::size_t char_idx) const;
    bool is_prefix(NodePtr n) const;

    /// @brief Recursive method for printing the strings. It performs a DFS and 
    /// @param ptr The current tree node.
    /// @param curr_str The control string
    /// @param curr_digit Idx that'll keep track of the current's node respective digit
    /// @param return_str Stream that accumulates the strings
    void print_rec(digital_tree::NodePtr ptr, std::string & curr_str, std::size_t curr_digit,
                    std::stringstream & return_str) const;
};
#endif // __DIGITAL__




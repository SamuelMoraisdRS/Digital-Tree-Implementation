#include <string>
#include <vector>
#include <memory>
#include <array>
#include <utility>
#include "/home/samuel_morais/github-classroom/selan-active-classes/trabalho-05-hash-table-duplas-samuel_-_kael/source/include/hashtbl.h"

class digital_tree
{
    struct Node {
        bool terminal_bit = false;
        // const size_t parent_pos;   // POsition in relation to its parent node
        std::vector<std::shared_ptr<Node>> pointer_vec;
        Node(bool t, std::size_t alphabet_sz) : terminal_bit {t} {
            // pointer_vec.reserve(alphabet_sz);
        }
        std::vector<std::shared_ptr<Node>> get_pointers() {
            return pointer_vec;
        }
        bool get_terminal() {
            return terminal_bit;
        }

    };
private:
    std::vector<char> alphabet; //!< Char array representing the alphabet 
    std::vector<std::string> key_bank; //!< String bank
    std::shared_ptr<Node> root = nullptr;
public:
    digital_tree(std::vector<char> a, std::string keys [],  std::size_t bank_sz);
    ~digital_tree() = default;
    bool search(const std::string & key);
    void insert(const std::string & key);
    bool remove(const std::string & key);
private:
    std::size_t digit_idx(char c);
    std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> search2(const std::string & key);
};

// digital_tree::digital_tree(/* args */)
// {
// }

// digital_tree::~digital_tree()
// {
// }




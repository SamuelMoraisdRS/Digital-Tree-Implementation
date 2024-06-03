
#include "digital_tree.h"

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
        DEBUG_MSG("Ctro: Chaves -> " << e);
        key_bank.push_back(e);
    }
    root = std::make_shared<Node>(false, alphabet.size()); 
    // std::cout << "Teve segfault\n";
    for (auto e : key_bank) {
        DEBUG_MSG("Ctro: Chave a ser inserida -> " << e);
        insert(e);
    }
    // std::cout << "\n\n";
}

std::size_t digital_tree::digit_idx(char c) {
    for (std::size_t i {0}; i < alphabet.size(); i++) {
        if (alphabet[i] == c) {
            return i;
        }
    } return -1;    // TODO: replace with an exception
}

std::pair<std::size_t, std::shared_ptr<digital_tree::Node>> digital_tree::__search(const std::string & key) {
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
    }
    // std::cout << "sai if\n";
    if (ptr->get_terminal()) {
        return true;
    } return false;
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
        ptr->set_terminal();
        return;
    } std::cerr << "Chave ja existente: " << key << std::endl; // TODO: replace with an exception
}



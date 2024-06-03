cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(DigitalTreeProject)

# Definir o padrão de compilação como C++11
set(CMAKE_CXX_STANDARD 11)

# Adicionar os arquivos de origem
add_executable(DigitalTreeProject main.cpp digital_tree.cpp)

# Incluir diretórios de cabeçalhos
target_include_directories(DigitalTreeProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

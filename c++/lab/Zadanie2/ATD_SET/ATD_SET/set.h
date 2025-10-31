#pragma once
#include "hash_table.h"
#include <string>

class Set {
private:
    ChainingHashTable table;
    int tableSize;

public:
    Set(int size = 100);

    bool add(int value);      // SETADD
    bool remove(int value);   // SETDEL
    bool contains(int value); // SET_AT

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
};

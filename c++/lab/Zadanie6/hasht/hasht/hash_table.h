#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include "array.h"
#include "listTwo.h"

class ChainingHashTable {
private:
    Array* table;
    int size;

    int hash(int key) const;
    ForwardListTwo* getList(int index) const;
    void clearList(ForwardListTwo* list);

public:
    ChainingHashTable(int tableSize);
    ~ChainingHashTable();

    void insert(int key);
    bool search(int key) const;
    void remove(int key);  // Добавляем метод удаления
    void getStatistics(int& minLength, int& maxLength, double& avgLength) const;
    void printDetailedStatistics() const;
};

#endif
#include "Set.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Set::Set(int size) : table(size), tableSize(size) {}

bool Set::add(int value) {
    if (table.search(value))
        return false;
    table.insert(value);
    return true;
}

bool Set::remove(int value) {
    if (!table.search(value))
        return false;
    table.remove(value);
    return true;
}

bool Set::contains(int value) {
    return table.search(value);
}

void Set::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                int value = stoi(line);
                table.insert(value);
            }
            catch (...) {
                cerr << "Неверный формат данных в файле: " << line << endl;
            }
        }
    }
    file.close();
}

void Set::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи " << filename << endl;
        return;
    }

    for (int i = 0; i < tableSize; i++) {
        ForwardListTwo* list = table.getList(i);
        if (list && list->head) {
            DoublyNode* current = list->head;
            while (current) {
                file << current->node << endl;
                current = current->next;
            }
        }
    }
    file.close();
}

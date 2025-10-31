#include <iostream>
#include <string>
#include <algorithm>
#include "hash_table.h"

using namespace std;

// Хеш-функция
int ChainingHashTable::hash(int key) const {
    return abs(key) % size;
}

// Получение списка по индексу
ForwardListTwo* ChainingHashTable::getList(int index) const {
    if (index < 0 || index >= size) return nullptr;
    string ptrStr = get(*table, index);
    if (ptrStr.empty()) return nullptr;
    return reinterpret_cast<ForwardListTwo*>(stoll(ptrStr));
}

// Очистка списка
void ChainingHashTable::clearList(ForwardListTwo* list) {
    if (!list) return;
    while (list->head != nullptr) {
        deleteNodeHeadTwo(list);
    }
    delete list;
}

// Конструктор
ChainingHashTable::ChainingHashTable(int tableSize) : size(tableSize) {
    table = new Array;
    init(*table, size);

    for (int i = 0; i < size; i++) {
        ForwardListTwo* newList = new ForwardListTwo;
        newList->head = nullptr;
        newList->tail = nullptr;
        add(*table, "");
        set(*table, i, to_string(reinterpret_cast<long long>(newList)));
    }
}

// Деструктор
ChainingHashTable::~ChainingHashTable() {
    for (int i = 0; i < size; i++) {
        ForwardListTwo* list = getList(i);
        clearList(list);
    }
    destroy(*table);
    delete table;
}

// Вставка элемента
void ChainingHashTable::insert(int key) {
    int index = hash(key);
    ForwardListTwo* list = getList(index);
    if (list) {
        addNodeTailTwo(list, to_string(key));
    }
}

// Поиск элемента
bool ChainingHashTable::search(int key) const {
    int index = hash(key);
    ForwardListTwo* list = getList(index);
    if (!list) return false;
    return findNodeIndexTwo(list, to_string(key));
}

// Получение статистики
void ChainingHashTable::getStatistics(int& minLength, int& maxLength, double& avgLength) const {
    minLength = INT_MAX;
    maxLength = 0;
    int totalElements = 0;
    int nonEmptyBuckets = 0;

    for (int i = 0; i < size; i++) {
        ForwardListTwo* list = getList(i);
        if (list) {
            int listSize = countNodesTwo(*list);
            if (listSize > 0) {
                if (listSize < minLength) minLength = listSize;
                if (listSize > maxLength) maxLength = listSize;
                totalElements += listSize;
                nonEmptyBuckets++;
            }
        }
    }

    if (minLength == INT_MAX) minLength = 0;
    avgLength = nonEmptyBuckets > 0 ? static_cast<double>(totalElements) / nonEmptyBuckets : 0;
}

void ChainingHashTable::remove(int key) {
    int index = hash(key);
    ForwardListTwo* list = getList(index);
    if (list) {
        deleteNodeIndexTwo(list, to_string(key));
    }
} 

// Детальная статистика
void ChainingHashTable::printDetailedStatistics() const {
    int totalElements = 0;
    int emptyBuckets = 0;
    int maxChain = 0;
    int minChain = INT_MAX;

    cout << "Распределение цепочек:\n";
    for (int i = 0; i < size; i++) {
        ForwardListTwo* list = getList(i);
        int chainLength = list ? countNodesTwo(*list) : 0;

        if (chainLength == 0) emptyBuckets++;
        if (chainLength > maxChain) maxChain = chainLength;
        if (chainLength < minChain && chainLength > 0) minChain = chainLength;

        totalElements += chainLength;

        if (i < 10) { // Показываем первые 10 цепочек для примера
            cout << "Ячейка " << i << ": " << chainLength << " элементов\n";
        }
    }

    cout << "\nОбщая статистика:\n";
    cout << "Минимальная длина непустой цепочки: " << (minChain == INT_MAX ? 0 : minChain) << "\n";
    cout << "Максимальная длина цепочки: " << maxChain << "\n";
    cout << "Пустых ячеек: " << emptyBuckets << " из " << size << "\n";
    cout << "Общее количество элементов: " << totalElements << "\n";
    cout << "Коэффициент заполнения: " << static_cast<double>(totalElements) / size << "\n";
}
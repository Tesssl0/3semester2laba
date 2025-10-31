// LRUCache.cpp
#include "LRU_Cache.h"
#include <iostream>
#include <sstream>

using namespace std;

void processLRUQueries() {
    int cap, Q;
    cout << "Введите емкость кэша: ";
    cin >> cap;
    cout << "Введите количество запросов: ";
    cin >> Q;
    cin.ignore();

    LRUCache cache(cap);

    cout << "Введите запросы (SET x y или GET x):" << endl;

    // Счетчик для результатов GET
    int getCount = 0;
    const int MAX_RESULTS = 100;
    string results[MAX_RESULTS];

    for (int i = 0; i < Q; i++) {
        string query;
        getline(cin, query);

        istringstream iss(query);
        string command;
        iss >> command;

        // Простая конвертация в верхний регистр без algorithm
        for (size_t j = 0; j < command.length(); j++) {
            if (command[j] >= 'a' && command[j] <= 'z') {
                command[j] = command[j] - 'a' + 'A';
            }
        }

        if (command == "SET") {
            int key, value;
            if (iss >> key >> value) {
                cache.set(key, value);
                cout << "SET " << key << " " << value << " выполнено" << endl;
            }
        }
        else if (command == "GET") {
            int key;
            if (iss >> key) {
                int result = cache.get(key);
                if (getCount < MAX_RESULTS) {
                    results[getCount] = to_string(result);
                    getCount++;
                }
                cout << "GET " << key << " = " << result << endl;
            }
        }
        cache.printCache();
    }

    cout << "Результаты: ";
    for (int i = 0; i < getCount; i++) {
        cout << results[i];
        if (i < getCount - 1) {
            cout << " ";
        }
    }
    cout << endl;
}
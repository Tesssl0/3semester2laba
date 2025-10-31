// LRUCache.cpp
#include "LRU_Cache.h"
#include <iostream>
#include <sstream>

using namespace std;

void processLRUQueries() {
    int cap, Q;
    cout << "������� ������� ����: ";
    cin >> cap;
    cout << "������� ���������� ��������: ";
    cin >> Q;
    cin.ignore();

    LRUCache cache(cap);

    cout << "������� ������� (SET x y ��� GET x):" << endl;

    // ������� ��� ����������� GET
    int getCount = 0;
    const int MAX_RESULTS = 100;
    string results[MAX_RESULTS];

    for (int i = 0; i < Q; i++) {
        string query;
        getline(cin, query);

        istringstream iss(query);
        string command;
        iss >> command;

        // ������� ����������� � ������� ������� ��� algorithm
        for (size_t j = 0; j < command.length(); j++) {
            if (command[j] >= 'a' && command[j] <= 'z') {
                command[j] = command[j] - 'a' + 'A';
            }
        }

        if (command == "SET") {
            int key, value;
            if (iss >> key >> value) {
                cache.set(key, value);
                cout << "SET " << key << " " << value << " ���������" << endl;
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

    cout << "����������: ";
    for (int i = 0; i < getCount; i++) {
        cout << results[i];
        if (i < getCount - 1) {
            cout << " ";
        }
    }
    cout << endl;
}
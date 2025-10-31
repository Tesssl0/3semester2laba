// main.cpp
#include <iostream>
#include "LRU_Cache.h"

using namespace std;

void runTestCases() {
    cout << "=== ���� 1 ===" << endl;
    cout << "cap = 2, Q = 2" << endl;
    cout << "Queries = SET 1 2 GET 1" << endl;

    LRUCache cache1(2);
    cache1.set(1, 2);
    cache1.printCache();
    int result1 = cache1.get(1);
    cout << "GET 1 = " << result1 << endl;
    cout << "���������: 2" << endl;

    cout << "\n=== ���� 2 ===" << endl;
    cout << "cap = 2, Q = 8" << endl;
    cout << "Queries = SET 1 2 SET 2 3 SET 1 5 SET 4 5 SET 6 7 GET 4 SET 1 2 GET 3" << endl;

    LRUCache cache2(2);

    // ������ ���������� GET �������� � �������
    int results[10];
    int resultCount = 0;

    cache2.set(1, 2);
    cache2.printCache();
    cache2.set(2, 3);
    cache2.printCache();
    cache2.set(1, 5);
    cache2.printCache();
    cache2.set(4, 5);
    cache2.printCache();
    cache2.set(6, 7);
    cache2.printCache();

    results[resultCount++] = cache2.get(4);
    cout << "GET 4 = " << results[resultCount - 1] << endl;

    cache2.set(1, 2);
    cache2.printCache();

    results[resultCount++] = cache2.get(3);
    cout << "GET 3 = " << results[resultCount - 1] << endl;

    cout << "���������: ";
    for (int i = 0; i < resultCount; i++) {
        cout << results[i];
        if (i < resultCount - 1) {
            cout << " ";
        }
    }
    cout << endl;
    cout << "���������: 5 -1" << endl;
}

int main() {
    int choice;

    do {
        cout << "\n=== LRU Cache Menu ===" << endl;
        cout << "1. ��������� �������� �������" << endl;
        cout << "2. ������ ���� �������" << endl;
        cout << "3. �����" << endl;
        cout << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            runTestCases();
            break;
        case 2:
            processLRUQueries();
            break;
        case 3:
            cout << "�����..." << endl;
            break;
        default:
            cout << "�������� �����!" << endl;
        }
    } while (choice != 3);

    return 0;
}
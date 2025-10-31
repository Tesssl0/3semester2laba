#include <iostream>
#include <string>
#include "Set.h"

using namespace std;

// ������� ��� �������������� ���� �������� � ���������� �����
int pairToInt(const string& pair) {
    return (pair[0] - 'A') * 26 + (pair[1] - 'A');
}

int main() {
    string genome1, genome2;
    cin >> genome1 >> genome2;

    // ������� ��������� ��� �������� ��� ��������� ������� ������
    Set pairsSet(1000);

    // ��������� ��� ���� �� ������� ������ � ���������
    for (size_t i = 0; i + 1 < genome2.length(); i++) {
        string pair = genome2.substr(i, 2);
        pairsSet.add(pairToInt(pair));
    }

    int closeness = 0;

    // ������������ ���� �� ������� ������, ������� ���� �� ������
    for (size_t i = 0; i + 1 < genome1.length(); i++) {
        string pair = genome1.substr(i, 2);
        int pairValue = pairToInt(pair);

        // ���� ���� ������������ �� ������ ������
        if (pairsSet.contains(pairValue)) {
            closeness++;
        }
    }

    cout << closeness << endl;
    return 0;
}
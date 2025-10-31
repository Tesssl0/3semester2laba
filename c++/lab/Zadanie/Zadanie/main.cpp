#include <iostream>
#include <string>
#include "TaskScheduler.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
    setlocale(LC_ALL, "Ru");
    Array tasks, dependencies;
    init(tasks, 10);
    init(dependencies, 10);

    cout << "=== �������� ���������� ����� � ������������� ===" << endl;

    // ���� �����
    int taskCount;
    cout << "������� ���������� �����: ";
    cin >> taskCount;
    clearInputBuffer();

    cout << "������� �������� ����� (������ � ����� ������):" << endl;
    for (int i = 0; i < taskCount; i++) {
        string task;
        cout << "������ " << (i + 1) << ": ";
        getline(cin, task);
        add(tasks, task);
    }

    // ���� ������������
    int depCount;
    cout << "\n������� ���������� ������������: ";
    cin >> depCount;
    clearInputBuffer();

    if (depCount > 0) {
        cout << "������� ����������� � ������� '���������_������,��������_������':" << endl;
        cout << "������: A,B  (������ A ������� �� ���������� ������ B)" << endl;

        for (int i = 0; i < depCount; i++) {
            string dep;
            cout << "����������� " << (i + 1) << ": ";
            getline(cin, dep);

            // ��������� ������
            if (dep.find(',') == string::npos) {
                cout << "������: ����������� ������ 'A,B'. ���������� �����." << endl;
                i--;
                continue;
            }

            // ��������� ������������� �����
            size_t comma = dep.find(',');
            string after = dep.substr(0, comma);
            string before = dep.substr(comma + 1);

            if (findInArray(tasks, after) == -1 || findInArray(tasks, before) == -1) {
                cout << "������: ���� �� ����� �� �������. ���������� �����." << endl;
                i--;
                continue;
            }

            add(dependencies, dep);
        }
    }

    // ����� ��������� ������
    cout << "\n=== ��������� ������ ===" << endl;
    cout << "������: ";
    print(tasks);
    cout << "�����������: ";
    print(dependencies);

    // �������� ����������� ����������
    cout << "\n=== ��������� �������� ===" << endl;
    if (canFinish(tasks, dependencies)) {
        cout << "�������� ��������� ��� ������" << endl;
    }
    else {
        cout << " ���������� ��������� ��� ������ (��������� ���� ������������)" << endl;
    }

    // ������������ ������
    destroy(tasks);
    destroy(dependencies);

    cout << "\n������� Enter ��� ������...";
    clearInputBuffer();
    getchar();

    return 0;
}
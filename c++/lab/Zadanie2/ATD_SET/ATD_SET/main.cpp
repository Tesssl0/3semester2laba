#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "Set.h"

using namespace std;

void printFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������: �� ������� ������� ���� " << filename << endl;
        return;
    }
    cout << "���������� ����� " << filename << ":" << endl;
    cout << "----------------------------------------" << endl;
    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        if (!line.empty()) {
            cout << lineNumber++ << ": " << line << endl;
        }
    }
    if (lineNumber == 1)
        cout << "���� ����" << endl;
    cout << "----------------------------------------" << endl;
    file.close();
}

void printUsage() {
    cout << "�������������: ./program --file <����> --query <��������>" << endl;
    cout << "��������� �������:" << endl;
    cout << "  SETADD <�����>  - �������� ������� � ���������" << endl;
    cout << "  SETDEL <�����>  - ������� ������� �� ���������" << endl;
    cout << "  SET_AT <�����>  - ��������� ������� ��������" << endl;
    cout << "  SHOW_FILE       - ������� ���������� �����" << endl;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    if (argc != 5) {
        printUsage();
        return 1;
    }

    string filename, query;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc)
            filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc)
            query = argv[++i];
    }

    if (filename.empty() || query.empty()) {
        printUsage();
        return 1;
    }

    Set mySet;
    mySet.loadFromFile(filename);

    istringstream iss(query);
    string cmd, valueStr;
    iss >> cmd >> valueStr;

    if (cmd == "SHOW_FILE") {
        printFile(filename);
        return 0;
    }

    if (valueStr.empty()) {
        cerr << "������: �� ������� �������� ��� ��������" << endl;
        return 1;
    }

    try {
        int value = stoi(valueStr);
        if (cmd == "SETADD") {
            if (mySet.add(value)) {
                cout << "������� " << value << " ��������" << endl;
                mySet.saveToFile(filename);
            }
            else {
                cout << "������� " << value << " ��� ����������" << endl;
            }
        }
        else if (cmd == "SETDEL") {
            if (mySet.remove(value)) {
                cout << "������� " << value << " �����" << endl;
                mySet.saveToFile(filename);
            }
            else {
                cout << "������� " << value << " �� ������" << endl;
            }
        }
        else if (cmd == "SET_AT") {
            cout << "������� " << value
                << (mySet.contains(value) ? " ������������" : " �����������")
                << " � ���������" << endl;
        }
        else {
            cerr << "����������� ��������: " << cmd << endl;
            printUsage();
            return 1;
        }
    }
    catch (...) {
        cerr << "������: ������������ �������� �����" << endl;
        return 1;
    }

    return 0;
}

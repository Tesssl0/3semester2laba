#include "fullBinaryTree.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    fullBinaryTree tree;
    string input;

    cout << "������� ������������������ ����� ����� (��� ���������� ������� 'q'):" << endl;

    while (true) {
        cin >> input;

        if (input == "q" || input == "Q") {
            break;
        }

        try {
            stoi(input); // ���������, ��� ������� �����

            // ���� ����� ��� � ������, ��������� ���
            if (BFS(&tree, input) == nullptr) {
                insertBST(&tree, input);
            }
        }
        catch (const exception& e) {
            cout << "������: '" << input << "' �� �������� ������" << endl;
            break;
        }
    }

    // ��������� ������ ������ � ������� ������� �� ����������
    int height = getTreeHeight(tree.root);
    cout << "������ ������������� ������: " << height << endl;

    // ������� ������
    clearFullBinaryTree(&tree);

    return 0;
}
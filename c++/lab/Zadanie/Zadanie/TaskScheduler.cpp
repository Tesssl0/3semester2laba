#include "TaskScheduler.h"
#include <iostream>
#include <string>

using namespace std;

// ��������������� ����������� ������� ��� ������ ������
bool hasCycle(int taskIndex, Array& graph, bool visited[], bool inStack[],
    Array& tasks, Stack& stack) {
    if (inStack[taskIndex]) return true; // ������ ����
    if (visited[taskIndex]) return false; // ��� ���������

    visited[taskIndex] = true;
    inStack[taskIndex] = true;
    stack.push(get(tasks, taskIndex));

    // �������� ������ ������������ ��� ������� ������
    string dependencies = get(graph, taskIndex);
    for (int i = 0; i < length(tasks); i++) {
        string taskName = get(tasks, i);
        // ���������, ���� �� ������� ������ � ������������
        if (dependencies.find(taskName) != string::npos) {
            // ���� ����������� taskIndex -> i
            if (hasCycle(i, graph, visited, inStack, tasks, stack)) {
                return true;
            }
        }
    }

    stack.pop();
    inStack[taskIndex] = false;
    return false;
}

bool canFinish(Array& tasks, Array& dependencies) {
    int taskCount = length(tasks);

    if (taskCount == 0) return true;

    // ������� ���� � ���� ������� ����� (������ ������ �������� �����������)
    Array graph;
    init(graph, taskCount);
    for (int i = 0; i < taskCount; i++) {
        add(graph, ""); // �������������� ������� ��������
    }

    // ��������� ����: ��� ������ ������ ��������� ������ � �� �������������
    for (int i = 0; i < length(dependencies); i++) {
        string dep = get(dependencies, i);
        // dep � ������� "A,B" ��� A ������� �� B
        size_t comma = dep.find(',');
        if (comma != string::npos) {
            string after = dep.substr(0, comma); // ������, ������� �������
            string before = dep.substr(comma + 1); // ������, �� ������� �������

            int afterIndex = findInArray(tasks, after);
            int beforeIndex = findInArray(tasks, before);

            if (afterIndex != -1 && beforeIndex != -1) {
                // ��������� ����������� � ����: before -> after
                string currentDeps = get(graph, beforeIndex);
                if (currentDeps.find(after) == string::npos) {
                    set(graph, beforeIndex, currentDeps + after + ",");
                }
            }
        }
    }

    // ������� ��� ������������ ���������
    bool* visited = new bool[taskCount];
    bool* inStack = new bool[taskCount];
    for (int i = 0; i < taskCount; i++) {
        visited[i] = false;
        inStack[i] = false;
    }

    Stack dfsStack(taskCount, true); // ����� �����

    // ��������� ������ ������ �� �����
    bool hasCycleFound = false;
    for (int i = 0; i < taskCount; i++) {
        if (!visited[i]) {
            if (hasCycle(i, graph, visited, inStack, tasks, dfsStack)) {
                hasCycleFound = true;
                break;
            }
        }
    }

    // ����������� �������
    delete[] visited;
    delete[] inStack;
    destroy(graph);

    return !hasCycleFound; // ���� ������ ��� - ����� ���������
}
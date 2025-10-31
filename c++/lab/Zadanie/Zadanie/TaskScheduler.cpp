#include "TaskScheduler.h"
#include <iostream>
#include <string>

using namespace std;

// Вспомогательная рекурсивная функция для поиска циклов
bool hasCycle(int taskIndex, Array& graph, bool visited[], bool inStack[],
    Array& tasks, Stack& stack) {
    if (inStack[taskIndex]) return true; // Найден цикл
    if (visited[taskIndex]) return false; // Уже проверили

    visited[taskIndex] = true;
    inStack[taskIndex] = true;
    stack.push(get(tasks, taskIndex));

    // Получаем список зависимостей для текущей задачи
    string dependencies = get(graph, taskIndex);
    for (int i = 0; i < length(tasks); i++) {
        string taskName = get(tasks, i);
        // Проверяем, есть ли текущая задача в зависимостях
        if (dependencies.find(taskName) != string::npos) {
            // Есть зависимость taskIndex -> i
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

    // Создаем граф в виде массива строк (каждая строка содержит зависимости)
    Array graph;
    init(graph, taskCount);
    for (int i = 0; i < taskCount; i++) {
        add(graph, ""); // Инициализируем пустыми строками
    }

    // Заполняем граф: для каждой задачи сохраняем строку с ее зависимостями
    for (int i = 0; i < length(dependencies); i++) {
        string dep = get(dependencies, i);
        // dep в формате "A,B" где A зависит от B
        size_t comma = dep.find(',');
        if (comma != string::npos) {
            string after = dep.substr(0, comma); // Задача, которая зависит
            string before = dep.substr(comma + 1); // Задача, от которой зависит

            int afterIndex = findInArray(tasks, after);
            int beforeIndex = findInArray(tasks, before);

            if (afterIndex != -1 && beforeIndex != -1) {
                // Добавляем зависимость в граф: before -> after
                string currentDeps = get(graph, beforeIndex);
                if (currentDeps.find(after) == string::npos) {
                    set(graph, beforeIndex, currentDeps + after + ",");
                }
            }
        }
    }

    // Массивы для отслеживания состояния
    bool* visited = new bool[taskCount];
    bool* inStack = new bool[taskCount];
    for (int i = 0; i < taskCount; i++) {
        visited[i] = false;
        inStack[i] = false;
    }

    Stack dfsStack(taskCount, true); // Тихий режим

    // Проверяем каждую задачу на циклы
    bool hasCycleFound = false;
    for (int i = 0; i < taskCount; i++) {
        if (!visited[i]) {
            if (hasCycle(i, graph, visited, inStack, tasks, dfsStack)) {
                hasCycleFound = true;
                break;
            }
        }
    }

    // Освобождаем ресурсы
    delete[] visited;
    delete[] inStack;
    destroy(graph);

    return !hasCycleFound; // Если циклов нет - можно выполнить
}
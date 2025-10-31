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

    cout << "=== Проверка выполнения задач с зависимостями ===" << endl;

    // Ввод задач
    int taskCount;
    cout << "Введите количество задач: ";
    cin >> taskCount;
    clearInputBuffer();

    cout << "Введите названия задач (каждое с новой строки):" << endl;
    for (int i = 0; i < taskCount; i++) {
        string task;
        cout << "Задача " << (i + 1) << ": ";
        getline(cin, task);
        add(tasks, task);
    }

    // Ввод зависимостей
    int depCount;
    cout << "\nВведите количество зависимостей: ";
    cin >> depCount;
    clearInputBuffer();

    if (depCount > 0) {
        cout << "Введите зависимости в формате 'ЗАВИСИМАЯ_ЗАДАЧА,ОСНОВНАЯ_ЗАДАЧА':" << endl;
        cout << "Пример: A,B  (задача A зависит от выполнения задачи B)" << endl;

        for (int i = 0; i < depCount; i++) {
            string dep;
            cout << "Зависимость " << (i + 1) << ": ";
            getline(cin, dep);

            // Проверяем формат
            if (dep.find(',') == string::npos) {
                cout << "Ошибка: используйте формат 'A,B'. Попробуйте снова." << endl;
                i--;
                continue;
            }

            // Проверяем существование задач
            size_t comma = dep.find(',');
            string after = dep.substr(0, comma);
            string before = dep.substr(comma + 1);

            if (findInArray(tasks, after) == -1 || findInArray(tasks, before) == -1) {
                cout << "Ошибка: одна из задач не найдена. Попробуйте снова." << endl;
                i--;
                continue;
            }

            add(dependencies, dep);
        }
    }

    // Вывод введенных данных
    cout << "\n=== Введенные данные ===" << endl;
    cout << "Задачи: ";
    print(tasks);
    cout << "Зависимости: ";
    print(dependencies);

    // Проверка возможности выполнения
    cout << "\n=== Результат проверки ===" << endl;
    if (canFinish(tasks, dependencies)) {
        cout << "ВОЗМОЖНО выполнить все задачи" << endl;
    }
    else {
        cout << " НЕВОЗМОЖНО выполнить все задачи (обнаружен цикл зависимостей)" << endl;
    }

    // Освобождение памяти
    destroy(tasks);
    destroy(dependencies);

    cout << "\nНажмите Enter для выхода...";
    clearInputBuffer();
    getchar();

    return 0;
}
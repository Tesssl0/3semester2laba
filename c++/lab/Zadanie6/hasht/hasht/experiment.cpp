#include "experiment.h"
#include <iostream>
#include <iomanip>

ExperimentResult HashTableExperiment::runSingleExperiment(int N) {
    ExperimentResult result;
    result.tableSize = std::max(1, N / 100);
    result.loadFactor = static_cast<double>(N) / result.tableSize;

    // Генерация случайных чисел
    Timer timer;
    timer.start();
    Array* randomNumbers = RandomGenerator::generateRandomNumbers(N);
    result.genTime = timer.elapsedMillis();

    // Заполнение хеш-таблицы
    ChainingHashTable hashTable(result.tableSize);

    timer.start();
    for (int i = 0; i < length(*randomNumbers); ++i) {
        int num = std::stoi(get(*randomNumbers, i));
        hashTable.insert(num);
    }
    result.insertTime = timer.elapsedMillis();

    // Получение статистики
    hashTable.getStatistics(result.minLength, result.maxLength, result.avgLength);

    // Очистка
    destroy(*randomNumbers);
    delete randomNumbers;

    return result;
}

void HashTableExperiment::runComparisonExperiment(int N) {
    std::cout << "=== Сравнительный эксперимент для N = " << N << " ===\n";

    Array* randomNumbers = RandomGenerator::generateRandomNumbers(N);
    int tableSizes[] = { N / 200, N / 100, N / 50, N / 20 };

    for (int tableSize : tableSizes) {
        if (tableSize < 1) tableSize = 1;

        ChainingHashTable hashTable(tableSize);
        for (int i = 0; i < length(*randomNumbers); ++i) {
            int num = std::stoi(get(*randomNumbers, i));
            hashTable.insert(num);
        }

        int minLength, maxLength;
        double avgLength;
        hashTable.getStatistics(minLength, maxLength, avgLength);

        std::cout << "Размер таблицы: " << std::setw(6) << tableSize
            << " | Заполнение: " << std::setw(8) << std::fixed << std::setprecision(2)
            << static_cast<double>(N) / tableSize
            << " | Цепочки: мин=" << std::setw(3) << minLength
            << ", макс=" << std::setw(3) << maxLength
            << ", средняя=" << std::setw(6) << std::setprecision(2) << avgLength << "\n";
    }

    destroy(*randomNumbers);
    delete randomNumbers;
    std::cout << "\n" << std::string(50, '=') << "\n\n";
}

void HashTableExperiment::printResult(const ExperimentResult& result, int N) {
    std::cout << "=== Эксперимент для N = " << N << " ===\n";
    std::cout << "Размер хеш-таблицы: " << result.tableSize << "\n";
    std::cout << "Коэффициент заполнения: " << std::fixed << std::setprecision(2)
        << result.loadFactor << "\n";
    std::cout << "Время генерации чисел: " << result.genTime << " мс\n";
    std::cout << "Время вставки: " << result.insertTime << " мс\n";
    std::cout << "\nРезультаты:\n";
    std::cout << "Самая короткая цепочка: " << result.minLength << "\n";
    std::cout << "Самая длинная цепочка: " << result.maxLength << "\n";
    std::cout << "Средняя длина непустой цепочки: " << std::fixed << std::setprecision(2)
        << result.avgLength << "\n";
}

void HashTableExperiment::printDetailedStatistics(const ChainingHashTable& hashTable) {
    hashTable.printDetailedStatistics();
}
#include "experiment.h"
#include <iostream>
#include <iomanip>

ExperimentResult HashTableExperiment::runSingleExperiment(int N) {
    ExperimentResult result;
    result.tableSize = std::max(1, N / 100);
    result.loadFactor = static_cast<double>(N) / result.tableSize;

    // ��������� ��������� �����
    Timer timer;
    timer.start();
    Array* randomNumbers = RandomGenerator::generateRandomNumbers(N);
    result.genTime = timer.elapsedMillis();

    // ���������� ���-�������
    ChainingHashTable hashTable(result.tableSize);

    timer.start();
    for (int i = 0; i < length(*randomNumbers); ++i) {
        int num = std::stoi(get(*randomNumbers, i));
        hashTable.insert(num);
    }
    result.insertTime = timer.elapsedMillis();

    // ��������� ����������
    hashTable.getStatistics(result.minLength, result.maxLength, result.avgLength);

    // �������
    destroy(*randomNumbers);
    delete randomNumbers;

    return result;
}

void HashTableExperiment::runComparisonExperiment(int N) {
    std::cout << "=== ������������� ����������� ��� N = " << N << " ===\n";

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

        std::cout << "������ �������: " << std::setw(6) << tableSize
            << " | ����������: " << std::setw(8) << std::fixed << std::setprecision(2)
            << static_cast<double>(N) / tableSize
            << " | �������: ���=" << std::setw(3) << minLength
            << ", ����=" << std::setw(3) << maxLength
            << ", �������=" << std::setw(6) << std::setprecision(2) << avgLength << "\n";
    }

    destroy(*randomNumbers);
    delete randomNumbers;
    std::cout << "\n" << std::string(50, '=') << "\n\n";
}

void HashTableExperiment::printResult(const ExperimentResult& result, int N) {
    std::cout << "=== ����������� ��� N = " << N << " ===\n";
    std::cout << "������ ���-�������: " << result.tableSize << "\n";
    std::cout << "����������� ����������: " << std::fixed << std::setprecision(2)
        << result.loadFactor << "\n";
    std::cout << "����� ��������� �����: " << result.genTime << " ��\n";
    std::cout << "����� �������: " << result.insertTime << " ��\n";
    std::cout << "\n����������:\n";
    std::cout << "����� �������� �������: " << result.minLength << "\n";
    std::cout << "����� ������� �������: " << result.maxLength << "\n";
    std::cout << "������� ����� �������� �������: " << std::fixed << std::setprecision(2)
        << result.avgLength << "\n";
}

void HashTableExperiment::printDetailedStatistics(const ChainingHashTable& hashTable) {
    hashTable.printDetailedStatistics();
}
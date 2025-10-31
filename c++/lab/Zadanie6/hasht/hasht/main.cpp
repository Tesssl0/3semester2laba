#include <iostream>
#include "experiment.h"

int main() {
    std::setlocale(LC_ALL, "Ru");

    // �������� ������������
    const int sizes[] = { 5000, 10000, 20000 };

    for (int N : sizes) {
        ExperimentResult result = HashTableExperiment::runSingleExperiment(N);
        HashTableExperiment::printResult(result, N);

        // ��� ������������ ��������� ���������� ���������� ������ �������
        if (N == 5000) {
            ChainingHashTable demoTable(std::max(1, N / 100));
            Array* demoNumbers = RandomGenerator::generateRandomNumbers(100); // ������� ����� ��� ����
            for (int i = 0; i < length(*demoNumbers); ++i) {
                int num = std::stoi(get(*demoNumbers, i));
                demoTable.insert(num);
            }
            HashTableExperiment::printDetailedStatistics(demoTable);
            destroy(*demoNumbers);
            delete demoNumbers;
        }

        std::cout << "\n" << std::string(50, '-') << "\n\n";
    }

    // ������������� ������������
    HashTableExperiment::runComparisonExperiment(10000);

    return 0;
}
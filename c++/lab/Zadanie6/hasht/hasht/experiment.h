#pragma once
#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "hash_table.h"
#include "util.h"

struct ExperimentResult {
    int minLength;
    int maxLength;
    double avgLength;
    long long genTime;
    long long insertTime;
    int tableSize;
    double loadFactor;
};

class HashTableExperiment {
public:
    static ExperimentResult runSingleExperiment(int N);
    static void runComparisonExperiment(int N);
    static void printResult(const ExperimentResult& result, int N);
    static void printDetailedStatistics(const ChainingHashTable& hashTable);
};

#endif
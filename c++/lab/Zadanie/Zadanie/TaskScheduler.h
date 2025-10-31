#pragma once
#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include "Stack.h"
#include "array.h"

// Проверяет, возможно ли выполнить все задачи с учетом зависимостей
bool canFinish(Array& tasks, Array& dependencies);

#endif // TASKSCHEDULER_H
#ifndef DEBUG_H
#define DEBUG_H

#include "utils.h"

#define cpuDebug(...) do { /*qDebug(formatCpuState(*this).toLatin1().data());*/ qDebug(__VA_ARGS__); } while (false)

#endif // DEBUG_H

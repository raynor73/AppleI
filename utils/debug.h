#ifndef DEBUG_H
#define DEBUG_H

#include "utils.h"

//#define cpuDebug(...) do { qDebug(formatCpuState(*this).toLatin1().data()); qDebug(__VA_ARGS__); qDebug("==="); } while (false)
//#define cpuDebug(...) do { qDebug("0x%04x: ", (*this).pc); qDebug(__VA_ARGS__); } while (false)
#define cpuDebug(...)

#endif // DEBUG_H

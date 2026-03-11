#include <fstream>
#include <QString>
#include "utils.h"

void logToFile(const QString& msg) {
    std::ofstream log("/home/denys/Стільниця/University/year_2025_2026/sem4/KG/Lab2_KG/code/core/curveLog.txt", std::ios::app);
    if (log.is_open()) {
        log << msg.toStdString() << std::endl;
    }
}

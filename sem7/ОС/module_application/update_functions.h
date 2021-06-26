#ifndef UPDATE_FUNCTIONS
#define UPDATE_FUNCTIONS

#include <QString>
#include <vector>
#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <QProcess>
#include <chrono>
#include <thread>

std::vector <float> read_cpu_stats();
int get_cpu_load(int dt);
QString get_hostname();
QString get_user_name();
QString get_uptime();
QString get_cpu_model();
QString get_cpu_frequency();
QString get_available_memory();
QString get_busy_memory();
int get_memory_percentage();
std::string file_read(const char *file_name);

#endif // UPDATE_FUNCTIONS


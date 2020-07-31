#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <cpr/cpr.h>

using namespace std;

void diff(string fileAfter, string fileBefore, string result);

void applyChanges(string original, string changes);

#endif
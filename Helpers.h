#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>  
#include <boost/filesystem.hpp>
#include "Statistic.h"

void SearchFiles(std::string str, std::vector<boost::filesystem::path>& vec);
Statistic CountLinesInFile(boost::filesystem::path path, Statistic& statistic);
Statistic CountLinesInFile(std::string path, Statistic& statistic);
Statistic CountLinesInFilePackage(std::vector<boost::filesystem::path> file_names, Statistic& statistic);
void DoCall();
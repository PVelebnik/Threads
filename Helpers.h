#pragma once
#include "Statistic.h"
#include <boost/filesystem.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>  

void SearchFiles(std::string str, std::vector<boost::filesystem::path>& vec);
void CountLinesInFile(boost::filesystem::path path, Statistic& statistic);
void CountLinesInFilePackage(std::vector<boost::filesystem::path> file_names, Statistic& statistic);
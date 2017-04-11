#pragma once
#include "Statistic.h"
#include <boost/filesystem.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>  

void SearchFiles(const std::string& str, std::vector<boost::filesystem::path>& vec);
void CountLinesInFile(const boost::filesystem::path& path, Statistic& statistic);
void CountLinesInFilePackage(const std::vector<boost::filesystem::path>& file_names, Statistic& statistic);
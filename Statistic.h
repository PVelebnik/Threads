#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <atomic>

struct Statistic
{
public:
	Statistic();
	void PrintStatistic();
	void WriteToFile(std::ofstream& file_to_write);

	std::atomic<std::uint32_t> files_quantity;
	std::atomic<std::uint32_t> all_lines;
	std::atomic<std::uint32_t> blank_lines;
	std::atomic<std::uint32_t> code_lines;
	std::atomic<std::uint32_t> comment_lines;
	std::uint32_t time;
};
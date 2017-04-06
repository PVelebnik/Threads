#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>

struct Statistic
{
public:
	Statistic();
	void PrintStatistic();
	void WriteToFile(std::ofstream& file_to_write);
	static void CountStatistics(std::vector<Statistic> statistic_for_threads, Statistic& result);

	std::uint32_t m_files_quantity;
	std::uint32_t m_all_lines;
	std::uint32_t m_blank_lines;
	std::uint32_t m_code_lines;
	std::uint32_t m_comment_lines;
	std::uint32_t m_time;
};
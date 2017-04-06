#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>

struct Statistic
{
public:
	Statistic();
	void PrintStatistic();
	void WriteToFile(std::ofstream& file_to_write);

	int m_files_quantity;
	std::uint32_t m_all_lines;
	std::uint32_t m_blank_lines;
	std::uint32_t m_code_lines;
	std::uint32_t m_comment_lines;
	std::uint32_t m_time;
};
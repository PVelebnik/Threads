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

	std::atomic<std::uint32_t> m_files_quantity;
	std::atomic<std::uint32_t> m_all_lines;
	std::atomic<std::uint32_t> m_blank_lines;
	std::atomic<std::uint32_t> m_code_lines;
	std::atomic<std::uint32_t> m_comment_lines;
	std::uint32_t m_time;
};
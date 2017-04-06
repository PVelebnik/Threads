#include "Statistic.h"

Statistic::Statistic()
	: m_files_quantity(0)
	, m_all_lines(0)
	, m_blank_lines(0)
	, m_code_lines(0)
	, m_comment_lines(0)
	, m_time(0)
{
}

void Statistic::PrintStatistic()
{
	std::cout << "Files quantity: " << m_files_quantity << std::endl;
	std::cout << "All lines: " << m_all_lines << std::endl;
	std::cout << "Blank lines: " << m_blank_lines << std::endl;
	std::cout << "Code lines: " << m_code_lines << std::endl;
	std::cout << "Comment lines: " << m_comment_lines << std::endl;
	std::cout << "Time: " << m_time << " ms" <<std::endl;
}

void Statistic::WriteToFile(std::ofstream& file_to_write)
{
	file_to_write << "Files quantity: " << m_files_quantity
				<< "All lines: " << m_all_lines 
				<< "\nBlank lines: " << m_blank_lines
				<< "\nCode lines: " << m_code_lines
				<< "\nComment lines: " << m_comment_lines
				<< "\nTime: " << m_time << " ms" << std::endl;
}
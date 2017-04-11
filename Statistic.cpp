#include "Statistic.h"

Statistic::Statistic()
	: files_quantity(0)
	, all_lines(0)
	, blank_lines(0)
	, code_lines(0)
	, comment_lines(0)
	, time(0)
{
}

void Statistic::PrintStatistic()
{
	std::cout << "Files quantity: " << files_quantity << std::endl;
	std::cout << "All lines: " << all_lines << std::endl;
	std::cout << "Blank lines: " << blank_lines << std::endl;
	std::cout << "Code lines: " << code_lines << std::endl;
	std::cout << "Comment lines: " << comment_lines << std::endl;
	std::cout << "Time: " << time << " ms" <<std::endl;
}

void Statistic::WriteToFile(std::ofstream& file_to_write)
{
	file_to_write << "Files quantity: " << files_quantity
				<< "All lines: " << all_lines 
				<< "\nBlank lines: " << blank_lines
				<< "\nCode lines: " << code_lines
				<< "\nComment lines: " << comment_lines
				<< "\nTime: " << time << " ms" << std::endl;
}

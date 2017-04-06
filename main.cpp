#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <thread>

#include "Helpers.h"
#include "Statistic.h"

void main()
{
	std::string str = "D:/SS/Task 3 (threads)/boost/boost_lib";
	std::vector<boost::filesystem::path> file_names;

	std::thread form_file_vector(SearchFiles, str, std::ref(file_names));
	form_file_vector.join();

	Statistic statistic;
	statistic.m_files_quantity = file_names.size();

	int best_threads_quantity = std::thread::hardware_concurrency();
	std::vector<std::thread> threads_for_parsing;


	std::vector<std::vector<boost::filesystem::path>> packages(best_threads_quantity);

	int subvector_to_push=0;
	for (auto element: file_names)
	{
		packages[subvector_to_push%best_threads_quantity].push_back(element);
		subvector_to_push++;
	}

	std::vector<Statistic> statistic_for_threads(best_threads_quantity);
	std::chrono::high_resolution_clock::time_point start
		= std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < best_threads_quantity; i++)
	{
		threads_for_parsing.emplace_back(std::thread (CountLinesInFilePackage, packages[i], std::ref(statistic_for_threads[i])));
	}
	for (size_t i = 0; i < best_threads_quantity; i++)
	{
		threads_for_parsing[i].join();
	}

	for (int i = 0; i < statistic_for_threads.size(); i++)
	{
		statistic.m_all_lines += statistic_for_threads[i].m_all_lines;
		statistic.m_blank_lines += statistic_for_threads[i].m_blank_lines;
		statistic.m_code_lines += statistic_for_threads[i].m_code_lines;
		statistic.m_comment_lines += statistic_for_threads[i].m_comment_lines;
	}

	/*std::thread count_lines_in_package(CountLinesInFilePackage, file_names, std::ref(statistic));
	count_lines_in_package.join();*/

	std::chrono::high_resolution_clock::time_point finish
		= std::chrono::high_resolution_clock::now();

	std::chrono::duration<int, std::milli> time_span
		= std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

	statistic.m_time = time_span.count();

	statistic.PrintStatistic();

	std::ofstream myfile;
	myfile.open("statistic.txt");
	statistic.WriteToFile(myfile);
	myfile.close();

	system("pause");
}
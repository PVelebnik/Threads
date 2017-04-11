#include "Helpers.h"
#include "Statistic.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <thread>

void main()
{
	const std::string path = "D:/SS/Task 3 (threads)/boost/boost_lib";
	std::vector<boost::filesystem::path> file_names;

	std::thread form_file_vector(SearchFiles, path, std::ref(file_names));
	form_file_vector.join();

	Statistic statistic;
	statistic.files_quantity = static_cast<std::uint32_t>(file_names.size());

	const unsigned best_threads_quantity = std::thread::hardware_concurrency();
	std::vector<std::thread> threads_for_parsing;


	std::vector<std::vector<boost::filesystem::path>> packages(best_threads_quantity);

	unsigned subvector_to_push = 0;
	for (const auto& element: file_names)
	{
		packages[subvector_to_push%best_threads_quantity].push_back(element);
		subvector_to_push++;
	}

	const std::chrono::high_resolution_clock::time_point start
		= std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < best_threads_quantity; i++)
	{
		threads_for_parsing.emplace_back(std::thread (CountLinesInFilePackage
			, packages[i], std::ref(statistic)));
	}
	for (size_t i = 0; i < best_threads_quantity; i++)
	{
		threads_for_parsing[i].join();
	}
	
	const std::chrono::high_resolution_clock::time_point finish
		= std::chrono::high_resolution_clock::now();

	const std::chrono::duration<int, std::milli> time_span
		= std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

	statistic.time = time_span.count();

	statistic.PrintStatistic();

	std::ofstream output;
	output.open("statistic.txt");
	statistic.WriteToFile(output);
	output.close();

	system("pause");
}
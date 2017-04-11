#include "Helpers.h"

enum class LineType
{
	Blank,
	Comment,
	MulticommentStart,
	CodeAndMulticommentStart,
	Code
};

namespace
{
	LineType Find(const std::string& str)
	{
		std::size_t position = str.std::string::find_first_not_of("\t ");
		if (position == std::string::npos)
		{
			return LineType::Blank;
		}
		else
		{
			if (str[position] == '/')
			{
				if (str[position + 1] == '/')
				{
					return LineType::Comment;
				}
				else if (str[position + 1] == '*')
				{
					return LineType::MulticommentStart;
				}
				return LineType::Code;
			}
			else
			{
				if (str.find("/*", position) == std::string::npos)
				{
					return LineType::Code;
				}
				else
				{
					return LineType::MulticommentStart;
				}
			}

		}

	}
}

void SearchFiles(std::string str, std::vector<boost::filesystem::path>& vec)
{
	for (boost::filesystem::recursive_directory_iterator it(str), end; it != end; ++it) 
	{
		if (it->path().extension() == ".cpp" 
			|| it->path().extension() == ".c" 
			|| it->path().extension() == ".hpp" 
			|| it->path().extension() == ".h")
		{
			vec.push_back(*it);
		}
	}
}

void CountLinesInFile(boost::filesystem::path path, Statistic& statistic)
{
	std::ifstream in_file(path.string());
	std::string str;
	bool in_multicomment = false;
	while (std::getline(in_file, str))
	{
		if (in_multicomment)
		{
			if (str.find("*/") != std::string::npos)
			{
				in_multicomment = false;
			}
			statistic.comment_lines++;
		}
		else
		{
			LineType result = Find(str);
			switch (result)
			{
			case LineType::Blank:
			{	
				statistic.blank_lines++;
				break;
			}
			case LineType::Comment:
			{
				statistic.comment_lines++;
				break;
			}
			case LineType::MulticommentStart:
			{
				statistic.comment_lines++;
				in_multicomment = true;
				break;
			}
			case LineType::CodeAndMulticommentStart:
			{
				statistic.code_lines++;
				in_multicomment = true;
				break;
			}
			case LineType::Code:
			{
				statistic.code_lines++;
				break;
			}
			default:
			{
				assert(false);
				break;
			}
			}
		}
		statistic.all_lines++;
	}
}

void CountLinesInFilePackage(std::vector<boost::filesystem::path> file_names, Statistic& statistic)
{
	for (int i = 0; i < file_names.size(); i++)
	{
		CountLinesInFile(file_names[i], statistic);
	}
}
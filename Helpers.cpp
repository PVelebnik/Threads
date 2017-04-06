#include "Helpers.h"

enum class LINE_TYPE
{
	BLANK,
	COMMENT,
	MULTICOMMENT_START,
	CODE_AND_MULTICOMMENT_START,
	CODE
};

namespace
{
	LINE_TYPE find(const std::string& str)
	{
		std::size_t position = str.std::string::find_first_not_of("\t ");
		if (position == std::string::npos)
		{
			return LINE_TYPE::BLANK;
		}
		else
		{
			if (str[position] == '/')
			{
				if (str[position + 1] == '/')
				{
					return LINE_TYPE::COMMENT;
				}
				else if (str[position + 1] == '*')
				{
					return LINE_TYPE::MULTICOMMENT_START;
				}
				return LINE_TYPE::CODE;
			}
			else
			{
				if (str.find("/*", position) == std::string::npos)
				{
					return LINE_TYPE::CODE;
				}
				else
				{
					return LINE_TYPE::MULTICOMMENT_START;
				}
			}

		}

	}
}

void SearchFiles(std::string str, std::vector<boost::filesystem::path>& vec)
{
	for (boost::filesystem::recursive_directory_iterator it(str), end; it != end; ++it) {
		if (it->path().extension() == ".cpp" ||
			it->path().extension() == ".c" ||
			it->path().extension() == ".hpp" ||
			it->path().extension() == ".h")
		{
			vec.push_back(*it);
		}
	}
}

void CountLinesInFile(boost::filesystem::path path, Statistic& statistic)
{
	std::ifstream inFile(path.string());
	std::string s;
	bool in_multicomment = false;
	while (std::getline(inFile, s))
	{
		if (in_multicomment)
		{
			if (s.find("*/") != std::string::npos)
			{
				in_multicomment = false;
			}
			statistic.m_comment_lines++;
		}
		else
		{
			LINE_TYPE result = find(s);
			switch (result)
			{
			case LINE_TYPE::BLANK:
			{	
				statistic.m_blank_lines++;
				break;
			}
			case LINE_TYPE::COMMENT:
			{
				statistic.m_comment_lines++;
				break;
			}
			case LINE_TYPE::MULTICOMMENT_START:
			{
				statistic.m_comment_lines++;
				in_multicomment = true;
				break;
			}
			case LINE_TYPE::CODE_AND_MULTICOMMENT_START:
			{
				statistic.m_code_lines++;
				in_multicomment = true;
				break;
			}
			case LINE_TYPE::CODE:
			{
				statistic.m_code_lines++;
				break;
			}
			default:
			{
				assert(false);
				break;
			}
			}
		}
		statistic.m_all_lines++;
	}
}

void CountLinesInFilePackage(std::vector<boost::filesystem::path> file_names, Statistic& statistic)
{
	for (int i = 0; i < file_names.size(); i++)
	{
		CountLinesInFile(file_names[i], statistic);
	}
}
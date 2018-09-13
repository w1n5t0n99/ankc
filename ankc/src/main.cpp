#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>

#include "ZipLib\ZipFile.h"
#include "ziplib\streams\memstream.h"
#include "ziplib\methods\Bzip2Method.h"

namespace fs = std::experimental::filesystem;

std::vector<std::string> list_of_archive(const fs::path& archive_path)
{
	std::vector<std::string> results;

	std::cout << "opening archive <" << archive_path.string() << "> " << std::endl;
	if (!fs::exists(archive_path))
	{
		std::cout << "archive does not exits" << std::endl;
		return results;
	}

	try
	{
		auto archive = ZipFile::Open(archive_path.string());

		std::cout << "archive count: " << archive->GetEntriesCount() << std::endl;

		for (int i = 0; i < archive->GetEntriesCount(); ++i)
		{
			auto entry = archive->GetEntry(i);
			if (entry)
				results.push_back(entry->GetFullName());
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return results;
}

bool extract_from_archive(const fs::path& archive_path, std::string_view file_name)
{
	std::cout << "opening archive <" << archive_path.string() << "> " << std::endl;
	if (!fs::exists(archive_path))
	{
		std::cout << "archive does not exits" << std::endl;
		return false;
	}

	std::ofstream extracted_file(file_name, std::ios::binary | std::ios::out);
	if (!extracted_file)
	{
		std::cout << "<" << file_name << "> could not be created" << std::endl;
		return false;
	}

	try
	{
		auto archive = ZipFile::Open(archive_path.string());

		std::cout << "archive count: " << archive->GetEntriesCount() << std::endl;

		for (int i = 0; i < archive->GetEntriesCount(); ++i)
		{
			auto entry = archive->GetEntry(i);
			if (entry && !entry->IsDirectory())
			{
				if (entry->GetName() == file_name)
				{
					std::cout << "file found in archive" << std::endl;

					auto decompression_stream = entry->GetDecompressionStream();
					std::copy(std::istreambuf_iterator<char>(*decompression_stream),
						std::istreambuf_iterator<char>(),
						std::ostreambuf_iterator<char>(extracted_file));
				}
			}	
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return true;
}

int main()
{
	fs::path p = fs::current_path();
	p += "\\Japanese_Basic_Hiragana.apkg";

	/*
	auto results = list_of_archive(p);

	for (const auto& e : results)
		std::cout << e << std::endl;
	*/

	extract_from_archive(p, "collection.anki2");	

	std::cin.get();
	return 0;
}

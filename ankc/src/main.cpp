#include <iostream>
#include <filesystem>
#include <string>
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

int main()
{
	fs::path p = fs::current_path();
	p += "\\Japanese_Basic_Hiragana.apkg";

	auto results = list_of_archive(p);

	for (const auto& e : results)
		std::cout << e << std::endl;
	

	std::cin.get();
	return 0;
}

#include <iostream>
#include <filesystem>
#include <string>

#include "ZipLib\ZipFile.h"
#include "ziplib\streams\memstream.h"
#include "ziplib\methods\Bzip2Method.h"

namespace fs = std::experimental::filesystem;

int main()
{
	fs::path p = fs::current_path();
	auto abs_p = fs::absolute(p);

	std::cout << abs_p << std::endl;
	try
	{
		ZipFile::AddFile("test_zf.zip", "test_doc0.txt", LzmaMethod::Create());
		ZipFile::AddFile("test_zf.zip", "test_doc1.txt", LzmaMethod::Create());
	}
	catch (std::exception& e)
	{
		std::cout <<  "- An exception occured: " << e.what() << "\n";
	}

	std::cin.get();
	return 0;
}

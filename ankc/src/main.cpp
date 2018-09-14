#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>

#include "../includes/ankc/archiver.h"

namespace fs = std::experimental::filesystem;


int main()
{

	fs::path archive_path = fs::current_path() / fs::path{ "Japanese_Basic_Hiragana.apkg" };
	fs::path dest_path = fs::current_path() / fs::path{ "Results" };

	
	ankc::decompress_archive(archive_path, dest_path);

	std::cin.get();
	return 0;
}

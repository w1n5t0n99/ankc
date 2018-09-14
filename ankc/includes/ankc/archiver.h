#pragma once

#include <filesystem>
#include <string_view>

namespace ankc
{
	namespace fs = std::experimental::filesystem;
	
	bool decompress_archive(const fs::path& archive_path, const fs::path& destination_path);



}

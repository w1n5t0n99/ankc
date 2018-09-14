#include "../includes/ankc/archiver.h"

#include <fstream>
#include <vector>
#include <string>

#include "ZipLib\ZipFile.h"
#include "ziplib\streams\memstream.h"
#include "ziplib\methods\Bzip2Method.h"
#include "ziplib/utils/stream_utils.h"


namespace ankc
{

	void ensure_directory_exists(const fs::path& dir)
	{
		if (!fs::exists(dir))
		{
			std::error_code ec;
			fs::create_directories(dir, ec);
		}
	}

	void decompress_entry(const fs::path& destination_path, std::shared_ptr<ZipArchiveEntry> entry)
	{
		if (!entry)
			return;

		auto entry_path = destination_path / fs::path{ entry->GetFullName() };

		if (entry->IsDirectory())
		{
			ensure_directory_exists(entry_path);
		}
		else
		{
			ensure_directory_exists(entry_path.parent_path());

			std::ofstream dest_file(entry_path.string().c_str(), std::ios::binary | std::ios::trunc);
			if (!dest_file)
				return;

			auto data_stream = entry->GetDecompressionStream();
			if (!data_stream)
				return;

			utils::stream::copy(*data_stream, dest_file);

		}

	}

	bool decompress_archive(const fs::path& archive_path, const fs::path& destination_path)
	{
		ensure_directory_exists(destination_path);

		try
		{
			auto zip_archive = ZipFile::Open(archive_path.string());

			for (int i = 0; i < zip_archive->GetEntriesCount(); ++i)
			{
				auto entry = zip_archive->GetEntry(i);
				decompress_entry(destination_path, entry);
			}

		}
		catch (std::exception& e)
		{
			return false;
		}


		return true;
	}


}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Place this compiled at Obsidian vault root directory

// Replace 'Prisegtukai' (attachments) with whatever (I assume you use a folder for attachments, why wouldn't you),
// use code editor's find-replace function.

// This program likely does not support UTF-8 filenames, depending on your compiler's implementation.

// This program also heavily relies on system calls, so while not great and hacky, it does it thing.

int main()
{
	system("mkdir cleanup");
	system("dir /b /ad > cleanup\\directories.txt");
	system("dir /b > cleanup\\files.txt");
	system("dir /b Prisegtukai > cleanup\\attachments.txt");

	vector<string> Directories, Files, Attachments;
		ifstream GetDirectories;
			GetDirectories.open("cleanup\\directories.txt");

			while (!GetDirectories.eof())
			{
				string Directory;
				getline(GetDirectories, Directory);
				Directories.push_back(Directory);
			}

			GetDirectories.close();

			ifstream GetFiles;
			GetFiles.open("cleanup\\files.txt");

			while (!GetFiles.eof())
			{
				string File;
				getline(GetFiles, File);
				Files.push_back(File);
			}

			GetFiles.close();

			ifstream GetAttachments;
			GetAttachments.open("cleanup\\attachments.txt");

			while (!GetAttachments.eof())
			{
				string Attachment;
				getline(GetAttachments, Attachment);
				Attachments.push_back(Attachment);
			}

			GetAttachments.close();

		for (unsigned i = 0; i < Directories.size(); ++i)
		{
			Files.erase(remove(Files.begin(), Files.end(), Directories[i]), Files.end());
		}
		Files.erase(remove(Files.begin(), Files.end(), "delete_orphaned.cpp"), Files.end());
		Files.erase(remove(Files.begin(), Files.end(), "delete_orphaned.exe"), Files.end());

	vector<string> NotOrphans;
		ifstream ImpFiles;
			for (unsigned i = 0; i < Files.size(); ++i)
			{
				string File;

				ImpFiles.open(Files[i]);
				while (!ImpFiles.eof())
				{
					string Str;
					ImpFiles >> Str;
					File += Str + ' ';
				}

				ImpFiles.close();

				for (unsigned i; i < Attachments.size(); ++i)
				{
					if (File.find(Attachments[i]) != string::npos) {
						NotOrphans.push_back(Attachments[i]);
					}
				}

			}

		for (unsigned i = 0; i < Attachments.size(); ++i)
		{
			if (find(NotOrphans.begin(), NotOrphans.end(), Attachments[i]) == NotOrphans.end()) {
				string DeleteOrphaned = "del \"Prisegtukai\\" + Attachments[i] + "\"";
				system(DeleteOrphaned.c_str());
			}
		}
	
	system("rmdir /s /q cleanup");
}
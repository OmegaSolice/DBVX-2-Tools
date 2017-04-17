#include "Header.h"
 

void getFileName(HWND hwnd, char szFileName[MAX_PATH], COMDLG_FILTERSPEC *Filter, int numFilter)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); //Initialize COM library

	if (SUCCEEDED(hr))
	{
		//Create FileOpenDialog Object
		IFileOpenDialog *OpenFile;
		//CocreateInstance creates Common Item dialog object and get pointer to IFileOpenDialog pointer
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&OpenFile));

		//COMDLG_FILTERSPEC filter[] = { {L"aur file", L"*.aur"} }; //array list for telling file extensions that can be opened
		OpenFile->SetFileTypes(numFilter, Filter); //sets list of acceptable file by their extension
		

		if (SUCCEEDED(hr))
		{
			//Show the dialog box
			hr = OpenFile->Show(hwnd); 

			//Get file name frpm dialog box
			if (SUCCEEDED(hr))
			{
				IShellItem *Item;
				hr = OpenFile->GetResult(&Item);
				if (SUCCEEDED(hr))
				{
					LPWSTR FileName;
					hr = Item->GetDisplayName(SIGDN_FILESYSPATH, &FileName);
					wcstombs(szFileName, FileName, wcslen(FileName)); // wcstombs converts LPWSTR to Char array, 
																	  //wcslen used to find length of wide characters
					CoTaskMemFree(FileName);  //Frees FileName after finish using
				}

				Item->Release();
			}

		}
		OpenFile->Release();
		CoUninitialize();
	}
}

void getFolderPath(HWND hwnd, char szFolderPath[MAX_PATH])
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); //Initialize COM library

	if (SUCCEEDED(hr))
	{
		//Create FileOpenDialog Object
		IFileOpenDialog *OpenFile;
		//CocreateInstance creates Common Item dialog object and get pointer to IFileOpenDialog pointer
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&OpenFile));

		OpenFile->SetOptions(FOS_PICKFOLDERS);

		if (SUCCEEDED(hr))
		{
			//Show the dialog box
			hr = OpenFile->Show(hwnd);

			//Get file name frpm dialog box
			if (SUCCEEDED(hr))
			{
				IShellItem *Item;
				hr = OpenFile->GetResult(&Item);
				if (SUCCEEDED(hr))
				{
					LPWSTR FolderPath;
					hr = Item->GetDisplayName(SIGDN_FILESYSPATH, &FolderPath);
					wcstombs(szFolderPath, FolderPath, wcslen(FolderPath)); // wcstombs converts LPWSTR to Char array, 
																	  //wcslen used to find length of wide characters
					CoTaskMemFree(FolderPath);  //Frees FolderPath after finish using
				}

				Item->Release();
			}

		}
		OpenFile->Release();
		CoUninitialize();
	}
}

void openFile(char szFileName[MAX_PATH], std::string &Output)
{
	std::ifstream file(szFileName, std::ios::binary);       //opens file input stream
	std::string Line = "";                                
	if (file.is_open())
	{
#ifdef _DEBUG
		std::cout << "File is Open\n";
#endif // _DEBUG

		while (getline(file, Line))
		{
			Output += Line + '\n';
		}
		file.close();
		if (!Output.empty()) Output.erase(std::prev(Output.end())); //Erases last '\n' which will be added as it is a excess
	}
}

void openFileW(char szFileName[MAX_PATH], std::wstring &Output)
{
	std::wifstream file(szFileName, std::ios::binary);       //opens file input stream
	std::wstring Line;
	Line.clear();
	if (file.is_open())
	{
#ifdef _DEBUG
		std::cout << "File is Open\n";
#endif // _DEBUG

		while (getline(file, Line))
		{
			Output += Line + L'\n';
		}
		file.close();
		if (!Output.empty()) Output.erase(std::prev(Output.end())); //Erases last '\n' which will be added as it is a excess
	}
}

int saveFile(char szFileName[MAX_PATH], std::string Input)
{
	std::ofstream file(szFileName, std::ios::binary);

	
	if (file.is_open())
	{
		file << Input;
#ifdef _DEBUG
		std::cout << "File is save\n";
#endif // _DEBUG
	}
	else
	{
		return -1; //fail to open
	}
	file.close();
	return 0;
}

int saveFileW(char szFileName[MAX_PATH], std::wstring Input)
{
	std::wofstream file(szFileName, std::ios::binary);


	if (file.is_open())
	{
		file << Input;
#ifdef _DEBUG
		std::cout << "File is save\n";
#endif // _DEBUG
	}
	else
	{
		return -1; //fail to open
	}
	file.close();
	return 0;
}
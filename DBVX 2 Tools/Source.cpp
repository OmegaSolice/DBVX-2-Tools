#include "Header.h"
#include "MSGCS.h"
//#include <vcclr.h>  


//#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

//gcroot <XV2Lib::MSG> NameMSGDataCS;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	std::cout << "Console Initialzed" << std::endl;
#endif // _DEBUG

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, (LPCWSTR)IDR_IMAGE1));
	wcex.hCursor = NULL;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Window";
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDR_MENU1);
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Class failed to register", L"Error", MB_ICONERROR | MB_OK);
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"DBXV2 Tool", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 1000, NULL, NULL, hInstance, NULL);
	/*hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"DBXV2 Tool", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 1200, NULL, NULL, hInstance, NULL);*/
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation fail", L"Error", MB_ICONERROR | MB_OK);
	}

	g_hInst = hInstance;
	int  count = 0;
	SSkillID[0].RefID = -1, SSkillID[0].HexID1 = 0xff, SSkillID[0].HexID2 = 0xff, SSkillID[0].RefCode = "BLK", SSkillID[0].Name = "---";
	USkillID[0].RefID = -1, USkillID[0].HexID1 = 0xff, USkillID[0].HexID2 = 0xff, USkillID[0].RefCode = "BLK", USkillID[0].Name = "---";
	ASkillID[0].RefID = -1, ASkillID[0].HexID1 = 0xff, ASkillID[0].HexID2 = 0xff, ASkillID[0].RefCode = "BLK", ASkillID[0].Name = "---";
	ESkillID[0].RefID = -1, ESkillID[0].HexID1 = 0xff, ESkillID[0].HexID2 = 0xff, ESkillID[0].RefCode = "BLK", ESkillID[0].Name = "---";
	SSSetting.Flag[0] = 0xff, SSSetting.Flag[1] = 0x01, SSSetting.Flag[2] = 0x0A, SSSetting.Flag[3] = 0x0A, SSSetting.Flag[4] = 0x00;
	SSSetting.TimerID1[0] = 0x80, SSSetting.TimerID2[0] = 0xBF, SSSetting.TimerID1[1] = 0x70, SSSetting.TimerID2[1] = 0x41;
	SSSetting.TimerID1[2] = 0xF0, SSSetting.TimerID2[2] = 0x41, SSSetting.TimerID1[3] = 0x70, SSSetting.TimerID2[3] = 0x42;
	SSSetting.TimerID1[4] = 0xff, SSSetting.TimerID2[4] = 0xff, SSSetting.TimerID1[5] = 0x00, SSSetting.TimerID2[5] = 0x00;
	SSSetting.Target[0] = 0x00, SSSetting.Target[1] = 0x01, SSSetting.Target[2] = 0x05, SSSetting.Target[2] = 0xff;

	LoadAura();
	LoadCharacter();
	LoadCostume();
	int SSkillCount = LoadSkill("Data/Super Skill ID.ini", SSkillSetting, SSkillID);
	int USkillCount = LoadSkill("Data/Ultimate Skill ID.ini", USkillSetting, USkillID);
	int ASkillCount = LoadSkill("Data/Awoken Skill ID.ini", ASkillSetting, ASkillID);
	int ESkillCount = LoadSkill("Data/Evasive Skill ID.ini", ESkillSetting, ESkillID);
	LoadEffect();
	LoadEffectAmount();
	LoadTrigger();
	LoadTC();
	LoadSoulList();
	openFile("Data/AuraSetup.ini", AuraSetupData);

	TCHAR *TabLabel[] = { L"Aura", L"Skill", L"Super Soul", L"Stat", L"Costume" };
	count = 0;
	int numTab = 5;
	HWND hTemp;
	DWORD Err = NULL;
	WCHAR WERR[100] = L"";

	hwndTab = CreateTabControl(hwnd, g_hInst, numTab, TabLabel);
	hwndDisplay[0] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwndTab, MainDialogProc);
	if (!hwndDisplay[0]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[1] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwndTab, MainDialogProc);
	if (!hwndDisplay[1]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[2] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwndTab, MainDialogProc);
	if (!hwndDisplay[2]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[3] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwndTab, MainDialogProc);
	if (!hwndDisplay[3]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[4] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG5), hwndTab, MainDialogProc);
	if (!hwndDisplay[4]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }

	hComboCheck[0] = GetDlgItem(hwndDisplay[0], IDC_COMBO3); //Used to check combo box so when character change costume box can be set appropriatley  
	hComboCheck[1] = GetDlgItem(hwndDisplay[1], IDC_COMBO6);
	hComboCheck[2] = GetDlgItem(hwndDisplay[2], IDC_COMBO1);
	hComboCheck[3] = GetDlgItem(hwndDisplay[3], IDC_COMBO1);
	hComboCheck[4] = GetDlgItem(hwndDisplay[4], IDC_COMBO1);

	hTemp = GetDlgItem(hwndDisplay[3], IDC_COMBO4);
	SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)L"PQ"));
	SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)L"Battle"));

	while (count < numTab)        //resizes dialog to window client
	{
		DialogResize(hwndTab, hwndDisplay[count]);
		count++;
	}

	count = 0;
	while (count < AuraCount)
	{
		size_t size = strlen(AuraID[count].skillName.c_str()) + 1;
		wchar_t *ComboBoxItemAuraTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemAuraTemp, size, AuraID[count].skillName.c_str(), size - 1);
		const TCHAR *ComboBoxItemAura = { ComboBoxItemAuraTemp };
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO1);
		if (!hTemp) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO2);
		if (!hTemp) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO5);
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;
	while (count < CharCount)
	{
		size_t size = strlen(CharID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemCharTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemCharTemp, size, CharID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemChar = { ComboBoxItemCharTemp };
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO3);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemChar));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO6);
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemChar));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[3], IDC_COMBO1);
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemChar));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;
	//int maxCount = sizeof(SSkillID) / sizeof SKILL;

	while (count < SSkillCount)
	{
		size_t size = strlen(SSkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, SSkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO8);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO9);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO10);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO11);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < USkillCount)
	{
		size_t size = strlen(USkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, USkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO12);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO13);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < ASkillCount)
	{
		size_t size = strlen(ASkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, ASkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO14);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < ESkillCount)
	{
		size_t size = strlen(ESkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, ESkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO15);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;
	TCHAR *Ki_Blast[] = { L"Paralyze", L"Power", L"Rush", L"Bomb", L"Homing" };
	while (count < 5)
	{
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO2);
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)Ki_Blast[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;

	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO3);

	while (count < SSEffectCount)
	{
		std::cout << SSEffectID[count].EffectName << "\n";
		size_t size = strlen(SSEffectID[count].EffectName.c_str()) + 1;
		wchar_t *ComboBoxItemEffectTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemEffectTemp, size, SSEffectID[count].EffectName.c_str(), size - 1);
		const TCHAR *ComboBoxItemEffect = { ComboBoxItemEffectTemp };
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffect));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;

	while (count < SSEffectAmountCount)
	{
		size_t size = strlen(SSEAID[count].Amount.c_str()) + 1;
		wchar_t *ComboBoxItemEffectAmountTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemEffectAmountTemp, size, SSEAID[count].Amount.c_str(), size - 1);
		const TCHAR *ComboBoxItemEffectAmount = { ComboBoxItemEffectAmountTemp };

		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO4);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO11);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO12);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO13);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO14);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO15);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO16);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO17);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO18);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO19);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO20);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO21);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO22);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO23);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO24);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO25);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO26);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO27);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO28);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO5);
	TCHAR* ComboBoxItemFlag[] = { L"None", L"Once", L"Stack 10 Times", L"None",L"Not Found" };

	while (count < 5)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemFlag[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO6);
	while (count < SSTriggerCount)
	{
		std::cout << SSTriggerID[count].Trigger << "\n";
		size_t size = strlen(SSTriggerID[count].Trigger.c_str()) + 1;
		wchar_t *ComboBoxItemTriggerTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemTriggerTemp, size, SSTriggerID[count].Trigger.c_str(), size - 1);
		const TCHAR *ComboBoxItemTrigger = { ComboBoxItemTriggerTemp };
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTrigger));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;

	while (count < SSTCCount)
	{
		std::cout << SSTCID[count].TCName << "\n";
		size_t size = strlen(SSTCID[count].TCName.c_str()) + 1;
		wchar_t *ComboBoxItemTCTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemTCTemp, size, SSTCID[count].TCName.c_str(), size - 1);
		const TCHAR *ComboBoxItemTC = { ComboBoxItemTCTemp };
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO8);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO9);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO10);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO30);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO31);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO7);
	TCHAR* ComboBoxItemTarget[] = { L"Self", L"Allies", L"Enemies", L"Not Found" };

	while (count < 4)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTarget[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO29);
	TCHAR* ComboBoxItemTimer[] = { L"0s", L"15s", L"30s", L"60s", L"None", L"Not Found" };

	while (count < 5)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTimer[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[3], IDC_COMBO3);

	while (count < SoulCount)
	{
		std::cout << SuperSoulID[count].Name << "\n";
		size_t size = strlen(SuperSoulID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSuperSoulTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSuperSoulTemp, size, SuperSoulID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSuperSoul = { ComboBoxItemSuperSoulTemp };
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSuperSoul));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	ShowWindow(hwndTab, SW_SHOWNORMAL);
	ShowWindow(hwndDisplay[0], SW_SHOWNORMAL);
	UpdateWindow(hwndDisplay[0]);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!IsDialogMessage(hwndDisplay[TabCtrl_GetCurSel(hwndTab)], &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_COMMAND:
		/*switch (wParam)
		{

		}*/
	case WM_CREATE:
	{

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		OnNotify(hwndTab, hwndDisplay, lParam, g_hInst);
		break;
	case WM_PAINT:
		break;
	case WM_SIZE:
	{
		int  count = 0;
		RECT rcClient;

		GetClientRect(hwnd, &rcClient);
		SetWindowPos(hwndTab, NULL, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, NULL);

		while (count < 5)        //resizes dialog to window client
		{
			DialogResize(hwndTab, hwndDisplay[count]);
			count++;
		}
	}
	UpdateWindow(hwnd);
	UpdateWindow(hwndDisplay[TabCtrl_GetCurSel(hwndTab)]);
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		int count = 0;
		WCHAR WERR[100] = L"";
		HWND hTemp;
		TC_ITEMHEADER tabInfo;
		TCHAR* TabLabel1[] = { L"Intial Effect", L"Effect 1", L"Effect 2" };
		hTemp = GetDlgItem(hwndDisplay[2], IDC_TAB1);
		TabCtrl_DeleteAllItems(hTemp);

		tabInfo.mask = TCIF_TEXT;
		tabInfo.iImage = -1;

		while (count < 3) //set super soul tab effects tabs name
		{
			//mbtowc(WTemp, Temp, strlen(Temp));// +1 is to include null character
			tabInfo.pszText = TabLabel1[count];
			SendMessage(hTemp, TCM_INSERTITEM, count, (LPARAM)&tabInfo);
			count++;
		}

		count = 0;

		TCHAR* TabLabel2[] = { L"Top", L"Bottom", L"Gloves", L"Shoes" };
		hTemp = GetDlgItem(hDlg, IDC_TAB1);
		TabCtrl_DeleteAllItems(hTemp);
		while (count < 4) //set super soul tab effects tabs name
		{
			//mbtowc(WTemp, Temp, strlen(Temp));// +1 is to include null character
			tabInfo.pszText = TabLabel2[count];
			SendMessage(hTemp, TCM_INSERTITEM, count, (LPARAM)&tabInfo);
			count++;
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDB_SET_AURA_COLOR:
		{
			LRESULT Name, Aura;
			HWND hAuraName = GetDlgItem(hwndDisplay[0], IDC_COMBO1);
			HWND hAuraColor = GetDlgItem(hwndDisplay[0], IDC_COMBO2);
			Name = SendMessage(hAuraName, CB_GETCURSEL, 0, 0);
			Aura = SendMessage(hAuraColor, CB_GETCURSEL, 0, 0);
			ChangeAuraColor(Name, Aura, GetDlgItem(hDlg, IDC_EDITERROR1));
			break;
		}
		break;
		case IDB_SET_CHAR_AURA_COLOR:
		{
			LRESULT Name = NULL, Costume, Color, InfiniteCheck;
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO4);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO5);
			Color = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_CHECK1);
			InfiniteCheck = SendMessage(hTemp, BM_GETCHECK, 0, 0);
			ChangeCharAura(Name, Costume, Color, InfiniteCheck, GetDlgItem(hDlg, IDC_EDITERROR1));
			break;
		}
		case ID_FILE_OPEN_AURA:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"aur file", L"*.aur" } };
			getFileName(hwnd, AuraFile, L"Xenoverse aur file\0*.aur");
			openFile(AuraFile, AuraData);
			break;
		}
		case ID_FILE_SAVE_AURA:
			if (saveFile(AuraFile, AuraData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			break;
		case IDC_AURASETUP:
			AuraSetup(GetDlgItem(hDlg, IDC_EDITERROR1));
			break;
		case IDC_BUTTON2:
		{
			LRESULT Name, Costume;
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO4);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO5);
			SendMessage(hTemp, CB_SETCURSEL, GetAura(Name, Costume, GetDlgItem(hDlg, IDC_EDITERROR1)), 0);
		}
		break;
		case IDC_BUTTON3:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"cus file", L"*.cus" } };
			getFileName(hwnd, CusFile, L"Xenoverse Cus file\0*.cus\0");
			openFile(CusFile, CusData);
			break;
		}
		case IDC_BUTTON4:
			if (saveFile(CusFile, CusData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			break;
		case IDC_BUTTON5:

			break;
		case IDC_BUTTON6:
		{
			LRESULT Name, Costume, SuperSkill[4], UltimateSkill[2], AwokenSkill, EvasiveSkill;
			HWND hTemp;
			hTemp = GetDlgItem(hDlg, IDC_COMBO6);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO7);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO8);
			SuperSkill[1] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO9);
			SuperSkill[0] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO10);
			SuperSkill[2] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO11);
			SuperSkill[3] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO12);
			UltimateSkill[0] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO13);
			UltimateSkill[1] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO14);
			AwokenSkill = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO15);
			EvasiveSkill = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			ChangeSkill(Name, Costume, SuperSkill, UltimateSkill, AwokenSkill, EvasiveSkill, GetDlgItem(hDlg, IDC_EDITERROR2));
			break;
		}
		case IDC_BUTTON7:
		{
			LRESULT Name, Costume, SuperSkill[4] = { 0 }, UltimateSkill[2] = { 0 }, AwokenSkill = 0, EvasiveSkill = 0;
			HWND hTemp;
			hTemp = GetDlgItem(hDlg, IDC_COMBO6);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO7);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			GetSkill(Name, Costume, SuperSkill, UltimateSkill, AwokenSkill, EvasiveSkill, GetDlgItem(hDlg, IDC_EDITERROR2));
			hTemp = GetDlgItem(hDlg, IDC_COMBO8);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[1], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO9);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[0], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO10);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[2], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO11);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[3], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO12);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, UltimateSkill[1], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO13);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, UltimateSkill[0], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO14);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, AwokenSkill, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO15);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, EvasiveSkill, 0);
		}
		break;
		case IDC_OPENNAMEMSG:
		{
			//COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			HWND hTemp;
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, NameMsgFile, L"Xenoverse MSG file\0*.msg\0");
			if (NameMsgFile[0] == 0) break;
			LoadMSGID(NameMsgFile, &MSGCount, 1);

			hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO1);
			if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
			SendMessage(hTemp, CB_RESETCONTENT, 0, 0);

			while (count < MSGCount)
			{
				SendMessageA(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> (GetNameID(count, 1)));
				if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
				count++;
			}
		}
		break;

		case IDC_OPENDESCMSG:
		{
			//COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			WCHAR WERR[100] = L"";
			getFileName(hwnd, DescMsgFile, L"Xenoverse MSG file\0*.msg\0");;
			if (DescMsgFile[0] == 0) break;
			LoadMSGID(DescMsgFile, &MSGCount, 3);
		}
		break;
		case IDC_OPENIDB:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"Tailsman idb file", L"*.idb" } };
			WCHAR WERR[100] = L"";
			getFileName(hwnd, SSIDBFile, L"Xenoverse Tailsman idb file\0*.idb\0");
			openFile(SSIDBFile, SSIDBData);
			//IDBSetup();
		}
		break;
		case IDOK: //this for when enter is pressed any of ID# edit control
		{
			if ((GetFocus() == GetDlgItem(hDlg, IDC_EDIT5) || GetFocus() == GetDlgItem(hDlg, IDC_EDIT3)) && hDlg == hwndDisplay[2])
			{
				char CInput[10];
				std::stringstream HexNum;

				if (GetFocus() == GetDlgItem(hDlg, IDC_EDIT3))
				{
					GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), CInput, 4);
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT5), CInput);
				}
				else
				{
					GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT5), CInput, 4);
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), CInput);
				}

				if (CInput[0] == ' ' || atoi(CInput) > 210) break;
				int index = 0;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				wchar_t Temp[10];
				HWND hTemp = GetDlgItem(hDlg, IDC_EDIT3);
				HexNum << std::hex << CInput;
				HexNum >> index;
				if (isMSGLoaded(1))
				{
					SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, index, 0);
					wsprintfW(Temp, L"%x", GetID(index, 1));
					Err = SetWindowText(hTemp, Temp);

					hTemp = GetDlgItem(hDlg, IDC_EDIT1);
					SetWindowTextW(hTemp, GetLines(index, 1));
				}

				hTemp = GetDlgItem(hDlg, IDC_EDIT2);
				if (!DescMsgFile[0] == 0)
				{
					SetWindowText(hTemp, GetLines(index, 3));
				}
				else
				{
					SetWindowText(hTemp, L"Load Description MSG and reselect Name MSG ID");
				}

				if (!SSIDBData.empty())
				{
					memset(&SSData, 0, sizeof(SUPERSOUL));
					SSData = SearchIDB(index, SSIDBData);
					int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
					hTemp = GetDlgItem(hDlg, IDC_EDIT5);
					wsprintfW(Temp, L"%x", (uint8_t)SSIDBData[SSData.ID]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_EDIT4);
					wsprintfW(Temp, L"%d", SSIDBData[SSData.Rarity]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_COMBO2);
					SendMessage(hTemp, CB_SETCURSEL, SSIDBData[SSData.Ki_BlastType], 0);
					hTemp = GetDlgItem(hDlg, IDC_EDIT6);
					char CPrice[5];
					int Price;
					Price = ((uint8_t)SSIDBData[SSData.Price + 3] * 0x1000000) + ((uint8_t)SSIDBData[SSData.Price + 2] * 0x10000) +
						((uint8_t)SSIDBData[SSData.Price + 1] * 0x100) + (uint8_t)SSIDBData[SSData.Price];
					sprintf(CPrice, "%d", Price);
					SetWindowTextA(hTemp, CPrice);
					SetAllCurEffect();
					DisplayEffect(hDlg, TabNum);
				}
			}

			if ((GetFocus() == GetDlgItem(hDlg, IDC_EDIT5) || GetFocus() == GetDlgItem(hDlg, IDC_EDIT3)) && hDlg == hwndDisplay[4])
			{

				char CInput[10];
				std::stringstream HexNum;

				if (GetFocus() == GetDlgItem(hDlg, IDC_EDIT3))
				{
					GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), CInput, 4);
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT5), CInput);
				}
				else
				{
					GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT5), CInput, 4);
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), CInput);
				}

				int index;
				HexNum.str(std::string());
				HexNum.clear();
				HexNum << std::hex << CInput;
				HexNum >> index;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				wchar_t Temp[10];
				HWND hTemp = GetDlgItem(hDlg, IDC_EDIT3);;

				if (!NameMsgFile1[0] == 0)
				{
					SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, index, 0);
					wsprintfW(Temp, L"%x", GetID(index, 2));
					Err = SetWindowText(hTemp, Temp);

					hTemp = GetDlgItem(hDlg, IDC_EDIT1);
					SetWindowText(hTemp, GetLines(index, 2));
				}

				hTemp = GetDlgItem(hDlg, IDC_EDIT2);
				if (!DescMsgFile1[0] == 0)
				{
					Err = SetWindowText(hTemp, GetLines(index, 4));
				}
				else
				{
					SetWindowText(hTemp, L"Load Description MSG and reselect Name MSG ID");
				}


				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					memset(&CSData, 0, sizeof(SUPERSOUL));
					for (int i = 0; i < 4; i++)
					{
						if (!CSIDBData[i].empty())
							CSData[i] = SearchIDB(index, CSIDBData[i]);
					}
					int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
					hTemp = GetDlgItem(hDlg, IDC_EDIT5);

					if (!CSIDBData[TabNum].empty())
						DisplayCostumeStat(hDlg, TabNum);
				}
			}
			break;
		}

		case IDC_SAVESOUL:
		{
			if (!NameMsgFile[0] == 0)
			{
				SaveMSG(NameMsgFile, 1);
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Name Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"No Name MSG Loaded");
				SetFocus(EditError);
			}
			if (!DescMsgFile[0] == 0)
			{
				SaveMSG(DescMsgFile, 3);
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Description Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"No Description MSG Loaded");
				SetFocus(EditError);
			}
			if (saveFile(SSIDBFile, SSIDBData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
				SetWindowText(EditError, L"IDB Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!SSIDBData.empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
					SetWindowText(EditError, L"Error Failed to Save IDB");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
					SetWindowText(EditError, L"No IDB Loaded");
					SetFocus(EditError);
				}
			}
		}
		break;
		case IDC_SETSOUL:
		{
			int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
			GetCurEffect(hDlg, TabNum);
			SetSoul(hDlg);
		}
		break;
		case IDC_OPENPSC:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"psc file", L"*.psc" } };
			getFileName(hwnd, PscFile, L"Xenoverse psc file\0*.psc\0");
			openFile(PscFile, PSCData);
			LoadPSC(HStat, Stats, PSCData);
		}
		break;
		case IDC_GETSTAT:
		{
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO1);
			int count = 0, TempIndex = 0, index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			bool battleStats = false;

			if (SendMessage(GetDlgItem(hDlg, IDC_COMBO4), CB_GETCURSEL, 0, 0) == 1)
			{
				battleStats = true;
			}

			while (CharID[index].HexID != HStat[count].CharHexID || battleStats)
			{
				TempIndex += HStat[count].CostumeAmount;
				if (CharID[index].HexID == HStat[count].CharHexID) battleStats = false;
				count++;
			}
			
			index = TempIndex;
			hTemp = GetDlgItem(hDlg, IDC_COMBO2);
			index += SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			
			if (index > -1 && index < (sizeof(Stats) / sizeof STAT) && !PSCData.empty())
			{
				DisplayStat(index, hDlg, Stats);
			}
			else
			{
				hTemp = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(hTemp, L"Error PSC Not Loaded/ Character or Costume Not Selected");
			}
		}
		break;
		case IDC_SETSTAT:
		{
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO1);
			int count = 0, TempIndex = 0, index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			bool battleStats = false;

			if (SendMessage(GetDlgItem(hDlg, IDC_COMBO4), CB_GETCURSEL, 0, 0) == 1)
			{
				battleStats = true;
			}

			while (CharID[index].HexID != HStat[count].CharHexID || battleStats)
			{
				TempIndex += HStat[count].CostumeAmount;
				if (CharID[index].HexID == HStat[count].CharHexID) battleStats = false;
				count++;
			}
			index = TempIndex;
			hTemp = GetDlgItem(hDlg, IDC_COMBO2);
			index += SendMessage(hTemp, CB_GETCURSEL, 0, 0);

			if (index > -1 && (sizeof(Stats) / sizeof STAT) && !PSCData.empty())
			{
				SetStat(hDlg, index, Stats);
			}
			else
			{
				hTemp = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(hTemp, L"Error PSC Not Loaded/ Character or Costume Not Selected");
			}
		}
		break;
		case IDC_SETALL:
		{
			HWND hTemp;

			if (!PSCData.empty())
			{
				SetAllStat(hDlg, Stats);
			}
			else
			{
				hTemp = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(hTemp, L"Error PSC Not Loaded/ Character or Costume Not Selected");
			}
		}
		break;
		case IDC_SETALLCHECKED:
		{
			HWND hTemp;

			if (!PSCData.empty())
			{
				SetAllCheckStat(hDlg, Stats);
			}
			else
			{
				hTemp = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(hTemp, L"Error PSC Not Loaded/ Character or Costume Not Selected");
			}
		}
		break;
		case IDC_SAVEPSC:
		{
			if (!PSCData.empty())
			{
				SetPSCData(Stats);
				if (saveFile(PscFile, PSCData) == 0)
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
					SetWindowText(EditError, L"PSC Save Succcesful");
					SetFocus(EditError);
				}
				else
				{
					if (!PSCData.empty())
					{
						HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
						SetWindowText(EditError, L"Error Failed to Save PSC");
						SetFocus(EditError);
					}
					else
					{
						HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
						SetWindowText(EditError, L"No PSC Loaded");
						SetFocus(EditError);
					}
				}
			}
		}
		break;
		case IDC_OPENNAMEMSG1:
		{
			//COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			HWND hTemp;
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, NameMsgFile1, L"Xenoverse MSG file\0*.msg\0");;
			if (NameMsgFile1[0] == 0) break;
			LoadMSGID(NameMsgFile1, &MSGCount1, 2);
			hTemp = GetDlgItem(hwndDisplay[4], IDC_COMBO1);
			if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
			SendMessage(hTemp, CB_RESETCONTENT, 0, 0);

			while (count < MSGCount1)
			{
				SendMessageA(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((GetNameID(count, 2))));
				if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
				count++;
			}
		}
		break;

		case IDC_OPENDESCMSG1:
		{
			//COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, DescMsgFile1, L"Xenoverse MSG file\0*.msg\0");
			if (DescMsgFile1[0] == 0) break;
			LoadMSGID(DescMsgFile1, &MSGCount1, 4);
		}
		break;
		case IDC_IDBFOLDER:
		{
			WCHAR WERR[100] = L"";

			/*struct Thread
			{
				struct ThreadArgs { HWND hwnd; char* path; };
				static DWORD WINAPI ThreadFunc(void* data)
				{
					//ThreadArgs *temp = static_cast<ThreadArgs*>(data);
					getFolderPath(hwnd, CSIDBFile[0]);
					return 0;
				}
			};
			//Thread::ThreadArgs *args;
			//args->hwnd = hwnd, args->path = CSIDBFile[0];
			HANDLE thread = CreateThread(NULL, 0, Thread::ThreadFunc, NULL, 0, NULL);
			if (thread) {
				WaitForMultipleObjects(1, &thread, TRUE, INFINITE);
			}*/
			getFolderPath(CSIDBFile[0]);
			for (int i = 0; i < 4; i++)
				strcpy(CSIDBFile[i], CSIDBFile[0]);
			strcat(CSIDBFile[0], "\\costume_top_item.idb");
			strcat(CSIDBFile[1], "\\costume_bottom_item.idb");
			strcat(CSIDBFile[2], "\\costume_gloves_item.idb");
			strcat(CSIDBFile[3], "\\costume_shoes_item.idb");
			for (int i = 0; i < 4; i++)
				openFile(CSIDBFile[i], CSIDBData[i]);
		}
		break;
		case IDC_SETCOSTUME:
		{
			SetCurCostumeStat(hDlg, PrevCostumeTab, CSIDBData);
		}
		break;
		case IDC_SAVECOSTUME:
		{
			if (!NameMsgFile1[0] == 0)
			{
				SaveMSG(NameMsgFile1, 2);
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Name Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"No Name MSG Loaded");
				SetFocus(EditError);
			}
			if (!DescMsgFile1[0] == 0)
			{
				SaveMSG(DescMsgFile1, 4);
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Description Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"No Description MSG Loaded");
				SetFocus(EditError);
			}
			if (saveFile(CSIDBFile[0], CSIDBData[0]) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
				SetWindowText(EditError, L"Costume top Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!CSIDBData[0].empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
					SetWindowText(EditError, L"Error Failed to Save Costume top");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR3);
					SetWindowText(EditError, L"No Costume top IDB Loaded");
					SetFocus(EditError);
				}
			}

			if (saveFile(CSIDBFile[1], CSIDBData[1]) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR4);
				SetWindowText(EditError, L"Costume bottom Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!CSIDBData[1].empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR4);
					SetWindowText(EditError, L"Error Failed to Save Costume bottom");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR4);
					SetWindowText(EditError, L"No Costume bottom IDB Loaded");
					SetFocus(EditError);
				}
			}

			if (saveFile(CSIDBFile[2], CSIDBData[2]) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR5);
				SetWindowText(EditError, L"Costume gloves Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!CSIDBData[2].empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR5);
					SetWindowText(EditError, L"Error Failed to Save Costume gloves");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR5);
					SetWindowText(EditError, L"No Costume gloves IDB Loaded");
					SetFocus(EditError);
				}
			}

			if (saveFile(CSIDBFile[3], CSIDBData[3]) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR6);
				SetWindowText(EditError, L"Costume shoes Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!CSIDBData[3].empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR6);
					SetWindowText(EditError, L"Error Failed to Save Costume shoes");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR6);
					SetWindowText(EditError, L"No Costume shoes IDB Loaded");
					SetFocus(EditError);
				}
			}

		}
		break;
		}
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
		{
			if ((HWND)lParam == hComboCheck[0] || (HWND)lParam == hComboCheck[1] || (HWND)lParam == hComboCheck[3])
			{
				int index, count = 0;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				HWND hTemp;
				if ((HWND)lParam == hComboCheck[0])
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
				else
				{
					if ((HWND)lParam == hComboCheck[1])
						hTemp = GetDlgItem(hDlg, IDC_COMBO7);
					else
						hTemp = GetDlgItem(hDlg, IDC_COMBO2);
				}
				index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SendMessage(hTemp, CB_RESETCONTENT, 0, 0);
				while (TRUE)
				{
					//if stat tab Custom Char skip first entry
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x64) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x65) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x66) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x67) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x68) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x69) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x6a) count = 1;
					if ((HWND)lParam == hComboCheck[3] && count == 0 && CharID[index].HexID == 0x6b) count = 1;
					std::cout << CharID[index].List[count].Name << "\n";
					if (CharID[index].List[count].Name[0] == '\0') break;
					size_t size = strlen(CharID[index].List[count].Name.c_str()) + 1;
					wchar_t *ComboBoxItemCostumeTemp = new wchar_t[size];

					size_t outSize;
					mbstowcs_s(&outSize, ComboBoxItemCostumeTemp, size, CharID[index].List[count].Name.c_str(), size - 1);
					const TCHAR *ComboBoxItemCostume = { ComboBoxItemCostumeTemp };
					if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
					SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemCostume));
					if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
					if ((HWND)lParam != hComboCheck[3])//skip if not stats tab
					{
						if (CharID[index].HexID == 0x64 || CharID[index].HexID == 0x65) break;//used to limit Custom character costume unless
						if (CharID[index].HexID == 0x66 || CharID[index].HexID == 0x67) break;//its psc editor
						if (CharID[index].HexID == 0x68 || CharID[index].HexID == 0x69) break;
						if (CharID[index].HexID == 0x6a || CharID[index].HexID == 0x6b) break;
					}
					count++;
				}
			}
			if ((HWND)lParam == hComboCheck[2])
			{
				int index;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				wchar_t Temp[10];
				HWND hTemp = GetDlgItem(hDlg, IDC_EDIT3);
				index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

				wsprintfW(Temp, L"%x", GetID(index, 1));
				Err = SetWindowText(hTemp, Temp);

				hTemp = GetDlgItem(hDlg, IDC_EDIT1);
				SetWindowTextW(hTemp, GetLines(index, 1));
				hTemp = GetDlgItem(hDlg, IDC_EDIT2);
				if (!DescMsgFile[0] == 0)
				{
					SetWindowText(hTemp, GetLines(index, 3));
				}
				else
				{
					SetWindowText(hTemp, L"Load Description MSG and reselect Name MSG ID");
				}

				if (!SSIDBData.empty())
				{
					memset(&SSData, 0, sizeof(SUPERSOUL));
					SSData = SearchIDB(index, SSIDBData);
					int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
					hTemp = GetDlgItem(hDlg, IDC_EDIT5);
					wsprintfW(Temp, L"%x", SSIDBData[SSData.ID]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_EDIT4);
					wsprintfW(Temp, L"%d", SSIDBData[SSData.Rarity]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_COMBO2);
					SendMessage(hTemp, CB_SETCURSEL, SSIDBData[SSData.Ki_BlastType], 0);
					hTemp = GetDlgItem(hDlg, IDC_EDIT6);
					char CPrice[5];
					int Price;
					Price = ((uint8_t)SSIDBData[SSData.Price + 3] * 0x1000000) + ((uint8_t)SSIDBData[SSData.Price + 2] * 0x10000)
						+ ((uint8_t)SSIDBData[SSData.Price + 1] * 0x100) + (uint8_t)SSIDBData[SSData.Price];
					sprintf(CPrice, "%d", Price);
					SetWindowTextA(hTemp, CPrice);
					SetAllCurEffect();
					DisplayEffect(hDlg, TabNum);
				}
			}
			if ((HWND)lParam == hComboCheck[4])
			{
				int index;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				wchar_t Temp[10];
				HWND hTemp = GetDlgItem(hDlg, IDC_EDIT3);
				index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

				if (!NameMsgFile1[0] == 0)
				{
					SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, index, 0);
					wsprintfW(Temp, L"%x", GetNameID(index, 2));
					Err = SetWindowText(hTemp, Temp);

					hTemp = GetDlgItem(hDlg, IDC_EDIT1);
					SetWindowText(hTemp, GetLines(index, 2));
				}

				hTemp = GetDlgItem(hDlg, IDC_EDIT2);
				if (!DescMsgFile1[0] == 0)
				{
					SetWindowText(hTemp, GetLines(index, 4));
				}
				else
				{
					SetWindowText(hTemp, L"Load Description MSG and reselect Name MSG ID");
				}


				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					memset(&CSData, 0, sizeof(SUPERSOUL));
					for (int i = 0; i < 4; i++)
					{
						if (!CSIDBData[i].empty())
							CSData[i] = SearchIDB(index, CSIDBData[i]);
					}
					int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
					hTemp = GetDlgItem(hDlg, IDC_EDIT5);

					if (!CSIDBData[TabNum].empty())
						DisplayCostumeStat(hDlg, TabNum);
				}
			}
		}
		}
		return (INT_PTR)TRUE;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
			//switch (lParam)
		{
		case TCN_SELCHANGING:
		{
			// Return FALSE to allow the selection to change.
			return FALSE;
		}
		break;
		case TCN_SELCHANGE:
		{
			int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
			switch (TabNum)
			{
			case 0:
			{
				if (!SSIDBData.empty())
				{
					GetCurEffect(hDlg, PrevEffectTab);
					PrevEffectTab = 0;
					DisplayEffect(hDlg, TabNum);
				}
				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					if (!CSIDBData[PrevCostumeTab].empty())
					{
						SetCurCostumeStat(hDlg, PrevCostumeTab, CSIDBData);
					}
					PrevCostumeTab = 0;
					DisplayCostumeStat(hDlg, TabNum);
				}
			}
			break;
			case 1:
			{
				if (!SSIDBData.empty())
				{
					GetCurEffect(hDlg, PrevEffectTab);
					PrevEffectTab = 1;
					DisplayEffect(hDlg, TabNum);
				}
				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					if (!CSIDBData[PrevCostumeTab].empty())
					{
						SetCurCostumeStat(hDlg, PrevCostumeTab, CSIDBData);
					}
					PrevCostumeTab = 1;
					DisplayCostumeStat(hDlg, TabNum);
				}
			}
			break;
			case 2:
			{
				if (!SSIDBData.empty())
				{
					GetCurEffect(hDlg, PrevEffectTab);
					PrevEffectTab = 2;
					DisplayEffect(hDlg, TabNum);
				}
				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					if (!CSIDBData[PrevCostumeTab].empty())
					{
						SetCurCostumeStat(hDlg, PrevCostumeTab, CSIDBData);
					}
					PrevCostumeTab = 2;
					DisplayCostumeStat(hDlg, TabNum);
				}
			}
			break;
			case 3:
			{
				if (!CSIDBData[0].empty() || !CSIDBData[1].empty() || !CSIDBData[2].empty() || !CSIDBData[3].empty())
				{
					if (!CSIDBData[PrevCostumeTab].empty())
					{
						SetCurCostumeStat(hDlg, PrevCostumeTab, CSIDBData);
					}
					PrevCostumeTab = 3;
					DisplayCostumeStat(hDlg, TabNum);
				}
			}
			break;
			}
		}
		break;
		}
		return (INT_PTR)TRUE;
	default:
		return (INT_PTR)FALSE;

	}
	return (INT_PTR)FALSE;
}


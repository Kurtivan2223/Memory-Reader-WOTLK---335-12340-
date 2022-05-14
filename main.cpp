#include <iostream>
#include <Windows.h>
#include <string>
#include <stdint.h>
#include <winuser.h>
#include <TlHelp32.h>

using namespace std;

int main()
{
	int playerID;
	int health;
	int level;
	int playerIsIngame;
	int playerIsLoadingscreen;
	char characterName[12];
	char gameState[12];
	
	HWND hwnd = FindWindowA(NULL, "World of Warcraft");
	DWORD procID;
	GetWindowThreadProcessId(hwnd, &procID);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	
	if(handle)
	{
		for(;;)
		{
			if(GetKeyState(VK_SPACE))
			{
				system("cls");
				//Player Character ID
				ReadProcessMemory(handle, (void*)((unsigned long long)0xCA1238), &playerID, sizeof(playerID), 0);
				
				//Player Name
				ReadProcessMemory(handle, (void*)((unsigned long long)0xC79D18), &characterName, sizeof(characterName), 0); 
				
				//Player Level
				ReadProcessMemory(handle, (void*)((unsigned long long)0x00400000  + 0x006DACA4), &level, sizeof(level), 0);
				ReadProcessMemory(handle, (void*)((unsigned long long)level + 0xC), &level, sizeof(level), 0);
				ReadProcessMemory(handle, (void*)((unsigned long long)level + 0x24), &level, sizeof(level), 0);
				ReadProcessMemory(handle, (void*)((unsigned long long)level + 0x8), &level, sizeof(level), 0);
				ReadProcessMemory(handle, (void*)((unsigned long long)level + 0xD8), &level, sizeof(level), 0);
				
				//Game State
				ReadProcessMemory(handle, (void*)((unsigned long long)0xB6A9E0), &gameState, sizeof(gameState), 0);
				
				//Online Bool
				ReadProcessMemory(handle, (void*)((unsigned long long)0xBD0792), &playerIsIngame, sizeof(playerIsIngame), 0);
				
				//Loading Bool
				ReadProcessMemory(handle, (void*)((unsigned long long)0xB6AA38), &playerIsLoadingscreen, sizeof(playerIsLoadingscreen), 0);
				
				if(playerIsIngame == 1)
				{
					if(playerIsLoadingscreen == 1)
					{
						cout << "Logging in..." << endl;
					}
					else if(playerIsLoadingscreen == 2)
					{
						cout << "Logged in Successfully" << endl;
					}
					else if(playerIsLoadingscreen == 3 || playerIsLoadingscreen == 10)
					{
						cout << "Loading..." << endl;
					}
					else
					{
						cout << "Character ID: " << playerID << endl;
						cout << "Character Name: " << characterName << endl;
						cout << "Character Level: " << level << endl;
					}
				}
				else
				{
					if(playerIsLoadingscreen == 1)
					{
						cout << "Logging in..." << endl;
					}
					else if(playerIsLoadingscreen == 2)
					{
						cout << "Logged in Successfully" << endl;
					}
					else if(playerIsLoadingscreen == 3 || playerIsLoadingscreen == 10)
					{
						cout << "Loading..." << endl;
					}
					else
					{
						cout << "State: " << gameState << endl;
					}
				}
				Sleep(1);
			}
		}
	}
}

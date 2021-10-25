#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain(void)
{
    TCHAR buffer[256] = TEXT("");
    TCHAR szDescription[8][32] = {TEXT("NetBIOS"), 
        TEXT("DNS hostname"), 
        TEXT("DNS domain"), 
        TEXT("DNS fully-qualified"), 
        TEXT("Physical NetBIOS"), 
        TEXT("Physical DNS hostname"), 
        TEXT("Physical DNS domain"), 
        TEXT("Physical DNS fully-qualified")};
    int cnf = 0;
    DWORD dwSize = _countof(buffer);
    
    for (cnf = 0; cnf < ComputerNameMax; cnf++)
    {
        if (!GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize))
        {
            _tprintf(TEXT("GetComputerNameEx failed (%d)\n"), GetLastError());
            return;
        }
        else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);

        dwSize = _countof(buffer);
        ZeroMemory(buffer, dwSize);
    }
}

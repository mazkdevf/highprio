#include <windows.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc != 2) {
        _tprintf(_T("Usage: %s <path_to_file>\n"), argv[0]);
        return 1;
    }

    // Set the priority class to HIGH_PRIORITY_CLASS
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};
    if (CreateProcess(
        argv[1],    // Application path
        NULL,       // Command line
        NULL,       // Process handle not inheritable
        NULL,       // Thread handle not inheritable
        FALSE,      // Set handle inheritance to FALSE
        HIGH_PRIORITY_CLASS, // Set the process priority class to high
        NULL,       // Use parent's environment block
        NULL,       // Use parent's starting directory 
        &si,        // Pointer to STARTUPINFO structure
        &pi         // Pointer to PROCESS_INFORMATION structure
    )) {
        // Wait for the process to finish (optional)
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        _tprintf(_T("Error creating process: %d\n"), GetLastError());
        return 1;
    }

    return 0;
}

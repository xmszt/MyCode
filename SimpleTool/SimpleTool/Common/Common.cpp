#include "stdafx.h"
#include "Common.h"

namespace common
{
    BOOL IsWin7()
    {
        OSVERSIONINFO osver;
        osver.dwOSVersionInfoSize = sizeof(osver);
        if (GetVersionEx(&osver))
        {
            if(osver.dwPlatformId == VER_PLATFORM_WIN32_NT
                && osver.dwMajorVersion == 6)
            {
                return TRUE;
            }
        }
        return FALSE;
    }

    BOOL IsWow64System()
    {
        typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
        LPFN_ISWOW64PROCESS fnIsWow64Process;
        BOOL bIsWow64 = FALSE;
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
        if (NULL != fnIsWow64Process)
        {
            fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
        }
        return bIsWow64;
    }

    void GetLocalPartition(vector<char>& vecPartions)
    {
        int nPos = 0;
        DWORD dwDriveList = ::GetLogicalDrives();
        CString strDrive = _T("?:");
        while(dwDriveList)
        {
            if (dwDriveList & 1)
            {
                strDrive.SetAt(0, 0x41 + nPos);
                UINT nType = ::GetDriveType((LPCTSTR)strDrive);
                switch (nType)
                {
                case DRIVE_FIXED:
                    vecPartions.push_back(0x41 + nPos);
                    break;
                default:
                    break;
                }
            }
            dwDriveList >>= 1;
            nPos++;
        }
    }
}

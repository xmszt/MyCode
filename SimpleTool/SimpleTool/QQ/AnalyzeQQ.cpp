#include "stdafx.h"
#include "AnalyzeQQ.h"
#include "..\Common\Common.h"

CAnalyzeQQ::CAnalyzeQQ()
{
}

CAnalyzeQQ::~CAnalyzeQQ()
{
}

void CAnalyzeQQ::LocateFile()
{
    LocateFromReg();
    LocateFromDir();
}

void CAnalyzeQQ::LocateFromReg()
{
    DWORD dwSize = MAX_PATH;
    TCHAR szPath[MAX_PATH] = {0};
    HKEY hKey;

    //通过注册表获取QQ安装目录
    vector<HKEY> vecHKey;
    vecHKey.push_back(HKEY_LOCAL_MACHINE);
    vecHKey.push_back(HKEY_CURRENT_USER);
    for (vector<HKEY>::iterator itr = vecHKey.begin(); itr != vecHKey.end(); itr++)
    {
        if (ERROR_SUCCESS != ::RegOpenKey(*itr, _T("Software\\Tencent\\QQ2009"), &hKey))
        {
            continue;
        }

        if (ERROR_SUCCESS != ::RegQueryValueEx(hKey, _T("Install"), NULL, NULL, (LPBYTE)szPath, &dwSize))
        {
            RegCloseKey(hKey);
            continue;
        }
        RegCloseKey(hKey);

        if (_tcslen(szPath) != 0)
        {
            CString strUserFolder = szPath;
            strUserFolder += _T("\\Users");
            if (PathFileExists(strUserFolder))
            {
                m_setUserFolder.insert(strUserFolder);
            }
        }
    }
}

void CAnalyzeQQ::LocateFromDir()
{
    CString strUserPath;
    CString strExtDefault = _T("\\Program Files\\Tencent\\QQ\\Users");    //QQ可能的用户目录

    //遍历本机所有硬盘分区
    vector<char> vecPartition;
    common::GetLocalPartition(vecPartition);
    for (vector<char>::iterator itr = vecPartition.begin(); itr != vecPartition.end(); itr++)
    {
        strUserPath.Format(_T("%c:%s"), *itr, strExtDefault);
        if (PathFileExists(strUserPath))
        {
            m_setUserFolder.insert(strUserPath);
        }
    }

    //QQ配置文件路径，保存用户定义的用户信息所在路径
    TCHAR szUserDir[MAX_PATH] = {0};
    TCHAR szDocument[MAX_PATH];
    SHGetSpecialFolderPath(NULL, szDocument, CSIDL_COMMON_DOCUMENTS, FALSE);
    CString strIniPath = szDocument;
    strIniPath += _T("\\Tencent\\QQ\\UserDataInfo.ini");
    ::GetPrivateProfileString(_T("UserDataSet"), _T("UserDataSavePath"), NULL, szUserDir, MAX_PATH, strIniPath);    //获取用户指定的目录
    strUserPath = szUserDir;
    if (PathFileExists(strUserPath))
    {
        m_setUserFolder.insert(strUserPath);
    }

    ::GetPrivateProfileString(_T("UserDataImportSet"), _T("OldVerDataPath"), NULL, szUserDir, MAX_PATH, strIniPath);    //旧版本QQ用户目录
    strUserPath = szUserDir;
    if (PathFileExists(strUserPath))
    {
        m_setUserFolder.insert(strUserPath);
    }
}


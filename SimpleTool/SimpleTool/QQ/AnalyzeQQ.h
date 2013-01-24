#ifndef ANALYZE_QQ_H
#define ANALYZE_QQ_H
#include <set>
#include <vector>
using namespace std;

class CAnalyzeQQ
{
public:
    CAnalyzeQQ();
    ~CAnalyzeQQ();

    void LocateFile();

private:
    void LocateFromReg();
    void LocateFromDir();

protected:
    set<CString> m_setUserFolder;        //QQ用户目录
    //vector<CString> m_vecFilePath;      //关联文件路径
};
#endif

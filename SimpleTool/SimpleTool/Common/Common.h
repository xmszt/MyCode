#ifndef COMMON_H
#define COMMON_H
#include <vector>
using namespace std;

namespace common
{
    BOOL IsWin7();
    BOOL IsWow64System();
    void GetLocalPartition(vector<char> &vecPartions);

}
#endif
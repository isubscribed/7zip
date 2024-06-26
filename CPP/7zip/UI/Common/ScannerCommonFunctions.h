#pragma once

enum class ScanFileState
{
    E_ScanFileState_None,							//File scan state: running
    E_ScanFileState_Abort						    //File scan state: scan abort by service
};

class CScannerCommonFunctions
{
public:
    bool CheckForScanAbortState(ScanFileState* pScanFileState);
};

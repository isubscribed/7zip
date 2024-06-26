#include "ScannerCommonFunctions.h"

bool CScannerCommonFunctions::CheckForScanAbortState(ScanFileState* pScanFileState)
{
    return *pScanFileState == ScanFileState::E_ScanFileState_Abort;
}

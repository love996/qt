#include "error_info.h"

std::map<int, const char*> ErrorMsg =
{
    {Unknown, "unknown"},
    {Success, "success"},
    {MallocFail, "alloc memory fail"},
    {OpenCameraFail, "open camera fail"},
    {GetExposureFail, "get exposure fail"},
    {SetExposureFail, "set exposure fail"},
    {GetVideoFpsFail, "get video fps fail"},
    {SetVideoFpsFail, "set video fps fail"},
};

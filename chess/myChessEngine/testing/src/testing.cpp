#include "testing_lib"

static bool debugEnabled = true;

bool isDebugEnabled()
{
    return debugEnabled;
}

void setDebugEnabled(bool enable)
{
    debugEnabled = enable;
}

#include "path_dependent_lib"
#include <algorithm>

PathDependent::PathDependent(const Vector &lookAtTimes) : lookAtTimes(lookAtTimes) {}

const Vector &PathDependent::getLookAtTimes() const
{
    return lookAtTimes;
}
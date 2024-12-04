#include<heapapi.h>
class MemChecker
{
public:
    static void EnableLeakCheck()
    {
        //da([ ]() = {assert(nullptr == ::GetHeapObjectInformation(None))
        ::HeapSetInformation(::GetProcessHeap(), HeapEnableTerminationOnCorruption,
            NULL, 0);
    }
};
// Here, it permits us to  check manually  memory ??malloc afterward verifying temperature
#include "memory.h"

void *memset(void *ptr, int c, size_t size)
{
    //sets all memory from ptr to ptr+size to a value
    char *c_ptr = (char *)ptr;
    for(int index = 0; index < size; index++)
    {
        c_ptr[index] = (char)c;
    } 

    return ptr;
}

int memcompare(void *value1, void *value2, int length)
{
    int different = 0;

    //compares each memory address for each pointer to determine if any are different
    for(int index = 0; index < length; index++)
    {
        char *memory1 = ((char *)value1)[index];
        char *memory2 = ((char *)value2)[index];

        if(memory1 != memory2)
        {
            different = 1;
            break;
        }
    }

    return different;
}
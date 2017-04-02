#include <stdio.h>
#include "rtspLib.h"
#include <unistd.h>

int main(void)
{
    printf("Hello World!\n");
    RtspServiceStart();
    while (1) {
        sleep(1);
    }
    return 0;
}


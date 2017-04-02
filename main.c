
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include "rtspLib.h"

static int s32_quit = 0;

static void signal_handler(int signo)
{
    switch (signo) {
    case SIGINT:
        s32_quit = 1;
//        exit(0);
        break;
    case SIGPIPE:
        break;
    default:
        break;
    }
    return;
}

static void init_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);
    return;
}

extern void *SAMPLE_VENC_1080P_CLASSIC(void *p);

int main(int argc, char *argv[])
{
    pthread_t id;
    init_signals();
    s32_quit = 0;
    pthread_create(&id, NULL, SAMPLE_VENC_1080P_CLASSIC, NULL);
    RtspServiceStart();

    while (!s32_quit) {
        sleep(1);
    }
    printf("The Server quit!\n");
    return 0;
}

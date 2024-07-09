#ifndef CLIPROG_H
#define CLIPROG_H

#include <stdbool.h>
#include <stdint.h>

typedef bool     b8;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;

typedef enum { CLI_SPINNER, CLI_BAR } cliProcType;

typedef struct {
    const char* Frames;
    u8          Framerate;
} cliSpinnerConfig;

#include <pthread.h>
#include <stdatomic.h>
#include <time.h>

typedef struct {
    cliSpinnerConfig _Conf;
    clock_t          _Beg;
    const char*      _StartMsg;
    pthread_t        _Th;
    _Atomic b8       _Active;
} cliSpinner;

static inline cliSpinner cliCreateSpinner(const char* StartMsg, const cliSpinnerConfig* Conf) {
    cliSpinner Proc;

    if (StartMsg) {
        Proc._StartMsg = StartMsg;
    } else {
        Proc._StartMsg = "";
    }

    if (Conf && Conf->Frames && Conf->Framerate > 0) {
        Proc._Conf = *Conf;
    } else {
        Proc._Conf = (cliSpinnerConfig){ .Frames = "|/-\\", .Framerate = 7 };
    }

    Proc._Active = false;
    return Proc;
}

#include <stdio.h>

static void*     _ThreadProcSpinner(void* _Arg);

static inline b8 cliStartSpinner(cliSpinner* Proc) {
    if (!Proc) { return false; }

    Proc->_Beg    = clock();
    Proc->_Active = true;

    i32 Result    = pthread_create(&Proc->_Th, NULL, _ThreadProcSpinner, (void*)(Proc));
    if (Result != 0) { return false; }

    printf("%s  ", Proc->_StartMsg);
    fflush(stdout);

    Result = pthread_detach(Proc->_Th);
    if (Result != 0) { return false; }

    return true;
}

static inline void cliStopSpinner(cliSpinner* Proc) {
    if (Proc) {
        atomic_store(&Proc->_Active, false);

        // f64 SecondsRan = (f64)(clock() - Proc->_Beg) / CLOCKS_PER_SEC;
        // printf("\b(%fs)\n", SecondsRan);
        puts("\b ");
    }
}

#include <string.h>
#include <unistd.h>

static inline void* _ThreadProcSpinner(void* _Arg) {
    cliSpinner* Proc           = (cliSpinner*)(_Arg);
    const u64   MicrosPerFrame = 1000000 / Proc->_Conf.Framerate;
    const u8    FrameCount     = strlen(Proc->_Conf.Frames);

    while (Proc && Proc->_Active) {
        for (u8 i = 0; i < FrameCount; ++i) {
            printf("\b%c", Proc->_Conf.Frames[i]);
            fflush(stdout);
            usleep(MicrosPerFrame);
        }
    }

    return NULL;
}

#endif

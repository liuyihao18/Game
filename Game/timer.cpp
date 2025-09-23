#include "config.h"
#include "core.h"
#include "framework.h"
#include <mmsystem.h>

#pragma region TQTIMER

static HANDLE hTimer = NULL;
static HANDLE hTimerQueue = NULL;

VOID CALLBACK onTQTimer(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    _CRT_UNUSED(TimerOrWaitFired);
	GameLoop((HWND)lpParam);
}

void InitTQTimer(HWND hWnd) {
    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        Log(0, "CreateTimerQueue failed (%d)\n");
        return;
    }

    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
        (WAITORTIMERCALLBACK)onTQTimer, (PVOID)hWnd, 0, (DWORD)(1000 / FPS), // timeout只接受整数
        WT_EXECUTEINTIMERTHREAD | WT_EXECUTELONGFUNCTION))
    {
        Log(0, "CreateTimerQueueTimer failed (%d)\n");
        return;
    }
}

void DeleteTQTimer() {
    if (!DeleteTimerQueue(hTimerQueue)) {
        Log(0, "DeleteTimerQueue failed (%d)\n");
    }
}

#pragma endregion

#pragma region MMTIMER

static UINT mmTimerID;
static UINT wTimerRes;

void CALLBACK onMMTimer(UINT wTimerID, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    _CRT_UNUSED(wTimerID);
    _CRT_UNUSED(msg);
    _CRT_UNUSED(dw1);
    _CRT_UNUSED(dw2);
    GameLoop((HWND)dwUser);
}

void InitMMTimer(HWND hWnd) {
    TIMECAPS tc;
    timeGetDevCaps(&tc, sizeof(TIMECAPS));

    const UINT target_resolution = 1000 / FPS;
    wTimerRes = min(max(tc.wPeriodMin, target_resolution), tc.wPeriodMax);
    timeBeginPeriod(wTimerRes);

    mmTimerID = timeSetEvent(
        wTimerRes,  // delay
        wTimerRes,  // resolution
        (LPTIMECALLBACK)onMMTimer,
        (DWORD_PTR)hWnd,
        TIME_PERIODIC
    );
}

void DeleteMMTimer() {
    timeKillEvent(mmTimerID);
    timeEndPeriod(wTimerRes);
}

#pragma endregion
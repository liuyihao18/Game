#include "stdafx.h"
#include "direct2d.h"

#include "scene.h"

static ID2D1Factory* pFactory = nullptr;
static ID2D1HwndRenderTarget* pRenderTarget = nullptr;
static HWND hWnd = nullptr;

HRESULT CreateGraphicsResources(HWND hwnd);
void DiscardGraphicsResources();

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

#pragma region 钩子函数

int D2DInit(HWND _hWnd) {
    if (FAILED(D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
    {
        return -1;  // Fail CreateWindowEx.
    }
    hWnd = _hWnd;
    return 0;
}

int D2DDestroy(HWND _hWnd) {
    if (_hWnd != hWnd) {
        return -1;
    }
    DiscardGraphicsResources();
    SafeRelease(&pFactory);
    hWnd = nullptr;
    return 0;
}

int D2DRender(HWND _hWnd) {
    if (_hWnd != hWnd) {
        return -1;
    }
    HRESULT hr = CreateGraphicsResources(hWnd);
    if (FAILED(hr))
    {
        return -1;
    }
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

    D2DRenderScene(pRenderTarget);

    hr = pRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
    {
        DiscardGraphicsResources();
        return -1;
    }
    EndPaint(hWnd, &ps);
    return 0;
}

int D2DResize(HWND _hWnd, UINT width, UINT height) {
    if (_hWnd != hWnd) {
        return -1;
    }
    if (pRenderTarget == nullptr)
    {
        return -1;
    }
    D2D1_SIZE_U size = D2D1::SizeU(width, height);

    pRenderTarget->Resize(size);
    return 0;
}

#pragma endregion

#pragma region 内部函数

void DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
}

HRESULT CreateGraphicsResources(HWND hWnd)
{
    HRESULT hr = S_OK;
    if (pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(),
                0.0F,
                0.0F,
                D2D1_RENDER_TARGET_USAGE_NONE
            ),
            D2D1::HwndRenderTargetProperties(
                hWnd,
                size,
                D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS
            ),
            &pRenderTarget);
    }
    return hr;
}

#pragma endregion

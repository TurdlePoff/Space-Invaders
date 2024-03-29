//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "BackBuffer.h"
// Description	: Declaration file for BackBuffer
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#if !defined(__BACKBUFFER_H__)
#define __BACKBUFFER_H__

// Library Includes
#include <Windows.h>

class CBackBuffer
{
    // Member Functions
public:
    CBackBuffer();
    ~CBackBuffer();

    bool Initialise(HWND _hWnd, int _iWidth, int _iHeight);

    HDC GetBFDC() const;

    int GetHeight() const;
    int GetWidth() const;

    void Clear();
    void Present();

protected:

private:
    CBackBuffer(const CBackBuffer& _kr);
    CBackBuffer& operator= (const CBackBuffer& _kr);

    // Member Variables
public:

protected:
    HWND m_hWnd;
    HDC m_hDC;
    HBITMAP m_hSurface;
    HBITMAP m_hOldObject;
    int m_iWidth;
    int m_iHeight;

private:

};

#endif    // __BACKBUFFER_H__


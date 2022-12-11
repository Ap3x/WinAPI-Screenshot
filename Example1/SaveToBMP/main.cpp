#include <windows.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <gdiplus.h>

using namespace Gdiplus;

void screenshot(LPCSTR filename)
{
    // Get the dimensions of the screen
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    
    // Create a compatible bitmap for the device context
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
    HDC hDc = CreateCompatibleDC(0);
    SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, GetDC(0), 0, 0, SRCCOPY | CAPTUREBLT);
    Bitmap bitmap(hBmp, NULL);
    
    // Create a Bitmap file
    HANDLE hBmpFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Setting up bitmap header information
    BITMAPFILEHEADER bmfHeader;
    int bmp_padding = (width * 3) % 4;
    if (bmp_padding != 0) bmp_padding = 4 - bmp_padding;
    DWORD dwSizeofDIB = (width * 3 + bmp_padding) * height + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
    bmfHeader.bfSize = dwSizeofDIB;
    bmfHeader.bfType = 0x4D42; //BM


    BITMAPINFO bmpInfo = { 0 };
    bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
    bmpInfo.bmiHeader.biWidth = width;
    bmpInfo.bmiHeader.biHeight = height;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 24;
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    BYTE* bmp_pixels = new BYTE[(width * 3 + bmp_padding) * height];;
    GetDIBits(hDc, hBmp, 0, height, bmp_pixels, &bmpInfo, DIB_RGB_COLORS);

    // Writing bitmap data to file
    DWORD dwBytesWritten = 0;
    WriteFile(hBmpFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hBmpFile, (LPSTR)&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hBmpFile, (LPSTR)bmp_pixels, (width * 3 + bmp_padding) * height, &dwBytesWritten, NULL);
    
    DeleteDC(hDc);
    ReleaseDC(HWND_DESKTOP, GetDC(0));
}

int main()
{
    screenshot("Ap3x-ScreenCapture.bmp");
    return 0; 
}
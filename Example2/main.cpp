#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <memory>

using namespace Gdiplus;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0;          // number of image encoders
    UINT size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
    {
        return -1;  // Failure
    }

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
    {
        return -1;  // Failure
    }

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }    
    }

    free(pImageCodecInfo);
    return -1;  // Failure
}

void BitmapToJpg(HBITMAP hbmpImage, int width, int height, WCHAR* filename )
{
    Bitmap *p_bmp = Bitmap::FromHBITMAP(hbmpImage, NULL);
    CLSID pngClsid;

    GetEncoderClsid(L"image/jpeg", &pngClsid);
    p_bmp->Save(filename, &pngClsid, NULL);
    delete p_bmp;
}

bool ScreenCapture(int x, int y, int width, int height, const wchar_t* filename)
{
    // Create a compatible bitmap for the device context
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	HDC hDc = CreateCompatibleDC(0);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
    BitmapToJpg(hBmp, width, height, (WCHAR*)filename);
	DeleteObject(hBmp);
	return true;
}

int main() {
    const wchar_t* filename = L"Ap3x-ScreenCapture.jpg";

    // Initialize GDI+.
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
	int x1 = 0;
	int y1 = 0;
	int x2 = GetSystemMetrics(SM_CXSCREEN);
	int y2 = GetSystemMetrics(SM_CYSCREEN);

	ScreenCapture(x1, y1, x2, y2, filename);
    
    //Shutdown GDI+
    GdiplusShutdown(gdiplusToken);
    
	return 0;
}
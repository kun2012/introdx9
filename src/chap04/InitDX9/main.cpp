#include "d3dApp.h"
#include <string.h>
#include <crtdbg.h>

class InitDX9App : public D3DApp
{
public:
	InitDX9App(HINSTANCE hInstance, std::wstring winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	virtual ~InitDX9App();

	virtual bool checkDeviceCaps() override;
	virtual void onLostDevice() override;
	virtual void onResetDevice() override;
	virtual void updateScene(float dt) override;
	virtual void drawScene() override;

private:
	ID3DXFont* mFont;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
#if defined (DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	InitDX9App app(hInstance, L"Hello Direct3D 9", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &app;

	return gd3dApp->run();
}

InitDX9App::InitDX9App(HINSTANCE hInstance, std::wstring winCaption, D3DDEVTYPE devType, DWORD requestedVP)
	: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	srand(time_t(0));

	if (!checkDeviceCaps())
	{
		MessageBox(0, L"checkDeviceCaps() failed", 0, 0);
		PostQuitMessage(0);
	}

	D3DXFONT_DESC fontDesc;
	fontDesc.Height          = 80;
	fontDesc.Width           = 40;
	fontDesc.Weight          = FW_BOLD;
	fontDesc.MipLevels       = 0;
	fontDesc.Italic          = true;
	fontDesc.CharSet         = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(fontDesc.FaceName, LF_FACESIZE, L"Times New Roman");

	HR(D3DXCreateFontIndirect(gd3dDevice, &fontDesc, &mFont));
}

InitDX9App::~InitDX9App()
{
	SafeRelease(mFont);
}

bool InitDX9App::checkDeviceCaps()
{
	return true;
}

void InitDX9App::onLostDevice()
{
	HR(mFont->OnLostDevice());
}

void InitDX9App::onResetDevice()
{
	HR(mFont->OnResetDevice());
}

void InitDX9App::updateScene(float dt)
{
}

void InitDX9App::drawScene()
{
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0));

	RECT formatRect;
	GetClientRect(mhMainWnd, &formatRect);

	HR(gd3dDevice->BeginScene());

	mFont->DrawText(0, L"Hello Direct3D 9", -1, &formatRect, DT_CENTER | DT_VCENTER,
		D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

	HR(gd3dDevice->EndScene());
	HR(gd3dDevice->Present(0, 0, 0, 0));
}
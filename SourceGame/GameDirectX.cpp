#include "GameDirectX.h"
#include"List.h"

GameDirectX::GameDirectX(void)
{
	this->hWnd = WindowGame::getInstance()->getHandleWindow();
	init();
}


GameDirectX::~GameDirectX(void)
{
	Release();
}

GameDirectX* GameDirectX::instance = 0;

GameDirectX* GameDirectX::getInstance()
{
	if (instance == 0)
		instance = new GameDirectX();
	return instance;
}

bool GameDirectX::initDirectXWithSize(int backbufferWidth, int backbufferHeight)
{

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = backbufferWidth;
	d3dpp.BackBufferHeight = backbufferHeight;
	d3dpp.hDeviceWindow = this->hWnd;


	auto x = d3ddv->Reset(&d3dpp);

	List<HRESULT> results;
	results._Add(D3DERR_CONFLICTINGRENDERSTATE);
	results._Add(D3DERR_CONFLICTINGTEXTUREFILTER);
	results._Add(D3DERR_CONFLICTINGTEXTUREPALETTE);
	results._Add(D3DERR_DEVICEHUNG);
	results._Add(D3DERR_DEVICELOST);
	results._Add(D3DERR_DEVICENOTRESET);
	results._Add(D3DERR_DEVICEREMOVED);
	results._Add(D3DERR_DRIVERINTERNALERROR);
	results._Add(D3DERR_DRIVERINVALIDCALL);
	results._Add(D3DERR_INVALIDCALL);
	results._Add(D3DERR_INVALIDDEVICE);
	results._Add(D3DERR_MOREDATA);
	results._Add(D3DERR_NOTAVAILABLE);
	results._Add(D3DERR_NOTFOUND);
	results._Add(D3D_OK);
	results._Add(D3DERR_OUTOFVIDEOMEMORY);
	results._Add(D3DERR_TOOMANYOPERATIONS);
	results._Add(D3DERR_UNSUPPORTEDALPHAARG);
	results._Add(D3DERR_UNSUPPORTEDALPHAOPERATION);
	results._Add(D3DERR_UNSUPPORTEDCOLORARG);
	results._Add(D3DERR_UNSUPPORTEDCOLOROPERATION);
	results._Add(D3DERR_UNSUPPORTEDFACTORVALUE);
	results._Add(D3DERR_UNSUPPORTEDTEXTUREFILTER);
	results._Add(D3DERR_WASSTILLDRAWING);
	results._Add(D3DERR_WRONGTEXTUREFORMAT);

	auto y = results._IndexOf(x);

	if (!isSetBackBuffer())
	{
		int a = 5;
	}


	return true;
}


bool GameDirectX::initDirectX()
{
	LPDIRECT3D9 d3d;
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = GLOBALS_D("backbuffer_width");
	d3dpp.BackBufferHeight = GLOBALS_D("backbuffer_height");

	backbufferWidth = GLOBALS_D("backbuffer_width");
	backbufferHeight = GLOBALS_D("backbuffer_height");

	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv)))
	{
		return false;
	}
	if (!d3ddv)
		return false;
	d3d->Release();
	return true;
}

bool GameDirectX::isInitSprite()
{
	HRESULT hr = D3DXCreateSprite(d3ddv, &sprite);
	return !FAILED(hr);
}

bool GameDirectX::isSetBackBuffer()
{
	HRESULT hr = d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&backBuffer);
	return !FAILED(hr);
}

void GameDirectX::init()
{
	if (!initDirectX() || !isInitSprite() || !isSetBackBuffer())
		error();
}

void GameDirectX::error()
{
	MessageBoxA(hWnd, "Khong the khoi tao graphics", "Loi", MB_ICONERROR);
}




void GameDirectX::Release()
{
	if (d3ddv)
	{
		d3ddv->Release();
		d3ddv = 0;
	}
	if (backBuffer)
	{
		backBuffer->Release();
		backBuffer = 0;

	}
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}



LPDIRECT3DDEVICE9 GameDirectX::GetDevice()
{
	return d3ddv;
}

LPDIRECT3DSURFACE9 GameDirectX::GetBackBuffer()
{
	return backBuffer;
}

LPD3DXSPRITE GameDirectX::GetSprite()
{
	return sprite;
}

void GameDirectX::PrintText(char* str, int size, int x, int y, DWORD color)
{
	ID3DXFont* dxfont;
	RECT textbox;
	SetRect(&textbox, x, y, 272, 272);
	D3DXCreateFontA(d3ddv,    // the D3D Device
		size,    // font height
		0,    // default font width
		FW_NORMAL,    // font weight
		1,    // not using MipLevels
		false,    // italic font
		DEFAULT_CHARSET,    // default character set
		OUT_DEFAULT_PRECIS,    // default OutputPrecision,
		DEFAULT_QUALITY,    // default Quality
		DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
		"Arial",    // use Facename Arial
		&dxfont);    // the font object
	dxfont->DrawTextA(NULL,
		str,
		strlen(str),
		&textbox,
		DT_LEFT | DT_TOP,
		color);

	dxfont->Release();
}

void GameDirectX::BeginGraphics()
{
	HRESULT hr = d3ddv->BeginScene();
	HRESULT hr1 = sprite->Begin(D3DXSPRITE_ALPHABLEND);
	// khởi tạo màu trong suốt
	d3ddv->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(10, 10, 10), 1.0f, 0);
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBoxA(0, "Khong the bat dau ve", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void GameDirectX::EndGraphics()
{
	HRESULT hr1 = sprite->End();
	HRESULT hr = d3ddv->EndScene();
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBoxA(0, "Khong the ket thuc ve", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}

}

void GameDirectX::PresentBackBuffer()
{
	d3ddv->Present(0, 0, 0, 0);
}

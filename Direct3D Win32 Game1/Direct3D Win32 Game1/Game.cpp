//
// Game.cpp -
//

#include "pch.h"
#include "Game.h"
#include<d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
using namespace DirectX;
using namespace CourseWork;

using Microsoft::WRL::ComPtr;

// Constructor.
Game::Game() :
	m_window(0),
	m_outputWidth(800),
	m_outputHeight(600),
	m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
	DungeonInitializer *g = new DungeonInitializer();
	_dungeon = g->Initialize();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max( width, 1 );
    m_outputHeight = std::max( height, 1 );

    CreateDevice();

    CreateResources();

	LoadContent();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

// Executes basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here
	XMMATRIX m = XMMatrixIdentity();
	m = XMMatrixMultiply(m, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	XMStoreFloat4x4(&m_constantBufferData.model, m);
    elapsedTime;
}

void Game::Update()
{
	// TODO: Add your game logic here
	XMMATRIX m = XMMatrixIdentity();
	m = XMMatrixMultiply(m, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	XMStoreFloat4x4(&m_constantBufferData.model, m);
}

// Draws the scene
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
        return;

    Clear();

    // TODO: Add your rendering code here

	auto context = m_d3dContext;
	
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(viewMatrix_));
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(viewMatrix_));
	XMStoreFloat4x4(&m_constantBufferData.projection, XMMatrixTranspose(projMatrix_));
	m_d3dContext->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);

	/*m_d3dContext->UpdateSubresource(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0
		);*/

	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	// Attach our vertex shader.
	m_d3dContext->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	m_d3dContext->VSSetConstantBuffers(
		0,
		1,
		m_constantBuffer.GetAddressOf()
		);

	// Attach our pixel shader.
	m_d3dContext->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_d3dContext->IASetInputLayout(m_inputLayout.Get());


	/*XMMATRIX rotationMat = XMMatrixRotationRollPitchYaw(0.0f, 0.7f, 0.7f);
	XMMATRIX translationMat = XMMatrixTranslation(0.0f, 0.0f, 6.0f);

	XMMATRIX worldMat = rotationMat * translationMat;
	worldMat = XMMatrixTranspose(worldMat);*/

	/*context->UpdateSubresource(worldCB_, 0, 0, &worldMat, 0, 0);
	context->UpdateSubresource(viewCB_, 0, 0, &viewMatrix_, 0, 0);
	context->UpdateSubresource(projCB_, 0, 0, &projMatrix_, 0, 0);*/

	/*context->VSSetConstantBuffers(0, 1, &worldCB_);
	context->VSSetConstantBuffers(1, 1, &viewCB_);
	context->VSSetConstantBuffers(2, 1, &projCB_);*/
	//context->VSSetConstantBuffers(0, 1, &m_constantBuffer);
	for (int i = 0; i < _dungeon->GetMaps()[0]->GetHeight()*_dungeon->GetMaps()[0]->GetWidth(); i++)
	{
		m_d3dContext->IASetVertexBuffers(
			0,
			1,
			vertexBuffers[0].GetAddressOf(),
			&stride,
			&offset
			);

		m_d3dContext->IASetIndexBuffer(
			indexBuffers[0].Get(),
			DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
			0
			);
		m_d3dContext->DrawIndexed(
			indexCounts[0],
			0,
			0
			);
		//Present();
	}

    Present();
}

// Helper method to clear the backbuffers
void Game::Clear()
{
    // Clear the views
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    CD3D11_VIEWPORT viewPort(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewPort);
}

// Presents the backbuffer contents to the screen
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized)
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize)
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200)
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling)
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,                          // optionally set debug and Direct2D compatibility flags
        featureLevels,                          // list of feature levels this app can support
        _countof(featureLevels),                // number of entries in above list
        D3D11_SDK_VERSION,                      // always set this to D3D11_SDK_VERSION
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                creationFlags, &featureLevels[1], _countof(featureLevels) - 1,
                                D3D11_SDK_VERSION, m_d3dDevice.ReleaseAndGetAddressOf(),
                                &m_featureLevel, m_d3dContext.ReleaseAndGetAddressOf());
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    hr = m_d3dDevice.As(&d3dDebug);
    if (SUCCEEDED(hr))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        hr = d3dDebug.As(&d3dInfoQueue);
        if (SUCCEEDED(hr))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed 
            };
            D3D11_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    hr = m_d3dDevice.As(&m_d3dDevice1);
    if (SUCCEEDED(hr))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size)
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(2, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        HRESULT hr = dxgiFactory.As(&dxgiFactory2);
        if (SUCCEEDED(hr))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = 2;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(), m_window, &swapChainDesc,
                &fsSwapChainDesc,
                nullptr, m_swapChain1.ReleaseAndGetAddressOf()));

            m_swapChain1.As(&m_swapChain);
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = 2;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support 'full-screen' mode and prevents the ALT+ENTER shortcut from working
        dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER);
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here
	/*float aspectRatio = 800 / 600;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);
	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix)
		);
	static const XMVECTORF32 eye = { 0.0f, 10.0f, 0.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));*/
	//
	D3D11_VIEWPORT vp;

	vp.Width = (FLOAT)m_outputWidth;

	vp.Height = (FLOAT)m_outputHeight;

	vp.MinDepth = 0.0f;

	vp.MaxDepth = 1.0f;

	vp.TopLeftX = 0;

	vp.TopLeftY = 0;

	m_d3dContext->RSSetViewports(1, &vp);
	//
	//LoadContent();
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here

    m_depthStencil.Reset();
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

void Game::InitMapGraph()
{
	VertexPositionColor wallFrag[8] = {
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f) }, };

	VertexPositionColor floorFrag[4] =
	{
		{ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.0f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) }
	};

	int indexCount;

	unsigned short cubeIndices[] =
	{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};

	unsigned short floorIndices[] =
	{
		0,1,2,
		1,3,2
	};

	/*int k = 0;*/
	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(wallFrag), D3D11_BIND_VERTEX_BUFFER);
	CD3D11_BUFFER_DESC vertexBufferDesc1(sizeof(floorFrag), D3D11_BIND_VERTEX_BUFFER);

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	CD3D11_BUFFER_DESC indexBufferDesc1(sizeof(floorIndices), D3D11_BIND_INDEX_BUFFER);

	/*vertexBuffers = { nullptr };
	indexBuffers = { nullptr };*/

	Microsoft::WRL::ComPtr<ID3D11Buffer> vtemp;
	Microsoft::WRL::ComPtr<ID3D11Buffer> itemp;

	for (int i = 0; i < _dungeon->GetMaps()[0]->GetWidth(); i++)
		for (int j = 0; j < _dungeon->GetMaps()[0]->GetHeight(); j++)
		{
			if (_dungeon->GetMaps()[0]->GetPattern()[i][j] == wall)
			{
				wallFrag[0] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep() + 1.0f),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[1] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[2] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep() + 1.0f),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[3] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[4] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, 0.0f, i*_dungeon->GetMaps()[0]->GetStep() + 1.0f),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[5] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, 0.0f, i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[6] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep() + 1.0f),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[7] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};

				vertexBufferData.pSysMem = wallFrag;
				indexBufferData.pSysMem = cubeIndices;
				DX::ThrowIfFailed(
					m_d3dDevice->CreateBuffer(
						&vertexBufferDesc,
						&vertexBufferData,
						&vtemp
						)
					);
				DX::ThrowIfFailed(
					m_d3dDevice->CreateBuffer(
						&indexBufferDesc,
						&indexBufferData,
						&itemp
						)
					);
				indexCount = ARRAYSIZE(cubeIndices);
			}
			else
			{
				floorFrag[0] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep() + 1.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[1] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep()), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[2] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, 0.0f, i*_dungeon->GetMaps()[0]->GetStep() + 1.0), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[3] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep() + 1.0f, 0.0f, i*_dungeon->GetMaps()[0]->GetStep()),XMFLOAT3(1.0f, 1.0f, 0.0f) };
				vertexBufferData.pSysMem = floorFrag;
				indexBufferData.pSysMem = floorIndices;
				DX::ThrowIfFailed(
					m_d3dDevice->CreateBuffer(
						&vertexBufferDesc1,
						&vertexBufferData,
						&vtemp
						)
					);
				DX::ThrowIfFailed(
					m_d3dDevice->CreateBuffer(
						&indexBufferDesc1,
						&indexBufferData,
						&itemp
						)
					);
				indexCount = ARRAYSIZE(floorIndices);
			}
			vertexBuffers.push_back(vtemp);
			indexBuffers.push_back(itemp);
			indexCounts.push_back(indexCount);
		}
}

HRESULT Game::CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob)
{
	if (!srcFile || !entryPoint || !profile || !blob)
		return E_INVALIDARG;

	*blob = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(srcFile, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint, profile,
		flags, 0, &shaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}

		if (shaderBlob)
			shaderBlob->Release();

		return hr;
	}

	*blob = shaderBlob;

	return hr;
}

bool Game::LoadContent()
{
	ID3DBlob *vsBlob = nullptr;
	HRESULT hr1 = CompileShader(L"SampleVertexShader.hlsl", "main", "vs_4_0_level_9_1", &vsBlob);
	// Compile pixel shader shader
	ID3DBlob *psBlob = nullptr;
	hr1 = CompileShader(L"SamplePixelShader.hlsl", "main", "ps_4_0_level_9_1", &psBlob);

	HRESULT d3dResult;

	d3dResult = m_d3dDevice->CreateVertexShader(vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(), 0, &m_vertexShader);

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);
	LPVOID g = vsBlob->GetBufferPointer(); 
	SIZE_T t = vsBlob->GetBufferSize();
	d3dResult = m_d3dDevice->CreateInputLayout(solidColorLayout, totalLayoutElements,
		vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);

	vsBlob->Release();

	d3dResult = m_d3dDevice->CreatePixelShader(psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(), 0, &m_pixelShader);

	psBlob->Release();

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_d3dDevice->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&m_constantBuffer
			)
		);

	InitMapGraph();

	/*d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_,
		"decal.dds", 0, 0, &colorMap_, 0);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG("Failed to load the texture image!");
		return false;
	}*/

	/*D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = d3dDevice_->CreateSamplerState(&colorMapDesc, &colorMapSampler_);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG("Failed to create color map sampler state!");
		return false;
	}*/


	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc, sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(XMMATRIX);
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	d3dResult = m_d3dDevice->CreateBuffer(&constDesc, 0, &viewCB_);

	if (FAILED(d3dResult))
	{
		return false;
	}

	d3dResult = m_d3dDevice->CreateBuffer(&constDesc, 0, &projCB_);

	if (FAILED(d3dResult))
	{
		return false;
	}

	d3dResult = m_d3dDevice->CreateBuffer(&constDesc, 0, &worldCB_);

	if (FAILED(d3dResult))
	{
		return false;
	}

	viewMatrix_ = XMMatrixIdentity();
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.01f, 100.0f);

	viewMatrix_ = XMMatrixTranspose(viewMatrix_);
	projMatrix_ = XMMatrixTranspose(projMatrix_);

	return true;
}
//
// Game.h
//

#pragma once

#include "StepTimer.h"

#include "ShaderStructures.h"
//#include "Dungeon.h"
#include "DungeonInitializer.h"
#include <dinput.h>
//#include "VSD3DStarter.h"
//#include "StepTimer.h"

//using namespace VSD3DStarter;

// A basic game implementation that creates a D3D11 device and
// provides a game loop
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();
    void Present();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properites
    void GetDefaultSize( int& width, int& height ) const;

	void InitMapGraph();
	HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob);
	bool LoadContent();
	void Update();
private:

    void Update(DX::StepTimer const& timer);

    void CreateDevice();
    void CreateResources();
    
    void OnDeviceLost();

    // Application state
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    // Direct3D Objects
    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    // Rendering resources
    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_depthStencil;

    // Game state
    DX::StepTimer                                   m_timer;
	vector<int> indexCounts;
	vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> vertexBuffers;
	vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> indexBuffers;
	CourseWork::Dungeon *_dungeon;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
	CourseWork::ModelViewProjectionConstantBuffer	m_constantBufferData;

	ID3D11Buffer* viewCB_;
	ID3D11Buffer* projCB_;
	ID3D11Buffer* worldCB_;
	XMMATRIX viewMatrix_;
	XMMATRIX projMatrix_;
};


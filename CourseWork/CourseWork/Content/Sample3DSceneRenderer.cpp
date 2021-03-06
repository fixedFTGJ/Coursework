﻿#include "pch.h"
#include "Sample3DSceneRenderer.h"
#include "Header.h"
#include "..\Common\DirectXHelper.h"

using namespace CourseWork;
using namespace DirectX;
using namespace Windows::Foundation;
using namespace VSD3DStarter;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Store;
using namespace Windows::Graphics::Display;
using namespace Windows::Storage;
using namespace Windows::UI::Input;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::System::Threading;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	DungeonInitializer m;
	_dungeon = m.Initialize();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

void Sample3DSceneRenderer::OnKeyDown(
	__in CoreWindow^ sender,
	__in KeyEventArgs^ args)
{
	Windows::System::VirtualKey Key;
	Key = args->VirtualKey;

	// figure out the command from the keyboard
	/*if (Key == VirtualKey::W)		// forward
		m_forward = true;
	if (Key == VirtualKey::S)		// back
		m_back = true;
	if (Key == VirtualKey::A)		// left
		m_left = true;
	if (Key == VirtualKey::D)		// right
		m_right = true;*/
}
// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);
	cam.SetPosition(XMFLOAT3(_dungeon->GetMaps()[0]->GetStartPosition().X*0.5f + 1.0f, 0.5f, _dungeon->GetMaps()[0]->GetStartPosition().Y*0.5f +1.0f));
	cam.SetLookAt(XMFLOAT3(_dungeon->GetMaps()[0]->GetStartPosition().X*0.5f + 1.0f, 0.5f, _dungeon->GetMaps()[0]->GetStartPosition().Y*0.5f + 2.0f));

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	/*static const XMVECTORF32 eye = { 2.0f, 2.0f, 2.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };*/
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(XMLoadFloat3(&cam.GetPosition()), XMLoadFloat3(&cam.GetLookAt()), up)));
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
<<<<<<< HEAD
	
		XMMATRIX m = XMMatrixIdentity();
		m = XMMatrixMultiply(m, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
		//m = XMMatrixMultiply(m, XMMatrixRotationY(radians));
		//m = XMMatrixMultiply(m, XMMatrixScaling(0.1f, 0.1f, 0.1f));
		XMStoreFloat4x4(&m_constantBufferData.model, m);
=======

		//Rotate(90.0);
>>>>>>> origin/master
		//Rotate(radians);
	}
}

void CourseWork::Sample3DSceneRenderer::InitMapGraph()
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

	uint32 indexCount;

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
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep()+1.0),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[1] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0, i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[2] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep()+1.0),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[3] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[4] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+1.0, 0.0, i*_dungeon->GetMaps()[0]->GetStep() + 1.0),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[5] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+1.0, 0.0, i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[6] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+1.0, _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep() + 1.0),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};
				wallFrag[7] = {
					XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+ 1.0, _dungeon->GetMaps()[0]->GetStep(), i*_dungeon->GetMaps()[0]->GetStep()),
					XMFLOAT3(0.0f, 1.0f, 0.0f)
				};

				vertexBufferData.pSysMem = wallFrag;
				indexBufferData.pSysMem = cubeIndices;
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
						&vertexBufferDesc,
						&vertexBufferData,
						&vtemp
						)
					);
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
						&indexBufferDesc,
						&indexBufferData,
						&itemp
						)
					);
				indexCount = ARRAYSIZE(cubeIndices);
			}
			else
			{
				floorFrag[0] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep()+1.0), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[1] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep(), 0.0f, i*_dungeon->GetMaps()[0]->GetStep()), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[2] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+1.0, 0.0f, i*_dungeon->GetMaps()[0]->GetStep()+1.0), XMFLOAT3(1.0f, 1.0f, 0.0f) };
				floorFrag[3] = { XMFLOAT3(j*_dungeon->GetMaps()[0]->GetStep()+1.0, 0.0f, i*_dungeon->GetMaps()[0]->GetStep()),XMFLOAT3(1.0f, 1.0f, 0.0f) };
				vertexBufferData.pSysMem = floorFrag;
				indexBufferData.pSysMem = floorIndices;
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
						&vertexBufferDesc1,
						&vertexBufferData,
						&vtemp
						)
					);
				DX::ThrowIfFailed(
					m_deviceResources->GetD3DDevice()->CreateBuffer(
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

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
		//Rotate(90.0);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
/*	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);*/

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers(
		0,
		1,
		m_constantBuffer.GetAddressOf()
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	// Draw the objects.
	/*context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);*/

	/*context->IASetVertexBuffers(
		0,
		1,
		m_v.GetAddressOf(),
		&stride,
		&offset
		);

	context->Draw(m_i, 0);*/

	for (int i = 0; i < _dungeon->GetMaps()[0]->GetHeight()*_dungeon->GetMaps()[0]->GetWidth(); i++)
	{
		context->IASetVertexBuffers(
			0,
			1,
			vertexBuffers[i].GetAddressOf(),
			&stride,
			&offset
			);

		context->IASetIndexBuffer(
			indexBuffers[i].Get(),
			DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
			0
			);
		context->DrawIndexed(
			indexCounts[i],
			0,
			0
			);
	}
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	// Load shaders asynchronously.
	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader
				)
			);

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				&fileData[0],
				fileData.size(),
				&m_inputLayout
				)
			);
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});


	// Once both shaders are loaded, create the mesh.
	auto createCubeTask = (createPSTask && createVSTask).then([this] () {

		// Load mesh vertices. Each vertex has a position and a color.
		static const VertexPositionColor cubeVertices[] = 
		{
			{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
			{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
			{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
			{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
			{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
			{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
			{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
			{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&m_vertexBuffer
				)
			);

		// Load mesh indices. Each trio of indices represents
		// a triangle to be rendered on the screen.
		// For example: 0,2,1 means that the vertices with indexes
		// 0, 2 and 1 from the vertex buffer compose the 
		// first triangle of this mesh.
		static const unsigned short cubeIndices [] =
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

		m_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&m_indexBuffer
				)
			);

		//
		InitMapGraph();

		/*Coursework::ObjModel objModel;
		if (objModel.LoadOBJ("Assets/Desktop.txt") == false)
		{
		}
		m_i = objModel.GetTotalVerts();
		VertexPositionColor* vertices = new VertexPositionColor[m_i];
		float* vertsPtr = objModel.GetVertices();
		//float* texCPtr = objModel.GetTexCoords();
		for (int i = 0; i < m_i; i++)
		{
			vertices[i].pos = XMFLOAT3(*(vertsPtr + 0), *(vertsPtr + 1), *(vertsPtr + 2));
			vertsPtr += 3;
			vertices[i].color = XMFLOAT3(1.0f, 0.0f, 0.0f);
			//texCPtr += 2;
		}
		D3D11_BUFFER_DESC vertexDesc1;
		ZeroMemory(&vertexDesc1, sizeof(vertexDesc1));
		vertexDesc1.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc1.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc1.ByteWidth = sizeof(VertexPositionColor) * m_i;
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = vertices;
		m_deviceResources->GetD3DDevice()->CreateBuffer(&vertexDesc1, &resourceData,
			&m_v);
		delete[] vertices;
		objModel.Release();*/
		//
	});

	// Once the cube is loaded, the object is ready to be rendered.
	createCubeTask.then([this] () {
		m_loadingComplete = true;
	});
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();

	for (auto buffer : vertexBuffers)
		buffer.Reset();
	for (auto buffer : indexBuffers)
		buffer.Reset();
}
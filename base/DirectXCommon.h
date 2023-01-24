#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"
#include <chrono>
#include <thread>

#include "WinApp.h"

// DirectX汎用
class DirectXCommon
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// 初期化
	void Initialize(WinApp* win);

	// 描画前処理
	void PreDraw();

	// 描画後処理
	void PostDraw();

	// レンダーターゲットのクリア
	void ClearRenderTarget();

	// 深度バッファのクリア
	void ClearDepthBuffer();

	// デバイスの取得
	// <returns>デバイス</returns>
	ID3D12Device* GetDevice() { return device.Get(); }

	// 描画コマンドリストの取得
	// <returns>描画コマンドリスト</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }

	void InitializeFixFPS();

	void UpdateFixFPS();

	std::chrono::steady_clock::time_point reference_;


private: // メンバ変数
	// ウィンドウズアプリケーション管理
	WinApp* winApp;

	// Direct3D関連
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	ComPtr<ID3D12DescriptorHeap> _heapForImgui; //ヒープ保持用

private: // メンバ関数
	// DXGIデバイス初期化
	// <returns>成否</returns>
	bool InitializeDXGIDevice();

	// スワップチェーンの生成
	// <returns>成否</returns>
	bool CreateSwapChain();

	// コマンド関連初期化
	// <returns>成否</returns>
	bool InitializeCommand();

	// レンダーターゲット生成
	// <returns>成否</returns>
	bool CreateFinalRenderTargets();

	// 深度バッファ生成
	// <returns>成否</returns>
	bool CreateDepthBuffer();

	// フェンス生成
	// <returns>成否</returns>
	bool CreateFence();	

	//imgui初期化
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeapForImgui();

	ComPtr<ID3D12DescriptorHeap> GetHeapForImgui();

	bool InitializeImgui();
};


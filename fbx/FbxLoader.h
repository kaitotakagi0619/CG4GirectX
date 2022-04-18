#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>

class FbxLoader
{
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	void Initialize(ID3D12Device* device);

	void Finalize();

	static FbxLoader* GetInstance();

private:

	ID3D12Device* device = nullptr;

	FbxManager* fbxManager = nullptr;

	FbxImporter* fbxImporter = nullptr;
	// コンストラクタ
	FbxLoader() = default;
	// デストラクタ
	~FbxLoader() = default;
	// コピーコンストラクタを禁止
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止
	void operator=(const FbxLoader& obj) = delete;
};
#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxLoader
{
private:
	using string = std::string;
public:
	static const string baseDirectory;
	void LoadModelFromFile(const string& modelName);
public:
	// 初期化
	void Initialize(ID3D12Device* device);
	// ファイナライズ
	void Finalize();

	// シングルトンインスタンスの取得
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
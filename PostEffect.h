#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    PostEffect();
    void Initialize();
    void Draw(ID3D12GraphicsCommandList* cmdList);
    ComPtr<ID3D12Resource> texBuff;
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //マルチパスレンダリング
    ComPtr<ID3D12Resource> depthBuff;
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
public:
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    static const float clearColor[4];
};
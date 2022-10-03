#pragma once
#include "WinApp.h"
#include <DirectXMath.h>

class FpsCamera final
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static void init(WinApp* winApp);

	//�X�V
	static void upDate(XMFLOAT3 move, float speed);

	//�Ǐ]����I�u�W�F�N�g�̈ʒu���L�^
	void SetPositon(XMFLOAT3 pos);

	static XMMATRIX View() { return view; }

	static XMMATRIX Projection() { return matProjection; }

private:
	static XMFLOAT3 positon;
	static XMFLOAT3 f0;
	static XMVECTOR v0;
	static XMFLOAT3 up;
	static XMMATRIX view;
	static XMMATRIX matProjection;//�ˉe�s��
};


﻿#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	//safe_delete(spriteBG);
	for (int i = 0; i < _countof(sprite); i++)
	{
		safe_delete(sprite[i]);
	}
	safe_delete(particleMan);
	safe_delete(objSkydome);
	safe_delete(objSphere);
	safe_delete(objGround);
	safe_delete(objFighter);
	safe_delete(modelSkydome);
	safe_delete(modelGround);
	safe_delete(modelFighter);
	safe_delete(light);
	safe_delete(camera);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	FbxObject3d::SetDevice(dxCommon->GetDevice());

	FbxObject3d::SetCamera(camera);

	FbxObject3d::CreateGraphicsPipeline();

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/texture.png")) {
		assert(0);
		return;
	}
	// テクスチャ読み込み
	if (!Sprite::LoadTexture(2, L"Resources/pointer.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	//spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	sprite[0] = Sprite::Create(2, { 0.0f,0.0f });
	sprite[0]->SetSize({ 16.0f,16.0f });
	sprite[0]->SetPosition({ WinApp::window_width / 2,WinApp::window_height / 2 });
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), camera);

	// テクスチャ2番に読み込み

	// モデル読み込み
	modelSkydome = ReadModel::CreateFromOBJ("skydome");
	modelGround = ReadModel::CreateFromOBJ("ground");
	modelFighter = ReadModel::CreateFromOBJ("chr_sword");
	modelFighter2 = ReadModel::CreateFromOBJ("chr_sword");
	modelSphere = ReadModel::CreateFromOBJ("sphere2", true);

	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	objGround = Object3d::Create(modelGround);
	objFighter = Object3d::Create(modelFighter);
	objFighter2 = Object3d::Create(modelFighter2);

	objFighter->SetPosition({ 0,0,-20 });
	objFighter2->SetPosition({ -2,0,-5 });
	objFighter2->SetRotation({ 0,180,0 });

	objSphere = Object3d::Create(modelSphere);
	objSphere->SetPosition({ +2,1,0 });

	audio->PlayWave("Resources/bgm.wav", 0.1f);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 0, 0 });
	camera->SetEye({ 0,0,0 });

	light = Light::Create();
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light);

	//モデル名を指定してファイル読み込み
	fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//3Dオブジェクト生成とモデルのセット
	fbxObject1 = new FbxObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(fbxModel1);
	fbxObject1->SetRotation({0,90,0});
}

void GameScene::Update()
{
	XMFLOAT3 playerPos = objFighter->GetPosition();
	// 移動後の座標を計算
	CharactorMove(playerPos);
	objFighter->SetPosition(playerPos);
	cameraPos = objFighter->GetPosition();

	camera->SetEye({ cameraPos.x, cameraPos.y , cameraPos.z });
	camera->SetTarget({ cameraPos.x , cameraPos.y, cameraPos.z + 20 });
	camera->Update();
	//CreateLight();

	fbxObject1->AnimationFlag = true;

	particleMan->Update();

	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objFighter2->Update();
	objSphere->Update();
	light->Update();
	fbxObject1->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	// ここに背景スプライトの描画処理を追加できる

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	Object3d::PreDraw(cmdList);
	objSkydome->Draw();
	// 3Dオブジェクトの描画
	objGround->Draw();
	objFighter->Draw();
	//objFighter2->Draw();
	//objSphere->Draw();
	Object3d::PostDraw();

	fbxObject1->Draw(cmdList);

	// パーティクルの描画
	particleMan->Draw(cmdList);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// ここに前景スプライトの描画処理を追加できる
	//spriteBG->Draw();
	// デバッグテキストの描画
	sprite[0]->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}

void GameScene::CreateLight()
{
	//光線方向初期値
	static XMVECTOR lightDir = { 0, 1, 5, 0 };

	if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }

	light->SetLightDir(lightDir);

	std::ostringstream debugstr;
	debugstr << "lightDirFactor("
		<< std::fixed << std::setprecision(2)
		<< lightDir.m128_f32[0] << ","
		<< lightDir.m128_f32[1] << ","
		<< lightDir.m128_f32[2] << ")";
	debugText.Print(debugstr.str(), 50, 50, 1.0f);
	debugstr.str("");
	debugstr.clear();

	const XMFLOAT3& cameraPos = camera->GetEye();
	debugstr << "cameraPos("
		<< std::fixed << std::setprecision(2)
		<< cameraPos.x << ","
		<< cameraPos.y << ","
		<< cameraPos.z << ")";
	debugText.Print(debugstr.str(), 50, 70, 1.0f);
}

void GameScene::CharactorMove(XMFLOAT3 pos)
{
	if (input->PushKey(DIK_W) && pos.z < 15.0f)
	{
		pos.z += 0.1f;
	}
	else if (input->PushKey(DIK_S) && pos.z > -15.0f)
	{
		pos.z -= 0.1f;
	}

	if (input->PushKey(DIK_D) && pos.x < 15.0f)
	{
		pos.x += 0.1f;
	}
	else if (input->PushKey(DIK_A) && pos.x > -15.0f)
	{
		pos.x -= 0.1f;
	}
}

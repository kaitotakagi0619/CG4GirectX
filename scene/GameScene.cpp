#include "GameScene.h"
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
	safe_delete(spriteMagazineUI);

	//オブジェクトのdelete
	safe_delete(objSkydome);
	for (int i = 0; i < _countof(objSphere); i++)
	{
		safe_delete(objSphere[i]);
	}
	safe_delete(objGround);
	safe_delete(objFighter);
	safe_delete(objFighter2);
	safe_delete(bossEnemy);
	safe_delete(objCity);

	//機能のdelete
	//safe_delete(dxCommon);
	//safe_delete(input);
	//safe_delete(audio);
	safe_delete(light);
	safe_delete(particleMan);
	safe_delete(camera);
	//モデルのdelete
	safe_delete(modelSkydome);
	safe_delete(modelGround);
	safe_delete(modelFighter);
	safe_delete(modelFighter2);
	safe_delete(modelSphere);
	safe_delete(modelCity);

	//fbxのdelete
	safe_delete(fbxModel1);
	safe_delete(fbxObject1);
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
	//camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

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
	if (!Sprite::LoadTexture(2, L"Resources/pointer.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(3, L"Resources/title.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(4, L"Resources/win.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	//spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	sprite[0] = Sprite::Create(2, { 0.0f,0.0f });
	sprite[1] = Sprite::Create(3, { 0.0f,0.0f });
	sprite[2] = Sprite::Create(4, { 0.0f,0.0f });
	sprite[0]->SetSize({ 16.0f,16.0f });
	sprite[0]->SetPosition({ (WinApp::window_width / 2) - 8,(WinApp::window_height / 2) - 8 });
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), camera);

	// テクスチャ2番に読み込み

	// モデル読み込み
	modelSkydome = ReadModel::CreateFromOBJ("skydome");
	modelGround = ReadModel::CreateFromOBJ("ground");
	modelFighter = ReadModel::CreateFromOBJ("chr_sword");
	modelFighter2 = ReadModel::CreateFromOBJ("chr_sword");
	modelSphere = ReadModel::CreateFromOBJ("sphere2", true);
	modelCity = ReadModel::CreateFromOBJ("city", true);
	modelcowgirl = ReadModel::CreateFromOBJ("cowgirl", true);

	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	objGround = Object3d::Create(modelGround);
	objFighter = Object3d::Create(modelFighter);
	objFighter2 = Object3d::Create(modelFighter2);
	objFighter3 = Object3d::Create(modelFighter2);
	objCity = Object3d::Create(modelCity);
	bossEnemy = Object3d::Create(modelcowgirl);

	objFighter->SetPosition({ 0,2,30 });
	objFighter2->SetPosition({ 0,12,30 });
	objFighter3->SetPosition({ 0,12,30 });
	bossEnemy->SetPosition({ 0,2, 40 });
	enemy_data.angleX = 0;
	enemy_data.angleY = 0;
	enemy_data.angleZ = 0;

	enemy_data.virangleX = 90;
	enemy_data.virangleY = 0;
	enemy_data.virangleZ = 90;
	objFighter2->SetRotation({ 0,180,0 });
	objFighter3->SetRotation({ 0,180,0 });
	bossEnemy->SetRotation({ 0,180,0 });
	objCity->SetPosition({ 0,0,20 });
	objCity->SetRotation({ 0,90,0 });
	objCity->SetScale({ 3,3,3 });

	for (int i = 0; i < _countof(objSphere); i++)
	{
		objSphere[i] = Object3d::Create(modelSphere);
		objSphere[i]->SetPosition({ +1000,-10,1000 });
		objSphere[i]->SetScale({ 0.2,0.2,0.2 });
	}

	audio->PlayWave("Resources/rock.wav", 0.1f);

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
	fbxObject1->SetRotation({ 0,90,0 });

	SceneNum = Title;
}

void GameScene::Update()
{

	//imgui準備
	CreateLight();
	XMFLOAT3 playerPos = objFighter->GetPosition();
	XMFLOAT3 bossPos = bossEnemy->GetPosition();
	XMFLOAT3 playerScale = objFighter->GetScale();
	XMFLOAT3 targetCameraPos = objFighter2->GetPosition();
	XMFLOAT3 virCameraPos = objFighter3->GetPosition();
	XMFLOAT3 centerPos = { 0, 2, 50 };
	for (int i = 0; i < _countof(objSphere); i++)
	{
		bullet[i].Pos = objSphere[i]->GetPosition();
		bullet[i].Size = objSphere[i]->GetScale();
	}
	if (SceneNum == Title)
	{
		if (input->TriggerKey(DIK_RETURN))
		{
			SceneNum = Game;
			CircularMotionUD(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleY, +1);
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleX, +1);
			CircularMotionUD(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleY, +1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleX, +1);
		}
	}

	if (SceneNum == Game)
	{
		if (timing < 60)
		{
			timing++;
		}
		else
		{
			timing = 0;
		}
		//移動用velocity計算
		plVelocity.x = targetCameraPos.x - playerPos.x;
		plVelocity.y = targetCameraPos.y - playerPos.y;
		plVelocity.z = targetCameraPos.z - playerPos.z;
		
		virVelocity.x = virCameraPos.x - playerPos.x;
		virVelocity.y = virCameraPos.y - playerPos.y;
		virVelocity.z = virCameraPos.z - playerPos.z;
		//タイミングよく移動すると加速
	/*	if ((input->TriggerKey(DIK_W) && timing > 55)
			|| (input->TriggerKey(DIK_W) && timing < 5))
		{
			playerPos.z += 2.5f;
			targetCameraPos.z += 2.5f;
		}
		if ((input->TriggerKey(DIK_S) && timing > 55)
			|| (input->TriggerKey(DIK_S) && timing < 5))
		{
			playerPos.z -= 2.5f;
			targetCameraPos.z -= 2.5f;
		}*/
		/*if ((input->TriggerKey(DIK_A) && timing > 55)
			|| (input->TriggerKey(DIK_A) && timing < 5))
		{
			playerPos.x -= 2.5f;
			targetCameraPos.x -= 2.5f;
		}
		if ((input->TriggerKey(DIK_D) && timing > 55)
			|| (input->TriggerKey(DIK_D) && timing < 5))
		{
			playerPos.x += 2.5f;
			targetCameraPos.x += 2.5f;
		}*/
		// 移動後の座標を計算
		if (input->PushKey(DIK_W))
		{
			playerPos.x +=			(plVelocity.x / 100);
			playerPos.z +=			(plVelocity.z / 100);
			targetCameraPos.x +=	(plVelocity.x / 100);
			targetCameraPos.z +=	(plVelocity.z / 100);
			virCameraPos.x +=		(plVelocity.x / 100);
			virCameraPos.z +=		(plVelocity.z / 100);
		}
		else if (input->PushKey(DIK_S))
		{
			playerPos.x -=			(plVelocity.x / 100);
			playerPos.z -=			(plVelocity.z / 100);
			targetCameraPos.x -=	(plVelocity.x / 100);
			targetCameraPos.z -=	(plVelocity.z / 100);
			virCameraPos.x -=		(plVelocity.x / 100);
			virCameraPos.z -=		(plVelocity.z / 100);
		}

		if (input->PushKey(DIK_D))
		{
			playerPos.x +=	 		(virVelocity.x / 100);
			playerPos.z +=			(virVelocity.z / 100);
			targetCameraPos.x +=	(virVelocity.x / 100);
			targetCameraPos.z +=	(virVelocity.z / 100);
			virCameraPos.x +=		(virVelocity.x / 100);
			virCameraPos.z +=		(virVelocity.z / 100);
		}
		else if (input->PushKey(DIK_A))
		{
			playerPos.x -=			(virVelocity.x / 100);
			playerPos.z -=			(virVelocity.z / 100);
			targetCameraPos.x -=	(virVelocity.x / 100);
			targetCameraPos.z -=	(virVelocity.z / 100);
			virCameraPos.x -=		(virVelocity.x / 100);
			virCameraPos.z -=		(virVelocity.z / 100);
		}


		if (input->TriggerKey(DIK_SPACE) && bullet[bulCount].bulShotFlag == false)
		{
			bullet[bulCount].bulFlag = true;
			bulCount++;
		}

		if (bulCount > 49)
		{
			bulCount = 0;
		}

		if (bullet[bulCount-1].bulFlag == true)
		{
			bullet[bulCount-1].Pos = playerPos;
			bullet[bulCount-1].bulShotFlag = true;
			bullet[bulCount-1].bulFlag = false;
		}

		for (int i = 0; i < _countof(objSphere); i++)
		{
			if (bullet[i].bulShotFlag == true)
			{
				bullet[i].Pos.x += plVelocity.x;
				bullet[i].Pos.y += plVelocity.y;
				bullet[i].Pos.z += plVelocity.z;
			}
			if (bullet[i].Pos.z > 70)
			{
				bullet[i].Pos = { +1000,-10,1000 };
				bullet[i].bulShotFlag = false;
			}
		}

		if (enemy_data.angleY < 90)
		{
			if (input->PushKey(DIK_UP))
			{
				CircularMotionUD(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleY, +1);
				CircularMotionUD(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleY, +1);
			}
		}
		if (enemy_data.angleY > -90)
		{
			if (input->PushKey(DIK_DOWN))
			{
				CircularMotionUD(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleY, -1);
				CircularMotionUD(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleY, -1);
			}
		}
		if (input->PushKey(DIK_LEFT))
		{
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleX, -1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleX, -1);
		}
		if (input->PushKey(DIK_RIGHT))
		{
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleX , +1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleX , +1);
		}

		// ジャンプ
		if (input->PushKey(DIK_RSHIFT) && isJump == false && isJustJump == false)
		{
			if(timing > 55 || timing < 5)
			{
				isJustJump = true;
				jCount = jCountMax;
			}
			else
			{
				isJump = true;
				jCount = jCountMin;
			}
		}
		if (isJump == true)
		{
			jCount -= 0.025;
			if (jCount > -jCountMin)
			{
				playerPos.y += jCount;
				targetCameraPos.y += jCount;
			}
			else
			{
				isJump = false;
			}
		}
		if (isJustJump == true)
		{
			jCount -= 0.025;
			if (jCount > -jCountMax)
			{
				playerPos.y += jCount;
				targetCameraPos.y += jCount;
			}
			else
			{
				isJustJump = false;
			}
		}


		objFighter->SetPosition(playerPos);
		objFighter2->SetPosition(targetCameraPos);
		objFighter3->SetPosition(virCameraPos);

		for (int i = 0; i < _countof(objSphere); i++)
		{
			objSphere[i]->SetPosition(bullet[i].Pos);
		}

		bool bossHit = (bossPos.x - playerScale.x < bullet[49].Pos.x + bullet[49].Size.x)
			&& (bossPos.x + playerScale.x > bullet[49].Pos.x - bullet[49].Size.x)
			&& (bossPos.z - playerScale.z < bullet[49].Pos.z + bullet[49].Size.z)
			&& (bossPos.z + playerScale.z > bullet[49].Pos.z - bullet[49].Size.z)
			&& (enemyAlive == true);
		{
			if (bossHit)
			{
				for (int i = 0; i < _countof(objSphere); i++)
				{
					objSphere[i]->SetPosition({ +1000,-10,1000 });
					bullet[i].Pos = objSphere[i]->GetPosition();
					bullet[i].Size = objSphere[i]->GetScale();
					SceneNum = Win;
				}
				
			}
		}

		if (enemyAlive == false)
		{
			enemyTimer++;
		}

		if (enemyTimer > 120)
		{
			enemyAlive = true;
			bulCount = 0;
			/*for (int i = 0; i < _countof(objSphere); i++)
			{
				bullet[i].bulFlag = false;
				bullet[i].bulShotFlag = false;
			}*/
			waveFlag = false;
			waveFlag2 = false;
			waveShotFlag = false;
			waveShotFlag2 = false;
			plBulFlag = false;
			plBulShotFlag = false;
			enemyVec = 0.1f;
			enemyTimer = 0;
		}
		// 移動後の座標を計算
		cameraPos = objFighter->GetPosition();

		camera->SetEye({ playerPos.x, playerPos.y , playerPos.z });
		camera->SetTarget({ targetCameraPos.x , targetCameraPos.y , targetCameraPos.z });
		camera->Update();

		fbxObject1->AnimationFlag = true;
	}

	else if (SceneNum == Win || SceneNum == Lose)
	{
		camera->SetEye({ 0,0,-50 });
		camera->SetTarget({ 0, 0, 0 });
		camera->Update();
		if (input->TriggerKey(DIK_RETURN))
		{
			SceneNum = Title;
			objFighter->SetPosition({ 0,1,30 });
			objFighter2->SetPosition({ 0,1,50 });
			objFighter2->SetRotation({ 0,180,0 });
			objFighter3->SetPosition({ 0,1,50 });
			objFighter3->SetRotation({ 0,180,0 });
			playerPos = objFighter->GetPosition();
			playerScale = objFighter->GetScale();
			targetCameraPos = objFighter2->GetPosition();
			virCameraPos = objFighter3->GetPosition();
			bulCount = 0;
			for (int i = 0; i < _countof(objSphere); i++)
			{
				bullet[i].bulFlag = false;
				bullet[i].bulShotFlag = false;
			}
			waveFlag = false;
			waveFlag2 = false;
			waveShotFlag = false;
			waveShotFlag2 = false;
			plBulFlag = false;
			plBulShotFlag = false;
			enemyAlive = true;
			enemyVec = 0.1f;
			for (int i = 0; i < _countof(objSphere); i++)
			{
				objSphere[i]->SetPosition({ +1000,-10,1000 });
				bullet[i].Pos = objSphere[i]->GetPosition();
				bullet[i].Size = objSphere[i]->GetScale();
			}
		}
	}

	particleMan->Update();

	objSkydome->Update();
	objGround->Update();
	bossEnemy->Update();
	objFighter->Update();
	objFighter2->Update();
	objFighter3->Update();
	objCity->Update();
	for (int i = 0; i < _countof(objSphere); i++)
	{
		objSphere[i]->Update();
	}
	light->Update();
	fbxObject1->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	/*ImGui::Begin("Rendering Test Menu");
	ImGui::SetWindowSize(ImVec2(400, 500), ImGuiCond_::ImGuiCond_FirstUseEver);
	ImGui::End();*/

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
	//objGround->Draw();
	objCity->Draw();
	//objFighter->Draw();
	if (enemyAlive == true)
	{
		//objFighter2->Draw();
		bossEnemy->Draw();
	}
	for (int i = 0; i < _countof(objSphere); i++)
	{
		objSphere[i]->Draw();
	}
	Object3d::PostDraw();

	//fbxObject1->Draw(cmdList);

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
	if (SceneNum == Title)
	{
		sprite[1]->Draw();
	}
	if (SceneNum == Win)
	{
		sprite[2]->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::Move()
{
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

	/*if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }*/

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

void GameScene::CircularMotionUD(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, int& angleZ, int& angleY, const int add)
{
	//angleZ += add;
	angleY += add;

	pos.z = (cosf(3.14 / 180.0f * angleZ) * r) + center_pos.z;//円運動の処理
	pos.y = (sinf(3.14 / 180.0f * angleY) * r) + center_pos.y;//円運動の処理
}

void GameScene::CircularMotionLR(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, int& angleZ, int& angleX, const int add)
{
	angleZ += add;
	angleX += add;

	pos.z = (cosf(3.14 / 180.0f * angleZ) * r) + center_pos.z;//円運動の処理
	pos.x = (sinf(3.14 / 180.0f * angleX) * r) + center_pos.x;//円運動の処理
}
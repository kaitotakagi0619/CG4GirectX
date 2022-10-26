#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "Audio.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	//safe_delete(spriteBG);
	//スプライトのdelete
	for (int i = 0; i < _countof(sprite); i++)
	{
		safe_delete(sprite[i]);
	}
	for (int i = 0; i < _countof(spriteNum); i++)
	{
		safe_delete(spriteNum[i]);
	}
	safe_delete(spriteMagazineUI);
	safe_delete(spritebossHP);
	safe_delete(spritebossHPFrame);
	safe_delete(reloadText);

	//オブジェクトのdelete
	safe_delete(objSkydome);
	for (int i = 0; i < _countof(objBul); i++)
	{
		safe_delete(objBul[i]);
	}
	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		safe_delete(objEnemyBul[i]);
	}
	safe_delete(objGround);
	safe_delete(objFighter);
	safe_delete(objFighter2);
	safe_delete(objFighter3);
	safe_delete(bossEnemy);
	safe_delete(objCity);

	//機能のdelete
	//safe_delete(dxCommon);
	//safe_delete(input);
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

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	Audio::GetInstance()->LoadWave("rock.wav");
	Audio::GetInstance()->LoadWave("SE/jump.wav");
	Audio::GetInstance()->LoadWave("SE/enter.wav");
	Audio::GetInstance()->LoadWave("SE/damage.wav");
	ShowCursor(FALSE);
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

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
	if (!Sprite::LoadTexture(0, L"Resources/Number0.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(1, L"Resources/Number1.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(2, L"Resources/Number2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(3, L"Resources/Number3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(4, L"Resources/Number4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(5, L"Resources/Number5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(6, L"Resources/Number6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(7, L"Resources/Number7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(8, L"Resources/Number8.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(9, L"Resources/Number9.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(11, L"Resources/bossHPber.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(12, L"Resources/reticle.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(13, L"Resources/title.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(14, L"Resources/win.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(15, L"Resources/timingUI.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(16, L"Resources/timingUILeft.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(17, L"Resources/timingUIRight.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(18, L"Resources/magazineUI.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(19, L"Resources/bossHPFrame.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(20, L"Resources/reloadText.png")) {
		assert(0);
		return;
	}

	// スプライト生成
	for (int i = 0; i < _countof(sprite); i++)
	{
		sprite[i] = Sprite::Create((12 + i), { 0.0f,0.0f });
	}
	spriteNum[0] = Sprite::Create(0, { 0.0f,0.0f });
	spriteNum[1] = Sprite::Create(1, { 0.0f,0.0f });
	spriteNum[2] = Sprite::Create(2, { 0.0f,0.0f });
	spriteNum[3] = Sprite::Create(3, { 0.0f,0.0f });
	spriteMagazineUI = Sprite::Create(18, { 0.0f,0.0f });
	spritebossHP = Sprite::Create(11, { 0.0f,0.0f });
	spritebossHPFrame = Sprite::Create(19, { 0.0f,0.0f });
	reloadText = Sprite::Create(20, { 0.0f,0.0f });

	//スプライトの初期変更
	sprite[0]->SetSize({ 64.0f,64.0f });
	sprite[0]->SetPosition({ spritePos.center.x - 32,spritePos.center.y - 32 });
	sprite[3]->SetSize({ 64.0f,64.0f });
	sprite[4]->SetSize({ 32.0f,64.0f });
	sprite[5]->SetSize({ 32.0f,64.0f });
	spriteNum[0]->SetSize({ 24,48 });
	spriteNum[1]->SetSize({ 24,48 });
	spriteNum[2]->SetSize({ 24,48 });
	spriteNum[3]->SetSize({ 24,48 });
	spriteNum[0]->SetPosition({ WinApp::window_width - 174,WinApp::window_height - 112 });
	spriteNum[1]->SetPosition({ WinApp::window_width - 150,WinApp::window_height - 112 });
	spriteNum[2]->SetPosition({ WinApp::window_width - 104,WinApp::window_height - 64 });
	spriteNum[3]->SetPosition({ WinApp::window_width - 80,WinApp::window_height - 64 });
	sprite[3]->SetPosition({ spritePos.center.x - 32,WinApp::window_height - 160 });
	sprite[4]->SetPosition({ spritePos.center.x - 272,WinApp::window_height - 160 });
	sprite[5]->SetPosition({ spritePos.center.x + 208,WinApp::window_height - 160 });
	spriteMagazineUI->SetSize({ 256.0f,128.0f });
	spriteMagazineUI->SetPosition({ WinApp::window_width - 256,WinApp::window_height - 128 });
	reloadText->SetPosition({ WinApp::window_width - 124,WinApp::window_height - 96 });

	spritebossHP->SetPosition({ 303 , 47 });
	spritebossHP->SetSize({ 694 , 20 });

	spritebossHPFrame->SetPosition({ 300 , 00 });
	spritebossHPFrame->SetSize({ 700 , 70 });



	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), camera);

	// テクスチャ2番に読み込み

	// モデル読み込み
	modelSkydome =	ReadModel::CreateFromOBJ("skydome");
	modelGround =	ReadModel::CreateFromOBJ("ground");
	modelFighter =	ReadModel::CreateFromOBJ("chr_sword");
	modelFighter2 = ReadModel::CreateFromOBJ("chr_sword");
	modelSphere =	ReadModel::CreateFromOBJ("sphere2", true);
	modelCity =		ReadModel::CreateFromOBJ("city", true);
	modelcowgirl =	ReadModel::CreateFromOBJ("cowgirl", true);

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


	//カメラデータ
	camera_data.angleX = 0;
	camera_data.angleY = 0;
	camera_data.angleZ = 0;

	//横にいるので(90,0,90にすること)
	camera_data.virangleX = 90;
	camera_data.virangleY = 0;
	camera_data.virangleZ = 90;

	firstBossHP = 20;

	objFighter2->SetRotation({ 0,180,0 });
	objFighter3->SetRotation({ 0,180,0 });
	bossEnemy->SetRotation({ 0,180,0 });
	objCity->SetPosition({ 0,0,20 });
	objCity->SetRotation({ 0,90,0 });
	objCity->SetScale({ 3,3,3 });

	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i] = Object3d::Create(modelSphere);
		objBul[i]->SetPosition({ +1000,-10,1000 });
		objBul[i]->SetScale({ 0.2,0.2,0.2 });
	}

	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		objEnemyBul[i] = Object3d::Create(modelSphere);
		objEnemyBul[i]->SetPosition({ +1000,-10,1000 });
		objEnemyBul[i]->SetScale({ 0.5,0.5,0.5 });
	}

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
	SetCursorPos(640,400);
	CreateLight();
	//各種変数関係
	Input::MouseMove mouseMove = input->GetMouseMove();
	mousePos = { (float)mouseMove.lX / 50,(float)mouseMove.lY / 50};
	playerPos = objFighter->GetPosition();
	bossPos = bossEnemy->GetPosition();
	playerScale = objFighter->GetScale();
	targetCameraPos = objFighter2->GetPosition();
	virCameraPos = objFighter3->GetPosition();
	centerPos = { 0, 2, 50 };


	for (int i = 0; i < _countof(objBul); i++)
	{
		bullet[i].Pos = objBul[i]->GetPosition();
		bullet[i].Size = objBul[i]->GetScale();
	}
	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		eBullet[i].Pos = objEnemyBul[i]->GetPosition();
		eBullet[i].Size = objEnemyBul[i]->GetScale();
	}
	if (SceneNum == Title)
	{
		if (input->TriggerKey(DIK_RETURN))
		{
			SceneNum = Game;
			CircularMotionUD(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleY, +1);
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleX, +1);
			CircularMotionUD(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleY, +1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleX, +1);
		}
	}

	if (SceneNum == Game)
	{
		Audio::GetInstance()->PlayWave("SE/enter.wav", 0.03, false);
		Audio::GetInstance()->PlayWave("rock.wav", 0.03, true);
		if (timing > 0)
		{
			timing--;
		}
		else
		{
			timing = 60;
		}

		sprite[4]->SetPosition({ (WinApp::window_width / 2) - (4 * (float)timing + 32),WinApp::window_height - 160});
		sprite[5]->SetPosition({ (WinApp::window_width / 2) + (4 * (float)timing),WinApp::window_height - 160});

		//sprite[0]->SetPosition({ mousePos.x,mousePos.y });

		//移動用velocity計算
		if (input->PushKey(DIK_LSHIFT))
		{
			plVelocity.x = (targetCameraPos.x - playerPos.x) * 2;
			plVelocity.y = (targetCameraPos.y - playerPos.y) * 2;
			plVelocity.z = (targetCameraPos.z - playerPos.z) * 2;

			virVelocity.x = (virCameraPos.x - playerPos.x) * 2;
			virVelocity.y = (virCameraPos.y - playerPos.y) * 2;
			virVelocity.z = (virCameraPos.z - playerPos.z) * 2;
		}
		else
		{
			plVelocity.x = targetCameraPos.x - playerPos.x;
			plVelocity.y = targetCameraPos.y - playerPos.y;
			plVelocity.z = targetCameraPos.z - playerPos.z;

			virVelocity.x = virCameraPos.x - playerPos.x;
			virVelocity.y = virCameraPos.y - playerPos.y;
			virVelocity.z = virCameraPos.z - playerPos.z;
		}

		// 移動後の座標を計算
		//タイミングよく移動すると加速
		// -----------------------------------------//
		if ((input->TriggerKey(DIK_W) && timing > 55)
			|| (input->TriggerKey(DIK_W) && timing < 5))
		{
			playerPos.x += (plVelocity.x / 10);
			playerPos.z += (plVelocity.z / 10);
			targetCameraPos.x += (plVelocity.x / 10);
			targetCameraPos.z += (plVelocity.z / 10);
			virCameraPos.x += (plVelocity.x / 10);
			virCameraPos.z += (plVelocity.z / 10);
		}
		else if (input->PushKey(DIK_W))
		{
			playerPos.x += (plVelocity.x / 100);
			playerPos.z += (plVelocity.z / 100);
			targetCameraPos.x += (plVelocity.x / 100);
			targetCameraPos.z += (plVelocity.z / 100);
			virCameraPos.x += (plVelocity.x / 100);
			virCameraPos.z += (plVelocity.z / 100);
		}


		if ((input->TriggerKey(DIK_S) && timing > 55)
			|| (input->TriggerKey(DIK_S) && timing < 5))
		{
			playerPos.x -= (plVelocity.x / 10);
			playerPos.z -= (plVelocity.z / 10);
			targetCameraPos.x -= (plVelocity.x / 10);
			targetCameraPos.z -= (plVelocity.z / 10);
			virCameraPos.x -= (plVelocity.x / 10);
			virCameraPos.z -= (plVelocity.z / 10);
		}
		else if (input->PushKey(DIK_S))
		{
			playerPos.x -= (plVelocity.x / 100);
			playerPos.z -= (plVelocity.z / 100);
			targetCameraPos.x -= (plVelocity.x / 100);
			targetCameraPos.z -= (plVelocity.z / 100);
			virCameraPos.x -= (plVelocity.x / 100);
			virCameraPos.z -= (plVelocity.z / 100);
		}


		if ((input->TriggerKey(DIK_A) && timing > 55)
			|| (input->TriggerKey(DIK_A) && timing < 5))
		{
			playerPos.x -= (virVelocity.x / 10);
			playerPos.z -= (virVelocity.z / 10);
			targetCameraPos.x -= (virVelocity.x / 10);
			targetCameraPos.z -= (virVelocity.z / 10);
			virCameraPos.x -= (virVelocity.x / 10);
			virCameraPos.z -= (virVelocity.z / 10);
		}
		else if (input->PushKey(DIK_A))
		{
			playerPos.x -= (virVelocity.x / 100);
			playerPos.z -= (virVelocity.z / 100);
			targetCameraPos.x -= (virVelocity.x / 100);
			targetCameraPos.z -= (virVelocity.z / 100);
			virCameraPos.x -= (virVelocity.x / 100);
			virCameraPos.z -= (virVelocity.z / 100);
		}


		if ((input->TriggerKey(DIK_D) && timing > 55)
			|| (input->TriggerKey(DIK_D) && timing < 5))
		{
			playerPos.x += (virVelocity.x / 10);
			playerPos.z += (virVelocity.z / 10);
			targetCameraPos.x += (virVelocity.x / 10);
			targetCameraPos.z += (virVelocity.z / 10);
			virCameraPos.x += (virVelocity.x / 10);
			virCameraPos.z += (virVelocity.z / 10);
		}
		else if (input->PushKey(DIK_D))
		{
			playerPos.x += (virVelocity.x / 100);
			playerPos.z += (virVelocity.z / 100);
			targetCameraPos.x += (virVelocity.x / 100);
			targetCameraPos.z += (virVelocity.z / 100);
			virCameraPos.x += (virVelocity.x / 100);
			virCameraPos.z += (virVelocity.z / 100);
		}
		// -----------------------------------------//

		//弾を撃つ
		// -----------------------------------------//
		if (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount < 50)
		{
			bullet[bulCount].bulFlag = true;
			bulCount++;
		}

		lastBul = 50 - bulCount;
		spriteNum[0]->ChangeTex(lastBul / 10);
		spriteNum[1]->ChangeTex(lastBul % 10);
		spriteNum[2]->ChangeTex(maxMagazine / 10);
		spriteNum[3]->ChangeTex(maxMagazine % 10);

		//リロード
		if ((input->TriggerKey(DIK_R) && timing > 55)
			|| (input->TriggerKey(DIK_R) && timing < 5))
		{
			reloadCount = 30;
			justTiming = true;
			isReload = true;
		}
		else if (input->TriggerKey(DIK_R))
		{
			reloadCount = 30;
			maxMagazine = 20;
			isReload = true;
		}

		if (reloadCount > 0 && isReload == true)
		{
			reloadCount--;
		}

		if (reloadCount == 0 && isReload == true && justTiming == true)
		{
			bulCount = 20;
			maxMagazine = 30;
			isReload = false;
			justTiming = false;
		}
		else if (reloadCount == 0 && isReload == true)
		{
			bulCount = 30;
			isReload = false;
		}

		//弾を撃つ

		if (bullet[bulCount - 1].bulFlag == true)
		{
			bullet[bulCount - 1].Pos = playerPos;
			bullet[bulCount - 1].bulShotFlag = true;
			bullet[bulCount - 1].bulFlag = false;
		}

		for (int i = 0; i < _countof(objBul); i++)
		{
			if (bullet[i].bulShotFlag == true)
			{
				bullet[i].Pos.x += (plVelocity.x / 2);
				bullet[i].Pos.y += (plVelocity.y / 2);
				bullet[i].Pos.z += (plVelocity.z / 2);
			}
			if ((bullet[i].Pos.z > 400) || (bullet[i].Pos.z < -400)
				|| (bullet[i].Pos.x > 400)|| (bullet[i].Pos.x < -400))
			{
				bullet[i].Pos = { +1000,-10,1000 };
				bullet[i].bulShotFlag = false;
			}
		}

		if (camera_data.angleY < 90 && mousePos.y < 0 || camera_data.angleY > -90 && mousePos.y > 0)
		{
			CircularMotionUD(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleY, -mousePos.y);
			CircularMotionUD(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleY, -mousePos.y);
		}
		if (mousePos.x != 0)
		{
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleX, mousePos.x);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleX, mousePos.x);
		}
		/*if (input->PushKey(DIK_UP))
		{
			CircularMotionUD(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleY, +1);
			CircularMotionUD(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleY, +1);
		}*/
		/*if (input->PushKey(DIK_DOWN))
		{
			CircularMotionUD(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleY, -1);
			CircularMotionUD(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleY, -1);
		}*/
		/*if (input->PushKey(DIK_RIGHT))
		{
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleX, +1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleX, +1);
		}*/
		/*if (input->PushKey(DIK_LEFT))
		{
			CircularMotionLR(targetCameraPos, playerPos, 10.00f, enemy_data.angleZ, enemy_data.angleX, -1);
			CircularMotionLR(virCameraPos, playerPos, 10.00f, enemy_data.virangleZ, enemy_data.virangleX, -1);
		}*/

		// ジャンプ
		if (input->TriggerKey(DIK_SPACE) && isJump == false && isJustJump == false)
		{
			if (timing > 55 || timing < 5)
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
			Audio::GetInstance()->PlayWave("SE/jump.wav", 0.03, false);
			jCount -= 0.025;
			if (jCount > -jCountMin)
			{
				playerPos.y += jCount;
				targetCameraPos.y += jCount;
			}
			else
			{
				isJump = false;
				Audio::GetInstance()->SoundStop("SE/jump.wav");
			}
		}
		if (isJustJump == true)
		{
			Audio::GetInstance()->PlayWave("SE/jump.wav", 0.03, false);
			jCount -= 0.025;
			if (jCount > -jCountMax)
			{
				playerPos.y += jCount;
				targetCameraPos.y += jCount;
			}
			else
			{
				isJustJump = false;
				Audio::GetInstance()->SoundStop("SE/jump.wav");
			}
		}


		objFighter->SetPosition(playerPos);
		objFighter2->SetPosition(targetCameraPos);
		objFighter3->SetPosition(virCameraPos);

		for (int i = 0; i < _countof(objBul); i++)
		{
			objBul[i]->SetPosition(bullet[i].Pos);
		}

		for (int i = 0; i < _countof(objBul); i++)
		{
			bool bossHit = (bossPos.x - playerScale.x < bullet[i].Pos.x + bullet[i].Size.x)
				&& (bossPos.x + playerScale.x > bullet[i].Pos.x - bullet[i].Size.x)
				&& (bossPos.z - playerScale.z < bullet[i].Pos.z + bullet[i].Size.z)
				&& (bossPos.z + playerScale.z > bullet[i].Pos.z - bullet[i].Size.z)
				&& (enemyAlive == true);
			{
				if (bossHit)
				{
					firstBossHP--;
					objBul[i]->SetPosition({ +1000,-10,1000 });
					bullet[i].Pos = objBul[i]->GetPosition();
					bullet[i].Size = objBul[i]->GetScale();
					//SceneNum = Win;
					//enemyAlive = false;
				}
			}
		}

		spritebossHP->SetSize({ 34.7f * (float)firstBossHP , 20});

		if (firstBossHP <= 0)
		{
			enemyAlive = false;
		}

		if (enemyAlive == false)
		{
			enemyTimer++;
		}

		if (enemyTimer > 120)
		{
			enemyAlive = true;
			firstBossHP = 20;
			enemySinpleAttack = false;
			enemyTripleAttack = false;
			enemyHomingAttack = false;
			/*enemyAttackCounter = 0;*/
			enemyTimer = 0;
		}

		//敵の行動
		if (enemyAlive == true)
		{
			enemyAttackCounter++;
			if (enemyMove < 320 && isPlus)
			{
				enemyMove++;
			}
			if (enemyMove >= 320 && isPlus)
			{
				enemyMove = 0;
			}
			if (enemyMove < 40)
			{
				bossPos.x += 0.1;
			}

			if (enemyMove > 40 && enemyMove < 80)
			{
				bossPos.x -= 0.1;
				bossPos.z += 0.1;
			}
			if (enemyMove > 80 && enemyMove < 120)
			{
				bossPos.x -= 0.1;
				bossPos.z -= 0.1;
			}
			if (enemyMove > 120 && enemyMove < 140)
			{
				bossPos.x += 0.1;
				bossPos.z -= 0.1;
			}if (enemyMove > 140 && enemyMove < 160)
			{
				bossPos.x += 0.1;
				bossPos.z += 0.1;
			}
			if (enemyMove > 160 && enemyMove < 180)
			{
				bossPos.x += 0.1;
				bossPos.z -= 0.1;
			}
			if (enemyMove > 180 && enemyMove < 200)
			{
				bossPos.x += 0.1;
				bossPos.z += 0.1;
			}
			if (enemyMove > 200 && enemyMove < 240)
			{
				bossPos.x -= 0.1;
				bossPos.z += 0.1;
			}
			if (enemyMove > 240 && enemyMove < 280)
			{
				bossPos.x -= 0.1;
				bossPos.z -= 0.1;
			}
			if (enemyMove > 280 && enemyMove < 320)
			{
				bossPos.x += 0.1;
			}
		}


		if (enemyAttackCounter >= 59)
		{
			selectAttack = rand() % 100;
			enemyAttackCounter = 0;
		}

		if (selectAttack < 50 && selectAttack != 0)
		{
			enemySinpleAttack = true;
			enemyAttackCounter = 0;
			selectAttack = 0;
		}

		if (enemySinpleAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			eBullet[enemyBulCount].bulFlag = true;
			enemyBulCount++;
			enemySinpleAttack = false;
		}

		if (eBullet[enemyBulCount - 1].bulFlag == true)
		{
			eBullet[enemyBulCount - 1].Pos = bossPos;
			eBullet[enemyBulCount - 1].bulShotFlag = true;
			eBullet[enemyBulCount - 1].bulFlag = false;
		}

		if (enemyTripleAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			eBullet[enemyBulCount].bulFlag = true;
			eBullet[enemyBulCount + 1].bulFlag = true;
			eBullet[enemyBulCount + 2].bulFlag = true;
			enemyBulCount += 3;
			enemyTripleAttack = false;
		}

		if (eBullet[enemyBulCount - 1].bulFlag == true)
		{
			eBullet[enemyBulCount - 1].Pos = bossPos;
			eBullet[enemyBulCount - 1].bulShotFlag = true;
			eBullet[enemyBulCount - 1].bulFlag = false;
			eBullet[enemyBulCount].Pos = bossPos;
			eBullet[enemyBulCount].bulShotFlag = true;
			eBullet[enemyBulCount].bulFlag = false;
			eBullet[enemyBulCount + 1].Pos = bossPos;
			eBullet[enemyBulCount + 1].bulShotFlag = true;
			eBullet[enemyBulCount + 1].bulFlag = false;
		}

		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			if (eBullet[i].bulShotFlag == true)
			{
				eBullet[i].Pos.z += -0.2;
			}
			if ((eBullet[i].Pos.z > 400) || (eBullet[i].Pos.z < -400)
				|| (eBullet[i].Pos.x > 400) || (eBullet[i].Pos.x < -400))
			{
				eBullet[i].Pos = { +1000,-10,1000 };
				eBullet[i].bulShotFlag = false;
			}
		}

		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			bool playerHit = (playerPos.x - playerScale.x < eBullet[i].Pos.x + eBullet[i].Size.x)
				&& (playerPos.x + playerScale.x > eBullet[i].Pos.x - eBullet[i].Size.x)
				&& (playerPos.z - playerScale.z < eBullet[i].Pos.z + eBullet[i].Size.z)
				&& (playerPos.z + playerScale.z > eBullet[i].Pos.z - eBullet[i].Size.z)
				&& (isAlive == true);
			{
				if (playerHit)
				{
					hitTimer = 20;
					playerPos.z -= 2;
					objEnemyBul[i]->SetPosition({ +1000,-10,1000 });
					eBullet[i].Pos = objEnemyBul[i]->GetPosition();
					eBullet[i].Size = objEnemyBul[i]->GetScale();
					//SceneNum = Win;
					//enemyAlive = false;
				}
			}
		}
		if (hitTimer > 0)
		{
			hitTimer--;
			Audio::GetInstance()->PlayWave("SE/damage.wav", 0.03, false);
		}
		else
		{
			Audio::GetInstance()->SoundStop("SE/damage.wav");
		}

		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			objEnemyBul[i]->SetPosition(eBullet[i].Pos);
		}
		bossEnemy->SetPosition(bossPos);

		// 移動後の座標を計算
		cameraPos = objFighter->GetPosition();

		camera->SetEye({ playerPos.x, playerPos.y , playerPos.z });
		camera->SetTarget({ targetCameraPos.x , targetCameraPos.y , targetCameraPos.z });
		camera->Update();

		fbxObject1->AnimationFlag = true;
	}

	/*else if (SceneNum == Win || SceneNum == Lose)
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
			bulCount = 30;
			for (int i = 0; i < _countof(objBul); i++)
			{
				bullet[i].bulFlag = false;
				bullet[i].bulShotFlag = false;
			}
			enemyAlive = true;
			for (int i = 0; i < _countof(objBul); i++)
			{
				objBul[i]->SetPosition({ +1000,-10,1000 });
				bullet[i].Pos = objBul[i]->GetPosition();
				bullet[i].Size = objBul[i]->GetScale();
			}
			for (int i = 0; i < _countof(objEnemyBul); i++)
			{
				eBullet[i].bulFlag = false;
				eBullet[i].bulShotFlag = false;
			}
			for (int i = 0; i < _countof(objEnemyBul); i++)
			{
				objEnemyBul[i]->SetPosition({ +1000,-10,1000 });
				eBullet[i].Pos = objEnemyBul[i]->GetPosition();
				eBullet[i].Size = objEnemyBul[i]->GetScale();
			}
		}
	}*/

	particleMan->Update();

	objSkydome->Update();
	objGround->Update();
	bossEnemy->Update();
	objFighter->Update();
	objFighter2->Update();
	objFighter3->Update();
	objCity->Update();
	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i]->Update();
	}
	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		objEnemyBul[i]->Update();
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
	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i]->Draw();
	}
	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		objEnemyBul[i]->Draw();
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
	if (SceneNum == Game)
	{
		sprite[3]->Draw();
		sprite[4]->Draw();
		sprite[5]->Draw();
		spriteMagazineUI->Draw();
		spriteNum[0]->Draw();
		spriteNum[1]->Draw();
		spriteNum[2]->Draw();
		spriteNum[3]->Draw();
		if (enemyAlive == 1)
		{
			spritebossHPFrame->Draw();
			spritebossHP->Draw();
		}
		if (bulCount == 50)
		{
			reloadText->Draw();
		}
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

void GameScene::CircularMotionUD(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleY, const float add)
{
	//angleZ += add;
	angleY += add;

	pos.z = (cosf(3.14 / 180.0f * angleZ) * r) + center_pos.z;//円運動の処理
	pos.y = (sinf(3.14 / 180.0f * angleY) * r) + center_pos.y;//円運動の処理
}

void GameScene::CircularMotionLR(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleX, const float add)
{
	angleZ += add;
	angleX += add;

	pos.z = (cosf(3.14 / 180.0f * angleZ) * r) + center_pos.z;//円運動の処理
	pos.x = (sinf(3.14 / 180.0f * angleX) * r) + center_pos.x;//円運動の処理
}
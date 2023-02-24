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
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		safe_delete(spriteLife[i]);
	}
	safe_delete(spriteMagazineUI);
	safe_delete(spritebossHP);
	safe_delete(spritebossHPFrame);
	safe_delete(reloadText);
	safe_delete(diedText);
	safe_delete(brinkEffect);

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
	for (int i = 0; i < _countof(particleObject); i++)
	{
		safe_delete(particleObject[i]);
	}
	for (int i = 0; i < _countof(redParticleObject); i++)
	{
		safe_delete(redParticleObject[i]);
	}
	for (int i = 0; i < map_max_x; i++)
	{
		for (int j = 0; j < map_max_y; j++)
		{
			safe_delete(objBlock[i][j]);
		}
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
	safe_delete(modelBox);
	safe_delete(modelFire);
	safe_delete(modelRed);

	//fbxのdelete
	safe_delete(fbxModel1);
	safe_delete(fbxObject1);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	Audio::GetInstance()->LoadWave("BGM/bgm.wav");
	Audio::GetInstance()->LoadWave("SE/jump.wav");
	Audio::GetInstance()->LoadWave("SE/enter.wav");
	Audio::GetInstance()->LoadWave("SE/damage.wav");
	Audio::GetInstance()->LoadWave("SE/swing.wav");
	Audio::GetInstance()->LoadWave("SE/reload.wav");
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
	if (!Sprite::LoadTexture(21, L"Resources/life.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(22, L"Resources/youdied.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(23, L"Resources/brink.png")) {
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
	diedText = Sprite::Create(22, { 0.0f,0.0f });
	brinkEffect = Sprite::Create(23, { 0.0f,0.0f });
	diedText->SetPosition({ WinApp::window_width / 2 - 254,WinApp::window_height / 2 - 38 });
	diedText->SetColor(color);
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i] = Sprite::Create(21, { 0.0f,0.0f });
	}
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i]->SetSize({ 64,32 });
	}
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i]->SetPosition({ 100.0f + (i * 60),600.0f });
	}

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
	reloadText->SetPosition({ WinApp::window_width / 2 - 80,WinApp::window_height / 2 + 80 });

	spritebossHP->SetPosition({ 303 , 47 });
	spritebossHP->SetSize({ 694 , 20 });

	spritebossHPFrame->SetPosition({ 300 , 00 });
	spritebossHPFrame->SetSize({ 700 , 70 });



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
	modelBox = ReadModel::CreateFromOBJ("block", true);
	modelFire = ReadModel::CreateFromOBJ("fire", true);
	modelRed = ReadModel::CreateFromOBJ("red", true);

	Mapchip::CsvToVector(map, "Resources/csv/bigmap.csv");//mapNum=0

	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	objGround = Object3d::Create(modelGround);
	objFighter = Object3d::Create(modelFighter);
	objFighter2 = Object3d::Create(modelFighter2);
	objFighter3 = Object3d::Create(modelFighter2);
	objCity = Object3d::Create(modelCity);
	bossEnemy = Object3d::Create(modelcowgirl);

	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x] = Object3d::Create(modelBox);
			objBlock[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objBlock[y][x]->SetPosition({ 1000.0f,1000.0f,0.0f });
		}
	}

	for (int i = 0; i < _countof(particleObject); i++)
	{
		particleObject[i] = Object3d::Create(modelFire);
		particleObject[i]->SetScale({ 0.2f,0.2f,0.2f });
		particleObject[i]->SetPosition({ 1000.0f,1000.0f,0.0f });
	}

	for (int i = 0; i < _countof(redParticleObject); i++)
	{
		redParticleObject[i] = Object3d::Create(modelRed);
		redParticleObject[i]->SetScale({ 0.05f,0.05f,0.05f });
		redParticleObject[i]->SetPosition({ 1000.0f,1000.0f,0.0f });
	}

	//プレイヤー、敵、カメラの初期セット
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
	SetCursorPos(640, 400);
	CreateLight();
	//各種変数関係
	MapCreate(0);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Update();
		}
	}
	Input::MouseMove mouseMove = input->GetMouseMove();
	mousePos = { (float)mouseMove.lX / 50,(float)mouseMove.lY / 50 };
	playerPos = objFighter->GetPosition();
	bossPos = bossEnemy->GetPosition();
	playerScale = objFighter->GetScale();
	targetCameraPos = objFighter2->GetPosition();
	virCameraPos = objFighter3->GetPosition();
	centerPos = { 0, 2, 50 };

	p_x_radius = objFighter->GetScale().x;
	p_z_radius = objFighter->GetScale().z;

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
	//タイトルシーン
	if (SceneNum == Title)
	{
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

		objFighter2->SetRotation({ 0,180,0 });
		objFighter3->SetRotation({ 0,180,0 });
		bossEnemy->SetRotation({ 0,180,0 });

		for (int i = 0; i < _countof(objBul); i++)
		{
			objBul[i]->SetPosition({ +1000,-10,1000 });
			objBul[i]->SetScale({ 0.2,0.2,0.2 });
		}

		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			objEnemyBul[i]->SetPosition({ +1000,-10,1000 });
			objEnemyBul[i]->SetScale({ 0.5,0.5,0.5 });
		}
		mousePos = { (float)mouseMove.lX / 50,(float)mouseMove.lY / 50 };
		playerPos = objFighter->GetPosition();
		bossPos = bossEnemy->GetPosition();
		playerScale = objFighter->GetScale();
		targetCameraPos = objFighter2->GetPosition();
		virCameraPos = objFighter3->GetPosition();
		centerPos = { 0, 2, 50 };
		bulCount = 30;
		enemyBulCount = 1;
		plVelocity = { 0,0,0 };
		virVelocity = { 0,0,0 };
		bossAlive = true;
		enemyTimer = 0;
		timing = 75;
		isJust = false;
		isJump = false;
		isJustJump = false;
		isAlive = true;
		hitTimer = 0;
		jCount = 0.6;
		isHit = false;
		centerPos = { 0, 2, 50 };
		color = { 1,1,1,0 };
		justTiming = false;
		isJustTiming = false;
		lastBul = 0;
		reloadCount = 0;
		isReload = false;
		maxMagazine = 20;
		enemyAttackCounter = 0;
		isParticle = false;
		setParticle = false;
		partTimer = 0;
		attackAnimation = false;
		animeCount = 0;
		fiveAttack = false;
		fiveAttack2 = false;
		viewMatrix = camera->GetMatrix();
		justCount = 0;
		bossVelocity = { 0,0,0 };

		clearTimer = 0;
		randUIX = 0;
		randUIY = 0;

		selectAttack = 0;
		enemySinpleAttack = false;
		enemyTripleAttack = false;
		enemyBirdAttack = false;
		enemyStarAttack = false;
		enemyIsAttack = false;

		enemyMove = 0;
		isPlus = true;

		firstBossHP = 20;
		playerHP = 4;
		skyBul = 0;


		if (input->TriggerKey(DIK_RETURN))
		{
			isEase = true;
			Audio::GetInstance()->PlayWave("SE/enter.wav", 0.3, false);
		}
		if (isEase == true)
		{
			timeRate = nowCount / maxTime;

			titleEye.y = static_cast<float>(Ease::easeIn(titleFirstEyeY, playerPos.y, timeRate));
			titleEye.z = static_cast<float>(Ease::easeIn(titleFirstEyeZ, playerPos.z, timeRate));

			//イージングのカウント
			nowCount++;

			//カウントダウンがマックスならbattleに移る
			if (nowCount > maxTime) {
				SceneNum = Game;
				CircularMotionUD(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleY, +1);
				CircularMotionLR(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleX, +1);
				CircularMotionUD(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleY, +1);
				CircularMotionLR(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleX, +1);
				nowCount = 0.0f;
				timeRate = 0.0f;

				titleEye = { 0,20,-30 };
				titleTarget = { 0,2, 40 };
				isEase = false;
			}
		}
		camera->SetEye(titleEye);
		camera->SetTarget(titleTarget);
		camera->Update();
	}

	//ゲームシーン
	if (SceneNum == Game)
	{
		oldPlayerPos = playerPos;
		oldTargetCameraPos = targetCameraPos;
		oldVirCameraPos = virCameraPos;
		oldBossAlive = bossAlive;
		Audio::GetInstance()->SoundStop("SE/enter.wav");
		Audio::GetInstance()->PlayWave("BGM/bgm.wav", 0.1, true);
		if (timing > 1)
		{
			timing--;
		}
		else
		{
			timing = 60;
		}

		if (timing > 55 || timing < 5)
		{
			isJustTiming = true;
		}
		else
		{
			isJustTiming = false;
		}

		sprite[4]->SetPosition({ (WinApp::window_width / 2) - (4 * (float)timing + 32),WinApp::window_height - 160 });
		sprite[5]->SetPosition({ (WinApp::window_width / 2) + (4 * (float)timing),WinApp::window_height - 160 });

		//タイミングがジャストだった時にUIを揺らす処理
		if (isJust)
		{
			randUIX = 30;
			randUIY = 30;
			spritebossHP->SetPosition({ 303 , 47 - (float)randUIY });
			spritebossHPFrame->SetPosition({ 300 , 0 - (float)randUIY });
			spriteNum[0]->SetPosition({ WinApp::window_width - 174 + (float)randUIX,WinApp::window_height - 112 + (float)randUIY });
			spriteNum[1]->SetPosition({ WinApp::window_width - 150 + (float)randUIX,WinApp::window_height - 112 + (float)randUIY });
			spriteNum[2]->SetPosition({ WinApp::window_width - 104 + (float)randUIX,WinApp::window_height - 64 + (float)randUIY });
			spriteNum[3]->SetPosition({ WinApp::window_width - 80 + (float)randUIX,WinApp::window_height - 64 + (float)randUIY });
			spriteMagazineUI->SetPosition({ WinApp::window_width - 256 + (float)randUIX,WinApp::window_height - 128 + (float)randUIY });
			for (int i = 0; i < _countof(spriteLife); i++)
			{
				spriteLife[i]->SetPosition({ 100.0f + (i * 60) - (float)randUIX ,600.0f + (float)randUIY });
			}
			//視野角の変更
			viewMatrix = 55;
			justCount++;
			if (justCount > 10)
			{
				isJust = false;
				viewMatrix = 60;
			}
			camera->SetMatrix(viewMatrix);
		}
		//そうじゃなかったときに戻す処理
		else
		{
			spritebossHP->SetPosition({ 303 , 47 });
			spritebossHPFrame->SetPosition({ 300 , 0 });
			spriteNum[0]->SetPosition({ WinApp::window_width - 174,WinApp::window_height - 112 });
			spriteNum[1]->SetPosition({ WinApp::window_width - 150,WinApp::window_height - 112 });
			spriteNum[2]->SetPosition({ WinApp::window_width - 104,WinApp::window_height - 64 });
			spriteNum[3]->SetPosition({ WinApp::window_width - 80,WinApp::window_height - 64 });
			spriteMagazineUI->SetPosition({ WinApp::window_width - 256,WinApp::window_height - 128 });
			for (int i = 0; i < _countof(spriteLife); i++)
			{
				spriteLife[i]->SetPosition({ 100.0f + (i * 60),600.0f });
			}
			justCount = 0;
		}

		//sprite[0]->SetPosition({ mousePos.x,mousePos.y });
		if (isAlive == true)
		{
			//移動用velocity計算
			if (input->PushKey(DIK_LSHIFT))
			{
				VelocityBoost(plVelocity, virVelocity, targetCameraPos, virCameraPos, playerPos);
				Audio::GetInstance()->PlayWave("SE/swing.wav", 0.3, false);
			}
			else
			{
				VelocityNormal(plVelocity, virVelocity, targetCameraPos, virCameraPos, playerPos);
				Audio::GetInstance()->SoundStop("SE/swing.wav");
			}

			// 移動後の座標を計算
			//タイミングよく移動すると加速
			// -----------------------------------------//
			if (input->TriggerKey(DIK_W) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, 10, 1);
				isJust = true;
			}
			else if (input->PushKey(DIK_W))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, 100, 1);
			}
			if (input->TriggerKey(DIK_S) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, 10, 2);
				isJust = true;
			}
			else if (input->PushKey(DIK_S))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, 100, 2);
			}
			if (input->TriggerKey(DIK_A) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, 10, 2);
				isJust = true;
			}
			else if (input->PushKey(DIK_A))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, 100, 2);
			}
			if (input->TriggerKey(DIK_D) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, 10, 1);
				isJust = true;
			}
			else if (input->PushKey(DIK_D))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, 100, 1);
			}
			// -----------------------------------------//

			//プレイヤーが弾を撃つ
			// -----------------------------------------//
			if (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount < 50)
			{
				bullet[bulCount].bulFlag = true;
				bulCount++;
				if (isJustTiming)
				{
					isJust = true;
				}
			}

			lastBul = 50 - bulCount;
			spriteNum[0]->ChangeTex(lastBul / 10);
			spriteNum[1]->ChangeTex(lastBul % 10);
			spriteNum[2]->ChangeTex(maxMagazine / 10);
			spriteNum[3]->ChangeTex(skyBul);

			//リロード
			if ((input->TriggerKey(DIK_R) && isJustTiming && isReload == false)
				|| (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount == 50 && isJustTiming && isReload == false))
			{
				reloadCount = 30;
				justTiming = true;
				isReload = true;
				isJust = true;
			}
			else if ((input->TriggerKey(DIK_R) && isReload == false)
				|| (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount == 50 && isReload == false))
			{
				reloadCount = 30;
				maxMagazine = 20;
				isReload = true;
			}
		}

		//リロード音を鳴らす
		if (reloadCount > 0 && isReload == true)
		{
			reloadCount--;
			Audio::GetInstance()->PlayWave("SE/reload.wav", 0.3, false);
		}

		//リロード内部実行(タイミングジャスト)
		if (reloadCount == 0 && isReload == true && justTiming == true)
		{
			bulCount = 20;
			maxMagazine = 30;
			isReload = false;
			
			Audio::GetInstance()->SoundStop("SE/reload.wav");
		}
		//リロード内部実行
		else if (reloadCount == 0 && isReload == true)
		{
			bulCount = 30;
			isReload = false;
			Audio::GetInstance()->SoundStop("SE/reload.wav");
		}

		//弾を撃つ

		if (bullet[bulCount - 1].bulFlag == true && isReload == false)
		{
			sprite[0]->SetSize({ 64.0f + randUIX,64.0f + randUIY });
			sprite[0]->SetPosition({ spritePos.center.x - (32 + (randUIX / 2)),spritePos.center.y - (32 + (randUIY / 2)) });
			bullet[bulCount - 1].Pos = playerPos;
			bullet[bulCount - 1].bulShotFlag = true;
			bullet[bulCount - 1].bulFlag = false;
		}

		// 弾の処理
		for (int i = 0; i < _countof(objBul); i++)
		{
			if (bullet[i].bulShotFlag == true)
			{
				bullet[i].Pos.x += (plVelocity.x / 2);
				bullet[i].Pos.y += (plVelocity.y / 2);
				bullet[i].Pos.z += (plVelocity.z / 2);
				if ((bullet[i].Pos.z > 400) || (bullet[i].Pos.z < -400)
					|| (bullet[i].Pos.x > 400) || (bullet[i].Pos.x < -400))
				{
					bullet[i].Pos = { +1000,-10,1000 };
					bullet[i].bulShotFlag = false;
					sprite[0]->SetSize({ 64.0f,64.0f });
					sprite[0]->SetPosition({ spritePos.center.x - 32,spritePos.center.y - 32 });
				}
			}
		}

		//プレイヤーが生きているとき
		if (isAlive == true)
		{
			//マウスを動かすことによる視点移動
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

			// ジャンプ
			if (input->TriggerKey(DIK_SPACE) && isJump == false && isJustJump == false)
			{
				if (isJustTiming)
				{
					isJustJump = true;
					jCount = jCountMax;
					isJust = true;
				}
				else
				{
					isJump = true;
					jCount = jCountMin;
				}
			}
		}
		//ジャンプしたとき
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
		//ジャストタイミングでジャンプしたとき
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

		//マップ判定
		for (int y = 0; y < map_max_y; y++)
		{
			for (int x = 0; x < map_max_x; x++)
			{
				if (MapCollide(playerPos, objBlock[y][x]->GetPosition()))
				{
					isHit = true;
				}
			}
		}

		//マップと当たってないときにカメラを正常に戻す
		if (isHit == true && isAlive == true)
		{
			playerPos.x = oldPlayerPos.x;
			playerPos.z = oldPlayerPos.z;
			targetCameraPos = oldTargetCameraPos;
			virCameraPos = oldVirCameraPos;
			isHit = false;
		}
		//カメラ位置更新
		objFighter->SetPosition(playerPos);
		objFighter2->SetPosition(targetCameraPos);
		objFighter3->SetPosition(virCameraPos);

		//弾の初期化
		for (int i = 0; i < _countof(objBul); i++)
		{
			objBul[i]->SetPosition(bullet[i].Pos);
		}

		//弾がボスに当たったとき
		for (int i = 0; i < _countof(objBul); i++)
		{
			bool bossHit = (bossPos.x - playerScale.x < bullet[i].Pos.x + bullet[i].Size.x)
				&& (bossPos.x + playerScale.x > bullet[i].Pos.x - bullet[i].Size.x)
				&& (bossPos.z - playerScale.z < bullet[i].Pos.z + bullet[i].Size.z)
				&& (bossPos.z + playerScale.z > bullet[i].Pos.z - bullet[i].Size.z)
				&& (bossAlive == true);
			{
				if (bossHit)
				{
					firstBossHP--;
					objBul[i]->SetPosition({ +1000,-10,1000 });
					bullet[i].Pos = objBul[i]->GetPosition();
					bullet[i].Size = objBul[i]->GetScale();
					setParticle = true;
				}
			}
		}

		//パーティクルをセット
		if (setParticle == true)
		{
			for (int i = 0; i < _countof(redParticleObject); i++)
			{
				redParticleObject[i]->SetPosition({ bossPos });
				partPos2[i] = redParticleObject[i]->GetPosition();
				partVelocityx[i] = rand() % 10 - 5;
				partVelocityy[i] = rand() % 10 - 5;
				partVelocityz[i] = rand() % 10 - 5;
			}
			isParticle = true;
			setParticle = false;
		}
		//パーティクルを出す
		for (int i = 0; i < _countof(redParticleObject); i++)
		{
			if (isParticle == true)
			{
				partPos2[i].x += static_cast<float>(partVelocityx[i]) / 100;
				partPos2[i].y += static_cast<float>(partVelocityy[i]) / 100;
				partPos2[i].z += static_cast<float>(partVelocityz[i]) / 100;
				redParticleObject[i]->SetPosition({ partPos2[i]});
			}
		}

		//一定の時間経過で消える
		if (isParticle == true)
		{
			partTimer++;
			if (partTimer > 120)
			{
				isParticle = false;
				partTimer = 0;
			}
		}
		//ボスのHPの描画
		spritebossHP->SetSize({ 34.7f * (float)firstBossHP , 20 });

		if (firstBossHP <= 0)
		{
			bossAlive = false;
		}

		//ボスが死んだときのパーティクルを出す
		for (int i = 0; i < _countof(particleObject); i++)
		{
			if (bossAlive == false && oldBossAlive == true)
			{
				particleObject[i]->SetPosition({ bossPos });
				partPos[i] = particleObject[i]->GetPosition();
				partVelocityx[i] = rand() % 10 - 5;
				partVelocityy[i] = rand() % 10 - 5;
				partVelocityz[i] = rand() % 10 - 5;
			}
			if (bossAlive == false && oldBossAlive == false)
			{
				//ここ指摘されたとこだけどパーティクルのために全部変えていたためやり方がわからなかった
				partPos[i].x += static_cast<float>(partVelocityx[i]) / 10;
				partPos[i].y += static_cast<float>(partVelocityy[i]) / 10;
				partPos[i].z += static_cast<float>(partVelocityz[i]) / 10;
				//XMVectorAdd(partPos[i], static_cast<float>(partVelocityx[i]) / 10)
				particleObject[i]->SetPosition({ partPos[i] });
			}
		}

		//クリア時
		if (bossAlive == false && oldBossAlive == false)
		{
			clearTimer++;
		}
		if (clearTimer > 240)
		{
			SceneNum = Title;
		}
		//敵の行動
		if (bossAlive == true)
		{
			//atan2で敵の角度を割り出す
			bossVelocity.x = (bossPos.x - playerPos.x);
			bossVelocity.z = (bossPos.z - playerPos.z);
			bossRota.y = atan2(bossVelocity.x , bossVelocity.z) * 55 + 180.0f;
			bossEnemy->SetRotation(bossRota);

			if (skyBul == 0)
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
				if ((enemyMove < 40) || (enemyMove > 280 && enemyMove < 320))
				{
					bossPos.x += 0.1;
				}

				if ((enemyMove > 40 && enemyMove < 80) || (enemyMove > 200 && enemyMove < 240))
				{
					bossPos.x -= 0.1;
					bossPos.z += 0.1;
				}
				if (enemyMove > 80 && enemyMove < 120)
				{
					bossPos.x -= 0.1;
					bossPos.z -= 0.1;
				}
				if ((enemyMove > 120 && enemyMove < 140) || (enemyMove > 160 && enemyMove < 180))
				{
					bossPos.x += 0.1;
					bossPos.z -= 0.1;
				}
				if ((enemyMove > 140 && enemyMove < 160) || (enemyMove > 180 && enemyMove < 200))
				{
					bossPos.x += 0.1;
					bossPos.z += 0.1;
				}
				if (enemyMove > 240 && enemyMove < 280)
				{
					bossPos.x -= 0.1;
					bossPos.z -= 0.1;
				}
			}

			//---------------------ここから攻撃選定と前処理----------------------//

			//攻撃選定
			if (enemyAttackCounter >= 59 && skyBul == 0 && enemyBulCount < 42)
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
			else if (selectAttack < 75 && selectAttack != 0)
			{
				enemyTripleAttack = true;
				enemyAttackCounter = 0;
				selectAttack = 0;
			}
			else if (selectAttack < 85 && selectAttack != 0 && skyBul <= 4)
			{
				enemyBirdAttack = true;
				enemyAttackCounter = 0;
				selectAttack = 0;
			}
			else if (selectAttack < 100 && selectAttack != 0 && skyBul <= 4)
			{
				enemyStarAttack = true;
				enemyAttackCounter = 0;
				selectAttack = 0;
			}
		}

		//攻撃前処理
		if (enemySinpleAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			eBullet[enemyBulCount].bulFlag = true;
			eBullet[enemyBulCount].type = 1;
			enemyBulCount++;
			enemySinpleAttack = false;
		}
		if (eBullet[enemyBulCount - 1].bulFlag == true && eBullet[enemyBulCount - 1].type == 1)
		{
			eBullet[enemyBulCount - 1].Pos = bossPos;
			eBullet[enemyBulCount - 1].velocity.x = playerPos.x - bossPos.x;
			eBullet[enemyBulCount - 1].velocity.z = playerPos.z - bossPos.z;
			eBullet[enemyBulCount - 1].bulShotFlag = true;
			eBullet[enemyBulCount - 1].bulFlag = false;
		}

		if (enemyTripleAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 3); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 1;
				eBullet[i].velocity.x = playerPos.x - bossPos.x;
				eBullet[i].velocity.z = playerPos.z - bossPos.z;
			}
			enemyBulCount += 3;
			enemyTripleAttack = false;
		}

		if (eBullet[enemyBulCount - 1].bulFlag == true
			&& eBullet[enemyBulCount - 2].bulFlag == true
			&& eBullet[enemyBulCount - 3].bulFlag == true)
		{
			eBullet[enemyBulCount - 1].Pos = bossPos;
			eBullet[enemyBulCount - 1].Pos.x = bossPos.x - 2;
			eBullet[enemyBulCount - 1].bulShotFlag = true;
			eBullet[enemyBulCount - 1].bulFlag = false;

			eBullet[enemyBulCount - 2].Pos = bossPos;
			eBullet[enemyBulCount - 2].bulShotFlag = true;
			eBullet[enemyBulCount - 2].bulFlag = false;

			eBullet[enemyBulCount - 3].Pos = bossPos;
			eBullet[enemyBulCount - 3].Pos.x = bossPos.x + 2;
			eBullet[enemyBulCount - 3].bulShotFlag = true;
			eBullet[enemyBulCount - 3].bulFlag = false;
		}

		if (enemyBirdAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 5); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 2;
			}
			enemyBulCount += 5;
			skyBul += 5;
			enemyBirdAttack = false;
			fiveAttack = true;
		}

		//5つの弾が三角形に飛んでいく処理
		if (fiveAttack == true)
		{
			animeCount += 3;
			if (animeCount == 60)
			{
				eBullet[enemyBulCount - 1].Pos = bossPos;
				eBullet[enemyBulCount - 1].Pos.x = bossPos.x - 4;
				eBullet[enemyBulCount - 1].bulShotFlag = true;
				eBullet[enemyBulCount - 1].bulFlag = false;
			}
			if (animeCount == 120)
			{
				eBullet[enemyBulCount - 2].Pos = bossPos;
				eBullet[enemyBulCount - 2].Pos.x = bossPos.x - 2;
				eBullet[enemyBulCount - 2].Pos.y = bossPos.y + 1;
				eBullet[enemyBulCount - 2].bulShotFlag = true;
				eBullet[enemyBulCount - 2].bulFlag = false;
			}
			if (animeCount == 180)
			{
				eBullet[enemyBulCount - 3].Pos = bossPos;
				eBullet[enemyBulCount - 3].Pos.y = bossPos.y + 2;
				eBullet[enemyBulCount - 3].bulShotFlag = true;
				eBullet[enemyBulCount - 3].bulFlag = false;
			}
			if (animeCount == 240)
			{
				eBullet[enemyBulCount - 4].Pos = bossPos;
				eBullet[enemyBulCount - 4].Pos.x = bossPos.x + 2;
				eBullet[enemyBulCount - 4].Pos.y = bossPos.y + 1;
				eBullet[enemyBulCount - 4].bulShotFlag = true;
				eBullet[enemyBulCount - 4].bulFlag = false;
			}
			if (animeCount == 300)
			{
				eBullet[enemyBulCount - 5].Pos = bossPos;
				eBullet[enemyBulCount - 5].Pos.x = bossPos.x + 4;
				eBullet[enemyBulCount - 5].bulShotFlag = true;
				eBullet[enemyBulCount - 5].bulFlag = false;
			}
			if (animeCount == 360)
			{
				for (int i = enemyBulCount - 5; i < enemyBulCount; i++)
				{
					eBullet[i].velocity.x = playerPos.x - bossPos.x;
					eBullet[i].velocity.z = playerPos.z - bossPos.z;
				}
				fiveAttack = false;
				animeCount = 0;
			}
		}

		//5つの弾が五角形に飛んでいく前処理
		if (enemyStarAttack == true && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 5); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 2;
			}
			enemyBulCount += 5;
			skyBul += 5;
			enemyStarAttack = false;
			fiveAttack2 = true;
		}

		//5つの弾が五角形に飛んでいく処理
		if (fiveAttack2 == true)
		{
			animeCount += 3;
			if (animeCount == 60)
			{
				eBullet[enemyBulCount - 1].Pos = bossPos;
				eBullet[enemyBulCount - 1].Pos.x = bossPos.x - 1;
				eBullet[enemyBulCount - 1].bulShotFlag = true;
				eBullet[enemyBulCount - 1].bulFlag = false;
			}
			if (animeCount == 120)
			{
				eBullet[enemyBulCount - 2].Pos = bossPos;
				eBullet[enemyBulCount - 2].Pos.x = bossPos.x - 2;
				eBullet[enemyBulCount - 2].Pos.y = bossPos.y + 2;
				eBullet[enemyBulCount - 2].bulShotFlag = true;
				eBullet[enemyBulCount - 2].bulFlag = false;
			}
			if (animeCount == 180)
			{
				eBullet[enemyBulCount - 3].Pos = bossPos;
				eBullet[enemyBulCount - 3].Pos.y = bossPos.y + 4;
				eBullet[enemyBulCount - 3].bulShotFlag = true;
				eBullet[enemyBulCount - 3].bulFlag = false;
			}
			if (animeCount == 240)
			{
				eBullet[enemyBulCount - 4].Pos = bossPos;
				eBullet[enemyBulCount - 4].Pos.x = bossPos.x + 2;
				eBullet[enemyBulCount - 4].Pos.y = bossPos.y + 2;
				eBullet[enemyBulCount - 4].bulShotFlag = true;
				eBullet[enemyBulCount - 4].bulFlag = false;
			}
			if (animeCount == 300)
			{
				eBullet[enemyBulCount - 5].Pos = bossPos;
				eBullet[enemyBulCount - 5].Pos.x = bossPos.x + 1;
				eBullet[enemyBulCount - 5].bulShotFlag = true;
				eBullet[enemyBulCount - 5].bulFlag = false;
			}
			if (animeCount == 360)
			{
				for (int i = enemyBulCount - 5; i < enemyBulCount; i++)
				{
					eBullet[i].velocity.x = playerPos.x - bossPos.x;
					eBullet[i].velocity.z = playerPos.z - bossPos.z;
				}
				fiveAttack2 = false;
				animeCount = 0;
			}
		}

		//----------------ここから敵の撃つ処理-----------------//
		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			//タイプごとに飛ばし方を変える
			if (eBullet[i].type == 1)
			{
				if (eBullet[i].bulShotFlag == true)
				{
					eBullet[i].normalize = sqrtf((eBullet[i].velocity.x * eBullet[i].velocity.x) + (eBullet[i].velocity.z * eBullet[i].velocity.z));
					eBullet[i].Pos.x += eBullet[i].velocity.x / (eBullet[i].normalize * 3);
					eBullet[i].Pos.z += eBullet[i].velocity.z / (eBullet[i].normalize * 3);
				}
			}
			else if (eBullet[i].type == 2 && fiveAttack == false
				|| eBullet[i].type == 2 && fiveAttack2 == false)
			{
				if (eBullet[i].bulShotFlag == true)
				{
					eBullet[i].Pos.x += eBullet[i].velocity.x / 40;
					eBullet[i].Pos.y += eBullet[i].velocity.y / 40;
					eBullet[i].Pos.z += eBullet[i].velocity.z / 40;
				}
			}
			if (eBullet[i].bulShotFlag == true)
			{
				if ((eBullet[i].Pos.z > 400) || (eBullet[i].Pos.z < -400)
					|| (eBullet[i].Pos.x > 400) || (eBullet[i].Pos.x < -400))
				{
					if (skyBul > 0)
					{
						skyBul--;
					}
					eBullet[i].Pos = { +1000,-10,1000 };
					eBullet[i].bulShotFlag = false;
				}
				for (int y = 0; y < map_max_y; y++)
				{
					for (int x = 0; x < map_max_x; x++)
					{
						//マップチップとの当たり判定
						if (MapCollide(eBullet[i].Pos, objBlock[y][x]->GetPosition()))
						{
							if (skyBul > 0)
							{
								skyBul--;
							}
							eBullet[i].Pos = { 1000,-10,1000 };
							eBullet[i].bulShotFlag = false;
							eBullet[i].bulFlag = false;
							eBullet[i].attackAnimation = false;
							eBullet[i].type = 0;
							eBullet[i].velocity = { 0,0,0 };
						}
					}
				}
			}
		}

		//----------------ここまで敵の撃つ処理-----------------//

		// 
		if (enemyBulCount > 42 && skyBul == 0 && enemyAttackCounter >= 59)
		{
			//弾の初期化処理が必要
			enemyBulCount = 1;
			for (int i = 0; i < _countof(objEnemyBul); i++)
			{
				eBullet[i].bulShotFlag = false;
				eBullet[i].bulFlag = false;
				eBullet[i].attackAnimation = false;
				eBullet[i].type = 0;
				eBullet[i].velocity = { 0,0,0 };
			}
		}
		camera->SetEye({ playerPos.x, playerPos.y , playerPos.z });
		camera->SetTarget({ targetCameraPos.x , targetCameraPos.y , targetCameraPos.z });
		camera->Update();

		//敵の攻撃と自分との当たり判定
		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			bool playerHit = (playerPos.x - (playerScale.x / 3) < eBullet[i].Pos.x + eBullet[i].Size.x)
				&& (playerPos.x + (playerScale.x / 3) > eBullet[i].Pos.x - eBullet[i].Size.x)
				&& (playerPos.y - (playerScale.y / 3) < eBullet[i].Pos.y + eBullet[i].Size.y)
				&& (playerPos.y + (playerScale.y / 3) > eBullet[i].Pos.y - eBullet[i].Size.y)
				&& (playerPos.z - (playerScale.z / 3) < eBullet[i].Pos.z + eBullet[i].Size.z)
				&& (playerPos.z + (playerScale.z / 3) > eBullet[i].Pos.z - eBullet[i].Size.z)
				&& (isAlive == true);
			{
				//ノックバックとダメージ
				if (playerHit && hitTimer == 0)
				{
					hitTimer = 20;
					playerPos.x -= (plVelocity.x / 10);
					playerPos.z -= (plVelocity.z / 10);
					targetCameraPos.x -= (plVelocity.x / 10);
					targetCameraPos.z -= (plVelocity.z / 10);
					virCameraPos.x -= (plVelocity.x / 10);
					virCameraPos.z -= (plVelocity.z / 10);
					objFighter->SetPosition(playerPos);
					objFighter2->SetPosition(targetCameraPos);
					objFighter3->SetPosition(virCameraPos);
					playerHP--;
					if (skyBul > 0)
					{
						skyBul--;
					}
					eBullet[i].Pos = { +1000,-10,1000 };
					eBullet[i].bulShotFlag = false;
				}
			}
		}

		//プレイヤーのHPが0になったら死ぬ
		if (playerHP <= 0)
		{
			isAlive = false;
		}
		//プレイヤーが死んだら
		if (isAlive == false)
		{
			targetCameraPos.y -= 0.2;
			objFighter2->SetPosition(targetCameraPos);
			if (color.w < 1.0f)
			{
				color.w += 0.01;
			}
			diedText->SetColor(color);
			if (color.w >= 1.0f)
			{
				SceneNum = Title;
			}
		}

		//ヒット時の無敵時間
		if (hitTimer > 0)
		{
			hitTimer--;
			Audio::GetInstance()->PlayWave("SE/damage.wav", 0.03, false);
		}
		//当たり判定が消えたら音をリセットする
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

	objGround->SetPosition({ 0,1,0 });

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
	for (int i = 0; i < _countof(particleObject); i++)
	{
		particleObject[i]->Update();
	}
	for (int i = 0; i < _countof(redParticleObject); i++)
	{
		redParticleObject[i]->Update();
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
	objGround->Draw();
	//objCity->Draw();
	//objFighter2->Draw();
	if (bossAlive == true)
	{
		//objFighter2->Draw();
		bossEnemy->Draw();
	}
	if (bossAlive == false)
	{
		for (int i = 0; i < _countof(particleObject); i++)
		{
			particleObject[i]->Draw();
		}
	}
	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i]->Draw();
	}
	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		objEnemyBul[i]->Draw();
	}
	if (isParticle == true)
	{
		for (int i = 0; i < _countof(redParticleObject); i++)
		{
			redParticleObject[i]->Draw();
		}
	}
	//マップチップの描画
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Draw();
		}
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
	if (SceneNum == Title && isEase == false)
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
		for (int i = 0; i < playerHP; i++)
		{
			spriteLife[i]->Draw();
		}
		if (bossAlive == 1)
		{
			spritebossHPFrame->Draw();
			spritebossHP->Draw();
		}
		if (bulCount == 50)
		{
			reloadText->Draw();
		}
		if (isAlive == false)
		{
			diedText->Draw();
		}
		//brinkEffect->Draw();
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

void GameScene::CharactorMove(XMFLOAT3 &pos, XMFLOAT3 &camera, XMFLOAT3 &vir, XMFLOAT3 vec, int size,int type)
{
	if (type == 1)
	{
		pos.x += (vec.x / size);
		pos.z += (vec.z / size);
		camera.x += (vec.x / size);
		camera.z += (vec.z / size);
		vir.x += (vec.x / size);
		vir.z += (vec.z / size);
	}
	if (type == 2)
	{
		pos.x -= (vec.x / size);
		pos.z -= (vec.z / size);
		camera.x -= (vec.x / size);
		camera.z -= (vec.z / size);
		vir.x -= (vec.x / size);
		vir.z -= (vec.z / size);
	}
}

void GameScene::VelocityBoost(XMFLOAT3& vel, XMFLOAT3& vel2, XMFLOAT3 camera, XMFLOAT3 vir, XMFLOAT3 pos)
{
	vel.x = (camera.x - pos.x) * 2;
	vel.y = (camera.y - pos.y) * 2;
	vel.z = (camera.z - pos.z) * 2;

	vel2.x = (vir.x - pos.x) * 2;
	vel2.y = (vir.y - pos.y) * 2;
	vel2.z = (vir.z - pos.z) * 2;
}

void GameScene::VelocityNormal(XMFLOAT3& vel, XMFLOAT3& vel2, XMFLOAT3 camera, XMFLOAT3 vir, XMFLOAT3 pos)
{
	vel.x = (camera.x - pos.x);
	vel.y = (camera.y - pos.y);
	vel.z = (camera.z - pos.z);

	vel2.x = (vir.x - pos.x);
	vel2.y = (vir.y - pos.y);
	vel2.z = (vir.z - pos.z);
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

void GameScene::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(yが26)
		for (int x = 0; x < map_max_x; x++) {//(xが26)

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Ground)
			{
				//位置と大きさの変更(今は大きさは変更しないで)
				//objBlock[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objBlock[y][x]->SetPosition({ x * LAND_SCALE - 26,   2 , -y * LAND_SCALE + 50 });
			}
			else
			{
				objBlock[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

bool GameScene::MapCollide(XMFLOAT3& playerPos, const XMFLOAT3& blockPos)
{
	if ((playerPos.x - (playerScale.x / 2) < blockPos.x + (LAND_SCALE / 2))
		&& (playerPos.x + (playerScale.x / 2) > blockPos.x - (LAND_SCALE / 2))
		&& (playerPos.z - (playerScale.z / 2) < blockPos.z + (LAND_SCALE / 2))
		&& (playerPos.z + (playerScale.z / 2) > blockPos.z - (LAND_SCALE / 2)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

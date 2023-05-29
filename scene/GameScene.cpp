#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "Audio.h"

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
	for (int i = 0; i < _countof(spriteBul); i++)
	{
		safe_delete(spriteBul[i]);
	}
	for (int i = 0; i < _countof(lightParticle); i++)
	{
		safe_delete(lightParticle[i]);
	}
	safe_delete(spritebossHP);
	safe_delete(spritebossHPFrame);
	safe_delete(reloadText);
	safe_delete(diedText);
	safe_delete(brinkEffect);
	safe_delete(spriteEnterUI);
	safe_delete(spriteGood);

	//オブジェクトのdelete
	safe_delete(objSkydome);
	for (int i = 0; i < _countof(objBul); i++)
	{
		safe_delete(objBul[i]);
	}
	for (int i = 0; i < _countof(objCannonBul); i++)
	{
		safe_delete(objCannonBul[i]);
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
			safe_delete(objSecondBlock[i][j]);
		}
	}
	for (int i = 0; i < map_max_x; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			safe_delete(objWallFront[i][j]);
			safe_delete(objWallBack[i][j]);
			safe_delete(objWallRight[i][j]);
			safe_delete(objWallLeft[i][j]);
		}
	}
	safe_delete(objGround);
	safe_delete(objCannon);
	safe_delete(player);
	safe_delete(objFighter2);
	safe_delete(objFighter3);
	safe_delete(bossEnemy);
	safe_delete(shotgun);
	safe_delete(pistol);

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
	safe_delete(modelSphere2);
	safe_delete(modelBox);
	safe_delete(modelFire);
	safe_delete(modelRed);
	safe_delete(modelGun);
	safe_delete(modelPistol);
	for (int i = 0; i < _countof(timingParticle); i++)
	{
		safe_delete(timingParticle[i]);
	}
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

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

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
	if (!Sprite::LoadTexture(21, L"Resources/heart.png")) {
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
	if (!Sprite::LoadTexture(24, L"Resources/damageEffect.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(25, L"Resources/reticleRed.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(26, L"Resources/pushEnter.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(27, L"Resources/good.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(28, L"Resources/bullet.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(29, L"Resources/light.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(30, L"Resources/blood.png")) {
		assert(0);
		return;
	}

	

	// スプライト生成
	for (int i = 0; i < _countof(sprite); i++)
	{
		sprite[i] = Sprite::Create((12 + i), { 0.0f,0.0f });
	}
	for (int i = 0; i < _countof(spriteBul); i++)
	{
		spriteBul[i] = Sprite::Create(28, { 0.0f,0.0f });
	}

	spriteNum[0] = Sprite::Create(0, { 0.0f,0.0f });
	spriteNum[1] = Sprite::Create(1, { 0.0f,0.0f });
	spriteNum[2] = Sprite::Create(2, { 0.0f,0.0f });
	spriteNum[3] = Sprite::Create(3, { 0.0f,0.0f });
	spritedamageEffect = Sprite::Create(24, { 0.0f,0.0f });
	spritedamageEffect->SetSize({ WinApp::window_width,WinApp::window_height });
	spritebossHP = Sprite::Create(11, { 0.0f,0.0f });
	spritebossHPFrame = Sprite::Create(19, { 0.0f,0.0f });
	reloadText = Sprite::Create(20, { 0.0f,0.0f });
	diedText = Sprite::Create(22, { 0.0f,0.0f });
	brinkEffect = Sprite::Create(23, { 0.0f,0.0f });
	spriteEnterUI = Sprite::Create(26, {0.0f, 0.0f});
	spriteGood = Sprite::Create(27, { 0.0f,0.0f });
	spriteEnterUI->SetPosition({ WinApp::window_width / 2 - 192, WinApp::window_height - 80 });
	diedText->SetPosition({ WinApp::window_width / 2 - 254,WinApp::window_height / 2 - 38 });
	diedText->SetColor(diedTextColor);
	spriteBlood = Sprite::Create(30, { 0.0f,0.0f });
	//spriteBlood->SetSize({ 720.0f,1280.0f });
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i] = Sprite::Create(21, { 0.0f,0.0f });
	}
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i]->SetSize({ HeartMaxSize,HeartMaxSize });
	}
	for (int i = 0; i < _countof(spriteLife); i++)
	{
		spriteLife[i]->SetPosition({ heartPos + (i * 80),600.0f });
	}
	for (int i = 0; i < _countof(spriteBul); i++)
	{
		spriteBul[i]->SetSize({ 64,64 });
	}
	for (int i = 0; i < _countof(lightParticle); i++)
	{
		lightParticle[i] = Sprite::Create(29, { WinApp::window_width / 2 - 8, WinApp::window_height / 2 - 8 });
	}
	for (int i = 0; i < _countof(spriteBul); i++)
	{
		spriteBul[i]->SetPosition({ (float)WinApp::window_width - 64.0f, 128.0f + (i * 32.0f)});
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
	sprite[3]->SetPosition({ spritePos.center.x - 32,WinApp::window_height / 2 - 32 });
	sprite[4]->SetPosition({ spritePos.center.x - 272,WinApp::window_height - 160 });
	sprite[5]->SetPosition({ spritePos.center.x + 208,WinApp::window_height - 160 });
	reloadText->SetPosition({ WinApp::window_width / 2 - 80,WinApp::window_height / 2 + 80 });

	spritebossHP->SetPosition({ 303 , 47 });
	spritebossHP->SetSize({ 694 , 20 });

	spritebossHPFrame->SetPosition({ 300 , 00 });
	spritebossHPFrame->SetSize({ 700 , 70 });

	spriteGood->SetPosition({ WinApp::window_width / 2 - 80, WinApp::window_height / 2 + 80 });



	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), camera);

	// テクスチャ2番に読み込み

	// モデル読み込み
	modelSkydome = ReadModel::CreateFromOBJ("skydome");
	modelGround = ReadModel::CreateFromOBJ("ground");
	modelFighter = ReadModel::CreateFromOBJ("chr_sword");
	modelFighter2 = ReadModel::CreateFromOBJ("chr_sword");
	modelSphere = ReadModel::CreateFromOBJ("sphere3", true);
	modelSphere2 = ReadModel::CreateFromOBJ("sphere2", true);
	modelcowgirl = ReadModel::CreateFromOBJ("cowgirl", true);
	modelBox = ReadModel::CreateFromOBJ("block", true);
	modelFire = ReadModel::CreateFromOBJ("fire", true);
	modelRed = ReadModel::CreateFromOBJ("red", true);
	modelGun = ReadModel::CreateFromOBJ("Shotgun", true);
	modelPistol = ReadModel::CreateFromOBJ("Pistol", true);

	Mapchip::CsvToVector(map, "Resources/csv/bigmap.csv");//mapNum=0
	Mapchip::CsvToVector(map, "Resources/csv/Wall.csv");//mapNum=1
	Mapchip::CsvToVector(map, "Resources/csv/Wall.csv");//mapNum=2
	Mapchip::CsvToVector(map, "Resources/csv/Wall.csv");//mapNum=3
	Mapchip::CsvToVector(map, "Resources/csv/Wall.csv");//mapNum=4
	Mapchip::CsvToVector(map, "Resources/csv/bigmap2.csv");//mapNum=5

	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	objGround = Object3d::Create(modelGround);
	player = Object3d::Create(modelFighter);
	objFighter2 = Object3d::Create(modelPistol);
	objFighter3 = Object3d::Create(modelFighter2);
	bossEnemy = Object3d::Create(modelcowgirl);
	shotgun = Object3d::Create(modelGun);
	pistol = Object3d::Create(modelPistol);

	shotgun->SetScale({ 0.2,0.2,0.2 });
	shotgun->SetPosition({ dropGun.Pos });

	objFighter2->SetScale({ 0.01f,0.01f,0.01f });
	objFighter2->SetRotation({ 0,270,0 });
	pistol->SetScale({ 0.01f,0.01f,0.01f });
	pistol->SetRotation({ 0,270,0 });

	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x] = Object3d::Create(modelBox);
			objBlock[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objBlock[y][x]->SetPosition(OutAriaPos);
			objSecondBlock[y][x] = Object3d::Create(modelBox);
			objSecondBlock[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objSecondBlock[y][x]->SetPosition(OutAriaPos);
		}
	}

	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			objWallFront[y][x] = Object3d::Create(modelBox);
			objWallBack[y][x] = Object3d::Create(modelBox);
			objWallRight[y][x] = Object3d::Create(modelBox);
			objWallLeft[y][x] = Object3d::Create(modelBox);
			objWallFront[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objWallBack[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objWallRight[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objWallLeft[y][x]->SetScale({ 0.2f,0.2f,0.2f });
			objWallFront[y][x]->SetPosition(OutAriaPos);;
			objWallBack[y][x]->SetPosition(OutAriaPos);
			objWallRight[y][x]->SetPosition(OutAriaPos);;
			objWallLeft[y][x]->SetPosition(OutAriaPos);
		}
	}

	for (int i = 0; i < _countof(particleObject); i++)
	{
		particleObject[i] = Object3d::Create(modelFire);
		particleObject[i]->SetScale({ 0.2f,0.2f,0.2f });
		particleObject[i]->SetPosition(OutAriaPos);
	}

	for (int i = 0; i < _countof(redParticleObject); i++)
	{
		redParticleObject[i] = Object3d::Create(modelRed);
		redParticleObject[i]->SetScale({ 0.05f,0.05f,0.05f });
		redParticleObject[i]->SetPosition(OutAriaPos);
	}

	objCannon = Object3d::Create(modelcowgirl);
	objCannon->SetScale({ 0.5f,0.5f,0.5f });
	objCannon->SetRotation({cannon.Rotation});
	objCannon->SetPosition(cannon.Pos);

	for (int i = 0; i < _countof(objCannonBul); i++)
	{
		objCannonBul[i] = Object3d::Create(modelSphere);
		objCannonBul[i]->SetScale({ 0.5f,0.5f,0.5f });
		objCannonBul[i]->SetPosition(OutAriaPos);
	}


	//プレイヤー、敵、カメラの初期セット
	player->SetPosition({ 0,2,30 });
	objFighter2->SetPosition({ 0,12,30 });
	objFighter3->SetPosition({ 0,12,30 });
	bossEnemy->SetPosition({ 0,2, 40 });

	objGround->SetPosition({ 0,1,0 });
	objGround->SetScale({ 10,1,10 });


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

	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i] = Object3d::Create(modelSphere2);
		objBul[i]->SetPosition(OutAriaPos);
		objBul[i]->SetScale({ 0.2,0.2,0.2 });
	}

	for (int i = 0; i < _countof(objEnemyBul); i++)
	{
		objEnemyBul[i] = Object3d::Create(modelSphere);
		objEnemyBul[i]->SetPosition(OutAriaPos);
		objEnemyBul[i]->SetScale({ 0.5,0.5,0.5 });
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 0, 0 });
	camera->SetEye({ resetFloat3 });

	light = Light::Create();
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light);

	SceneNum = Title;
}

void GameScene::Update()
{
	SetCursorPos(mousePosX, mousePosY);
	CreateLight(timing);
	//各種変数関係
	MapCreate(0);
	MapCreate(1);
	MapCreate(2);
	MapCreate(3);
	MapCreate(4);
	MapCreate(5);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Update();
			objBlock[y][x]->GetPosition();
			objSecondBlock[y][x]->Update();
			objSecondBlock[y][x]->GetPosition();
		}
		for (int x = 0; x < 5; x++)
		{
			objWallFront[y][x]->Update();
			objWallBack[y][x]->Update();
			objWallRight[y][x]->Update();
			objWallLeft[y][x]->Update();
			objWallFront[y][x]->GetPosition();
			objWallBack[y][x]->GetPosition();
			objWallRight[y][x]->GetPosition();
			objWallLeft[y][x]->GetPosition();
		}
	}
	Input::MouseMove mouseMove = input->GetMouseMove();
	mousePos = { (float)mouseMove.lX / sensitivity,(float)mouseMove.lY / sensitivity };
	playerPos = player->GetPosition();
	bossPos = bossEnemy->GetPosition();
	playerScale = player->GetScale();
	targetCameraPos = objFighter2->GetPosition();
	virCameraPos = objFighter3->GetPosition();
	centerPos = { 0, 2, 50 };

	p_x_radius = player->GetScale().x;
	p_z_radius = player->GetScale().z;

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
		titleDrowCount++;
		player->SetPosition({ 0,2,30 });
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
			objBul[i]->SetPosition(OutAriaPos);
			objBul[i]->SetScale({ 0.2,0.2,0.2 });
		}

		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			objEnemyBul[i]->SetPosition(OutAriaPos);
			objEnemyBul[i]->SetScale({ 0.5,0.5,0.5 });
		}
		playerPos = player->GetPosition();
		bossPos = bossEnemy->GetPosition();
		playerScale = player->GetScale();
		targetCameraPos = objFighter2->GetPosition();
		virCameraPos = objFighter3->GetPosition();
		centerPos = { 0, 2, 50 };
		bulCount = 45;
		enemyBulCount = 1;
		plVelocity = { resetFloat3 };
		virVelocity = { resetFloat3 };
		bossAlive = true;
		enemyTimer = 0;
		timing = 75;
		isJust = false;
		isJump = Bad;
		isAlive = true;
		hitTimer = 0;
		jCount = 0.6;
		isHit = false;
		centerPos = { 0, 2, 50 };
		diedTextColor = { 1,1,1,0 };
		justTiming = false;
		isJustTiming = false;
		lastBul = 0;
		reloadCount = 0;
		isReload = false;
		maxMagazine = 5;
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
		bossVelocity = { resetFloat3 };

		clearTimer = 0;
		randUIX = 30;
		randUIY = 30;

		selectAttack = 0;
		howAttack = Non;
		enemyIsAttack = false;

		enemyMove = -15;
		isPlus = true;

		firstBossHP = 20;
		playerHP = 5;
		skyBul = 0;


		if (input->TriggerKey(DIK_RETURN) || input->TriggerMouseLeft())
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
				titleDrowCount = 0;
				CircularMotionUD(targetCameraPos, playerPos, circle, camera_data.angleZ, camera_data.angleY, circleAdd);
				CircularMotionLR(targetCameraPos, playerPos, circle, camera_data.angleZ, camera_data.angleX, circleAdd);
				CircularMotionUD(virCameraPos, playerPos, circle, camera_data.virangleZ, camera_data.virangleY, circleAdd);
				CircularMotionLR(virCameraPos, playerPos, circle, camera_data.virangleZ, camera_data.virangleX, circleAdd);
				nowCount = 0.0f;
				timeRate = 0.0f;

				titleEye = { 0,20,-30 };
				titleTarget = { 0,2, 40 };
				isEase = false;
			}
		}
		if (skyDomeRota < 360)
		{
			skyDomeRota += 0.1f;
		}
		else
		{
			skyDomeRota = 0;
		}
		objSkydome->SetRotation({ 0, skyDomeRota, 0 });

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
			if (mapRotaY == 0)
			{
				mapRotaY = 180.0f;
			}
			else
			{
				mapRotaY = 0.0f;
			}

			timing = timingMax;
			for (int y = 0; y < map_max_y; y++) {//(yが26)
				for (int x = 0; x < map_max_x; x++) {//(xが26)
					//objBlock[y][x]->SetRotation({ mapRotaY, 0, 0 });
					//objBlock[y][x]->Update();
				}
			}
		}

		if (TimingCheck(timing))
		{
			isJustTiming = true;
		}
		else
		{
			isJustTiming = false;
		}
		//---------------スプライトを変更する処理--------------//

		timeHeart = (timing / 60.0f);
		sprite[4]->SetPosition({ (WinApp::window_width / 2) - (4 * (float)timing + 32),WinApp::window_height  / 2 - 32 });
		sprite[5]->SetPosition({ (WinApp::window_width / 2) + (4 * (float)timing),WinApp::window_height / 2 - 32 });
		heartSize = static_cast<float>(Ease::easeIn(HeartMaxSize, HeartMinSize, timeHeart));
		heartPos = static_cast<float>(Ease::easeIn(MaxPos, MinPos, timeHeart));
		for (int i = 0; i < _countof(spriteLife); i++)
		{
			spriteLife[i]->SetSize({heartSize,heartSize});
		}
		for (int i = 0; i < _countof(spriteLife); i++)
		{
			spriteLife[i]->SetPosition({ heartPos + (i * 80),600.0f });
		}
		//---------------スプライトを変更する処理ここまで-------//
		if (isJust)
		{
			justCount++;
			if (justCount > 10)
			{
				isJust = false;
			}
		}
		else
		{
			justCount = 0;
		}

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
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, MinMoveVelocity, Plus);
				isJust = true;
			}
			else if (input->PushKey(DIK_W))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, MaxMoveVelocity, Plus);
			}
			if (input->TriggerKey(DIK_S) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, MinMoveVelocity, Minus);
				isJust = true;
			}
			else if (input->PushKey(DIK_S))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, plVelocity, MaxMoveVelocity, Minus);
			}
			if (input->TriggerKey(DIK_A) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, MinMoveVelocity, Minus);
				isJust = true;
			}
			else if (input->PushKey(DIK_A))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, MaxMoveVelocity, Minus);
			}
			if (input->TriggerKey(DIK_D) && isJustTiming)
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, MinMoveVelocity, Plus);
				isJust = true;
			}
			else if (input->PushKey(DIK_D))
			{
				CharactorMove(playerPos, targetCameraPos, virCameraPos, virVelocity, MaxMoveVelocity, Plus);
			}
			pistolVec.x = (targetCameraPos.x - playerPos.x) / 50;
			pistolVec.z = (targetCameraPos.z - playerPos.z) / 50;

			pistolPos.x = playerPos.x + pistolVec.x;
			pistolPos.y = playerPos.y - 0.05;
			pistolPos.z = playerPos.z + pistolVec.z;

			pistolVel.x = (targetCameraPos.x - playerPos.x);
			pistolVel.z = (targetCameraPos.z - playerPos.z);
			if (playerGun == Pistol)
			{
				pistolRotaY = atan2(pistolVel.x, pistolVel.z) * 57 + 270.0f;
			}
			else
			{
				pistolRotaY = atan2(pistolVel.x, pistolVel.z) * 57 + 180.0f;
			}
			pistol->SetRotation({ 0,pistolRotaY,knock });

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
					setParticleTiming = true;
					isParticleSprite = true;
				}
			}
			if (setParticleTiming == true)
			{
				for (int i = 0; i < _countof(lightParticle); i++)
				{
					partPosition[i] = XMFLOAT2(WinApp::window_width / 2 - 8, WinApp::window_height / 2 - 8);
					spriteVelX[i] = rand() % 20 - 10;
					spriteVelY[i] = rand() % 20 - 10;
				}
				isParticleTiming = true;
				setParticleTiming = false;
			}

			for (int i = 0; i < _countof(lightParticle); i++)
			{
				if (isParticleTiming == true && setParticleTiming == false)
				{
					partPosition[i].x += spriteVelX[i];
					partPosition[i].y += spriteVelY[i];
					lightParticle[i]->SetPosition({ partPosition[i] });
				}
			}

			if (isJust == false)
			{
				isParticleSprite = false;
			}

			//元々の残弾数表示
			lastBul = 50 - bulCount;

			//リロード
			if ((input->TriggerKey(DIK_R) && isJustTiming && isReload == false)
				|| (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount == 50 && isJustTiming && isReload == false))
			{
				reloadCount = 30;
				maxMagazine = BigMag;
				justTiming = true;
				isReload = true;
				isJust = true;
			}
			else if ((input->TriggerKey(DIK_R) && isReload == false)
				|| (input->TriggerMouseLeft() && bullet[bulCount].bulShotFlag == false && bulCount == 50 && isReload == false))
			{
				reloadCount = 30;
				maxMagazine = MinMag;
				isReload = true;
			}
		}

		//リロード実行
		Reload(reloadCount, isReload, justTiming, bulCount, maxMagazine);


		DropItemInfo();

		if (bullet[bulCount - 1].bulFlag == true && isReload == false)
		{
			sprite[0]->SetSize({ 64.0f + randUIX,64.0f + randUIY });
			sprite[0]->ChangeTex(25);
			sprite[0]->SetPosition({ spritePos.center.x - (32 + (randUIX / 2)),spritePos.center.y - (32 + (randUIY / 2)) });
			knock = 20.0f;
			bullet[bulCount - 1].Pos = playerPos;
			bullet[bulCount - 1].bulShotFlag = true;
			if (isJust)
			{
				bullet[bulCount - 1].damage = 1.0f;
			}
			else
			{
				bullet[bulCount - 1].damage = 0.1f;
			}
			bullet[bulCount - 1].bulFlag = false;
		}

		// 弾の処理
		for (int i = 0; i < _countof(objBul); i++)
		{
			if (bullet[i].bulShotFlag == true)
			{
				bullet[i].Pos.x += (plVelocity.x / 8);
				bullet[i].Pos.y += (plVelocity.y / 8);
				bullet[i].Pos.z += (plVelocity.z / 8);
				for (int y = 0; y < map_max_y; y++)
				{
					for (int x = 0; x < map_max_x; x++)
					{
						if ((bullet[i].Pos.z > AriaField) || (bullet[i].Pos.z < -AriaField)
							|| (bullet[i].Pos.x > AriaField) || (bullet[i].Pos.x < -AriaField)
							|| MapCollide3D(bullet[i].Pos, objBlock[y][x]->GetPosition()))
						{
							bullet[i].Pos = OutAriaPos;
							bullet[i].bulShotFlag = false;
							sprite[0]->SetSize({ 64.0f,64.0f });
							sprite[0]->ChangeTex(12);
							sprite[0]->SetPosition({ spritePos.center.x - 32,spritePos.center.y - 32 });
							knock = 0.0f;
						}
					}
				}
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

		//プレイヤーが生きているとき
		if (isAlive == true && isHit == false)
		{
			mousePos = { (float)mouseMove.lX / 50,(float)mouseMove.lY / 50 };
			//マウスを動かすことによる視点移動
			if (camera_data.angleY < 90 && mousePos.y < 0 || camera_data.angleY > -90 && mousePos.y > 0 )
			{
				CircularMotionUD(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleY, -mousePos.y);
				CircularMotionUD(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleY, -mousePos.y);
			}
			if (mousePos.x != 0)
			{
				CircularMotionLR(targetCameraPos, playerPos, 10.00f, camera_data.angleZ, camera_data.angleX, mousePos.x);
				CircularMotionLR(virCameraPos, playerPos, 10.00f, camera_data.virangleZ, camera_data.virangleX, mousePos.x);
			}

			// ジャンプ選定
			JumpStart(isJustTiming, isJump, jCount, isJust);
		}
		//ジャンプ
		Jump(isJump, jCount, playerPos, targetCameraPos);



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
		player->SetPosition(playerPos);
		objFighter2->SetPosition(targetCameraPos);
		objFighter3->SetPosition(virCameraPos);
		if (playerGun == Pistol)
		{
			pistol->SetPosition({ pistolPos.x,pistolPos.y,pistolPos.z });
			pistol->Update();
		}
		else
		{
			shotgun->SetScale({ 0.03f,0.03f,0.03f });
			shotgun->SetRotation({ knock,pistolRotaY,0 });
			shotgun->SetPosition({ pistolPos.x,pistolPos.y,pistolPos.z });
			shotgun->Update();
		}

		//弾の初期化
		for (int i = 0; i < _countof(objBul); i++)
		{
			objBul[i]->SetPosition(bullet[i].Pos);
		}

		//弾がボスに当たったとき
		for (int i = 0; i < _countof(objBul); i++)
		{
			bool bossHit = Collide(bossPos, playerScale, bullet[i].Pos, bullet[i].Size, bossAlive);
			{
				if (bossHit)
				{
					firstBossHP -= bullet[i].damage;
					objBul[i]->SetPosition(OutAriaPos);
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
			bossRota.y = atan2(bossVelocity.x , bossVelocity.z) * 57 + 180.0f;
			bossEnemy->SetRotation(bossRota);

			if (skyBul == 0)
			{
				enemyAttackCounter++;
				EnemyMove2(bossPos, enemyMove, isPlus);
			}

			//---------------------ここから攻撃選定と前処理----------------------//

			//攻撃選定
			if (enemyAttackCounter >= 59 && skyBul == 0 && enemyBulCount < 46 && timing == timingMax)
			{
				selectAttack = rand() % 100;
				enemyAttackCounter = 0;
			}

			SelectAttack(selectAttack, howAttack, skyBul, enemyAttackCounter);
		}

		if (cannonAttackCount < 92)
		{
			cannonAttackCount++;
		}
		else
		{
			cannonBullet[cannonCount].bulFlag = true;
			cannonAttackCount = 0;
		}

		if (cannonBullet[cannonCount].bulFlag == true)
		{
			cannonBullet[cannonCount].Pos = cannon.Pos;
			cannonBullet[cannonCount].bulShotFlag = true;
			cannonBullet[cannonCount].bulFlag = false;
		}

		if (cannonBullet[cannonCount].bulShotFlag == true)
		{
			cannonBullet[cannonCount].Pos.x -= 0.5f;
			if ((cannonBullet[cannonCount].Pos.z > AriaField) || (cannonBullet[cannonCount].Pos.z < -AriaField)
				|| (cannonBullet[cannonCount].Pos.x > AriaField) || (cannonBullet[cannonCount].Pos.x < -AriaField))
			{
				cannonBullet[cannonCount].Pos = OutAriaPos;
				cannonBullet[cannonCount].bulShotFlag = false;
			}
			for (int y = 0; y < map_max_y; y++)
			{
				for (int x = 0; x < map_max_x; x++)
				{
					if (MapCollide(cannonBullet[cannonCount].Pos, objBlock[y][x]->GetPosition()))
					{
						cannonBullet[cannonCount].Pos = OutAriaPos;
						cannonBullet[cannonCount].bulShotFlag = false;
					}
				}
			}
		}

		//攻撃前処理
		if (howAttack == Sinple && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			eBullet[enemyBulCount].bulFlag = true;
			eBullet[enemyBulCount].type = 1;
			enemyBulCount++;
			howAttack = Non;
		}
		if (eBullet[enemyBulCount - 1].bulFlag == true && eBullet[enemyBulCount - 1].type == 1)
		{
			eBullet[enemyBulCount - 1].Pos = bossPos;
			eBullet[enemyBulCount - 1].velocity.x = playerPos.x - bossPos.x;
			eBullet[enemyBulCount - 1].velocity.z = playerPos.z - bossPos.z;
			eBullet[enemyBulCount - 1].bulShotFlag = true;
			eBullet[enemyBulCount - 1].bulFlag = false;
		}

		if (howAttack == Triple && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 3); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 1;
				eBullet[i].velocity.x = playerPos.x - bossPos.x;
				eBullet[i].velocity.z = playerPos.z - bossPos.z;
			}
			enemyBulCount += 3;
			howAttack = Non;
		}

		if (eBullet[enemyBulCount - 1].bulFlag == true
			&& eBullet[enemyBulCount - 2].bulFlag == true
			&& eBullet[enemyBulCount - 3].bulFlag == true)
		{
			eBullet[enemyBulCount - 1].Pos = XMFLOAT3(bossPos.x - 2, bossPos.y ,bossPos.z);

			eBullet[enemyBulCount - 2].Pos = bossPos;

			eBullet[enemyBulCount - 3].Pos = XMFLOAT3(bossPos.x + 2, bossPos.y, bossPos.z);
			for (int i = enemyBulCount - 3; i < enemyBulCount; i++)
			{
				eBullet[i].bulShotFlag = true;
				eBullet[i].bulFlag = false;
			}
		}

		if (howAttack == Bird && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 5); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 2;
			}
			enemyBulCount += 5;
			skyBul += 5;
			howAttack = Non;
			fiveAttack = true;
		}

		//5つの弾が三角形に飛んでいく処理
		if (fiveAttack == true)
		{
			animeCount += 1;
			if (animeCount == 30)
			{
				eBullet[enemyBulCount - 1].Pos = XMFLOAT3(bossPos.x - 4, bossPos.y, bossPos.z);
			}
			if (animeCount == 60)
			{
				eBullet[enemyBulCount - 2].Pos = XMFLOAT3(bossPos.x - 2, bossPos.y + 1, bossPos.z);
			}
			if (animeCount == 90)
			{
				eBullet[enemyBulCount - 3].Pos = XMFLOAT3(bossPos.x, bossPos.y + 2, bossPos.z);
			}
			if (animeCount == 120)
			{
				eBullet[enemyBulCount - 4].Pos = XMFLOAT3(bossPos.x + 2, bossPos.y + 1, bossPos.z);
			}
			if (animeCount == 150)
			{
				eBullet[enemyBulCount - 5].Pos = XMFLOAT3(bossPos.x + 4, bossPos.y, bossPos.z);
			}
			if (animeCount == 180)
			{
				for (int i = enemyBulCount - 5; i < enemyBulCount; i++)
				{
					eBullet[i].velocity.x = playerPos.x - bossPos.x;
					eBullet[i].velocity.z = playerPos.z - bossPos.z;
					eBullet[i].bulShotFlag = true;
					eBullet[i].bulFlag = false;
				}
				fiveAttack = false;
				animeCount = 0;
			}
		}

		//5つの弾が五角形に飛んでいく前処理
		if (howAttack == Star && eBullet[enemyBulCount].bulShotFlag == false && enemyBulCount < 49)
		{
			for (int i = enemyBulCount; i < (enemyBulCount + 5); i++)
			{
				eBullet[i].bulFlag = true;
				eBullet[i].type = 2;
			}
			enemyBulCount += 5;
			skyBul += 5;
			howAttack = Non;
			fiveAttack2 = true;
		}

		//5つの弾が五角形に飛んでいく処理
		if (fiveAttack2 == true)
		{
			animeCount += 1;
			if (animeCount == 30)
			{
				eBullet[enemyBulCount - 1].Pos = XMFLOAT3(bossPos.x - 1, bossPos.y, bossPos.z);
			}
			if (animeCount == 60)
			{
				eBullet[enemyBulCount - 2].Pos = XMFLOAT3(bossPos.x - 2, bossPos.y + 2,bossPos.z);
			}
			if (animeCount == 90)
			{
				eBullet[enemyBulCount - 3].Pos = XMFLOAT3(bossPos.x, bossPos.y + 4, bossPos.z);
			}
			if (animeCount == 120)
			{
				eBullet[enemyBulCount - 4].Pos = XMFLOAT3(bossPos.x + 2, bossPos.y + 2, bossPos.z);
			}
			if (animeCount == 150)
			{
				eBullet[enemyBulCount - 5].Pos = XMFLOAT3(bossPos.x + 1, bossPos.y, bossPos.z);
			}
			if (animeCount == 180)
			{
				for (int i = enemyBulCount - 5; i < enemyBulCount; i++)
				{
					eBullet[i].velocity.x = playerPos.x - bossPos.x;
					eBullet[i].velocity.z = playerPos.z - bossPos.z;
					eBullet[i].bulShotFlag = true;
					eBullet[i].bulFlag = false;
				}
				fiveAttack2 = false;
				animeCount = 0;
			}
		}

		//----------------ここから敵の撃つ処理-----------------//
		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			//タイプごとに飛ばし方を変える
			if (eBullet[i].type == Streat)
			{
				if (eBullet[i].bulShotFlag == true)
				{
					eBullet[i].normalize = sqrtf((eBullet[i].velocity.x * eBullet[i].velocity.x) + (eBullet[i].velocity.z * eBullet[i].velocity.z));
					eBullet[i].Pos.x += eBullet[i].velocity.x / (eBullet[i].normalize * 3);
					eBullet[i].Pos.z += eBullet[i].velocity.z / (eBullet[i].normalize * 3);
				}
			}
			else if (eBullet[i].type == Anime && fiveAttack == false
				|| eBullet[i].type == Anime && fiveAttack2 == false)
			{
				eBullet[i].Pos.x += eBullet[i].velocity.x / 40;
				eBullet[i].Pos.y += eBullet[i].velocity.y / 40;
				eBullet[i].Pos.z += eBullet[i].velocity.z / 40;
			}
			if (eBullet[i].bulShotFlag == true)
			{
				if ((eBullet[i].Pos.z > AriaField) || (eBullet[i].Pos.z < -AriaField)
					|| (eBullet[i].Pos.x > AriaField) || (eBullet[i].Pos.x < -AriaField))
				{
					if (eBullet[i].type == 2)
					{
						if (skyBul > 0)
						{
							skyBul--;
						}
					}
					eBullet[i].Pos = OutAriaPos;
					eBullet[i].bulShotFlag = false;
				}
				for (int y = 0; y < map_max_y; y++)
				{
					for (int x = 0; x < map_max_x; x++)
					{
						//マップチップとの当たり判定
						if (MapCollide(eBullet[i].Pos, objBlock[y][x]->GetPosition()))
						{
							//アニメーション弾なら
							if (eBullet[i].type == 2)
							{
								if (skyBul > 0)
								{
									skyBul--;
								}
							}
							eBullet[i].Pos = OutAriaPos;
							eBullet[i].bulShotFlag = false;
							eBullet[i].type = 0;
							eBullet[i].velocity = { resetFloat3 };
						}

					}
				}
			}
		}

		//----------------ここまで敵の撃つ処理-----------------//

		// 弾の初期化と弾数リセット
		if (enemyBulCount > 42 && skyBul == 0 && enemyAttackCounter <= 59)
		{
			//弾の初期化処理が必要
			for (int i = 0; i < _countof(objEnemyBul); i++)
			{
				eBullet[i].bulShotFlag = false;
				eBullet[i].bulFlag = false;
				eBullet[i].type = 0;
				eBullet[i].velocity = { resetFloat3 };
				eBullet[i].Pos = OutAriaPos;
			}
			enemyBulCount = 1;
		}
		camera->SetEye(playerPos);
		camera->SetTarget(targetCameraPos);
		camera->Update();

		//敵の攻撃と自分との当たり判定
		for (int i = 0; i < _countof(objEnemyBul); i++)
		{
			XMcalculation(playerCollideScale,playerScale,collideSize,4);
			bool playerHit = Collide(playerPos, playerCollideScale, eBullet[i].Pos, eBullet[i].Size, isAlive);
			{
				//ノックバックとダメージ
				if (playerHit && hitTimer == 0)
				{
					hitTimer = 40;
					playerHP--;
					if (skyBul > 0)
					{
						skyBul--;
					}
					eBullet[i].Pos = OutAriaPos;
					eBullet[i].bulShotFlag = false;
				}
			}
		}
		//敵の攻撃と自分との当たり判定
		for (int i = 0; i < _countof(cannonBullet); i++)
		{
			bool playerHit = Collide(playerPos, playerCollideScale, cannonBullet[i].Pos, cannonBullet[i].Size, isAlive);
			{
				//ノックバックとダメージ
				if (playerHit && hitTimer == 0)
				{
					hitTimer = 40;
					playerHP--;
					cannonBullet[i].Pos = OutAriaPos;
					cannonBullet[i].bulShotFlag = false;
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
			if (diedTextColor.w < 1.0f)
			{
				diedTextColor.w += 0.01;
			}
			diedText->SetColor(diedTextColor);
			if (diedTextColor.w >= 1.0f)
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
		for (int i = 0; i < _countof(objCannonBul); i++)
		{
			objCannonBul[i]->SetPosition(cannonBullet[i].Pos);
		}
		bossEnemy->SetPosition(bossPos);

		// 移動後の座標を計算
		cameraPos = player->GetPosition();

		camera->SetEye({ playerPos.x, playerPos.y , playerPos.z });
		camera->SetTarget({ targetCameraPos.x , targetCameraPos.y , targetCameraPos.z });
		camera->Update();
		if (timing == timingMax)
		{
			if (skyDomeRota < 360)
			{
				skyDomeRota += 10.0f;
			}
			else
			{
				skyDomeRota = 0;
			}
		}
		objSkydome->SetRotation({ 0, skyDomeRota, 0 });
	}

	particleMan->Update();

	objSkydome->Update();
	objGround->Update();
	objCannon->Update();
	bossEnemy->Update();
	shotgun->Update();
	pistol->Update();
	player->Update();
	objFighter2->Update();
	objFighter3->Update();
	for (int i = 0; i < _countof(cannonBullet); i++)
	{
		objCannonBul[i]->Update();
	}
	for (int i = 0; i < _countof(objBul); i++)
	{
		objBul[i]->Update();
		objEnemyBul[i]->Update();
		particleObject[i]->Update();
		redParticleObject[i]->Update();
	}
	light->Update();
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
	shotgun->Draw();
	//objFighter2->Draw();
	if (playerGun == Pistol)
	{
		pistol->Draw();
	}
	if (bossAlive == true)
	{
		//objFighter2->Draw();
		bossEnemy->Draw();
		objCannon->Draw();
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
	for (int i = 0; i < _countof(cannonBullet); i++)
	{
		objCannonBul[i]->Draw();
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
			if (Mapchip::GetChipNum(x, y, map[0]) == Ground)
			{
				objBlock[y][x]->Draw();
				objSecondBlock[y][x]->Draw();
			}
		}
		for (int x = 0; x < 5; x++)
		{
			objWallFront[y][x]->Draw();
			objWallBack[y][x]->Draw();
			objWallRight[y][x]->Draw();
			objWallLeft[y][x]->Draw();
		}
	}
	Object3d::PostDraw();

	// パーティクルの描画
	particleMan->Draw(cmdList);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// ここに前景スプライトの描画処理を追加できる
	//spriteBG->Draw();
	// デバッグテキストの描画
	//sprite[0]->Draw();
	if (SceneNum == Title && isEase == false)
	{
		if (titleDrowCount % 100 < 50)
		{
			sprite[1]->Draw();
			spriteEnterUI->Draw();
		}
	}
	if (SceneNum == Win)
	{
		sprite[2]->Draw();
	}
	if (SceneNum == Game)
	{
		if (hitTimer > 0)
		{
			spritedamageEffect->SetColor({ 1, 0, 0, ((float)hitTimer / 80)});
			spritedamageEffect->Draw();
			spriteBlood->SetColor({ 1, 0, 0, ((float)hitTimer / 40) });
			spriteBlood->Draw();
		}
		sprite[3]->Draw();
		sprite[4]->Draw();
		sprite[5]->Draw();
		if (isJust)
		{
			spriteGood->Draw();
			if (isParticleSprite == true)
			{
				for (int i = 0; i < _countof(lightParticle); i++)
				{
					lightParticle[i]->Draw();
				}
			}
		}
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
		for (int i = 0; i < lastBul; i++)
		{
			spriteBul[i]->Draw();
		}
		if (isAlive == false)
		{
			diedText->Draw();
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

void GameScene::CreateLight(int timing)
{
	//光線方向初期値
	static XMVECTOR lightDir = { 0, 50, 5, 0 };

	if (timing == timingMax)
	{
		if (lightDir.m128_f32[1] < 0) { lightDir.m128_f32[1] += 50.0f; }
		else { lightDir.m128_f32[1] -= 50.0f; }
	}

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

void GameScene::EnemyMove(XMFLOAT3& epos, int& emove, bool eflag)
{
	if (eflag)
	{
		if (emove < 480)
		{
			emove++;
		}
		if (emove >= 480)
		{
			emove = 0;
		}
	}
	if (emove > 0)
	{
		if ((emove < 60) || (emove > 420 && emove < 480))
		{
			epos.x += 0.1;
		}

		if ((emove > 60 && emove < 120) || (emove > 300 && emove < 360))
		{
			epos.x -= 0.1;
			epos.z += 0.1;
		}
		if (emove > 120 && emove < 180)
		{
			epos.x -= 0.1;
			epos.z -= 0.1;
		}
		if ((emove > 180 && emove < 210) || (emove > 240 && emove < 270))
		{
			epos.x += 0.1;
			epos.z -= 0.1;
		}
		if ((emove > 210 && emove < 240) || (emove > 270 && emove < 300))
		{
			epos.x += 0.1;
			epos.z += 0.1;
		}
		if (emove > 360 && emove < 420)
		{
			epos.x -= 0.1;
			epos.z -= 0.1;
		}
	}
}

void GameScene::EnemyMove2(XMFLOAT3& epos, int& emove, bool eflag)
{
	if (eflag)
	{
		if (emove < 1440)
		{
			emove++;
		}
		if (emove >= 1440)
		{
			emove = 0;
		}
	}
	if (emove > 0)
	{
		if ((emove < 90) || (emove > 150 && emove < 240) || (emove > 1200 && emove < 1290) || (emove > 1350 && emove < 1440))
		{
			epos.x += 0.1;
		}

		if ((emove > 90 && emove < 150))
		{
			epos.x += 0.1;
			epos.z -= 0.1;
		}

		if ((emove > 240 && emove < 480))
		{
			epos.z -= 0.1;
		}
		if ((emove > 480 && emove < 540)|| (emove > 600 && emove < 660) || (emove > 720 && emove < 780))
		{
			epos.x -= 0.1;
			epos.z -= 0.1;
		}
		if ((emove > 540 && emove < 600) ||(emove > 660 && emove < 720) || (emove > 780 && emove < 840))
		{
			epos.x -= 0.1;
			epos.z += 0.1;
		}
		if ((emove > 840 && emove < 960))
		{
			epos.x -= 0.1;
		}
		if ((emove > 960 && emove < 1200))
		{
			epos.z += 0.1;
		}
		if ((emove > 1290 && emove < 1350))
		{
			epos.x += 0.1;
			epos.z += 0.1;
		}
	}
}

void GameScene::Reload(int& reloadCount, bool& isReload, bool& justTiming, int& bulCount, int& maxMagazine)
{
	//リロード音を鳴らす
	if (reloadCount > 0 && isReload == true)
	{
		reloadCount--;
		Audio::GetInstance()->PlayWave("SE/reload.wav", 0.3, false);
	}
	//リロード内部実行(タイミングジャスト)
	if (reloadCount == 0 && isReload == true && justTiming == true)
	{
		bulCount = 50 - BigMag;
		isReload = false;

		Audio::GetInstance()->SoundStop("SE/reload.wav");
		justTiming = false;
	}
	//リロード内部実行
	else if (reloadCount == 0 && isReload == true)
	{
		bulCount = 50 - MinMag;
		isReload = false;
		Audio::GetInstance()->SoundStop("SE/reload.wav");
	}
}

void GameScene::JumpStart(bool timing, int& isJump, float& jCount, bool& isJust)
{
	if (input->TriggerKey(DIK_SPACE) && isJump == Bad)
	{
		if (timing)
		{
			isJump = Good;
			jCount = jCountMax;
			isJust = true;
		}
		else
		{
			isJump = Normal;
			jCount = jCountMin;
		}
	}
}

void GameScene::Jump(int& isJump, float& jCount, XMFLOAT3& playerPos, XMFLOAT3& targetPos)
{
	//ジャンプしたとき
	if (isJump == Normal)
	{
		Audio::GetInstance()->PlayWave("SE/jump.wav", 0.03, false);
		jCount -= 0.025;
		if (jCount > -jCountMin)
		{
			playerPos.y += jCount;
			targetPos.y += jCount;
		}
		else
		{
			isJump = false;
			Audio::GetInstance()->SoundStop("SE/jump.wav");
		}
	}
	//ジャストタイミングでジャンプしたとき
	if (isJump == Good)
	{
		Audio::GetInstance()->PlayWave("SE/jump.wav", 0.03, false);
		jCount -= 0.025;
		if (jCount > -jCountMax)
		{
			playerPos.y += jCount;
			targetPos.y += jCount;
		}
		else
		{
			isJump = Bad;
			Audio::GetInstance()->SoundStop("SE/jump.wav");
		}
	}
}

void GameScene::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(yが26)
		if (mapNumber == 0 || mapNumber == 5)
		{
			for (int x = 0; x < map_max_x; x++)//(xが26)
			{
				if (mapNumber == 0)
				{
					if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Ground)
					{
						//位置と大きさの変更(今は大きさは変更しないで)
						//objBlock[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
						objBlock[y][x]->SetPosition({ x * LAND_SCALE - 26,   1.5f , -y * LAND_SCALE + 50 });
					}
					else
					{
						objBlock[y][x]->SetPosition(OutAriaPos);
					}
				}
				if (mapNumber == 5)
				{
					if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Ground)
					{
						//位置と大きさの変更(今は大きさは変更しないで)
						//objBlock[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
						objSecondBlock[y][x]->SetPosition({ x * LAND_SCALE - 26,   2.5f , -y * LAND_SCALE + 50 });
					}
					else
					{
						objSecondBlock[y][x]->SetPosition(OutAriaPos);
					}
				}
			}
		}
		else
		{
			for (int x = 0; x < 5; x++)//(xが26)
			{
				if (mapNumber == 4)
				{
					objWallLeft[y][x]->SetPosition({ -26 , 1.5f + x * LAND_SCALE , -y * LAND_SCALE + 50 });
				}
				if (mapNumber == 3)
				{
					objWallRight[y][x]->SetPosition({ 25 , 1.5f + x * LAND_SCALE , -y * LAND_SCALE + 50 });
				}
				if (mapNumber == 2)
				{
					objWallBack[y][x]->SetPosition({ y * LAND_SCALE - 26 , 1.5f + x * LAND_SCALE , 50 });
				}
				if (mapNumber == 1)
				{
					objWallFront[y][x]->SetPosition({ y * LAND_SCALE - 26 , 1.5f + x * LAND_SCALE , -1 });
				}
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

bool GameScene::MapCollide3D(XMFLOAT3& playerPos, const XMFLOAT3& blockPos)
{
	if ((playerPos.x - (playerScale.x / 2) < blockPos.x + (LAND_SCALE / 2))
		&& (playerPos.x + (playerScale.x / 2) > blockPos.x - (LAND_SCALE / 2))
		&& (playerPos.y - (playerScale.y / 2) < blockPos.y + (LAND_SCALE / 2))
		&& (playerPos.y + (playerScale.y / 2) > blockPos.y - (LAND_SCALE / 2))
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

bool GameScene::TimingCheck(int time)
{
	if (time > timingStart || time < timingEnd /*|| (time > timingBackStart && time < timingBackEnd)*/)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameScene::Collide(XMFLOAT3& pos, XMFLOAT3 scale, const XMFLOAT3& bulPos, XMFLOAT3 bulSize, bool alive)
{
	if ((pos.x - scale.x < bulPos.x + bulSize.x)
		&& (pos.x + scale.x > bulPos.x - bulSize.x)
		&& (pos.y - scale.y < bulPos.y + bulSize.y)
		&& (pos.y + scale.y > bulPos.y - bulSize.y)
		&& (pos.z - scale.z < bulPos.z + bulSize.z)
		&& (pos.z + scale.z > bulPos.z - bulSize.z)
		&& (alive == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameScene::DropItemInfo()
{
	if (dropGun.situation == Drop)
	{
		if (Collide(playerPos, playerScale, dropGun.Pos, playerScale, dropGun.isDrop) == true)
		{
			reloadCount = 30;
			maxMagazine = BigMag;
			isReload = true;
			Reload(reloadCount, isReload, justTiming, bulCount, maxMagazine);
			dropGun.isDrop = false;
			dropGun.situation = Have;
			playerGun = Shotgun;
		}
	}
}

void GameScene::SelectAttack(int& selectAttack, int& howAttack, int skyBul, int& enemyAttackCounter)
{
	if (selectAttack != 0)
	{
		if (selectAttack < 50)
		{
			howAttack = Sinple;
		}
		else if (selectAttack < 75)
		{
			howAttack = Triple;
		}
		//元々skybul4以下だった
		else if (selectAttack < 85 && skyBul == 0)
		{
			howAttack = Bird;
		}
		else if (selectAttack < 100 && skyBul == 0)
		{
			howAttack = Star;
		}
		enemyAttackCounter = 0;
		selectAttack = 0;
	}
}

void GameScene::XMcalculation(XMFLOAT3& firstScore, XMFLOAT3 Score1, XMFLOAT3 Score2, int type)
{
	if (type == 1)
	{
		firstScore.x = Score1.x + Score2.x;
		firstScore.y = Score1.y + Score2.y;
		firstScore.z = Score1.z + Score2.z;
	}
	if (type == 2)
	{
		firstScore.x = Score1.x - Score2.x;
		firstScore.y = Score1.y - Score2.y;
		firstScore.z = Score1.z - Score2.z;
	}
	if (type == 3)
	{
		firstScore.x = Score1.x* Score2.x;
		firstScore.y = Score1.y* Score2.y;
		firstScore.z = Score1.z* Score2.z;
	}
	if (type == 4)
	{
		firstScore.x = Score1.x / Score2.x;
		firstScore.y = Score1.y / Score2.y;
		firstScore.z = Score1.z / Score2.z;
	}
}

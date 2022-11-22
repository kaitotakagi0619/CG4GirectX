#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Light.h"
#include "CollisionPrimitive.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Mapchip.h"
#include "Ease.h"

// ゲームシーン
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 10;

	struct CameraData
	{
		XMFLOAT3 e_pos; //座標
		XMFLOAT3 old_e_pos; //1フレーム前の座標
		bool is_alive; //生死


		float e_speed; //移動量
		float e_down; //下降度

		float e_acc; //加速度

		float angleX; //円運動の角度
		float angleY; //円運動の角度
		float angleZ; //円運動の角度

		float virangleX; //円運動の角度
		float virangleY; //円運動の角度
		float virangleZ; //円運動の角度

		int enemy_type; //エネミーの種類
		bool is_add; //加算するか

		bool is_fall;
	};

public: // メンバ関数

	// コンストクラタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize(DirectXCommon* dxCommon, Input* input);

	// 毎フレーム処理
	void Update();

	// 描画
	void Draw();

	// 動き
	void Move();

	// パーティクル生成
	void CreateParticles();

	void CreateLight();

	void CharactorMove(XMFLOAT3 pos);

	//カメラの動きを制御する関数
	void CircularMotionUD(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleY, const float add);

	void CircularMotionLR(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleX, const float add);

	//マップチップ1つの大きさ
	const float LAND_SCALE = 1.0f;

	//マップチップの番号
	enum MapNumber
	{
		None, Ground
	};

	enum BossAttack
	{
		Single, Side, Homing
	};

	/// <summary>
	/// //マップチップ生成
	/// </summary>
	void MapCreate(int mapNumber);

	/// <summary>
	/// //マップチップ当たり判定
	/// </summary>
	bool MapCollide(XMFLOAT3& playerPos, const XMFLOAT3& blockPos);


private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugText debugText;

	std::vector<std::vector<int>> map;
	Object3d* objBlock[map_max_y][map_max_x]; //ステージブロック

	const int enemyBul = 50;

	struct Bullet
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Size;
		XMFLOAT3 Rotation;
		bool bulFlag = false;
		bool bulShotFlag = false;
	};
	Bullet bullet[50];

	struct EnemyBullet
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Size;
		XMFLOAT3 Rotation;
		bool bulFlag = false;
		bool bulShotFlag = false;
		int type = 0;
	};
	EnemyBullet eBullet[50];

	struct SpritePos
	{
		const XMFLOAT2 center = { (WinApp::window_width / 2),(WinApp::window_height / 2) };
	};
	SpritePos spritePos;

	enum Scene
	{
		Title, Game, Win, Lose,
	};
	int SceneNum = Title;

	int		 bulCount = 30;
	int		 enemyBulCount = 20;
	XMFLOAT3 plVelocity = { 0,0,0 };
	XMFLOAT3 virVelocity = { 0,0,0 };
	bool	 bossAlive = true;
	bool	 oldBossAlive = true;
	int      enemyTimer = 0;
	int		 timing = 75;
	bool	 isJump = false;
	bool	 isJustJump = false;
	bool	 isAlive = true;
	int		 hitTimer = 0;
	float	 jCount = 0.6;
	const float jCountMax = 0.5;
	const float jCountMin = 0.3;
	XMFLOAT3	playerPos = { 0,0,0 };
	XMFLOAT3	oldPlayerPos = { 0,0,0 };
	bool		isHit = false;
	XMFLOAT3	bossPos = { 0,0,0 };
	XMFLOAT3	playerScale = { 0,0,0 };
	XMFLOAT3	targetCameraPos = { 0,0,0 };
	XMFLOAT3	oldTargetCameraPos = { 0,0,0 };
	XMFLOAT3	virCameraPos = { 0,0,0 };
	XMFLOAT3	oldVirCameraPos = { 0,0,0 };
	XMFLOAT3	centerPos = { 0, 2, 50 };
	XMFLOAT2	mousePos = { 0,0 };
	XMFLOAT4	color = { 1,1,1,0 };
	CameraData camera_data;
	bool justTiming = false;
	//残段数カウント用変数
	int lastBul = 0;
	//リロード関係
	int reloadCount = 0;
	bool isReload = false;
	int maxMagazine = 20;

	float p_x_radius;
	float p_z_radius;

	int  enemyAttackCounter = 0;

	int  selectAttack = 0;
	bool enemySinpleAttack = false;
	bool enemyTripleAttack = false;
	bool enemyHomingAttack = false;
	bool isParticle = false;
	bool setParticle = false;
	bool enemyIsAttack = false;
	int partTimer = 0;

	int  enemyMove = 0;
	bool isPlus = true;

	int  firstBossHP = 0;
	int  playerHP = 1;

	int bossAttack = 0;

	//イージング用
	const float  maxTime = 180.0f;//全体時間
	//イージングの進行度用
	float nowCount = 0.0f;
	float timeRate = 0.0f;
	bool isEase = false;

	const float titleFirstEyeY = 20;
	const float titleFirstEyeZ = -30;

	XMFLOAT3 titleEye = { 0,20,-30 };
	XMFLOAT3 titleTarget = { 0,2, 40 };

	XMFLOAT3 partVelocity = { 0,0,0 };

	int partVelocityx[50] = { 0 };
	int partVelocityy[50] = { 0 };
	int partVelocityz[50] = { 0 };
	XMFLOAT3 partPos[50] = {};
	XMFLOAT3 partPos2[50] = {};

	int clearTimer = 0;


	XMFLOAT3 cameraPos = { 0,0,0 };
	float	 cameraPosZ = 30.0f;

	// ゲームシーン用
	Camera* camera = nullptr;
	//Sprite* spriteBG = nullptr;
	Sprite* sprite[6] = { nullptr };
	Sprite* spriteNum[4] = { nullptr };
	Sprite* spriteLife[4] = { nullptr };
	Sprite* spriteMagazineUI = nullptr;
	Sprite* spritebossHP = nullptr;
	Sprite* spritebossHPFrame = nullptr;
	Sprite* reloadText = nullptr;
	Sprite* diedText = nullptr;
	ParticleManager* particleMan = nullptr;
	Light* light = nullptr;

	ReadModel* modelSkydome = nullptr;
	ReadModel* modelGround = nullptr;
	ReadModel* modelFighter = nullptr;
	ReadModel* modelFighter2 = nullptr;
	ReadModel* modelSphere = nullptr;
	ReadModel* modelCity = nullptr;
	ReadModel* modelcowgirl = nullptr;
	ReadModel* modelBox = nullptr;
	ReadModel* modelFire = nullptr;
	ReadModel* modelRed = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;
	Object3d* objFighter2 = nullptr;
	Object3d* objFighter3 = nullptr;
	Object3d* objBul[50] = { nullptr };
	Object3d* objEnemyBul[50] = { nullptr };
	Object3d* particleObject[50] = { nullptr };
	Object3d* bossEnemy = nullptr;
	Object3d* objCity = nullptr;
	Object3d* redParticleObject[50] = { nullptr };

	//FBX実装
	FbxModel* fbxModel1 = nullptr;
	FbxObject3d* fbxObject1 = nullptr;
};
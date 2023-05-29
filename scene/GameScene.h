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

	void CreateLight(int timing);

	void CharactorMove(XMFLOAT3 &pos, XMFLOAT3 &camera, XMFLOAT3 &vir, XMFLOAT3 vec , int size, int type);

	void VelocityBoost(XMFLOAT3& vel, XMFLOAT3& vel2, XMFLOAT3 camera, XMFLOAT3 vir, XMFLOAT3 pos);

	void VelocityNormal(XMFLOAT3& vel, XMFLOAT3& vel2, XMFLOAT3 camera, XMFLOAT3 vir, XMFLOAT3 pos);

	//カメラの動きを制御する関数
	void CircularMotionUD(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleY, const float add);

	void CircularMotionLR(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, float& angleZ, float& angleX, const float add);

	void EnemyMove(XMFLOAT3& epos, int& emove, bool eflag);

	void EnemyMove2(XMFLOAT3& epos, int& emove, bool eflag);

	void Reload(int& reloadCount, bool& isReload, bool& justTiming, int& bulCount, int& maxMagazine);

	void JumpStart(bool timing, int& isJump, float& jCount, bool& isJust);

	void Jump(int& isJump, float& jCount, XMFLOAT3& playerPos, XMFLOAT3& targetPos);

	void XMcalculation(XMFLOAT3& firstScore, XMFLOAT3 Score1, XMFLOAT3 Score2, int type);

	bool Collide(XMFLOAT3& pos, XMFLOAT3 scale, const XMFLOAT3& bulPos, XMFLOAT3 bulSize, bool alive);

	void DropItemInfo();

	void SelectAttack(int& selectAttack, int& howAttack, int skyBul, int& enemyAttackCounter);
	//マップチップ1つの大きさ
	const float LAND_SCALE = 1.0f;

	//マップチップの番号
	enum MapNumber
	{
		None, Ground, WallFront, WallBack, WallRight, WallLeft,
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
	bool MapCollide3D(XMFLOAT3& playerPos, const XMFLOAT3& blockPos);

	bool TimingCheck(int time);



private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugText debugText;

	std::vector<std::vector<int>> map;
	Object3d* objBlock[map_max_y][map_max_x]; //ステージブロック
	Object3d* objSecondBlock[map_max_y][map_max_x]; //ステージブロック
	Object3d* objWallFront[map_max_y][5]; //ステージブロック
	Object3d* objWallBack[map_max_y][5]; //ステージブロック
	Object3d* objWallRight[map_max_y][5]; //ステージブロック
	Object3d* objWallLeft[map_max_y][5]; //ステージブロック

	const int enemyBul = 50;
	const float circle = 10.0f;
	const float circleAdd = 1.0f;
	const int timingStart = 55;
	const int timingEnd = 7;
	const int timingBackStart = 25;
	const int timingBackEnd = 35;
	const float timingMax = 57;

	const XMFLOAT3 OutAriaPos = { 1000,-10,1000 };
	const XMFLOAT3 resetFloat3 = { 0,0,0 };

	const float AriaField = 50.0f;
	const int mousePosX = 640;
	const int mousePosY = 400;
	const int sensitivity = 50;
	const int MaxMoveVelocity = 100;
	const int MinMoveVelocity = 10;


	struct Bullet
	{
		XMFLOAT3 Pos = { 0,0,0 };
		XMFLOAT3 Size = { 0,0,0 };
		XMFLOAT3 Rotation = { 0,0,0 };
		bool bulFlag = false;
		bool bulShotFlag = false;
		float damage = 0;
	};
	Bullet bullet[50];

	struct DropGun
	{
		XMFLOAT3 Pos = { 15.0f, 1.5f,20.0f };
		XMFLOAT3 Size = { 0,0,0 };
		XMFLOAT3 Rotation = { 0,0,0 };
		float damage = 0;
		int magazine = 10;
		int situation = Drop;
		bool isDrop = true;
	};
	DropGun dropGun;

	const int BigMag = 10;
	const int MinMag = 5;

	struct EnemyBullet
	{
		XMFLOAT3 Pos = { 0,0,0 };
		XMFLOAT3 Size = { 0,0,0 };
		XMFLOAT3 Rotation = { 0,0,0 };
		XMFLOAT3 velocity = { 0,0,0 };
		float normalize = 0.0f;
		bool attackAnimation = false;
		bool bulFlag = false;
		bool bulShotFlag = false;
		int type = 0;
	};
	EnemyBullet eBullet[50];

	struct Cannon
	{
		XMFLOAT3 Pos = { 22.0f,1.5f,22.0f };
		XMFLOAT3 Size = { 0.5,0.5,0.5 };
		XMFLOAT3 Rotation = { 0,270,0 };
		XMFLOAT3 velocity = { 0,0,0 };
		float normalize = 0.0f;
		bool bulFlag = false;
		bool bulShotFlag = false;
	};
	Cannon cannon;

	struct CannonBullet
	{
		XMFLOAT3 Pos = { 0,0,0 };
		XMFLOAT3 Size = { 0.5,0.5,0.5 };
		XMFLOAT3 Rotation = { 0,0,0 };
		XMFLOAT3 velocity = { 0,0,0 };
		float normalize = 0.0f;
		bool bulFlag = false;
		bool bulShotFlag = false;
	};
	CannonBullet cannonBullet[10];

	struct SpritePos
	{
		const XMFLOAT2 center = { (WinApp::window_width / 2),(WinApp::window_height / 2) };
	};
	SpritePos spritePos;

	enum Scene
	{
		Title, Game, Win, Lose,
	};

	enum MoveType
	{
		Zero, Plus, Minus,
	};

	enum BulletSelect
	{
		Non,Sinple, Triple, Star, Bird,
	};

	enum BulletType
	{
		Stop, Streat, Anime,
	};

	enum Timing
	{
		Bad, Normal, Good,
	};
	int SceneNum = Title;

	enum GunSituation
	{
		NotExist, Drop, Have,
	};

	enum Weapon
	{
		Pistol, Shotgun,
	};

	int		 bulCount = 30;
	int		 enemyBulCount = 20;
	bool isParticleTiming = false;
	bool setParticleTiming = false;
	XMFLOAT3 plVelocity = { resetFloat3 };
	XMFLOAT3 virVelocity = { resetFloat3 };
	bool	 bossAlive = true;
	bool	 oldBossAlive = true;
	int      enemyTimer = 0;
	int		 timing = 75;
	bool	 isJust = false;
	int		 justCount = 0;
	int      isJump = Bad;
	float    viewMatrix = 0;
	bool	 isAlive = true;
	int		 hitTimer = 0;
	float	 jCount = 0.6;
	const float jCountMax = 0.5;
	const float jCountMin = 0.3;
	XMFLOAT3	playerPos = { resetFloat3 };
	XMFLOAT3	oldPlayerPos = { resetFloat3 };
	XMFLOAT3    collideSize = { 3,3,3 };
	XMFLOAT3 playerCollideScale = { resetFloat3 };
	bool		isHit = false;
	XMFLOAT3	bossPos = { resetFloat3 };
	XMFLOAT3	playerScale = { resetFloat3 };
	XMFLOAT3	targetCameraPos = { resetFloat3 };
	XMFLOAT3	oldTargetCameraPos = { resetFloat3 };
	XMFLOAT3	virCameraPos = { resetFloat3 };
	XMFLOAT3	oldVirCameraPos = { resetFloat3 };
	XMFLOAT3	centerPos = { 0, 2, 50 };
	XMFLOAT2	mousePos = { 0,0 };
	XMFLOAT4	diedTextColor = { 1,1,1,0 };
	CameraData camera_data;
	bool justTiming = false;
	bool isJustTiming = false;
	//残段数カウント用変数
	int lastBul = 0;
	//リロード関係
	int reloadCount = 0;
	bool isReload = false;
	int maxMagazine = 5;

	float p_x_radius;
	float p_z_radius;

	int  enemyAttackCounter = 0;

	//敵関係
	int  selectAttack = 0;
	bool isParticle = false;
	bool setParticle = false;
	bool enemyIsAttack = false;
	bool attackAnimation = false;
	bool fiveAttack = false;
	bool fiveAttack2 = false;
	int animeCount = 0;
	int partTimer = 0;
	int skyBul = 0;
	int howAttack = Non;

	float brinkEffectPos = -1280.0;

	int randUIX = 0;
	int randUIY = 0;

	int  enemyMove = 0;
	bool isPlus = true;

	float  firstBossHP = 0;
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

	XMFLOAT3 partVelocity = { resetFloat3 };
	XMFLOAT3 bossVelocity = { resetFloat3 };
	XMFLOAT3 bossRota = { resetFloat3 };

	float spriteVelX[50];
	float spriteVelY[50];

	int partVelocityx[50] = { 0 };
	int partVelocityy[50] = { 0 };
	int partVelocityz[50] = { 0 };
	XMFLOAT3 partPos[50] = {};
	XMFLOAT3 partPos2[50] = {};

	const float HeartMaxSize = 128.0f;
	const float HeartMinSize = 64.0f;
	const float MaxPos = 50;
	const float MinPos = 82;
	float heartPos = 50.0f;

	float timeHeart = 0.0f;
	float heartSize = 64.0f;

	XMFLOAT2 partPosition[50] = {};

	int clearTimer = 0;

	float skyDomeRota = 0.0f;
	float mapRotaY = 0.0f;

	int titleDrowCount = 0;
	bool isParticleSprite = false;

	XMFLOAT3 cameraPos = { 0,0,0 };
	float	 cameraPosZ = 30.0f;

	XMFLOAT3 pistolPos = { 0,0,0 };
	XMFLOAT3 pistolVec = { 0,0,0 };
	float pistolRotaY = 0.0f;
	float knock = 0.0f;

	int playerGun = Pistol;

	int cannonAttackCount = 0;
	int cannonCount = 0;


	XMFLOAT3 pistolVel = { 0,0,0 };

	// ゲームシーン用
	Camera* camera = nullptr;
	//Sprite* spriteBG = nullptr;
	Sprite* sprite[6] = { nullptr };
	Sprite* spriteEnterUI = { nullptr };
	Sprite* spriteNum[4] = { nullptr };
	Sprite* spriteLife[5] = { nullptr };
	Sprite* spritedamageEffect = nullptr;
	Sprite* spritebossHP = nullptr;
	Sprite* spritebossHPFrame = nullptr;
	Sprite* reloadText = nullptr;
	Sprite* diedText = nullptr;
	Sprite* brinkEffect = nullptr;
	Sprite* spriteGood = nullptr;
	Sprite* spriteBlood = nullptr;
	Sprite* spriteBul[10] = { nullptr };
	Sprite* lightParticle[50] = { nullptr };
	ParticleManager* particleMan = nullptr;
	Light* light = nullptr;

	//モデル読み込み
	ReadModel* modelSkydome = nullptr;
	ReadModel* modelGround = nullptr;
	ReadModel* modelFighter = nullptr;
	ReadModel* modelFighter2 = nullptr;
	ReadModel* modelSphere = nullptr;
	ReadModel* modelSphere2 = nullptr;
	ReadModel* modelcowgirl = nullptr;
	ReadModel* modelBox = nullptr;
	ReadModel* modelFire = nullptr;
	ReadModel* modelRed = nullptr;
	ReadModel* modelGun = nullptr;
	ReadModel* modelPistol = nullptr;
	ReadModel* modelParticle = nullptr;
	

	//3dオブジェクト宣言
	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objCannon = nullptr;
	Object3d* player = nullptr;
	Object3d* objFighter2 = nullptr;
	Object3d* objFighter3 = nullptr;
	Object3d* objBul[50] = { nullptr };
	Object3d* objEnemyBul[50] = { nullptr };
	Object3d* objCannonBul[10] = { nullptr };
	Object3d* particleObject[50] = { nullptr };
	Object3d* bossEnemy = nullptr;
	Object3d* redParticleObject[50] = { nullptr };
	Object3d* shotgun = nullptr;
	Object3d* pistol = nullptr;
	Object3d* timingParticle[30] = { nullptr };
};

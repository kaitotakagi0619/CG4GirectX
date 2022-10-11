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
#include "Audio.h"
#include "Light.h"
#include "CollisionPrimitive.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Mapchip.h"

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
	static const int debugTextTexNumber = 0;

	struct EnemyData
	{
		XMFLOAT3 e_pos; //座標
		XMFLOAT3 old_e_pos; //1フレーム前の座標

		float e_x_radius; //中心点からxの最大値まで
		float e_y_radius; //中心点からyの最大値まで

		bool is_normal; //徘徊状態
		bool is_bounce; //跳ねる状態
		bool is_catch; //捕縛状態
		bool is_alive; //生死
		bool is_grand; //地面についているか
		bool is_turn; //攻撃を受けたか

		float e_speed; //移動量
		float e_down; //下降度

		float e_acc; //加速度

		int angleX; //円運動の角度
		int angleY; //円運動の角度
		int angleZ; //円運動の角度

		int virangleX; //円運動の角度
		int virangleY; //円運動の角度
		int virangleZ; //円運動の角度

		int enemy_type; //エネミーの種類
		bool can_catch; //捕縛可能か

		bool is_add; //加算するか

		bool is_fall;

		float turn_move; //裏返るときの動き

		int escape_time; //逃げるまでの時間

		float max_rope; //ロープの最大

		float circle_radius; //円の半径
	};

public: // メンバ関数

	// コンストクラタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

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

	void CircularMotionUD(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, int& angleZ, int& angleY, const int add);

	void CircularMotionLR(XMFLOAT3& pos, const XMFLOAT3 center_pos, const float r, int& angleZ, int& angleX, const int add);


private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	struct Bullet
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Size;
		XMFLOAT3 Rotation;
		bool bulFlag = false;
		bool bulShotFlag = false;
	};
	Bullet bullet[50];

	enum Scene
	{
		Title, Game, Win, Lose,
	};
	int SceneNum = Title;

	int bulCount = 0;
	/*bool bulFlag = false;
	bool bulShotFlag = false;*/
	bool waveFlag = false;
	bool waveFlag2 = false;
	bool waveShotFlag = false;
	bool waveShotFlag2 = false;
	bool plBulFlag = false;
	bool plBulShotFlag = false;
	XMFLOAT3 plVelocity = { 0,0,0 };
	XMFLOAT3 virVelocity = { 0,0,0 };
	XMFLOAT3 virCameraPos = { 0,0,0 };
	float enemyVec = 0.1f;
	bool enemyAlive = false;
	int enemyTimer = 0;
	int timing = 0;
	bool isJump = false;
	bool isJustJump = false;
	float jCount = 0.6;
	const float jCountMax = 0.5;
	const float jCountMin = 0.3;

	EnemyData enemy_data;



	XMFLOAT3 cameraPos = { 0,0,0 };
	float cameraPosZ = 30.0f;

	// ゲームシーン用
	Camera* camera = nullptr;
	//Sprite* spriteBG = nullptr;
	Sprite* sprite[3] = { nullptr };
	Sprite* spriteMagazineUI = nullptr;
	ParticleManager* particleMan = nullptr;
	Light* light = nullptr;

	ReadModel* modelSkydome = nullptr;
	ReadModel* modelGround = nullptr;
	ReadModel* modelFighter = nullptr;
	ReadModel* modelFighter2 = nullptr;
	ReadModel* modelSphere = nullptr;
	ReadModel* modelCity = nullptr;
	ReadModel* modelcowgirl = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;
	Object3d* objFighter2 = nullptr;
	Object3d* objFighter3 = nullptr;
	Object3d* objSphere[50] = { nullptr };
	Object3d* bossEnemy = nullptr;
	Object3d* objCity = nullptr;

	//FBX実装
	FbxModel* fbxModel1 = nullptr;
	FbxObject3d* fbxObject1 = nullptr;
};
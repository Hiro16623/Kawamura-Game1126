#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <random>


//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "collision/CollisionObject.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	DeleteGO(m_collisionObject);
}

bool Enemy::Start()
{
	//乱数生成
	constexpr int MIN = -2000; //乱数範囲の最低値
	constexpr int MAX = 2000; //乱数範囲の最大値
	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数生成をする回数


	//敵の乱数。
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	int i = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (i) {
		case 0:
			m_position.x = distr(eng);
			i++;
			break;
		case 1:
			m_position.z = distr(eng);
			break;
		}
	}

	m_enemy.SetPosition(m_position);
	m_enemy.Update();

	//アニメーションを読み込む
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/Enemy/JillRun.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/Enemy/JillDead.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	m_enemy.Init("Assets/modelData/Jill.fbm/JillEnemy.tkm", m_animationClips, enAnimationClip_Num);



	//回転を設定する。
	m_enemy.SetRotation(m_rotation);
	//大きさを設定する。
	m_enemy.SetScale(m_scale);
	//移動させた座標を表示
	//m_enemy.SetPosition(m_position);

	m_enemy.Update();

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0f,			//半径。
		100.0f,			//高さ。
		m_position		//座標。
	);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//座標を敵の位置に設定する。
	collisionPosition = m_position;
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(collisionPosition,       //座標。
		Quaternion::Identity,                             //回転。
		100.0f);                                          //球の大きさ(半径)。
	//名前を付ける。
	m_collisionObject->SetName("enemy_hit");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);



	return true;
}

void Enemy::Update()
{
	//動く
	Move();
	//回転処理
	Rotation();
	if (m_enemyState == 2)
	{
		DownState();
	}
	m_enemy.Update();
}

void Enemy::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)

	{

		//キャラクターの方向を変える。

		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		//絵描きさんに回転を教える。

		m_enemy.SetRotation(m_rotation);

	}
}

void Enemy::EnemyGO()
{

}

void Enemy::Move()
{
	if (m_enemyState == 2&&m_enemy.IsPlayingAnimation() == true)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	m_playerposition = FindGO<Player>("player")->m_position;
	//エネミーを移動させる。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		//重力を0にする。
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//ちょっとだけモデルの座標を挙げる。
	modelPosition.y += 2.5f;
	//座標を設定する。
	m_enemy.SetPosition(modelPosition);
	//エネミーからプレイヤーに向かうベクトルを計算する。
	Vector3 diff = m_playerposition - m_position;

	//ベクトルを正規化する。
	diff.Normalize();
	//移動速度を設定する。
	m_moveSpeed = diff * 50.0f;

	//Bulletが作成した、弾のヒット判定用のコリジョンの配列を取得。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("fmj_hit");

	//for文で配列を回す。
	for (auto collision : collisions)
	{

		//弾のコリジョンと敵のキャラこんが。
		//衝突していたら。
		if (collision->IsHit(m_charaCon) == true)
		{
			m_enemy.PlayAnimation(enAnimationClip_Down);
			m_enemyState = 2;
			DownState();
			//DeleteGO(this);
		}
	}

	//setpositionで動いた敵の当たり判定の反映
	m_collisionObject->SetPosition(m_position);
	//動いた敵の描画
	m_enemy.SetPosition(m_position);

}
void Enemy::DownState()
{
	if (m_enemy.IsPlayingAnimation() == false)
	{
		auto game = FindGO<Game>("game");
		FindGO<Game>("game")->m_enemycount=-1;
        FindGO<Game>("game")->m_clearcount=-1;
		DeleteGO(this);
	}
}
void Enemy::ManageState()
{
	
}

void Enemy::PlayAnimation()
{
	//switch文。
	switch (m_enemyState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//走りアニメーションを再生する。
		m_enemy.PlayAnimation(enAnimationClip_Run);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//攻撃アニメーションを再生する。
		m_enemy.PlayAnimation(enAnimationClip_Attack);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//ダウンアニメーションを再生する。
		m_enemy.PlayAnimation(enAnimationClip_Down);
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_enemy.Draw(rc);
}

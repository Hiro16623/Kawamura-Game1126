#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "collision/CollisionObject.h"

Bullet::Bullet()
{

}
Bullet::~Bullet()
{
	DeleteGO(m_collisionObject);
}

bool Bullet::Start()
{
	//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
	m_position = FindGO<Player>("player")->m_position;
	//弾のモデルを読み込む
	m_modelRender.Init("Assets/modelData/TestBullet.tkm");
	m_modelRender.SetScale({ 0.5f,0.5f,0.5f });
	m_position.y = 50.0f;
	//FindGOで読み込んで入れたm_positionに弾を配置する。
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	//コライダーを初期化。
	m_sphereCollider.Create(48.0f);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	//半径の数値を変えるとコライダーの円の大きさが変わる
	m_collisionObject->CreateSphere(
		m_position,                     //座標。
		Quaternion::Identity,           //回転。
		10.0f                           //半径。
	);
	//名前をつける
	m_collisionObject->SetName("fmj_hit");
	//自動で削除を無効「DeleteGOで消去する必要がある」
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Bullet::Update() //常に1秒間に60回呼び出される
{
	Move();
	Moji();
	//絵描きさんの更新処理。
	m_modelRender.Update();
}

void Bullet::Move()
{
	if (m_deletefmjtimer >= 3.0f)
	{
		DeleteGO(this);
	}

	m_deletefmjtimer += g_gameTime->GetFrameDeltaTime();


	//弾の座標にmovespeedを+してやって、弾を動かす
	m_position += m_moveSpeed * 5.0f;
	m_modelRender.SetPosition(m_position);

	//Setpositionで動いた弾の当たり判定
	m_collisionObject->SetPosition(m_position);
	//プレイヤの座標と弾の距離のベクトルを求める
	Vector3 deff = m_playerposition - m_position;
}

void Bullet::Moji()
{
	int x = m_position.x;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"x:%d", x / 50);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-200.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.0f);

	int y = m_position.y;
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"y:%d", y / 50);

	//表示するテキストを設定。
	m_fontRender2.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender2.SetPosition(Vector3(-200.0f, 150.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender2.SetScale(1.0f);

	int z = m_position.z;
	wchar_t wcsbuf3[256];
	swprintf_s(wcsbuf3, 256, L"z:%d", z / 50);

	//表示するテキストを設定。
	m_fontRender1.SetText(wcsbuf3);
	//フォントの位置を設定。
	m_fontRender1.SetPosition(Vector3(-200.0f, 100.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender1.SetScale(1.0f);
}

void Bullet::Render(RenderContext& rc)
{
	//描画する。
	m_fontRender.Draw(rc);
	m_fontRender1.Draw(rc);
	m_fontRender2.Draw(rc);
	m_modelRender.Draw(rc);
}
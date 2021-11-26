#pragma once
//クラス宣言
class collisionObject;

class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	//最初に一回だけ実行
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//文字
	void Moji();

	FontRender m_fontRender;                       //文字の描画
	FontRender m_fontRender1;                     //文字の描画２
	FontRender m_fontRender2;                    //文字の描画３
	SphereCollider m_sphereCollider;		   //円型のコライダー。
	Vector3 m_playerposition;                  //プレイヤーの位置
	Vector3 m_position;			              //座標。
	Vector3 m_moveSpeed;					 //移動速度。
	Quaternion m_rotation;                  //クウォータニオン
	ModelRender m_modelRender;             //モデルレンダー
	CollisionObject* m_collisionObject;    //CollisionObject。

	float m_deletefmjtimer = 0.0f;
}; 


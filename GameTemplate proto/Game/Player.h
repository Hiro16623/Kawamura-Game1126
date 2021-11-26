#pragma once
//クラス宣言
class Bullet;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Turn();

	ModelRender m_modelRender;
	Vector3 m_position;						//座標。
	CharacterController m_charaCon;			//キャラクターコントローラー。
	Vector3 m_moveSpeed;					//移動速度。
	Quaternion m_rotation;					//クォータニオン。
	Bullet* m_bullet;                   //弾

	Vector3 m_forward;
	Vector3 m_toForward = Vector3(0.0f, 0.0f, 1.0f);

	float m_timer = 1.0f;
};


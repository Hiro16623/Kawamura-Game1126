#pragma once
class Player;

class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	void DownState();
	void EnemyGO();

	enum EnAnimationClip {
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Down,
		enAnimationClip_Num,
	};

	CollisionObject* m_collisionObject;
	AnimationClip  m_animationClips[enAnimationClip_Num];	 //アニメーションクリップ。
	SphereCollider m_sphereCollider;                        //円型のコライダー。
	ModelRender m_enemy;                                   //モデルレンダ
	Vector3 m_position;                                   //座標。
	Vector3	m_moveSpeed;                                 //移動速度
	Vector3 m_scale = { 1.0f,1.0f,1.0f };               //大きさ
	Vector3                 m_positionlength;          //位置の長さ
	Vector3 m_playerposition;                         //プレイヤーの位置
	Quaternion m_rotation;                           //回転
	CharacterController	m_charaCon;                 //キャラクターコントロール
	PhysicsStaticObject m_physicsStaticObject;     //静的物理オブジェクト。
	Vector3 m_firstPosition;
	
	int hitdamagecooltime = false;
	int m_enemyState = 0;
};


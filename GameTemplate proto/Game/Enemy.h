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
	AnimationClip  m_animationClips[enAnimationClip_Num];	 //�A�j���[�V�����N���b�v�B
	SphereCollider m_sphereCollider;                        //�~�^�̃R���C�_�[�B
	ModelRender m_enemy;                                   //���f�������_
	Vector3 m_position;                                   //���W�B
	Vector3	m_moveSpeed;                                 //�ړ����x
	Vector3 m_scale = { 1.0f,1.0f,1.0f };               //�傫��
	Vector3                 m_positionlength;          //�ʒu�̒���
	Vector3 m_playerposition;                         //�v���C���[�̈ʒu
	Quaternion m_rotation;                           //��]
	CharacterController	m_charaCon;                 //�L�����N�^�[�R���g���[��
	PhysicsStaticObject m_physicsStaticObject;     //�ÓI�����I�u�W�F�N�g�B
	Vector3 m_firstPosition;
	
	int hitdamagecooltime = false;
	int m_enemyState = 0;
};


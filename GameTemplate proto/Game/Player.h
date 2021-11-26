#pragma once
//�N���X�錾
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
	Vector3 m_position;						//���W�B
	CharacterController m_charaCon;			//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;					//�ړ����x�B
	Quaternion m_rotation;					//�N�H�[�^�j�I���B
	Bullet* m_bullet;                   //�e

	Vector3 m_forward;
	Vector3 m_toForward = Vector3(0.0f, 0.0f, 1.0f);

	float m_timer = 1.0f;
};


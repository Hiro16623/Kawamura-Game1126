#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <random>


//CollisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
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
	//��������
	constexpr int MIN = -2000; //�����͈͂̍Œ�l
	constexpr int MAX = 2000; //�����͈͂̍ő�l
	constexpr int RAND_NUMS_TO_GENERATE = 2;//���������������


	//�G�̗����B
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

	//�A�j���[�V������ǂݍ���
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/Enemy/JillRun.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/Enemy/JillDead.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	m_enemy.Init("Assets/modelData/Jill.fbm/JillEnemy.tkm", m_animationClips, enAnimationClip_Num);



	//��]��ݒ肷��B
	m_enemy.SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_enemy.SetScale(m_scale);
	//�ړ����������W��\��
	//m_enemy.SetPosition(m_position);

	m_enemy.Update();

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,			//���a�B
		100.0f,			//�����B
		m_position		//���W�B
	);

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//���W��G�̈ʒu�ɐݒ肷��B
	collisionPosition = m_position;
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(collisionPosition,       //���W�B
		Quaternion::Identity,                             //��]�B
		100.0f);                                          //���̑傫��(���a)�B
	//���O��t����B
	m_collisionObject->SetName("enemy_hit");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);



	return true;
}

void Enemy::Update()
{
	//����
	Move();
	//��]����
	Rotation();
	if (m_enemyState == 2)
	{
		DownState();
	}
	m_enemy.Update();
}

void Enemy::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)

	{

		//�L�����N�^�[�̕�����ς���B

		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		//�G�`������ɉ�]��������B

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
	//�G�l�~�[���ړ�������B
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		//�d�͂�0�ɂ���B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//������Ƃ������f���̍��W��������B
	modelPosition.y += 2.5f;
	//���W��ݒ肷��B
	m_enemy.SetPosition(modelPosition);
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = m_playerposition - m_position;

	//�x�N�g���𐳋K������B
	diff.Normalize();
	//�ړ����x��ݒ肷��B
	m_moveSpeed = diff * 50.0f;

	//Bullet���쐬�����A�e�̃q�b�g����p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("fmj_hit");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{

		//�e�̃R���W�����ƓG�̃L�������񂪁B
		//�Փ˂��Ă�����B
		if (collision->IsHit(m_charaCon) == true)
		{
			m_enemy.PlayAnimation(enAnimationClip_Down);
			m_enemyState = 2;
			DownState();
			//DeleteGO(this);
		}
	}

	//setposition�œ������G�̓����蔻��̔��f
	m_collisionObject->SetPosition(m_position);
	//�������G�̕`��
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
	//switch���B
	switch (m_enemyState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//����A�j���[�V�������Đ�����B
		m_enemy.PlayAnimation(enAnimationClip_Run);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�U���A�j���[�V�������Đ�����B
		m_enemy.PlayAnimation(enAnimationClip_Attack);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�_�E���A�j���[�V�������Đ�����B
		m_enemy.PlayAnimation(enAnimationClip_Down);
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_enemy.Draw(rc);
}

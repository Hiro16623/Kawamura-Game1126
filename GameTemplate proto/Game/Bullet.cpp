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
	//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
	m_position = FindGO<Player>("player")->m_position;
	//�e�̃��f����ǂݍ���
	m_modelRender.Init("Assets/modelData/TestBullet.tkm");
	m_modelRender.SetScale({ 0.5f,0.5f,0.5f });
	m_position.y = 50.0f;
	//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	//�R���C�_�[���������B
	m_sphereCollider.Create(48.0f);

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	//���a�̐��l��ς���ƃR���C�_�[�̉~�̑傫�����ς��
	m_collisionObject->CreateSphere(
		m_position,                     //���W�B
		Quaternion::Identity,           //��]�B
		10.0f                           //���a�B
	);
	//���O������
	m_collisionObject->SetName("fmj_hit");
	//�����ō폜�𖳌��uDeleteGO�ŏ�������K�v������v
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Bullet::Update() //���1�b�Ԃ�60��Ăяo�����
{
	Move();
	Moji();
	//�G�`������̍X�V�����B
	m_modelRender.Update();
}

void Bullet::Move()
{
	if (m_deletefmjtimer >= 3.0f)
	{
		DeleteGO(this);
	}

	m_deletefmjtimer += g_gameTime->GetFrameDeltaTime();


	//�e�̍��W��movespeed��+���Ă���āA�e�𓮂���
	m_position += m_moveSpeed * 5.0f;
	m_modelRender.SetPosition(m_position);

	//Setposition�œ������e�̓����蔻��
	m_collisionObject->SetPosition(m_position);
	//�v���C���̍��W�ƒe�̋����̃x�N�g�������߂�
	Vector3 deff = m_playerposition - m_position;
}

void Bullet::Moji()
{
	int x = m_position.x;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"x:%d", x / 50);

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-200.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.0f);

	int y = m_position.y;
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"y:%d", y / 50);

	//�\������e�L�X�g��ݒ�B
	m_fontRender2.SetText(wcsbuf2);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender2.SetPosition(Vector3(-200.0f, 150.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender2.SetScale(1.0f);

	int z = m_position.z;
	wchar_t wcsbuf3[256];
	swprintf_s(wcsbuf3, 256, L"z:%d", z / 50);

	//�\������e�L�X�g��ݒ�B
	m_fontRender1.SetText(wcsbuf3);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender1.SetPosition(Vector3(-200.0f, 100.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender1.SetScale(1.0f);
}

void Bullet::Render(RenderContext& rc)
{
	//�`�悷��B
	m_fontRender.Draw(rc);
	m_fontRender1.Draw(rc);
	m_fontRender2.Draw(rc);
	m_modelRender.Draw(rc);
}
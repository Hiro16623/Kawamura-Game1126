#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

Player::Player()
{

}
Player::~Player()
{

}

bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,			//���a�B
		100.0f,			//�����B
		m_position		//���W�B
	);

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/fpsarms2.tkm");

	m_position.y = 100.0f;

	return true;
}

void Player::Update()
{
	//�ړ������B
	Move();
	//���񏈗��B
	Turn();

	//���f�����X�V�B
	m_modelRender.Update();
}

void Player::Move()
{
	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 200.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 200.0f;		//�E�����ւ̈ړ����x�����Z�B
	if (g_pad[0]->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
	}
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}

	//�e�̔��ˊԊu
	m_timer += g_gameTime->GetFrameDeltaTime();

	if(g_pad[0]->IsTrigger(enButtonRB2) && m_timer >= 0.4f)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");
		m_bullet->m_moveSpeed = g_camera3D->GetForward();

		m_timer = 0.0f;
	}

	//���W��ݒ�B
	m_modelRender.SetPosition(m_position + Vector3(0.0f, 72.0f, 0.0f));
}

void Player::Turn()
{
	// �J�����ƈꏏ�ɉ�]���������̂ŁA�J�����̉�]�s��������Ă���B
	Matrix cameraRot = g_camera3D->GetCameraRotation();
	// ��]�s�񂩂�N�H�[�^�j�I�������
	Quaternion qRot;
	qRot.SetRotation(cameraRot);
	m_modelRender.SetRotation(qRot);
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
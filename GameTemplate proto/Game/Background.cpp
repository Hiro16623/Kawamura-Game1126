#include "stdafx.h"
#include "Background.h"

Background::Background()
{

}

Background::~Background()
{

}

bool Background::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/stagets.tkm");
	/*//Y����180����]�B
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	//��]��ݒ�B
	m_modelRender.SetRotation(rot);
	//�傫����ݒ�B
	m_modelRender.SetScale({ 1.5f,1.5f,1.5f });
	//�傫���A��]�̕ύX�𔽉f�����邽�߂ɁA���f�����X�V�B
	m_modelRender.Update();*/

	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//�R���C�_�[�̉���
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Background::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
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
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/stagets.tkm");
	/*//Y軸に180°回転。
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	//回転を設定。
	m_modelRender.SetRotation(rot);
	//大きさを設定。
	m_modelRender.SetScale({ 1.5f,1.5f,1.5f });
	//大きさ、回転の変更を反映させるために、モデルを更新。
	m_modelRender.Update();*/

	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//コライダーの可視化
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Background::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
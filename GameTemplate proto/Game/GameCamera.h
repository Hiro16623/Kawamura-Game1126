#pragma once
class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Player* m_player = nullptr;		//�v���C���[�B
	Vector3 m_toCameraPos = Vector3::One;
};

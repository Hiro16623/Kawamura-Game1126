#pragma once
//�N���X�錾
class collisionObject;

class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	//�ŏ��Ɉ�񂾂����s
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//����
	void Moji();

	FontRender m_fontRender;                       //�����̕`��
	FontRender m_fontRender1;                     //�����̕`��Q
	FontRender m_fontRender2;                    //�����̕`��R
	SphereCollider m_sphereCollider;		   //�~�^�̃R���C�_�[�B
	Vector3 m_playerposition;                  //�v���C���[�̈ʒu
	Vector3 m_position;			              //���W�B
	Vector3 m_moveSpeed;					 //�ړ����x�B
	Quaternion m_rotation;                  //�N�E�H�[�^�j�I��
	ModelRender m_modelRender;             //���f�������_�[
	CollisionObject* m_collisionObject;    //CollisionObject�B

	float m_deletefmjtimer = 0.0f;
}; 


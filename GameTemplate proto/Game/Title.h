#pragma once
#include "sound/SoundSource.h"

//�^�C�g���B

class Title : public IGameObject
{
public:
    Title();
    ~Title();

    bool Start();
    //�`��֐��B
    void Render(RenderContext& rc);
    //�X�V�����B
    void Update();

    //�X�v���C�g�����_�\�B
    SpriteRender spriteRender;
    SoundSource* bgm;
};


#include "stdafx.h"
#include "Title.h"
#include "Game.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
    spriteRender.Init("Assets/modelData/TestTitle2.dds", 1280.0f, 720.0f);

    g_soundEngine->ResistWaveFileBank(1, "Assets/modelData/sound/Gunsoundtitle.wav");

    return true;
}

void Title::Update()
{
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        //SoundSource�̃C���X�^���X���쐬����B
        SoundSource* se = NewGO<SoundSource>(0);
        se->Init(1);
        //���ʉ��̓��[�v�����Ȃ��̂ŁAfalse�ɂ���B
        se->Play(false);
        //����
        se->SetVolume(10.0f);

        NewGO<Game>(0,"game");
        DeleteGO(this);
    }
}

void Title::Render(RenderContext& rc)
{
    //�摜��`�悷��B
    spriteRender.Draw(rc);
}
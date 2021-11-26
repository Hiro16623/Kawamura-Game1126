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
        //SoundSourceのインスタンスを作成する。
        SoundSource* se = NewGO<SoundSource>(0);
        se->Init(1);
        //効果音はループさせないので、falseにする。
        se->Play(false);
        //音量
        se->SetVolume(10.0f);

        NewGO<Game>(0,"game");
        DeleteGO(this);
    }
}

void Title::Render(RenderContext& rc)
{
    //画像を描画する。
    spriteRender.Draw(rc);
}
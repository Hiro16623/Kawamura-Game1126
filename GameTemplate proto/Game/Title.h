#pragma once
#include "sound/SoundSource.h"

//タイトル。

class Title : public IGameObject
{
public:
    Title();
    ~Title();

    bool Start();
    //描画関数。
    void Render(RenderContext& rc);
    //更新処理。
    void Update();

    //スプライトレンダ―。
    SpriteRender spriteRender;
    SoundSource* bgm;
};


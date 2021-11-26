#include "stdafx.h"
#include "GameClear.h"
#include"Title.h"
#include "Game.h"
#include "Player.h"

GameClear::GameClear()
{
	//ゲームクリアの画像を読み込む。
	spriteRender.Init("Assets/modelData/TestTitle2.dds", 1280.0f, 720.0f);
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{

}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
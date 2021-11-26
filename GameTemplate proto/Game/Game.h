#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Background;
class title;
class Enemy;
class skyCube;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void EnemyGO();
	void Enemyrand();

	Player* m_player = nullptr;				//プレイヤー。
	Background* m_background = nullptr;		//背景。
	GameCamera* m_gameCamera = nullptr;		//ゲームカメラ。
	Enemy* m_enemy;

	int m_enemycount = 0;
	int m_clearcount = 0;
	int m_enemygocount = 0;

private:
	ModelRender m_modelRender;
	float m_enemyrandtimer;
};


#include "stdafx.h"
#include "Game.h"

#include"Background.h"
#include"GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "nature/SkyCube.h"
#include "Title.h"

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -600.0f });
	
	SkyCube* m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetScale({ 1000.0f });

		Enemy* enemy = NewGO<Enemy>(0, "enemy");
		enemy->m_firstPosition = enemy->m_position;

		Enemy* enemy2 = NewGO<Enemy>(0, "enemy");
		enemy2->m_firstPosition = enemy2->m_position;

		Enemy* enemy3 = NewGO<Enemy>(0, "enemy");
		enemy3->m_firstPosition = enemy3->m_position;

	//m_enemy = NewGO<Enemy>(0, "Enemy");
	m_player = NewGO<Player>(0, "player");
	m_background = NewGO<Background>(0, "background");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	return true;
}
void Game::EnemyGO()
{
	for (int m = 0; m < 3; m++)
	{
		Enemy* enemy = NewGO<Enemy>(0, "enemy");
		enemy->m_firstPosition = enemy->m_position;
		m_enemycount++;
		m_enemygocount++;
		m_clearcount++;
	}
}
void Game::Enemyrand()
{
	m_enemyrandtimer += g_gameTime->GetFrameDeltaTime();
	//‘O‚É“G‚ªoŒ»‚µ‚Ä‚©‚ç5•bˆÈãŒo‚Á‚Ä‚¢‚Ä‚©‚Â“G‚Ì”‚ª3ˆÈ‰º‚È‚ç“G‚ðoŒ»‚³‚¹‚éB
	if (m_enemyrandtimer >= 5.0f && m_enemycount <= 3&& m_enemygocount <=10)
	{
		EnemyGO();
		m_enemyrandtimer = 0.0f;
	}
}
void Game::Update()
{
	Enemyrand();
	if (m_enemygocount <= 10&&m_clearcount==0)
	{
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{

}
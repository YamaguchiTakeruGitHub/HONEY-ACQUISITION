#pragma once
#include "..\Player\Player.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>
#include <ctime>
#include <cstdlib>

struct EnemyThreeData
{
	static const int Pos_X = 13;				//�G�l�~�[2  							��X���W��
	static const int Pos_Y = 16;				//�G�l�~�[2  							��Y���W��
	static const int moveSpeed = 1;					//�G�l�~�[  							�����x��
	static const int HitDamagedHandlePos_X = 0;					//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��X���W��
	static const int HitDamagedHandlePos_Y = 0;					//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��Y���W��
	static const int AfterTakingDamegeTime = 0;					//�_���[�W���o���Ԃ�					�������l��
	static const int FlashPoint = 0;					//�_���[�W���o�̍ۂ̃t���b�V��			�������l��
	static const int PlayerPosReset_X = 14;				//�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��X���W��
	static const int PlayerPosReset_Y = 26;				//�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��Y���W��
	static const int BUFTime = 60;				//�v���C���[���p���[�t�[�h���擾������	����~�o�t��
};

struct NodeThree
{
	int x;
	int y;
	int g;
	int h;
	NodeThree* parent;

	NodeThree(int x, int y, int g, int h, NodeThree* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

	int f() const { return g + h; }

};

class PowerFeed;
class Player;
class Enemy;
class EnemyTwo;
class EnemyThree
{
public:
	EnemyThree();
	~EnemyThree();

	void Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo);
	void Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo);
	void Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo);
	void Final();
	void enemyThreeSetHandle(int* handle) { ThreeEnemyGraphHandle = *handle; }

	void MoveTowardsPlayerThree(Player& player);								//�G�P���v���C���[��ǂ�������֐�
	bool IsWallThree(int x, int y);									//�G�l�~�[���ǂ𔻒f���邽�߂̊֐�
	int CalculateHeuristicThree(int x1, int y1, int x2, int y2);				//�v���C���[�܂ł̋����𔻒f����w���X�e�b�N�֐�
	std::vector<NodeThree*> AStarThree(int startX, int startY, int goalX, int GoalY); //A�X�^�[�A���S���Y��
	


	int EnemyThreeCoordinate_X;
	int EnemyThreeCoordinate_Y;

	int ThreeMoveSpeed;

	int ThreeHitDamePos_X;
	int ThreeHitDamePos_Y;

	int ThreeEnemyGraphHandle;
	int ThreeHitDamegeGraphHandle;
	int ThreeGameOverGraphHandle;
	int ThreeBUFEnemyHandle;

	int ThreeDameSoundHandle;

	int ThreeHitDameTime;
	int ThreeHitPointFlash;

	bool ThreeisGameOver;

	int ThreePowerFeedBUFTime;
	bool ThreeBUF;
private:


};



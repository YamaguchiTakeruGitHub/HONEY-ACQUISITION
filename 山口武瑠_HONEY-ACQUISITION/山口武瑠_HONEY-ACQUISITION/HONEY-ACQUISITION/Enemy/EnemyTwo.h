#pragma once
#include "..\Player\Player.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>
#include <ctime>
#include <cstdlib>

struct EnemyTwoData
{
	static const int Pos_X				   = 13;				//�G�l�~�[2  							��X���W��
	static const int Pos_Y				   = 16;				//�G�l�~�[2  							��Y���W��
	static const int moveSpeed			   = 1;					//�G�l�~�[  							�����x��
	static const int HitDamagedHandlePos_X = 0;					//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��X���W��
	static const int HitDamagedHandlePos_Y = 0;					//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��Y���W��
	static const int AfterTakingDamegeTime = 0;					//�_���[�W���o���Ԃ�					�������l��
	static const int FlashPoint			   = 0;					//�_���[�W���o�̍ۂ̃t���b�V��			�������l��
	static const int PlayerPosReset_X	   = 14;				//�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��X���W��
	static const int PlayerPosReset_Y	   = 26;				//�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��Y���W��
	static const int BUFTime			   = 60;				//�v���C���[���p���[�t�[�h���擾������	����~�o�t��
};

struct NodeTwo
{
	int x;
	int y;
	int g;
	int h;
	NodeTwo* parent;

	NodeTwo(int x, int y, int g, int h, NodeTwo* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

	int f() const { return g + h; }

};

class PowerFeed;
class Player;
class Enemy;
class EnemyThree;
class EnemyTwo
{
public:
	EnemyTwo();
	~EnemyTwo();

	void Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree);
	void Final();
	void enemyTwoSetHandle(int* handle) { TwoEnemyGraphHandle = *handle; }

	void MoveTowardsPlayerTwo(Player& player);								//�G�P���v���C���[��ǂ�������֐�
	bool IsWallTwo(int x, int y);									//�G�l�~�[���ǂ𔻒f���邽�߂̊֐�
	int CalculateHeuristicTwo(int x1, int y1, int x2, int y2);				//�v���C���[�܂ł̋����𔻒f����w���X�e�b�N�֐�
	std::vector<NodeTwo*> AStarTwo(int startX, int startY, int goalX, int GoalY); //A�X�^�[�A���S���Y��

	int EnemyTwoCoordinate_X;
	int EnemyTwoCoordinate_Y;

	int TwoMoveSpeed;

	int TwoHitDamePos_X;
	int TwoHitDamePos_Y;

	int TwoEnemyGraphHandle;
	int TwoHitDamegeGraphHandle;
	int TwoGameOverGraphHandle;
	int TwoBUFEnemyHandle;

	int TwoDameSoundHandle;

	int TwoHitDameTime;
	int TwoHitPointFlash;

	bool TwoisGameOver;

	int TwoPowerFeedBUFTime;
	bool TwoBUF;
private:
	

};


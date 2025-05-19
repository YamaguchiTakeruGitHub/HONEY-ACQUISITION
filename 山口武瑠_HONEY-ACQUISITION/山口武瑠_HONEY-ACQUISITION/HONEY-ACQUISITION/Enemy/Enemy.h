#pragma once
#include "..\Player\Player.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <thread>

struct Node
{
	int x;
	int y;
	int g;
	int h;
	Node* parent;

	Node(int x, int y, int g, int h, Node* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

	int f() const { return g + h; }

};

struct EnemyData
{
	static const int Pos_X				    = 13;								//�G�l�~�[  							��X���W��
	static const int Pos_Y				    = 16;								//�G�l�~�[  							��Y���W��
	static const int TwoPos_X			    = 13;								//�G�l�~�[2  							��X���W��
	static const int TwoPos_Y			    = 16;								//�G�l�~�[2  							��Y���W��
	static const int moveSpeed			    =  1;								//�G�l�~�[  							�����x��
	static const int HitDamagedHandlePos_X  =  0;								//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��X���W��
	static const int HitDamagedHandlePos_Y  =  0;								//�v���C���[�ƏՓ˂����ۂ̉摜�n���h��	��Y���W��
	static const int AfterTakingDamegeTime  =  0;								//�_���[�W���o���Ԃ�					�������l��
	static const int FlashPoint			    =  0;								//�_���[�W���o�̍ۂ̃t���b�V��			�������l��
	static const int PlayerPosReset_X	    = 14;							    //�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��X���W��
	static const int PlayerPosReset_Y	    = 26;							    //�Փ˂����ۂ̃v���C���[�̍��W���Z�b�g	��Y���W��
	static const int BUFTime				= 60;								//�v���C���[���p���[�t�[�h���擾������	����~�o�t��
	static const int DameTime				=  0;
};

class PowerFeed;
class Player;
class EnemyTwo;
class EnemyThree;
class Enemy
{
public:
		 Enemy					();												//EnemyConstructor
		~Enemy					();												//EnemyDestructor
	void Init					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//������
	void Update					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//�X�V
	void Draw					(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree);			//�`��
	void Final					();												//�I��
	void enemyBlinkySetHandle	(int* handle) { EnemyGraphHandle = *handle; }	//SceneMain�ŎQ�ƊǗ�����摜�n���h���֐�
	void MoveTowardsPlayer		(Player& player);								//�G�P���v���C���[��ǂ�������֐�
	bool IsWall					(int x, int y);									//�G�l�~�[���ǂ𔻒f���邽�߂̊֐�
	int CalculateHeuristic		(int x1, int y1, int x2, int y2);				//�v���C���[�܂ł̋����𔻒f����w���X�e�b�N�֐�
	std::vector<Node*> AStar	(int startX, int startY, int goalX, int GoalY); //A�X�^�[�A���S���Y��

	int EnemyCoordinate_Y;
	int EnemyCoordinate_X;

	int HitDamePos_X;
	int HitDamePos_Y;

	int EnemyGraphHandle;
	int HitDamegeGraphHandle;
	int GameOverGraphHandle;
	
	int DameSoundHandle;
	
	int HitDameTime;
	int HitPointFlash;
	
	float MoveSpeed;
	
	bool isGameOver;

	int BUFEnemyHandle;

	int PowerFeedBUFTime;
	bool BUF;

};




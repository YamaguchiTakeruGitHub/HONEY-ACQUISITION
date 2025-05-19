#include "DxLib.h"
#include "../Game.h"
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../Feed/PowerFeed.h"
#include "..\Enemy\EnemyTwo.h"
#include "../Enemy/EnemyThree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>



Enemy::Enemy() :	
	EnemyCoordinate_Y		(EnemyData::Pos_Y),							//�G�́�Y���W��������
	EnemyCoordinate_X		(EnemyData::Pos_X),							//�G�́�X���W��������
	MoveSpeed				(EnemyData::moveSpeed),						//�G�́����x��������
	HitDamePos_X			(EnemyData::HitDamagedHandlePos_X),			//�摜�n���h����HitDamegeHandle���́�X���W��������
	HitDamePos_Y			(EnemyData::HitDamagedHandlePos_Y),			//�摜�n���h����HitDamegeHandle���́�Y���W��������
	HitDameTime				(EnemyData::AfterTakingDamegeTime),			//�v���C���[�ƓG�����������ۂ́����o���ԁ�������
	HitPointFlash			(EnemyData::FlashPoint),					//�摜�n���h����HitDamegeHandle���́��t���b�V�����o��������
	isGameOver				(false),									//�Q�[���I�[�o�[�𔻒肷�邽�߂́��t���O��������
	BUF						(false),									//�o�t�t���O
	HitDamegeGraphHandle	(LoadGraph("img/Damage.png")),				//HitDamegeHandle���O���t�n���h�����̏�����
	EnemyGraphHandle		(LoadGraph("img/brownbear.png")),			//m_enemyBlinkyHandle���O���t�n���h�����̏�����
	GameOverGraphHandle		(LoadGraph("img/GAMEOVERTEXT.png")),		//m_GameOverHandle���O���t�n���h�����̏�����
	BUFEnemyHandle			(LoadGraph("img/brownbearSleepOne.png")),	//�o�t���ʂ���������ۂ̓G���O���t�n���h�����̏�����
	DameSoundHandle			(LoadSoundMem("img/Dameg.mp3")),			//DameSoundHandle���T�E���h�n���h�����̏�����
	PowerFeedBUFTime		(EnemyData::BUFTime)						//�v���C���[���p���[�a���擾�����ۂ̃o�t������
{
}

Enemy::~Enemy()
{
	DeleteGraph(EnemyGraphHandle);
	DeleteGraph(GameOverGraphHandle);
	DeleteGraph(HitDamegeGraphHandle);
	DeleteSoundMem(DameSoundHandle);
}

void Enemy::Init(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	EnemyCoordinate_Y	  = EnemyData::Pos_Y;
	EnemyCoordinate_X	  = EnemyData::Pos_X;
	MoveSpeed			  = EnemyData::moveSpeed;
	HitDamePos_X		  = EnemyData::HitDamagedHandlePos_X;
	HitDamePos_Y		  = EnemyData::HitDamagedHandlePos_Y;
	HitPointFlash	  	  = EnemyData::FlashPoint;
	HitDameTime			  = EnemyData::DameTime;
	isGameOver			  = false;
	BUF					  = false;
	HitDamegeGraphHandle  = LoadGraph("img/Damage.png");
	EnemyGraphHandle	  = LoadGraph("img/brownbear.png");
	GameOverGraphHandle	  = LoadGraph("img/GAMEOVERTEXT.png");
	BUFEnemyHandle        = LoadGraph("img/brownbearSleepOne.png");
	DameSoundHandle		  = LoadSoundMem("sound/Dameg.mp3");
}

void Enemy::Update(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		BUF = true;
	}
	//�G�̏���
	if (player.PlayerPos_X >= EnemyCoordinate_X + 1 || player.PlayerPos_X <= EnemyCoordinate_X - 1 || player.PlayerPos_Y >= EnemyCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyCoordinate_Y - 1) //�G�̍��p���O���ɂ����Ƃ��̏���
	{
		if (BUF == true)
		{
			PowerFeedBUFTime--;

			if (BUF == true)
			{
				if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
				{
					PowerFeedBUFTime = 30;
				}
			}

			//�l��10�ɂȂ�����O�ɂ���
			if (PowerFeedBUFTime == 0)
			{
				PowerFeedBUFTime = 60;
				BUF = false;
			}
		}

		if (BUF == false)
		{
			MoveTowardsPlayer(player); //A*�A���S���Y�����g�p�����v���C���[�̒ǐ�
		}

		if (player.ClearManager != 244)
		{
			if (player.PlayerPos_X >= EnemyCoordinate_X && player.PlayerPos_X <= EnemyCoordinate_X) //�����蔻�聃�w���W��
			{
				if (player.PlayerPos_Y >= EnemyCoordinate_Y && player.PlayerPos_Y <= EnemyCoordinate_Y) //�����蔻�聃�w���W��
				{
					HitDameTime = 10; //�����蔻���ʉ߂����ۂ�HitDameTime�ɒl�[��10����
					player.PlayerResidue -= 1; //�v���C���[�̎c�@������炷

					if (player.PlayerResidue == 2) //�v���C���[�̎c�@���Q�ɂȂ����Ƃ�
					{
						/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
						player.PlayerPos_X = EnemyData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyData::PlayerPosReset_Y;

						EnemyCoordinate_Y = EnemyData::Pos_Y;
						EnemyCoordinate_X = EnemyData::Pos_X;

						enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
					}

					if (player.PlayerResidue == 1) //�v���C���[�̎c�@��1�ɂȂ����Ƃ�
					{
						/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
						player.PlayerPos_X = EnemyData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyData::PlayerPosReset_Y;

						EnemyCoordinate_Y = EnemyData::Pos_Y;
						EnemyCoordinate_X = EnemyData::Pos_X;

						enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
					}
					if (player.PlayerResidue == 0) //�v���C���[�̎c�@��0�ɂȂ����Ƃ�
					{
						isGameOver = true; //�Q�[���I�[�o�[�p�̃t���O��true������
					}
				}
			}
		}
	}
	
	//�G�ƃv���C���[�������������̃t���b�V���X�V
	if (HitDameTime > 0)
	{
		// ���Ԃ����炷
		HitDameTime--;
		//�����_�ł̒l��ǉ����Ă���
		HitPointFlash++;
		//�l��10�ɂȂ�����O�ɂ���
		if (HitPointFlash == 20)
		{
			HitPointFlash = 0;
		}

		// 10�b�o�߂����ꍇ�̏���
		if (HitDameTime >= 0)
		{
			// ������10�b�o�ߌ�̏�����ǉ�����
			if (HitDamePos_X <= 0 && HitDamePos_X >= 60 && HitDamePos_Y <= 0 && HitDamePos_X >= 60)
			{
				HitDamePos_X += 10;
				HitDamePos_Y += 10;
			}
			if (HitDamePos_X >= 60 && HitDamePos_Y >= 60)
			{
				HitDamePos_X -= 10;
				HitDamePos_Y -= 10;
			}
		}
	}

	if (isGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void Enemy::Draw(Player& player, PowerFeed& powerfeed, EnemyTwo& enemytwo, EnemyThree& enemythree)
{
	if (HitDameTime > 0)
	{
		// ���Ԃ����炷
		HitDameTime--;

		// 10�b�o�߂����ꍇ�̏���
		if (HitDameTime >= 0)
		{
			if (HitPointFlash == 1 || HitPointFlash == 2 || HitPointFlash == 4 || HitPointFlash == 5 || HitPointFlash == 8 || HitPointFlash == 10)
			{
				DrawGraph(HitDamePos_X, HitDamePos_Y, HitDamegeGraphHandle, true);
				PlaySoundMem(DameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}

	if (BUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG

	}

	if (BUF == false)
	{
		DrawGraph(EnemyCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, EnemyGraphHandle, true);
	}
	
	if (BUF == true)
	{
		DrawGraph(EnemyCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, BUFEnemyHandle, true);
	}
}

void Enemy::Final()
{
	DeleteGraph(EnemyGraphHandle);
	DeleteGraph(GameOverGraphHandle);
	DeleteGraph(HitDamegeGraphHandle);
	DeleteGraph(BUFEnemyHandle);
	DeleteSoundMem(DameSoundHandle);
}



void Enemy::MoveTowardsPlayer(Player& player)
{
	/*std::vector<Node*> path = AStar(eb_x, eb_y, player.px, player.py);

	if (!path.empty())
	{
		Node* nextNode = path[1];
		if (!IsWall(nextNode->x, nextNode->y))
		{
			eb_x = nextNode->x;
			eb_y = nextNode->y;
		}
	}*/
	
	std::vector<Node*> path = AStar(EnemyCoordinate_X, EnemyCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		Node* nextNode = path[1];
		if (!IsWall(nextNode->x, nextNode->y))
		{
			// �ړ����x���l�����Ĉʒu���X�V
			float deltaX = static_cast<float>(nextNode->x - EnemyCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = MoveSpeed / distance;
				EnemyCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool Enemy::IsWall(int x, int y)
{
	//�}�b�v�͈̔͊O�͕ǂƂ݂Ȃ�
	if (x < 1 || x >= Game::MapChipWidth || y < 1 || y >= Game::MapChipHeight)
	{
		return true;
	}

	//MapData�̕ϐ��P��Ԃ�)
	return Game::MapData[y][x] == 1;
	//return Game::MapData[x][y] == 1;
}

int Enemy::CalculateHeuristic(int x1, int y1, int x2, int y2)
{
	//�}���n�b�^���������v�Z����w���X�e�B�b�N�֐�
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//���[�N���b�h�������v�Z����w���X�e�b�N�֐�
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}


std::vector<Node*> Enemy::AStar(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;//�ړ��R�X�g�̒�`

	std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> openList;//�I�[�v�����X�g���쐬����B�m�[�h�̃|�C���^�������Ɋi�[����
	std::vector<Node*> closedList;//�N���[�Y���X�g���쐬����B�m�[�h�̃|�C���^���i�[����B

	Node* startNode = new Node(startX, startY, 0, 0, nullptr);//�X�^�[�g�m�[�h���쐬����B
	
	openList.push(startNode);//�X�^�[�g�m�[�h���I�[�v�����X�g�ɒǉ�����Bpush -> openList(kyu-)

	while (!openList.empty())//�I�[�v�����X�g����łȂ��ԁA�T���𑱂���B
	{
		Node* currentNode = openList.top();//�I�[�v�����X�g��R�X�g���ŏ��̃m�[�h���擾����
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)//�ŏ��̃m�[�h���S�[���ɓ��B�������`�F�b�N����
		{
			std::vector<Node*> path;//�S�[���ɓ��B�����ꍇ�p�X���\�z����B
			while (currentNode != nullptr) 
			{
				// �S�[������X�^�[�g�܂ł̃p�X���t���Ƀp�X�x�N�^�[�ɒǉ�����
				{
					path.push_back(currentNode);
					currentNode = currentNode->parent;
				}
			}
			std::reverse(path.begin(), path.end());// �p�X�𐳂��������ɕ��ёւ���
			return path; // �p�X��Ԃ�
		}
		
		closedList.push_back(currentNode);// ���݂̃m�[�h���N���[�Y�h���X�g�ɒǉ�����

		
		//// 4�����̈ړ�������
		//for (int dy = -1; dy <= 1; ++dy += 2)
		//{
		//	for (int dx = -1; dx <= 1; ++dx)
		//	{
		//		if (dx == 0 && dy == 0) continue;
			
		

		// 8�����̈ړ�������
		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dx == 0 && dy == 0) continue;//���݂̈ʒu�̓X�L�b�v����

				// ���̈ړ���̍��W���v�Z����
				int nextX = currentNode->x + dx;
				int nextY = currentNode->y + dy;

				if (!IsWall(nextX, nextY))//���̍��W���ǂłȂ��ꍇ
				{
					//���̃m�[�h���쐬����
					Node* nextNode = new Node(nextX, nextY, currentNode->g + moveCost, CalculateHeuristic(nextX, nextY, goalX, goalY), currentNode);

					// �N���[�Y�h���X�g�Ƀm�[�h���܂܂�Ă��Ȃ��ꍇ�A�I�[�v�����X�g�ɒǉ�����
					if (std::find_if(closedList.begin(), closedList.end(), [&](const Node* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//�S�[���ɓ��B�ł��Ȃ��ꍇ��NULL��Ԃ�
	return std::vector<Node*>(NULL);
}




#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "../Game.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyTwo.h"
#include "../Feed/PowerFeed.h"
#include "../Enemy/EnemyThree.h"
#include "../Scene/SceneManager.h"

EnemyThree::EnemyThree() :
	EnemyThreeCoordinate_Y		(EnemyThreeData::Pos_Y),						//�G�́�Y���W��������
	EnemyThreeCoordinate_X		(EnemyThreeData::Pos_X),						//�G�́�X���W��������
	ThreeMoveSpeed				(EnemyThreeData::moveSpeed),					//�G�́����x��������
	ThreeHitDamePos_X			(EnemyThreeData::HitDamagedHandlePos_X),		//�摜�n���h����HitDamegeHandle���́�X���W��������
	ThreeHitDamePos_Y			(EnemyThreeData::HitDamagedHandlePos_Y),		//�摜�n���h����HitDamegeHandle���́�Y���W��������
	ThreeHitDameTime			(EnemyThreeData::AfterTakingDamegeTime),		//�v���C���[�ƓG�����������ۂ́����o���ԁ�������
	ThreeHitPointFlash			(EnemyThreeData::FlashPoint),					//�摜�n���h����HitDamegeHandle���́��t���b�V�����o��������
	ThreeisGameOver				(false),										//�Q�[���I�[�o�[�𔻒肷�邽�߂́��t���O��������
	ThreeBUF					(false),										//�o�t�t���O
	ThreeHitDamegeGraphHandle	(LoadGraph("img/Damage.png")),					//HitDamegeHandle���O���t�n���h�����̏�����
	ThreeEnemyGraphHandle		(LoadGraph("img/whitebear.png")),				//m_enemyBlinkyHandle���O���t�n���h�����̏�����
	ThreeGameOverGraphHandle	(LoadGraph("img/GAMEOVERTEXT.png")),			//m_GameOverHandle���O���t�n���h�����̏�����
	ThreeBUFEnemyHandle			(LoadGraph("img/whitebearBUF.png")),			//�o�t��Ԃ̓G���O���t�n���h�����̏�����
	ThreeDameSoundHandle		(LoadSoundMem("img/Dameg.mp3")),				//DameSoundHandle���T�E���h�n���h�����̏�����
	ThreePowerFeedBUFTime		(EnemyThreeData::BUFTime)						//�v���C���[���p���[�a���擾�����ۂ̃o�t������
{
}

EnemyThree::~EnemyThree()
{
	DeleteGraph					(ThreeEnemyGraphHandle);
	DeleteGraph					(ThreeGameOverGraphHandle);
	DeleteGraph					(ThreeHitDamegeGraphHandle);
	DeleteSoundMem				(ThreeDameSoundHandle);
}

void EnemyThree::Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	EnemyThreeCoordinate_Y		= EnemyThreeData::Pos_Y;
	EnemyThreeCoordinate_X		= EnemyThreeData::Pos_X;
	ThreeMoveSpeed				= EnemyThreeData::moveSpeed;
	ThreeHitDamePos_X			= EnemyThreeData::HitDamagedHandlePos_X;
	ThreeHitDamePos_Y			= EnemyThreeData::HitDamagedHandlePos_Y;
	ThreeHitPointFlash			= EnemyThreeData::FlashPoint;
	ThreeisGameOver				= false;
	ThreeBUF					= false;
	ThreeHitDamegeGraphHandle	= LoadGraph		("img/Damage.png");
	ThreeEnemyGraphHandle		= LoadGraph		("img/panda.png");
	ThreeGameOverGraphHandle	= LoadGraph		("img/GAMEOVERTEXT.png");
	ThreeBUFEnemyHandle			= LoadGraph		("img/BUFpanda.png");
	ThreeDameSoundHandle		= LoadSoundMem	("sound/Dameg.mp3");
}

void EnemyThree::Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		ThreeBUF = true;
	}
	//�G�̏���
	if (player.PlayerPos_X >= EnemyThreeCoordinate_X + 1 || player.PlayerPos_X <= EnemyThreeCoordinate_X - 1 || player.PlayerPos_Y >= EnemyThreeCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyThreeCoordinate_Y - 1) //�G�̍��p���O���ɂ����Ƃ��̏���
		if (player.PlayerPos_X >= EnemyThreeCoordinate_X + 1 || player.PlayerPos_X <= EnemyThreeCoordinate_X - 1 || player.PlayerPos_Y >= EnemyThreeCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyThreeCoordinate_Y - 1) //�G�̍��p���O���ɂ����Ƃ��̏���
		{
			if (ThreeBUF == true)
			{
				ThreePowerFeedBUFTime--;

				if (ThreeBUF == true)
				{
					if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
					{
						ThreePowerFeedBUFTime = 30;
					}
				}

				//�l��10�ɂȂ�����O�ɂ���
				if (ThreePowerFeedBUFTime == 0)
				{
					ThreePowerFeedBUFTime = 60;
					ThreeBUF = false;
				}
			}


			if (player.ClearManager >= 110 && ThreeBUF == false)
			{
				MoveTowardsPlayerThree(player); //A*�A���S���Y�����g�p�����v���C���[�̒ǐ�
			}

			if (player.ClearManager != 244)
			{

				if (player.PlayerPos_X >= EnemyThreeCoordinate_X && player.PlayerPos_X <= EnemyThreeCoordinate_X) //�����蔻�聃�w���W��
				{
					if (player.PlayerPos_Y >= EnemyThreeCoordinate_Y && player.PlayerPos_Y <= EnemyThreeCoordinate_Y) //�����蔻�聃�w���W��
					{
						ThreeHitDameTime = 10; //�����蔻���ʉ߂����ۂ�HitDameTime�ɒl�[��10����
						player.PlayerResidue -= 1; //�v���C���[�̎c�@������炷

						if (player.PlayerResidue == 2) //�v���C���[�̎c�@���Q�ɂȂ����Ƃ�
						{
							/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
							player.PlayerPos_X = EnemyThreeData::PlayerPosReset_X;
							player.PlayerPos_Y = EnemyThreeData::PlayerPosReset_Y;

							EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
							EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;

							enemy.EnemyCoordinate_X = EnemyData::Pos_X;
							enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

							enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;
							enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;

						}

						if (player.PlayerResidue == 1) //�v���C���[�̎c�@��1�ɂȂ����Ƃ�
						{
							/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
							player.PlayerPos_X = EnemyThreeData::PlayerPosReset_X;
							player.PlayerPos_Y = EnemyThreeData::PlayerPosReset_Y;

							EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;
							EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;

							enemy.EnemyCoordinate_X = EnemyData::Pos_X;
							enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

							enemytwo.EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;
							enemytwo.EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;


						}
						if (player.PlayerResidue == 0) //�v���C���[�̎c�@��0�ɂȂ����Ƃ�
						{
							ThreeisGameOver = true; //�Q�[���I�[�o�[�p�̃t���O��true������
						}

					}

				}
			}

		}

	//�G�ƃv���C���[�������������̃t���b�V���X�V
	if (ThreeHitDameTime > 0)
	{
		// ���Ԃ����炷
		ThreeHitDameTime--;
		//�����_�ł̒l��ǉ����Ă���
		ThreeHitPointFlash++;
		//�l��10�ɂȂ�����O�ɂ���
		if (ThreeHitPointFlash == 20)
		{
			ThreeHitPointFlash = 0;
		}

		// 10�b�o�߂����ꍇ�̏���
		if (ThreeHitDameTime >= 0)
		{
			// ������10�b�o�ߌ�̏�����ǉ�����
			if (ThreeHitDamePos_X <= 0 && ThreeHitDamePos_X >= 60 && ThreeHitDamePos_Y <= 0 && ThreeHitDamePos_X >= 60)
			{
				ThreeHitDamePos_X += 10;
				ThreeHitDamePos_Y += 10;
			}
			if (ThreeHitDamePos_X >= 60 && ThreeHitDamePos_Y >= 60)
			{
				ThreeHitDamePos_X -= 10;
				ThreeHitDamePos_Y -= 10;
			}
		}
	}

	if (ThreeisGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void EnemyThree::Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyTwo& enemytwo)
{
	if (ThreeHitDameTime > 0)
	{
		// ���Ԃ����炷
		ThreeHitDameTime--;

		// 10�b�o�߂����ꍇ�̏���
		if (ThreeHitDameTime >= 0)
		{
			if (ThreeHitPointFlash == 1 || ThreeHitPointFlash == 2 || ThreeHitPointFlash == 4 || ThreeHitPointFlash == 5 || ThreeHitPointFlash == 8 || ThreeHitPointFlash == 10)
			{
				DrawGraph(ThreeHitDamePos_X, ThreeHitDamePos_Y, ThreeHitDamegeGraphHandle, true);
				PlaySoundMem(ThreeDameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}


	if (ThreeBUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG
	}

	if (ThreeBUF == false)
	{
		DrawGraph(EnemyThreeCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyThreeCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, ThreeEnemyGraphHandle, true);
	}

	if (player.ClearManager <= 120 || ThreeBUF == true)
	{
		DrawGraph(EnemyThreeCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyThreeCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, ThreeBUFEnemyHandle, true);
	}
}

void EnemyThree::Final()
{
	DeleteGraph(ThreeEnemyGraphHandle);
	DeleteGraph(ThreeBUFEnemyHandle);
	DeleteGraph(ThreeHitDamegeGraphHandle);
	DeleteGraph(ThreeGameOverGraphHandle);
	DeleteSoundMem(ThreeDameSoundHandle);
}

void EnemyThree::MoveTowardsPlayerThree(Player& player)
{
	/*std::vector<NodeThree*> path = AStarThree(EnemyThreeCoordinate_X, EnemyThreeCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeThree* nextNode = path[1];
		if (!IsWallThree(nextNode->x, nextNode->y))
		{
			EnemyThreeCoordinate_X = nextNode->x;
			EnemyThreeCoordinate_Y = nextNode->y;
		}
	}*/

	std::vector<NodeThree*> path = AStarThree(EnemyThreeCoordinate_X, EnemyThreeCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeThree* nextNode = path[1];
		if (!IsWallThree(nextNode->x, nextNode->y))
		{
			// �ړ����x���l�����Ĉʒu���X�V
			float deltaX = static_cast<float>(nextNode->x - EnemyThreeCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyThreeCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = ThreeMoveSpeed / distance;
				EnemyThreeCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyThreeCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool EnemyThree::IsWallThree(int x, int y)
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

int EnemyThree::CalculateHeuristicThree(int x1, int y1, int x2, int y2)
{
	//�}���n�b�^���������v�Z����w���X�e�B�b�N�֐�
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//���[�N���b�h�������v�Z����w���X�e�b�N�֐�
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}

std::vector<NodeThree*> EnemyThree::AStarThree(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;

	std::priority_queue<NodeThree*, std::vector<NodeThree*>, std::greater<NodeThree*>> openList;
	std::vector<NodeThree*> closedList;

	NodeThree* startNode = new NodeThree(startX, startY, 0, 0, nullptr);

	openList.push(startNode);

	while (!openList.empty())
	{
		NodeThree* currentNode = openList.top();
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)
		{
			std::vector<NodeThree*> path;
			while (currentNode != nullptr)
			{
				path.push_back(currentNode);
				currentNode = currentNode->parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		closedList.push_back(currentNode);

		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dx == 0 && dy == 0) continue;


				int nextX = currentNode->x + dx;
				int nextY = currentNode->y + dy;

				if (!IsWallThree(nextX, nextY))
				{
					NodeThree* nextNode = new NodeThree(nextX, nextY, currentNode->g + moveCost, CalculateHeuristicThree(nextX, nextY, goalX, goalY), currentNode);

					if (std::find_if(closedList.begin(), closedList.end(), [&](const NodeThree* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//�S�[���ɓ��B�ł��Ȃ��ꍇ��NULL��Ԃ�
	return std::vector<NodeThree*>(NULL);
}



#include <queue>
#include <cmath>
#include <vector>
#include <iostream>
#include "../Game.h"
#include "../Player/Player.h"
#include "../Feed/PowerFeed.h"
#include "../Enemy/EnemyTwo.h"
#include "../Enemy/EnemyThree.h"
#include "../Scene/SceneManager.h"

EnemyTwo::EnemyTwo():
	EnemyTwoCoordinate_Y		(EnemyTwoData::Pos_Y),						//�G�́�Y���W��������
	EnemyTwoCoordinate_X		(EnemyTwoData::Pos_X),						//�G�́�X���W��������
	TwoMoveSpeed				(EnemyTwoData::moveSpeed),					//�G�́����x��������
	TwoHitDamePos_X				(EnemyTwoData::HitDamagedHandlePos_X),		//�摜�n���h����HitDamegeHandle���́�X���W��������
	TwoHitDamePos_Y				(EnemyTwoData::HitDamagedHandlePos_Y),		//�摜�n���h����HitDamegeHandle���́�Y���W��������
	TwoHitDameTime				(EnemyTwoData::AfterTakingDamegeTime),		//�v���C���[�ƓG�����������ۂ́����o���ԁ�������
	TwoHitPointFlash			(EnemyTwoData::FlashPoint),				//�摜�n���h����HitDamegeHandle���́��t���b�V�����o��������
	TwoisGameOver				(false),								//�Q�[���I�[�o�[�𔻒肷�邽�߂́��t���O��������
	TwoBUF						(false),								//�o�t�t���O
	TwoHitDamegeGraphHandle		(LoadGraph("img/Damage.png")),			//HitDamegeHandle���O���t�n���h�����̏�����
	TwoEnemyGraphHandle			(LoadGraph("img/whitebear.png")),		//m_enemyBlinkyHandle���O���t�n���h�����̏�����
	TwoGameOverGraphHandle		(LoadGraph("img/GAMEOVERTEXT.png")),	//m_GameOverHandle���O���t�n���h�����̏�����
	TwoBUFEnemyHandle			(LoadGraph("img/whitebearBUF.png")),	//�o�t��Ԃ̓G���O���t�n���h�����̏�����
	TwoDameSoundHandle			(LoadSoundMem("img/Dameg.mp3")),		//DameSoundHandle���T�E���h�n���h�����̏�����
	TwoPowerFeedBUFTime			(EnemyTwoData::BUFTime)					//�v���C���[���p���[�a���擾�����ۂ̃o�t������
{
}

EnemyTwo::~EnemyTwo()
{
	DeleteGraph					(TwoEnemyGraphHandle);
	DeleteGraph					(TwoGameOverGraphHandle);
	DeleteGraph					(TwoHitDamegeGraphHandle);
	DeleteSoundMem				(TwoDameSoundHandle);
}

void EnemyTwo::Init(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	EnemyTwoCoordinate_Y		= EnemyTwoData::Pos_Y;
	EnemyTwoCoordinate_X		= EnemyTwoData::Pos_X;
	TwoMoveSpeed				= EnemyTwoData::moveSpeed;
	TwoHitDamePos_X				= EnemyTwoData::HitDamagedHandlePos_X;
	TwoHitDamePos_Y				= EnemyTwoData::HitDamagedHandlePos_Y;
	TwoHitPointFlash			= EnemyTwoData::FlashPoint;
	TwoisGameOver				= false;
	TwoBUF						= false;
	TwoHitDamegeGraphHandle		= LoadGraph		("img/Damage.png");
	TwoEnemyGraphHandle			= LoadGraph		("img/whitebear.png");
	TwoGameOverGraphHandle		= LoadGraph		("img/GAMEOVERTEXT.png");
	TwoBUFEnemyHandle			= LoadGraph		("img/whitebearBUF.png");
	TwoDameSoundHandle			= LoadSoundMem	("sound/Dameg.mp3");
}

void EnemyTwo::Update(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		TwoBUF = true;
	}
	//�G�̏���
	if (player.PlayerPos_X >= EnemyTwoCoordinate_X + 1 || player.PlayerPos_X <= EnemyTwoCoordinate_X - 1 || player.PlayerPos_Y >= EnemyTwoCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyTwoCoordinate_Y - 1) //�G�̍��p���O���ɂ����Ƃ��̏���
	if (player.PlayerPos_X >= EnemyTwoCoordinate_X + 1 || player.PlayerPos_X <= EnemyTwoCoordinate_X - 1 || player.PlayerPos_Y >= EnemyTwoCoordinate_Y + 1 || player.PlayerPos_Y <= EnemyTwoCoordinate_Y - 1) //�G�̍��p���O���ɂ����Ƃ��̏���
	{
		if (TwoBUF == true)
		{
			TwoPowerFeedBUFTime--;
			
			if (TwoBUF == true)
			{
				if (powerfeed.PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
				{
					TwoPowerFeedBUFTime = 60;
				}
			}
			
			//�l��10�ɂȂ�����O�ɂ���
			if (TwoPowerFeedBUFTime == 0)
			{
				TwoPowerFeedBUFTime = 60;
				TwoBUF = false;
			}
		}
		

		if (player.ClearManager >= 110 && TwoBUF == false)
		{
			MoveTowardsPlayerTwo(player); //A*�A���S���Y�����g�p�����v���C���[�̒ǐ�
		}

		if (player.ClearManager != 244)
		{

			if (player.PlayerPos_X >= EnemyTwoCoordinate_X && player.PlayerPos_X <= EnemyTwoCoordinate_X) //�����蔻�聃�w���W��
			{
				if (player.PlayerPos_Y >= EnemyTwoCoordinate_Y && player.PlayerPos_Y <= EnemyTwoCoordinate_Y) //�����蔻�聃�w���W��
				{
					TwoHitDameTime = 10; //�����蔻���ʉ߂����ۂ�HitDameTime�ɒl�[��10����
					player.PlayerResidue -= 1; //�v���C���[�̎c�@������炷

					if (player.PlayerResidue == 2) //�v���C���[�̎c�@���Q�ɂȂ����Ƃ�
					{
						/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
						player.PlayerPos_X = EnemyTwoData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyTwoData::PlayerPosReset_Y;

						EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemy.EnemyCoordinate_X = EnemyData::Pos_X;
						enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;


					}

					if (player.PlayerResidue == 1) //�v���C���[�̎c�@��1�ɂȂ����Ƃ�
					{
						/*�G�̍��W�ƃv���C���[�̍��W�������l�ɖ߂�*/
						player.PlayerPos_X = EnemyTwoData::PlayerPosReset_X;
						player.PlayerPos_Y = EnemyTwoData::PlayerPosReset_Y;

						EnemyTwoCoordinate_Y = EnemyTwoData::Pos_Y;
						EnemyTwoCoordinate_X = EnemyTwoData::Pos_X;

						enemy.EnemyCoordinate_X = EnemyData::Pos_X;
						enemy.EnemyCoordinate_Y = EnemyData::Pos_Y;

						enemythree.EnemyThreeCoordinate_X = EnemyThreeData::Pos_X;
						enemythree.EnemyThreeCoordinate_Y = EnemyThreeData::Pos_Y;


					}
					if (player.PlayerResidue == 0) //�v���C���[�̎c�@��0�ɂȂ����Ƃ�
					{
						TwoisGameOver = true; //�Q�[���I�[�o�[�p�̃t���O��true������
					}

				}

			}
		}

	}

	//�G�ƃv���C���[�������������̃t���b�V���X�V
	if (TwoHitDameTime > 0)
	{
		// ���Ԃ����炷
		TwoHitDameTime--;
		//�����_�ł̒l��ǉ����Ă���
		TwoHitPointFlash++;
		//�l��10�ɂȂ�����O�ɂ���
		if (TwoHitPointFlash == 20)
		{
			TwoHitPointFlash = 0;
		}

		// 10�b�o�߂����ꍇ�̏���
		if (TwoHitDameTime >= 0)
		{
			// ������10�b�o�ߌ�̏�����ǉ�����
			if (TwoHitDamePos_X <= 0 && TwoHitDamePos_X >= 60 && TwoHitDamePos_Y <= 0 && TwoHitDamePos_X >= 60)
			{
				TwoHitDamePos_X += 10;
				TwoHitDamePos_Y += 10;
			}
			if (TwoHitDamePos_X >= 60 && TwoHitDamePos_Y >= 60)
			{
				TwoHitDamePos_X -= 10;
				TwoHitDamePos_Y -= 10;
			}
		}
	}

	if (TwoisGameOver == true)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_anim);
	}
}

void EnemyTwo::Draw(Player& player, PowerFeed& powerfeed, Enemy& enemy, EnemyThree& enemythree)
{
	if (TwoHitDameTime > 0)
	{
		// ���Ԃ����炷
		TwoHitDameTime--;

		// 10�b�o�߂����ꍇ�̏���
		if (TwoHitDameTime >= 0)
		{
			if (TwoHitPointFlash == 1 || TwoHitPointFlash == 2 || TwoHitPointFlash == 4 || TwoHitPointFlash == 5 || TwoHitPointFlash == 8 || TwoHitPointFlash == 10)
			{
				DrawGraph(TwoHitDamePos_X, TwoHitDamePos_Y, TwoHitDamegeGraphHandle, true);
				PlaySoundMem(TwoDameSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
	}


	if (TwoBUF == true)
	{
#ifdef DEBUG
		DrawString(10, 500, "BUF = true", 0xffffff, 16);

#endif // DEBUG
	}

	if (TwoBUF == false)
	{
		DrawGraph(EnemyTwoCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyTwoCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, TwoEnemyGraphHandle, true);
	}
	
	if (player.ClearManager <= 110 || TwoBUF == true)
	{
		DrawGraph(EnemyTwoCoordinate_X * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn,
			EnemyTwoCoordinate_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int>(Game::CorrectCoordinates) - Game::Sechzehn, TwoBUFEnemyHandle, true);
	}
}

void EnemyTwo::Final()
{
	DeleteGraph(TwoBUFEnemyHandle);
	DeleteGraph(TwoEnemyGraphHandle);
	DeleteGraph(TwoHitDamegeGraphHandle);
	DeleteGraph(TwoGameOverGraphHandle);
	DeleteSoundMem(TwoDameSoundHandle);
}

void EnemyTwo::MoveTowardsPlayerTwo(Player& player)
{
	/*std::vector<NodeTwo*> path = AStarTwo(EnemyTwoCoordinate_X, EnemyTwoCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeTwo* nextNode = path[1];
		if (!IsWallTwo(nextNode->x, nextNode->y))
		{
			EnemyTwoCoordinate_X = nextNode->x;
			EnemyTwoCoordinate_Y = nextNode->y;
		}
	}*/

	std::vector<NodeTwo*> path = AStarTwo(EnemyTwoCoordinate_X, EnemyTwoCoordinate_Y, player.PlayerPos_X, player.PlayerPos_Y);

	if (!path.empty())
	{
		NodeTwo* nextNode = path[1];
		if (!IsWallTwo(nextNode->x, nextNode->y))
		{
			// �ړ����x���l�����Ĉʒu���X�V
			float deltaX = static_cast<float>(nextNode->x - EnemyTwoCoordinate_X);
			float deltaY = static_cast<float>(nextNode->y - EnemyTwoCoordinate_Y);
			float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance > 0)
			{
				float ratio = TwoMoveSpeed / distance;
				EnemyTwoCoordinate_X += static_cast<int>(deltaX * ratio);
				EnemyTwoCoordinate_Y += static_cast<int>(deltaY * ratio);
			}
		}
	}
}

bool EnemyTwo::IsWallTwo(int x, int y)
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

int EnemyTwo::CalculateHeuristicTwo(int x1, int y1, int x2, int y2)
{
	//�}���n�b�^���������v�Z����w���X�e�B�b�N�֐�
	return std::abs(x1 - x2) + std::abs(y1 - y2);

	//���[�N���b�h�������v�Z����w���X�e�b�N�֐�
	//return static_cast<int>(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}

std::vector<NodeTwo*> EnemyTwo::AStarTwo(int startX, int startY, int goalX, int goalY)
{
	const int moveCost = 1;

	std::priority_queue<NodeTwo*, std::vector<NodeTwo*>, std::greater<NodeTwo*>> openList;
	std::vector<NodeTwo*> closedList;

	NodeTwo* startNode = new NodeTwo(startX, startY, 0, 0, nullptr);

	openList.push(startNode);

	while (!openList.empty())
	{
		NodeTwo* currentNode = openList.top();
		openList.pop();

		if (currentNode->x == goalX && currentNode->y == goalY)
		{
			std::vector<NodeTwo*> path;
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

				if (!IsWallTwo(nextX, nextY))
				{
					NodeTwo* nextNode = new NodeTwo(nextX, nextY, currentNode->g + moveCost, CalculateHeuristicTwo(nextX, nextY, goalX, goalY), currentNode);

					if (std::find_if(closedList.begin(), closedList.end(), [&](const NodeTwo* n) {return n->x == nextX && n->y == nextY; }) == closedList.end())
					{
						openList.push(nextNode);
					}
				}
			}
		}
	}

	//�S�[���ɓ��B�ł��Ȃ��ꍇ��NULL��Ԃ�
	return std::vector<NodeTwo*>(NULL);
}

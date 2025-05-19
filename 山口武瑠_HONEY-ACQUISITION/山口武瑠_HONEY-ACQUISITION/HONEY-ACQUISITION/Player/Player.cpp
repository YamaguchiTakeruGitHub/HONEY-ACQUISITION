#include "DxLib.h"
#include "../Game.h"
#include "../Sound.h"
#include "../Map/Map.h"
#include "../UITool/UI.h"
#include "../Feed/Feed.h"
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include <fstream>
#include <string>
#include <ctime>


Player::Player() :
	ky					(PlayerData::ComplexPosY),				//�񎟌��z��̈�}�X���P�̎��Ɉʒu��������y���W�ɓ���Ȃ����p�̋����W
	kx					(PlayerData::ComplexPosX),				//�񎟌��z��̈�}�X���P�̎��Ɉʒu��������x���W�ɓ���Ȃ����p�̋����W
	PlayerPos_X			(PlayerData::Pos_X),					//�v���C���[�̍��W���������Wx�̐ݒ�
	PlayerPos_Y			(PlayerData::Pos_Y),					//�v���C���[�̍��W���������Wy�̐ݒ�
	
	PrevPlayerPox_X     (PlayerData::PrevPos_X),				//�v���C���[�̑O�t���[���̈ʒu���w���W�����X�V
	PrevPlayerPox_Y		(PlayerData::PrevPos_Y),				//�v���C���[�̑O�t���[���̈ʒu���x���W�����X�V

	KEY					(PlayerData::KeyNumber),				//�L�[���͂̏����l
	score				(PlayerData::ScoreContainer),			//�X�R�A�̏����l
	FrameRate			(PlayerData::FrameNumber),
	PreviousKey			(PlayerData::InputKeyContainer),		//�L�[���͏������邽�߂̂���
	
	UPThought			(PlayerData::InputKeyContainerOne),		//��L�[���͏��
	DownThought			(PlayerData::InputKeyContainerTwo),		//���L�[���͏��
	LeftThought			(PlayerData::InputKeyContainerThree),	//���L�[���͏��
	RightThought		(PlayerData::InputKeyContainerFour),	//�E�L�[���͏��
	
	ClearManager		(PlayerData::ClearNumber),				//�����N���A���o�����Ƃ���ꂽ�Ƃ��p
	PlayerResidue		(PlayerData::RemainingMachines),		//�v���C���[�̎c�@
	
	AnimUP				(false),								//��̃A�j���[�V�����t���O
	AnimDOWN			(false),								//���̃A�j���[�V�����t���O
	AnimLEFT			(false),								//���̃A�j���[�V�����t���O
	AnimRIGHT			(false),								//�E�̃A�j���[�V�����t���O
	
	UpFlag				(false),								//��L�[�̏��t���O
	DownFlag			(false),								//���L�[�̏��t���O
	LeftFlag			(false),								//���L�[�̏��t���O
	RightFlag			(false),								//�E�L�[�̏��t���O
	Player_GameOverFlag	(false),								//�Q�[���I�[�o�[�̃t���O
	
	currentDirection	(),										//���݂̕���������ϐ�
	
	m_playerHandle		(),										//���C���֐��ŊǗ�����摜�n���h��
	BeeHandleUp			(LoadGraph("img/BeeUp.png")),			//������̎��@�n���h��
	BeeHandleLeft		(LoadGraph("img/beeLeft.png")),			//�������̎��@�n���h��
	BeeHandleDown		(LoadGraph("img/BeeDown.png")),			//�������̎��@�n���h��
	BeeHandleRight		(LoadGraph("img/beeRight.png")),		//�E�����̎��@�n���h��
	ResidueHandle		(LoadGraph("img/Residue.png")),			//�c�@�摜�̃n���h��
	ResidueHandle2		(LoadGraph("img/Residue.png")),			//�c�@�摜�̃n���h��2
	ResidueHandle3		(LoadGraph("img/Residue.png")),			//�c�@�摜�̃n���h��3
	PlayerMapData		()										//�v���C���[�̈ړ������ɂȂ��Ղ̃}�b�v�f�[�^

{
	
}

Player::~Player()
{
}

void Player::Init(Enemy& enemy, UI& ui)
{
	ky						= PlayerData::ComplexPosY;
	kx						= PlayerData::ComplexPosX;
	PlayerPos_X				= PlayerData::Pos_X;
	PlayerPos_Y				= PlayerData::Pos_Y;
	PrevPlayerPox_X			= PlayerData::PrevPos_X;
	PrevPlayerPox_Y			= PlayerData::PrevPos_Y;

	KEY						= PlayerData::KeyNumber;
	FrameRate				= PlayerData::FrameNumber;
	ClearManager			= PlayerData::ClearNumber;
	PlayerResidue			= PlayerData::RemainingMachines;
	score					= PlayerData::ScoreContainer;
	AnimUP					= false;
	AnimDOWN				= false;
	AnimLEFT				= false;
	AnimRIGHT				= false;
	
	Player_GameOverFlag		= false;
	
	ResidueHandle			= LoadGraph("img/Residue.png");
	ResidueHandle2			= LoadGraph("img/Residue.png");
	ResidueHandle3			= LoadGraph("img/Residue.png");

	currentDirection;
	BeeHandleUp;
	BeeHandleDown;
	BeeHandleRight;
	BeeHandleLeft;

	
	UPThought;
	DownThought;
	LeftThought;
	RightThought;
	PreviousKey;


	UpFlag = false;
	DownFlag = false;
	LeftFlag = false;
	RightFlag = false;

	/*************************************�v���C���[��p�ړ���Ճ}�b�v�f�[�^*******************************/
	
	int row1[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row3[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row4[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row5[] = { 1,37,32,32,32,32,36,32,32,32,32,32,38, 1, 1,37,32,32,32,32,32,36,32,32,32,32,38, 1 };
	int row6[] = { 1,33, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row7[] = { 1,33, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row8[] = { 1,33, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row9[] = { 1,31,32,32,32,32,34,32,32,36,32,32,35,32,32,35,32,32,36,32,32,34,32,32,32,32,30, 1 };
	int row10[] ={ 1,33, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row11[] ={ 1,33, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row12[] ={ 1,40,32,32,32,32,30, 1, 1,40,32,32,38, 1, 1,37,32,32,41, 1, 1,31,32,32,32,32,41, 1 };
	int row13[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row14[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row15[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,37,32,32,35,32,32,35,32,32,38, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row16[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row17[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 0, 0, 0, 0, 0, 0, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row18[] ={ 4,32,32,32,32,32,34,32,32,30, 1, 0, 0, 0, 0, 0, 0, 1,31,32,32,34,32,32,32,32,32, 5 };
	int row19[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 0, 0, 0, 0, 0, 0, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row20[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row21[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,31,32,32,32,32,32,32,32,32,30, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row22[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row23[] ={ 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1 };
	int row24[] ={ 1,37,32,32,32,32,34,32,32,35,32,32,38, 1, 1,37,32,32,35,32,32,34,32,32,32,32,38, 1 };
	int row25[] ={ 1,33, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row26[] ={ 1,33, 1, 1, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1,33, 1, 1, 1, 1,33, 1 };
	int row27[] ={ 1,40,32,38, 1, 1,31,32,32,36,32,32,35,32,32,35,32,32,36,32,32,30, 1, 1,37,32,41, 1 };
	int row28[] ={ 1, 1, 1,33, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1,33, 1, 1, 1 };
	int row29[] ={ 1, 1, 1,33, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1,33, 1, 1, 1 };
	int row30[] ={ 1,37,32,35,32,32,41, 1, 1,40,32,32,38, 1, 1,37,32,32,41, 1, 1,40,32,32,35,32,38, 1 };
	int row31[] ={ 1,33, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,33, 1 };
	int row32[] ={ 1,33, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,33, 1, 1,33, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,33, 1 };
	int row33[] ={ 1,40,32,32,32,32,32,32,32,32,32,32,35,32,32,35,32,32,32,32,32,32,32,32,32,32,41, 1 };
	int row34[] ={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row35[] ={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int row36[] ={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	int* rows[] = { row1,row2, row3, row4, row5, row6, row7, row8, row9, row10,
				   row11,row12, row13, row14, row15, row16, row17, row18, row19, row20,
				   row21,row22, row23, row24, row25, row26, row27, row28, row29, row30,
				   row31,row32, row33, row34, row35, row36 };

	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			PlayerMapData[y][x] = rows[y][x];
		}
	}
	/*******************************************************************************************************/
}


void Player::Update(Enemy& enemy, Feed& feed, UI& ui)
{
	

	FileWritingScore(score);
	
	if (Player_GameOverFlag == false)
	{
		//�ʒu���W��߂����߂̋���
		kx = PlayerPos_X, ky = PlayerPos_Y;

		PrevPlayerPox_X = kx;
		PrevPlayerPox_Y = ky;

		//�L�[���͏���
		//
		{
			/**/
		}
		
		//�㉺��
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 30)
		{
			UpFlag		= true;
			DownFlag	= true;
			LeftFlag	= true;
			RightFlag	= false;
		}

		//�㉺��
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 31)
		{
			UpFlag		= true;
			DownFlag	= true;
			LeftFlag	= false;
			RightFlag	= true;
		}

		//���E
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 32)
		{
			UpFlag		= false;
			DownFlag	= false;
			LeftFlag	= true;
			RightFlag	= true;
		}

		//�㉺
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 33)
		{
			UpFlag		= true;
			DownFlag	= true;
			LeftFlag	= false;
			RightFlag	= false;
		}

		//�㉺���E
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 34)
		{
			UpFlag		= true;
			DownFlag	= true;
			LeftFlag	= true;
			RightFlag	= true;
		}

		//��E��
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 35)
		{
			UpFlag		= true;
			DownFlag	= false;
			LeftFlag	= true;
			RightFlag	= true;
		}

		//�����E
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 36)
		{
			UpFlag		= false;
			DownFlag	= true;
			LeftFlag	= true;
			RightFlag	= true;
		}

		//���E
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 37)
		{
			UpFlag		= false;
			DownFlag	= true;
			LeftFlag	= false;
			RightFlag	= true;
		}

		//����
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 38)
		{
			UpFlag		= false;
			DownFlag	= true;
			LeftFlag	= true;
			RightFlag	= false;
		}

		//��E
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 40)
		{
			UpFlag		= true;
			DownFlag	= false;
			LeftFlag	= false;
			RightFlag	= true;
		}

		//�㍶
		if (PlayerMapData[PlayerPos_Y][PlayerPos_X] == 41)
		{
			UpFlag		= true;
			DownFlag	= false;
			LeftFlag	= true;
			RightFlag	= false;
		}

		//�\���L�[��
		if (CheckHitKey(KEY_INPUT_UP) != 0 )
		{
			PreviousKey = UPThought;
		}

		//�p�b�h��
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) == 0)
		{
			// ������Ă��Ȃ�
		}
		else
		{
			// ������Ă���
			PreviousKey = UPThought;
		}
		
		//�\���L�[��
		if (CheckHitKey(KEY_INPUT_DOWN) != 0 )
		{
			PreviousKey = DownThought;
		}
		//�p�b�h��
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) == 0)
		{
			// ������Ă��Ȃ�
		}
		else
		{
			// ������Ă���
			PreviousKey = DownThought;
		}

		//�\���L�[��
		if (CheckHitKey(KEY_INPUT_LEFT) != 0 )
		{
			PreviousKey = LeftThought;
		}
		//�p�b�h��
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) == 0)
		{
			// ������Ă��Ȃ�
		}
		else
		{
			// ������Ă���
			PreviousKey = LeftThought;
		}

		//�\���L�[��
		if (CheckHitKey(KEY_INPUT_RIGHT) != 0 )
		{
			PreviousKey = RightThought;
		}
		//�p�b�h��
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == 0)
		{
			// ������Ă��Ȃ�
		}
		else
		{
			// ������Ă���
			PreviousKey = RightThought;
		}

		if (UpFlag == true && GetCurrentDirection() != UP && PreviousKey == UPThought)
		{
			ChangeDirection(UP);
		}
		if (DownFlag == true && GetCurrentDirection() != DOWN && PreviousKey == DownThought)
		{
			ChangeDirection(DOWN);
		}
		if (LeftFlag == true && GetCurrentDirection() != LEFT && PreviousKey == LeftThought)
		{
			ChangeDirection(LEFT);
		}
		if (RightFlag == true && GetCurrentDirection() != RIGHT && PreviousKey == RightThought)
		{
			ChangeDirection(RIGHT);
		}

		switch (currentDirection)
		{
		case UP:
			ky--;

			AnimUP = true;
			AnimDOWN = false;
			AnimRIGHT = false;
			AnimLEFT = false;

			break ;
		case DOWN:
			ky++;

			AnimUP = false;
			AnimDOWN = true;
			AnimRIGHT = false;
			AnimLEFT = false;

			break;
		case LEFT:
			kx--;

			AnimUP = false;
			AnimDOWN =false;
			AnimRIGHT = false;
			AnimLEFT = true;

			break;
		case RIGHT:
			kx++;

			AnimUP = false;
			AnimDOWN = false;
			AnimRIGHT = true;
			AnimLEFT = false;

			break;
		}
		
		//MEMO:�}�b�v�f�[�^���P�łȂ��̎����W
		if (Game::MapData[ky][kx] != 1 && Game::MapData[ky][kx] != 6)
		{
			PlayerPos_X = kx;
			PlayerPos_Y = ky;
		}

		//�G�T�ƃv���C���[�̓����蔻�聕�X�R�A���Z�i��G�T10�_���Z�j
		if (Game::MapData[PlayerPos_Y][PlayerPos_X] == 8)
		{
			Game::MapData[PlayerPos_Y][PlayerPos_X] = 0;
			score += 10;
			ClearManager += 1;
		}

		//�p���[�a�ƃv���C���[�̓����蔻�聕�X�R�A���Z�i��G�T50�_���Z�j
		if (Game::MapData[PlayerPos_Y][PlayerPos_X] == 9)
		{
			Game::MapData[PlayerPos_Y][PlayerPos_X] = 0;
			score += 50;
			ClearManager += 1;
		}

		//���[�v�]�[���T
		if (Game::MapData[PlayerPos_Y][PlayerPos_X] == 5)
		{
			PlayerPos_X = 1;
		}

		//���[�v�]�[���S
		if (Game::MapData[PlayerPos_Y][PlayerPos_X] == 4)
		{
			PlayerPos_X = 26;
		}

		for (int x = 0; x < PlayerResidue; x++)
		{
			if (PlayerResidue == 0)
			{

				Player_GameOverFlag = true;
			}
		}

		SceneManager::ScorePlayerCountManager(ClearManager, 244);

		Sleep(FrameRate);
	}
	else
	{ 
		
	}


}

void Player::Draw(Enemy& enemy, UI& ui)
{
	
	DrawPlayerEffect();
	
	if (PlayerResidue >= 3)
	{
		DrawGraph(500, 10, ResidueHandle, true);

	}
	if (PlayerResidue >= 2)
	{
		DrawGraph(540, 10, ResidueHandle2, true);
	}
	if(PlayerResidue >= 1)
	{
		DrawGraph(580, 10, ResidueHandle3, true);
	}

	if (AnimUP == true && AnimDOWN == false && AnimRIGHT == false && AnimLEFT == false)
	{
		DrawGraph(PlayerPos_X * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn,
			PlayerPos_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn, BeeHandleUp, true);
	}
	if (AnimUP == false && AnimDOWN == true && AnimRIGHT == false && AnimLEFT == false)
	{
		DrawGraph(PlayerPos_X * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn,
			PlayerPos_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn, BeeHandleDown, true);
	}
	if (AnimUP == false && AnimDOWN == false && AnimRIGHT == true && AnimLEFT == false)
	{
		DrawGraph(PlayerPos_X * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn,
			PlayerPos_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn,BeeHandleRight, true);
	}
	if (AnimUP == false && AnimDOWN == false && AnimRIGHT == false && AnimLEFT == true)
	{
		DrawGraph(PlayerPos_X * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn,
			PlayerPos_Y * Game::MapChipSize + Game::MapChipSize * static_cast<int> (Game::CorrectCoordinates) - Game::Sechzehn, /*BeeHandleLeft*/
			m_playerHandle, true);
	}
	

	//DrawFormatString(200, 0, 0xffffff, "%d", ClearManager);
}

void Player::Final()
{
	DeleteGraph(BeeHandleUp);
	DeleteGraph(BeeHandleLeft);
	DeleteGraph(ResidueHandle);
	DeleteGraph(BeeHandleDown);
	DeleteGraph(m_playerHandle);
	DeleteGraph(BeeHandleRight);
}

Direction Player::GetCurrentDirection() const
{
	return currentDirection;
}

void Player::ChangeDirection(Direction newDirection)
{

	currentDirection = newDirection;

}

bool Player::isWall(int x, int y)
{
	return (Game::MapData[y][x] == 1);
}

void Player::FileWritingScore(int S)
{
	std::ofstream outputfile("ScoreText/HighScore.txt");
	outputfile << S;
	outputfile.close();
}

void Player::UpdatePlayerEffect()
{
	

}

void Player::DrawPlayerEffect()
{
}







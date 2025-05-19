#pragma once

/*****************************�`�������`*************************************/
//�@�R�����g�̖����́����ɕύX���Ă��悢�l�����L�����Ă���܂��B			 /
//�A�����l�܂��͕ύX�s�Ə����Ă���l�̕ύX�͂��Ȃ��ł��������B				 /
//�B�ύX�\�Ȓl�̒��ňʒu���W��ύX����ۂ͕ύX���ꂽ�����������Ă��������B /  
/****************************************************************************/

#include "../Game.h"		//�Q�[���w�b�_�[
#include "../Feed/Feed.h"	//�t�[�h�w�b�_�[
#include "../Enemy/Enemy.h"	//�G�l�~�[�w�b�_�[

/// <summary>
/// �჆�[�U�[��`��
/// �v���C���[�̃f�[�^�l�ϐ�
/// </summary>
struct PlayerData
{
	static constexpr int ComplexPosX			 =  0;	//�����p�ϐ��@		�� X���W /�����l /�ύX�s��
	static constexpr int ComplexPosY			 =  0;	//�����p�ϐ��@		�� Y���W /�����l /�ύX�s��
	static const     int Pos_X					 = 14;	//�v���C���[�@		�� X���W /�����l /�ύX��
	static const     int Pos_Y					 = 26;	//�v���C���[�@		�� Y���W /�����l /�ύX��
	static const     int PrevPos_X				 =	0;	//�O�t���[���ʒu	�� X���W /�����l /�ύX�s��
	static const     int PrevPos_Y				 =  0;	//�O�t���[���ʒu	�� Y���W /�����l /�ύX�s��
	static const     int KeyNumber				 =  0;	//�L�[		�@		�������l         /�ύX�s��
	static const	 int FrameNumber			 = 60;	//�t���[������		�������l         /�ύX�s��
	static const	 int ClearNumber			 =  0;	//�N���A�p	�@		�������l         /�ύX�s��
	static const	 int RemainingMachines		 =  3;	//�v���C���[�@		��  �c�@         /�ύX��
	static const	 int ScoreContainer			 =  0;	//�X�R�A			�������l         /�ύX��
	static const	 int InputKeyContainer		 =  0;	//�L�[���	�@		�������l         /�ύX�s��
	static const	 int InputKeyContainerOne	 =  1;	//��L�[���@		���Œ�l         /�ύX�s��
	static const	 int InputKeyContainerTwo	 =  2;  //���L�[���		���Œ�l�@�@�@�@ /�ύX�s��
	static const	 int InputKeyContainerThree	 =  3;	//���L�[���		���Œ�l�@�@�@�@ /�ύX�s��
	static const     int InputKeyContainerFour	 =  4;	//�E�L�[���		���Œ�l�@�@�@�@ /�ύX�s��
};


/// <summary>
/// �჆�[�U�[��`�����enum
/// </summary>
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Feed;
class Enemy;
class SceneManager;
class Sound;
class UI;

class Player
{
public:
	Player();
	~Player();

	void Init(Enemy& enemy, UI& ui);
	void Update(Enemy& enemy, Feed& feed, UI& ui);
	void Draw(Enemy& enemy, UI& ui);
	void Final();

	Direction GetCurrentDirection() const;

	void ChangeDirection(Direction newDirection);

	void playerSetHandle(int* handle) { m_playerHandle = *handle; }

	bool isWall(int x, int y);

	void FileWritingScore(int S);

	void UpdatePlayerEffect();
	void DrawPlayerEffect();

	int PlayerPos_X;
	int PlayerPos_Y;

	int ky;
	int kx;
	
	int PrevPlayerPox_X;
	int PrevPlayerPox_Y;
	
	int ClearManager;


	int score;
 
	int FrameRate;

	int m_playerHandle;

	bool Player_GameOverFlag;

	int ResidueHandle;
	int ResidueHandle2;
	int ResidueHandle3;


	int PlayerResidue;
	

	
	int BeeHandleUp;
	int BeeHandleDown;
	int BeeHandleRight;
	int BeeHandleLeft;

	bool AnimUP;
	bool AnimDOWN;
	bool AnimLEFT;
	bool AnimRIGHT;

	int UPThought;
	int DownThought;
	int LeftThought;
	int RightThought;

	int PreviousKey;
	int PlayerMapData[36][28];
	
	bool UpFlag;
	bool DownFlag;
	bool LeftFlag;
	bool RightFlag;

private:
	
	int KEY;

	Direction currentDirection;
};


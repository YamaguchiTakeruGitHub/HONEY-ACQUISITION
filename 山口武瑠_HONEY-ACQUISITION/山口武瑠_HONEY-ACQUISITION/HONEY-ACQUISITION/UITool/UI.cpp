#include "DxLib.h"
#include "UI.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Game.h"
#include <stdio.h>
#include "../Scene/TitleScene.h"
#include <fstream>
#include <iostream>
#include <string>
#include "../Scene/SceneManager.h"

#pragma warning(disable:4996)

UI::UI() :
	flashPoint(0),
	highScore(0),
	playerScoreHandle(FileRead_open("ScoreText/PlayerScore.txt"))
{
}

UI::~UI()
{
}

void UI::Init(Player& player, Enemy& enemy)
{
	highScore = 0;
	flashPoint = 0;
	playerScoreHandle = FileRead_open("ScoreText/PlayerScore.txt");
}

void UI::Update(Player& player, Enemy& enemy)
{
	
	/*���̒��Ƀ^�C�g���{�^�����������܂ł̏���������*/
	if (player.Player_GameOverFlag == false)
	{
		//�����_�ł̒l��ǉ����Ă���
		flashPoint++;

		//�l��10�ɂȂ�����O�ɂ���
		if (flashPoint == 10)
		{
			flashPoint = 0;
		}
	}	
	
	//�X�R�A���e�L�X�g�ɏ�������
	if (player.score >= highScore)
	{
		FILE* fp;

		fp = fopen("ScoreText/HighScore.txt", "r");

		fscanf_s(fp, "%d", &highScore);

		fclose(fp);
	}

}

void UI::Draw(Player& player, Enemy& enemy)
{
	if (flashPoint == 2 || flashPoint == 3 || flashPoint == 4 || flashPoint == 5 || flashPoint == 6 || flashPoint == 7 || flashPoint == 8)
	{
		DrawFormatString(50, 0, 0xffffff, "�P�t�o");
	}

	DrawFormatString(70, 20, 0xffffff, "%d", player.score);
	
	DrawFormatString(250, 0, 0xffffff, "�g�h�f�g�@�r�b�n�q�d");

	DrawFormatString(325, 20, 0xffffff, "%d", highScore);

}

void UI::Final()
{
}





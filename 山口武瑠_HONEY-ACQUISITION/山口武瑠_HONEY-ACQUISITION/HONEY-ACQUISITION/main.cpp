#include "DxLib.h"
#include "Game.h"
#include"Scene/SceneManager.h"
#include "Scene/SceneResult.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetWindowText("HaneyAcception");
	SetGraphMode(Game::WindowWidth, Game::WindowHeight - 50, Game::ColorBit);

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(false);//true�������\��//false�t���X�N���[��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager;

	pScene->Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		//��ʂ𕢂�������(6���̕s�����x)�̎l�p��\�����Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16);
		DrawBox(0, 0, 640, 480, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, false);


		pScene->Update();//�X�V

		pScene->Draw();//�`��
		 
		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}


		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	pScene->Final();

	delete pScene;//�������̉��

	pScene = nullptr;//pScene����ɂ���

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
//
//	@file	Main_Scene.h
//	@brief	���C���Q�[���V�[���Ǘ��N���X
//	@date	2016/11/08
//	@outher	�m�ȍ��c
#pragma once
#include "./Origin.h"
#include "./Read/XFileRead.h"
#include "./Stage/Stage.h"
#include "./Charactor/Player/JobManager.h"

class Main_Scene
{
	Stage* stage_;				//�X�e�[�W���
	JobManager** virChar_;	//�m�F�p���L�����N�^�[
public:
	Main_Scene();
	~Main_Scene();

	void Init(HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext);	//������
	void Update();																			//�X�V
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj);										//�`��
};


//
//	@file	MAIN.h
//	@brief	���C���N���X

//�w�b�_�[�t�@�C���̃C���N���[�h
#include "Origin.h"
#include "Main_Scene.h"
#include "./Camera.h"
//
//
//
class MAIN
{
public:
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCWSTR);	//�E�B���h�E������
	HRESULT InitD3D();										//������
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);				//�E�B���h�E�v���V�[�W��
	void Loop();		//�A�v���P�[�V�������������
	void App();			//�A�v���P�[�V��������
	void Update();		//�X�V����
	void Render();		//�`�揈��
	void DestroyD3D();	//�������

	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext *m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;
	ID3D11Texture2D* m_pBackBuffer_DSTex;

	Main_Scene* mainScene_;		//�Q�[�����C���V�[���N���X
	//Stage* stageMesh_;
	Camera* camera_;

};

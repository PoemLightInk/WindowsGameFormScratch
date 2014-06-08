//=============================================================================
// Name: XFileModelClass.h
//	Des: һ����װ��X�ļ���������Ⱦ���ܵ���ͷ�ļ�
// 2013�� 4��7��  Create by ǳī 
//=============================================================================

#pragma once
#include "D3DUtil.h"


class XFileModelClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D�豸����
	LPD3DXMESH						m_pMesh;       //����ģ�Ͷ���
	DWORD								m_dwNumMaterials; //���ʵ�����
	D3DMATERIAL9*					m_pMaterials;     //ģ�Ͳ��ʽṹ���ʵ��
	LPDIRECT3DTEXTURE9 *			m_pTextures;      //ģ������ṹ���ʵ��

public:
	XFileModelClass(IDirect3DDevice9 *pd3dDevice); //���캯��
	~XFileModelClass(void);     //��������   

public:
	HRESULT		LoadModelFromXFile(WCHAR* strFilename );  //��.X�ļ���ȡ��άģ�͵��ڴ���
	HRESULT		RenderModel( );  //��Ⱦ��ά����ģ��
	
};
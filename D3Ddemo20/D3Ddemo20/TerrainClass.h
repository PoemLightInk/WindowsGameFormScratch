//=============================================================================
// Name: TerrainClass.h
//	Des: һ����װ����ά����ϵͳ�����ͷ�ļ�
// 2013�� 3��17��  Create by ǳī 
//=============================================================================

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include  "D3DUtil.h"

class TerrainClass
{
private:
    LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D�豸
    LPDIRECT3DTEXTURE9			m_pTexture;				//����
    LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;			//���㻺��
    LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;		//��������

    int								m_nCellsPerRow;		// ÿ�еĵ�Ԫ����
    int								m_nCellsPerCol;			// ÿ�еĵ�Ԫ����
    int								m_nVertsPerRow;		// ÿ�еĶ�����
    int								m_nVertsPerCol;			// ÿ�еĶ�����
    int								m_nNumVertices;		// ��������
    FLOAT						m_fTerrainWidth;		// ���εĿ��
    FLOAT						m_fTerrainDepth;		// ���ε����
    FLOAT						m_fCellSpacing;			// ��Ԫ��ļ��
    FLOAT						m_fHeightScale;			// �߶�����ϵ��
    std::vector<FLOAT>   m_vHeightInfo;			// ���ڴ�Ÿ߶���Ϣ

	//����һ�����ε�FVF�����ʽ
    struct TERRAINVERTEX
    {
        FLOAT _x, _y, _z;
        FLOAT _u, _v;
        TERRAINVERTEX(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) 
            :_x(x), _y(y), _z(z), _u(u), _v(v) {}
        static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
    };

public:
    TerrainClass(IDirect3DDevice9 *pd3dDevice); //���캯��
    virtual ~TerrainClass(void);		//��������

public:
    BOOL LoadTerrainFromFile(wchar_t *pRawFileName, wchar_t *pTextureFile);		//���ļ����ظ߶�ͼ������ĺ���
    BOOL InitTerrain(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale);  //���γ�ʼ������
    BOOL RenderTerrain(D3DXMATRIX *pMatWorld, BOOL bDrawFrame=FALSE);  //������Ⱦ����
};

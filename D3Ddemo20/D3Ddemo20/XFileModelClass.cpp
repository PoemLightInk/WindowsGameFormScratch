//=============================================================================
// Name: XFileModelClass.h
//	Des: һ����װ��X�ļ���������Ⱦ���ܵ���Դ�ļ�
// 2013�� 4��7��  Create by ǳī 
//=============================================================================
#include <d3dx9.h>
#include <tchar.h> 
#include "XFileModelClass.h"

//-----------------------------------------------------------------------------
// Desc: ���캯��
//-----------------------------------------------------------------------------
XFileModelClass::XFileModelClass(IDirect3DDevice9* pd3dDevice)
{	
	//��������Ա��������ֵ
	m_pd3dDevice = pd3dDevice;
}

//--------------------------------------------------------------------------------------
// Name: XFileModelClass::LoadModelFromXFile()
// Desc: ��.X�ļ���ȡ��άģ�͵��ڴ���
//--------------------------------------------------------------------------------------
HRESULT XFileModelClass::LoadModelFromXFile( WCHAR* strFilename )
{

	LPD3DXBUFFER pAdjacencyBuffer = NULL;  //����ģ���ڽ���Ϣ
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;   //�洢����ģ�Ͳ��ʵĻ������

	//�Ӵ����ļ���������ģ��
	D3DXLoadMeshFromX( strFilename, D3DXMESH_MANAGED,  m_pd3dDevice, &pAdjacencyBuffer, 
		&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh );

	// ��ȡ���ʺ���������
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	//���Ӽ���ȡ�������Ժ������ļ���
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		//��ȡ���ʣ�������һ�»��������ɫֵ
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		//����һ���������
		m_pTextures[i] = NULL;
		if( d3dxMaterials[i].pTextureFilename != NULL && 
			strlen(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			//��������
			if( FAILED( D3DXCreateTextureFromFileA( m_pd3dDevice,d3dxMaterials[i].pTextureFilename, &m_pTextures[i] ) ) )
			{
				MessageBox(NULL, L"SORRY~!û���ҵ������ļ�!", L"XFileModelClass���ȡ�ļ�����", MB_OK);
			}
		}
	}
	//�Ż�����ģ��
	m_pMesh->OptimizeInplace( D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_STRIPREORDER,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL, NULL, NULL );

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Name: XFileModelClass::RenderModel()
// Desc: ��Ⱦ��ά����ģ��
//--------------------------------------------------------------------------------------
HRESULT XFileModelClass::RenderModel( )
{
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{

		m_pd3dDevice->SetMaterial( &m_pMaterials[i] );
		m_pd3dDevice->SetTexture( 0, m_pTextures[i] );
		m_pMesh->DrawSubset( i );
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// Desc: ��������
//-----------------------------------------------------------------------------
XFileModelClass::~XFileModelClass(void)
{
	//�ͷ�����ģ�Ͳ���
	SAFE_DELETE_ARRAY(m_pMaterials);

	//�ͷ�����ģ������
	if( m_pTextures )
	{
		for( DWORD i = 0; i < m_dwNumMaterials; i++ )
		{
			SAFE_RELEASE(m_pTextures[i]);
		}
		SAFE_DELETE_ARRAY(m_pTextures);
	}

	//�ͷ�����ģ�Ͷ���
	SAFE_RELEASE(m_pMesh);
}

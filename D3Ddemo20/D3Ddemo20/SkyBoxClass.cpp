//=============================================================================
// Name: SkyBoxClass.cpp
//	Des: һ����װ����ά��պ�ϵͳ�����Դ�ļ�
// 2013�� 3��24��  Create by ǳī 
//=============================================================================
#include "d3dx9.h"
#include "SkyBoxClass.h"
#include "D3DUtil.h"


//-------------------------------------------------------------------------------------------------
// Desc: ���캯��
//-------------------------------------------------------------------------------------------------
SkyBoxClass::SkyBoxClass( LPDIRECT3DDEVICE9  pDevice )
{
	//��������������ֵ
	m_pVertexBuffer=NULL;
	m_pd3dDevice=pDevice;
	for(int i=0; i<5; i++)
		m_pTexture[i] = NULL; 
	m_Length = 0.0f;
}

//-------------------------------------------------------------------------------------------------
// Name:  SkyBoxClass::InitSkyBox( )
// Desc: ��պг�ʼ�����������㻺�����ĸ�ֵ
//-------------------------------------------------------------------------------------------------
BOOL SkyBoxClass::InitSkyBox( float Length )
{
	m_Length=Length;

	//1.�������������㻺��
	 m_pd3dDevice->CreateVertexBuffer( 20 * sizeof(SKYBOXVERTEX), 0, 
		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0 );

	//��һ���ṹ��Ѷ���������׼����
	SKYBOXVERTEX vertices[] =
    {
		//ǰ����ĸ�����
		{ -m_Length/2, 0.0f,    m_Length/2, 0.0f, 1.0f, },
		{ -m_Length/2, m_Length/2,   m_Length/2, 0.0f, 0.0f, },
		{  m_Length/2, 0.0f,    m_Length/2, 1.0f, 1.0f, },
		{  m_Length/2, m_Length/2,   m_Length/2, 1.0f, 0.0f, },

		//������ĸ�����
		{  m_Length/2, 0.0f,   -m_Length/2, 0.0f, 1.0f, },
		{  m_Length/2, m_Length/2,  -m_Length/2, 0.0f, 0.0f, },
		{ -m_Length/2, 0.0f,   -m_Length/2, 1.0f, 1.0f, },
		{ -m_Length/2, m_Length/2,  -m_Length/2, 1.0f, 0.0f, },

		//������ĸ�����
		{ -m_Length/2, 0.0f,   -m_Length/2, 0.0f, 1.0f, },
		{ -m_Length/2, m_Length/2,  -m_Length/2, 0.0f, 0.0f, },
		{ -m_Length/2, 0.0f,    m_Length/2, 1.0f, 1.0f, },
		{ -m_Length/2, m_Length/2,   m_Length/2, 1.0f, 0.0f, },

		//������ĸ�����
		{ m_Length/2, 0.0f,   m_Length/2, 0.0f, 1.0f, },
		{ m_Length/2, m_Length/2,  m_Length/2, 0.0f, 0.0f, },
		{ m_Length/2, 0.0f,  -m_Length/2, 1.0f, 1.0f, },
		{ m_Length/2, m_Length/2, -m_Length/2, 1.0f, 0.0f, },

		//������ĸ�����
		{  m_Length/2, m_Length/2, -m_Length/2, 1.0f, 0.0f, },
		{  m_Length/2, m_Length/2,  m_Length/2, 1.0f, 1.0f, },
		{ -m_Length/2, m_Length/2, -m_Length/2, 0.0f, 0.0f, },
		{ -m_Length/2, m_Length/2,  m_Length/2, 0.0f, 1.0f, },

    };

	//׼����䶥������
    void* pVertices;
	//2.����
    m_pVertexBuffer->Lock( 0, 0, (void**)&pVertices, 0 );
	//3.���ʡ��ѽṹ���е�����ֱ�ӿ������㻺������
    memcpy( pVertices, vertices, sizeof(vertices) );
	//4.����
	m_pVertexBuffer->Unlock();

	 return TRUE;
}

//-------------------------------------------------------------------------------------------------
// Name:  SkyBoxClass::LoadSkyTextureFromFile( )
// Desc: ��պ�������غ���
//-------------------------------------------------------------------------------------------------
BOOL SkyBoxClass::LoadSkyTextureFromFile(
											wchar_t *pFrontTextureFile, 
											wchar_t *pBackTextureFile,
											wchar_t *pLeftTextureFile, 
											wchar_t *pRightTextureFile,
											wchar_t *pTopTextureFile)
{
	//���ļ�������������
	D3DXCreateTextureFromFile( m_pd3dDevice , pFrontTextureFile, &m_pTexture[0] );  //ǰ��
	D3DXCreateTextureFromFile( m_pd3dDevice , pBackTextureFile,  &m_pTexture[1] );  //����
	D3DXCreateTextureFromFile( m_pd3dDevice , pLeftTextureFile,  &m_pTexture[2] );  //����
	D3DXCreateTextureFromFile( m_pd3dDevice , pRightTextureFile, &m_pTexture[3] );  //����
	D3DXCreateTextureFromFile( m_pd3dDevice , pTopTextureFile,   &m_pTexture[4] );  //����	
	return TRUE;
}



//--------------------------------------------------------------------------------------
// Name: SkyBoxClass::RenderSkyBox()
// Desc: ���Ƴ���պУ�����ͨ���ڶ�������ѡ���Ƿ���Ƴ��߿�
//--------------------------------------------------------------------------------------
void SkyBoxClass::RenderSkyBox( D3DXMATRIX *pMatWorld, BOOL bRenderFrame )
{
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);  //��������ɫ��ϵĵ�һ����������ɫֵ�������
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );   //������ɫ��ϵĵ�һ��������ֵ��ȡ������ɫֵ
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatWorld );  //�����������
	m_pd3dDevice->SetStreamSource(0,m_pVertexBuffer, 0, sizeof(SKYBOXVERTEX));    //�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������  
	m_pd3dDevice->SetFVF(D3DFVF_SKYBOX);  //����FVF�����ʽ

	//һ��forѭ������5������Ƴ���
	for(int i =0; i<5; i++)
	{
		m_pd3dDevice->SetTexture(0, m_pTexture[i]);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);
	}

	//���Ƿ���Ⱦ�߿�Ĵ������
	if (bRenderFrame)  //���Ҫ��Ⱦ���߿�Ļ�
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //�����ģʽ��Ϊ�߿����
		//һ��forѭ������5������߿���Ƴ���
		for(int i =0; i<5; i++)
		{
			m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);	//���ƶ��� 
		}

		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	//�����ģʽ����ʵ�����
	}
}


//-------------------------------------------------------------------------------------------------
// Desc: ��������
//-------------------------------------------------------------------------------------------------
SkyBoxClass::~SkyBoxClass(void)
{
	SAFE_RELEASE( m_pVertexBuffer );
	for(int i=0; i<5; i++)
	{
		SAFE_RELEASE( m_pTexture[i] );
	}
}
//=============================================================================
// Name: SnowParticleClass.cpp
//	Des: һ����װ��ѩ������ϵͳϵͳ�����Դ�ļ�
// 2013�� 3��31��  Create by ǳī 
//=============================================================================

#include "d3dx9.h"
#include "SnowParticleClass.h"


//-------------------------------------------------------------------------------------------------
// Desc: ���캯��
//-------------------------------------------------------------------------------------------------
SnowParticleClass::SnowParticleClass(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//��������������ֵ
	m_pd3dDevice=pd3dDevice;
	m_pVertexBuffer=NULL;	
	for(int i=0; i<5; i++)
		m_pTexture[i] = NULL; 
}

//-------------------------------------------------------------------------------------------------
// Name:  SnowParticleClass::InitSnowParticle( )
// Desc: ����ϵͳ��ʼ������
//-------------------------------------------------------------------------------------------------
HRESULT SnowParticleClass::InitSnowParticle( )
{
	//��ʼ��ѩ����������
	srand(GetTickCount());
	for(int i=0; i<PARTICLE_NUMBER; i++)
	{	
		m_Snows[i].x        = float(rand()%SNOW_SYSTEM_LENGTH_X-SNOW_SYSTEM_LENGTH_X/2);
		m_Snows[i].z        = float(rand()%SNOW_SYSTEM_WIDTH_Z-SNOW_SYSTEM_WIDTH_Z/2);
		m_Snows[i].y        = float(rand()%SNOW_SYSTEM_HEIGHT_Y);
		m_Snows[i].RotationY     = (rand()%100)/50.0f*D3DX_PI;
		m_Snows[i].RotationX   = (rand()%100)/50.0f*D3DX_PI;
		m_Snows[i].FallSpeed   = 300.0f + rand()%500;
		m_Snows[i].RotationSpeed   = 5.0f +  rand()%10/10.0f;
		m_Snows[i].TextureIndex = rand()%6;
	}


	//����ѩ�����Ӷ��㻺��
	m_pd3dDevice->CreateVertexBuffer( 4*sizeof(POINTVERTEX), 0, 
		D3DFVF_POINTVERTEX,D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );

	//���ѩ�����Ӷ��㻺��
	POINTVERTEX vertices[] =
	{
		{ -30.0f, 0.0f, 0.0f,   0.0f, 1.0f, },
		{ -30.0f, 60.0f, 0.0f,   0.0f, 0.0f, },
		{  30.0f, 0.0f, 0.0f,   1.0f, 1.0f, }, 
		{  30.0f, 60.0f, 0.0f,   1.0f, 0.0f, }
	};
	//����
	VOID* pVertices;
	m_pVertexBuffer->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	//����
	memcpy( pVertices, vertices, sizeof(vertices) );
	//����
	m_pVertexBuffer->Unlock();

	//����6��ѩ������
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow1.jpg", &m_pTexture[0] );
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow2.jpg", &m_pTexture[1] );
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow3.jpg", &m_pTexture[2] );
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow4.jpg", &m_pTexture[3] );
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow5.jpg", &m_pTexture[4] );
	D3DXCreateTextureFromFile( m_pd3dDevice, L"GameMedia\\snow6.jpg", &m_pTexture[5] );

	return S_OK;
}


//-------------------------------------------------------------------------------------------------
// Name:  SnowParticleClass::UpdateSnowParticle( )
// Desc: ����ϵͳ���º���
//-------------------------------------------------------------------------------------------------
HRESULT SnowParticleClass::UpdateSnowParticle( float fElapsedTime)
{

	//һ��forѭ��������ÿ��ѩ�����ӵĵ�ǰλ�úͽǶ�
	for(int i=0; i<PARTICLE_NUMBER; i++)
	{
		m_Snows[i].y -= m_Snows[i].FallSpeed*fElapsedTime;

		//���ѩ�������䵽����, ���½���߶�����Ϊ���
		if(m_Snows[i].y<0)
			m_Snows[i].y = SNOW_SYSTEM_WIDTH_Z;
		//���������Ƕ�
		m_Snows[i].RotationY    += m_Snows[i].RotationSpeed * fElapsedTime;
		m_Snows[i].RotationX  += m_Snows[i].RotationSpeed * fElapsedTime;
	}

	return S_OK;
}


//-------------------------------------------------------------------------------------------------
// Name:  SnowParticleClass::RenderSnowParticle( )
// Desc: ����ϵͳ��Ⱦ����
//-------------------------------------------------------------------------------------------------
HRESULT SnowParticleClass::RenderSnowParticle(  )
{
	//��������Ч��
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, false );

	//��������״̬
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);   //��������ɫ��ϵĵ�һ����������ɫֵ�������
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );   //������ɫ��ϵĵ�һ��������ֵ��ȡ������ɫֵ
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );  //��С����״̬���������������
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR ); //�Ŵ����״̬���������������

	//����Alpha���ϵ��
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);   //��Alpha���
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);   //Դ���ϵ����Ϊ1
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);  //Ŀ����ϵ����Ϊ1

	//�����޳�ģʽΪ���޳��κ���
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//��Ⱦѩ��
	for(int i=0; i<PARTICLE_NUMBER; i++)
	{
		//���첢���õ�ǰѩ�����ӵ��������
		static D3DXMATRIX matYaw, matPitch, matTrans, matWorld;
		D3DXMatrixRotationY(&matYaw, m_Snows[i].RotationY);
		D3DXMatrixRotationX(&matPitch, m_Snows[i].RotationX);
		D3DXMatrixTranslation(&matTrans, m_Snows[i].x, m_Snows[i].y, m_Snows[i].z);
		matWorld = matYaw * matPitch * matTrans;
		m_pd3dDevice->SetTransform( D3DTS_WORLD,  &matWorld);

		//��Ⱦ��ǰѩ������
		m_pd3dDevice->SetTexture( 0, m_pTexture[m_Snows[i].TextureIndex] );    //��������
		m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(POINTVERTEX));  //�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������  
		m_pd3dDevice->SetFVF(D3DFVF_POINTVERTEX);    //����FVF�����ʽ
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //����

	}

	//�ָ������Ⱦ״̬��Alpha��� ���޳�״̬������
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, true );

	return S_OK;
}




//-------------------------------------------------------------------------------------------------
// Desc: ��������
//-------------------------------------------------------------------------------------------------
SnowParticleClass::~SnowParticleClass()
{
	SAFE_RELEASE(m_pVertexBuffer);

	for(int i=0;i<3; i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
}
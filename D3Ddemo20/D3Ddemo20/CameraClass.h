//=============================================================================
// Name: CameraClass.h
//	Des: һ����װ��ʵ����������������ͷ�ļ�
// 2013�� 3��10��  Create by ǳī 
//=============================================================================


#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CameraClass
{
private:
	//��Ա����������
    D3DXVECTOR3				m_vRightVector;        // �ҷ�������
    D3DXVECTOR3				m_vUpVector;           // �Ϸ�������
    D3DXVECTOR3				m_vLookVector;         // �۲췽������
    D3DXVECTOR3				m_vCameraPosition;        // �����λ�õ�����
	D3DXVECTOR3				m_vTargetPosition;        //Ŀ��۲�λ�õ�����
    D3DXMATRIX				m_matView;          // ȡ���任����
    D3DXMATRIX				m_matProj;          // ͶӰ�任����   
    LPDIRECT3DDEVICE9		m_pd3dDevice;  //Direct3D�豸����

public:
	//һ������ȡ���任�ĺ���
    VOID CalculateViewMatrix(D3DXMATRIX *pMatrix);    //����ȡ���任����

	//����Getϵ�к���
    VOID GetProjMatrix(D3DXMATRIX *pMatrix)  { *pMatrix = m_matProj; }  //���ص�ǰͶӰ����
    VOID GetCameraPosition(D3DXVECTOR3 *pVector)  { *pVector = m_vCameraPosition; } //���ص�ǰ�����λ�þ���
    VOID GetLookVector(D3DXVECTOR3 *pVector) { *pVector = m_vLookVector; }  //���ص�ǰ�Ĺ۲����

	//�ĸ�Setϵ�к�����ע�����ǲ�������Ĭ��ֵNULL�ģ�����ʱ��д����Ҳ����
    VOID SetTargetPosition(D3DXVECTOR3 *pLookat = NULL);  //�����������Ŀ��۲�λ������
    VOID SetCameraPosition(D3DXVECTOR3 *pVector = NULL); //������������ڵ�λ������
    VOID SetViewMatrix(D3DXMATRIX *pMatrix = NULL);  //����ȡ���任����
    VOID SetProjMatrix(D3DXMATRIX *pMatrix = NULL);  //����ͶӰ�任����

public:
    // �ظ�����ƽ�Ƶ���������
    VOID MoveAlongRightVec(FLOAT fUnits);   // ��right�����ƶ�
    VOID MoveAlongUpVec(FLOAT fUnits);      // ��up�����ƶ�
    VOID MoveAlongLookVec(FLOAT fUnits);    // ��look�����ƶ�

    // �Ƹ�������ת����������
    VOID RotationRightVec(FLOAT fAngle);    // ��right������ת
    VOID RotationUpVec(FLOAT fAngle);       // ��up������ת
    VOID RotationLookVec(FLOAT fAngle);     // ��look������ת

public:
	//���캯������������
	CameraClass(IDirect3DDevice9 *pd3dDevice);  //���캯��
	virtual ~CameraClass(void);  //��������

};

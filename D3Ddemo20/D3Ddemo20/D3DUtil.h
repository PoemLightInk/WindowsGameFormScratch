
//*****************************************************************************************
// Desc: D3DUtil.hͷ�ļ������ڹ���������Ķ���
// 2013�� 2��03��  Create by ǳī 
//*****************************************************************************************

#pragma once


#ifndef HR
#define HR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }         //�Զ���һ��HR�꣬����ִ�д���ķ���
#endif

#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }       //�Զ���һ��SAFE_RELEASE()��,����ָ����Դ���ͷ�
#endif    

#ifndef SAFE_RELEASE			
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }     //�Զ���һ��SAFE_RELEASE()��,����COM��Դ���ͷ�
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
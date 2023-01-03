/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "Frosbite.h"

bool fb::ClientSoldierEntity::GetBonePos(int BoneId, D3DXVECTOR3* vOut)
{
	BoneCollisionComponent* pBoneCollisionComponent = this->bonecollisioncomponent;
	if (!ValidPointer(pBoneCollisionComponent)) return false;

	if (!pBoneCollisionComponent->m_ragdollTransforms.m_ValidTransforms) return false;

	fb::UpdatePoseResultData::QuatTransform* pQuat = pBoneCollisionComponent->m_ragdollTransforms.m_ActiveWorldTransforms;
	if (!ValidPointer(pQuat)) return false;

	vOut->x = pQuat[BoneId].m_TransAndScale.x;
	vOut->y = pQuat[BoneId].m_TransAndScale.y;
	vOut->z = pQuat[BoneId].m_TransAndScale.z;
	//vOut->w = pQuat[BoneId].m_TransAndScale.w;

	return true;
}


bool fb::ClientSoldierEntity::GetBoneRotation(int BoneId, D3DXVECTOR3* vOut)
{
	BoneCollisionComponent* pBoneCollisionComponent = this->bonecollisioncomponent;
	if (!ValidPointer(pBoneCollisionComponent)) return false;

	if (!pBoneCollisionComponent->m_ragdollTransforms.m_ValidTransforms) return false;

	fb::UpdatePoseResultData::QuatTransform* pQuat = pBoneCollisionComponent->m_ragdollTransforms.m_ActiveWorldTransforms;
	if (!ValidPointer(pQuat)) return false;

	vOut->x = pQuat[BoneId].m_Rotation.x;
	vOut->y = pQuat[BoneId].m_Rotation.y;
	vOut->z = pQuat[BoneId].m_Rotation.z;
	//vOut->w = pQuat[BoneId].m_Rotation.w;

	return true;
}


bool WorldToScreen(D3DXVECTOR3 Pos, D3DXVECTOR2 &Point, float zRise)
{
	fb::GameRenderer* game_render = fb::GameRenderer::GetInstance();
	if (!ValidPointer(game_render) || !ValidPointer(game_render->renderView))
		return false;

	D3DXMATRIXA16 ViewProj = game_render->renderView->viewProj;
	float mX = g_drawRect.width / 2;
	float mY = g_drawRect.height / 2;

	float w = ViewProj(0, 3) * Pos.x + ViewProj(1, 3) * Pos.y + ViewProj(2, 3) * Pos.z + ViewProj(3, 3);

	if (w < 0.01f)
	{
		return false;
	}
	float x = ViewProj(0, 0) * Pos.x + ViewProj(1, 0) * Pos.y + ViewProj(2, 0) * Pos.z + ViewProj(3, 0);
	float y = ViewProj(0, 1) * Pos.x + ViewProj(1, 1) * Pos.y + ViewProj(2, 1) * (Pos.z + zRise) + ViewProj(3, 1);
	Point.x = (mX + mX * x / w);
	Point.y = (mY - mY * y / w);
	// Point.z = w;
	return true;
}
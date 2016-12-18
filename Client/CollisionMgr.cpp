#include "StdAfx.h"
#include "CollisionMgr.h"
#include "EnemyUnit.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::SkillCollision(list<CObj*>* pSkill, list<CObj*>* pEnemyUnit)
{
	RECT	rcCol;

	for(list<CObj*>::iterator Skilliter = pSkill->begin();
			Skilliter != pSkill->end(); ++Skilliter)
		{
			for(list<CObj*>::iterator	Enemyiter = pEnemyUnit->begin();
				Enemyiter != pEnemyUnit->end(); ++Enemyiter)
			{
				if(IntersectRect(&rcCol, &((*Skilliter))->GetRect(), &((*Enemyiter)->GetRect())))
				{
					int iHeight = rcCol.bottom  - rcCol.top ;
					int iWidth  = rcCol.right  - rcCol.left ; 
					
					if(iWidth > iHeight) // 상하충돌
					{
						if(!(*Skilliter)->GetHit())
						{
							if((*Skilliter)->GetObjKey() == L"Effect")
							{
								(*Enemyiter)->SetDamage(50);
								(*Skilliter)->SetHit(true);
							
								if((*Enemyiter)->GetStat()->iHealthPoint <=0)
								{
									(*Enemyiter)->SetDestroy(true);
								}
							}
						}

					}
					
					else
					{
						if(!(*Skilliter)->GetHit())
						{
							if((*Skilliter)->GetObjKey() == L"Effect")
							{
								(*Skilliter)->SetHit(true);
								(*Enemyiter)->SetDamage(50);
							
								if((*Enemyiter)->GetStat()->iHealthPoint <=0)
								{
									(*Enemyiter)->SetDestroy(true);
								}
							}
						}
					}	
				}
			}
	
		}

}

#include "StdAfx.h"
#include "CollisionMgr.h"
#include "EnemyUnit.h"
#include "Effect.h"

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
				if(IntersectRect(&rcCol, &((CEffect*)(*Skilliter))->GetRect(), &((*Enemyiter)->GetRect())))
				{
					if(!(*Skilliter)->GetHit())
					{
						(*Enemyiter)->SetDamage(50);
						(*Skilliter)->SetHit(true);
					
						if((*Enemyiter)->GetStat()->iHealthPoint <=0)
						{
							(*Enemyiter)->SetDestroy(true);
							/*(*Enemyiter)->SetOrder(OD_DIE);
							(*Enemyiter)->GetBridge()->SetFrame(L"Die");*/
						}
					}
				}
			}
		}

}

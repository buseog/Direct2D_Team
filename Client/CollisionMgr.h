#pragma once
#include "Obj.h"

class CCollisionMgr
{

public:
	static void SkillCollision(list<CObj*>* pSkill, list<CObj*>* pEnemyUnit);


public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};

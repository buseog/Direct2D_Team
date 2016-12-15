#pragma once

enum TEXTYPE
{
	TEX_SINGLE,
	TEX_MULTI,
	TEX_END
};

enum SCENEID
{
	SC_START,
	SC_MENU,
	SC_FILED,
	SC_VILLAGE,
	SC_BATTLEFIELD,
	SC_END
};

enum OBJID
{
	OBJ_BACK,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_END
};

enum UIID
{
	UI_MAIN,
	UI_INVEN,
	UI_STAT,
	UI_STORE,
	UI_END

};

enum ITEMID
{
	IT_WEAPON,
	IT_ARMOR,
	IT_GLOVE,
	IT_HELMET,
	IT_BOOTS,
	IT_BELT,
	IT_FOOD,
	IT_TRADE,
	IT_END
};


enum ORDERID
{
	OD_STAND,
	OD_ASTAR,
	OD_MOVE
};

enum DATAID		
{ 
	PLAYER_DATA, 
	PLAYER_MATRIX, 
	PLAYER_END
};
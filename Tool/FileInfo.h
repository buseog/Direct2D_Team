#pragma once

#include "Bigheader.h"

class CFileInfo
{
public:
	wstring		ConvertRelativePath(wstring wstrFullPath);

	void	DirInfoExtraction(const wstring& wstrPath, 
							list<IMGPATH*>& rPathInfoList);

	int		DirFileCount(const wstring& wstrPath);

public:
	CFileInfo(void);
	~CFileInfo(void);
};

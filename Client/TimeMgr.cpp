#include "StdAfx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr(void)
: m_fTime(0.f)
{
	ZeroMemory(&m_FrameTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_FixTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_LastTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}

CTimeMgr::~CTimeMgr(void)
{
}
float CTimeMgr::GetTime(void)
{
	return m_fTime;
}

void CTimeMgr::InitTime(void)
{
	QueryPerformanceCounter(&m_FrameTime);	// 1000
	QueryPerformanceCounter(&m_FixTime);	// 1003		
	QueryPerformanceCounter(&m_LastTime);	// 1012	

	QueryPerformanceFrequency(&m_CpuTick);	// 고해상도 타이머의 주기(초당 진동 수)를 반환하는 함수
}

void CTimeMgr::SetTime(void)
{
	QueryPerformanceCounter(&m_FrameTime);	// 1100 - 1003		//1500

	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}

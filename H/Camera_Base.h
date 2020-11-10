//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : CCD_Base.h
//
// (C) 2001-2014 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef CCD_BASE_H
#define CCD_BASE_H
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
//------------------------------------------------------------------------------------------
#include <Kutlstr.h>
#include <Kutltime.h>
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// â∫ãLÇÃenumÇÕÅCModule_Name[16]Ç…Ç†ÇÌÇπÇÈ
//enum { CCD_LL1L , CCD_LL2L , CCD_PMA , CCD_PMB , CCD_PMC , CCD_P1T1 , CCD_PME, CCD_PMF,
//       CCD_PMG  , CCD_PMH  , CCD_PMI  , CCD_PMJ  , CCD_PMK , CCD_PML , CCD_PMM  , CCD_P1T2 };
enum { CAM_ARM_A , CAM_ARM_B };
//------------------------------------------------------------------------------------------

int  Maint_CAM_Basis();
void Maint_CAM_BASIS_Pause();
void Maint_CAM_BASIS_Continue();
	
#endif

//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Sys_Align.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef SYS_ALIGN_H
#define SYS_ALIGN_H
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
// SYS_AL_Station(DIO)óp, enum MtlRecvStn2 Ç…çáÇÌÇπÇÈ
// 2015.03.26 enum Ç PASS1çÌèúÅATr2.P1 Å® PM-G ïœçXÇ…ëŒâûÇ≥ÇπÇÈ
enum {
	SYS_LPMA , SYS_LPMB , SYS_LPMC , SYS_LPMD ,
	SYS_Aligner ,
	SYS_LLA_ATM , SYS_LLB_ATM ,
	SYS_LLA_VAC , SYS_LLB_VAC ,
	SYS_PM1 , SYS_PM2 , SYS_PM3 , SYS_PM4 , SYS_PM14 , 
	SYS_PM5 , SYS_PM6 , SYS_PM7 , SYS_PM8 , SYS_PM9  , SYS_PM10 ,
	SYS_PM12_1 , SYS_PM12_2 };
// Å´Double PASS
//enum {
//	SYS_LPMA , SYS_LPMB , SYS_LPMC , SYS_LPMD ,
//	SYS_Aligner ,
//	SYS_LLA_ATM , SYS_LLB_ATM ,
//	SYS_LLA_VAC , SYS_LLB_VAC ,
//	SYS_PM1 , SYS_PM2 , SYS_PM3 , SYS_PM4 ,
//	SYS_PM5 , SYS_PM6 , SYS_PM7 , SYS_PM8 , SYS_PM9 , SYS_PM10 ,
//	SYS_PM11_1 , SYS_PM11_2 , SYS_PM12_1 , SYS_PM12_2 };
//------------------------------------------------------------------------------------------

void Maint_SysAlign_SET_RUN_MODE( int data );

int  Maint_Sys_Alignment( int type , int option );

//------------------------------------------------------------------------------------------

int  Maint_SysAlign_MAINT_INTERFACE_RUN( LPSTR list , ... );

BOOL Maint_SysAlign_IO_FIND_CM_WIO( int Cass , int Slot , int ckdata );
BOOL Maint_SysAlign_IO_FIND_TM_WIO( int Tms , int Arm , int ckdata );
BOOL Maint_SysAlign_IO_FIND_FM_WIO( int Arm , int ckdata );
BOOL Maint_SysAlign_IO_FIND_PM_WIO( int Chamber , int ckdata );
BOOL Maint_SysAlign_IO_FIND_PM_WIO2( int Chamber , int ckdata );
BOOL Maint_SysAlign_IO_FIND_BM_WIO( int Ch , int Slot , int ckdata , int * , int * );

BOOL Maint_SysAlign_IO_FIND_FAL_WIO( int ckdata , int * , int * );
BOOL Maint_SysAlign_IO_FIND_FM_WDATA( int Arm , int *sdata , int *wdata );
BOOL Maint_SysAlign_IO_FIND_TM_WDATA( int Tms , int Arm , int *sdata , int *wdata );
BOOL Maint_SysAlign_IO_FIND_PM_WDATA( int ch , int *sdata , int *wdata );

#endif

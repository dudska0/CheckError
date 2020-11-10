//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Transfer.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef TRANSFER_H
#define TRANSFER_H
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
#ifdef EQ_TYPE_IARIM2A
	//------------------------------------------------------------------------------------------
	// IARIM2(SingleLL仕様)
	//------------------------------------------------------------------------------------------
	enum {
		TR_LPMA , TR_LPMB , TR_LPMC , TR_LPMD ,
		TR_FAL ,
		TR_LLA , TR_LLB , 
		TR_PM1 , TR_PM2 , TR_PM3 , TR_PM4 , TR_PM5 , TR_PM6 , TR_PM7 , TR_PM8 , TR_PM9 , TR_PM10 , TR_PM11 , TR_PM12 , TR_PM13 , TR_PM14 , TR_PM15 ,
		TR_FM  , TR_TM1 , TR_TM2 , TR_TM3 ,
		// 下記は仕様にないため関係のない数値を代入
		TR_LLC=100 , TR_LLD=101
	};

	// 2015.03.26 PM14追加、PM11削除
	enum {
		BTR_NONE , BTR_LPMA , BTR_LPMB , BTR_LPMC , BTR_LPMD ,
		BTR_FAL ,
		BTR_LLA , BTR_LLB , 
		BTR_PM1 , BTR_PM2 , BTR_PM3 , BTR_PM4 , BTR_PM5 , BTR_PM6 , BTR_PM7 , BTR_PM8 , BTR_PM9 , BTR_PM10 ,
		BTR_PM14, BTR_PM12,
		// 下記は仕様にないため関係のない数値を代入
		BTR_LLC=100 , BTR_LLD=101
	};

#else
	//------------------------------------------------------------------------------------------
	// IARIM2(QuadroLL仕様)
	//------------------------------------------------------------------------------------------
	enum {
		TR_LPMA , TR_LPMB , TR_LPMC , TR_LPMD ,
		TR_FAL ,
		TR_LLA , TR_LLB , TR_LLC , TR_LLD ,
		TR_PM1 , TR_PM2 , TR_PM3 , TR_PM4 , TR_PM5 , TR_PM6 , TR_PM7 , TR_PM8 , TR_PM9 , TR_PM10 , TR_PM11 , TR_PM12 , TR_PM13 , TR_PM14 , TR_PM15 ,
		TR_FM , TR_TM1 , TR_TM2 , TR_TM3
	};

	// 2015.03.26 PM11削除
	enum {
		BTR_NONE , BTR_LPMA , BTR_LPMB , BTR_LPMC , BTR_LPMD ,
		BTR_FAL ,
		BTR_LLA , BTR_LLB , BTR_LLC , BTR_LLD ,
		BTR_PM1 , BTR_PM2 , BTR_PM3 , BTR_PM4 , BTR_PM5 , BTR_PM6 , BTR_PM7 , BTR_PM8 , BTR_PM9 , BTR_PM10 ,
		BTR_PM14, BTR_PM12
	};
#endif
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

enum {
	TR_ARM_A , TR_ARM_B
};
//------------------------------------------------------------------------------------------
int Maint_Transfer_Move();
//------------------------------------------------------------------------------------------
int Maint_Transfer_Batch();
int Maint_Batch_IO_All_Clear();
//------------------------------------------------------------------------------------------
int Maint_Transfer_Clear();
//------------------------------------------------------------------------------------------
void Maint_Transfer_Pause();
void Maint_Transfer_Continue();
void Maint_Transfer_Abort();
//------------------------------------------------------------------------------------------
void Maint_Transfer_TR_GUI( char * );
//------------------------------------------------------------------------------------------
void Maint_Transfer_SET_RUN_MODE( int data );

#endif

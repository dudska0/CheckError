//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Fine_Tune.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef FINE_TUNE_H
#define FINE_TUNE_H
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
enum {
	FT_READY ,
	FT_NOTSELECT ,
	FT_ARM_HAS_WAFER ,
	FT_NO_WAFER ,
	FT_FAILED ,
	FT_PREPARE ,
	FT_PICK_PM ,
	FT_PLACE_AL ,
	FT_ALIGNING ,
	FT_PICK_AL_R ,
	FT_PLACE_PM_R ,
	FT_SUCCESS ,
};
//------------------------------------------------------------------------------------------

void Maint_FineTune_SET_RUN_MODE( int data );
void Maint_FineTune_SET_MAX_PM( int data );
void Maint_FineTune_SET_MAX_BM( int data );
void Maint_FineTune_SET_PER_GROUP_PM( char *data );
void Maint_FineTune_SET_PER_GROUP_BM( char *data );
void Maint_FineTune_SET_AL_STATION( int data );
BOOL Maint_FineTune_SET_FUNCTION_ALIGN( char *data );
BOOL Maint_FineTune_SET_FUNCTION_ALIGN2( char *data );
//
int  Maint_FineTune_Aligning( int tm , int Arm , int pm , int Pathmode ); // 2006.09.03
int  Maint_Transfer_Aligning( int tm , int Arm , int pm , int Pathmode ); // 2006.09.03

int  Maint_Transfer_Aligning2( int tm , int Arm , int pm , int Pathmode );

int  Maint_Fine_Tune();
int  Maint_Notch_Angle_Correct();
int  Maint_Notch_Angle_Check();

#endif

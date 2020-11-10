//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Mtl_Recv_Sub.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef MTL_RECV_SUB_H
#define MTL_RECV_SUB_H
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
enum { MTL_SUB_REAL_CHECK , MTL_SUB_WAFER_SET , MTL_SUB_WAFER_CLEAR };
//------------------------------------------------------------------------------------------
enum { MTL_PART_CM , MTL_PART_FM , MTL_PART_FAL , MTL_PART_TM , MTL_PART_BM , MTL_PART_PM , MTL_PART_BM_F , MTL_PART_PM_F };
//------------------------------------------------------------------------------------------
void Maint_Material_Recovery_SET_RUN_MODE( int data );
void Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( int tms , int data );
void Maint_Material_Recovery_SET_CASSETTE_MAXSLOT( int data );
void Maint_Material_Recovery_SET_BUFFER_MAXSLOT( int data );
void Maint_Material_Recovery_SET_FALSNS_CHECK_STYLE( int data );
//
BOOL Maint_Material_Recovery_SET_FUNCTION_ROBOT( int tms , char *data );
BOOL Maint_Material_Recovery_SET_IO_FMASNS( char *data );
BOOL Maint_Material_Recovery_SET_IO_FMBSNS( char *data );
BOOL Maint_Material_Recovery_SET_IO_FALSNS( char *data );
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Check_CM( int Mode , int CassChamber , int Slot );
int Maint_Material_Recovery_Check_FM( int Mode , int Arm , int PresentSetValue , int *Sel );
int Maint_Material_Recovery_Check_FAL( int Mode , int PresentSetValue );
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Check_TM( int Mode , int tms , int Station , int Arm , int PresentSetValue , int *Sel );
int Maint_Material_Recovery_Check_PM( BOOL fm , int Mode , int tms , int Chamber , int Arm , int PresentSetValue );
int Maint_Material_Recovery_Check_BM( BOOL fm , int Mode , int tms , int Chamber , int Arm , int Slot , int PresentSetValue );
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Check( int RunPart , int CheckType , int TmSide , int ModuleIndex , int RunArm , int RunSlot , int PresentSetValue , int *Rec_Arm );
//------------------------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Mtl_Recv.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef MTL_RECV_H
#define MTL_RECV_H
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
enum { MTL_TYPE_REAL_ALL , MTL_TYPE_REAL_PART , MTL_TYPE_OCCUPY , MTL_TYPE_CLEAR };
//------------------------------------------------------------------------------------------
// 2015.03.26 enum MtlRecvStn Ç…çáÇÌÇπÇƒïœçX
enum {
	MTL_LPMA , MTL_LPMB , MTL_LPMC , MTL_LPMD ,
	MTL_FM , MTL_Aligner ,
	MTL_LLA_ATM , MTL_LLB_ATM ,
	MTL_LLA_VAC , MTL_LLB_VAC ,
	MTL_TM , MTL_TM2 ,
	MTL_PM1/*PM-A*/ , MTL_PM2/*PM-B*/ , MTL_PM3/*PM-E*/ , MTL_PM4/*PM-F*/ , MTL_PM14/*PM-G*/,
	MTL_PM5/*PM-H*/ , MTL_PM6/*PM-I*/ , MTL_PM7/*PM-J*/ , MTL_PM8/*PM-K*/ , MTL_PM9/*PM-L*/ , MTL_PM10/*PM-M*/ , 
	MTL_PM12_1
	};
//enum {
//	MTL_LPMA , MTL_LPMB , MTL_LPMC , MTL_LPMD ,
//	MTL_FM , MTL_Aligner ,
//	MTL_LLA_ATM , MTL_LLB_ATM ,
//	MTL_LLA_VAC , MTL_LLB_VAC ,
//	MTL_TM , MTL_TM2 ,
//	MTL_PM1/*PM-A*/ , MTL_PM2/*PM-B*/ , MTL_PM3/*PM-E*/ ,
//	MTL_PM4/*PM-F*/ , MTL_PM5/*PM-H*/ , MTL_PM6/*PM-I*/ ,
//	MTL_PM7/*PM-J*/ , MTL_PM8/*PM-K*/ , MTL_PM9/*PM-L*/ , MTL_PM10/*PM-M*/ ,
//	MTL_PM11_1 , MTL_PM12_1
//	};
//
//------------------------------------------------------------------------------------------
void Maint_Material_Recovery_SET_RUN_MODE( int data );
void Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( int tms , int data );
void Maint_Material_Recovery_SET_CASSETTE_MAXSLOT( int data );
void Maint_Material_Recovery_SET_BUFFER_MAXSLOT( int data );
void Maint_Material_Recovery_SET_FALSNS_CHECK_STYLE( int data );
//
BOOL Maint_Material_Recovery_SET_FUNCTION_ROBOT( int tms , char *data );
BOOL Maint_Material_Recovery_SET_FUNCTION_TMSNS( int tms , char *data );
BOOL Maint_Material_Recovery_SET_IO_FMASNS( char *data );
BOOL Maint_Material_Recovery_SET_IO_FMBSNS( char *data );
BOOL Maint_Material_Recovery_SET_IO_FALSNS( char *data );

BOOL Maint_Material_Recovery_SET_FUNCTION_PMSNS( char *data );
BOOL Maint_Material_Recovery_SET_FUNCTION_MAPPING( int cass , char *data );
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Map( int type );
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Empty_All( BOOL all );
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_All( BOOL all );
//------------------------------------------------------------------------------------------

#endif

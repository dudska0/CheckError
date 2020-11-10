//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Fine_Tune.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"
#include "Fine_Tune.h"
#include "Mtl_Recv_Sub.h"
#include "Sys_Align.h"
//------------------------------------------------------------------------------------------
#include "Kutlgui.h"
#include "..\resource.h"
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
extern BOOL SIMULATION_MODE;
//------------------------------------------------------------------------------------------
extern IO_Name_String_Map IO_STR_Map_Table[];
//------------------------------------------------------------------------------------------
//=========================================================================================================
int	Address_FINETUNE_IO_Init = FALSE;
//
int	Address_FINETUNE_Transfer_Status;
int	Address_FINETUNE_Scheduler;
//
int	Address_FINETUNE_TM_WIO[4][2];

int Address_FINETUNE_F_FAL;
int Address_FINETUNE_F_FAL2;

int Address_FINETUNE_CHECK_PM[60];

int Address_FINETUNE_STATUS_PM[60];
int Address_FINETUNE_OLD_R_POS_PM[60];
int Address_FINETUNE_OLD_T_POS_PM[60];
int Address_FINETUNE_NEW_R_POS_PM[60];
int Address_FINETUNE_NEW_T_POS_PM[60];

int Address_FINETUNE_CHECK_BM[10];

int Address_FINETUNE_STATUS_BM[10];
int Address_FINETUNE_OLD_R_POS_BM[10];
int Address_FINETUNE_OLD_T_POS_BM[10];
int Address_FINETUNE_NEW_R_POS_BM[10];
int Address_FINETUNE_NEW_T_POS_BM[10];

int Address_FINETUNE_OLD_R_RPOS;
int Address_FINETUNE_OLD_T_RPOS;
int Address_FINETUNE_NEW_R_RPOS;
int Address_FINETUNE_NEW_T_RPOS;

int Address_FINETUNE_CHECK_ARM;
int Address_FINETUNE_CHECK_STATION;
int Address_FINETUNE_CHECK_TMS;

int Address_NOTCH_CORRECT_CHECK_ARM;
int Address_NOTCH_CORRECT_CHECK_TR;

char Address_FINETUNE_fstr_FAL[64] = { 0 , };
char Address_FINETUNE_fstr_FAL2[64] = { 0 , };
//=========================================================================================================
int FINETUNE_GROUP_PM[60];
int FINETUNE_GROUP_BM[10];
extern int SYSALIGN_RUNMODE;
int FINETUNE_RUNMODE	= 3;
// 2015.04.02 PM14追加
int FINETUNE_MAX_PM		= 11;
//int FINETUNE_MAX_PM		= 10;
//
int FINETUNE_MAX_BM		= 2;
int FINETUNE_AL_STATION	= -1;
//=========================================================================================================
// 2015.04.02 PM14追加
int FINETUNE_PM_ORDER[] = { 1, 2, 3, 4, 14, 5, 6, 7, 8, 9, 10, 12, 12 };
//                          0  1  2  3  4  5  6  7  8   9  10  11
//int FINETUNE_PM_ORDER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 12 };
//=========================================================================================================
//=========================================================================================================
// 2013/05/07 ----------------------------------------------------------------->>
char NOTCH_ANGLE_SETTING_TR[2][4] = { "TR1" , "TR2" };
char NOTCH_ANGLE_SETTING_ARM[2][2] = { "A" , "B" };
// 2013/05/07 -----------------------------------------------------------------<<

void Maint_FineTune_SET_RUN_MODE( int data ) {
	FINETUNE_RUNMODE = data;
}

void Maint_FineTune_SET_MAX_PM( int data ) {
	FINETUNE_MAX_PM = data;
}

void Maint_FineTune_SET_MAX_BM( int data ) {
	FINETUNE_MAX_BM = data;
}

void Maint_FineTune_SET_AL_STATION( int data ) {
	FINETUNE_AL_STATION = data;
}

void Maint_FineTune_SET_PER_GROUP_PM( char *data ) {
	int i , l;
	l = strlen( data );
	for ( i = 0 ; i < 60 ; i++ ) {
		FINETUNE_GROUP_PM[i] = 0;
	}
	for ( i = 0 ; i < l ; i++ ) {
		if ( ( data[i] >= '0' ) && ( data[i] <= '9' ) ) {
			FINETUNE_GROUP_PM[i] = data[i] - '0';
		}
	}
}

void Maint_FineTune_SET_PER_GROUP_BM( char *data ) {
	int i , l;
	l = strlen( data );
	for ( i = 0 ; i < 10 ; i++ ) {
		FINETUNE_GROUP_BM[i] = 0;
	}
	for ( i = 0 ; i < l ; i++ ) {
		if ( ( data[i] >= '0' ) && ( data[i] <= '9' ) ) {
			FINETUNE_GROUP_BM[i] = data[i] - '0';
		}
	}
}

BOOL Maint_FineTune_SET_FUNCTION_ALIGN( char *data ) {
	strncpy( Address_FINETUNE_fstr_FAL , data , 63 );
	return TRUE;
}

BOOL Maint_FineTune_SET_FUNCTION_ALIGN2( char *data ) {
	strncpy( Address_FINETUNE_fstr_FAL2 , data , 63 );
	return TRUE;
}

//=========================================================================================================
BOOL Maint_FineTune_IO_FIND( int mode , char *ioname , int *ioaddress ) {
	int i , j;
	if ( !Address_FINETUNE_IO_Init ) {

		Address_FINETUNE_IO_Init = TRUE;
		//=========================================================
		Address_FINETUNE_Transfer_Status = -2;
		Address_FINETUNE_Scheduler = -2;
		//=========================================================
		if ( Address_FINETUNE_fstr_FAL[0] == 0 ) strcpy( Address_FINETUNE_fstr_FAL , "TMC_ALIGNER_CONTROL" );
		Address_FINETUNE_F_FAL = -2;
		if ( Address_FINETUNE_fstr_FAL2[0] == 0 ) strcpy( Address_FINETUNE_fstr_FAL2 , "TMC_ALIGNER2_CONTROL" );
		Address_FINETUNE_F_FAL2 = -2;
		//=========================================================
		Address_FINETUNE_CHECK_ARM = -2;
		Address_FINETUNE_CHECK_STATION = -2;
		Address_FINETUNE_CHECK_TMS = -2;
		//
		Address_NOTCH_CORRECT_CHECK_ARM = -2;
		Address_NOTCH_CORRECT_CHECK_TR	= -2;	
		//
		Address_FINETUNE_OLD_R_RPOS = -2;
		Address_FINETUNE_OLD_T_RPOS = -2;
		Address_FINETUNE_NEW_R_RPOS = -2;
		Address_FINETUNE_NEW_T_RPOS = -2;

		for ( i = 0 ; i < 60 ; i++ ) {
			Address_FINETUNE_CHECK_PM[i] = -2;

			Address_FINETUNE_STATUS_PM[i] = -2;

			Address_FINETUNE_OLD_R_POS_PM[i] = -2;
			Address_FINETUNE_OLD_T_POS_PM[i] = -2;
			Address_FINETUNE_NEW_R_POS_PM[i] = -2;
			Address_FINETUNE_NEW_T_POS_PM[i] = -2;
		}
		//
		for ( i = 0 ; i < 10 ; i++ ) {
			Address_FINETUNE_CHECK_BM[i] = -2;

			Address_FINETUNE_STATUS_BM[i] = -2;

			Address_FINETUNE_OLD_R_POS_BM[i] = -2;
			Address_FINETUNE_OLD_T_POS_BM[i] = -2;
			Address_FINETUNE_NEW_R_POS_BM[i] = -2;
			Address_FINETUNE_NEW_T_POS_BM[i] = -2;
		}
		//
		for ( i = 0 ; i < 4 ; i++ ) {
			for ( j = 0 ; j < 2 ; j++ ) {
				Address_FINETUNE_TM_WIO[i][j] = -2;
			}
		}
		//=========================================================
	}
	if ( *ioaddress == -2 ) {
		if      ( mode == _K_D_IO ) {
			*ioaddress = _FIND_FROM_STRING( _K_D_IO , ioname );
		}
		else if ( mode == _K_A_IO ) {
			*ioaddress = _FIND_FROM_STRING( _K_A_IO , ioname );
		}
		else if ( mode == _K_S_IO ) {
			*ioaddress = _FIND_FROM_STRING( _K_S_IO , ioname );
		}
		else if ( mode == _K_F_IO ) {
			*ioaddress = _FIND_FROM_STRING( _K_F_IO , ioname );
		}
		else {
			return FALSE;
		}
	}
	if ( *ioaddress == -1 ) return FALSE;
	return TRUE;
}

BOOL Maint_FineTune_IO_FIND_TM_WIO( int Tms , int Arm , int ckdata ) {
	int CommStatus;
	char Buffer[32];
	if ( Tms == 1 ) {
		if ( Arm == 0 ) {
			sprintf( Buffer , "CTC.TA_Wafer_Status" );
		}
		else {
			sprintf( Buffer , "CTC.TB_Wafer_Status" );
		}
	}
	else {
		if ( Arm == 0 ) {
			sprintf( Buffer , "CTC.TA%d_Wafer_Status" , Tms );
		}
		else {
			sprintf( Buffer , "CTC.TB%d_Wafer_Status" , Tms );
		}
	}
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , Buffer , &(Address_FINETUNE_TM_WIO[Tms-1][Arm]) ) ) return FALSE;
	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_FINETUNE_TM_WIO[Tms-1][Arm] , &CommStatus ) != ckdata ) return FALSE;
	}
	return TRUE;
}

int Maint_FineTune_PM11_WIO( ) {
	int ioaddress;
	char Buffer[32];
	int CommStatus;

	sprintf( Buffer , "CTC.PM11_Wafer_Status" );
	
	ioaddress = _FIND_FROM_STRING( _K_D_IO , Buffer );
	if ( ioaddress == -1 ) return -1;
	return ( _dREAD_DIGITAL( ioaddress , &CommStatus ) );
}

int Maint_FineTune_PM12_WIO( ) {
	int ioaddress;
	char Buffer[32];
	int CommStatus;

	sprintf( Buffer , "CTC.PM12_Wafer_Status" );
	
	ioaddress = _FIND_FROM_STRING( _K_D_IO , Buffer );
	if ( ioaddress == -1 ) return -1;
	return ( _dREAD_DIGITAL( ioaddress , &CommStatus ) );
}

BOOL Maint_FineTune_IO_FINETUNE_STATUS_PM_SET( int chamber , int data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_STATUS_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , Buffer , &(Address_FINETUNE_STATUS_PM[chamber-1]) ) ) return FALSE;
	_dWRITE_DIGITAL( Address_FINETUNE_STATUS_PM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( int chamber , int data ) {
	int CommStatus;
	WRITE_DIGITAL( FINETUNE_STATUS_PM1 + chamber - 1 , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( int chamber , int data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_STATUS_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , Buffer , &(Address_FINETUNE_STATUS_BM[chamber-1]) ) ) return FALSE;
	_dWRITE_DIGITAL( Address_FINETUNE_STATUS_BM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_OLD_R_POS_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_OLD_R_POS_PM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_OLD_R_POS_PM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( int chamber , double data ) {
	int CommStatus;
	WRITE_ANALOG( FINETUNE_OLD_R_POS_PM1 + chamber - 1 , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_R_POS_BM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_OLD_R_POS_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_OLD_R_POS_BM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_OLD_R_POS_BM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_OLD_T_POS_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_OLD_T_POS_PM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_OLD_T_POS_PM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( int chamber , double data ) {
	int CommStatus;
	WRITE_ANALOG( FINETUNE_OLD_T_POS_PM1 + chamber - 1 , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_OLD_T_POS_BM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_OLD_T_POS_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_OLD_T_POS_BM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_OLD_T_POS_BM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_NEW_R_POS_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_NEW_R_POS_PM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_NEW_R_POS_PM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( int chamber , double data ) {
	int CommStatus;
	WRITE_ANALOG( FINETUNE_NEW_R_POS_PM1 + chamber - 1 , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_R_POS_BM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_NEW_R_POS_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_NEW_R_POS_BM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_NEW_R_POS_BM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_NEW_T_POS_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_NEW_T_POS_PM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_NEW_T_POS_PM[chamber-1] , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( int chamber , double data ) {
	int CommStatus;
	WRITE_ANALOG( FINETUNE_NEW_T_POS_PM1 + chamber - 1 , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FINETUNE_NEW_T_POS_BM_SET( int chamber , double data ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_NEW_T_POS_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , Buffer , &(Address_FINETUNE_NEW_T_POS_BM[chamber-1]) ) ) return FALSE;
	_dWRITE_ANALOG( Address_FINETUNE_NEW_T_POS_BM[chamber-1] , data , &CommStatus );
	return TRUE;
}

double Maint_FineTune_IO_FINETUNE_OLD_R_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , "FINETUNE_OLD_R_POS" , &Address_FINETUNE_OLD_R_RPOS ) ) return 0;
	return _dREAD_ANALOG( Address_FINETUNE_OLD_R_RPOS , &CommStatus );
}

double Maint_FineTune_IO_FINETUNE_OLD_T_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , "FINETUNE_OLD_T_POS" , &Address_FINETUNE_OLD_T_RPOS ) ) return 0;
	return _dREAD_ANALOG( Address_FINETUNE_OLD_T_RPOS , &CommStatus );
}

double Maint_FineTune_IO_FINETUNE_NEW_R_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , "FINETUNE_NEW_R_POS" , &Address_FINETUNE_NEW_R_RPOS ) ) return 0;
	return _dREAD_ANALOG( Address_FINETUNE_NEW_R_RPOS , &CommStatus );
}

double Maint_FineTune_IO_FINETUNE_NEW_T_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_A_IO , "FINETUNE_NEW_T_POS" , &Address_FINETUNE_NEW_T_RPOS ) ) return 0;
	return _dREAD_ANALOG( Address_FINETUNE_NEW_T_RPOS , &CommStatus );
}

int Maint_FineTune_IO_FINETUNE_CHECK_PM_GET( int chamber ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_CHECT_PM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , Buffer , &(Address_FINETUNE_CHECK_PM[chamber-1]) ) ) return 1;
	return _dREAD_DIGITAL( Address_FINETUNE_CHECK_PM[chamber-1] , &CommStatus );
}

int Maint_FineTune_IO_FINETUNE_CHECK_PM_GET2( int chamber ) {
	int CommStatus;
	return READ_DIGITAL( FINETUNE_CHECT_PM1 + chamber - 1 , &CommStatus );
}

int Maint_FineTune_IO_FINETUNE_CHECK_BM_GET( int chamber ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "FINETUNE_CHECT_BM%d" , chamber );
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , Buffer , &(Address_FINETUNE_CHECK_BM[chamber-1]) ) ) return 1;
	return _dREAD_DIGITAL( Address_FINETUNE_CHECK_BM[chamber-1] , &CommStatus );
}

int Maint_FineTune_IO_FINETUNE_CHECK_ARM_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "FINETUNE_CHECK_ARM" , &(Address_FINETUNE_CHECK_ARM) ) ) return 0;
	return _dREAD_DIGITAL( Address_FINETUNE_CHECK_ARM , &CommStatus );
}

int Maint_FineTune_IO_NOTCH_CORRECT_CHECK_ARM_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "NOTCH_CORRECT_CHECK_ARM" , &(Address_NOTCH_CORRECT_CHECK_ARM) ) ) return 0;
	return _dREAD_DIGITAL( Address_NOTCH_CORRECT_CHECK_ARM , &CommStatus );
}

int Maint_FineTune_IO_NOTCH_CORRECT_CHECK_TR_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "NOTCH_CORRECT_CHECK_TR" , &(Address_NOTCH_CORRECT_CHECK_TR) ) ) return 0;
	return _dREAD_DIGITAL( Address_NOTCH_CORRECT_CHECK_TR , &CommStatus );
}

int Maint_FineTune_IO_FINETUNE_CHECK_TMS_GET() {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "FINETUNE_CHECK_TMS" , &(Address_FINETUNE_CHECK_TMS) ) ) return 0;
	return _dREAD_DIGITAL( Address_FINETUNE_CHECK_TMS , &CommStatus );
}

BOOL Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( int data ) {
	int CommStatus;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "FINETUNE_CHECK_STATION" , &(Address_FINETUNE_CHECK_STATION) ) ) return FALSE;
	_dWRITE_DIGITAL( Address_FINETUNE_CHECK_STATION , data , &CommStatus );
	return TRUE;
}

BOOL Maint_FineTune_IO_FIND_F_AL() {
	return Maint_FineTune_IO_FIND( _K_F_IO , Address_FINETUNE_fstr_FAL , &Address_FINETUNE_F_FAL );
}

BOOL Maint_FineTune_IO_FIND_F_AL2() {
	return Maint_FineTune_IO_FIND( _K_F_IO , Address_FINETUNE_fstr_FAL2 , &Address_FINETUNE_F_FAL2 );
}

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_FineTune_MAINT_INTERFACE_RUN( LPSTR list , ... ) {
	va_list va;
	int CommStatus;
	char Buffer[256];
	char Buffer2[256];
	//
	if ( !Maint_FineTune_IO_FIND( _K_S_IO , "e:SCHEDULER"   , &Address_FINETUNE_Scheduler ) ) return SYS_ABORTED;
	if ( !Maint_FineTune_IO_FIND( _K_D_IO , "CTC.TR_STATUS" , &Address_FINETUNE_Transfer_Status ) ) return SYS_ABORTED;
	//
	va_start( va , list );
	vsprintf( Buffer2 , list , (LPSTR) va );
	va_end( va );
	//
	_dWRITE_DIGITAL( Address_FINETUNE_Transfer_Status , 0 , &CommStatus );
	sprintf( Buffer , "MAINT_INTERFACE %s" , Buffer2 );
	_dWRITE_STRING( Address_FINETUNE_Scheduler , Buffer , &CommStatus );
	while ( TRUE ) {
		if ( !WAIT_SECONDS( 0.25 ) ) return SYS_ABORTED;
		switch( _dREAD_DIGITAL( Address_FINETUNE_Transfer_Status , &CommStatus ) ) {
		case SYS_ABORTED : return SYS_ABORTED;
		case SYS_ERROR   : return SYS_ERROR;
		case SYS_SUCCESS : return SYS_SUCCESS;
		}
	}
}
//------------------------------------------------------------------------------------------
int Maint_FineTune_Get_Aling_ID_PM( int tid , int pid ) {
	if ( tid == 1 ) return 2;
	if ( tid == 2 ) return 1;
	if ( tid == 3 ) return 5;
	return 0;
}
//------------------------------------------------------------------------------------------
int Maint_FineTune_Get_Aling_ID_BM( int tid , int pid ) {
	if ( tid == 1 ) return 2;
	if ( tid == 2 ) return 1;
	if ( tid == 3 ) return 5;
	return 0;
}
//------------------------------------------------------------------------------------------

int Maint_FineTune_Get_TMCheck_PM( int t ) {
	int i;
	for ( i = 1 ; i <= FINETUNE_MAX_PM + 2 ; i++ ) {
		//=====================================================================
		if ( Maint_FineTune_IO_FINETUNE_CHECK_PM_GET2( i ) == 0 ) continue;
//		printf("\n[Finetune] t = %d , i = %d , IO Name = %s, PM Group = %d\n", t , i , IO_STR_Map_Table[FINETUNE_CHECT_PM1 + i - 1].IO_Name , FINETUNE_GROUP_PM[i-1]);
		//=====================================================================
		// 対象モジュールがNoUse,Uninit以外ならば処理続行
		if ( !MODULE_CONTROL_IS_POSSIBLE_PM( FINETUNE_PM_ORDER[i-1] ) ) continue;
		//=====================================================================
		switch( FINETUNE_GROUP_PM[i-1] ) {
		case 0 :
			continue;
			break;
		case 1 : // 1
			if ( t != 1 ) continue;
			break;
		case 2 : //   2
			if ( t != 2 ) continue;
			break;
		case 3 : // 1 2
			if ( ( t != 1 ) && ( t != 2 ) ) continue;
			break;
		case 4 : //     3
			if ( t != 3 ) continue;
			break;
		case 5 : // 1   3
			if ( ( t != 1 ) && ( t != 3 ) ) continue;
			break;
		case 6 : //   2 3
			if ( ( t != 2 ) && ( t != 3 ) ) continue;
			break;
		case 7 : // 1 2 3
			if ( ( t != 1 ) && ( t != 2 ) && ( t != 3 ) ) continue;
			break;
		}
		return i;
	}
	return -1;
}

int Maint_FineTune_Get_PM11_Check( ) {
	int i;
	int tm[2] = { 0 , 0 };
	int CommStatus;
	int res = 0;
	int selected_Chamber = -1;

	for ( i = 0; i < 2; i++ )
	{
		tm[i] = READ_DIGITAL( FINETUNE_CHECT_PM11 + i , &CommStatus );
	}
	
	if ( ( tm[0] == 1 ) && ( tm[1] == 1 ) )				// Tr1 && Tr2 was selected
	{
		// Tr1, Tr2の両方が選択されていたら、両方とも実施する。
		selected_Chamber = 2;
///		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select TR for PASS1 Align", "TR" , "TR1|TR2" , &selected_Chamber) )
///		{
///			return 0;
///		}
	}
	else if ( tm[0] == 1 )
	{
		selected_Chamber = 0;
	}
	else if ( tm[1] == 1 )
	{
		selected_Chamber = 1;
	}
	
	if ( selected_Chamber != -1 )
	{
		res = selected_Chamber + 1;
	}
	else
	{
		res = 0;
	}

	return res;
}

int Maint_FineTune_Get_PM12_Check( ) {
	int i;
	int tm[2] = { 0 , 0 };
	int CommStatus;
	int res = 0;
	int selected_Chamber = -1;

	for ( i = 0; i < 2; i++ )
	{
		tm[i] = READ_DIGITAL( FINETUNE_CHECT_PM12 + i , &CommStatus );
	}
	
	if ( ( tm[0] == 1 ) && ( tm[1] == 1 ) )				// Tr1 && Tr2 was selected
	{
		// Tr1, Tr2の両方が選択されていたら、両方とも実施する。
		selected_Chamber = 2;
///		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Tr for PASS2 Align", "TR" , "TR1|TR2" , &selected_Chamber) )
///		{
///			return 0;
///		}
	}
	else if ( tm[0] == 1 )
	{
		selected_Chamber = 0;
	}
	else if ( tm[1] == 1 )
	{
		selected_Chamber = 1;
	}
	
	if ( selected_Chamber != -1 )
	{
		res = selected_Chamber + 1;
	}
	else
	{
		res = 0;
	}

	return res;
}

int Maint_FineTune_Get_PM11_P12_Check( ) {
	int i;
	int tm[2] = { 0 , 0 };
	int CommStatus;
	int res = 0;
	int selected_Chamber = -1;

	for ( i = 0; i < 2; i++ )
	{
		tm[i] = READ_DIGITAL( FINETUNE_CHECT_PM12_P1_1 + i , &CommStatus );
	}
	
	if ( ( tm[0] == 1 ) && ( tm[1] == 1 ) )				// Tr1 && Tr2 was selected
	{
		// Tr1, Tr2の両方が選択されていたら、両方とも実施する。
		selected_Chamber = 2;
///		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select TR for PASS1 Align", "TR" , "TR1|TR2" , &selected_Chamber) )
///		{
///			return 0;
///		}
	}
	else if ( tm[0] == 1 )
	{
		selected_Chamber = 0;
	}
	else if ( tm[1] == 1 )
	{
		selected_Chamber = 1;
	}
	
	if ( selected_Chamber != -1 )
	{
		res = selected_Chamber + 1;
	}
	else
	{
		res = 0;
	}

	return res;
}

//------------------------------------------------------------------------------------------
int Maint_Fine_Tune() {
	int i , t , Arm , Tmd , Rec_Arm , bmr , tp , P1_Tr , P2_Tr , P1_P2 , /*Align_Count ,*/ FT_Check_Pass; // 2014.08.20 未使用のためコメントアウト
	int CommStatus;
	//int Finetune_use[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 2014.08.20 未使用のためコメントアウト
	double FT_DeltaPick_Comp_R/*, FT_R_OFFSET*/; // 2014.08.20 未使用のためコメントアウト
	//int check; // 2014.08.20 未使用のためコメントアウト

	//=====================================================================
	//↓下記PASS1のチェックは必ず必要とは限らない。
	//  PASS1を使用するときのみ、Maintモードかチェックする。
	//if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) return 101;
	//=====================================================================
	for ( i = 1 ; i <= FINETUNE_MAX_PM + 6 ; i++ ) {
		Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_READY );
		//
		Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( i , 0 );
		Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( i , 0 );
		Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( i , 0 );
		Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( i , 0 );
	}
	//=====================================================================
	for ( i = 1 ; i <= FINETUNE_MAX_BM ; i++ ) {
		Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_READY );
		//
		Maint_FineTune_IO_FINETUNE_OLD_R_POS_BM_SET( i , 0 );
		Maint_FineTune_IO_FINETUNE_OLD_T_POS_BM_SET( i , 0 );
		Maint_FineTune_IO_FINETUNE_NEW_R_POS_BM_SET( i , 0 );
		Maint_FineTune_IO_FINETUNE_NEW_T_POS_BM_SET( i , 0 );
	}
	//=====================================================================
	Tmd = Maint_FineTune_IO_FINETUNE_CHECK_TMS_GET(); // All TM1 TM2 TM3 TM1/TM2 TM1/TM3 TM2/TM3 ALL(LL) TM1(LL) TM2(LL) TM1/TM2(LL)
	Arm = Maint_FineTune_IO_FINETUNE_CHECK_ARM_GET();
	//
	// PASS2をPASS1でFineTeachingするフラグを初期化
	WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
	FT_DeltaPick_Comp_R = READ_ANALOG( FINETUNE_DPICK_COMP_R , &CommStatus );
	// 2015.04.02 Single PASS化対応 (PM12 単一)
	FT_Check_Pass = 1; // 1：PASS2
	//FT_Check_Pass = READ_DIGITAL( FINETUNE_CHECK_PASS , &CommStatus );
	//

	P1_Tr = Maint_FineTune_Get_PM11_Check(); // 2015.04.02 PM11が無いので常に0
	P2_Tr = Maint_FineTune_Get_PM12_Check();
	P1_P2 = Maint_FineTune_Get_PM11_P12_Check(); // 2015.04.02 未使用のため常に0

	//=====================================================================
	// Z-axis SensorがOFFの時、TM*.Wafer_Resultをチェックしない為"RealWafer"が更新されない対策。(2009.09.01 sawatari)
	// Zaxis Wafer Sensor CheckがOffのときの処理
	// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
	// 2014.03.27 suzuki modify↓↓
	/*
	if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
		if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Z-axis sensor is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	*/

	// オムロンカメラ正式対応時はカメラのOnOffだけをみる。(2014.08.20 追加)
	if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
		// 2015.01.14 suzuki modify
		// 画面を切り替えても、メッセージウィンドウが一番上に表示されるように変更。
		//if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		if ( IDYES == MessageBox( NULL , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO | MB_TOPMOST ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	//=====================================================================

	if ( ( P1_Tr != 0 )||( P2_Tr != 0 ) ) {
		// 2015.04.02 PM11は使わないためソース未修正 -------------------------------------------------↓
		if ( P1_Tr != 0 )
		{
			/*
			for ( t = 1 ; t <= 2 ; t++ ) {
				if ( ( P1_Tr == 1 )&&( t == 2 ) ) continue;
				if ( ( P1_Tr == 2 )&&( t == 1 ) ) continue;

				// FineTune対象モジュールはPASS1(PM11)とする
				if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) return 101;
				Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( 11 );

				//--------------------------------------------------------------------------------
				// 2007/3/30 削除
				// PASS1(Aligner)へのFineTeachingについて，EndEffectorにあるWaferをチェックすることを削除する。
				// 最終的にWaferをチェックするようにするか検討すること。
				//--------------------------------------------------------------------------------
				//if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , P1_Tr , 11 , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
				//	return 99;
				//}
				//--------------------------------------------------------------------------------
				if ( Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_NO_WAFER );
					return 98;
				}
				if ( Maint_FineTune_PM11_WIO() != 0 )
				{
					return 97;
				}
				
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_PLACE_AL );
				
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM11|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_FAILED );
					return 96;
				}
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_ALIGNING );
		
				if ( !Maint_FineTune_IO_FIND_F_AL() ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_FAILED );
					return 95;
				}
				if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , 13 + t - 1 ) ) == SYS_ABORTED ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_FAILED );
					return 94;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_PICK_AL_R );
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM11|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_FAILED );
					return 93;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( 13 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
				Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( 13 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( 13 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( 13 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
				//=====================================================================
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 13 + t - 1 , FT_SUCCESS );
				//=====================================================================
			}
			*/
		}
		// 2015.04.02 PM11は使わないためソース未修正 -------------------------------------------------↑
		if ( P2_Tr != 0 )
		{
			for ( t = 1 ; t <= 2 ; t++ ) {
				if ( ( P2_Tr == 1 )&&( t == 2 ) ) continue;
				if ( ( P2_Tr == 2 )&&( t == 1 ) ) continue;

				// FineTune対象モジュールはPASS2(PM12)とする
				if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) return 102;
				Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( 12 );

				//--------------------------------------------------------------------------------
				// 2007/3/30 削除
				// PASS1(Aligner)へのFineTeachingについて，EndEffectorにあるWaferをチェックすることを削除する。
				// 最終的にWaferをチェックするようにするか検討すること。
				//--------------------------------------------------------------------------------
				//if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , P2_Tr , 12 , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
				//	return 889;
				//}
				//--------------------------------------------------------------------------------
				if ( Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) {
					// 2015.04.02 enumにPM14を追加したため+1
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_NO_WAFER );
					//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_NO_WAFER );
					//
					return 88;
				}
				if ( Maint_FineTune_PM12_WIO() != 0 )
				{
					return 87;
				}
				
				// 2015.04.02 enumにPM14を追加したため+1
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_PLACE_AL );
				//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_PLACE_AL );
				//

				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM12|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
					// 2015.04.02 enumにPM14を追加したため+1
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_FAILED );
					//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_FAILED );
					//
					return 86;
				}
				// 2015.04.02 enumにPM14を追加したため+1
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_ALIGNING );
				//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_ALIGNING );
				//
				
				if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
					// 2015.04.02 enumにPM14を追加したため+1
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_FAILED );
					//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_FAILED );
					//
					return 85;
				}
				// 2015.04.02 enumにPM14を追加したため+1
				if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , 16 + t - 1 ) ) == SYS_ABORTED ) {
				//if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , 15 + t - 1 ) ) == SYS_ABORTED ) {
				//
					// 2015.04.02 enumにPM14を追加したため+1
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_FAILED );
					//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_FAILED );
					//
					return 84;
				}
				//=====================================================================
				// 2015.04.02 enumにPM14を追加したため+1
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_PICK_AL_R );
				//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_PICK_AL_R );
				//
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM12|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
					// 2015.04.02 enumにPM14を追加したため+1
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_FAILED );
					//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_FAILED );
					//
					return 83;
				}
				//=====================================================================
				// 2015.04.02 enumにPM14を追加したため+1
				Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( 16 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
				Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( 16 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( 16 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( 16 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
				//Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( 15 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
				//Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( 15 + t - 1 , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
				//Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( 15 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
				//Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( 15 + t - 1 , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
				//
				//=====================================================================
				//=====================================================================
				// 2015.04.02 enumにPM14を追加したため+1
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 16 + t - 1 , FT_SUCCESS );
				//Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( 15 + t - 1 , FT_SUCCESS );
				//
				//=====================================================================
			}
		}
	}
	// 2015.04.02 使わないためソース未修正 -------------------------------------------------↓
	else if ( P1_P2 != 0 )
	{
		/*
		// FineTune基準モジュールはPASS1(PM11)とする
		if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) return 103;

		// PASS2をPASS1でFineTeachingするフラグを立てる
		WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 1, &CommStatus );

		// PASS2をPASS1でFineTeachingする。
		for ( t = 1 ; t <= 2 ; t++ ) {
			//=====================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM( t ) ) continue;
			//=====================================================================
			if      ( t == 1 ) { // TM1
				if ( Tmd == 2 ) continue; //      TM2
				if ( Tmd == 3 ) continue; //           TM3
				if ( Tmd == 6 ) continue; //      TM2  TM3
				if ( Tmd == 9 ) continue; //      TM2L
			}
			else if ( t == 2 ) { // TM2
				if ( Tmd == 1 ) continue; // TM1
				if ( Tmd == 3 ) continue; //           TM3
				if ( Tmd == 5 ) continue; // TM1       TM3
				if ( Tmd == 8 ) continue; // TM1L
			}
			//=====================================================================
			Rec_Arm = -1;
			tp = Maint_FineTune_Get_TMCheck_PM( t );
//				printf("\n\n[Finetune] tp = %d , PM_ORDER = %d\n\n", tp , FINETUNE_PM_ORDER[tp-1] );
			//--------------------------------------------------------------------------------
			if( tp > 0 ) {
				if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , t , FINETUNE_PM_ORDER[tp-1] , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
					return 16;
				}
				if ( ( Rec_Arm != Arm ) || ( !Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) ) {
					return 17;
				}
			}
			//=====================================================================
			for ( i = 11 ; i <= 12 ; i++ ) {
				//=====================================================================
				if ( Maint_FineTune_IO_FINETUNE_CHECK_PM_GET2( i ) == 0 ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NOTSELECT );
					continue;
				}
				//=====================================================================
				if ( !MODULE_CONTROL_IS_POSSIBLE_PM( FINETUNE_PM_ORDER[i-1] ) ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NOTSELECT );
					continue;
				}
				//=====================================================================
				if ( Maint_FineTune_PM12_WIO() == 0 )
				{
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NO_WAFER );
					return 18;
				}
				//=====================================================================
				switch( FINETUNE_GROUP_PM[i-1] ) {
				case 0 :
					continue;
					break;
				case 1 : // 1
					if ( t != 1 ) continue;
					break;
				case 2 : //   2
					if ( t != 2 ) continue;
					break;
				case 3 : // 1 2
					if ( ( t != 1 ) && ( t != 2 ) ) continue;
					break;
				}
				//=====================================================================
				// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
				//Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( i );
				// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
				Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( FINETUNE_PM_ORDER[i-1] );
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PREPARE );
				//=====================================================================
				Align_Count = 0;
				while ( TRUE ) {
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_ALIGNING );
					//=====================================================================
					if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 19;
					}
					if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , i ) ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 20;
					}
					Align_Count++;

					// SIMULATION_MODEがTRUEのときは、Alignを5回行うと、RがPASS2の中心の判断基準内に入るようにする。
					if ( SIMULATION_MODE ) {
						if ( Align_Count >= 5 ) {
							WRITE_ANALOG( P2_R_OFFSET , FT_DeltaPick_Comp_R, &CommStatus );
						}
					}

					// RがPASS2の中心の判断基準内になったら抜ける。
					FT_R_OFFSET = READ_ANALOG( P2_R_OFFSET , &CommStatus );
					if ( FT_DeltaPick_Comp_R >= FT_R_OFFSET ) {
						break;
					}

					// Alignを5回行ってもRが判断基準内に入らない場合はFine TeachingをNGとする。
					if ( Align_Count >= 5 ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 21;
					}

					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PICK_PM );
					//=====================================================================
					// アライナからDelta Pickするため、SYSALIGN_RUNMODEを使用する。
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , SYSALIGN_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 22;
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PLACE_AL );
					//=====================================================================
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 23;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PICK_PM );
				//=====================================================================
				// PASS2の中心に置けたら通常のPickを行う。
				WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 1 , &CommStatus );	// No Align
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , SYSALIGN_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
					WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// No Align
					WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 24;
				}
				WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// No Align
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PLACE_AL );
				//=====================================================================
				if ( FINETUNE_AL_STATION == -1 ) {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						return 25;
					}
				}
				else {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION , Arm + 'A' ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 26;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_ALIGNING );
				if ( !Maint_FineTune_IO_FIND_F_AL() ) {
					WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 27;
				}
				if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , i ) ) == SYS_ABORTED ) {
					WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 28;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PICK_AL_R );
				// PASS1でAlign後はDelta Pickする。Delta Pickするため、SYSALIGN_RUNMODEを使用する。
				if ( FINETUNE_AL_STATION == -1 ) {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 29;
					}
				}
				else {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION , Arm + 'A' ) == SYS_ABORTED ) {
						WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 30;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
				Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PLACE_PM_R );
				//=====================================================================
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
					WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 31;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_SUCCESS );
				//=====================================================================
			}
		}
		WRITE_DIGITAL( FINETUNE_CHECK_PASS1_PASS2, 0, &CommStatus );
		*/
	}
	// 2015.04.02 使わないためソース未修正 -------------------------------------------------↑
	else
	{
		//FT_Check_Pass = 0:PASS1使用
		//FT_Check_Pass = 1:PASS2使用
		// FineTune基準モジュールはPASS1(PM11)とする
		if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 + FT_Check_Pass ) ) return 104;

		// 2015.04.02 TM3は無し
		for ( t = 1 ; t <= 2 ; t++ ) {
		//for ( t = 1 ; t <= 3 ; t++ ) {
			//=====================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM( t ) ) continue;
			//=====================================================================
			if      ( t == 1 ) { // TM1
				if ( Tmd == 2 ) continue; //      TM2
				if ( Tmd == 3 ) continue; //           TM3
				if ( Tmd == 6 ) continue; //      TM2  TM3
				if ( Tmd == 9 ) continue; //      TM2L
			}
			else if ( t == 2 ) { // TM2
				if ( Tmd == 1 ) continue; // TM1
				if ( Tmd == 3 ) continue; //           TM3
				if ( Tmd == 5 ) continue; // TM1       TM3
				if ( Tmd == 8 ) continue; // TM1L
			}
			else if ( t == 3 ) { // TM3
				if ( Tmd ==  1 ) continue; // TM1
				if ( Tmd ==  2 ) continue; //      TM2
				if ( Tmd ==  4 ) continue; // TM1  TM2
				if ( Tmd ==  8 ) continue; // TM1L
				if ( Tmd ==  9 ) continue; //      TM2L
				if ( Tmd == 10 ) continue; // TM1L TM2L
			}
			//=====================================================================
			Rec_Arm = -1;
			tp = Maint_FineTune_Get_TMCheck_PM( t );
//				printf("\n\n[Finetune] tp = %d , PM_ORDER = %d\n\n", tp , FINETUNE_PM_ORDER[tp-1] );
			//--------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------
			// LoadLockのみを指定すると，tpに-1が返ってくる。このときは下記の処理をしない。
			// 処理に問題がないか最終確認をすること。
			// EHA
			//--------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------
			if( tp > 0 ) {
				if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , t , FINETUNE_PM_ORDER[tp-1] , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
					return 1;
				}
				if ( ( Rec_Arm != Arm ) || ( !Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) ) {
					return 2;
				}
			}
			//=====================================================================
			for ( i = 1 ; i <= FINETUNE_MAX_PM ; i++ ) {
				//=====================================================================
				if ( Maint_FineTune_IO_FINETUNE_CHECK_PM_GET2( i ) == 0 ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NOTSELECT );
					continue;
				}
				//=====================================================================
				if ( !MODULE_CONTROL_IS_POSSIBLE_PM( FINETUNE_PM_ORDER[i-1] ) ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NOTSELECT );
					continue;
				}
				//=====================================================================
				switch( FINETUNE_GROUP_PM[i-1] ) {
				case 0 :
					continue;
					break;
				case 1 : // 1
					if ( t != 1 ) continue;
					break;
				case 2 : //   2
					if ( t != 2 ) continue;
					break;
				case 3 : // 1 2
					if ( ( t != 1 ) && ( t != 2 ) ) continue;
					break;
				case 4 : //     3
					if ( t != 3 ) continue;
					break;
				case 5 : // 1   3
					if ( ( t != 1 ) && ( t != 3 ) ) continue;
					break;
				case 6 : //   2 3
					if ( ( t != 2 ) && ( t != 3 ) ) continue;
					break;
				case 7 : // 1 2 3
					if ( ( t != 1 ) && ( t != 2 ) && ( t != 3 ) ) continue;
					break;
				}
				//=====================================================================
				// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
				//Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( i );
				// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
				Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( FINETUNE_PM_ORDER[i-1] );
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PREPARE );
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PICK_PM );
				//=====================================================================
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 3;
				}
				//=====================================================================
				if ( Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_NO_WAFER );
					continue;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PLACE_AL );
				//=====================================================================
				if ( FINETUNE_AL_STATION == -1 ) {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 4;
					}
				}
				else {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION + FT_Check_Pass, Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 5;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_ALIGNING );

				// 使用するPASSによって切り替える。
				if ( FT_Check_Pass == 0 ) {
					if ( !Maint_FineTune_IO_FIND_F_AL() ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 6;
					}
					if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , i ) ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 7;
					}
				}
				else if ( FT_Check_Pass == 1 ) {
					if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 6;
					}
					if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( t , i ) ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 7;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PICK_AL_R );
				if ( FINETUNE_AL_STATION == -1 ) {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 8;
					}
				}
				else {
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION + FT_Check_Pass, Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
						return 9;
					}
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_OLD_R_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
				Maint_FineTune_IO_FINETUNE_OLD_T_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_R_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
				Maint_FineTune_IO_FINETUNE_NEW_T_POS_PM_SET2( i , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_PLACE_PM_R );
				if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_PM_ORDER[i-1] , Arm + 'A' ) == SYS_ABORTED ) {
					Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_FAILED );
					return 10;
				}
				//=====================================================================
				Maint_FineTune_IO_FINETUNE_STATUS_PM_SET2( i , FT_SUCCESS );
				//=====================================================================
			}
			//===============================================================================================================
			//===============================================================================================================
			//=====================================================================
			bmr = FALSE;
			//=====================================================================
			if      ( t == 1 ) { // TM1
				if ( Tmd ==  7 ) bmr = TRUE; //
				if ( Tmd ==  8 ) bmr = TRUE; //
				if ( Tmd == 10 ) bmr = TRUE; //
			}
			else if ( t == 2 ) { // TM2
				if ( Tmd ==  7 ) bmr = TRUE; //
				if ( Tmd ==  9 ) bmr = TRUE; //
				if ( Tmd == 10 ) bmr = TRUE; //
			}
			else if ( t == 3 ) { // TM3
			}
			//===============================================================================================================
			if ( bmr ) {
				for ( i = 1 ; i <= FINETUNE_MAX_BM ; i++ ) {
					//=====================================================================
					if ( Maint_FineTune_IO_FINETUNE_CHECK_BM_GET( i ) == 0 ) {
						Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_NOTSELECT );
						continue;
					}
					//=====================================================================
					if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) {
						Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_NOTSELECT );
						continue;
					}
					//=====================================================================
					switch( FINETUNE_GROUP_BM[i-1] ) {
					case 0 :
						continue;
						break;
					case 1 : // 1
						if ( t != 1 ) continue;
						break;
					case 2 : //   2
						if ( t != 2 ) continue;
						break;
					case 3 : // 1 2
						if ( ( t != 1 ) && ( t != 2 ) ) continue;
						break;
					case 4 : //     3
						if ( t != 3 ) continue;
						break;
					case 5 : // 1   3
						if ( ( t != 1 ) && ( t != 3 ) ) continue;
						break;
					case 6 : //   2 3
						if ( ( t != 2 ) && ( t != 3 ) ) continue;
						break;
					case 7 : // 1 2 3
						if ( ( t != 1 ) && ( t != 2 ) && ( t != 3 ) ) continue;
						break;
					}
					//=====================================================================
					// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
					//Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( i + FINETUNE_MAX_PM );
					// bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug bug
					Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET( i + 15/*14*/ );
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_PREPARE );
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_PICK_PM );
					//=====================================================================
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|BM%d|%c|1|1" , t , FINETUNE_RUNMODE , i , Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
						return 105;
					}
					//=====================================================================
					if ( Maint_FineTune_IO_FIND_TM_WIO( t , Arm , 0 ) ) {
						Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_NO_WAFER );
						continue;
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_PLACE_AL );
					//=====================================================================
					if ( FINETUNE_AL_STATION == -1 ) {
						if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 106;
						}
					}
					else {
						if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION + FT_Check_Pass , Arm + 'A' ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 107;
						}
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_ALIGNING );

					// 使用するPASSによって切り替える。
					if ( FT_Check_Pass == 0 ) {
						if ( !Maint_FineTune_IO_FIND_F_AL() ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 108;
						}
						if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_BM( t , i ) ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 107;
						}
					}
					if ( FT_Check_Pass == 1 ) {
						if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 109;
						}
						if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_BM( t , i ) ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 110;
						}
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_PICK_AL_R );
					if ( FINETUNE_AL_STATION == -1 ) {
						if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|AL|%c|1|1" , t , FINETUNE_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 111;
						}
					}
					else {
						if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , t , FINETUNE_RUNMODE , FINETUNE_AL_STATION + FT_Check_Pass, Arm + 'A' ) == SYS_ABORTED ) {
							Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
							return 112;
						}
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_OLD_R_POS_BM_SET( i , Maint_FineTune_IO_FINETUNE_OLD_R_GET() );
					Maint_FineTune_IO_FINETUNE_OLD_T_POS_BM_SET( i , Maint_FineTune_IO_FINETUNE_OLD_T_GET() );
					Maint_FineTune_IO_FINETUNE_NEW_R_POS_BM_SET( i , Maint_FineTune_IO_FINETUNE_NEW_R_GET() );
					Maint_FineTune_IO_FINETUNE_NEW_T_POS_BM_SET( i , Maint_FineTune_IO_FINETUNE_NEW_T_GET() );
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_PLACE_PM_R );
					if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|BM%d|%c|1|1" , t , FINETUNE_RUNMODE , i , Arm + 'A' ) == SYS_ABORTED ) {
						Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_FAILED );
						return 113;
					}
					//=====================================================================
					Maint_FineTune_IO_FINETUNE_STATUS_BM_SET( i , FT_SUCCESS );
					//=====================================================================
				}
			}
		}
	}
	return 0;
}
//------------------------------------------------------------------------------------------
// 浮動小数点の値を比較する関数
// Data1 > Data2:return 1
// Data1 < Data2:return -1
// Data1 = Data2:return 0
int Value_Comparison( double Data1, double Data2, int n ) {
	double dst1;
	double dst2;
	int value1;
	int value2;

//	printf("Data1=%.100f\n",Data1);
//	printf("Data2=%.100f\n",Data2);
	// n倍して小数点以下を四捨五入
	dst1 = Data1 * n;
	dst2 = Data2 * n;
//	printf("dst1=%.100f\n",dst1);
//	printf("dst2=%.100f\n",dst2);
	if   ( Data1 < 0 ) {
		value1 = (int) (dst1 -0.5);
	}
	else {
		value1 = (int) (dst1 +0.5);
	}

	if   ( Data2 < 0 ) {
		value2 = (int) (dst2 -0.5);
	}
	else {
		value2 = (int) (dst2 +0.5);
	}
//	printf("value1=%d\n",value1);
//	printf("value2=%d\n",value2);
	if (value1 > value2 ) return 1;
	else if (value1 < value2 ) return -1;
	else return 0;
}
// 2013/05/07 ----------------------------------------------------------------->>
void NotchAngleCorrect_Log( char *LogString ) {
	FILE *fp = NULL;
	char Path[MAX_PATH] , FileName[256];
	SYSTEMTIME st;
	
	GetLocalTime( &st );
	sprintf( FileName , "NOTCH_ANGLE_CORRECT.log" );
	sprintf( Path , "History\\%s" , FileName );
	fp = fopen( Path , "a+" );
	if( !fp ) { printf( "[NOTCH ANGLE CORRECT LOG] : Can't Create Log File : %s\n" , FileName ); return; }
	fprintf( fp , "%04d/%02d/%02d\t%02d:%02d:%02d\t" , st.wYear , st.wMonth , st.wDay , st.wHour , st.wMinute , st.wSecond );
	
	fprintf( fp , "%s\n" , LogString );
	fclose( fp );
}

// 2013/05/07 -----------------------------------------------------------------<<
int Maint_Notch_Angle_Correct() {
	int Tr , Arm , Rec_Arm , Align_Count;
	int CommStatus;
	double Notch_Angle, Set_CorrectAngle, Get_CorrectAngle;
	double FT_DeltaPick_Comp_R, FT_R_OFFSET;
	// 2013/05/07 ----------------------------------------------------------------->>
	char Log_Buffer[512];
	// 2013/05/07 -----------------------------------------------------------------<<

	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_READY , &CommStatus );
	WRITE_ANALOG( FINETUNE_NOTCH_ANGLE , 0 , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_SET , 0 , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_GET , 0 , &CommStatus );
	FT_DeltaPick_Comp_R = READ_ANALOG( FINETUNE_DPICK_COMP_R , &CommStatus );

	Arm = Maint_FineTune_IO_NOTCH_CORRECT_CHECK_ARM_GET();
	Tr  = Maint_FineTune_IO_NOTCH_CORRECT_CHECK_TR_GET() + 1;

	//=====================================================================
	// 2014.08.20 オムロンカメラ正式対応 ----------------------------------------------↓↓
	// オムロンカメラ正式対応時はカメラのOnOffをみる。
	// Z-axis SensorがOFFの時、TM*.Wafer_Resultをチェックしない為"RealWafer"が更新されない対策。
	// Zaxis Wafer Sensor CheckがOffのときの処理
	// 2014.08.20 参照IO(TM_WFRSNS_CONTROL → TM_CAM_CONTROL)およびメッセージを変更
	if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
		// 2015.01.14 suzuki modify
		// 画面を切り替えても、メッセージウィンドウが一番上に表示されるように変更。
		//if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		if ( IDYES == MessageBox( NULL , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO | MB_TOPMOST ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	/* 2014.08.20 コメントアウト
	if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
		if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Wafer Sensor is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	*/
	// 2014.08.20 オムロンカメラ正式対応 ----------------------------------------------↑↑
	//=====================================================================
	// PASS1(PM11)とPASS2(PM12)がMaint Modeかをチェックする
	if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) )||( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 201;
	}

	// Pass1 Wafer Present Check
	// 2013.07.01 suzuki modify
	// CTC.PM11_Wafer_Statusが1未満だったら(Waferが存在しなかったら)、NGとする。(変更前は≠1でなかったらNGであったため、WaferIDが101,201,301以外だとNGになっていた。)
	//if ( !Maint_SysAlign_IO_FIND_PM_WIO( 11 , 1 ) )
	if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 11 , 1 ) )
	{
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 202;
	}

	Rec_Arm = -1;
	if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , Tr , 11 , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 203;
	}
	if ( ( Rec_Arm != Arm ) || ( !Maint_FineTune_IO_FIND_TM_WIO( Tr , Arm , 0 ) ) ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 204;
	}

	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PREPARE , &CommStatus );
	//=====================================================================
	Align_Count = 0;
	while ( TRUE ) {
		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_ALIGNING , &CommStatus );
		//=====================================================================
		if ( !Maint_FineTune_IO_FIND_F_AL() ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 205;
		}
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( Tr , 11 ) ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 206;
		}
		Align_Count++;

		// SIMULATION_MODEがTRUEのときは、Alignを5回行うと、RがPASS1の中心の判断基準内に入るようにする。
		if ( SIMULATION_MODE ) {
			if ( Align_Count >= 5 ) {
				WRITE_ANALOG( P1_R_OFFSET , FT_DeltaPick_Comp_R, &CommStatus );
			}
		}

		// RがPASS1の中心の判断基準内になったら抜ける。
		FT_R_OFFSET = READ_ANALOG( P1_R_OFFSET , &CommStatus );
		if ( FT_DeltaPick_Comp_R >= FT_R_OFFSET ) {
			break;
		}

		// Alignを5回行ってもRが判断基準内に入らない場合はFine TeachingをNGとする。
		if ( Align_Count >= 5 ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 207;
		}

		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PICK_PM , &CommStatus );
		//=====================================================================
		// PASS1に置いたウェハとPASS1の中心を合わせるため、アライン→Delta Pickを行う。
		// アライナからDelta Pickするため、SYSALIGN_RUNMODEを使用する。
		if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , Tr , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 208;
		}
		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PLACE_AL , &CommStatus );
		//=====================================================================
		if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , Tr , FINETUNE_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 209;
		}
	}
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PICK_PM , &CommStatus );
	//=====================================================================
	// PASS1に置いたウェハとPASS1の中心を合わせるため、アライン→Delta Pickを行う。
	// アライナからDelta Pickするため、SYSALIGN_RUNMODEを使用する。
	if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , Tr , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 210;
	}
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PLACE_AL , &CommStatus );
	//=====================================================================
	if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , Tr , FINETUNE_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 211;
	}

	// PASS2でAlignする前にAligner2の補正値を初期化する。
	if ( RUN_FUNCTIONF( TMC_ALGNLOW2_CONTROL , "CORRECT_ANGLE_SET 0" ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 212;
	}
	
	// PLCに書き込んだ補正値を読み出す。
	WRITE_DIGITAL( ALIGNER2_CORRECT_ANGLE , 0 , &CommStatus );
	Get_CorrectAngle = READ_ANALOG( ALIGNER2_GET_CORRECT_ANGLE , &CommStatus );

	// PLCに書き込んだ補正値と読み出した補正値が一致しているかを確認する。
	// 一致していなければNG終了とする。
	if ( Value_Comparison( Get_CorrectAngle, 0, 10 ) != 0 ) {
		printf("Disagreement! Set_CorrectAngle = 0, Get_CorrectAngle = %.1f\n",Get_CorrectAngle);
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 213;
	}
	printf("Set_CorrectAngle = 0, Get_CorrectAngle = %.1f\n", Get_CorrectAngle);

	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_ALIGNING , &CommStatus );
	//=====================================================================
	if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 214;
	}
	if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( Tr , 12 ) ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 215;
	}
	////
	// アライン終了後にアライナPLCに対してRQ MESURESULTを送信する。
	WRITE_DIGITAL( ALIGNER2_MESRESULT , 0 , &CommStatus );
	// ノッチ角度を読み出す。
	Notch_Angle = READ_ANALOG( ALIGNER2_M_ANGLE , &CommStatus );
	WRITE_ANALOG( FINETUNE_NOTCH_ANGLE , Notch_Angle , &CommStatus );
	Set_CorrectAngle = -Notch_Angle;
	// ノッチ角度の差分を補正値としてアライナPLCに書き込む。
	// %.1fは小数点2桁目を四捨五入する。小数点2桁目以下に浮動小数点によるゴミがあった場合、小数点2桁目以下を四捨五入した値がTMC_ALGNLOW2_CONTROLに送信される。
	if ( RUN_FUNCTIONF( TMC_ALGNLOW2_CONTROL , "CORRECT_ANGLE_SET %.1f", Set_CorrectAngle ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 216;
	}
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_SET , Set_CorrectAngle , &CommStatus );
	// PLCに書き込んだ補正値を読み出す。
	WRITE_DIGITAL( ALIGNER2_CORRECT_ANGLE , 0 , &CommStatus );
	Get_CorrectAngle = READ_ANALOG( ALIGNER2_GET_CORRECT_ANGLE , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_GET , Get_CorrectAngle , &CommStatus );
	//20141217 ECID用のIOに値をセットする
	WRITE_ANALOG( CORRECT_ANGLE_SET_GUI , Get_CorrectAngle , &CommStatus );
	////
	// PLCに書き込んだ補正値と読み出した補正値が一致しているかを確認する。
	// 一致していなければNG終了とする。
	if ( Value_Comparison( Set_CorrectAngle, Get_CorrectAngle, 10 ) != 0 ) {
		printf("Disagreement! Set_CorrectAngle = %.1f, Get_CorrectAngle = %.1f\n", Set_CorrectAngle, Get_CorrectAngle );
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 217;
	}
	printf("Set_CorrectAngle = %.1f, Get_CorrectAngle = %.1f\n", Set_CorrectAngle, Get_CorrectAngle );
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_SUCCESS , &CommStatus );
	//=====================================================================
	// 2013/05/07 ----------------------------------------------------------------->>
	// ログデータに記録を残す。
	sprintf( Log_Buffer , "%s\t%s\t%s\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.1f\t%.1f\t%.1f", "CORRECT",
																NOTCH_ANGLE_SETTING_TR[Tr-1],
																NOTCH_ANGLE_SETTING_ARM[Arm],
																READ_ANALOG( P1_X_OFFSET , &CommStatus ),
																READ_ANALOG( P1_Y_OFFSET , &CommStatus ),
																READ_ANALOG( P1_R_OFFSET , &CommStatus ),
																READ_ANALOG( P2_X_OFFSET , &CommStatus ),
																READ_ANALOG( P2_Y_OFFSET , &CommStatus ),
																READ_ANALOG( P2_R_OFFSET , &CommStatus ),
																READ_ANALOG( FINETUNE_NOTCH_ANGLE , &CommStatus ),
																READ_ANALOG( FINETUNE_CORRECT_ANGLE_SET , &CommStatus ),
																READ_ANALOG( FINETUNE_CORRECT_ANGLE_GET , &CommStatus ) );
	NotchAngleCorrect_Log( Log_Buffer );
	// 2013/05/07 -----------------------------------------------------------------<<
	return 0;
}
//------------------------------------------------------------------------------------------
int Maint_Notch_Angle_Check() {
	int Tr , Arm , Rec_Arm , Align_Count;
	int CommStatus;
	double Notch_Angle, Get_CorrectAngle;
	double FT_DeltaPick_Comp_R, FT_R_OFFSET;
	// 2013/05/07 ----------------------------------------------------------------->>
	char Log_Buffer[512];
	// 2013/05/07 -----------------------------------------------------------------<<

	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_READY , &CommStatus );
	WRITE_ANALOG( FINETUNE_NOTCH_ANGLE , 0 , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_SET , 0 , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_GET , 0 , &CommStatus );
	FT_DeltaPick_Comp_R = READ_ANALOG( FINETUNE_DPICK_COMP_R , &CommStatus );

	Arm = Maint_FineTune_IO_NOTCH_CORRECT_CHECK_ARM_GET();
	Tr  = Maint_FineTune_IO_NOTCH_CORRECT_CHECK_TR_GET() + 1;

	//=====================================================================
	// 2014.08.20 オムロンカメラ正式対応 ----------------------------------------------↓↓
	// オムロンカメラ正式対応時はカメラのOnOffをみる。
	// Z-axis SensorがOFFの時、TM*.Wafer_Resultをチェックしない為"RealWafer"が更新されない対策。
	// Zaxis Wafer Sensor CheckがOffのときの処理
	// 2014.08.20 参照IO(TM_WFRSNS_CONTROL → TM_CAM_CONTROL)およびメッセージを変更
	if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
		// 2015.01.14 suzuki modify
		// 画面を切り替えても、メッセージウィンドウが一番上に表示されるように変更。
		//if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		if ( IDYES == MessageBox( NULL , "Camera is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO | MB_TOPMOST ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	/* 2014.08.20 コメントアウト
	if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
		if ( IDYES == MessageBox( GET_MAIN_WINDOW() , "Wafer Sensor is Off.\nPlease confirm the position of the wafer.", "Wafer Present/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
		}
		else {
			return SYS_ABORTED;
		}
	}
	*/
	// 2014.08.20 オムロンカメラ正式対応 ----------------------------------------------↑↑
	//=====================================================================
	// PASS1(PM11)とPASS2(PM12)がMaint Modeかをチェックする
	if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) )||( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 251;
	}

	// Pass2 Wafer Present Check
	// 2013.07.01 suzuki modify
	// CTC.PM12_Wafer_Statusが1未満だったら(Waferが存在しなかったら)、NGとする。(変更前は≠1でなかったらNGであったため、WaferIDが101,201,301以外だとNGになっていた。)
	//if ( !Maint_SysAlign_IO_FIND_PM_WIO( 12 , 1 ) )
	if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 12 , 1 ) )
	{
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 252;
	}

	Rec_Arm = -1;
	if ( Maint_Material_Recovery_Check_TM( MTL_SUB_REAL_CHECK , Tr , 12 , Arm , 1 , &Rec_Arm ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 253;
	}
	if ( ( Rec_Arm != Arm ) || ( !Maint_FineTune_IO_FIND_TM_WIO( Tr , Arm , 0 ) ) ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 254;
	}

	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PREPARE , &CommStatus );
	//=====================================================================
	Align_Count = 0;
	while ( TRUE ) {
		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_ALIGNING , &CommStatus );
		//=====================================================================
		if ( !Maint_FineTune_IO_FIND_F_AL2() ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 255;
		}
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( Tr , 12 ) ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 256;
		}
		Align_Count++;

		// SIMULATION_MODEがTRUEのときは、Alignを5回行うと、RがPASS2の中心の判断基準内に入るようにする。
		if ( SIMULATION_MODE ) {
			if ( Align_Count >= 5 ) {
				WRITE_ANALOG( P2_R_OFFSET , FT_DeltaPick_Comp_R, &CommStatus );
			}
		}

		// RがPASS2の中心の判断基準内になったら抜ける。
		FT_R_OFFSET = READ_ANALOG( P2_R_OFFSET , &CommStatus );
		if ( FT_DeltaPick_Comp_R >= FT_R_OFFSET ) {
			break;
		}

		// Alignを5回行ってもRが判断基準内に入らない場合はFine TeachingをNGとする。
		if ( Align_Count >= 5 ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 257;
		}

		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PICK_PM , &CommStatus );
		//=====================================================================
		// PASS2に置いたウェハとPASS2の中心を合わせるため、アライン→Delta Pickを行う。
		// アライナからDelta Pickするため、SYSALIGN_RUNMODEを使用する。
		if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , Tr , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 258;
		}
		//=====================================================================
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PLACE_AL , &CommStatus );
		//=====================================================================
		if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , Tr , FINETUNE_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) {
			WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
			return 259;
		}
	}
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PICK_PM , &CommStatus );
	//=====================================================================
	// PASS2に置いたウェハとPASS2の中心を合わせるため、アライン→Delta Pickを行う。
	// アライナからDelta Pickするため、SYSALIGN_RUNMODEを使用する。
	if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|1" , Tr , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 260;
	}
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_PLACE_AL , &CommStatus );
	//=====================================================================
	if ( Maint_FineTune_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|1" , Tr , FINETUNE_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 261;
	}
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_ALIGNING , &CommStatus );
	//=====================================================================
	if ( !Maint_FineTune_IO_FIND_F_AL() ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 262;
	}
	if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( Tr , 11 ) ) == SYS_ABORTED ) {
		WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_FAILED , &CommStatus );
		return 263;
	}
	////
	// アライン終了後にアライナPLCに対してRQ MESURESULTを送信する。
	WRITE_DIGITAL( ALIGNER_MESRESULT , 0 , &CommStatus );
	// ノッチ角度を読み出す。
	Notch_Angle = READ_ANALOG( ALIGNER_M_ANGLE , &CommStatus );
	WRITE_ANALOG( FINETUNE_NOTCH_ANGLE , Notch_Angle , &CommStatus );
	// PLCに書き込んだ補正値を読み出す。
	WRITE_DIGITAL( ALIGNER_CORRECT_ANGLE , 0 , &CommStatus );
	Get_CorrectAngle = READ_ANALOG( ALIGNER_GET_CORRECT_ANGLE , &CommStatus );
	WRITE_ANALOG( FINETUNE_CORRECT_ANGLE_GET , Get_CorrectAngle , &CommStatus );
	////
	//=====================================================================
	WRITE_DIGITAL( NOTCH_CORRECT_STATUS , FT_SUCCESS , &CommStatus );
	//=====================================================================
	// 2013/05/07 ----------------------------------------------------------------->>
	// ログデータに記録を残す。
	sprintf( Log_Buffer , "%s\t%s\t%s\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.1f\t%.1f\t%.1f", "CHECK",
																NOTCH_ANGLE_SETTING_TR[Tr-1],
																NOTCH_ANGLE_SETTING_ARM[Arm],
																READ_ANALOG( P1_X_OFFSET , &CommStatus ),
																READ_ANALOG( P1_Y_OFFSET , &CommStatus ),
																READ_ANALOG( P1_R_OFFSET , &CommStatus ),
																READ_ANALOG( P2_X_OFFSET , &CommStatus ),
																READ_ANALOG( P2_Y_OFFSET , &CommStatus ),
																READ_ANALOG( P2_R_OFFSET , &CommStatus ),
																READ_ANALOG( FINETUNE_NOTCH_ANGLE , &CommStatus ),
																READ_ANALOG( FINETUNE_CORRECT_ANGLE_SET , &CommStatus ),
																READ_ANALOG( FINETUNE_CORRECT_ANGLE_GET , &CommStatus ) );
	NotchAngleCorrect_Log( Log_Buffer );
	// 2013/05/07 -----------------------------------------------------------------<<
	return 0;
}
//------------------------------------------------------------------------------------------
int Maint_FineTune_Aligning( int tm , int Arm , int pm , int Pathmode ) { // 2006.09.03
	if ( !Maint_FineTune_IO_FIND_F_AL() ) return SYS_ABORTED;
	if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) return SYS_ABORTED;
	if ( Pathmode ) {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( tm , pm ) + 10 ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	else {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_FineTune_Get_Aling_ID_PM( tm , pm ) ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int Maint_Transfer_Get_Aling_ID_PM( int tid , int pid ) {
	if ( tid == 1 ) return 2;
	if ( tid == 2 ) return 1;
	if ( tid == 3 ) {
		if ( ( pid == 12 ) || ( pid == 13 ) ) return 3;
		if ( ( pid == 14 ) || ( pid == 15 ) ) return 4;
		return 5;
	}
	return 0;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Aligning( int tm , int Arm , int pm , int Pathmode ) { // 2006.09.03
	if ( !Maint_FineTune_IO_FIND_F_AL() ) return SYS_ABORTED;
	if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) return SYS_ABORTED;
	if ( Pathmode ) {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_Transfer_Get_Aling_ID_PM( tm , pm ) + 10 ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	else {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_Transfer_Get_Aling_ID_PM( tm , pm ) ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Aligning2( int tm , int Arm , int pm , int Pathmode ) { // 2006.09.03
	if ( !Maint_FineTune_IO_FIND_F_AL2() ) return SYS_ABORTED;
	if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) return SYS_ABORTED;
	if ( Pathmode ) {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_Transfer_Get_Aling_ID_PM( tm , pm ) + 10 ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	else {
		if ( _dRUN_FUNCTIONF( Address_FINETUNE_F_FAL2 , "ALIGN %c_AL 1 %d" , Arm + 'A' , Maint_Transfer_Get_Aling_ID_PM( tm , pm ) ) != SYS_SUCCESS ) return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------

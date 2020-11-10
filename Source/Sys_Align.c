//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Sys_Align.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"

#include "Sys_Align.h"
#include "cimseqnc.h"

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//=========================================================================================================
int	Address_SYSALIGN_IO_Init = FALSE;
//
int	Address_SYSALIGN_Transfer_Status;
int	Address_SYSALIGN_Scheduler;
//
int	Address_SYSALIGN_CM_WIO[4][30];
int	Address_SYSALIGN_TM_WIO[4][2];
int	Address_SYSALIGN_PM_WIO[60];
int	Address_SYSALIGN_BM_WIO[4][30];
int	Address_SYSALIGN_FM_WIO[2];
int	Address_SYSALIGN_FAL_WIO;

int	Address_SYSALIGN_FAL_WSRC; // 2007.12.12
int	Address_SYSALIGN_PM_WSRC[60]; // 2007.12.12
int	Address_SYSALIGN_BM_WSRC[4][30]; // 2007.12.12

int	Address_SYSALIGN_FM_WSRC[2];
int	Address_SYSALIGN_TM_WSRC[4][2];
//=========================================================================================================
int SYSALIGN_RUNMODE = 1;
//=========================================================================================================
//=========================================================================================================
//=========================================================================================================
void Maint_SysAlign_SET_RUN_MODE( int data ) {
	SYSALIGN_RUNMODE = data;
}

//=========================================================================================================
BOOL Maint_SysAlign_IO_FIND( int mode , char *ioname , int *ioaddress ) {
	int i , j;
	if ( !Address_SYSALIGN_IO_Init ) {
		Address_SYSALIGN_IO_Init = TRUE;
		//=========================================================
		Address_SYSALIGN_Transfer_Status = -2;
		Address_SYSALIGN_Scheduler = -2;
		//=========================================================
		Address_SYSALIGN_FAL_WIO = -2;
		Address_SYSALIGN_FAL_WSRC = -2; // 2007.12.12
		//
		for ( i = 0 ; i < 2 ; i++ ) {
			Address_SYSALIGN_FM_WIO[i] = -2;
			Address_SYSALIGN_FM_WSRC[i] = -2;
		}
		//
		for ( i = 0 ; i < 60 ; i++ ) {
			Address_SYSALIGN_PM_WIO[i] = -2;
			Address_SYSALIGN_PM_WSRC[i] = -2;
		}
		//
		for ( i = 0 ; i < 4 ; i++ ) {
			for ( j = 0 ; j < 30 ; j++ ) {
				Address_SYSALIGN_CM_WIO[i][j] = -2;
				Address_SYSALIGN_BM_WIO[i][j] = -2;
				Address_SYSALIGN_BM_WSRC[i][j] = -2;
			}
			for ( j = 0 ; j < 2 ; j++ ) {
				Address_SYSALIGN_TM_WIO[i][j] = -2;
				Address_SYSALIGN_TM_WSRC[i][j] = -2;
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

BOOL Maint_SysAlign_IO_FIND_CM_WIO( int Cass , int Slot , int ckdata ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "CM%d.C%02d_WAFER" , Cass , Slot );
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_CM_WIO[Cass-1][Slot-1]) ) ) return FALSE;
	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_SYSALIGN_CM_WIO[Cass-1][Slot-1] , &CommStatus ) != ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_TM_WIO( int Tms , int Arm , int ckdata ) {
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
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_TM_WIO[Tms-1][Arm]) ) ) return FALSE;
	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_SYSALIGN_TM_WIO[Tms-1][Arm] , &CommStatus ) != ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_FM_WIO( int Arm , int ckdata ) {
	int CommStatus;
	char Buffer[32];
	if ( Arm == 0 ) {
		sprintf( Buffer , "CTC.FA_Wafer_Status" );
	}
	else {
		sprintf( Buffer , "CTC.FB_Wafer_Status" );
	}
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_FM_WIO[Arm]) ) ) return FALSE;

	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_SYSALIGN_FM_WIO[Arm] , &CommStatus ) != ckdata ) return FALSE;
	}
	return TRUE;
}


BOOL Maint_SysAlign_IO_FIND_PM_WIO( int Chamber , int ckdata ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "CTC.PM%d_Wafer_Status" , Chamber );
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_PM_WIO[Chamber-1]) ) ) return FALSE;
	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_SYSALIGN_PM_WIO[Chamber-1] , &CommStatus ) != ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_PM_WIO2( int Chamber , int ckdata ) {
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "CTC.PM%d_Wafer_Status" , Chamber );
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_PM_WIO[Chamber-1]) ) ) return FALSE;
	if ( ckdata != -1 ) {
		if ( _dREAD_DIGITAL( Address_SYSALIGN_PM_WIO[Chamber-1] , &CommStatus ) < ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_PM_WDATA( int Chamber , int *src , int *wfr ) { // 2007.12.12
	int CommStatus;
	char Buffer[32];
	sprintf( Buffer , "CTC.PM%d_Wafer_Status" , Chamber );
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_PM_WIO[Chamber-1]) ) ) return FALSE;
	*wfr = _dREAD_DIGITAL( Address_SYSALIGN_PM_WIO[Chamber-1] , &CommStatus );
	//
	sprintf( Buffer , "CTC.PM%d_Wafer_Source" , Chamber );
	if ( Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_PM_WSRC[Chamber-1]) ) ) {
		*src = _dREAD_DIGITAL( Address_SYSALIGN_PM_WSRC[Chamber-1] , &CommStatus );
	}
	else {
		*src = -1;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_BM_WIO( int Ch , int Slot , int ckdata , int *src , int *wfr ) {
	int CommStatus;
	char Buffer[32];
	char Buffer2[32];
	if ( Slot == 1 ) {
		sprintf( Buffer , "CTC.BM%d_Wafer_Status" , Ch );
		sprintf( Buffer2 , "CTC.BM%d_Wafer_Source" , Ch );
	}
	else {
		sprintf( Buffer , "CTC.BM%d_Wafer_Status%d" , Ch , Slot );
		sprintf( Buffer2 , "CTC.BM%d_Wafer_Source%d" , Ch , Slot );
	}
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_BM_WIO[Ch-1][Slot-1]) ) ) return FALSE;
	if ( Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_BM_WSRC[Ch-1][Slot-1]) ) ) {
		*src = _dREAD_DIGITAL( Address_SYSALIGN_BM_WSRC[Ch-1][Slot-1] , &CommStatus );
	}
	else {
		*src = -1;
	}
	if ( ckdata != -1 ) {
		*wfr = _dREAD_DIGITAL( Address_SYSALIGN_BM_WIO[Ch-1][Slot-1] , &CommStatus );
		if ( *wfr != ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_FAL_WIO( int ckdata , int *src , int *wfr ) {
	int CommStatus;
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , "CTC.FM_AL_Wafer_Status" , &Address_SYSALIGN_FAL_WIO ) ) return FALSE;
	if ( Maint_SysAlign_IO_FIND( _K_D_IO , "CTC.FM_AL_Wafer_Source" , &Address_SYSALIGN_FAL_WSRC ) ) {
		*src = _dREAD_DIGITAL( Address_SYSALIGN_FAL_WSRC , &CommStatus );
	}
	else {
		*src = -1;
	}
	if ( ckdata != -1 ) {
		*wfr = _dREAD_DIGITAL( Address_SYSALIGN_FAL_WIO , &CommStatus );
		if ( *wfr != ckdata ) return FALSE;
	}
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_FM_WDATA( int Arm , int *sdata , int *wdata ) {
	int CommStatus;
	char Buffer[32];
	if ( Arm == 0 ) {
		sprintf( Buffer , "CTC.FA_Wafer_Status" );
	}
	else {
		sprintf( Buffer , "CTC.FB_Wafer_Status" );
	}
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_FM_WIO[Arm]) ) ) return FALSE;

	*wdata = _dREAD_DIGITAL( Address_SYSALIGN_FM_WIO[Arm] , &CommStatus );

	if ( Arm == 0 ) {
		sprintf( Buffer , "CTC.FA_Wafer_Source" );
	}
	else {
		sprintf( Buffer , "CTC.FB_Wafer_Source" );
	}

	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_FM_WSRC[Arm]) ) ) return FALSE;

	*sdata = _dREAD_DIGITAL( Address_SYSALIGN_FM_WSRC[Arm] , &CommStatus );
	return TRUE;
}

BOOL Maint_SysAlign_IO_FIND_TM_WDATA( int Tms , int Arm , int *sdata , int *wdata ) {
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
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_TM_WIO[Tms-1][Arm]) ) ) return FALSE;
	*wdata = _dREAD_DIGITAL( Address_SYSALIGN_TM_WIO[Tms-1][Arm] , &CommStatus );

	if ( Tms == 1 ) {
		if ( Arm == 0 ) {
			sprintf( Buffer , "CTC.TA_Wafer_Source" );
		}
		else {
			sprintf( Buffer , "CTC.TB_Wafer_Source" );
		}
	}
	else {
		if ( Arm == 0 ) {
			sprintf( Buffer , "CTC.TA%d_Wafer_Source" , Tms );
		}
		else {
			sprintf( Buffer , "CTC.TB%d_Wafer_Source" , Tms );
		}
	}
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , Buffer , &(Address_SYSALIGN_TM_WSRC[Tms-1][Arm]) ) ) return FALSE;

	*sdata = _dREAD_DIGITAL( Address_SYSALIGN_TM_WSRC[Tms-1][Arm] , &CommStatus );

	return TRUE;
}

Module_Status Maint_SysAlign_Align_Mode_Set( int Arm , int option )
{
	int CommStatus;

	switch( option )
	{
	case 4: // No Align
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 1 , &CommStatus );	// No Align
		break;
	case 5: // Deltapick with previous align data
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 2 , &CommStatus );	// Deltapick with previous align data
		break;
	case 6: // Align Tr1
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 2" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 7: // Align Tr2
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 1" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 8: // Align Tr3
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 5" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 9: // Align Tr1->Tr2
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 1" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 10: // Align Tr2->Tr1
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 2" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	default:
		break;
	}

	return SYS_SUCCESS;
}

Module_Status Maint_SysAlign_Align2_Mode_Set( int Arm , int option )
{
	int CommStatus;
	switch( option )
	{
	case 4: // No Align
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 1 , &CommStatus );	// No Align
		break;
	case 5: // Deltapick with previous align data
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 2 , &CommStatus );	// Deltapick with previous align data
		break;
	case 6: // Align Tr1
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 2" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 7: // Align Tr2
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 1" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 8: // Align Tr3
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 5" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 9: // Align Tr1->Tr2
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 1" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	case 10: // Align Tr2->Tr1
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
		if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 2" , Arm + 'A' ) != SYS_SUCCESS ) return SYS_ABORTED;
		break;
	default:
		break;
	}

	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_SysAlign_MAINT_INTERFACE_RUN( LPSTR list , ... ) {
	va_list va;
	int CommStatus;
	char Buffer[256];
	char Buffer2[256];
	//
	if ( !Maint_SysAlign_IO_FIND( _K_S_IO , "e:SCHEDULER"   , &Address_SYSALIGN_Scheduler ) ) return SYS_ABORTED;
	if ( !Maint_SysAlign_IO_FIND( _K_D_IO , "CTC.TR_STATUS" , &Address_SYSALIGN_Transfer_Status ) ) return SYS_ABORTED;
	//
	va_start( va , list );
	vsprintf( Buffer2 , list , (LPSTR) va );
	va_end( va );
	//
	_dWRITE_DIGITAL( Address_SYSALIGN_Transfer_Status , 0 , &CommStatus );
	printf("------------Buffer -%s \n", Buffer2);
	sprintf( Buffer , "MAINT_INTERFACE %s" , Buffer2 );
	_dWRITE_STRING( Address_SYSALIGN_Scheduler , Buffer , &CommStatus );
	while ( TRUE ) {
		if ( !WAIT_SECONDS( 0.25 ) ) return SYS_ABORTED;
		switch( _dREAD_DIGITAL( Address_SYSALIGN_Transfer_Status , &CommStatus ) ) {
		case SYS_ABORTED : return SYS_ABORTED;
		case SYS_ERROR   : return SYS_ERROR;
		case SYS_SUCCESS : return SYS_SUCCESS;
		}
	}
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_Sys_Alignment( int type , int option ) {
	int CommStatus;
	int Arm , Station , Slot , dummy , dummy2;

	Arm     = READ_DIGITAL( SYS_AL_Arm		, &CommStatus );
	Station = READ_DIGITAL( SYS_AL_Station	, &CommStatus );
	Slot    = READ_DIGITAL( SYS_AL_Slot		, &CommStatus ) + 1;

	switch( Station ) {
	case SYS_LPMA :	//	LPMA
	case SYS_LPMB :	//	LPMB
	case SYS_LPMC :	//	LPMC
	case SYS_LPMD :	//	LPMD
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_CM( Station - SYS_LPMA + 1 ) )&&(( type == 1 )||( type == 2 )) ) return SYS_ABORTED;
		break;
	case SYS_Aligner :	//	Aligner
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return SYS_ABORTED;
		if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return SYS_ABORTED;
		break;
	case SYS_LLA_ATM :	//	LLA(A)
	case SYS_LLB_ATM :	//	LLB(A)
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_BM( Station - SYS_LLA_ATM + 1 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
	case SYS_LLA_VAC :	//	LLA(V)
	case SYS_LLB_VAC :	//	LLB(V)
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_BM( Station - SYS_LLA_VAC + 1 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
	case SYS_PM1 :	//	PM1
	case SYS_PM2 :	//	PM2
	case SYS_PM3 :	//	PM3
	case SYS_PM4 :	//	PM4
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( Station - SYS_PM1 + 1 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
    
	case SYS_PM5 :	//	PM5
	case SYS_PM6 :	//	PM6
	case SYS_PM7 :	//	PM7
	case SYS_PM8 :	//	PM8
	case SYS_PM9 :	//	PM9
	case SYS_PM10 :	//	PM10
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return SYS_ABORTED;
		// 2015.03.26 enumにPM14が入ったため"+1"を削除
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( Station - SYS_PM1 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		//if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( Station - SYS_PM1 + 1 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		//
		break;
	// 2015.03.26 PM11 削除
	//case SYS_PM11_1:
	//	if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return SYS_ABORTED;
	//	if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
	//	break;
	//case SYS_PM11_2:
	//	if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return SYS_ABORTED;
	//	if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
	//	break;

	// 2015.03.26 PM14(PM-G)追加
	case SYS_PM14 :
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 14 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
	//
	case SYS_PM12_1:
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
	case SYS_PM12_2:
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return SYS_ABORTED;
		if ( ( !MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) )&&(( type == 1 )||( type == 2 )) )  return SYS_ABORTED;
		break;
	}
	//=================================================================================================
	//=================================================================================================
	//=================================================================================================
	//=================================================================================================
	//=================================================================================================
	switch( type ) {
	case 0 : // HOME
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
		case SYS_Aligner :	//	Aligner
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_FM|%d|CM1|%d|0" , SYSALIGN_RUNMODE , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
		//case SYS_PM11_1: //	PM11(TM1) // 2015.03.26 PM11 削除
		case SYS_PM12_1: //	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM|%d|PM1|%c|1|1" , SYSALIGN_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
		case SYS_PM14 : //  PM14(PM-G)追加 // 2015.03.26 PM14 追加
		//case SYS_PM11_2: //	PM11(TM2)  // 2015.03.26 PM11 削除
		case SYS_PM12_2: //	PM12(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM2|%d|PM5|%c|1|1" , SYSALIGN_RUNMODE , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 1 : // PICK
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
			if ( !Maint_SysAlign_IO_FIND_FM_WIO( Arm , 0 ) ) return SYS_ABORTED;
			if ( Arm == 0 ) { // Arm A 
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|CM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|CM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_Aligner :	//	Aligner
			if ( !Maint_SysAlign_IO_FIND_FM_WIO( Arm , 0 ) ) return SYS_ABORTED;
			if ( option < 10 ) {
				if ( Arm == 0 ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0|BM%d" , SYSALIGN_RUNMODE , option + 1 ) == SYS_ABORTED ) return SYS_ABORTED;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0|BM%d" , SYSALIGN_RUNMODE , option + 1 ) == SYS_ABORTED ) return SYS_ABORTED;
				}
			}
			else if ( option == 10 ) {
				if ( Arm == 0 ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
				}
			}
			else if ( option == 11 ) {
				if ( Arm == 0 ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FALIC|%d|AL|1|0|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FALIC|%d|AL|0|1|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
				}
			}
			break;
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			if ( !Maint_SysAlign_IO_FIND_FM_WIO( Arm , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( Arm == 0 ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 1 , Arm , 0 ) ) return SYS_ABORTED;
//			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , RUNMODE_TMSIDE_WHEN_BM_PICK , Station - SYS_LLA_VAC + 1 ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 : 
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 1 , Arm , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 3 , Arm , 0 ) ) return SYS_ABORTED;
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 : //  PM14
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 2 , Arm , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( !Maint_SysAlign_IO_FIND_TM_WIO( 1 , Arm , 0 ) ) return SYS_ABORTED;
		//	// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	//
		//	if ( Maint_SysAlign_Align_Mode_Set( Arm , option ) == SYS_ABORTED ) return SYS_ABORTED;
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( !Maint_SysAlign_IO_FIND_TM_WIO( 2 , Arm , 0 ) ) return SYS_ABORTED;
		//	// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	//
		//	if ( Maint_SysAlign_Align_Mode_Set( Arm , option ) == SYS_ABORTED ) return SYS_ABORTED;
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 1 , Arm , 0 ) ) return SYS_ABORTED;
			// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM1|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			if ( Maint_SysAlign_Align2_Mode_Set( Arm , option ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM1|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM12(TM2)
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( 2 , Arm , 0 ) ) return SYS_ABORTED;
			// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			if ( Maint_SysAlign_Align2_Mode_Set( Arm , option ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 2 : // PLACE
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
			if ( !Maint_SysAlign_IO_FIND_CM_WIO( Station - SYS_LPMA + 1 , Slot , 1 ) ) return SYS_ABORTED;
			if ( Arm == 0 ) { // Arm A
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_Aligner :	//	Aligner
			if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return SYS_ABORTED;
			if ( Arm == 0 ) {
//				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FALIC|%d|AL|1|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|1|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
			}
			else {
//				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FALIC|%d|AL|0|1" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|0|1" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED; // 2006.10.24
			}
			break;
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			if ( !Maint_SysAlign_IO_FIND_BM_WIO( Station - SYS_LLA_ATM + 1 , Slot , 0 , &dummy , &dummy2 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( Arm == 0 ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( !Maint_SysAlign_IO_FIND_BM_WIO( Station - SYS_LLA_VAC + 1 , Slot , 0 , &dummy , &dummy2 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( Station - SYS_PM1 + 1 , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( Station - SYS_PM1 + 1 , 0 ) ) return SYS_ABORTED;
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( 14 , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( !Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) ) return SYS_ABORTED;
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( !Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) ) return SYS_ABORTED;
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM12(TM2)
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) ) return SYS_ABORTED;
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 3 : // GOTO
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
			if ( Arm == 0 ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|CM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|CM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LPMA + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_Aligner :	//	Aligner
			if ( Arm == 0 ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|AL|1|0" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|AL|0|1" , SYSALIGN_RUNMODE ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			if ( Arm == 0 ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|BM%d|%d|0" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_FM|%d|BM%d|0|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_ATM + 1 , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM12(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 4 : // EXTEND
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
		case SYS_Aligner :	//	Aligner
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			return SYS_ABORTED;
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM12(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "EXTEND_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 5 : // RETRACT
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
		case SYS_Aligner :	//	Aligner
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			return SYS_ABORTED;
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14, Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM12(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "RETRACT_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 6 : // UP
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
		case SYS_Aligner :	//	Aligner
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			return SYS_ABORTED;
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;

		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM11(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	case 7 : // DOWN
		switch( Station ) {
		case SYS_LPMA :	//	LPMA
		case SYS_LPMB :	//	LPMB
		case SYS_LPMC :	//	LPMC
		case SYS_LPMD :	//	LPMD
		case SYS_Aligner :	//	Aligner
		case SYS_LLA_ATM :	//	LLA(A)
		case SYS_LLB_ATM :	//	LLB(A)
			return SYS_ABORTED;
			break;
		case SYS_LLA_VAC :	//	LLA(V)
		case SYS_LLB_VAC :	//	LLB(V)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM|%d|BM%d|%c|1|%d" , SYSALIGN_RUNMODE , Station - SYS_LLA_VAC + 1 , Arm + 'A' , Slot ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM1 :	//	PM1
		case SYS_PM2 :	//	PM2
		case SYS_PM3 :	//	PM3
		case SYS_PM4 :	//	PM4
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM5 :	//	PM5
		case SYS_PM6 :	//	PM6
		case SYS_PM7 :	//	PM7
		case SYS_PM8 :	//	PM8
		case SYS_PM9 :	//	PM9
		case SYS_PM10 :	//	PM10
			// 2015.03.26 enumにPM14が入ったため"+1"を削除
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , Station - SYS_PM1 + 1 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			//
			break;
		// 2015.03.26 PM14(PM-G)追加
		case SYS_PM14 :	//	PM14
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 14 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		//
		// 2015.03.26 PM11 削除
		//case SYS_PM11_1 :	//	PM11(TM1)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//case SYS_PM11_2 :	//	PM11(TM2)
		//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 11 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		//	break;
		//
		case SYS_PM12_1 :	//	PM12(TM1)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		case SYS_PM12_2 :	//	PM11(TM2)
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "DOWN_TM2|%d|PM%d|%c|1|1" , SYSALIGN_RUNMODE , 12 , Arm + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
			break;
		default :
			return SYS_ABORTED;
		}
		break;
	}
	return SYS_SUCCESS;
}

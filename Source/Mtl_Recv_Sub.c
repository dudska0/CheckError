//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Mtl_Recv_Sub.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"
//------------------------------------------------------------------------------------------
#include "Mtl_Recv_Sub.h"
//------------------------------------------------------------------------------------------
#include "Kutlgui.h"
#include "..\resource.h"
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
extern BOOL SIMULATION_MODE;
//------------------------------------------------------------------------------------------
//=========================================================================================================
int	Address_MTLRECV_IO_Init = FALSE;
//
int	Address_MTLRECV_Transfer_Status;
int	Address_MTLRECV_Scheduler;
//
int	Address_MTLRECV_CM_WIO[4][30];
int	Address_MTLRECV_TM_WIO[4][2];
int	Address_MTLRECV_PM_WIO[60];
int	Address_MTLRECV_BM_WIO[4][30];
int	Address_MTLRECV_FM_WIO[2];
int	Address_MTLRECV_FAL_WIO;

int	Address_MTLRECV_TM_WSRC[4][2];
int	Address_MTLRECV_PM_WSRC[60];
int	Address_MTLRECV_BM_WSRC[4][30];
int	Address_MTLRECV_FM_WSRC[2];
int	Address_MTLRECV_FAL_WSRC;

int	Address_MTLRECV_TM_LOAD_STATUS[4][2];		// MTR7?_Load_Status? IO address
int Address_MTLRECV_MTR7_RUN_STATUS[4];	// 2016.03.31 suzuki
int Address_MTLRECV_MTR7_ERR_CODE[4];	// 2016.03.31 suzuki

int Address_MTLRECV_TM_RESULT[4];
int Address_MTLRECV_FM_RESULT;

int Address_MTLRECV_s_F_ROBOT[4];
int Address_MTLRECV_s_F_TMSNS[4]; // MapChamberで使用するFunction名のアドレス。
// 2014.03.19 suzuki add↓↓
int Address_MTLRECV_s_F_TMCAM[4]; // MapChamberで使用するFunction名のアドレス。
// 2014.03.19 suzuki add↑↑
int Address_MTLRECV_s_I_FMA_SNS;
int Address_MTLRECV_s_I_FMB_SNS;
int Address_MTLRECV_s_I_FAL_SNS;

char Address_MTLRECV_fstr_ROBOT[4][64] = { 0 , 0 , 0 , 0 };
char Address_MTLRECV_fstr_TMSNS[4][64] = { 0 , 0 , 0 , 0 }; // MapChamberで使用するFunction名のフ?ンクション名を格?する配列。
// 2014.03.19 suzuki add↓↓
char Address_MTLRECV_fstr_TMCAM[4][64] = { 0 , 0 , 0 , 0 }; // MapChamberで使用するFunction名のフ?ンクション名を格?する配列。(カメラ)
// 2014.03.19 suzuki add↑↑

char Address_MTLRECV_fstr_FMA_SNS[64] = { 0 , };
char Address_MTLRECV_fstr_FMB_SNS[64] = { 0 , };
char Address_MTLRECV_fstr_FAL_SNS[64] = { 0 , };

int Address_MTLRECV_s_F_PMSNS;
char Address_MTLRECV_fstr_PMSNS[64] = { 0 , };

int Address_MTLRECV_s_F_MAPPING[4];
char Address_MTLRECV_fstr_MAPPING1[64] = { 0 , };
char Address_MTLRECV_fstr_MAPPING2[64] = { 0 , };
char Address_MTLRECV_fstr_MAPPING3[64] = { 0 , };
char Address_MTLRECV_fstr_MAPPING4[64] = { 0 , };
//=========================================================================================================
int	MTLRECV_CASSETTE_MAX_SLOT = 25;
int	MTLRECV_BUFFER_MAX_SLOT = 2;
int	MTLRECV_TM_CHECKLOAD_PM[4] = { 11 , 11 , 7 , 0 };
int MTLRECV_RUNMODE = 2;
int	MTLRECV_FALSNS_STYLE = 0;
//=========================================================================================================
char LoadPort_Select_Map[16];
int LoadPort_Select_Number[4] = { 0, 1, 2, 3 };
//=========================================================================================================
//
// LoadPortの選択をUnuseにあわせて変更するための関数
//
//=========================================================================================================
void Set_LoadPort_Select_Map( void ) {
	int count = 0;
	int CommStatus;
	BOOL aFirstFlag = FALSE;

	if( READ_DIGITAL( FA_STATUS_MDL_CM1, &CommStatus ) != 0 ) {
		strcpy( LoadPort_Select_Map, "LP1" );
		LoadPort_Select_Number[count] = 0;
		aFirstFlag = TRUE;
		count++;
	}
	if( READ_DIGITAL( FA_STATUS_MDL_CM2, &CommStatus ) != 0 ) {
		if( aFirstFlag != TRUE ) { strcpy( LoadPort_Select_Map,  "LP2" ); }
		else                     { strcat( LoadPort_Select_Map, "|LP2" ); }
		LoadPort_Select_Number[count] = 1;
		aFirstFlag = TRUE;
		count++;
	}
	if( READ_DIGITAL( FA_STATUS_MDL_CM3, &CommStatus ) != 0 ) {
		if( aFirstFlag != TRUE ) { strcpy( LoadPort_Select_Map,  "LP3" ); }
		else                     { strcat( LoadPort_Select_Map, "|LP3" ); }
		LoadPort_Select_Number[count] = 2;
		aFirstFlag = TRUE;
		count++;
	}
	if( READ_DIGITAL( FA_STATUS_MDL_CM4, &CommStatus ) != 0 ) {
		if( aFirstFlag != TRUE ) { strcpy( LoadPort_Select_Map,  "LP4" ); }
		else                     { strcat( LoadPort_Select_Map, "|LP4" ); }
		LoadPort_Select_Number[count] = 3;
		aFirstFlag = TRUE;
		count++;
	}
	if( aFirstFlag != TRUE ) {
		printf("[MATERIAL RECOVERY] LoadPort All Unuse...\n");
		strcpy( LoadPort_Select_Map, "" );
	}

	return;
}
//=========================================================================================================
void Maint_Material_Simulation_IO_Check( int RunPart , int tms , int ModuleIndex , int Arm , int Slot , int *realwafer ) {
	char StrBuffer[256];
	//
	if ( !SIMULATION_MODE ) return;
	//
	switch( RunPart ) {
	case MTL_PART_CM :
		return;
		break;

	case MTL_PART_FM :
		sprintf( StrBuffer , "FM Wafer with [Arm%c] is Present? (YES=Present/NO=Absent)" , Arm + 'A' );
		break;

	case MTL_PART_FAL :
		sprintf( StrBuffer , "FAL Wafer is Present? (YES=Present/NO=Absent)" );
		break;

	case MTL_PART_BM :
		if ( tms == 0 ) {
			sprintf( StrBuffer , "BM%d Slot(%d) Wafer with [FM,Arm%c] is Present? (YES=Present/NO=Absent)" , ModuleIndex , Slot , Arm + 'A' );
		}
		else {
			sprintf( StrBuffer , "BM%d Slot(%d) Wafer with [TM%d,Arm%c] is Present? (YES=Present/NO=Absent)" , ModuleIndex , Slot , tms , Arm + 'A' );
		}
		break;

	case MTL_PART_TM :
		sprintf( StrBuffer , "TM%d Wafer with [Arm%c] is Present? (YES=Present/NO=Absent)" , tms , Arm + 'A' );
		break;

	case MTL_PART_PM :
		sprintf( StrBuffer , "PM%d Wafer with [TM%d,Arm%c] is Present? (YES=Present/NO=Absent)" , ModuleIndex , tms , Arm + 'A' );
		break;

	default :
		return;
		break;
	}

	// 2015.01.14 suzuki modify
	// 画面を切り替えても、メッセ?ジウィンドウが一番上に?示されるように変更。
	//if ( IDYES == MessageBox( GET_MAIN_WINDOW()/*GetTopWindow( NULL )*/ , StrBuffer , "Simulation Wafer Presnet/Absent Confirmation", MB_ICONQUESTION | MB_YESNO ) ) {
	if ( IDYES == MessageBox( NULL , StrBuffer , "Simulation Wafer Presnet/Absent Confirmation", MB_ICONQUESTION | MB_YESNO | MB_TOPMOST ) ) {
		if(( RunPart != MTL_PART_FAL )&&( RunPart != MTL_PART_FM )) { if ( *realwafer <= 0 ) { *realwafer = 1; }}
		else                                                        { if ( *realwafer != 2 ) { *realwafer = 2; }}
	}
	else {
		if(( RunPart != MTL_PART_FAL )&&( RunPart != MTL_PART_FM )) { *realwafer = 0; }
		else                                                        { *realwafer = 1; }
	}
}
//=========================================================================================================
//=========================================================================================================
void Maint_Material_Recovery_SET_RUN_MODE( int data ) {
	MTLRECV_RUNMODE = data;
}

void Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( int tms , int data ) {
	if ( ( tms >= 1 ) && ( tms <= 4 ) ) MTLRECV_TM_CHECKLOAD_PM[tms-1] = data;
}

void Maint_Material_Recovery_SET_CASSETTE_MAXSLOT( int data ) {
	if ( ( data >= 0 ) && ( data < 30 ) ) {
		MTLRECV_CASSETTE_MAX_SLOT = data;
	}
}

void Maint_Material_Recovery_SET_BUFFER_MAXSLOT( int data ) {
	if ( ( data >= 0 ) && ( data < 30 ) ) {
		MTLRECV_BUFFER_MAX_SLOT = data;
	}
}

void Maint_Material_Recovery_SET_FALSNS_CHECK_STYLE( int data ) {
	if ( ( data >= 0 ) && ( data < 4 ) ) {
		MTLRECV_FALSNS_STYLE = data;
	}
}

BOOL Maint_Material_Recovery_SET_FUNCTION_ROBOT( int tms , char *data ) {
	if ( ( tms <= 0 ) || ( tms > 4 ) ) return FALSE;
	strncpy( Address_MTLRECV_fstr_ROBOT[tms-1] , data , 63 );
	return TRUE;
}

// Program_Init_Codeで設定したフ?ンクション名(TMC_WFRSNS*_CONTROL)を配列に格?する。
BOOL Maint_Material_Recovery_SET_FUNCTION_TMSNS( int tms , char *data ) {
	if ( ( tms <= 0 ) || ( tms > 4 ) ) return FALSE;
	strncpy( Address_MTLRECV_fstr_TMSNS[tms-1] , data , 63 );
	return TRUE;
}

// 2014.03.19 suzuki add↓↓
// Program_Init_Codeで設定したフ?ンクション名(TMC_CAMERA*_CONTROL)を配列に格?する。
BOOL Maint_Material_Recovery_SET_FUNCTION_TMCAM( int tms , char *data ) {
	if ( ( tms <= 0 ) || ( tms > 4 ) ) return FALSE;
	strncpy( Address_MTLRECV_fstr_TMCAM[tms-1] , data , 63 );
	return TRUE;
}
// 2014.03.19 suzuki add↑↑

BOOL Maint_Material_Recovery_SET_IO_FMASNS( char *data ) {
	strncpy( Address_MTLRECV_fstr_FMA_SNS , data , 63 );
	return TRUE;
}

BOOL Maint_Material_Recovery_SET_IO_FMBSNS( char *data ) {
	strncpy( Address_MTLRECV_fstr_FMB_SNS , data , 63 );
	return TRUE;
}

BOOL Maint_Material_Recovery_SET_IO_FALSNS( char *data ) {
	strncpy( Address_MTLRECV_fstr_FAL_SNS , data , 63 );
	return TRUE;
}

BOOL Maint_Material_Recovery_SET_FUNCTION_PMSNS( char *data ) {
	strncpy( Address_MTLRECV_fstr_PMSNS , data , 63 );
	return TRUE;
}

BOOL Maint_Material_Recovery_SET_FUNCTION_MAPPING( int cass , char *data ) {
	if ( cass == 1 ) strncpy( Address_MTLRECV_fstr_MAPPING1 , data , 63 );
	if ( cass == 2 ) strncpy( Address_MTLRECV_fstr_MAPPING2 , data , 63 );
	if ( cass == 3 ) strncpy( Address_MTLRECV_fstr_MAPPING3 , data , 63 );
	if ( cass == 4 ) strncpy( Address_MTLRECV_fstr_MAPPING4 , data , 63 );
	return TRUE;
}

//=========================================================================================================
BOOL Maint_Material_Recovery_IO_FIND( int mode , char *ioname , int *ioaddress ) {
	int i , j;
	
	if ( !Address_MTLRECV_IO_Init ) {
		Address_MTLRECV_IO_Init = TRUE;
		//=========================================================
		if ( Address_MTLRECV_fstr_ROBOT[0][0] == 0 ) strcpy( Address_MTLRECV_fstr_ROBOT[0] , "TMC_ROBOT_CONTROL" );
		if ( Address_MTLRECV_fstr_ROBOT[1][0] == 0 ) strcpy( Address_MTLRECV_fstr_ROBOT[1] , "TMC_ROBOT2_CONTROL" );
//		if ( Address_MTLRECV_fstr_ROBOT[2][0] == 0 ) strcpy( Address_MTLRECV_fstr_ROBOT[2] , "TMC_ROBOT3_CONTROL" );
//		if ( Address_MTLRECV_fstr_ROBOT[3][0] == 0 ) strcpy( Address_MTLRECV_fstr_ROBOT[3] , "TMC_ROBOT4_CONTROL" );

		// Address_MTLRECV_fstr_TMSNSに何も格?されていない場合はTMC_WFRSNS*_CONTROLを格?する。
		if ( Address_MTLRECV_fstr_TMSNS[0][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMSNS[0] , "TMC_WFRSNS_CONTROL" );
		if ( Address_MTLRECV_fstr_TMSNS[1][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMSNS[1] , "TMC_WFRSNS2_CONTROL" );
//		if ( Address_MTLRECV_fstr_TMSNS[2][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMSNS[2] , "TMC_WFRSNS3_CONTROL" );

		// 2014.03.19 suzuki add↓↓
		// Address_MTLRECV_fstr_TMCAMに何も格?されていない場合はTMC_CAMERA*_CONTROLを格?する。
		if ( Address_MTLRECV_fstr_TMCAM[0][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMCAM[0] , "TMC_CAMERA_CONTROL" );
		if ( Address_MTLRECV_fstr_TMCAM[1][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMCAM[1] , "TMC_CAMERA2_CONTROL" );
//		if ( Address_MTLRECV_fstr_TMCAM[2][0] == 0 ) strcpy( Address_MTLRECV_fstr_TMSNS[2] , "TMC_WFRSNS3_CONTROL" );
		// 2014.03.19 suzuki add↑↑

		if ( Address_MTLRECV_fstr_FMA_SNS[0] == 0 ) strcpy( Address_MTLRECV_fstr_FAL_SNS  , "FM.ATR8_AWfrSns" );
		if ( Address_MTLRECV_fstr_FMB_SNS[0] == 0 ) strcpy( Address_MTLRECV_fstr_FAL_SNS  , "FM.ATR8_BWfrSns" );
		if ( Address_MTLRECV_fstr_FAL_SNS[0] == 0 ) strcpy( Address_MTLRECV_fstr_FAL_SNS  , "FM.ATR8_ALWfrSns" );

		if ( Address_MTLRECV_fstr_PMSNS[0] == 0 )   strcpy( Address_MTLRECV_fstr_PMSNS    , "PM_WFRSNS_CONTROL" );

		for ( i = 0 ; i < 4 ; i++ ) {
			Address_MTLRECV_s_F_ROBOT[i] = -2;
		}
		for ( i = 0 ; i < 4 ; i++ ) {
			Address_MTLRECV_s_F_MAPPING[i] = -2;
		}

		for ( i = 0 ; i < 4 ; i++ ) {
			Address_MTLRECV_s_F_TMSNS[i] = -2;
		}

		// 2014.03.19 suzuki add↓↓
		for ( i = 0 ; i < 4 ; i++ ) {
			Address_MTLRECV_s_F_TMCAM[i] = -2;
		}
		// 2014.03.19 suzuki add↑↑

		Address_MTLRECV_s_I_FMA_SNS = -2;
		Address_MTLRECV_s_I_FMB_SNS = -2;
		Address_MTLRECV_s_I_FAL_SNS = -2;
		//=========================================================
		Address_MTLRECV_s_F_PMSNS = -2;
		//=========================================================
		Address_MTLRECV_Transfer_Status = -2;
		Address_MTLRECV_Scheduler = -2;
		//=========================================================
		Address_MTLRECV_FM_RESULT = -2;
		Address_MTLRECV_FAL_WIO = -2;

		Address_MTLRECV_FAL_WSRC = -2;
		//
		for ( i = 0 ; i < 2 ; i++ ) {
			Address_MTLRECV_FM_WIO[i] = -2;
			Address_MTLRECV_FM_WSRC[i] = -2;
		}
		//
		for ( i = 0 ; i < 60 ; i++ ) {
			Address_MTLRECV_PM_WIO[i] = -2;
			Address_MTLRECV_PM_WSRC[i] = -2;
		}
		//
		for ( i = 0 ; i < 4 ; i++ ) {
			//
			Address_MTLRECV_TM_RESULT[i] = -2;
			Address_MTLRECV_MTR7_RUN_STATUS[i] = -2;	// 2016.03.31 suzuki
			Address_MTLRECV_MTR7_ERR_CODE[i] = -2;		// 2016.03.31 suzuki
			//
			for ( j = 0 ; j < 30 ; j++ ) {
				Address_MTLRECV_CM_WIO[i][j] = -2;
				Address_MTLRECV_BM_WIO[i][j] = -2;
				Address_MTLRECV_BM_WSRC[i][j] = -2;
			}
			for ( j = 0 ; j < 2 ; j++ ) {
				Address_MTLRECV_TM_WIO[i][j] = -2;
				Address_MTLRECV_TM_WSRC[i][j] = -2;
				Address_MTLRECV_TM_LOAD_STATUS[i][j] = -2;
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

BOOL Maint_Material_Recovery_IO_FIND_CM_WIO( int Cass , int Slot ) {
	char Buffer[32];
	sprintf( Buffer , "CM%d.C%02d_WAFER" , Cass , Slot );
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_CM_WIO[Cass-1][Slot-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_TM_WIO( int Tms , int Arm ) {
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
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_TM_WIO[Tms-1][Arm]) );
}

BOOL Maint_Material_Recovery_IO_FIND_TM_WSRC( int Tms , int Arm ) {
	char Buffer[32];
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
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_TM_WSRC[Tms-1][Arm]) );
}

BOOL Maint_Material_Recovery_IO_FIND_TM_LOAD_STATUS( int Tms , int Arm ) {
	char Buffer[32];
	if ( Tms == 1 ) {
		if ( Arm == 0 ) {
			sprintf( Buffer , "MTR7_Load_Status" );
		}
		else {
			sprintf( Buffer , "MTR7_Load_StatusB" );
		}
	}
	else {
		if ( Arm == 0 ) {
			sprintf( Buffer , "MTR7%d_Load_Status" , Tms );
		}
		else {
			sprintf( Buffer , "MTR7%d_Load_StatusB" , Tms );
		}
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_TM_LOAD_STATUS[Tms-1][Arm]) );
}

BOOL Maint_Material_Recovery_IO_FIND_MTR7_RUN_STATUS( int Tms ) {	// 2016.03.31 suzuki
	char Buffer[32];
	if ( Tms == 1 ) {
		sprintf( Buffer , "MTR7_Run_Status" );
	}
	else {
		sprintf( Buffer , "MTR7%d_Run_Status" , Tms );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_MTR7_RUN_STATUS[Tms-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_MTR7_ERR_CODE( int Tms ) {	// 2016.03.31 suzuki
	char Buffer[32];
	if ( Tms == 1 ) {
		sprintf( Buffer , "MTR7_ErrorCode" );
	}
	else {
		sprintf( Buffer , "MTR7%d_ErrorCode" , Tms );
	}
	return Maint_Material_Recovery_IO_FIND( _K_A_IO , Buffer , &(Address_MTLRECV_MTR7_ERR_CODE[Tms-1]) );
}


BOOL Maint_Material_Recovery_IO_FIND_FM_WIO( int Arm ) {
	char Buffer[32];
	if ( Arm == 0 ) {
		sprintf( Buffer , "CTC.FA_Wafer_Status" );
	}
	else {
		sprintf( Buffer , "CTC.FB_Wafer_Status" );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_FM_WIO[Arm]) );
}

BOOL Maint_Material_Recovery_IO_FIND_FM_WSRC( int Arm ) {
	char Buffer[32];
	if ( Arm == 0 ) {
		sprintf( Buffer , "CTC.FA_Wafer_Source" );
	}
	else {
		sprintf( Buffer , "CTC.FB_Wafer_Source" );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_FM_WSRC[Arm]) );
}

BOOL Maint_Material_Recovery_IO_FIND_PM_WIO( int Chamber ) {
	char Buffer[32];
	sprintf( Buffer , "CTC.PM%d_Wafer_Status" , Chamber );
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_PM_WIO[Chamber-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_PM_WSRC( int Chamber ) {
	char Buffer[32];
	sprintf( Buffer , "CTC.PM%d_Wafer_Source" , Chamber );
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_PM_WSRC[Chamber-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_BM_WIO( int Ch , int Slot ) {
	char Buffer[32];
	if ( Slot == 1 ) {
		sprintf( Buffer , "CTC.BM%d_Wafer_Status" , Ch );
	}
	else {
		sprintf( Buffer , "CTC.BM%d_Wafer_Status%d" , Ch , Slot );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_BM_WIO[Ch-1][Slot-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_BM_WSRC( int Ch , int Slot ) {
	char Buffer[32];
	if ( Slot == 1 ) {
		sprintf( Buffer , "CTC.BM%d_Wafer_Source" , Ch );
	}
	else {
		sprintf( Buffer , "CTC.BM%d_Wafer_Source%d" , Ch , Slot );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_BM_WSRC[Ch-1][Slot-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_FAL_WIO() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , "CTC.FM_AL_Wafer_Status" , &Address_MTLRECV_FAL_WIO );
}

BOOL Maint_Material_Recovery_IO_FIND_FAL_WSRC() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , "CTC.FM_AL_Wafer_Source" , &Address_MTLRECV_FAL_WSRC );
}

BOOL Maint_Material_Recovery_IO_FIND_TM_RESULT( int Tms ) {
	char Buffer[32];
	if ( Tms == 1 ) {
		sprintf( Buffer , "TM.Wafer_Result" );
	}
	else {
		sprintf( Buffer , "TM%d.Wafer_Result" , Tms );
	}
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Buffer , &(Address_MTLRECV_TM_RESULT[Tms-1]) );
}

BOOL Maint_Material_Recovery_IO_FIND_FM_RESULT() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , "FM.Wafer_Result" , &(Address_MTLRECV_FM_RESULT) );
}

BOOL Maint_Material_Recovery_IO_FIND_FUNCTION_ROBOT( int tms ) {
	return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_ROBOT[tms-1] , &(Address_MTLRECV_s_F_ROBOT[tms-1]) );
}
// MapChamberで使用するFunction名のアドレスを設定する。
BOOL Maint_Material_Recovery_IO_FIND_FUNCTION_TMSNS( int tms ) {
	return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_TMSNS[tms-1] , &(Address_MTLRECV_s_F_TMSNS[tms-1]) );
}
// 2014.03.19 sizuki add↓↓
// MapChamberで使用するFunction名のアドレスを設定する。(カメラ)
BOOL Maint_Material_Recovery_IO_FIND_FUNCTION_TMCAM( int tms ) {
	return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_TMCAM[tms-1] , &(Address_MTLRECV_s_F_TMCAM[tms-1]) );
}
// 2014.03.19 sizuki add↑↑

BOOL Maint_Material_Recovery_IO_FIND_IO_FMASNS() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Address_MTLRECV_fstr_FMA_SNS , &Address_MTLRECV_s_I_FMA_SNS );
}
BOOL Maint_Material_Recovery_IO_FIND_IO_FMBSNS() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Address_MTLRECV_fstr_FMB_SNS , &Address_MTLRECV_s_I_FMB_SNS );
}
BOOL Maint_Material_Recovery_IO_FIND_IO_FALSNS() {
	return Maint_Material_Recovery_IO_FIND( _K_D_IO , Address_MTLRECV_fstr_FAL_SNS , &Address_MTLRECV_s_I_FAL_SNS );
}
BOOL Maint_Material_Recovery_IO_FIND_FUNCTION_PMSNS() {
	return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_PMSNS , &Address_MTLRECV_s_F_PMSNS );
}
BOOL Maint_Material_Recovery_IO_FIND_FUNCTION_MAPPING( int cass ) {
	if ( cass == 1 ) return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_MAPPING1 , &(Address_MTLRECV_s_F_MAPPING[0]) );
	if ( cass == 2 ) return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_MAPPING2 , &(Address_MTLRECV_s_F_MAPPING[1]) );
	if ( cass == 3 ) return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_MAPPING3 , &(Address_MTLRECV_s_F_MAPPING[2]) );
	if ( cass == 4 ) return Maint_Material_Recovery_IO_FIND( _K_F_IO , Address_MTLRECV_fstr_MAPPING4 , &(Address_MTLRECV_s_F_MAPPING[3]) );
	return FALSE;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_MAINT_INTERFACE_RUN( LPSTR list , ... ) {
	va_list va;
	int CommStatus;
	char Buffer[256];
	char Buffer2[256];
	//
	if ( !Maint_Material_Recovery_IO_FIND( _K_S_IO , "e:SCHEDULER"   , &Address_MTLRECV_Scheduler ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND( _K_D_IO , "CTC.TR_STATUS" , &Address_MTLRECV_Transfer_Status ) ) return SYS_ABORTED;
	//
	va_start( va , list );
	vsprintf( Buffer2 , list , (LPSTR) va );
	va_end( va );
	//
	_dWRITE_DIGITAL( Address_MTLRECV_Transfer_Status , 0 , &CommStatus );
	
	sprintf( Buffer , "MAINT_INTERFACE %s" , Buffer2 );
	_dWRITE_STRING( Address_MTLRECV_Scheduler , Buffer , &CommStatus );
	while ( TRUE ) {
		if ( !WAIT_SECONDS( 0.25 ) ) return SYS_ABORTED;
		switch( _dREAD_DIGITAL( Address_MTLRECV_Transfer_Status , &CommStatus ) ) {
		case SYS_ABORTED : return SYS_ABORTED;
		case SYS_ERROR   : return SYS_ERROR;
		case SYS_SUCCESS : return SYS_SUCCESS;
		}
	}
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_CM( int Mode , int Cass , int Slot ) {
	int i , CommStatus , ss , es;
	//==================================================================
	if ( ( Cass <= 0 ) || ( Cass > 4 ) ) return SYS_ABORTED;
	//==================================================================
	if ( Slot <= 0 ) {
		ss = 1;
		es = MTLRECV_CASSETTE_MAX_SLOT;
	}
	else {
		if ( Slot > MTLRECV_CASSETTE_MAX_SLOT ) return SYS_ABORTED;
		ss = Slot;
		es = Slot;
	}
	//==================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_CM( Cass ) ) return SYS_SUCCESS;
		//======================================================================================
		if ( Maint_Material_Recovery_IO_FIND_FUNCTION_MAPPING( Cass ) ) {
			if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_MAPPING[Cass-1] , "MAPPING_MTL CM%d" , Cass ) == SYS_ABORTED ) return SYS_ABORTED;
		}
		else {
			if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "MAPPING|%d|CM%d" , MTLRECV_RUNMODE , Cass ) == SYS_ABORTED ) return SYS_ABORTED;
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		for ( i = ss ; i <= es ; i++ ) {
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_CM_WIO( Cass , i ) ) return SYS_ABORTED;
			//======================================================================================
			_dWRITE_DIGITAL( Address_MTLRECV_CM_WIO[Cass-1][i-1] , 2 , &CommStatus );
		}
	}
	else {
		for ( i = ss ; i <= es ; i++ ) {
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_CM_WIO( Cass , i ) ) return SYS_ABORTED;
			//======================================================================================
			_dWRITE_DIGITAL( Address_MTLRECV_CM_WIO[Cass-1][i-1] , 1 , &CommStatus );
		}
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
int _dREAD_DIGITAL_TRUE( int io , int *CommStatus ) {	// 2016.03.31 suzuki ProB semicon_00_OMR-0283 from OBJ_TM_Rblow
	int Data;
	Data = _dREAD_DIGITAL( io , CommStatus );
	if ( !(*CommStatus) ) {
		_sleep(250);
		Data = _dREAD_DIGITAL( io , CommStatus );
		if ( !(*CommStatus) ) {
			_sleep(500);
			Data = _dREAD_DIGITAL( io , CommStatus );
			if ( !(*CommStatus) ) {
				_sleep(1000);
				Data = _dREAD_DIGITAL( io , CommStatus );
				if ( !(*CommStatus) ) {
					_sleep(1000);
					return( _dREAD_DIGITAL( io , CommStatus ) );
				}
				else return Data;
			}
			else return Data;
		}
		else return Data;
	}
	else return Data;
}
//------------------------------------------------------------------------------------------
BOOL Get_Wafer_Info_From_Dialog( int tms, int Finger, int *Source , int *Status ) {	// 2016.03.31 suzuki ProB semicon_00_OMR-0283
	char TM_Wafer_IO_Name[64], TM_Wafer_SrcIO_Name[64];

	// ?イアログに?示するIO名を取得
	if ( tms == 1 )
	{
		if ( Finger == 0 )
		{
			strcpy( TM_Wafer_IO_Name , "CTC.TA_Wafer_Status" );
			strcpy( TM_Wafer_SrcIO_Name , "CTC.TA_Wafer_Source" );
		}
		else
		{
			strcpy( TM_Wafer_IO_Name , "CTC.TB_Wafer_Status" );
			strcpy( TM_Wafer_SrcIO_Name , "CTC.TB_Wafer_Source" );
		}
	}
	else if ( tms == 2 )
	{
		if ( Finger == 0 )
		{
			strcpy( TM_Wafer_IO_Name , "CTC.TA2_Wafer_Status" );
			strcpy( TM_Wafer_SrcIO_Name , "CTC.TA2_Wafer_Source" );
		}
		else
		{
			strcpy( TM_Wafer_IO_Name , "CTC.TB2_Wafer_Status" );
			strcpy( TM_Wafer_SrcIO_Name , "CTC.TB2_Wafer_Source" );
		}
	}

	// LP数を動的に取得
	Set_LoadPort_Select_Map();

	// ?イアログ?示
	if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", TM_Wafer_SrcIO_Name , LoadPort_Select_Map , Source) )
	{
		return FALSE;
	}
	if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", TM_Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , Status) )
	{
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------------------------
Module_Status Send_Wafer_Status_To_TM_Robot( int tms, int Finger, int isWaferOccupied) {	// // 2016.03.31 suzuki ProB semicon_00_OMR-0283
	int CommStatus;
	int err, AlmResult;
	const int ALARM_NO_MAG7_COMM_ERROR[2] = { 1121 , 1321 };
	const int ALARM_NO_MAG7_OTHER[2]      = { 1125 , 1325 };
	const int ALARM_NO_MAG7_CDM[2]        = { 1126 , 1326 };
	const int MTR7_ERROR_CODE_CDM = 604;
	char Buffer[256];

	while( TRUE )
	{
		// MAG7のLoadStatus更新する
		_dWRITE_DIGITAL( Address_MTLRECV_TM_LOAD_STATUS[tms-1][Finger] , isWaferOccupied , &CommStatus );
		//if( CommStatus ) { return SYS_SUCCESS; }	// 応答を待たないので、CommStatusを見る意味はない

		_dREAD_DIGITAL_TRUE( Address_MTLRECV_MTR7_RUN_STATUS[tms-1] , &CommStatus );
		if ( !CommStatus ) {
			// 通信異常
			AlmResult = ALARM_MANAGE( ALARM_NO_MAG7_COMM_ERROR[tms-1] );
			if      ( AlmResult == ALM_IGNORE ) { return SYS_SUCCESS; }
			else if ( AlmResult != ALM_RETRY  ) { return SYS_ABORTED; }
			else { continue; }
		}

		// エラ?応答 (CDM接続時)
		err = (int) _dREAD_ANALOG( Address_MTLRECV_MTR7_ERR_CODE[tms-1] , &CommStatus );
		if ( err == 0 )	// 正常動作
		{
			return SYS_SUCCESS;
		}
		else if ( err == MTR7_ERROR_CODE_CDM )
		{
			AlmResult = ALARM_MANAGE( ALARM_NO_MAG7_CDM[tms-1] );
			if ( AlmResult != ALM_RETRY  ) { return SYS_ABORTED; }
			else { continue; }
		}

		// エラ?応答 (?来ならALID=1122?1124に分けるべきだが、意味がなさそうなので省略)
		ALARM_MESSAGE_GET( ALARM_NO_MAG7_OTHER[tms-1] , Buffer );
		sprintf( Buffer , "%s (ERROR=%d)" , Buffer, err );
		ALARM_MESSAGE_SET( ALARM_NO_MAG7_OTHER[tms-1] , Buffer );

		AlmResult = ALARM_MANAGE( ALARM_NO_MAG7_OTHER[tms-1] );
		if      ( AlmResult == ALM_IGNORE ) { return SYS_SUCCESS; }
		else if ( AlmResult != ALM_RETRY  ) { return SYS_ABORTED; }
		else { continue; }
	}
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_TM( int Mode , int tms , int Station , int Finger , int PresentSetValue , int *Sel ) {
	int CommStatus , GuiWafer , RealWafer , rst;
	int Source = 0, Status = 1;
	
	if ( ( tms <= 0 ) || ( tms > 4 ) ) return SYS_ABORTED;
	
	//======================================================================================
	if ( !Maint_Material_Recovery_IO_FIND_TM_WIO( tms , Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_TM_WSRC( tms , Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_TM_LOAD_STATUS( tms , Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_MTR7_RUN_STATUS( tms ) ) return SYS_ABORTED;	// 2016.03.31 suzuki
	if ( !Maint_Material_Recovery_IO_FIND_MTR7_ERR_CODE( tms ) ) return SYS_ABORTED;	// 2016.03.31 suzuki
	//======================================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM( tms ) ) return SYS_SUCCESS;
		//======================================================================================
		GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , &CommStatus );
		//======================================================================================
		if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_ROBOT( tms ) ) return SYS_ABORTED;
		// MapChamberで使用するFunction名のアドレスを設定する。
		if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_TMSNS( tms ) ) return SYS_ABORTED;
		// 2014.03.19 suzuki add↓↓
		// MapChamberで使用するFunction名のアドレスを設定する。(カメラ)
		if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_TMCAM( tms ) ) return SYS_ABORTED;
		// 2014.03.19 suzuki add↑↑
		//======================================================================================
		if ( Station <= 0 ) rst = MTLRECV_TM_CHECKLOAD_PM[ tms - 1 ];
		else				rst = Station;
		//======================================================================================
		// 2016.03.31 suzuki Wafer有無が不明なので、低速回?と設定
		if( Send_Wafer_Status_To_TM_Robot( tms, Finger, 1 ) != SYS_SUCCESS ) { return SYS_ABORTED; }
		// 2016.03.31 suzuki コメント追加 - Rotate(default : PM11)して、カメラ撮影?ェック。結果はIO TM.Wafer_Resultに保存。
		// GOTOを実行してから、WaferSensorでウェハ有無を検出する。
		//if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_ROBOT[tms-1] , "CHECKLOAD %c_PM%d" , Finger + 'A' , rst ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( tms == 1 ) {
			if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , MTLRECV_RUNMODE , rst , Finger + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		}
		else if ( tms == 2 ) {
			if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , MTLRECV_RUNMODE , rst , Finger + 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
		}

		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↓↓
		// 2014.03.19 suzuki modify↓↓
		// PM-Fの時はカメラ撮影でウェハ有無を判定する。
		// オ?ロンカメラ正式対応版ではPM-Fでなくてもカメラ撮影でウェハ有無を判定するようにする。
		if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_TMCAM[tms-1] , "WAFER_CHECK %c_PM%d TR%d" , Finger + 'A' , rst , tms ) == SYS_ABORTED ) return SYS_ABORTED;

		/* 2014.08.20 コメントアウト
		//if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_TMSNS[tms-1] , "WAFER_CHECK %c_PM%d TR%d" , Finger + 'A' , rst , tms ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Station != 4 ) {
			if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_TMSNS[tms-1] , "WAFER_CHECK %c_PM%d TR%d" , Finger + 'A' , rst , tms ) == SYS_ABORTED ) return SYS_ABORTED;
		}
		else { 
			if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_TMCAM[tms-1] , "WAFER_CHECK %c_PM%d TR%d" , Finger + 'A' , rst , tms ) == SYS_ABORTED ) return SYS_ABORTED;
		}
		*/
		// 2014.03.19 suzuki modify↑↑
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↓↓
		
		//======================================================================================
		if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( tms ) ) return SYS_ABORTED;
		//======================================================================================
		RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , &CommStatus );
		//======================================================================================
		Maint_Material_Simulation_IO_Check( MTL_PART_TM , tms , 0 , Finger , 0 , &RealWafer );
		//======================================================================================
		
		// Z-axis SensorがOFFの時、TM*.Wafer_Resultを?ェックしない為"RealWafer"が更新されない対策。(2009.09.01 sawatari)
		// Zaxis Wafer Sensor CheckがOffのときの処理
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↓↓
		// 2014.03.19 suzuki modify↓↓
		// オ?ロンカメラ正式対応版ではPM-FでなくてもカメラOnOff設定を使用する。
		if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
			_dWRITE_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , 0 , &CommStatus );
			RealWafer = 0;			
		}
		/*
		if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
			_dWRITE_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , 0 , &CommStatus );
			RealWafer = 0;			
		}
		*/
		/* 2014.08.20 コメントアウト
		if ( Station != 4 ) {
			if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
				_dWRITE_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , 0 , &CommStatus );
				RealWafer = 0;			
			}
		}
		else { 
			if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
				_dWRITE_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , 0 , &CommStatus );
				RealWafer = 0;			
			}
		}
		*/
		// 2014.03.19 suzuki modify↑↑
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↑↑
		switch( RealWafer ) {
			case 0   :
				if ( GuiWafer > 0 ) {
					// Clear Wafer
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , 0 , &CommStatus );
				}
				if ( *Sel < 0 ) *Sel = Finger;
				break;
			default :
				if ( GuiWafer <= 0 ) {
					// Make Wafer
					if( !Get_Wafer_Info_From_Dialog( tms, Finger, &Source, &Status ) ) {return SYS_ABORTED; }	// 2016.03.31 suzuki
					if( Send_Wafer_Status_To_TM_Robot( tms, Finger, 1 ) != SYS_SUCCESS ) {return SYS_ABORTED; }	// 2016.03.31 suzuki

					// CTCの情報を更新
					printf( "1.Wafer Source Write : %d / value : %d / tms = %d, Finger = %d, Source = %d\n", Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source], tms, Finger, Source );
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source] , &CommStatus );
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , Status , &CommStatus );

					return SYS_SUCCESS;	// 2016.03.31 suzuki
				}
				break;
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		if( !Get_Wafer_Info_From_Dialog( tms, Finger, &Source, &Status ) ) {return SYS_ABORTED; }		// 2016.03.31 suzuki
		if( Send_Wafer_Status_To_TM_Robot( tms, Finger, 1 ) != SYS_SUCCESS ) {return SYS_ABORTED; }		// 2016.03.31 suzuki

		// CTCの情報を更新
		printf( "2.Wafer Source Write : %d / value : %d / tms = %d, Finger = %d, Source = %d\n", Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source], tms, Finger, Source );
		_dWRITE_DIGITAL( Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source] , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , Status , &CommStatus );

		return SYS_SUCCESS;	// 2016.03.31 suzuki
	}
	else {
		// 160125 nakamura コメント追加：ロ?ットの情報の更新は、わざとしていない？（WaferありでのEmptyでロ?ットを更新すると、ZもDown位置で範囲外になって、Pickで割れると思われる
		_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , 0 , &CommStatus );
	}

	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_PM( BOOL fm , int Mode , int tms , int Chamber , int Finger , int PresentSetValue ) {
	int CommStatus , GuiWafer , RealWafer;
	int Source = 0, Status = 1, iret, isrc;
	char Wafer_IO_Name[64], Wafer_SrcIO_Name[64];
	//======================================================================================
	if ( ( tms <= 0 ) || ( tms > 4 ) ) return SYS_ABORTED;
	if ( ( Chamber <= 0 ) || ( Chamber > 60 ) ) return SYS_ABORTED;
	//======================================================================================
	if ( !Maint_Material_Recovery_IO_FIND_TM_WIO( tms , Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_TM_WSRC( tms , Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_TM_LOAD_STATUS( tms , Finger ) ) return SYS_ABORTED;
	//======================================================================================
	if ( !Maint_Material_Recovery_IO_FIND_PM_WIO( Chamber ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_PM_WSRC( Chamber ) ) return SYS_ABORTED;
	//======================================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_PM( Chamber ) ) return SYS_SUCCESS;
		//======================================================================================
		GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , &CommStatus );
		//======================================================================================
		if ( fm ) {
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_PMSNS() ) return SYS_ABORTED;
			//======================================================================================
			if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_PMSNS , "PM%d 1" , Chamber ) == SYS_ABORTED ) return SYS_ABORTED;
			//============================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( 1 ) ) return SYS_ABORTED;
			//======================================================================================
			RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[0] , &CommStatus );
			//======================================================================================
		}
		else {
			//======================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM( tms ) ) return SYS_SUCCESS;
			//======================================================================================
				
			if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|PM%d|%c|1|%d" , tms , MTLRECV_RUNMODE , Chamber , Finger + 'A' , 1 ) == SYS_ABORTED ) return SYS_ABORTED;
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( tms ) ) return SYS_ABORTED;
			//======================================================================================
			RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , &CommStatus );
			//======================================================================================
		}
		//======================================================================================
		Maint_Material_Simulation_IO_Check( MTL_PART_PM , tms , Chamber , Finger , 0 , &RealWafer );
		//======================================================================================
		switch( RealWafer ) {
		case 0   :
			if ( GuiWafer > 0 ) {
				// Clear Wafer
				if ( fm ) {
					_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , 0 , &CommStatus );
				}
				else {
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , 0 , &CommStatus );
				}
			}
			break;
		default :
			if ( GuiWafer <= 0 ) {
				// Make Wafer
				if ( fm ) {
					sprintf( Wafer_IO_Name , "CTC.PM%d_Wafer_Status" , Chamber );//-1 );
					sprintf( Wafer_SrcIO_Name , "CTC.PM%d_Wafer_Source" , Chamber );//-1 );
					Set_LoadPort_Select_Map();
					//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
					if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
					{
						return SYS_ABORTED;
					}
					if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
					{
						return SYS_ABORTED;
					}
					//_dWRITE_DIGITAL( Address_MTLRECV_PM_WSRC[Chamber-1] , Source , &CommStatus );
					_dWRITE_DIGITAL( Address_MTLRECV_PM_WSRC[Chamber-1] , LoadPort_Select_Number[Source] , &CommStatus );
					_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , Status , &CommStatus );
					//_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , PresentSetValue , &CommStatus );	// 以前はこれ
				}
				else {
					if ( tms == 1 )
					{
						if ( Finger == 0 )
						{
							strcpy( Wafer_IO_Name , "CTC.TA_Wafer_Status" );
							strcpy( Wafer_SrcIO_Name , "CTC.TA_Wafer_Source" );
						}
						else
						{
							strcpy( Wafer_IO_Name , "CTC.TB_Wafer_Status" );
							strcpy( Wafer_SrcIO_Name , "CTC.TB_Wafer_Source" );
						}
					}
					else if ( tms == 2 )
					{
						if ( Finger == 0 )
						{
							strcpy( Wafer_IO_Name , "CTC.TA2_Wafer_Status" );
							strcpy( Wafer_SrcIO_Name , "CTC.TA2_Wafer_Source" );
						}
						else
						{
							strcpy( Wafer_IO_Name , "CTC.TB2_Wafer_Status" );
							strcpy( Wafer_SrcIO_Name , "CTC.TB2_Wafer_Source" );
						}
					}
					Set_LoadPort_Select_Map();
					//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )

					iret = MODAL_DIGITAL_BOX1(GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name, LoadPort_Select_Map, &Source);
					printf("wrf src Name = [%s] / LoadPort_Select_Map = %s / return = %d / Src = %d\n", Wafer_SrcIO_Name, LoadPort_Select_Map, iret, Source);
					if( !iret )
					{
						return SYS_ABORTED;
					}

					iret = MODAL_DIGITAL_BOX2(GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name, 1, MTLRECV_CASSETTE_MAX_SLOT, &Status);
					
					printf("Wafer IO = [%s] / End slot = %d / Status = %d / ret = %d\n", Wafer_IO_Name, MTLRECV_CASSETTE_MAX_SLOT, Status, iret );
					if( !iret )
					{
						return SYS_ABORTED;
					}


					//_dWRITE_DIGITAL( Address_MTLRECV_TM_WSRC[tms-1][Finger] , Source , &CommStatus );
					printf( "3.Wafer Source Write : %d / value : %d / tms = %d, Finger = %d, Source = %d\n", Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source], tms, Finger, Source );
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WSRC[tms-1][Finger] , LoadPort_Select_Number[Source] , &CommStatus );
					_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , Status , &CommStatus );
					//_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , PresentSetValue , &CommStatus );	// 以前はこれ
				}
			}
			if ( !fm ) {
				if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|PM%d|%c|1|%d" , tms , MTLRECV_RUNMODE , Chamber , Finger + 'A' , 1 ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			break;
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		sprintf( Wafer_IO_Name , "CTC.PM%d_Wafer_Status" , Chamber );//-1 );
		sprintf( Wafer_SrcIO_Name , "CTC.PM%d_Wafer_Source" , Chamber );//-1 );
		Set_LoadPort_Select_Map();
		//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
		{
			return SYS_ABORTED;
		}
		if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
		{
			return SYS_ABORTED;
		}
		//_dWRITE_DIGITAL( Address_MTLRECV_PM_WSRC[Chamber-1] , Source , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_PM_WSRC[Chamber-1] , LoadPort_Select_Number[Source] , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , Status , &CommStatus );
		//_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , PresentSetValue , &CommStatus );	// 以前はこれ
	}
	else {
		_dWRITE_DIGITAL( Address_MTLRECV_PM_WIO[Chamber-1] , 0 , &CommStatus );
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_BM( BOOL fm , int Mode , int tms , int Chamber , int Finger , int Slot , int PresentSetValue ) {
	int GuiWafer , CommStatus , RealWafer , j , ss , es;
	int Source = 0, Status = 1;
	char Wafer_IO_Name[64], Wafer_SrcIO_Name[64];
	//======================================================================================
	if ( ( tms < 0 ) || ( tms > 4 ) ) return SYS_ABORTED;
	if ( ( Chamber <= 0 ) || ( Chamber > 4 ) ) return SYS_ABORTED;
	//======================================================================================
	if ( Slot <= 0 ) {
		ss = 1;
		es = MTLRECV_BUFFER_MAX_SLOT;
	}
	else {
		if ( Slot > MTLRECV_BUFFER_MAX_SLOT ) return SYS_ABORTED;
		ss = Slot;
		es = Slot;
	}
	//======================================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_BM( Chamber ) ) return SYS_SUCCESS;
		//======================================================================================
		if ( tms == 0 ) {
			//======================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return SYS_SUCCESS;
			//======================================================================================
			if ( !fm ) {
				if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , MTLRECV_RUNMODE , Chamber ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			//=============================================================================================
			for ( j = ss ; j <= es ; j++ ) {
				//======================================================================================
				if ( !Maint_Material_Recovery_IO_FIND_BM_WIO( Chamber , j ) ) return SYS_ABORTED;
				if ( !Maint_Material_Recovery_IO_FIND_BM_WSRC( Chamber , j ) ) return SYS_ABORTED;
				//======================================================================================
				GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , &CommStatus );
				//======================================================================================
				if ( fm ) {
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_PMSNS() ) return SYS_ABORTED;
					//======================================================================================
					if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_PMSNS , "BM%d %d" , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
					//============================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( 1 ) ) return SYS_ABORTED;
					//======================================================================================
					RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[0] , &CommStatus );
					//======================================================================================
				}
				else {
					if ( Finger == 0 ) {
						if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|%d|0" , MTLRECV_RUNMODE , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
					}
					else {
						if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|0|%d" , MTLRECV_RUNMODE , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
					}
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_FM_RESULT() ) return SYS_ABORTED;
					//======================================================================================
					RealWafer = _dREAD_DIGITAL( Address_MTLRECV_FM_RESULT , &CommStatus );
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_FM_WIO( Finger ) ) return SYS_ABORTED;
					if ( !Maint_Material_Recovery_IO_FIND_FM_WSRC( Finger ) ) return SYS_ABORTED;
					//======================================================================================
				}
				Maint_Material_Simulation_IO_Check( MTL_PART_BM , 0 , Chamber , Finger , j , &RealWafer );
				//======================================================================================
				switch( RealWafer ) {
				case 0   :
					if ( GuiWafer > 0 ) {
						// Clear Wafer
						if ( fm ) {
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , 0 , &CommStatus );
						}
						else {
							_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , 0 , &CommStatus );
						}
					}
					break;
				default :
					if ( GuiWafer <= 0 ) {
						// Make Wafer
						if ( fm ) {
							sprintf( Wafer_IO_Name , "CTC.BM%d_Wafer_Status" , Chamber );
							sprintf( Wafer_SrcIO_Name , "CTC.BM%d_Wafer_Source" , Chamber );
							Set_LoadPort_Select_Map();
							//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
							if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
							{
								return SYS_ABORTED;
							}
							if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
							{
								return SYS_ABORTED;
							}
							//_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , Source , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , LoadPort_Select_Number[Source] , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , Status , &CommStatus );
							//_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , PresentSetValue , &CommStatus );	// 以前はこれ
						}
						else {
							if ( Finger == 0 )
							{
								sprintf( Wafer_IO_Name , "CTC.FA_Wafer_Status" , Chamber-1 );
								sprintf( Wafer_SrcIO_Name , "CTC.FA_Wafer_Source" , Chamber-1 );
							}
							else
							{
								sprintf( Wafer_IO_Name , "CTC.FB_Wafer_Status" , Chamber-1 );
								sprintf( Wafer_SrcIO_Name , "CTC.FB_Wafer_Source" , Chamber-1 );
							}
							Set_LoadPort_Select_Map();
							//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
							if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
							{
								return SYS_ABORTED;
							}
							if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
							{
								return SYS_ABORTED;
							}
							//_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , Source , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , LoadPort_Select_Number[Source] , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , Status , &CommStatus );
							//_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , PresentSetValue , &CommStatus );	// 以前はこれ
						}
					}
					if ( !fm ) {
						if ( Finger == 0 ) {
							if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|%d|0" , MTLRECV_RUNMODE , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
						}
						else {
							if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|0|%d" , MTLRECV_RUNMODE , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
						}
					}
					break;
				}
			}
		}
		else {
			//======================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM( tms ) ) return SYS_SUCCESS;
			//=============================================================================================
			if ( !fm ) {
				if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , MTLRECV_RUNMODE , Chamber ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			//=============================================================================================
			for ( j = ss ; j <= es ; j++ ) {
				//======================================================================================
				if ( !Maint_Material_Recovery_IO_FIND_BM_WIO( Chamber , j ) ) return SYS_ABORTED;
				if ( !Maint_Material_Recovery_IO_FIND_BM_WSRC( Chamber , j ) ) return SYS_ABORTED;
				//======================================================================================
				GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , &CommStatus );
				//======================================================================================
				if ( fm ) {
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_PMSNS() ) return SYS_ABORTED;
					//======================================================================================
					if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_PMSNS , "BM%d %d" , Chamber , j ) == SYS_ABORTED ) return SYS_ABORTED;
					//============================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( 1 ) ) return SYS_ABORTED;
					//======================================================================================
					RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[0] , &CommStatus );
					//======================================================================================
				}
				else {
					if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PICK_TM%d|%d|BM%d|%c|1|%d" , tms , MTLRECV_RUNMODE , Chamber , Finger + 'A' , j ) == SYS_ABORTED ) return SYS_ABORTED;
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_FUNCTION_ROBOT( tms ) ) return SYS_ABORTED;
					//======================================================================================
					if ( _dRUN_FUNCTIONF( Address_MTLRECV_s_F_ROBOT[tms-1] , "CHECKLOAD %c_PM%d" , Finger + 'A' , MTLRECV_TM_CHECKLOAD_PM[tms-1] ) == SYS_ABORTED ) return SYS_ABORTED;
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_TM_RESULT( tms ) ) return SYS_ABORTED;
					//======================================================================================
					RealWafer = _dREAD_DIGITAL( Address_MTLRECV_TM_RESULT[tms-1] , &CommStatus );
					//======================================================================================
					if ( !Maint_Material_Recovery_IO_FIND_TM_WIO( tms , Finger ) ) return SYS_ABORTED;
					if ( !Maint_Material_Recovery_IO_FIND_TM_WSRC( tms , Finger ) ) return SYS_ABORTED;
					if ( !Maint_Material_Recovery_IO_FIND_TM_LOAD_STATUS( tms , Finger ) ) return SYS_ABORTED;
					//======================================================================================
				}
				//======================================================================================
				Maint_Material_Simulation_IO_Check( MTL_PART_BM , tms , Chamber , Finger , j , &RealWafer );
				//======================================================================================
				switch( RealWafer ) {
				case 0   :
					if ( GuiWafer > 0 ) {
						// Clear Wafer
						if ( fm ) {
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , 0 , &CommStatus );
						}
						else {
							_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , 0 , &CommStatus );
						}
					}
					break;
				default :
					if ( GuiWafer <= 0 ) {
						// Make Wafer
						if ( fm ) {
							sprintf( Wafer_IO_Name , "CTC.BM%d_Wafer_Status" , Chamber );
							sprintf( Wafer_SrcIO_Name , "CTC.BM%d_Wafer_Source" , Chamber );
							Set_LoadPort_Select_Map();
							//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
							if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
							{
								return SYS_ABORTED;
							}
							if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
							{
								return SYS_ABORTED;
							}
							//_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , Source , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , LoadPort_Select_Number[Source] , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , Status , &CommStatus );
							//_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , PresentSetValue , &CommStatus );	// 以前はこれ
						}
						else {
							if ( Finger == 0 )
							{
								sprintf( Wafer_IO_Name , "CTC.FA_Wafer_Status" );
								sprintf( Wafer_SrcIO_Name , "CTC.FA_Wafer_Source" );
							}
							else
							{
								sprintf( Wafer_IO_Name , "CTC.FB_Wafer_Status" );
								sprintf( Wafer_SrcIO_Name , "CTC.FB_Wafer_Source" );
							}
							Set_LoadPort_Select_Map();
							//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
							if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
							{
								return SYS_ABORTED;
							}
							if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
							{
								return SYS_ABORTED;
							}
							//_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , PresentSetValue , &CommStatus );	// 以前はこれ
							//_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , Source , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , LoadPort_Select_Number[Source] , &CommStatus );
							_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , Status , &CommStatus );
						}

						//if ( fm ) {
						//	_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , PresentSetValue , &CommStatus );
						//}
						//else {
						//	_dWRITE_DIGITAL( Address_MTLRECV_TM_WIO[tms-1][Finger] , PresentSetValue , &CommStatus );
						//}
					}
					if ( !fm ) {
						if ( Maint_Material_Recovery_MAINT_INTERFACE_RUN( "PLACE_TM%d|%d|BM%d|%c|1|%d" , tms , MTLRECV_RUNMODE , Chamber , Finger + 'A' , j ) == SYS_ABORTED ) return SYS_ABORTED;
					}
					break;
				}
			}
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		for ( j = ss ; j <= es ; j++ ) {
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_BM_WIO( Chamber , j ) ) return SYS_ABORTED;
			if ( !Maint_Material_Recovery_IO_FIND_BM_WSRC( Chamber , j ) ) return SYS_ABORTED;
			//======================================================================================
			sprintf( Wafer_IO_Name , "CTC.BM%d_Wafer_Status" , Chamber );
			sprintf( Wafer_SrcIO_Name , "CTC.BM%d_Wafer_Source" , Chamber );
			Set_LoadPort_Select_Map();
			//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
			if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
			{
				return SYS_ABORTED;
			}
			if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
			{
				return SYS_ABORTED;
			}
			//_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , Source , &CommStatus );
			_dWRITE_DIGITAL( Address_MTLRECV_BM_WSRC[Chamber-1][j-1] , LoadPort_Select_Number[Source] , &CommStatus );
			_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , Status , &CommStatus );
			//_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , PresentSetValue , &CommStatus );	// 以前はこれ
		}

	}
	else {
		for ( j = ss ; j <= es ; j++ ) {
			//======================================================================================
			if ( !Maint_Material_Recovery_IO_FIND_BM_WIO( Chamber , j ) ) return SYS_ABORTED;
			if ( !Maint_Material_Recovery_IO_FIND_BM_WSRC( Chamber , j ) ) return SYS_ABORTED;
			//======================================================================================
			_dWRITE_DIGITAL( Address_MTLRECV_BM_WIO[Chamber-1][j-1] , 0 , &CommStatus );
		}
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_FAL( int Mode , int PresentSetValue ) {
	int CommStatus , GuiWafer , RealWafer , i;
	int Source = 0, Status = 1;
	char Wafer_IO_Name[64], Wafer_SrcIO_Name[64];
	//======================================================================================
	if ( !Maint_Material_Recovery_IO_FIND_FAL_WIO() ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_FAL_WSRC() ) return SYS_ABORTED;
	//======================================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return SYS_SUCCESS;
		//=============================================================================================
		GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_FAL_WIO , &CommStatus );
		//======================================================================================
		if ( !Maint_Material_Recovery_IO_FIND_IO_FALSNS() ) return SYS_ABORTED;
		//======================================================================================

		WRITE_DIGITAL( R1_STATE , 0 , &CommStatus );
		_sleep( 1000 );
		for ( i = 0 ; i < 5 ; i++ ) {
			RealWafer = _dREAD_DIGITAL( Address_MTLRECV_s_I_FAL_SNS , &CommStatus );
			if ( CommStatus ) break;
			_sleep(100);
		}
		if ( i == 5 ) return SYS_ABORTED;
		//======================================================================================
		Maint_Material_Simulation_IO_Check( MTL_PART_FAL , 0 , 0 , 0 , 0 , &RealWafer );
		//======================================================================================
		switch( RealWafer ) {
		case 1   :
			if ( GuiWafer > 0 ) {
				// Clear Wafer
				_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , 0 , &CommStatus );
			}
			break;
		case 2   :
			if ( GuiWafer <= 0 ) {
				// Make Wafer
				sprintf( Wafer_IO_Name , "CTC.FAL_Wafer_Status" );
				sprintf( Wafer_SrcIO_Name , "CTC.FAL_Wafer_Source" );
				Set_LoadPort_Select_Map();
				//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
				if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
				{
					return SYS_ABORTED;
				}
				if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
				{
					return SYS_ABORTED;
				}
				//_dWRITE_DIGITAL( Address_MTLRECV_FAL_WSRC , Source , &CommStatus );
				_dWRITE_DIGITAL( Address_MTLRECV_FAL_WSRC , LoadPort_Select_Number[Source] , &CommStatus );
				_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , Status , &CommStatus );
				//_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , PresentSetValue , &CommStatus );	// 以前はこれ
			}
			break;
		default :
			return SYS_ABORTED;
			break;
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		sprintf( Wafer_IO_Name , "CTC.FAL_Wafer_Status" );
		sprintf( Wafer_SrcIO_Name , "CTC.FAL_Wafer_Source" );
		Set_LoadPort_Select_Map();
		//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
		{
			return SYS_ABORTED;
		}
		if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
		{
			return SYS_ABORTED;
		}
		//_dWRITE_DIGITAL( Address_MTLRECV_FAL_WSRC , Source , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_FAL_WSRC , LoadPort_Select_Number[Source] , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , Status , &CommStatus );
		//_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , PresentSetValue , &CommStatus );	// 以前はこれ
	}
	else {
		_dWRITE_DIGITAL( Address_MTLRECV_FAL_WIO , 0 , &CommStatus );
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Check_FM( int Mode , int Finger , int PresentSetValue , int *Sel ) {
	int CommStatus , GuiWafer , RealWafer , i;
	int Source = 0, Status = 1;
	char Wafer_IO_Name[64], Wafer_SrcIO_Name[64];
	//============================================================================================
	if ( !Maint_Material_Recovery_IO_FIND_FM_WIO( Finger ) ) return SYS_ABORTED;
	if ( !Maint_Material_Recovery_IO_FIND_FM_WSRC( Finger ) ) return SYS_ABORTED;
	//============================================================================================
	if ( Mode == MTL_SUB_REAL_CHECK ) {
		//======================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return SYS_SUCCESS;
		//=============================================================================================
		GuiWafer = _dREAD_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , &CommStatus );
		//======================================================================================
		if ( Finger == 0 ) {
			if ( !Maint_Material_Recovery_IO_FIND_IO_FMASNS() ) return SYS_ABORTED;
		}
		else {
			if ( !Maint_Material_Recovery_IO_FIND_IO_FMBSNS() ) return SYS_ABORTED;
		}
		//======================================================================================
		WRITE_DIGITAL( R1_STATE , 0 , &CommStatus );
		_sleep( 1000 );

		for ( i = 0 ; i < 5 ; i++ ) {
			if ( Finger == 0 ) {
				RealWafer = _dREAD_DIGITAL( Address_MTLRECV_s_I_FMA_SNS , &CommStatus );
			}
			else {
				RealWafer = _dREAD_DIGITAL( Address_MTLRECV_s_I_FMB_SNS , &CommStatus );
			}
			if ( CommStatus ) break;
			_sleep(100);
		}
		if ( i == 5 ) return SYS_ABORTED;
		//============================================================================================
		Maint_Material_Simulation_IO_Check( MTL_PART_FM , 0 , 0 , Finger , 0 , &RealWafer );
		//============================================================================================
		switch( RealWafer ) {
		case 1   :
			if ( GuiWafer > 0 ) {
				// Clear Wafer
				_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , 0 , &CommStatus );
			}
			if ( *Sel < 0 ) *Sel = Finger;
			break;
		case 2   :
			if ( GuiWafer <= 0 ) {
				// Make Wafer
				if ( Finger == 0 )
				{
					sprintf( Wafer_IO_Name , "CTC.FA_Wafer_Status" );
					sprintf( Wafer_SrcIO_Name , "CTC.FA_Wafer_Source" );
				}
				else
				{
					sprintf( Wafer_IO_Name , "CTC.FB_Wafer_Status" );
					sprintf( Wafer_SrcIO_Name , "CTC.FB_Wafer_Source" );
				}
				Set_LoadPort_Select_Map();
				//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
				if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
				{
					return SYS_ABORTED;
				}
				if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
				{
					return SYS_ABORTED;
				}
				//_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , Source , &CommStatus );
				_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , LoadPort_Select_Number[Source] , &CommStatus );
				_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , Status , &CommStatus );
				//_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , PresentSetValue , &CommStatus );	// 以前はこれ
			}
			break;
		default :
			return SYS_ABORTED;
			break;
		}
	}
	else if ( Mode == MTL_SUB_WAFER_SET ) {
		// Make Wafer
		if ( Finger == 0 )
		{
			sprintf( Wafer_IO_Name , "CTC.FA_Wafer_Status" );
			sprintf( Wafer_SrcIO_Name , "CTC.FA_Wafer_Source" );
		}
		else
		{
			sprintf( Wafer_IO_Name , "CTC.FB_Wafer_Status" );
			sprintf( Wafer_SrcIO_Name , "CTC.FB_Wafer_Source" );
		}
		Set_LoadPort_Select_Map();
		//if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , "LP1|LP2|LP3|LP4" , &Source) )
		if( !MODAL_DIGITAL_BOX1(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Source", Wafer_SrcIO_Name , LoadPort_Select_Map , &Source) )
		{
			return SYS_ABORTED;
		}
		if( !MODAL_DIGITAL_BOX2(  GET_MAIN_WINDOW()/* GetTopWindow(NULL)*/, "Select Wafer Number", Wafer_IO_Name , 1 , MTLRECV_CASSETTE_MAX_SLOT , &Status) )
		{
			return SYS_ABORTED;
		}
		//_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , Source , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_FM_WSRC[ Finger ] , LoadPort_Select_Number[Source] , &CommStatus );
		_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , Status , &CommStatus );
		//_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , PresentSetValue , &CommStatus );	// 以前はこれ
	}
	else {
		_dWRITE_DIGITAL( Address_MTLRECV_FM_WIO[ Finger ] , 0 , &CommStatus );
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int Maint_Material_Recovery_Check( int RunPart , int CheckType , int TmSide , int ModuleIndex , int RunArm , int RunSlot , int PresentSetValue , int *Rec_Arm ) {
	int CommStatus;
	
	switch( RunPart ) {
	case MTL_PART_CM :
		return Maint_Material_Recovery_Check_CM( CheckType , ModuleIndex , RunSlot );
		break;

	case MTL_PART_FM :
		return Maint_Material_Recovery_Check_FM( CheckType , RunArm , PresentSetValue , Rec_Arm );
		break;

	case MTL_PART_FAL :
		return Maint_Material_Recovery_Check_FAL( CheckType , PresentSetValue );
		break;

	case MTL_PART_BM :
		if ( CheckType == 0 ) {
			*Rec_Arm = -1;
			if ( TmSide == 0 ) { // fm
				if ( Maint_Material_Recovery_Check_FM( CheckType , RunArm , RunSlot , Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			else {
				if ( Maint_Material_Recovery_Check_TM( CheckType , TmSide , -1 , RunArm , PresentSetValue , Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
			}
			if ( RunArm != *Rec_Arm ) return SYS_ABORTED;
		}
		if ( Maint_Material_Recovery_Check_BM( FALSE , CheckType , TmSide , ModuleIndex , RunArm , RunSlot , PresentSetValue ) == SYS_ABORTED ) return SYS_ABORTED;
		break;

	case MTL_PART_TM :
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↓↓
		// 2014.03.27 suzuki add↓↓
		if ( CheckType == 0 ) {
			// 2014.08.20 参照IO(TM_WFRSNS_CONTROL → TM_CAM_CONTROL)およびメッセ?ジを変更
			if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
				// 2015.01.14 suzuki modify
				// 画面を切り替えても、メッセ?ジウィンドウが一番上に?示されるように変更。
				//if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Camera is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
				if ( IDOK == MessageBox( NULL , "Map Chamber can't execute when Camera is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK | MB_TOPMOST ) ) {
					return SYS_ABORTED;
				}
			}

			/* コメントアウト
			// ウェハセンサ?がオフではMap Chamber実行不可。
			if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
				if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
					return SYS_ABORTED;
				}
			}
			*/
		}
		// 2014.03.27 suzuki add↑↑
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↑↑
		return Maint_Material_Recovery_Check_TM( CheckType , TmSide , ModuleIndex , RunArm , PresentSetValue , Rec_Arm );
		break;

	case MTL_PART_PM :
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↓↓
		// 2014.03.27 suzuki add↓↓
		// オ?ロンカメラ正式対応版はカメラのみ?ェックする。
		if ( CheckType == 0 ) {
			if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
				// 2015.01.14 suzuki modify
				// 画面を切り替えても、メッセ?ジウィンドウが一番上に?示されるように変更。
				//if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Camera is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
				if ( IDOK == MessageBox( NULL , "Map Chamber can't execute when Camera is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK | MB_TOPMOST ) ) {
					return SYS_ABORTED;
				}
			}

			/* 2014.08.20 コメントアウト
			// PM-Fの場合はカメラがオフではMap Chamber実行不可。
			if ( ModuleIndex == 4 ) {
				if ( READ_DIGITAL( TM_CAM_CONTROL , &CommStatus ) == 1 ) {
					if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Camera is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
						return SYS_ABORTED;
					}
				}
			}
			// PM-F以外の場合はZセンサ?がオフではMap Chamber実行不可。
			else {
				if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
					if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
						return SYS_ABORTED;
					}
				}
			}
			*/
		}
		// 2014.03.27 suzuki add↑↑
		// 2014.08.20 オ?ロンカメラ正式対応 ----------------------------------------------↑↑
		if ( CheckType == 0 ) {
			*Rec_Arm = -1;
				
			if ( Maint_Material_Recovery_Check_TM( CheckType , TmSide , ModuleIndex , RunArm , PresentSetValue , Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
			if ( RunArm != *Rec_Arm ) return SYS_ABORTED;
		}
			
		if ( Maint_Material_Recovery_Check_PM( FALSE , CheckType , TmSide , ModuleIndex , RunArm , PresentSetValue ) == SYS_ABORTED ) return SYS_ABORTED;
		break;

	case MTL_PART_BM_F :
		// 2014.03.27 suzuki add↓↓
		if ( CheckType == 0 ) {
			// ウェハセンサ?がオフではMap Chamber実行不可。
			if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
				// 2015.01.14 suzuki modify
				// 画面を切り替えても、メッセ?ジウィンドウが一番上に?示されるように変更。
				//if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
				if ( IDOK == MessageBox( NULL , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK | MB_TOPMOST ) ) {
					return SYS_ABORTED;
				}
			}
		}
		// 2014.03.27 suzuki add↑↑
		if ( Maint_Material_Recovery_Check_BM( TRUE , CheckType , TmSide , ModuleIndex , RunArm , RunSlot , PresentSetValue ) == SYS_ABORTED ) return SYS_ABORTED;
		break;

	case MTL_PART_PM_F :
		// 2014.03.27 suzuki add↓↓
		// ウェハセンサ?がオフではMap Chamber実行不可。
		if ( CheckType == 0 ) {
			if ( READ_DIGITAL( TM_WFRSNS_CONTROL , &CommStatus ) == 1 ) {
				// 2015.01.14 suzuki modify
				// 画面を切り替えても、メッセ?ジウィンドウが一番上に?示されるように変更。
				//if ( IDOK == MessageBox( GET_MAIN_WINDOW() , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK ) ) {
				if ( IDOK == MessageBox( NULL , "Map Chamber can't execute when Wafer Sensor is Off.", "Wafer Present/Absent Confirmation", MB_ICONSTOP | MB_OK | MB_TOPMOST ) ) {
					return SYS_ABORTED;
				}
			}
		}
		// 2014.03.27 suzuki add↑↑
		if ( Maint_Material_Recovery_Check_PM( TRUE , CheckType , TmSide , ModuleIndex , RunArm , PresentSetValue ) == SYS_ABORTED ) return SYS_ABORTED;
		break;

	default :
		return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}


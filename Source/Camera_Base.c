//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : CCD_Base.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"
#include "Fine_Tune.h"
#include "Mtl_Recv_Sub.h"
#include "Sys_Align.h"
#include "Camera_Base.h"
//------------------------------------------------------------------------------------------
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#define		ALARM_PASS1_NO_WAFER	181//281
#define		ALARM_TM1A_HAS_WAFER	182//282
#define		ALARM_TM2A_HAS_WAFER	183//283
#define		ALARM_TM3A_HAS_WAFER	184//284
#define		ALARM_TM1B_HAS_WAFER	185//285
#define		ALARM_TM2B_HAS_WAFER	186//286
#define		ALARM_TM3B_HAS_WAFER	187//287
//=========================================================================================================
int TM_Order[] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
//=========================================================================================================
#ifdef EQ_TYPE_IARIM2A
	// 2015.04.14 PM-G対応
	//------------------------------------------------------------------------------------------
	// IARIM2(SingleLL仕様) : LL1*はBM1，LL2*はBM2とする。TR2側 PM11->PM14
	//------------------------------------------------------------------------------------------
	char Module_Name[16][6] = { "BM1" , "BM2" , "PM1" , "PM2" , "PM3" , "PM4"  , "PM11" , "PM12" ,
									  "PM5" , "PM6" , "PM7" , "PM8" , "PM9" , "PM10" , "PM14" , "PM12"
	};
	//------------------------------------------------------------------------------------------
	// IARIM2(SingleLL仕様) : LL1*はBM1，LL2*はBM2とする。2007.11.10 EHA
	//------------------------------------------------------------------------------------------
	//char Module_Name[16][6] = { "BM1" , "BM2" , "PM1" , "PM2" , "PM3" , "PM4"  , "PM11" , "PM12" ,
	//								  "PM5" , "PM6" , "PM7" , "PM8" , "PM9" , "PM10" , "PM11" , "PM12"
	//};
#else
	//------------------------------------------------------------------------------------------
	// IARIM2(QuadroLL仕様)
	//------------------------------------------------------------------------------------------
	char Module_Name[18/*20*/][6] = { "BM1" , "BM2" , "BM3" , "BM4" , "PM1" , "PM2" , "PM14" ,  "PM11" ,  "PM3" , "PM4" ,
									  "PM14" , "PM5" ,  "PM6" , "PM7" , "PM8" , "PM9" , "PM10", "PM11"
	};
#endif
//=========================================================================================================
//int TM_Order[] = { 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3 };
//char Module_Name[20][6] = { "BM1" , "BM2" , "BM3" , "BM4" , "PM1" , "PM2" , "PM3" , "PM12" , "PM11" , "PM11" ,
//                         "PM14" , "PM4" , "PM5" , "PM6" , "PM12" , "PM7" , "PM8" , "PM9" , "PM10" , "PM14"
//};
//=========================================================================================================
int ALIGN_POST[] = { 0 , 2 , 1 , 5 };
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_CAM_MAINT_INTERFACE_RUN( LPSTR list , ... ) {
	va_list va;
	int CommStatus;
	char Buffer[256];
	char Buffer2[256];
	//
	//
	va_start( va , list );
	vsprintf( Buffer2 , list , (LPSTR) va );
	va_end( va );
	//
	WRITE_DIGITAL( CTC_TR_STATUS , 0 , &CommStatus );
	sprintf( Buffer , "MAINT_INTERFACE %s" , Buffer2 );
	WRITE_STRING( SCHEDULER , Buffer , &CommStatus );
	while ( TRUE ) {
		if ( !WAIT_SECONDS( 0.25 ) ) return SYS_ABORTED;
		switch( READ_DIGITAL( CTC_TR_STATUS , &CommStatus ) ) {
		case SYS_ABORTED : return SYS_ABORTED;
		case SYS_ERROR   : return SYS_ERROR;
		case SYS_SUCCESS : return SYS_SUCCESS;
		}
	}
}
//------------------------------------------------------------------------------------------
Module_Status Maint_CAM_Basis() {
	int i;
	int CommStatus;

	//===================================================================================
	// 注意：基準点測定動作する前にアームが縮位置になっていなかったらホーム動作をすること。2008/08/08 EHA
	//===================================================================================
	if( READ_DIGITAL( TR1_RobotArmShort, &CommStatus ) != 1 ) {
		if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM|1|PM1|%c|1|1" , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
	}
	if( READ_DIGITAL( TR2_RobotArmShort, &CommStatus ) != 1 ) {
		if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM2|1|PM5|%c|1|1" , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
	}
	//===================================================================================

	for ( i = 0; i < 16; i++ )
	{
		if ( READ_DIGITAL( CAM_LL1L_CHECK + i , &CommStatus ) == 1 ) // check is on
		{
			if ( READ_DIGITAL( CAM_BASIS_CONTROL , &CommStatus ) == 2 )
			{
				WRITE_DIGITAL( CAM_BASIS_CONTROL , 3 , &CommStatus );
				while( TRUE )
				{
					if ( !WAIT_SECONDS( 0.5 ) ) return SYS_ABORTED;
					if ( READ_DIGITAL( CAM_BASIS_CONTROL , &CommStatus ) == 1 ) break;
				}
			}

			if ( READ_DIGITAL( CAM_LL1L_CHECK_A + i , &CommStatus ) == 1 ) // arm A is on
			{

				// 2015.04.14 PASSのStationをPM11->PM12に変更
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|PM%d|%c|1|1" , 12 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
				//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|PM%d|%c|1|1" , 11 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
				//

				// 2015.04.14 PASSのStationをPM11->PM12に変更
				// Pass2 Wafer Present Check
				if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 12 , 1 ) )
				// Pass1 Wafer Present Check
				//if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 11 , 1 ) )
				//
				{
					ALARM_POST( ALARM_PASS1_NO_WAFER );
					return SYS_ABORTED;//1;
				}
				// TM Arm A Wafer Absent Check
				if ( !Maint_SysAlign_IO_FIND_TM_WIO( TM_Order[i] , CAM_ARM_A , 0 ) ) 
				{
					ALARM_POST( ALARM_TM1A_HAS_WAFER + TM_Order[i] - 1 );
					return SYS_ABORTED;//2;
				}
				// Align
				// 2015.06.12 "TMC_ALIGNER_CONTROL"->"TMC_ALIGNER2_CONTROL"に変更
				if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN A_AL 1 %d" , ALIGN_POST[TM_Order[i]] ) != SYS_SUCCESS ) return SYS_ABORTED;//3;
				//if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN A_AL 1 %d" , ALIGN_POST[TM_Order[i]] ) != SYS_SUCCESS ) return SYS_ABORTED;//3;

				if      ( TM_Order[i] == 1 )	// TM1
				{
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Pick from Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|PM%d|%c|1|1" , 12 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Pick from Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|PM%d|%c|1|1" , 11 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
					
					// Rotate to Chamber
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					
					// Up to Chamber
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;

					//if ( i <= CCD_LL3L )
					//{
					//	// Place to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					//else
					//{
					//	// Rotate to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//	
					//	// Up to Chamber
					//	//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}

					//2008.10.17 suzuki add
					//カメラがあるときのみカメラの基準値測定を行う
					if ( READ_DIGITAL( LL1L_CAM_EXISTS + i , &CommStatus ) == 1 ) {
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
						// 2014.03.12 suzuki modify↓↓
						// オムロンカメラ正式版では削除する↓↓
						// Camera Capture
						//if ( i == CAM_PMF_CHECK_A - CAM_LL1L_CHECK_A ) {
						//	if ( RUN_FUNCTIONF( TMC_CAMERA_CONTROL , "BASIS_CAPTURE A_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						//}
						//else {
						//	if ( RUN_FUNCTIONF( TMC_CCD_CONTROL , "BASIS_CAPTURE A_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						//}
						// オムロンカメラ正式版では削除する↑↑

						// オムロンカメラ正式版ではコメントアウトをとる↓↓
						//// Camera Capture
						if ( RUN_FUNCTIONF( TMC_CAMERA_CONTROL , "BASIS_CAPTURE A_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版ではコメントアウトをとる↑↑
						// 2014.03.12 suzuki modify↑↑
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
					// 2014.03.12 suzuki modify↓↓
					// オムロンカメラ正式版では削除する↓↓
					//if ( i != CAM_PMF_CHECK - CAM_LL1L_CHECK_A ) {
					//	// Z axis Capture
					//	if ( RUN_FUNCTIONF( TMC_WFRSNS_CONTROL , "BASIS_CAPTURE A_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
					//}
					// オムロンカメラ正式版では削除する↑↑
					// 2014.03.12 suzuki modify↑↑
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//if ( i <= CCD_LL3L )
					//{
					//	// Pick from Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Place to Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|PM%d|%c|1|1" , 12 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Place to Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|PM%d|%c|1|1" , 11 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
				}
				else if ( TM_Order[i] == 2 )	// TM2
				{
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Pick from Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|PM%d|%c|1|1" , 12 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Pick from Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|PM%d|%c|1|1" , 11 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
					
					// Rotate to Chamber
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					
					// Up to Chamber
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;

					//if ( i <= CCD_LL3L )
					//{
					//	// Place to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					//else
					//{
					//	// Rotate to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//	
					//	// Up to Chamber
					//	//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					
					//2008.10.17 suzuki add
					//カメラがあるときのみカメラの基準値測定を行う
					if ( READ_DIGITAL( LL1L_CAM_EXISTS + i , &CommStatus ) == 1 ) {
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
						// 2014.03.12 suzuki modify↓↓
						// Camera Capture
						// オムロンカメラ正式版では削除する↓↓
						//if ( RUN_FUNCTIONF( TMC_CCD_CONTROL , "BASIS_CAPTURE A_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版では削除する↑↑
						// オムロンカメラ正式版ではコメントアウトをとる↓↓
						if ( RUN_FUNCTIONF( TMC_CAMERA2_CONTROL , "BASIS_CAPTURE A_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版ではコメントアウトをとる↑↑
						// 2014.03.12 suzuki modify↑↑
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
					// 2014.03.12 suzuki modify↓↓
					// オムロンカメラ正式版では削除する↓↓
					// Z axis Capture
					//if ( RUN_FUNCTIONF( TMC_WFRSNS_CONTROL , "BASIS_CAPTURE A_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
					// オムロンカメラ正式版では削除する↑↑
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					//if ( i <= CCD_LL3L )
					//{
					//	// Pick from Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|%s|%c|1|1" , Module_Name[i] , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Place to Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|PM%d|%c|1|1" , 12 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Place to Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|PM%d|%c|1|1" , 11 , 'A' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
				}
			}

			if ( READ_DIGITAL( CAM_BASIS_CONTROL , &CommStatus ) == 2 )
			{
				WRITE_DIGITAL( CAM_BASIS_CONTROL , 3 , &CommStatus );
				while( TRUE )
				{
					if ( !WAIT_SECONDS( 0.5 ) ) return SYS_ABORTED;
					if ( READ_DIGITAL( CAM_BASIS_CONTROL , &CommStatus ) == 1 ) break;
				}
			}
			
			if ( READ_DIGITAL( CAM_LL1L_CHECK_B + i , &CommStatus ) == 1 ) // arm B is on
			{
				// 2015.04.14 PASSのStationをPM11->PM12に変更
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|PM%d|%c|1|1" , 12 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
				//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|PM%d|%c|1|1" , 11 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
				//

				// 2015.04.14 PASSのStationをPM11->PM12に変更
				// Pass2 Wafer Present Check
				if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 12 , 1 ) )
				// Pass1 Wafer Present Check
				//if ( !Maint_SysAlign_IO_FIND_PM_WIO2( 11 , 1 ) )
				{
					ALARM_POST( ALARM_PASS1_NO_WAFER );
					return SYS_ABORTED;//1;
				}
				// TM Arm B Wafer Absent Check
				if ( !Maint_SysAlign_IO_FIND_TM_WIO( TM_Order[i] , CAM_ARM_B , 0 ) ) 
				{
					ALARM_POST( ALARM_TM1B_HAS_WAFER + TM_Order[i] - 1 );
					return SYS_ABORTED;//2;
				}
				// Align
				// 2015.06.12 "TMC_ALIGNER_CONTROL"->"TMC_ALIGNER2_CONTROL"に変更
				if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN B_AL 1 %d" , ALIGN_POST[TM_Order[i]] ) != SYS_SUCCESS ) return SYS_ABORTED;//3;
				//if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN B_AL 1 %d" , ALIGN_POST[TM_Order[i]] ) != SYS_SUCCESS ) return SYS_ABORTED;//3;

				if      ( TM_Order[i] == 1 )	// TM1
				{
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Pick from Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|PM%d|%c|1|1" , 12 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Pick from Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|PM%d|%c|1|1" , 11 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
					
					// Rotate to Chamber
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					
					// Up to Chamber
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;

					//if ( i <= CCD_LL3L )
					//{
					//	// Place to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					//else
					//{
					//	// Rotate to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//	
					//	// Up to Chamber
					//	//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}

					//2008.10.17 suzuki add
					//カメラがあるときのみカメラの基準値測定を行う
					if ( READ_DIGITAL( LL1L_CAM_EXISTS + i , &CommStatus ) == 1 ) {
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
						// 2014.03.12 suzuki modify↓↓
						// オムロンカメラ正式版では削除する↓↓
						// Camera Capture
						//if ( i == CAM_PMF_CHECK_B - CAM_LL1L_CHECK_B ) {
						//	if ( RUN_FUNCTIONF( TMC_CAMERA_CONTROL , "BASIS_CAPTURE B_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						//}
						//else {
						//	if ( RUN_FUNCTIONF( TMC_CCD_CONTROL , "BASIS_CAPTURE B_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						//}
						// オムロンカメラ正式版では削除する↑↑

						// オムロンカメラ正式版ではコメントアウトをとる↓↓
						// Camera Capture
						if ( RUN_FUNCTIONF( TMC_CAMERA_CONTROL , "BASIS_CAPTURE B_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版ではコメントアウトをとる↑↑
						// 2014.03.12 suzuki modify↑↑
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
					// 2014.03.12 suzuki modify↓↓
					// オムロンカメラ正式版では削除する↓↓
					// Z axis Capture
					//if ( RUN_FUNCTIONF( TMC_WFRSNS_CONTROL , "BASIS_CAPTURE B_%s TR1 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
					// オムロンカメラ正式版では削除する↑↑
					// 2014.03.12 suzuki modify↑↑
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//if ( i <= CCD_LL3L )
					//{
					//	// Pick from Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Place to Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|PM%d|%c|1|1" , 12 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Place to Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|1|PM%d|%c|1|1" , 11 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
				}
				else if ( TM_Order[i] == 2 )	// TM2
				{
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Pick from Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|PM%d|%c|1|1" , 12 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Pick from Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|PM%d|%c|1|1" , 11 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
					
					// Rotate to Chamber
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					
					// Up to Chamber
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;

					//if ( i <= CCD_LL3L )
					//{
					//	// Place to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					//else
					//{
					//	// Rotate to Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//	
					//	// Up to Chamber
					//	//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "UP_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					
					//2008.10.17 suzuki add
					//カメラがあるときのみカメラの基準値測定を行う
					if ( READ_DIGITAL( LL1L_CAM_EXISTS + i , &CommStatus ) == 1 ) {
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
						// 2014.03.12 suzuki modify↓↓
						// Camera Capture
						// オムロンカメラ正式版では削除する↓↓
						//if ( RUN_FUNCTIONF( TMC_CCD_CONTROL , "BASIS_CAPTURE B_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版では削除する↑↑
						// オムロンカメラ正式版ではコメントアウトをとる↓↓
						if ( RUN_FUNCTIONF( TMC_CAMERA2_CONTROL , "BASIS_CAPTURE B_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
						// オムロンカメラ正式版ではコメントアウトをとる↑↑
						// 2014.03.12 suzuki modify↑↑
						// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↓↓
					// 2014.03.12 suzuki modify↓↓
					// オムロンカメラ正式版では削除する↓↓
					// Z axis Capture
					//if ( RUN_FUNCTIONF( TMC_WFRSNS_CONTROL , "BASIS_CAPTURE B_%s TR2 1" , Module_Name[i] ) != SYS_SUCCESS ) return SYS_ABORTED;//11;
					// オムロンカメラ正式版では削除する↑↑
					// 2014.03.12 suzuki modify↑↑
					// 2014.08.20 オムロンカメラ正式版対応 ----------------------------------------↑↑
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					//if ( i <= CCD_LL3L )
					//{
					//	// Pick from Chamber
					//	if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|1|%s|%c|1|1" , Module_Name[i] , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//}
					// 2015.04.14 PASSのStationをPM11->PM12に変更
					// Place to Pass2
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|PM%d|%c|1|1" , 12 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					// Place to Pass1
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|1|PM%d|%c|1|1" , 11 , 'B' ) == SYS_ABORTED ) return SYS_ABORTED;
					//
				}
			}
		}
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
void Maint_CAM_BASIS_Pause() {
	int CommStatus;

	WRITE_DIGITAL( CAM_BASIS_CONTROL , 2 , &CommStatus );
}

void Maint_CAM_BASIS_Continue() {
	int CommStatus;
	
	WRITE_DIGITAL( CAM_BASIS_CONTROL , 1 , &CommStatus );
}

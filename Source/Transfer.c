//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Transfer.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"

#include "Sys_Align.h"
#include "Fine_Tune.h"
#include "Transfer.h"
//------------------------------------------------------------------------------------------
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------
int TRANSFER_RUNMODE = 1;
//------------------------------------------------------------------------------------------
int TR_Order_Mode[50];
int TR_Order_Slot[50];
int TR_Order_Count;
//
int TR_Find_Count;
int TR_Find_Data;
//------------------------------------------------------------------------------------------
int BTR_Run_Source_Station[50];
int BTR_Run_Source_Slot[50];
//
int BTR_Run_Target_Station[50];
int BTR_Run_Target_Slot[50];
//
int BTR_Run_Count;
//------------------------------------------------------------------------------------------
void Maint_Transfer_SET_RUN_MODE( int data ) {
	TRANSFER_RUNMODE = data;
}
//------------------------------------------------------------------------------------------
void TR_Order_ReSet( int data ) {
	int CommStatus;
	if ( READ_DIGITAL( TR_CM1_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_CM1_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_CM1_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_CM2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_CM2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_CM2_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_CM3_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_CM3_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_CM3_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_CM4_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_CM4_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_CM4_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_FAL_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_FAL_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_FAL_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_BM1_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_BM1_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_BM1_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_BM2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_BM2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_BM2_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_BM3_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_BM3_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_BM3_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_BM4_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_BM4_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_BM4_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM1_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM1_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM1_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM2_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM3_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM3_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM3_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM4_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM4_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM4_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM5_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM5_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM5_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM6_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM6_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM6_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM7_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM7_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM7_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM8_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM8_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM8_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM9_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM9_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM9_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM10_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM10_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM10_ORDER2 , 0 , &CommStatus );
	}
	//
	if ( READ_DIGITAL( TR_PM11_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM11_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM11_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM12_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM12_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM12_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM14_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM14_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM14_ORDER2 , 0 , &CommStatus );
	}
	//
	if ( READ_DIGITAL( TR_PM11_2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM11_2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM11_2_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_PM12_2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_PM12_2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_PM12_2_ORDER2 , 0 , &CommStatus );
	}
	//
	if ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_FM_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_TM1_ORDER2 , 0 , &CommStatus );
	}
	if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) >= data ) {
		WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
		WRITE_DIGITAL( TR_TM2_ORDER2 , 0 , &CommStatus );
	}
}

BOOL TR_Order_Set( int io , int ch , BOOL sch ) {
	int CommStatus;
	if ( READ_DIGITAL( io , &CommStatus ) == TR_Find_Data ) {
		TR_Find_Count++;
		TR_Order_Mode[TR_Order_Count] = ch;
		//
		switch( ch ) {
		case TR_LPMA :
			TR_Order_Slot[TR_Order_Count] = READ_DIGITAL( TR_CM1_SLOT , &CommStatus );
			if ( sch ) {
				if ( TR_Order_Slot[TR_Order_Count] <= 0 ) return FALSE;
			}
			break;
		case TR_LPMB :
			TR_Order_Slot[TR_Order_Count] = READ_DIGITAL( TR_CM2_SLOT , &CommStatus );
			if ( sch ) {
				if ( TR_Order_Slot[TR_Order_Count] <= 0 ) return FALSE;
			}
			break;
		case TR_LPMC :
			TR_Order_Slot[TR_Order_Count] = READ_DIGITAL( TR_CM3_SLOT , &CommStatus );
			if ( sch ) {
				if ( TR_Order_Slot[TR_Order_Count] <= 0 ) return FALSE;
			}
			break;
		case TR_LPMD :
			TR_Order_Slot[TR_Order_Count] = READ_DIGITAL( TR_CM4_SLOT , &CommStatus );
			if ( sch ) {
				if ( TR_Order_Slot[TR_Order_Count] <= 0 ) return FALSE;
			}
			break;
		default :
			TR_Order_Slot[TR_Order_Count] = 1;
			break;
		}
		//
		TR_Order_Count++;
	}
	return TRUE;
}

void TR_Order_Check( int io , int io2 , int lastdata ) {
	int m , CommStatus;
	m = READ_DIGITAL( io , &CommStatus );
	switch ( m ) {
	case 0 :
		WRITE_DIGITAL( io2 , 0 , &CommStatus );
		break;
	case 1 :
		WRITE_DIGITAL( io2 , 1 , &CommStatus );
		break;
	default :
		if ( lastdata <= 1 ) {
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
		}
		else if ( lastdata == m ) {
			WRITE_DIGITAL( io2 , 2 , &CommStatus );
		}
		else {
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
		}
		break;
	}
}

void TR_Order_Select( int io ) {
	int m , CommStatus;
	if ( TR_Find_Data == 0 ) {
		WRITE_DIGITAL( io , 1 , &CommStatus );
		TR_Find_Data++;
	}
	else {
		m = READ_DIGITAL( io , &CommStatus );
		if ( m == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io , 0 , &CommStatus );
		}
		else if ( m == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io , TR_Find_Data , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io , TR_Find_Data , &CommStatus );
			}
		}
	}
}

void TR_Order_Select2( int io1 , int io2 ) {
	int m1 , m2 , CommStatus;
	if ( TR_Find_Data == 0 ) {
		WRITE_DIGITAL( io1 , 1 , &CommStatus );
		WRITE_DIGITAL( io2 , 0 , &CommStatus );
		TR_Find_Data++;
	}
	else {
		m1 = READ_DIGITAL( io1 , &CommStatus );
		m2 = READ_DIGITAL( io2 , &CommStatus );
		if      ( m1 == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io1 , 0 , &CommStatus );
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
		}
		else if ( m2 == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
		}
		else if ( m1 == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io1 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io2 , 0 , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io1 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io2 , 0 , &CommStatus );
			}
		}
		else if ( m2 == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io2 , TR_Find_Data , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					if ( READ_DIGITAL( io1 , &CommStatus ) == TR_Find_Data ) return;
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io2 , TR_Find_Data , &CommStatus );
			}
		}
	}
}
//------------------------------------------------------------------------------------------
void TR_Order_Select3( int io1 , int io2 , int io3 ) {
	int m1 , m2 , m3 , CommStatus;
	if ( TR_Find_Data == 0 ) {
		WRITE_DIGITAL( io1 , 1 , &CommStatus );
		WRITE_DIGITAL( io2 , 0 , &CommStatus );
		WRITE_DIGITAL( io3 , 0 , &CommStatus );
		TR_Find_Data++;
	}
	else {
		m1 = READ_DIGITAL( io1 , &CommStatus );
		m2 = READ_DIGITAL( io2 , &CommStatus );
		m3 = READ_DIGITAL( io3 , &CommStatus );
		if      ( m1 == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io1 , 0 , &CommStatus );
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
			WRITE_DIGITAL( io3 , 0 , &CommStatus );
		}
		else if ( m2 == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io2 , 0 , &CommStatus );
			WRITE_DIGITAL( io3 , 0 , &CommStatus );
		}
		else if ( m3 == TR_Find_Data ) {
			TR_Find_Data--;
			WRITE_DIGITAL( io3 , 0 , &CommStatus );
		}
		else if ( m1 == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io1 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io2 , 0 , &CommStatus );
				WRITE_DIGITAL( io3 , 0 , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io1 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io2 , 0 , &CommStatus );
				WRITE_DIGITAL( io3 , 0 , &CommStatus );
			}
		}
		else if ( m2 == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io2 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io3 , 0 , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					if ( READ_DIGITAL( io1 , &CommStatus ) == TR_Find_Data ) return;
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io2 , TR_Find_Data , &CommStatus );
				WRITE_DIGITAL( io3 , 0 , &CommStatus );
			}
		}
		else if ( m3 == 0 ) {
			if ( TR_Find_Data == 1 ) {
				TR_Find_Data++;
				WRITE_DIGITAL( io3 , TR_Find_Data , &CommStatus );
			}
			else {
				if      ( READ_DIGITAL( TR_FM_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_FM_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM1_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM1_ORDER , 0 , &CommStatus );
				}
				else if ( READ_DIGITAL( TR_TM2_ORDER , &CommStatus ) > 1 ) {
					WRITE_DIGITAL( TR_TM2_ORDER , 0 , &CommStatus );
				}
				else {
					if ( READ_DIGITAL( io2 , &CommStatus ) == TR_Find_Data ) return;
					TR_Find_Data++;
				}
				WRITE_DIGITAL( io3 , TR_Find_Data , &CommStatus );
			}
		}
	}
}
//------------------------------------------------------------------------------------------
BOOL TR_Pick_Arm_Check( int mode , int *runarm ) {
	int a , CommStatus;
	switch( mode ) {
	case 0 :
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return FALSE;
		//
		a = READ_DIGITAL( TR_FM_ARM , &CommStatus );
		if ( a == 0 ) {
			if ( !Maint_SysAlign_IO_FIND_FM_WIO( 0 , 0 ) ) {
				if ( !Maint_SysAlign_IO_FIND_FM_WIO( 1 , 0 ) ) {
					return FALSE;
				}
				else {
					*runarm = 1;
				}
			}
			else {
				*runarm = 0;
			}
		}
		else {
			if ( !Maint_SysAlign_IO_FIND_FM_WIO( a - 1 , 0 ) ) return FALSE;
			*runarm = a - 1;
		}
		break;
	default :
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM( mode ) ) return FALSE;
		//
		a = READ_DIGITAL( TR_FM_ARM + mode , &CommStatus );
		if ( a == 0 ) {
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( mode , 0 , 0 ) ) {
				if ( !Maint_SysAlign_IO_FIND_TM_WIO( mode , 1 , 0 ) ) {
					return FALSE;
				}
				else {
					*runarm = 1;
				}
			}
			else {
				*runarm = 0;
			}
		}
		else {
			if ( !Maint_SysAlign_IO_FIND_TM_WIO( mode , a - 1 , 0 ) ) return FALSE;
			*runarm = a - 1;
		}
		break;
	}
	return TRUE;
}
//------------------------------------------------------------------------------------------
BOOL TR_Place_Arm_Check( int mode , int *runarm ) {
	int a , CommStatus;
	switch( mode ) {
	case 0 :
		if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return FALSE;
		//
		a = READ_DIGITAL( TR_FM_ARM , &CommStatus );
		if ( a == 0 ) {
			if ( Maint_SysAlign_IO_FIND_FM_WIO( 0 , 0 ) ) {
				if ( Maint_SysAlign_IO_FIND_FM_WIO( 1 , 0 ) ) {
					return FALSE;
				}
				else {
					*runarm = 1;
				}
			}
			else {
				*runarm = 0;
			}
		}
		else {
			if ( Maint_SysAlign_IO_FIND_FM_WIO( a - 1 , 0 ) ) return FALSE;
			*runarm = a - 1;
		}
		break;
	default :
		if ( !MODULE_CONTROL_IS_POSSIBLE_TM( mode ) ) return FALSE;
		//
		a = READ_DIGITAL( TR_FM_ARM + mode , &CommStatus );
		if ( a == 0 ) {
			if ( Maint_SysAlign_IO_FIND_TM_WIO( mode , 0 , 0 ) ) {
				if ( Maint_SysAlign_IO_FIND_TM_WIO( mode , 1 , 0 ) ) {
					return FALSE;
				}
				else {
					*runarm = 1;
				}
			}
			else {
				*runarm = 0;
			}
		}
		else {
			if ( Maint_SysAlign_IO_FIND_TM_WIO( mode , a - 1 , 0 ) ) return FALSE;
			*runarm = a - 1;
		}
		break;
	}
	return TRUE;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Move_Check( BOOL sch , BOOL checkskip ) {
	int i , j , runarm , dummy , dummy2;
	//============================================================================	
	// Checking Part 1
	//============================================================================	
	if ( !checkskip ) {
		TR_Order_Count = 0;
		//
		TR_Find_Data = 1;
		//========================================================================
		while ( TRUE ) {
			//
			TR_Find_Count = 0;
			//
			if ( !TR_Order_Set( TR_CM1_ORDER , TR_LPMA , sch ) ) return 1;
			if ( !TR_Order_Set( TR_CM2_ORDER , TR_LPMB , sch ) ) return 1;
			if ( !TR_Order_Set( TR_CM3_ORDER , TR_LPMC , sch ) ) return 1;
			if ( !TR_Order_Set( TR_CM4_ORDER , TR_LPMD , sch ) ) return 1;

			if ( !TR_Order_Set( TR_FAL_ORDER , TR_FAL  , sch ) ) return 1;

#ifdef EQ_TYPE_IARIM2A
			//------------------------------------------------------------------------------------------
			// IARIM2(SingleLL仕様)
			//------------------------------------------------------------------------------------------
			if ( !TR_Order_Set( TR_BM1_ORDER , TR_LLA , sch ) ) return 1;
			if ( !TR_Order_Set( TR_BM2_ORDER , TR_LLB , sch ) ) return 1;
#else
			//------------------------------------------------------------------------------------------
			// IARIM2(QuadroLL仕様)
			//------------------------------------------------------------------------------------------
			if ( !TR_Order_Set( TR_BM1_ORDER , TR_LLA , sch ) ) return 1;
			if ( !TR_Order_Set( TR_BM2_ORDER , TR_LLB , sch ) ) return 1;
			if ( !TR_Order_Set( TR_BM3_ORDER , TR_LLC , sch ) ) return 1;
			if ( !TR_Order_Set( TR_BM4_ORDER , TR_LLD , sch ) ) return 1;
#endif

			if ( !TR_Order_Set( TR_PM1_ORDER  , TR_PM1 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM2_ORDER  , TR_PM2 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM3_ORDER  , TR_PM3 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM4_ORDER  , TR_PM4 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM5_ORDER  , TR_PM5 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM6_ORDER  , TR_PM6 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM7_ORDER  , TR_PM7 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM8_ORDER  , TR_PM8 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM9_ORDER  , TR_PM9 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM10_ORDER , TR_PM10 , sch ) ) return 1;

			if ( !TR_Order_Set( TR_PM11_ORDER , TR_PM11 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM12_ORDER , TR_PM12 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM14_ORDER , TR_PM14 , sch ) ) return 1;
			//
			if ( !TR_Order_Set( TR_PM11_2_ORDER , TR_PM11 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_PM12_2_ORDER , TR_PM12 , sch ) ) return 1;
			//
			//
			if ( !TR_Order_Set( TR_FM_ORDER , TR_FM , sch ) ) return 1;
			if ( !TR_Order_Set( TR_TM1_ORDER , TR_TM1 , sch ) ) return 1;
			if ( !TR_Order_Set( TR_TM2_ORDER , TR_TM2 , sch ) ) return 1;
			//
			if ( TR_Find_Count == 0 ) break;
			if ( TR_Find_Count != 1 ) return 2;
			//
			TR_Find_Data++;
		}
		//========================================================================
		if ( TR_Order_Count <= 0 ) return 3;
		if ( TR_Order_Count <= 1 ) return 4;
	}
	//============================================================================	
	// Checking Part 2
	//============================================================================	
	for ( i = 0 ; i < TR_Order_Count ; i++ ) {
		//====================================================
		if ( i == ( TR_Order_Count - 1 ) ) {
			switch( TR_Order_Mode[i] ) {
			case TR_FM :
			case TR_TM1 :
			case TR_TM2 :
				break;
			default :
				continue;
				break;
			}
		}
		//====================================================
		switch( TR_Order_Mode[i] ) {
		//====================================================
		case TR_FM :
			if ( ( i != 0 ) && ( i != ( TR_Order_Count - 1 ) ) ) {
//				return 11; // 2006.10.24
				if ( sch ) return 11; // 2006.10.24
			}
			if ( i == 0 ) {
				if ( TR_Order_Count > 1 ) { // 2006.10.24
					switch( TR_Order_Mode[i+1] ) {
					case TR_FM :
					case TR_TM1 :
					case TR_TM2 :
						return 12;
						break;
					case TR_LPMA :
					case TR_LPMB :
					case TR_LPMC :
					case TR_LPMD :
						break;
					case TR_FAL :
						break;
					case TR_LLA :
					case TR_LLB :
					case TR_LLC :
					case TR_LLD :
						break;
					case TR_PM1 :
					case TR_PM2 :
					case TR_PM3 :
					case TR_PM4 :
					case TR_PM5 :
					case TR_PM6 :
					case TR_PM7 :
					case TR_PM8 :
					case TR_PM9 :
					case TR_PM10 :
					case TR_PM11 :
					case TR_PM12 :
					case TR_PM14 :
						return 12;
						break;
					}
				}
			}
			else {
				switch( TR_Order_Mode[i-1] ) {
				case TR_FM :
				case TR_TM1 :
				case TR_TM2 :
//					return 13; // 2006.10.24
					if ( sch ) return 13; // 2006.10.24
					break;
				case TR_LPMA :
				case TR_LPMB :
				case TR_LPMC :
				case TR_LPMD :
					break;
				case TR_FAL :
					break;
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					break;
				case TR_PM1 :
				case TR_PM2 :
				case TR_PM3 :
				case TR_PM4 :
				case TR_PM5 :
				case TR_PM6 :
				case TR_PM7 :
				case TR_PM8 :
				case TR_PM9 :
				case TR_PM10 :
				case TR_PM11 :
				case TR_PM12 :
				case TR_PM14 :
					return 13;
					break;
				}
			}
			break;
		//====================================================
		case TR_TM1 :
			if ( ( i != 0 ) && ( i != ( TR_Order_Count - 1 ) ) ) {
//				return 21; // 2006.10.24
				if ( sch ) return 21; // 2006.10.24
			}
			if ( i == 0 ) {
				if ( TR_Order_Count > 1 ) { // 2006.10.24
					switch( TR_Order_Mode[i+1] ) {
					case TR_FM :
					case TR_TM1 :
					case TR_TM2 :
	//					return 22; // 2006.10.24
						if ( sch ) return 22; // 2006.10.24
						break;
					case TR_LPMA :
					case TR_LPMB :
					case TR_LPMC :
					case TR_LPMD :
						return 22;
						break;
					case TR_FAL :
						return 22;
						break;
					case TR_LLA :
					case TR_LLB :
					case TR_LLC :
					case TR_LLD :
						break;
					case TR_PM1 :
					case TR_PM2 :
					case TR_PM3 :
					case TR_PM4 :
						break;
					case TR_PM5 :
					case TR_PM6 :
					case TR_PM7 :
					case TR_PM8 :
					case TR_PM9 :
					case TR_PM14 :
					case TR_PM10 :
						return 22;
						break;
					case TR_PM11 :
					case TR_PM12 :
						break;
					}
				}
			}
			else {
				switch( TR_Order_Mode[i-1] ) {
				case TR_FM :
				case TR_TM1 :
				case TR_TM2 :
//					return 23; // 2006.10.24
					if ( sch ) return 23; // 2006.10.24
					break;
				case TR_LPMA :
				case TR_LPMB :
				case TR_LPMC :
				case TR_LPMD :
					return 23;
					break;
				case TR_FAL :
					return 23;
					break;
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					break;
				case TR_PM1 :
				case TR_PM2 :
				case TR_PM3 :
				case TR_PM4 :
					break;
				case TR_PM5 :
				case TR_PM6 :
				case TR_PM7 :
				case TR_PM8 :
				case TR_PM9 :
				case TR_PM10 :
				case TR_PM14 :
					return 23;
					break;
				case TR_PM11 :
				case TR_PM12 :
					break;
				}
			}
			break;
		//====================================================
		case TR_TM2 :
			if ( ( i != 0 ) && ( i != ( TR_Order_Count - 1 ) ) ) {
//				return 31; // 2006.10.24
				if ( sch ) return 31; // 2006.10.24
			}
			if ( i == 0 ) {
				if ( TR_Order_Count > 1 ) { // 2006.10.24
					switch( TR_Order_Mode[i+1] ) {
					case TR_FM :
					case TR_TM1 :
					case TR_TM2 :
	//					return 32; // 2006.10.24
						if ( sch ) return 32; // 2006.10.24
						break;
					case TR_LPMA :
					case TR_LPMB :
					case TR_LPMC :
					case TR_LPMD :
						return 32;
						break;
					case TR_FAL :
						return 32;
						break;
					case TR_LLA :
					case TR_LLB :
					case TR_LLC :
					case TR_LLD :
						return 32;
						break;
					case TR_PM1 :
					case TR_PM2 :
					case TR_PM3 :
					case TR_PM4 :
						return 32;
						break;
					case TR_PM5 :
					case TR_PM6 :
					case TR_PM7 :
					case TR_PM8 :
					case TR_PM9 :
					case TR_PM10 :
					case TR_PM14 :
						break;
					case TR_PM11 :
					case TR_PM12 :
						break;
					}
				}
			}
			else {
				switch( TR_Order_Mode[i-1] ) {
				case TR_FM :
				case TR_TM1 :
				case TR_TM2 :
//					return 33; // 2006.10.24
					if ( sch ) return 33; // 2006.10.24
					break;
				case TR_LPMA :
				case TR_LPMB :
				case TR_LPMC :
				case TR_LPMD :
					return 33;
					break;
				case TR_FAL :
					return 33;
					break;
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					return 33;
					break;
				case TR_PM1 :
				case TR_PM2 :
				case TR_PM3 :
				case TR_PM4 :
					return 33;
					break;
				case TR_PM5 :
				case TR_PM6 :
				case TR_PM7 :
				case TR_PM8 :
				case TR_PM9 :
				case TR_PM10 :
				case TR_PM14 :
					break;
				case TR_PM11 :
				case TR_PM12 :
					break;
				}
			}
			break;
		//====================================================
		//====================================================
		case TR_LPMA :
		case TR_LPMB :
		case TR_LPMC :
		case TR_LPMD :
			//
			if ( sch ) {
				if ( TR_Order_Slot[i] <=  0 ) return 51;
				if ( TR_Order_Slot[i] >= 30 ) return 51;
			}
			//
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				break;
			case TR_TM1 :
			case TR_TM2 :
				return 52;
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				break;
			case TR_FAL :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM12 :
			case TR_PM14 :
				return 52;
				break;
			}
			break;
		//====================================================
		case TR_FAL :
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				break;
			case TR_TM1 :
			case TR_TM2 :
				return 62;
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				break;
			case TR_FAL :
				return 62;
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM12 :
			case TR_PM13 :
			case TR_PM14 :
			case TR_PM15 :
				return 62;
				break;
			}
			break;
		//====================================================
		case TR_LLA :
		case TR_LLB :
		case TR_LLC :
		case TR_LLD :
			//
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				break;
			case TR_TM1 :
				break;
			case TR_TM2 :
				return 72;
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				break;
			case TR_FAL :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				return 72;
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			break;
		//====================================================
		case TR_PM1 :
		case TR_PM2 :
		case TR_PM3 :
		case TR_PM4 :
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 92;
				break;
			case TR_TM1 :
				break;
			case TR_TM2 :
				return 92;
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				return 92;
				break;
			case TR_FAL :
				return 92;
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				return 92;
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			break;
		//====================================================
		case TR_PM5 :
		case TR_PM6 :
		case TR_PM7 :
		case TR_PM8 :
		case TR_PM9 :
		case TR_PM10 :
		case TR_PM14 :
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 102;
				break;
			case TR_TM1 :
				return 102;
				break;
			case TR_TM2 :
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				return 102;
				break;
			case TR_FAL :
				return 102;
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				return 102;
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				return 102;
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
//				return 102;
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			break;
		//====================================================
		case TR_PM11 :
			//-----------------
			if ( TR_Order_Mode[i] == TR_Order_Mode[i+1] ) return 121;
			//-----------------
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 122;
				break;
			case TR_TM1 :
				break;
			case TR_TM2 :
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				return 122;
				break;
			case TR_FAL :
				return 122;
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM12 :
			case TR_PM14 :
				break;
			}
			break;
		//====================================================
		case TR_PM12 :
			//-----------------
			if ( TR_Order_Mode[i] == TR_Order_Mode[i+1] ) return 131;
			//-----------------
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 132;
				break;
			case TR_TM1 :
				break;
			case TR_TM2 :
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				return 132;
				break;
			case TR_FAL :
				return 132;
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM12 :
			case TR_PM14 :
				break;
			}
			break;
		//====================================================
		}
		//====================================================
	}
	//============================================================================	
	// Checking Part 3
	//============================================================================	
	for ( i = 0 ; i < TR_Order_Count ; i++ ) {
		//====================================================
		switch( TR_Order_Mode[i] ) {
		//====================================================
		case TR_FM :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 0 , &runarm ) ) return 1012;
			}
			else {
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 1011;
			}
			break;
		case TR_TM1 :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 1 , &runarm ) ) return 1022;
			}
			else {
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1021;
			}
			break;
		case TR_TM2 :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 2 , &runarm ) ) return 1032;
			}
			else {
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 1031;
			}
			break;
		//====================================================
		case TR_LPMA :
		case TR_LPMB :
		case TR_LPMC :
		case TR_LPMD :
			//===================================================================================
			if ( i == 0 ) { // 2006.10.24
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 1051;
			}
			//===================================================================================
			if ( sch ) {
				if ( i == 0 ) {
					if ( !Maint_SysAlign_IO_FIND_CM_WIO( TR_Order_Mode[i] - TR_LPMA + 1 , TR_Order_Slot[i] , 2 ) ) return 1052;
				}
				else {
					if ( !Maint_SysAlign_IO_FIND_CM_WIO( TR_Order_Mode[i] - TR_LPMA + 1 , TR_Order_Slot[i] , 1 ) ) return 1052;
				}
			}
			//===================================================================================
			break;
		//====================================================
		case TR_FAL :
			//===================================================================================
			if ( i == 0 ) { // 2006.10.24
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 1061;
			}
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) {
				if ( i == 0 ) return 1062;
			}
			else {
				if ( i != 0 ) return 1063;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_LLA :
		case TR_LLB :
		case TR_LLC :
		case TR_LLD :
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_BM_WIO( TR_Order_Mode[i] - TR_LLA + 1 , TR_Order_Slot[i] , 0 , &dummy , &dummy2 ) ) {
				if ( i == 0 ) return 1072;
			}
			else {
				if ( i != 0 ) return 1073;
			}
			//===================================================================================
			if ( i == 0 ) j = 1;
			else          j = -1;
			//===================================================================================
			switch( TR_Order_Mode[i+j] ) {
			case TR_FM :
			case TR_TM1 :
			case TR_TM2 :
				break;
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
			case TR_FAL :
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 1071;
				break;
			default :
				switch( TR_Order_Mode[i] ) {
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1071;
					break;
				}
			}
			break;
		//====================================================
		case TR_PM1 :
		case TR_PM2 :
		case TR_PM3 :
		case TR_PM4 :
			//===================================================================================
			if ( i == 0 ) {
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1091;
			}
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) {
				if ( i == 0 ) return 1092;
			}
			else {
				if ( i != 0 ) return 1093;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_PM5 :
		case TR_PM6 :
		case TR_PM7 :
		case TR_PM8 :
		case TR_PM9 :
		case TR_PM10 :
		case TR_PM14 :
			//===================================================================================
			if ( i == 0 ) {
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 1101;
			}
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) {
				if ( i == 0 ) return 1102;
			}
			else {
				if ( i != 0 ) return 1103;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_PM11 :
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) {
				if ( i == 0 ) return 1122;
			}
			else {
				if ( i != 0 ) return 1123;
			}
			//===================================================================================
			if ( i == 0 ) j = 1;
			else          j = -1;
			//===================================================================================
			switch( TR_Order_Mode[i+j] ) {
			case TR_FM :
			case TR_TM1 :
			case TR_TM2 :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1121;
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1121;
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 1121;
				break;
			}
			break;
		//====================================================
		case TR_PM12 :
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) {
				if ( i == 0 ) return 1132;
			}
			else {
				if ( i != 0 ) return 1133;
			}
			//===================================================================================
			if ( i == 0 ) j = 1;
			else          j = -1;
			//===================================================================================
			switch( TR_Order_Mode[i+j] ) {
			case TR_FM :
			case TR_TM1 :
			case TR_TM2 :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1131;
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 1131;
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 1131;
				break;
			}
			break;
		//====================================================
		}
		//====================================================
	}
	return 0;
}

//=============================================================================================
int Maint_Transfer_Tag_Chking() {
	int CommStatus;
	while( TRUE ) {
		if ( MANAGER_ABORT() ) return SYS_ABORTED;
		switch( READ_DIGITAL( MTR_CONTROL , &CommStatus ) ) {
		case CTL_IDLE :
		case CTL_WAITING :
		case CTL_WAIT_HANDOFF :
			WRITE_DIGITAL( MTR_CONTROL , CTL_RUNNING , &CommStatus );
			return SYS_SUCCESS;
			break;
		case CTL_RUNNING :
			return SYS_SUCCESS;
			break;
		case CTL_PAUSING :
			WRITE_DIGITAL( MTR_CONTROL , CTL_PAUSED , &CommStatus );
			break;
		case CTL_PAUSED :
			_sleep( 100 );
			break;
		case CTL_ABORTING :
		case CTL_DISABLE :
			return SYS_ABORTED;
			break;
		}
	}
	return SYS_ABORTED;
}
//=============================================================================================

int Maint_Transfer_Move_Sub( BOOL batchtr , int *pos ) {
	int i , runarm;
	int align_pass , dummy , dummy2;

	*pos = -99;

	// Error
	// 0 : OK
	// 1 : Tag Error
	// 2 : Data Error
	// 3 : Robot Wafer Invalid
	// 4 : Pick Wafer Invalid
	// 5 : Place Wafer Invalid
	// 6 : Robot Wafer Invalid 2
	// 7 : Pick Wafer Invalid 2
	// 8 : Place Wafer Invalid 2
	// 9 : Running with Aborted

	//============================================================================	
	// Check Part
	//============================================================================	
	if ( !batchtr ) {
		i = Maint_Transfer_Move_Check( TRUE , FALSE );
		if      ( i == 0 ) {
		}
		else if ( ( i > 0 ) && ( i < 1000 ) ) {
			return 2;
		}
		else {
			if      ( ( i % 3 ) == 0 ) {
				return 3;
			}
			else if ( ( i % 3 ) == 1 ) {
				return 4;
			}
			else if ( ( i % 3 ) == 2 ) {
				return 5;
			}
			else {
				return 2;
			}
		}
	}
	//============================================================================	
	*pos = -1;
	//============================================================================	
	align_pass = READ_DIGITAL( TR_ALIGNING , &i );
	//============================================================================	
	// Running Part
	//============================================================================	
	for ( i = 0 ; i < ( TR_Order_Count - 1 ) ; i++ ) {

		*pos = i;

		//====================================================
		if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9;
		//====================================================

		//====================================================
		// Pick Part
		//====================================================
		switch( TR_Order_Mode[i] ) {
		//====================================================
		case TR_FM :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 0 , &runarm ) ) return 6;
			}
			else {
				return 6;
			}
			break;
		case TR_TM1 :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 1 , &runarm ) ) return 6;
			}
			else {
				return 6;
			}
			break;
		case TR_TM2 :
			if ( i == 0 ) {
				if ( !TR_Place_Arm_Check( 2 , &runarm ) ) return 6;
			}
			else {
				return 6;
			}
			break;
		//====================================================
		case TR_LPMA :
		case TR_LPMB :
		case TR_LPMC :
		case TR_LPMD :
			//===================================================================================
			if ( !Maint_SysAlign_IO_FIND_CM_WIO( TR_Order_Mode[i] - TR_LPMA + 1 , TR_Order_Slot[i] , 2 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_CM( TR_Order_Mode[i] - TR_LPMA + 1 ) ) return 7;
			//===================================================================================

			if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 6;
			//
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|CM%d|%d|0" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LPMA + 1 , TR_Order_Slot[i] ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|CM%d|0|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LPMA + 1 , TR_Order_Slot[i] ) == SYS_ABORTED ) return 9;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_FAL :
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return 7;
			//===================================================================================
			if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 6;
			//
#ifdef EQ_TYPE_IARIM2A
			//------------------------------------------------------------------------------------------
			// IARIM2(SingleLL仕様)
			//------------------------------------------------------------------------------------------
			if ( runarm == TR_ARM_A ) {
				if ( ( TR_Order_Mode[i+1] >= TR_LLA ) && ( TR_Order_Mode[i+1] <= TR_LLB ) ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
			}
			else {
				if ( ( TR_Order_Mode[i+1] >= TR_LLA ) && ( TR_Order_Mode[i+1] <= TR_LLB ) ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
			}
#else
			//------------------------------------------------------------------------------------------
			// IARIM2(QuadroLL仕様)
			//------------------------------------------------------------------------------------------
			if ( runarm == TR_ARM_A ) {
				if ( ( TR_Order_Mode[i+1] >= TR_LLA ) && ( TR_Order_Mode[i+1] <= TR_LLD ) ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
			}
			else {
				if ( ( TR_Order_Mode[i+1] >= TR_LLA ) && ( TR_Order_Mode[i+1] <= TR_LLD ) ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
			}
#endif
			//===================================================================================
			break;
		//====================================================
		case TR_LLA :
		case TR_LLB :
		case TR_LLC :
		case TR_LLD :
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_BM_WIO( TR_Order_Mode[i] - TR_LLA + 1 , TR_Order_Slot[i] , 0 , &dummy , &dummy2 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_BM( TR_Order_Mode[i] - TR_LLA + 1 ) ) return 7;
			//===================================================================================
			//
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				//
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
			case TR_FAL :
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 6;
				//
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				if ( runarm == TR_ARM_A ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|%d|0" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LLA + 1 , TR_Order_Slot[i] ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|0|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LLA + 1 , TR_Order_Slot[i] ) == SYS_ABORTED ) return 9;
				}
				break;
			default :
				switch( TR_Order_Mode[i] ) {
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
					//
//					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LLA + 1 ) == SYS_ABORTED ) return 9; // 2006.10.25
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , RUNMODE_TMSIDE_WHEN_BM_PICK , TR_Order_Mode[i] - TR_LLA + 1 ) == SYS_ABORTED ) return 9; // 2006.10.25
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|BM%d|%c|1|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_LLA + 1 , runarm + 'A' , TR_Order_Slot[i] ) == SYS_ABORTED ) return 9;
					break;
				}
			}
			break;
		//====================================================
		case TR_PM1 :
		case TR_PM2 :
		case TR_PM3 :
		case TR_PM4 :
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i] - TR_PM1 + 1 ) ) return 7;
			//===================================================================================
			if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
			//
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
			break;
		//====================================================
		case TR_PM5 :
		case TR_PM6 :
		case TR_PM7 :
		case TR_PM8 :
		case TR_PM9 :
		case TR_PM10 :
		case TR_PM14 :
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i] - TR_PM1 + 1 ) ) return 7;
			//===================================================================================
			if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 6;
			//
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
			break;
		//====================================================
		case TR_PM11 :
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i] - TR_PM1 + 1 ) ) return 7;
			//===================================================================================
			//
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 6;
				break;

			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( Maint_Transfer_Aligning( 1 , runarm , 12 , align_pass ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM1 :
				//
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( TR_Order_Mode[i+1] == TR_TM1 ) {
					if ( Maint_Transfer_Aligning( 1 , runarm , 0 , align_pass ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_Transfer_Aligning( 1 , runarm , TR_Order_Mode[i+1] - TR_PM1 + 1 , align_pass ) == SYS_ABORTED ) return 9;
				}
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				//=========================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM2 :
				//
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM12 :
			case TR_PM14 :
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( TR_Order_Mode[i+1] == TR_TM2 ) {
					if ( Maint_Transfer_Aligning( 2 , runarm , 0 , align_pass ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_Transfer_Aligning( 2 , runarm , TR_Order_Mode[i+1] - TR_PM1 + 1 , align_pass ) == SYS_ABORTED ) return 9;
				}
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				//=========================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			}
			break;
		case TR_PM12 :
			if ( Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i] - TR_PM1 + 1 , 0 ) ) return 7;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i] - TR_PM1 + 1 ) ) return 7;
			//===================================================================================
			//
			switch( TR_Order_Mode[i+1] ) {
			case TR_FM :
				return 6;
				break;

			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( Maint_Transfer_Aligning2( 1 , runarm , 12 , align_pass ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM1 :
				//
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( TR_Order_Mode[i+1] == TR_TM1 ) {
					if ( Maint_Transfer_Aligning2( 1 , runarm , 0 , align_pass ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_Transfer_Aligning2( 1 , runarm , TR_Order_Mode[i+1] - TR_PM1 + 1 , align_pass ) == SYS_ABORTED ) return 9;
				}
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				//=========================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM2 :
				//
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM14 :
				if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 6;
				//=========================================================================================
				// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				//=========================================================================================
				if ( TR_Order_Mode[i+1] == TR_TM2 ) {
					if ( Maint_Transfer_Aligning2( 2 , runarm , 0 , align_pass ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_Transfer_Aligning2( 2 , runarm , TR_Order_Mode[i+1] - TR_PM1 + 1 , align_pass ) == SYS_ABORTED ) return 9;
				}
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				//=========================================================================================
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			}
			break;
		//====================================================
		}

		//====================================================
		if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9;
		//====================================================

		//====================================================
		// Place Part
		//====================================================
		switch( TR_Order_Mode[i+1] ) {
		//====================================================
		case TR_FM :
		case TR_TM1 :
		case TR_TM2 :
			if ( ( i + 1 ) != ( TR_Order_Count - 1 ) ) {
				return 6;
			}
			break;
		//====================================================
		case TR_LPMA :
		case TR_LPMB :
		case TR_LPMC :
		case TR_LPMD :
			//===================================================================================
			if ( !Maint_SysAlign_IO_FIND_CM_WIO( TR_Order_Mode[i+1] - TR_LPMA + 1 , TR_Order_Slot[i+1] , 1 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_CM( TR_Order_Mode[i+1] - TR_LPMA + 1 ) ) return 8;
			if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return 6;
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_FM_WIO( runarm , 0 ) ) return 6;
			// 一つ前が大気アライナでない場合
			if ( TR_Order_Mode[i] != TR_FAL ) {
				//===================================================================================
				if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return 7;
				if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return 7;
				//===================================================================================
				// LPにPlaceする前は、大気アライナを通す。
				if ( runarm == TR_ARM_A ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|%d|0" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|0|%d" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
				}

				if ( runarm == TR_ARM_A ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
				}
			}
			//
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|%d|0" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LPMA + 1 , TR_Order_Slot[i+1] ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|0|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LPMA + 1 , TR_Order_Slot[i+1] ) == SYS_ABORTED ) return 9;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_FAL :
			//===================================================================================
			if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return 8;
			if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return 6;
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_FM_WIO( runarm , 0 ) ) return 6;
			//
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|%d|0" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|0|%d" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
			}
			//===================================================================================
			break;
		//====================================================
		case TR_LLA :
		case TR_LLB :
		case TR_LLC :
		case TR_LLD :
			//===================================================================================
			if ( !Maint_SysAlign_IO_FIND_BM_WIO( TR_Order_Mode[i+1] - TR_LLA + 1 , TR_Order_Slot[i+1] , 0 , &dummy , &dummy2 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_BM( TR_Order_Mode[i+1] - TR_LLA + 1 ) ) return 8;
			//===================================================================================
			//
			switch( TR_Order_Mode[i] ) {
			case TR_FM :
				//
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
			case TR_FAL :
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return 6;
				if ( Maint_SysAlign_IO_FIND_FM_WIO( runarm , 0 ) ) return 6;
				// 一つ前が大気アライナでない場合
				if ( TR_Order_Mode[i] != TR_FAL ) {
					//===================================================================================
					if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return 7;
					if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return 7;
					//===================================================================================
					// LLにPlaceする前は、大気アライナを通す。
					if ( runarm == TR_ARM_A ) {
						if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|%d|0" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
					}
					else {
						if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|0|%d" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
					}

					if ( runarm == TR_ARM_A ) {
						if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
					}
					else {
						if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
					}
				}
				//
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
				//========================================================================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
				//========================================================================================================
				if ( runarm == TR_ARM_A ) {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|%d|0" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 , TR_Order_Slot[i+1] ) == SYS_ABORTED ) return 9;
				}
				else {
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|BM%d|0|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 , TR_Order_Slot[i+1] ) == SYS_ABORTED ) return 9;
				}
				break;
			default :
				switch( TR_Order_Mode[i+1] ) {
				case TR_LLA :
				case TR_LLB :
				case TR_LLC :
				case TR_LLD :
					if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return 6;
					if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) return 6;
					//
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 ) == SYS_ABORTED ) return 9;
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|BM%d|%c|1|%d" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_LLA + 1 , runarm + 'A' , TR_Order_Slot[i+1] ) == SYS_ABORTED ) return 9;
					break;
				}
			}
			break;
		//====================================================
		case TR_PM1 :
		case TR_PM2 :
		case TR_PM3 :
		case TR_PM4 :
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i+1] - TR_PM1 + 1 , 0 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i+1] - TR_PM1 + 1 ) ) return 8;
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return 6;
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) return 6;
			//
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
			break;
		//====================================================
		case TR_PM5 :
		case TR_PM6 :
		case TR_PM7 :
		case TR_PM8 :
		case TR_PM9 :
		case TR_PM10 :
		case TR_PM14 :
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i+1] - TR_PM1 + 1 , 0 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i+1] - TR_PM1 + 1 ) ) return 8;
			if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return 6;
			//===================================================================================
			if ( Maint_SysAlign_IO_FIND_TM_WIO( 2 , runarm , 0 ) ) return 6;
			//
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
			break;
		//====================================================
		case TR_PM11 :
		case TR_PM12 :
			if ( !Maint_SysAlign_IO_FIND_PM_WIO( TR_Order_Mode[i+1] - TR_PM1 + 1 , 0 ) ) return 8;
			//===================================================================================
			if ( !MODULE_CONTROL_IS_POSSIBLE_PM( TR_Order_Mode[i+1] - TR_PM1 + 1 ) ) return 8;
			//===================================================================================
			//
			switch( TR_Order_Mode[i] ) {
			case TR_FM :
				return 6;
				break;

			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return 6;
				if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) return 6;
				//
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM1 :
				//
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return 6;
				if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) return 6;
				//
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			case TR_TM2 :
				//
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM11 :
			case TR_PM12 :
			case TR_PM14 :
				if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return 6;
				if ( Maint_SysAlign_IO_FIND_TM_WIO( 2 , runarm , 0 ) ) return 6;
				//
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , TR_Order_Mode[i+1] - TR_PM1 + 1 , runarm + 'A' ) == SYS_ABORTED ) return 9;
				break;
			}
			break;
		//====================================================
		}
		//====================================================
	}
	return 0;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Clear_src_buffer[100];
int Maint_Transfer_Clear_wfr_buffer[100];
int Maint_Transfer_Clear_sw_bf_cnt;
//------------------------------------------------------------------------------------------
BOOL Maint_Transfer_Clear_Append( int src , int wfr ) {
	int i;
	for ( i = 0 ; i < Maint_Transfer_Clear_sw_bf_cnt ; i++ ) {
		if ( ( Maint_Transfer_Clear_src_buffer[i] == src ) && ( Maint_Transfer_Clear_wfr_buffer[i] == wfr ) ) return FALSE;
	}
	if ( Maint_Transfer_Clear_sw_bf_cnt >= 100 ) return FALSE;
	Maint_Transfer_Clear_src_buffer[Maint_Transfer_Clear_sw_bf_cnt] = src;
	Maint_Transfer_Clear_wfr_buffer[Maint_Transfer_Clear_sw_bf_cnt] = wfr;
	Maint_Transfer_Clear_sw_bf_cnt++;
	return TRUE;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
BOOL Maint_Transfer_Clear_Pre_Check_Error() { // 2007.12.12
	int i , src , wfr;
	//
	Maint_Transfer_Clear_sw_bf_cnt = 0;
	//===================================================================================
	// FM Wafer
	//===================================================================================
	for ( i = 0 ; i < 2 ; i++ ) {
		//========================================================================================================
		if ( Maint_SysAlign_IO_FIND_FM_WIO( i , 0 ) ) continue;
		//========================================================================================================
		if ( !Maint_SysAlign_IO_FIND_FM_WDATA( i , &src , &wfr ) ) continue;
		//========================================================================================================
		// src , wfr
		//========================================================================================================
		if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
		//========================================================================================================
		if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
		//========================================================================================================
	}
	//===================================================================================
	// FAL Wafer
	//===================================================================================
	if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &src , &wfr ) ) {
		if ( MODULE_CONTROL_IS_POSSIBLE_FAL() ) {
			//========================================================================================================
			// src , wfr
			//========================================================================================================
			if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
			//========================================================================================================
			if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
			//========================================================================================================
		}
	}
	//===================================================================================
	// BM Wafer
	//===================================================================================
	for ( i = 1 ; i <= 4 ; i++ ) { // 2006.10.24
		//===================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
		//===================================================================================
		if ( Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &src , &wfr ) ) continue;
		//===================================================================================
		// src , wfr
		//========================================================================================================
		if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
		//========================================================================================================
		if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
		//========================================================================================================
	}
	//===================================================================================
	// TM Wafer
	//===================================================================================
	for ( i = 0 ; i < 2 ; i++ ) {
		//===================================================================================
		if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , i , 0 ) ) continue;
		//===================================================================================
		if ( !Maint_SysAlign_IO_FIND_TM_WDATA( 1 , i , &src , &wfr ) ) continue;
		//===================================================================================
		// src , wfr
		if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
		//========================================================================================================
		//========================================================================================================
		if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
		//========================================================================================================
		//===================================================================================
		if ( Maint_SysAlign_IO_FIND_TM_WIO( 2 , i , 0 ) ) continue;
		//===================================================================================
		if ( !Maint_SysAlign_IO_FIND_TM_WDATA( 2 , i , &src , &wfr ) ) continue;
		//===================================================================================
		// src , wfr
		//========================================================================================================
		if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
		//========================================================================================================
		if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
		//========================================================================================================
	}
	//===================================================================================
	// PM Wafer(AL)
	//===================================================================================
	if ( MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
		if ( !Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) ) {
			if ( Maint_SysAlign_IO_FIND_PM_WDATA( 11 , &src , &wfr ) ) {
				//===================================================================================
				// src , wfr
				//========================================================================================================
				if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
				//========================================================================================================
				if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
				//========================================================================================================
			}
		}
	}
	//===================================================================================
	// PM Wafer(AL)
	//===================================================================================
	for ( i = 1 ; i <= 14 ; i++ ) {
		if ( i == 11 ) continue;
		if ( i == 12 ) continue;
		if ( i == 13 ) continue;
		//========================================================================================================
		if ( Maint_SysAlign_IO_FIND_PM_WIO( i , 0 ) ) continue;
		//========================================================================================================
		if ( !MODULE_CONTROL_IS_POSSIBLE_PM( i ) ) continue;
		//========================================================================================================
		//if ( i != 14 ) {
			if ( !CLEAR_CONTROL_IS_POSSIBLE_PM( i ) ) continue;
		//}
		//========================================================================================================
		if ( !Maint_SysAlign_IO_FIND_PM_WDATA( i , &src , &wfr ) ) continue;
		//===================================================================================
		// src , wfr
		//========================================================================================================
		if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
		//========================================================================================================
		if ( !Maint_Transfer_Clear_Append( src , wfr ) ) return TRUE;
		//========================================================================================================
	}
	//===================================================================================
	return FALSE;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Clear_Sub() {
	int i , p , src , wfr , runarm , dummy , dummy2;
	int Find_Data , Find_Data2;
	int Out_No_Space;
	int Need_Out;
	int CommStatus;


	//===================================================================================
	if ( !MODULE_CONTROL_IS_POSSIBLE_FM() ) return 1001;
	//===================================================================================
	if ( Maint_Transfer_Clear_Pre_Check_Error() ) return 1002; // 2007.12.12
	//===================================================================================

	//===================================================================================
	// 注意：クリア動作する前にアームが縮位置になっていなかったらホーム動作をすること。2008/08/08 EHA
	//===================================================================================
	if( READ_DIGITAL( TR1_RobotArmShort, &CommStatus ) != 1 ) {
		if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM|%d|PM1|%c|1|1" , TRANSFER_RUNMODE , 'A' ) == SYS_ABORTED ) return 9;
	}
	if( READ_DIGITAL( TR2_RobotArmShort, &CommStatus ) != 1 ) {
		if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "HOME_TM2|%d|PM5|%c|1|1" , TRANSFER_RUNMODE , 'A' ) == SYS_ABORTED ) return 9;
	}
	//===================================================================================

	while( TRUE ) {
		//====================================================
		if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9;
		//====================================================
		Find_Data = 0;
		//====================================================
		// 大気アライナのウェハをアライン→Pick→FOUPに回収する。
		//===================================================================================
		// FAL Wafer
		//===================================================================================
		if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) {
			//========================================================================================================
			if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
			//========================================================================================================
			if ( MODULE_CONTROL_IS_POSSIBLE_FAL() ) {
				if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 6;
				//
				if ( runarm == TR_ARM_A ) {
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|AL|1|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0|BM1" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;	// 2006.11.21 EHA modify
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|1|0|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;	// 2013.03.26 SUZUKI modify
				}
				else {
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|AL|0|1" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;
					//if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0|BM1" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;	// 2006.11.21 EHA modify
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICKAL_FALIC|%d|AL|0|1|0" , TRANSFER_RUNMODE ) == SYS_ABORTED ) return 9;	// 2013.03.26 SUZUKI modify
				}
			}
			//========================================================================================================
			if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
			//========================================================================================================
			if ( Maint_SysAlign_IO_FIND_FM_WIO( runarm , 0 ) ) continue;

			if ( !Maint_SysAlign_IO_FIND_FM_WDATA( runarm , &src , &wfr ) ) return 6;
			//========================================================================================================
			if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
			//========================================================================================================
			if ( !Maint_SysAlign_IO_FIND_CM_WIO( src + 1 , wfr , 1 ) ) return 6;
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|%d|0" , TRANSFER_RUNMODE , src + 1 , wfr ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_FM|%d|CM%d|0|%d" , TRANSFER_RUNMODE , src + 1 , wfr ) == SYS_ABORTED ) return 9;
			}
			Find_Data++;
		}
		if ( Find_Data != 0 ) continue;
		//====================================================
		// EFEM Arm上のウェハを大気アライナにPlaceする。
		//===================================================================================
		// FM Wafer
		//========================================================================================================
		if ( TR_Place_Arm_Check( 0 , &runarm ) ) {
			//========================================================================================================
			if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
			//===================================================================================
			if ( !Maint_SysAlign_IO_FIND_FAL_WIO( 0 , &dummy , &dummy2 ) ) return 6;
			//===================================================================================
			//if ( Maint_SysAlign_IO_FIND_FM_WIO( runarm , 0 ) ) continue;
			//if ( !Maint_SysAlign_IO_FIND_FM_WDATA( runarm , &src , &wfr ) ) return 6;
			//========================================================================================================
			//if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
			//========================================================================================================
			//if ( !Maint_SysAlign_IO_FIND_CM_WIO( src + 1 , wfr , 1 ) ) return 6;
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|%d|0" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACEONLY_FALIC|%d|AL|0|%d" , TRANSFER_RUNMODE , 1 ) == SYS_ABORTED ) return 9;
			}
			Find_Data++;
		}
		if ( Find_Data != 0 ) continue;
		//===================================================================================
		// BM Wafer(LLB/LLD)
		//===================================================================================
		for ( i = 1 ; i <= 4 ; i++ ) { // 2006.10.24
			//========================================================================================================
			if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
			//========================================================================================================
#ifdef EQ_TYPE_IARIM2A
			//------------------------------------------------------------------------------------------
			// IARIM2(SingleLL仕様)
			//------------------------------------------------------------------------------------------
			// C-7100EX(SingleLL)の仕様はどちらもLoad/Unload共用のためFEMから直接回収可能。よって削除。
#else
			//------------------------------------------------------------------------------------------
			// IARIM2(QuadroLL仕様)
			//------------------------------------------------------------------------------------------
			if ( ( i == 1 ) || ( i == 3 ) ) continue;
#endif
			if ( Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
			if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
			//
			if ( !TR_Pick_Arm_Check( 0 , &runarm ) ) return 6;
			//
			if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_FM|%d|BM%d" , TRANSFER_RUNMODE , i ) == SYS_ABORTED ) return 9;
			if ( runarm == TR_ARM_A ) {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|%d|0" , TRANSFER_RUNMODE , i , 1 ) == SYS_ABORTED ) return 9;
			}
			else {
				if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_FM|%d|BM%d|0|%d" , TRANSFER_RUNMODE , i , 1 ) == SYS_ABORTED ) return 9;
			}
			Find_Data++;
			break;
		}
		if ( Find_Data != 0 ) continue;
		//===================================================================================
		Need_Out = FALSE;
		//===================================================================================
		while( TRUE ) {
			Find_Data2 = 0;
			//===================================================================================
			// TM1 Wafer
			//===================================================================================
			while( TRUE ) {
				//====================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9;
				//====================================================
				//
				Out_No_Space = FALSE;
				//--------------------------------------------------------------------------------------------------------------------------↓
				// ↓↓↓↓↓ EHA 2006.11.21 add
				//--------------------------------------------------------------------------------------------------------------------------↓
				// PASS1,PASS2のウェハチェックしてウェハがあるときはアームをチェックしてPICKしてL1L,L2Lへ
				for ( p = 11 ; p <= 12 ; p++ ) {	// PASS1,PASS2のウェハチェック
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) continue;
					if ( !MODULE_CONTROL_IS_POSSIBLE_PM( p ) ) continue;

					Need_Out = TRUE;
					//-----------------------------------------------------------------------
					for ( runarm = 0 ; runarm < 2 ; runarm++ ) {
						if ( !Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) continue;	// アームにウェハがないか確認(runarm=0→A, runarm=1→B）
						if ( !Maint_SysAlign_IO_FIND_TM_WDATA( 1 , runarm , &src , &wfr ) ) return 6;
						//========================================================================================================
						if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
						//========================================================================================================
						break;
					}
					if( runarm > 1 ) {
						Out_No_Space = TRUE;
						break;
					}
					//-----------------------------------------------------------------------
					//
#ifdef EQ_TYPE_IARIM2A
					//------------------------------------------------------------------------------------------
					// IARIM2(SingleLL仕様)
					//------------------------------------------------------------------------------------------
					// C-7100EX(SingleLL)の仕様はどちらもLoad/Unload共用のためFEMから直接回収可能。よって全LLをチェック。
					for ( i = 1 ; i <= 4 ; i ++ ) {
						if ( !Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
						if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
						break;
					}
#else
					//------------------------------------------------------------------------------------------
					// IARIM2(QuadroLL仕様)
					//------------------------------------------------------------------------------------------
					for ( i = 2 ; i <= 4 ; i = i + 2 ) {	// LL1L,LL2Lのウェハ有無チェック
						if ( !Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
						if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
						break;
					}
#endif
					//
					if ( i > 4 ) {	// LL1L,LL2Lにスペースがない場合は処理中断
						Out_No_Space = TRUE;
						break;
					}
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					// 注意：アラインする前にアームを動かすこと。2008/08/08 EHA
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "ROTATE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;
					//========================================================================================================
					// PASS1とPASS2で使用するTMC_ALIGNER_CONTROLが異なる。
					if ( p == 11 ) {
						WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
						if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 2" , runarm + 'A' ) != SYS_SUCCESS ) return 9;
					}
					else if ( p == 12 ) {
						WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
						if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 2" , runarm + 'A' ) != SYS_SUCCESS ) return 9;
					}
					//
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS1からウェハをPICK
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , TRANSFER_RUNMODE , i ) == SYS_ABORTED ) return 9;	// LL3UorLL3Lをベント
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|BM%d|%c|1|%d" , TRANSFER_RUNMODE , i , runarm + 'A' , 1 ) == SYS_ABORTED ) return 9;	// LL3UorLL3LにPLACE
				}
				//--------------------------------------------------------------------------------------------------------------------------↓
				// ↑↑↑↑↑↑ EHA 2006.11.21 add
				//--------------------------------------------------------------------------------------------------------------------------↓
				//======================
				if ( Out_No_Space ) break;
				//======================
				// アームチェックしてウェハがあるときにはPASS1またはPASS2へ置いてアラインしてからL1L,L2Lへ
				for ( runarm = 0 ; runarm < 2 ; runarm++ ) {
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_TM_WIO( 1 , runarm , 0 ) ) continue;	// アームにウェハがないか確認(runarm=0→A, runarm=1→B）
					if ( !Maint_SysAlign_IO_FIND_TM_WDATA( 1 , runarm , &src , &wfr ) ) return 6;
					//========================================================================================================
					if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.06.02
					//========================================================================================================
					//
					Need_Out = TRUE;
					//--------------------------------------------------------------------------------------------------------------------------↓
					// ↓↓↓↓↓ EHA 2006.11.21 add
					//--------------------------------------------------------------------------------------------------------------------------↓
					/*
					for ( p = 11 ; p <= 11 ; p++ ) {	// PASS1のウェハチェック
						if ( !Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) continue;
						if ( !MODULE_CONTROL_IS_POSSIBLE_PM( p ) ) continue;
						break;
					}
					if ( p > 11 ) {	// PASS1にスペースがない場合は処理中断
						Out_No_Space = TRUE;
						break;
					}
					*/
					// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
					if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
					&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
						p = 11;
					}
					// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
					else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
					&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
						p = 12;
					}
					// それ以外の場合は、エラーを返す
					else{ // PASS1,PASS2にスペースがない場合は処理中断
						Out_No_Space = TRUE;
						break;
					}
					//--------------------------------------------------------------------------------------------------------------------------↓
					// ↑↑↑↑↑↑ EHA 2006.11.21 add
					//--------------------------------------------------------------------------------------------------------------------------↓
#ifdef EQ_TYPE_IARIM2A
					//------------------------------------------------------------------------------------------
					// IARIM2(SingleLL仕様)
					//------------------------------------------------------------------------------------------
					// C-7100EX(SingleLL)の仕様はどちらもLoad/Unload共用のためFEMから直接回収可能。よって全LLをチェック。
					for ( i = 1 ; i <= 4 ; i ++ ) {
						if ( !Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
						if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
						break;
					}
#else
					//------------------------------------------------------------------------------------------
					// IARIM2(QuadroLL仕様)
					//------------------------------------------------------------------------------------------
					for ( i = 2 ; i <= 4 ; i = i + 2 ) {	// LL1L,LL2Lのウェハ有無チェック
						if ( !Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
						if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
						break;
					}
#endif
					//
					if ( i > 4 ) {	// LL1L,LL2Lにスペースがない場合は処理中断
						Out_No_Space = TRUE;
						break;
					}
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS1にウェハをPLACE
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					// PASS1とPASS2で使用するTMC_ALIGNER_CONTROLが異なる。
					if ( p == 11 ) {
						WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
						if ( RUN_FUNCTIONF( TMC_ALIGNER_CONTROL , "ALIGN %c_AL 1 2" , runarm + 'A' ) != SYS_SUCCESS ) return 9;
					}
					else if ( p == 12 ) {
						WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
						if ( RUN_FUNCTIONF( TMC_ALIGNER2_CONTROL , "ALIGN %c_AL 1 2" , runarm + 'A' ) != SYS_SUCCESS ) return 9;
					}
					//
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS1からウェハをPICK
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , TRANSFER_RUNMODE , i ) == SYS_ABORTED ) return 9;	// LL3UorLL3Lをベント
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM|%d|BM%d|%c|1|%d" , TRANSFER_RUNMODE , i , runarm + 'A' , 1 ) == SYS_ABORTED ) return 9;	// LL3UorLL3LにPLACE
				}
				//======================
				if ( Out_No_Space ) break;
				//======================
				Find_Data = 0;
				for ( p = 1 ; p <= 4 ; p++ ) {	// PM-A, PM-B, PM-E, PM-F のウェハチェック
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) continue;
					if ( !MODULE_CONTROL_IS_POSSIBLE_PM( p ) ) continue;
					if ( !CLEAR_CONTROL_IS_POSSIBLE_PM( p ) ) continue; // 2007.12.09
					if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
					//-----------------------------------------------------------------------
					Need_Out = TRUE;
					Find_Data++;
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PMからウェハをPICK
					break;
				}
				//======================
				if ( Find_Data != 0 ) continue;
				//======================
				//===================================================================================
				// BM Wafer(LLA/LLC)
				//===================================================================================
#ifdef EQ_TYPE_IARIM2A
				//------------------------------------------------------------------------------------------
				// IARIM2(SingleLL仕様)
				//------------------------------------------------------------------------------------------
				// C-7100EX(SingleLL)の仕様はどちらもLoad/Unload共用のためFEMから直接回収可能なため上の処理にて回収されるはず。よって削除。
#else
				//------------------------------------------------------------------------------------------
				// IARIM2(QuadroLL仕様)
				//------------------------------------------------------------------------------------------
				for ( i = 1 ; i <= 4 ; i++ ) {
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( ( i == 2 ) || ( i == 4 ) ) continue;
					if ( Maint_SysAlign_IO_FIND_BM_WIO( i , 1 , 0 , &dummy , &dummy2 ) ) continue;
					if ( !MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) continue;
					if ( !TR_Pick_Arm_Check( 1 , &runarm ) ) return 6;
					//-----------------------------------------------------------------------
					Need_Out = TRUE;
					Find_Data++;
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "WAITING_FOR_TM|%d|BM%d" , TRANSFER_RUNMODE , i ) == SYS_ABORTED ) return 9;
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM|%d|BM%d|%c|1|%d" , TRANSFER_RUNMODE , i , runarm + 'A' , 1 ) == SYS_ABORTED ) return 9;
					break;
				}
#endif
				//======================
				if ( Find_Data != 0 ) continue;
				//======================
				printf("[Clear] TM1 while()\n" );
				break;
			}
			//===================================================================================
			// TM2 Wafer
			//===================================================================================
			while( TRUE ) {
				//====================================================
				if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9;
				//====================================================
				//
				Out_No_Space = FALSE;
				//
				for ( runarm = 0 ; runarm < 2 ; runarm++ ) {
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_TM_WIO( 2 , runarm , 0 ) ) continue;
					if ( !Maint_SysAlign_IO_FIND_TM_WDATA( 2 , runarm , &src , &wfr ) ) return 6;
					//========================================================================================================
					if ( (src >= 4) && (src < 8) ) src -= 5;	// 2009.03.09
					//========================================================================================================
					//
					//-----------------------------------------------------------------------
					Need_Out = TRUE;
					//-----------------------------------------------------------------------
					/*
					if ( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
						Out_No_Space = TRUE;
						break;
					}
					else {
						if ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) ) {
							if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , 11 , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS3へPLACE
							//-----------------------------------------------------------------------
							Find_Data2++;
							//-----------------------------------------------------------------------
						}
						else {
							Out_No_Space = TRUE;
							break;
						}
					}
					*/
					// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
					if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
					&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
						p = 11;
					}
					// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
					else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
					&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
						p = 12;
					}
					// それ以外の場合は、エラーを返す
					else{ // PASS1,PASS2にスペースがない場合は処理中断
						Out_No_Space = TRUE;
						break;
					}
					// 上の処理でウェハのチェックを行っているため、ここではウェハ有無のチェックは行わない。
					/*
					if ( Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) {
						if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS3へPLACE
						//-----------------------------------------------------------------------
						Find_Data2++;
						//-----------------------------------------------------------------------
					}
					else {
						Out_No_Space = TRUE;
						break;
					}
					*/
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PLACE_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;	// PASS3へPLACE
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
				}
				//======================
				if ( Out_No_Space ) break;
				//======================
				Find_Data = 0;
				for ( p = 5 ; p <= 10 ; p++ ) {
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) continue;
					if ( !MODULE_CONTROL_IS_POSSIBLE_PM( p ) ) continue;
					if ( !CLEAR_CONTROL_IS_POSSIBLE_PM( p ) ) continue; // 2007.12.09
					if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 6;
					//-----------------------------------------------------------------------
					Need_Out = TRUE;
					Find_Data++;
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;
					break;
				}
				//======================
				if ( Find_Data != 0 ) continue;
				//======================
				// 2015.03.26 PM-G(PM14)追加 -------------------------------↓
				for ( p = 14 ; p <= 14 ; p++ ) {
					//========================================================================================================
					if ( Maint_Transfer_Tag_Chking() == SYS_ABORTED ) return 9; // 2007.12.09
					//========================================================================================================
					if ( Maint_SysAlign_IO_FIND_PM_WIO( p , 0 ) ) continue;
					if ( !MODULE_CONTROL_IS_POSSIBLE_PM( p ) ) continue;
					if ( !CLEAR_CONTROL_IS_POSSIBLE_PM( p ) ) continue; // 2007.12.09
					if ( !TR_Pick_Arm_Check( 2 , &runarm ) ) return 6;
					//-----------------------------------------------------------------------
					Need_Out = TRUE;
					Find_Data++;
					//-----------------------------------------------------------------------
					Find_Data2++;
					//-----------------------------------------------------------------------
					if ( Maint_SysAlign_MAINT_INTERFACE_RUN( "PICK_TM2|%d|PM%d|%c|1|1" , TRANSFER_RUNMODE , p , runarm + 'A' ) == SYS_ABORTED ) return 9;
					break;
				}
				//======================
				if ( Find_Data != 0 ) continue;
				//======================
				// ---------------------------------------------------------↑
				break;
			}
			//=============================================================
			if ( Find_Data2 == 0 ) break;
			//=============================================================
		}
		//=================================================================
		if ( !Need_Out ) break;
		//=================================================================
#ifdef EQ_TYPE_IARIM2A
	// BM1かBM2のどちらかがMaintモードであればOKのため変更。
	//if( !MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ) return 1003;
	for ( i = 1; i <= 2; i++ ) {
		if( MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) break;
	}
	if( i > 2 ) return 1003;
#else
	for ( i = 2; i <= 4; i+=2 ) {
		if( MODULE_CONTROL_IS_POSSIBLE_BM( i ) ) break;
	}
	if( i > 4 ) return 1003;
#endif

	// PASS1,PASS2のどちらかがMaintモードであればOK(どちらもMaintモードで無ければ1004を戻す)
	if( !MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) && !MODULE_CONTROL_IS_POSSIBLE_PM( 12 )) { return 1004; }

	//===================================================================================
		printf("[Clear] whole while()\n" );
	}

	return 0;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void Maint_Transfer_Move_Check_Error_String( int code , char *data ) {
	printf("[Transfer Error No : %d]\n", code);
	switch ( code ) {
	case 0 : // OK
		strcpy( data , "" );
		break;
	case 1 : // Cassette Slot Set
		strcpy( data , "Cassette Slot Setting Error" );
		break;
	case 2 : // Multi Select
		strcpy( data , "Multiple Selection Error" );
		break;
	case 3 : // No Select
		strcpy( data , "Select Data is Nothing" );
		break;
	case 4 : // One Select
		strcpy( data , "Select Data is Just One" );
		break;
	//
	case 11 : // FEM Setting
		strcpy( data , "FEM Select Error" );
		break;
	case 12 : // FEM Next
		strcpy( data , "FEM Next Module Select Error" );
		break;
	case 13 : // FEM Previous
		strcpy( data , "FEM Previous Module Select Error" );
		break;
	//
	case 21 : // TM1 Setting
		strcpy( data , "TM1 Select Error" );
		break;
	case 22 : // TM1 Next
		strcpy( data , "TM1 Next Module Select Error" );
		break;
	case 23 : // TM1 Previous
		strcpy( data , "TM1 Previous Module Select Error" );
		break;
	//
	case 31 : // TM2 Setting
		strcpy( data , "TM2 Select Error" );
		break;
	case 32 : // TM2 Next
		strcpy( data , "TM2 Next Module Select Error" );
		break;
	case 33 : // TM2 Previous
		strcpy( data , "TM2 Previous Module Select Error" );
		break;
	//
	case 41 : // TM3 Setting
		strcpy( data , "TM3 Select Error" );
		break;
	case 42 : // TM3 Next
		strcpy( data , "TM3 Next Module Select Error" );
		break;
	case 43 : // TM3 Previous
		strcpy( data , "TM3 Previous Module Select Error" );
		break;
	//
	case 51 : // LPM Setting
		strcpy( data , "LPM Slot Select Error" );
		break;
	case 52 : // LPM Next
		strcpy( data , "LPM Next Module Select Error" );
		break;
	case 53 : // LPM Previous
		strcpy( data , "LPM Previous Module Select Error" );
		break;
	//
	case 61 : // FAL Setting
		strcpy( data , "FAL Select Error" );
		break;
	case 62 : // FAL Next
		strcpy( data , "FAL Next Module Select Error" );
		break;
	case 63 : // FAL Previous
		strcpy( data , "FAL Previous Module Select Error" );
		break;
	//
	case 71 : // LL Setting
		strcpy( data , "LL Select Error" );
		break;
	case 72 : // LL Next
		strcpy( data , "LL Next Module Select Error" );
		break;
	case 73 : // LL Previous
		strcpy( data , "LL Previous Module Select Error" );
		break;
	//
	case 81 : // LL Setting
		strcpy( data , "LL Select Error" );
		break;
	case 82 : // LL Next
		strcpy( data , "LL Next Module Select Error" );
		break;
	case 83 : // LL Previous
		strcpy( data , "LL Previous Module Select Error" );
		break;
	//
	case 91 : // PM(for TM1) Setting
		strcpy( data , "PM(for TM1) Select Error" );
		break;
	case 92 : // PM(for TM1) Next
		strcpy( data , "PM(for TM1) Next Module Select Error" );
		break;
	case 93 : // PM(for TM1) Previous
		strcpy( data , "PM(for TM1) Previous Module Select Error" );
		break;
	//
	case 101 : // PM(for TM2) Setting
		strcpy( data , "PM(for TM2) Select Error" );
		break;
	case 102 : // PM(for TM2) Next
		strcpy( data , "PM(for TM2) Next Module Select Error" );
		break;
	case 103 : // PM(for TM2) Previous
		strcpy( data , "PM(for TM2) Previous Module Select Error" );
		break;
	//
	case 111 : // PM(for TM3) Setting
		strcpy( data , "PM(for TM3) Select Error" );
		break;
	case 112 : // PM(for TM3) Next
		strcpy( data , "PM(for TM3) Next Module Select Error" );
		break;
	case 113 : // PM(for TM3) Previous
		strcpy( data , "PM(for TM3) Previous Module Select Error" );
		break;
	//
	case 121 : // PM11(ALIGNER) Setting
		strcpy( data , "PM11(ALIGNER) Select Error" );
		break;
	case 122 : // PM11(ALIGNER) Next
		strcpy( data , "PM11(ALIGNER) Next Module Select Error" );
		break;
	case 123 : // PM11(ALIGNER) Previous
		strcpy( data , "PM11(ALIGNER) Previous Module Select Error" );
		break;
	//
	case 131 : // PM12(ALIGNER) Setting
		strcpy( data , "PM12(ALIGNER) Select Error" );
		break;
	case 132 : // PM12(ALIGNER) Next
		strcpy( data , "PM12(ALIGNER) Next Module Select Error" );
		break;
	case 133 : // PM12(ALIGNER) Previous
		strcpy( data , "PM12(ALIGNER) Previous Module Select Error" );
		break;
	//
	case 141 : // PM14,15(PASS3) Setting
		strcpy( data , "PM14,15(PASS3) Select Error" );
		break;
	case 142 : // PM14,15(PASS3) Next
		strcpy( data , "PM14,15(PASS3) Next Module Select Error" );
		break;
	case 143 : // PM14,15(PASS3) Previous
		strcpy( data , "PM14,15(PASS3) Previous Module Select Error" );
		break;
	//
	//
	case 1011 : // FEM Pick Robot
		strcpy( data , "FEM Pick Robot Error" );
		break;
	case 1012 : // FEM Place Robot
		strcpy( data , "FEM Place Robot Error" );
		break;
	//
	case 1021 : // TM1 Pick Robot
		strcpy( data , "TM1 Pick Robot Error" );
		break;
	case 1022 : // TM1 Place Robot
		strcpy( data , "TM1 Place Robot Error" );
		break;
	//
	case 1031 : // TM2 Pick Robot
		strcpy( data , "TM2 Pick Robot Error" );
		break;
	case 1032 : // TM2 Place Robot
		strcpy( data , "TM2 Place Robot Error" );
		break;
	//
	case 1041 : // TM3 Pick Robot
		strcpy( data , "TM3 Pick Robot Error" );
		break;
	case 1042 : // TM3 Place Robot
		strcpy( data , "TM3 Place Robot Error" );
		break;
	//
	case 1051 : // LPM Robot has Wafer
		strcpy( data , "LPM Pick Robot has Wafer Error" );
		break;
	case 1052 : // LPM has not Wafer
		strcpy( data , "LPM has not Wafer Error" );
		break;
	case 1053 : // LPM has Wafer
		strcpy( data , "LPM has Wafer Error" );
		break;
	//
	case 1061 : // FAL Robot has Wafer
		strcpy( data , "FAL Pick Robot has Wafer Error" );
		break;
	case 1062 : // FAL has not Wafer
		strcpy( data , "FAL has not Wafer Error" );
		break;
	case 1063 : // FAL has Wafer
		strcpy( data , "FAL has Wafer Error" );
		break;
	//
	case 1071 : // LL Robot has Wafer
		strcpy( data , "LL Pick Robot has Wafer Error" );
		break;
	case 1072 : // LL has not Wafer
		strcpy( data , "LL has not Wafer Error" );
		break;
	case 1073 : // LL has Wafer
		strcpy( data , "LL has Wafer Error" );
		break;
	//
	case 1081 : // LL Robot has Wafer
		strcpy( data , "LL Pick Robot has Wafer Error" );
		break;
	case 1082 : // LL has not Wafer
		strcpy( data , "LL has not Wafer Error" );
		break;
	case 1083 : // LL has Wafer
		strcpy( data , "LL has Wafer Error" );
		break;
	//
	case 1091 : // PM(for TM1) Robot has Wafer
		strcpy( data , "PM(for TM1) Pick Robot has Wafer Error" );
		break;
	case 1092 : // PM(for TM1) has not Wafer
		strcpy( data , "PM(for TM1) has not Wafer Error" );
		break;
	case 1093 : // PM(for TM1) has Wafer
		strcpy( data , "PM(for TM1) has Wafer Error" );
		break;
	//
	case 1101 : // PM(for TM2) Robot has Wafer
		strcpy( data , "PM(for TM2) Pick Robot has Wafer Error" );
		break;
	case 1102 : // PM(for TM2) has not Wafer
		strcpy( data , "PM(for TM2) has not Wafer Error" );
		break;
	case 1103 : // PM(for TM2) has Wafer
		strcpy( data , "PM(for TM2) has Wafer Error" );
		break;
	//
	case 1111 : // PM(for TM3) Robot has Wafer
		strcpy( data , "PM(for TM3) Pick Robot has Wafer Error" );
		break;
	case 1112 : // PM(for TM3) has not Wafer
		strcpy( data , "PM(for TM3) has not Wafer Error" );
		break;
	case 1113 : // PM(for TM3) has Wafer
		strcpy( data , "PM(for TM3) has Wafer Error" );
		break;
	//
	case 1121 : // PM11(ALIGNER) Robot has Wafer
		strcpy( data , "PM11(ALIGNER) Pick Robot has Wafer Error" );
		break;
	case 1122 : // PM11(ALIGNER) has not Wafer
		strcpy( data , "PM11(ALIGNER) has not Wafer Error" );
		break;
	case 1123 : // PM11(ALIGNER) has Wafer
		strcpy( data , "PM11(ALIGNER) has Wafer Error" );
		break;
	//
	case 1131 : // PM12(ALIGNER) Robot has Wafer
		strcpy( data , "PM12(ALIGNER) Pick Robot has Wafer Error" );
		break;
	case 1132 : // PM12(ALIGNER) has not Wafer
		strcpy( data , "PM12(ALIGNER) has not Wafer Error" );
		break;
	case 1133 : // PM12(ALIGNER) has Wafer
		strcpy( data , "PM12(ALIGNER) has Wafer Error" );
		break;
	//
	case 1141 : // PM14,15(PASS3) Robot has Wafer
		strcpy( data , "PM14,15(PASS3) Pick Robot has Wafer Error" );
		break;
	case 1142 : // PM14,15(PASS3) has not Wafer
		strcpy( data , "PM14,15(PASS3) has not Wafer Error" );
		break;
	case 1143 : // PM14,15(PASS3) has Wafer
		strcpy( data , "PM14,15(PASS3) has Wafer Error" );
		break;
	//
	default :
		strcpy( data , "Move Flow Select Error" );
		break;
	}
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//=============================================================================================
int Maint_Transfer_Batch_Conv_to_TR_Station( int bch ) {
	switch( bch ) {
	case BTR_LPMA :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(1) ) return -1;	return TR_LPMA;	break;
	case BTR_LPMB :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(2) ) return -1;	return TR_LPMB;	break;
	case BTR_LPMC :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(3) ) return -1;	return TR_LPMC;	break;
	case BTR_LPMD :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(4) ) return -1;	return TR_LPMD;	break;
	case BTR_FAL :	if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return -1;	return TR_FAL;	break;
	case BTR_LLA :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(1) ) return -1;	return TR_LLA;	break;
	case BTR_LLB :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(2) ) return -1;	return TR_LLB;	break;
	case BTR_LLC :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(3) ) return -1;	return TR_LLC;	break;
	case BTR_LLD :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(4) ) return -1;	return TR_LLD;	break;
	case BTR_PM1 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(1) ) return -1;	return TR_PM1;	break;
	case BTR_PM2 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(2) ) return -1;	return TR_PM2;	break;
	case BTR_PM3 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(3) ) return -1;	return TR_PM3;	break;
	case BTR_PM4 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(4) ) return -1;	return TR_PM4;	break;
	case BTR_PM5 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(5) ) return -1;	return TR_PM5;	break;
	case BTR_PM6 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(6) ) return -1;	return TR_PM6;	break;
	case BTR_PM7 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(7) ) return -1;	return TR_PM7;	break;
	case BTR_PM8 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(8) ) return -1;	return TR_PM8;	break;
	case BTR_PM9 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(9) ) return -1;	return TR_PM9;	break;
	case BTR_PM10 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(10) ) return -1;	return TR_PM10;	break;
//	case BTR_PM11 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(11) ) return -1;	return TR_PM11;	break; // 2015.03.26 PM11削除
	case BTR_PM12 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(12) ) return -1;	return TR_PM12;	break;
	case BTR_PM14 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(14) ) return -1;	return TR_PM14;	break; // 2015.03.26 PM14追加
	default		  : return -1;		break;
	}
}

int Maint_Transfer_Batch_Sub( int *pos ) {
	int i , s , t , CommStatus , p;
	int dummy , dummy2;
	//=================================================================================================
	*pos = -9999;
	//=================================================================================================
	BTR_Run_Count = 0;
	//=================================================================================================
	for ( i = 0 ; i < 10 ; i++ ) {
		s = READ_DIGITAL( BatchTR_SrcStn1 + i , &CommStatus );
		t = READ_DIGITAL( BatchTR_DestStn1 + i , &CommStatus );
		if ( ( s != BTR_NONE ) && ( t != BTR_NONE ) ) {
			BTR_Run_Source_Station[BTR_Run_Count] = Maint_Transfer_Batch_Conv_to_TR_Station( s );
			if ( BTR_Run_Source_Station[BTR_Run_Count] == -1 ) return 1;
			BTR_Run_Source_Slot[BTR_Run_Count] = READ_DIGITAL( BatchTR_SrcSlot1 + i , &CommStatus ) + 1;
			//
			BTR_Run_Target_Station[BTR_Run_Count] = Maint_Transfer_Batch_Conv_to_TR_Station( t );
			if ( BTR_Run_Target_Station[BTR_Run_Count] == -1 ) return 2;
			BTR_Run_Target_Slot[BTR_Run_Count] = READ_DIGITAL( BatchTR_DestSlot1 + i , &CommStatus ) + 1;
			//
			BTR_Run_Count++;
		}
	}
	if ( BTR_Run_Count <= 0 ) return 3;
	//=================================================================================================
	for ( i = 0 ; i < BTR_Run_Count ; i++ ) {
		//=================================================
		*pos = -9998;
		//=================================================
		TR_Order_Mode[0] = BTR_Run_Source_Station[i];
		TR_Order_Slot[0] = BTR_Run_Source_Slot[i];
		// LLの場合は強制的にSlot番号を1にする。
		if(BTR_Run_Source_Station[i]==TR_LLA||BTR_Run_Source_Station[i]==TR_LLB){
			TR_Order_Slot[0] =1;
		}
		TR_Order_Count = 1;
		//=================================================
		switch( BTR_Run_Source_Station[i] ) {
		case TR_LPMA :
		case TR_LPMB :
		case TR_LPMC :
		case TR_LPMD :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
			case TR_FAL :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				TR_Order_Mode[TR_Order_Count] = TR_FAL;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				TR_Order_Mode[TR_Order_Count] = TR_FAL;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				TR_Order_Mode[TR_Order_Count] = TR_FAL;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// TR1→TR2への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM11 :
			case TR_PM12 :
				TR_Order_Mode[TR_Order_Count] = TR_FAL;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			}
			//===============================================================
			break;
		case TR_FAL :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
			case TR_FAL :
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// TR1→TR2への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM11 :
			case TR_PM12 :
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			}
			//===============================================================
			break;
		case TR_LLA :
		case TR_LLB :
		case TR_LLC :
		case TR_LLD :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				break;
			case TR_FAL :
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				return 11;
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				// TR1→TR2への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			//===============================================================
			break;
		case TR_PM1 :
		case TR_PM2 :
		case TR_PM3 :
		case TR_PM4 :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				// TR1→TR1への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_FAL :
				// TR1→TR1への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				// TR1→TR2への搬送はPASS1を優先して使用する。
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			//===============================================================
			break;
		case TR_PM5 :
		case TR_PM6 :
		case TR_PM7 :
		case TR_PM8 :
		case TR_PM9 :
		case TR_PM10 :
		case TR_PM14 :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				// TR2→TR1への搬送はPASS2を優先して使用する。
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_FAL :
				// TR2→TR1への搬送はPASS2を優先して使用する。
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				// TR2→TR1への搬送はPASS2を優先して使用する。
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				// TR2→TR1への搬送はPASS2を優先して使用する。
				// PASS2にウェハがなし、かつPASS2がMaint状態の場合はPASS2を使用する
				if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 12 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 12 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM12;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// PASS1にウェハがなし、かつPASS1がMaint状態の場合はPASS1を使用する
				else if ( ( Maint_SysAlign_IO_FIND_PM_WIO( 11 , 0 ) )
				&&  MODULE_CONTROL_IS_POSSIBLE_PM( 11 ) ) {
					TR_Order_Mode[TR_Order_Count] = TR_PM11;	TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				break;
			case TR_PM11 :
			case TR_PM12 :
				break;
			}
			//===============================================================
			break;
		case TR_PM11 :
		case TR_PM12 :
			//===============================================================
			switch( BTR_Run_Target_Station[i] ) {
			case TR_LPMA :
			case TR_LPMB :
			case TR_LPMC :
			case TR_LPMD :
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_FAL :
				// LL1のポートにウェハがなし、かつLL1ポートがMaint状態の場合はLL1ポートを使用する
				if( Maint_SysAlign_IO_FIND_BM_WIO( 1 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 1 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLA;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// LL2のポートにウェハがなし、かつLL2ポートがMaint状態の場合はLL2ポートを使用する
				else if( Maint_SysAlign_IO_FIND_BM_WIO( 2 , 1 , 0 , &dummy , &dummy2 )
				&&  MODULE_CONTROL_IS_POSSIBLE_BM( 2 ) ){
					TR_Order_Mode[TR_Order_Count] = TR_LLB;		TR_Order_Slot[TR_Order_Count] = 1;		TR_Order_Count++;
				}
				// それ以外の場合は、エラーを返す
				else{
					return 8;
				}
				break;
			case TR_LLA :
			case TR_LLB :
			case TR_LLC :
			case TR_LLD :
				break;
			case TR_PM1 :
			case TR_PM2 :
			case TR_PM3 :
			case TR_PM4 :
				break;
			case TR_PM5 :
			case TR_PM6 :
			case TR_PM7 :
			case TR_PM8 :
			case TR_PM9 :
			case TR_PM10 :
			case TR_PM14 :
				break;
			case TR_PM11 :
				return 13;
				break;
			}
			//===============================================================
			break;
		}
		//=================================================
		TR_Order_Mode[TR_Order_Count] = BTR_Run_Target_Station[i];
		TR_Order_Slot[TR_Order_Count] = BTR_Run_Target_Slot[i];
		if(BTR_Run_Target_Station[i]==TR_LLA||BTR_Run_Target_Station[i]==TR_LLB){
			TR_Order_Slot[TR_Order_Count] =1;
		}
		TR_Order_Count++;
		//=================================================
//		for ( t = 0 ; t < TR_Order_Count ; t++ ) {
//			printf( "[%d] [CH=%d][SLOT=%d]\n" , t + 1 , TR_Order_Mode[t] , TR_Order_Slot[t] );
//		}
		s = Maint_Transfer_Move_Sub( TRUE , &p );
		if ( s != 0 ) {
			*pos = p;
			return s;
		}
	}
	return 0;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void Maint_Transfer_Pause() {
	int CommStatus;
	switch( READ_DIGITAL( MTR_CONTROL , &CommStatus ) ) {
	case CTL_IDLE :
	case CTL_WAITING :
	case CTL_WAIT_HANDOFF :
		break;
	case CTL_RUNNING :
		WRITE_DIGITAL( MTR_CONTROL , CTL_PAUSING , &CommStatus );
		break;
	case CTL_PAUSING :
		break;
	case CTL_PAUSED :
		break;
	case CTL_ABORTING :
	case CTL_DISABLE :
		break;
	}
}
void Maint_Transfer_Continue() {
	int CommStatus;
	switch( READ_DIGITAL( MTR_CONTROL , &CommStatus ) ) {
	case CTL_IDLE :
	case CTL_WAITING :
	case CTL_WAIT_HANDOFF :
		break;
	case CTL_RUNNING :
		break;
	case CTL_PAUSING :
	case CTL_PAUSED :
		WRITE_DIGITAL( MTR_CONTROL , CTL_RUNNING , &CommStatus );
		break;
	case CTL_ABORTING :
	case CTL_DISABLE :
		break;
	}
}
void Maint_Transfer_Abort() {
	int CommStatus;
	switch( READ_DIGITAL( MTR_CONTROL , &CommStatus ) ) {
	case CTL_IDLE :
	case CTL_WAITING :
	case CTL_WAIT_HANDOFF :
		break;
	case CTL_RUNNING :
		WRITE_DIGITAL( MTR_CONTROL , CTL_ABORTING , &CommStatus );
		break;
	case CTL_PAUSING :
		WRITE_DIGITAL( MTR_CONTROL , CTL_ABORTING , &CommStatus );
		break;
	case CTL_PAUSED :
		WRITE_DIGITAL( MTR_CONTROL , CTL_ABORTING , &CommStatus );
		break;
	case CTL_ABORTING :
	case CTL_DISABLE :
		WRITE_DIGITAL( MTR_CONTROL , CTL_ABORTING , &CommStatus );
		break;
	}
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int Maint_Transfer_Move() {
	int res , CommStatus , p;
	if ( READ_DIGITAL( MTR_CONTROL , &CommStatus ) != CTL_IDLE ) return 1;
	WRITE_DIGITAL( MTR_CONTROL , CTL_RUNNING , &CommStatus );
	WRITE_STRING( TR_STATUS , "" , &CommStatus ); // 2007.12.12
	//
	res = Maint_Transfer_Move_Sub( FALSE , &p );
	WRITE_DIGITAL( MTR_CONTROL , CTL_IDLE , &CommStatus );
	if ( res != 0 ) {
		WRITE_STRING( TR_STATUS , "MOVE ERROR" , &CommStatus );
		printf( "[Move Error] = %d(%d)\n" , res , p );
	}
	if ( res == 0 ) return SYS_SUCCESS;
	return SYS_ABORTED;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Batch() {
	int res , CommStatus , p;
	if ( READ_DIGITAL( MTR_CONTROL , &CommStatus ) != CTL_IDLE ) return 1;
	WRITE_DIGITAL( MTR_CONTROL , CTL_RUNNING , &CommStatus );
	WRITE_STRING( TR_STATUS , "" , &CommStatus ); // 2007.12.12
	//
	res = Maint_Transfer_Batch_Sub( &p );
	WRITE_DIGITAL( MTR_CONTROL , CTL_IDLE , &CommStatus );
	if ( res != 0 ) {
		WRITE_STRING( TR_STATUS , "BATCH MOVE ERROR" , &CommStatus );
		printf( "[Batch Move Error] = %d(%d)\n" , res , p );
	}
	if ( res == 0 ) return SYS_SUCCESS;
	return SYS_ABORTED;
}
//------------------------------------------------------------------------------------------
// Batch Transfer の IOを初期値に戻す処理
//------------------------------------------------------------------------------------------
int Maint_Batch_IO_All_Clear() {
	int i, CommStatus;

	for(i = 0;i < 10;i++) {
		WRITE_DIGITAL( BatchTR_SrcStn1   + i , 0 , &CommStatus );
		WRITE_DIGITAL( BatchTR_SrcSlot1  + i , 0 , &CommStatus );
		WRITE_DIGITAL( BatchTR_DestStn1  + i , 0 , &CommStatus );
		WRITE_DIGITAL( BatchTR_DestSlot1 + i , 0 , &CommStatus );
	}
	return SYS_ABORTED;
}
//------------------------------------------------------------------------------------------
int Maint_Transfer_Clear() {
	int res , CommStatus;
	if ( READ_DIGITAL( MTR_CONTROL , &CommStatus ) != CTL_IDLE ) return 1;
	WRITE_DIGITAL( MTR_CONTROL , CTL_RUNNING , &CommStatus );
	WRITE_STRING( TR_STATUS , "" , &CommStatus ); // 2007.12.12

	// 2015.05.29
	WRITE_DIGITAL( CTC_TAKT_mode , 0 , &CommStatus ); // 0 == Off

	//
	res = Maint_Transfer_Clear_Sub();
	//
	WRITE_DIGITAL( MTR_CONTROL , CTL_IDLE , &CommStatus );
	if ( res != 0 ) {
		switch( res ) {
			case 6:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : Can not Move More" , &CommStatus );
				break;
			case 9:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : Clear Operation is Aborted" , &CommStatus );
				break;
			case 1001:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : EFEM is not Maintenance Mode" , &CommStatus );
				break;
			case 1002:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : WaferID Error" , &CommStatus );
				break;
			case 1003:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : Clear LL are not Maintenance Mode" , &CommStatus );
				break;
			case 1004:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR : Clear PASS are not Maintenance Mode" , &CommStatus );
				break;
			default:
				WRITE_STRING( TR_STATUS , "CLEAR ERROR" , &CommStatus );
				break;
		}
		printf( "[Clear Error] = %d\n" , res );
	}
	printf("Maint_Transfer_Clear, res=%d\n", res);
	if ( res == 0 ) return SYS_SUCCESS;
	return SYS_ABORTED;
}
//------------------------------------------------------------------------------------------
void Maint_Transfer_TR_GUI( char *data ) {
	int Res , ch , CommStatus;
	char Buffer[256];
	int SLOT_SET = 0; // 2007.12.12 HJKIM

	if      ( STRCMP_L( data , "CM1" ) ) ch = TR_LPMA;
	else if ( STRCMP_L( data , "CM2" ) ) ch = TR_LPMB;
	else if ( STRCMP_L( data , "CM3" ) ) ch = TR_LPMC;
	else if ( STRCMP_L( data , "CM4" ) ) ch = TR_LPMD;
	else if ( STRCMP_L( data , "FAL" ) ) ch = TR_FAL;
	else if ( STRCMP_L( data , "BM1" ) ) ch = TR_LLA;
	else if ( STRCMP_L( data , "BM2" ) ) ch = TR_LLB;
	else if ( STRCMP_L( data , "BM3" ) ) ch = TR_LLC;
	else if ( STRCMP_L( data , "BM4" ) ) ch = TR_LLD;
	else if ( STRCMP_L( data , "PM1" ) ) ch = TR_PM1;
	else if ( STRCMP_L( data , "PM2" ) ) ch = TR_PM2;
	else if ( STRCMP_L( data , "PM3" ) ) ch = TR_PM3;
	else if ( STRCMP_L( data , "PM4" ) ) ch = TR_PM4;
	else if ( STRCMP_L( data , "PM5" ) ) ch = TR_PM5;
	else if ( STRCMP_L( data , "PM6" ) ) ch = TR_PM6;
	else if ( STRCMP_L( data , "PM7" ) ) ch = TR_PM7;
	else if ( STRCMP_L( data , "PM8" ) ) ch = TR_PM8;
	else if ( STRCMP_L( data , "PM9" ) ) ch = TR_PM9;
	else if ( STRCMP_L( data , "PM10" ) ) ch = TR_PM10;
	else if ( STRCMP_L( data , "PM11" ) ) ch = TR_PM11;
	else if ( STRCMP_L( data , "PM12" ) ) ch = TR_PM12;
	else if ( STRCMP_L( data , "PM13" ) ) ch = TR_PM13;
	else if ( STRCMP_L( data , "PM14" ) ) ch = TR_PM14;
	else if ( STRCMP_L( data , "PM15" ) ) ch = TR_PM15;
	else if ( STRCMP_L( data , "FM"  ) ) ch = TR_FM;
	else if ( STRCMP_L( data , "TM1" ) ) ch = TR_TM1;
	else if ( STRCMP_L( data , "TM2" ) ) ch = TR_TM2;
	else if ( STRCMP_L( data , "TM3" ) ) ch = TR_TM3;
	else if ( STRCMP_L( data , "RESET" ) ) {
		WRITE_STRING( TR_STATUS , "" , &CommStatus );
		TR_Order_ReSet( -1 );
		return;
	}
	//=======================================================================
	// 2007.12.12 KORNIC HJKIM
	//=======================================================================
	else if ( STRNCMP_L( data , "SLOT_CM" , 7 ) ) {
		ch = data[7] - '0' - 1;
		if ( data[8] == '|' ) SLOT_SET = atoi( data + 9 );
		if ( SLOT_SET <= 0 ) return; 
		WRITE_DIGITAL( TR_CM1_SLOT + ch , SLOT_SET , &CommStatus );
	}
	//=======================================================================
	else return;
	//========================================================================
	if ( SLOT_SET <= 0 ) { // 2007.12.12 HJKIM
		switch( ch ) {
		case TR_LPMA :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(1) ) return;	break;
		case TR_LPMB :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(2) ) return;	break;
		case TR_LPMC :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(3) ) return;	break;
		case TR_LPMD :	if ( !MODULE_CONTROL_IS_POSSIBLE_CM(4) ) return;	break;
		case TR_FAL :	if ( !MODULE_CONTROL_IS_POSSIBLE_FAL() ) return;	break;
		case TR_LLA :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(1) ) return;	break;
		case TR_LLB :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(2) ) return;	break;
		case TR_LLC :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(3) ) return;	break;
		case TR_LLD :	if ( !MODULE_CONTROL_IS_POSSIBLE_BM(4) ) return;	break;
		case TR_PM1 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(1) ) return;	break;
		case TR_PM2 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(2) ) return;	break;
		case TR_PM3 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(3) ) return;	break;
		case TR_PM4 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(4) ) return;	break;
		case TR_PM5 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(5) ) return;	break;
		case TR_PM6 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(6) ) return;	break;
		case TR_PM7 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(7) ) return;	break;
		case TR_PM8 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(8) ) return;	break;
		case TR_PM9 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(9) ) return;	break;
		case TR_PM10 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(10) ) return;	break;
		case TR_PM11 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(11) ) return;	break;
		case TR_PM12 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(12) ) return;	break;
		case TR_PM13 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(13) ) return;	break;
		case TR_PM14 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(14) ) return;	break;
		case TR_PM15 :	if ( !MODULE_CONTROL_IS_POSSIBLE_PM(15) ) return;	break;
		case TR_FM :	if ( !MODULE_CONTROL_IS_POSSIBLE_FM()  ) return;	break;
		case TR_TM1 :	if ( !MODULE_CONTROL_IS_POSSIBLE_TM(1) ) return;	break;
		case TR_TM2 :	if ( !MODULE_CONTROL_IS_POSSIBLE_TM(2) ) return;	break;
		case TR_TM3 :	if ( !MODULE_CONTROL_IS_POSSIBLE_TM(3) ) return;	break;
		}
		//========================================================================
		Res = Maint_Transfer_Move_Check( FALSE , FALSE );
		switch( Res ) {
		case 0 : // OK
		case 1 : // Cassette Slot Set
		case 3 : // No Select
		case 4 : // One Select
			WRITE_STRING( TR_STATUS , "" , &CommStatus );
			break;
		default :
			Maint_Transfer_Move_Check_Error_String( Res , Buffer );
			strcat( Buffer , " [1]" );
			WRITE_STRING( TR_STATUS , Buffer , &CommStatus );
			return;
			break;
		}
		//============================================================================	
		// Checking
		//============================================================================	
		TR_Order_Count = 0;
		//
		TR_Find_Data = 1;
		//========================================================================
		while ( TRUE ) {
			//
			TR_Find_Count = 0;
			//
			TR_Order_Set( TR_CM1_ORDER , TR_LPMA , FALSE );
			TR_Order_Set( TR_CM2_ORDER , TR_LPMB , FALSE );
			TR_Order_Set( TR_CM3_ORDER , TR_LPMC , FALSE );
			TR_Order_Set( TR_CM4_ORDER , TR_LPMD , FALSE );

			TR_Order_Set( TR_FAL_ORDER , TR_FAL  , FALSE );

#ifdef EQ_TYPE_IARIM2A
			//------------------------------------------------------------------------------------------
			// IARIM2(SingleLL仕様)
			//------------------------------------------------------------------------------------------
			TR_Order_Set( TR_BM1_ORDER , TR_LLA , FALSE );
			TR_Order_Set( TR_BM2_ORDER , TR_LLB , FALSE );
#else
			//------------------------------------------------------------------------------------------
			// IARIM2(QuadroLL仕様)
			//------------------------------------------------------------------------------------------
			TR_Order_Set( TR_BM1_ORDER , TR_LLA , FALSE );
			TR_Order_Set( TR_BM2_ORDER , TR_LLB , FALSE );
			TR_Order_Set( TR_BM3_ORDER , TR_LLC , FALSE );
			TR_Order_Set( TR_BM4_ORDER , TR_LLD , FALSE );
#endif

			TR_Order_Set( TR_PM1_ORDER  , TR_PM1 , FALSE );
			TR_Order_Set( TR_PM2_ORDER  , TR_PM2 , FALSE );
			TR_Order_Set( TR_PM3_ORDER  , TR_PM3 , FALSE );
			TR_Order_Set( TR_PM4_ORDER  , TR_PM4 , FALSE );
			TR_Order_Set( TR_PM5_ORDER  , TR_PM5 , FALSE );
			TR_Order_Set( TR_PM6_ORDER  , TR_PM6 , FALSE );
			TR_Order_Set( TR_PM7_ORDER  , TR_PM7 , FALSE );
			TR_Order_Set( TR_PM8_ORDER  , TR_PM8 , FALSE );
			TR_Order_Set( TR_PM9_ORDER  , TR_PM9 , FALSE );
			TR_Order_Set( TR_PM10_ORDER , TR_PM10 , FALSE );

			TR_Order_Set( TR_PM11_ORDER , TR_PM11 , FALSE );
			TR_Order_Set( TR_PM12_ORDER , TR_PM12 , FALSE );
			TR_Order_Set( TR_PM14_ORDER , TR_PM14 , FALSE );

			TR_Order_Set( TR_PM11_2_ORDER , TR_PM11 , FALSE );
			TR_Order_Set( TR_PM12_2_ORDER , TR_PM12 , FALSE );

			TR_Order_Set( TR_FM_ORDER , TR_FM , FALSE );
			TR_Order_Set( TR_TM1_ORDER , TR_TM1 , FALSE );
			TR_Order_Set( TR_TM2_ORDER , TR_TM2 , FALSE );
			//
			if ( TR_Find_Count != 1 ) {
				TR_Order_ReSet( TR_Find_Data );
				TR_Find_Data--;
				break;
			}
			//
			TR_Find_Data++;
		}
		//========================================================================
		TR_Order_Mode[TR_Order_Count] = ch;
		TR_Order_Slot[TR_Order_Count] = 1;
		TR_Order_Count++;
		//========================================================================
		Res = Maint_Transfer_Move_Check( FALSE , TRUE );
		switch( Res ) {
		case 0 : // OK
		case 1 : // Cassette Slot Set
		case 3 : // No Select
		case 4 : // One Select
			WRITE_STRING( TR_STATUS , "" , &CommStatus );
			break;
		default :
			Maint_Transfer_Move_Check_Error_String( Res , Buffer );
			strcat( Buffer , " [2]" );
			WRITE_STRING( TR_STATUS , Buffer , &CommStatus );
			return;
			break;
		}
		//========================================================================
		switch( ch ) {
		case TR_LPMA :	TR_Order_Select( TR_CM1_ORDER );	break;
		case TR_LPMB :	TR_Order_Select( TR_CM2_ORDER );	break;
		case TR_LPMC :	TR_Order_Select( TR_CM3_ORDER );	break;
		case TR_LPMD :	TR_Order_Select( TR_CM4_ORDER );	break;
		case TR_FAL :	TR_Order_Select( TR_FAL_ORDER );	break;
		case TR_LLA :	TR_Order_Select( TR_BM1_ORDER );	break;
		case TR_LLB :	TR_Order_Select( TR_BM2_ORDER );	break;
		case TR_LLC :	TR_Order_Select( TR_BM3_ORDER );	break;
		case TR_LLD :	TR_Order_Select( TR_BM4_ORDER );	break;
		case TR_PM1 :	TR_Order_Select( TR_PM1_ORDER );	break;
		case TR_PM2 :	TR_Order_Select( TR_PM2_ORDER );	break;
		case TR_PM3 :	TR_Order_Select( TR_PM3_ORDER );	break;
		case TR_PM4 :	TR_Order_Select( TR_PM4_ORDER );	break;
		case TR_PM5 :	TR_Order_Select( TR_PM5_ORDER );	break;
		case TR_PM6 :	TR_Order_Select( TR_PM6_ORDER );	break;
		case TR_PM7 :	TR_Order_Select( TR_PM7_ORDER );	break;
		case TR_PM8 :	TR_Order_Select( TR_PM8_ORDER );	break;
		case TR_PM9 :	TR_Order_Select( TR_PM9_ORDER );	break;
		case TR_PM10 :	TR_Order_Select( TR_PM10_ORDER );	break;
			//
		case TR_PM11 :	TR_Order_Select2( TR_PM11_ORDER , TR_PM11_2_ORDER );	break;
		case TR_PM12 :	TR_Order_Select2( TR_PM12_ORDER , TR_PM12_2_ORDER );	break;
		case TR_PM14 :	TR_Order_Select( TR_PM14_ORDER );	break;
			//
		case TR_FM :	TR_Order_Select( TR_FM_ORDER );		break;
		case TR_TM1 :	TR_Order_Select( TR_TM1_ORDER );	break;
		case TR_TM2 :	TR_Order_Select( TR_TM2_ORDER );	break;
		}
		//========================================================================
		TR_Order_Check( TR_CM1_ORDER , TR_CM1_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_CM2_ORDER , TR_CM2_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_CM3_ORDER , TR_CM3_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_CM4_ORDER , TR_CM4_ORDER2 , TR_Find_Data );

		TR_Order_Check( TR_FAL_ORDER , TR_FAL_ORDER2 , TR_Find_Data );

		TR_Order_Check( TR_BM1_ORDER , TR_BM1_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_BM2_ORDER , TR_BM2_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_BM3_ORDER , TR_BM3_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_BM4_ORDER , TR_BM4_ORDER2 , TR_Find_Data );

		TR_Order_Check( TR_PM1_ORDER , TR_PM1_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM2_ORDER , TR_PM2_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM3_ORDER , TR_PM3_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM4_ORDER , TR_PM4_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM5_ORDER , TR_PM5_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM6_ORDER , TR_PM6_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM7_ORDER , TR_PM7_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM8_ORDER , TR_PM8_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM9_ORDER , TR_PM9_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM10_ORDER , TR_PM10_ORDER2 , TR_Find_Data );

		TR_Order_Check( TR_PM11_ORDER , TR_PM11_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM12_ORDER , TR_PM12_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_PM14_ORDER , TR_PM14_ORDER2 , TR_Find_Data );

		TR_Order_Check( TR_PM11_2_ORDER , TR_PM11_2_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_FM_ORDER , TR_FM_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_TM1_ORDER , TR_TM1_ORDER2 , TR_Find_Data );
		TR_Order_Check( TR_TM2_ORDER , TR_TM2_ORDER2 , TR_Find_Data );
	} // 2007.12.12 HJKIM
	//========================================================================
	Res = Maint_Transfer_Move_Check( TRUE , FALSE );
	switch( Res ) {
	case 0 : // OK
		WRITE_STRING( TR_STATUS , "" , &CommStatus );
		break;
	default :
		Maint_Transfer_Move_Check_Error_String( Res , Buffer );
		strcat( Buffer , " [3]" );
		WRITE_STRING( TR_STATUS , Buffer , &CommStatus );
		break;
	}
	//========================================================================
}

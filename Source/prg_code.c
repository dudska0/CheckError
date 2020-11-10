//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : prg_code.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"
#include "Mtl_Recv.h"
#include "Sys_Align.h"
#include "Fine_Tune.h"
#include "Transfer.h"
#include "Camera_Base.h"
#include "Kutlgui.h"
#include "..\resource.h"

#include "cimseqnc.h"

//------------------------------------------------------------------------------------------
BOOL	SIMULATION_MODE	= FALSE;
//------------------------------------------------------------------------------------------
IO_Name_String_Map IO_STR_Map_Table[] = {
	{ "IO_Driver_Loding"			, _K_D_IO	,	IO_Driver_Loding		,	0	} ,
	//============================================================================
	{ "e:SCHEDULER"					, _K_S_IO	,	SCHEDULER				,	0	} ,
	{ "CTC.TR_STATUS"				, _K_D_IO	,	CTC_TR_STATUS			,	0	} ,

	{ "CTC.INFO_SAVE"				, _K_D_IO	,	INFO_SAVE				,	0	} ,
	//------------------------------------------------------------------------------------------
	{ "SCHEDULER_ERROR"				, _K_F_IO	,	SCHEDULER_ERROR			,	0	} ,
	{ "TMC_STANDBY_CONTROL"			, _K_F_IO	,	TMC_STANDBY_CONTROL		,	0	} ,
	//------------------------------------------------------------------------------------------
	{ "SCHEDULER_MAINT_BM1"			, _K_F_IO	,	SCHEDULER_MAINT_BM1		,	0	} ,
	{ "SCHEDULER_MAINT_BM2"			, _K_F_IO	,	SCHEDULER_MAINT_BM2		,	0	} ,
	{ "SCHEDULER_MAINT_BM3"			, _K_F_IO	,	SCHEDULER_MAINT_BM3		,	0	} ,
	{ "SCHEDULER_MAINT_BM4"			, _K_F_IO	,	SCHEDULER_MAINT_BM4		,	0	} ,
	{ "SCHEDULER_MAINT_PM1"			, _K_F_IO	,	SCHEDULER_MAINT_PM1		,	0	} ,
	{ "SCHEDULER_MAINT_PM2"			, _K_F_IO	,	SCHEDULER_MAINT_PM2		,	0	} ,
	{ "SCHEDULER_MAINT_PM3"			, _K_F_IO	,	SCHEDULER_MAINT_PM3		,	0	} ,
	{ "SCHEDULER_MAINT_PM4"			, _K_F_IO	,	SCHEDULER_MAINT_PM4		,	0	} ,
	{ "SCHEDULER_MAINT_PM5"			, _K_F_IO	,	SCHEDULER_MAINT_PM5		,	0	} ,
	{ "SCHEDULER_MAINT_PM6"			, _K_F_IO	,	SCHEDULER_MAINT_PM6		,	0	} ,
	{ "SCHEDULER_MAINT_PM7"			, _K_F_IO	,	SCHEDULER_MAINT_PM7		,	0	} ,
	{ "SCHEDULER_MAINT_PM8"			, _K_F_IO	,	SCHEDULER_MAINT_PM8		,	0	} ,
	{ "SCHEDULER_MAINT_PM9"			, _K_F_IO	,	SCHEDULER_MAINT_PM9		,	0	} ,
	{ "SCHEDULER_MAINT_PM10"		, _K_F_IO	,	SCHEDULER_MAINT_PM10	,	0	} ,
	{ "SCHEDULER_MAINT_PM11"		, _K_F_IO	,	SCHEDULER_MAINT_PM11	,	0	} ,
	{ "SCHEDULER_MAINT_PM12"		, _K_F_IO	,	SCHEDULER_MAINT_PM12	,	0	} ,
	{ "SCHEDULER_MAINT_PM13"		, _K_F_IO	,	SCHEDULER_MAINT_PM13	,	0	} ,
	{ "SCHEDULER_MAINT_PM14"		, _K_F_IO	,	SCHEDULER_MAINT_PM14	,	0	} ,
//	{ "SCHEDULER_MAINT_PM15"		, _K_F_IO	,	SCHEDULER_MAINT_PM15	,	0	} ,
	{ "SCHEDULER_MAINT_FM"			, _K_F_IO	,	SCHEDULER_MAINT_FM		,	0	} ,
	{ "SCHEDULER_MAINT_TM"			, _K_F_IO	,	SCHEDULER_MAINT_TM		,	0	} ,
	{ "SCHEDULER_MAINT_TM2"			, _K_F_IO	,	SCHEDULER_MAINT_TM2		,	0	} ,
//	{ "SCHEDULER_MAINT_TM3"			, _K_F_IO	,	SCHEDULER_MAINT_TM3		,	0	} ,
	//------------------------------------------------------------------------------------------
	{ "TMC_WFRSNS_CONTROL"			, _K_F_IO	,	TMC_WFRSNS_CONTROL		,	0	} ,
	//------------------------------------------------------------------------------------------
	{ "CTC.SYS_AL_CONTROL"			, _K_D_IO	,	SYS_AL_CONTROL			,	0	} ,

	{ "SYS_AL_Arm"					, _K_D_IO	,	SYS_AL_Arm				,	0	} ,
	{ "SYS_AL_Station"				, _K_D_IO	,	SYS_AL_Station			,	0	} ,
	{ "SYS_AL_Slot"					, _K_D_IO	,	SYS_AL_Slot				,	0	} ,
	
	//------------------------------------------------------------------------------------------
	{ "CTC.MTL_RECV_CONTROL"		, _K_D_IO	,	MTL_RECV_CONTROL		,	0	} ,

	{ "MTL_RECV_Arm"				, _K_D_IO	,	MTL_RECV_Arm			,	0	} ,
	{ "MTL_RECV_Station"			, _K_D_IO	,	MTL_RECV_Station		,	0	} ,
	{ "MTL_RECV_Slot"				, _K_D_IO	,	MTL_RECV_Slot			,	0	} ,
	{ "MTL_RECV_Message"			, _K_S_IO	,	MTL_RECV_Message		,	0	} ,
	
	//------------------------------------------------------------------------------------------
	{ "CTC.MTR_CONTROL"				, _K_D_IO	,	MTR_CONTROL				,	0	} ,

	{ "TR.CM1_ORDER"				, _K_D_IO	,	TR_CM1_ORDER			,	0	} ,
	{ "TR.CM2_ORDER"				, _K_D_IO	,	TR_CM2_ORDER			,	0	} ,
	{ "TR.CM3_ORDER"				, _K_D_IO	,	TR_CM3_ORDER			,	0	} ,
	{ "TR.CM4_ORDER"				, _K_D_IO	,	TR_CM4_ORDER			,	0	} ,

	{ "TR.FAL_ORDER"				, _K_D_IO	,	TR_FAL_ORDER			,	0	} ,
	
	{ "TR.BM1_ORDER"				, _K_D_IO	,	TR_BM1_ORDER			,	0	} ,
	{ "TR.BM2_ORDER"				, _K_D_IO	,	TR_BM2_ORDER			,	0	} ,
	{ "TR.BM3_ORDER"				, _K_D_IO	,	TR_BM3_ORDER			,	0	} ,
	{ "TR.BM4_ORDER"				, _K_D_IO	,	TR_BM4_ORDER			,	0	} ,

	{ "TR.PM1_ORDER"				, _K_D_IO	,	TR_PM1_ORDER			,	0	} ,
	{ "TR.PM2_ORDER"				, _K_D_IO	,	TR_PM2_ORDER			,	0	} ,
	{ "TR.PM3_ORDER"				, _K_D_IO	,	TR_PM3_ORDER			,	0	} ,
	{ "TR.PM4_ORDER"				, _K_D_IO	,	TR_PM4_ORDER			,	0	} ,
	{ "TR.PM5_ORDER"				, _K_D_IO	,	TR_PM5_ORDER			,	0	} ,
	{ "TR.PM6_ORDER"				, _K_D_IO	,	TR_PM6_ORDER			,	0	} ,
	{ "TR.PM7_ORDER"				, _K_D_IO	,	TR_PM7_ORDER			,	0	} ,
	{ "TR.PM8_ORDER"				, _K_D_IO	,	TR_PM8_ORDER			,	0	} ,
	{ "TR.PM9_ORDER"				, _K_D_IO	,	TR_PM9_ORDER			,	0	} ,
	{ "TR.PM10_ORDER"				, _K_D_IO	,	TR_PM10_ORDER			,	0	} ,
	{ "TR.PM11_ORDER"				, _K_D_IO	,	TR_PM11_ORDER			,	0	} ,
	{ "TR.PM12_ORDER"				, _K_D_IO	,	TR_PM12_ORDER			,	0	} ,
//	{ "TR.PM13_ORDER"				, _K_D_IO	,	TR_PM13_ORDER			,	0	} ,
	{ "TR.PM14_ORDER"				, _K_D_IO	,	TR_PM14_ORDER			,	0	} ,
//	{ "TR.PM15_ORDER"				, _K_D_IO	,	TR_PM15_ORDER			,	0	} ,

	{ "TR.PM11_2_ORDER"				, _K_D_IO	,	TR_PM11_2_ORDER			,	0	} ,
	{ "TR.PM12_2_ORDER"				, _K_D_IO	,	TR_PM12_2_ORDER			,	0	} ,
//	{ "TR.PM13_2_ORDER"				, _K_D_IO	,	TR_PM13_2_ORDER			,	0	} ,
//	{ "TR.PM14_2_ORDER"				, _K_D_IO	,	TR_PM14_2_ORDER			,	0	} ,
//	{ "TR.PM15_2_ORDER"				, _K_D_IO	,	TR_PM15_2_ORDER			,	0	} ,

//	{ "TR.PM11_3_ORDER"				, _K_D_IO	,	TR_PM11_3_ORDER			,	0	} ,
//	{ "TR.PM12_3_ORDER"				, _K_D_IO	,	TR_PM12_3_ORDER			,	0	} ,
//	{ "TR.PM13_3_ORDER"				, _K_D_IO	,	TR_PM13_3_ORDER			,	0	} ,
//	{ "TR.PM14_3_ORDER"				, _K_D_IO	,	TR_PM14_3_ORDER			,	0	} ,
//	{ "TR.PM15_3_ORDER"				, _K_D_IO	,	TR_PM15_3_ORDER			,	0	} ,

	{ "TR.FM_ORDER"					, _K_D_IO	,	TR_FM_ORDER				,	0	} ,
	{ "TR.TM1_ORDER"				, _K_D_IO	,	TR_TM1_ORDER			,	0	} ,
	{ "TR.TM2_ORDER"				, _K_D_IO	,	TR_TM2_ORDER			,	0	} ,
//	{ "TR.TM3_ORDER"				, _K_D_IO	,	TR_TM3_ORDER			,	0	} ,
	
	{ "TR.CM1_ORDER2"				, _K_D_IO	,	TR_CM1_ORDER2			,	0	} ,
	{ "TR.CM2_ORDER2"				, _K_D_IO	,	TR_CM2_ORDER2			,	0	} ,
	{ "TR.CM3_ORDER2"				, _K_D_IO	,	TR_CM3_ORDER2			,	0	} ,
	{ "TR.CM4_ORDER2"				, _K_D_IO	,	TR_CM4_ORDER2			,	0	} ,

	{ "TR.FAL_ORDER2"				, _K_D_IO	,	TR_FAL_ORDER2			,	0	} ,
	
	{ "TR.BM1_ORDER2"				, _K_D_IO	,	TR_BM1_ORDER2			,	0	} ,
	{ "TR.BM2_ORDER2"				, _K_D_IO	,	TR_BM2_ORDER2			,	0	} ,
	{ "TR.BM3_ORDER2"				, _K_D_IO	,	TR_BM3_ORDER2			,	0	} ,
	{ "TR.BM4_ORDER2"				, _K_D_IO	,	TR_BM4_ORDER2			,	0	} ,

	{ "TR.PM1_ORDER2"				, _K_D_IO	,	TR_PM1_ORDER2			,	0	} ,
	{ "TR.PM2_ORDER2"				, _K_D_IO	,	TR_PM2_ORDER2			,	0	} ,
	{ "TR.PM3_ORDER2"				, _K_D_IO	,	TR_PM3_ORDER2			,	0	} ,
	{ "TR.PM4_ORDER2"				, _K_D_IO	,	TR_PM4_ORDER2			,	0	} ,
	{ "TR.PM5_ORDER2"				, _K_D_IO	,	TR_PM5_ORDER2			,	0	} ,
	{ "TR.PM6_ORDER2"				, _K_D_IO	,	TR_PM6_ORDER2			,	0	} ,
	{ "TR.PM7_ORDER2"				, _K_D_IO	,	TR_PM7_ORDER2			,	0	} ,
	{ "TR.PM8_ORDER2"				, _K_D_IO	,	TR_PM8_ORDER2			,	0	} ,
	{ "TR.PM9_ORDER2"				, _K_D_IO	,	TR_PM9_ORDER2			,	0	} ,
	{ "TR.PM10_ORDER2"				, _K_D_IO	,	TR_PM10_ORDER2			,	0	} ,
	{ "TR.PM11_ORDER2"				, _K_D_IO	,	TR_PM11_ORDER2			,	0	} ,
	{ "TR.PM12_ORDER2"				, _K_D_IO	,	TR_PM12_ORDER2			,	0	} ,
//	{ "TR.PM13_ORDER2"				, _K_D_IO	,	TR_PM13_ORDER2			,	0	} ,
	{ "TR.PM14_ORDER2"				, _K_D_IO	,	TR_PM14_ORDER2			,	0	} ,
//	{ "TR.PM15_ORDER2"				, _K_D_IO	,	TR_PM15_ORDER2			,	0	} ,
	
	{ "TR.PM11_2_ORDER2"			, _K_D_IO	,	TR_PM11_2_ORDER2		,	0	} ,
	{ "TR.PM12_2_ORDER2"			, _K_D_IO	,	TR_PM12_2_ORDER2		,	0	} ,
//	{ "TR.PM13_2_ORDER2"			, _K_D_IO	,	TR_PM13_2_ORDER2		,	0	} ,
//	{ "TR.PM14_2_ORDER2"			, _K_D_IO	,	TR_PM14_2_ORDER2		,	0	} ,
//	{ "TR.PM15_2_ORDER2"			, _K_D_IO	,	TR_PM15_2_ORDER2		,	0	} ,
	
//	{ "TR.PM11_3_ORDER2"			, _K_D_IO	,	TR_PM11_3_ORDER2		,	0	} ,
//	{ "TR.PM12_3_ORDER2"			, _K_D_IO	,	TR_PM12_3_ORDER2		,	0	} ,
//	{ "TR.PM13_3_ORDER2"			, _K_D_IO	,	TR_PM13_3_ORDER2		,	0	} ,
//	{ "TR.PM14_3_ORDER2"			, _K_D_IO	,	TR_PM14_3_ORDER2		,	0	} ,
//	{ "TR.PM15_3_ORDER2"			, _K_D_IO	,	TR_PM15_3_ORDER2		,	0	} ,
	
	{ "TR.FM_ORDER2"				, _K_D_IO	,	TR_FM_ORDER2			,	0	} ,
	{ "TR.TM1_ORDER2"				, _K_D_IO	,	TR_TM1_ORDER2			,	0	} ,
	{ "TR.TM2_ORDER2"				, _K_D_IO	,	TR_TM2_ORDER2			,	0	} ,
//	{ "TR.TM3_ORDER2"				, _K_D_IO	,	TR_TM3_ORDER2			,	0	} ,
	
	{ "TR.CM1_SLOT"					, _K_D_IO	,	TR_CM1_SLOT				,	0	} ,
	{ "TR.CM2_SLOT"					, _K_D_IO	,	TR_CM2_SLOT				,	0	} ,
	{ "TR.CM3_SLOT"					, _K_D_IO	,	TR_CM3_SLOT				,	0	} ,
	{ "TR.CM4_SLOT"					, _K_D_IO	,	TR_CM4_SLOT				,	0	} ,

	{ "TR.FM_ARM"					, _K_D_IO	,	TR_FM_ARM				,	0	} ,
	{ "TR.TM1_ARM"					, _K_D_IO	,	TR_TM1_ARM				,	0	} ,
	{ "TR.TM2_ARM"					, _K_D_IO	,	TR_TM2_ARM				,	0	} ,
//	{ "TR.TM3_ARM"					, _K_D_IO	,	TR_TM3_ARM				,	0	} ,

	{ "TR.ALIGNING"					, _K_D_IO	,	TR_ALIGNING				,	0	} ,
	{ "TR.STATUS"					, _K_S_IO	,	TR_STATUS				,	0	} ,

	//========================================================================================================
	{ "BatchTR_Source1"				, _K_D_IO	,	BatchTR_SrcStn1			,	0	} ,
	{ "BatchTR_Source2"				, _K_D_IO	,	BatchTR_SrcStn2			,	0	} ,
	{ "BatchTR_Source3"				, _K_D_IO	,	BatchTR_SrcStn3			,	0	} ,
	{ "BatchTR_Source4"				, _K_D_IO	,	BatchTR_SrcStn4			,	0	} ,
	{ "BatchTR_Source5"				, _K_D_IO	,	BatchTR_SrcStn5			,	0	} ,
	{ "BatchTR_Source6"				, _K_D_IO	,	BatchTR_SrcStn6			,	0	} ,
	{ "BatchTR_Source7"				, _K_D_IO	,	BatchTR_SrcStn7			,	0	} ,
	{ "BatchTR_Source8"				, _K_D_IO	,	BatchTR_SrcStn8			,	0	} ,
	{ "BatchTR_Source9"				, _K_D_IO	,	BatchTR_SrcStn9			,	0	} ,
	{ "BatchTR_Source10"			, _K_D_IO	,	BatchTR_SrcStn10		,	0	} ,

	{ "BatchTR_SrcSlot1"			, _K_D_IO	,	BatchTR_SrcSlot1		,	0	} ,
	{ "BatchTR_SrcSlot2"			, _K_D_IO	,	BatchTR_SrcSlot2		,	0	} ,
	{ "BatchTR_SrcSlot3"			, _K_D_IO	,	BatchTR_SrcSlot3		,	0	} ,
	{ "BatchTR_SrcSlot4"			, _K_D_IO	,	BatchTR_SrcSlot4		,	0	} ,
	{ "BatchTR_SrcSlot5"			, _K_D_IO	,	BatchTR_SrcSlot5		,	0	} ,
	{ "BatchTR_SrcSlot6"			, _K_D_IO	,	BatchTR_SrcSlot6		,	0	} ,
	{ "BatchTR_SrcSlot7"			, _K_D_IO	,	BatchTR_SrcSlot7		,	0	} ,
	{ "BatchTR_SrcSlot8"			, _K_D_IO	,	BatchTR_SrcSlot8		,	0	} ,
	{ "BatchTR_SrcSlot9"			, _K_D_IO	,	BatchTR_SrcSlot9		,	0	} ,
	{ "BatchTR_SrcSlot10"			, _K_D_IO	,	BatchTR_SrcSlot10		,	0	} ,

	{ "BatchTR_Destination1"		, _K_D_IO	,	BatchTR_DestStn1		,	0	} ,
	{ "BatchTR_Destination2"		, _K_D_IO	,	BatchTR_DestStn2		,	0	} ,
	{ "BatchTR_Destination3"		, _K_D_IO	,	BatchTR_DestStn3		,	0	} ,
	{ "BatchTR_Destination4"		, _K_D_IO	,	BatchTR_DestStn4		,	0	} ,
	{ "BatchTR_Destination5"		, _K_D_IO	,	BatchTR_DestStn5		,	0	} ,
	{ "BatchTR_Destination6"		, _K_D_IO	,	BatchTR_DestStn6		,	0	} ,
	{ "BatchTR_Destination7"		, _K_D_IO	,	BatchTR_DestStn7		,	0	} ,
	{ "BatchTR_Destination8"		, _K_D_IO	,	BatchTR_DestStn8		,	0	} ,
	{ "BatchTR_Destination9"		, _K_D_IO	,	BatchTR_DestStn9		,	0	} ,
	{ "BatchTR_Destination10"		, _K_D_IO	,	BatchTR_DestStn10		,	0	} ,

	{ "BatchTR_DestSlot1"			, _K_D_IO	,	BatchTR_DestSlot1		,	0	} ,
	{ "BatchTR_DestSlot2"			, _K_D_IO	,	BatchTR_DestSlot2		,	0	} ,
	{ "BatchTR_DestSlot3"			, _K_D_IO	,	BatchTR_DestSlot3		,	0	} ,
	{ "BatchTR_DestSlot4"			, _K_D_IO	,	BatchTR_DestSlot4		,	0	} ,
	{ "BatchTR_DestSlot5"			, _K_D_IO	,	BatchTR_DestSlot5		,	0	} ,
	{ "BatchTR_DestSlot6"			, _K_D_IO	,	BatchTR_DestSlot6		,	0	} ,
	{ "BatchTR_DestSlot7"			, _K_D_IO	,	BatchTR_DestSlot7		,	0	} ,
	{ "BatchTR_DestSlot8"			, _K_D_IO	,	BatchTR_DestSlot8		,	0	} ,
	{ "BatchTR_DestSlot9"			, _K_D_IO	,	BatchTR_DestSlot9		,	0	} ,
	{ "BatchTR_DestSlot10"			, _K_D_IO	,	BatchTR_DestSlot10		,	0	} ,
	
	{ "CTC.FA_STATUS_MDL_CM1"		, _K_D_IO	,	FA_STATUS_MDL_CM1		,	0	} ,
	{ "CTC.FA_STATUS_MDL_CM2"		, _K_D_IO	,	FA_STATUS_MDL_CM2		,	0	} ,
	{ "CTC.FA_STATUS_MDL_CM3"		, _K_D_IO	,	FA_STATUS_MDL_CM3		,	0	} ,
	{ "CTC.FA_STATUS_MDL_CM4"		, _K_D_IO	,	FA_STATUS_MDL_CM4		,	0	} ,

	{ "CTC.FA_STATUS_MDL_PM1"		, _K_D_IO	,	FA_STATUS_MDL_PM1		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM2"		, _K_D_IO	,	FA_STATUS_MDL_PM2		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM3"		, _K_D_IO	,	FA_STATUS_MDL_PM3		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM4"		, _K_D_IO	,	FA_STATUS_MDL_PM4		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM5"		, _K_D_IO	,	FA_STATUS_MDL_PM5		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM6"		, _K_D_IO	,	FA_STATUS_MDL_PM6		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM7"		, _K_D_IO	,	FA_STATUS_MDL_PM7		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM8"		, _K_D_IO	,	FA_STATUS_MDL_PM8		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM9"		, _K_D_IO	,	FA_STATUS_MDL_PM9		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM10"		, _K_D_IO	,	FA_STATUS_MDL_PM10		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM11"		, _K_D_IO	,	FA_STATUS_MDL_PM11		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM12"		, _K_D_IO	,	FA_STATUS_MDL_PM12		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM13"		, _K_D_IO	,	FA_STATUS_MDL_PM13		,	0	} ,
	{ "CTC.FA_STATUS_MDL_PM14"		, _K_D_IO	,	FA_STATUS_MDL_PM14		,	0	} ,
//	{ "CTC.FA_STATUS_MDL_PM15"		, _K_D_IO	,	FA_STATUS_MDL_PM15		,	0	} ,

	{ "CTC.FA_STATUS_MDL_BM1"		, _K_D_IO	,	FA_STATUS_MDL_BM1		,	0	} ,
	{ "CTC.FA_STATUS_MDL_BM2"		, _K_D_IO	,	FA_STATUS_MDL_BM2		,	0	} ,
	{ "CTC.FA_STATUS_MDL_BM3"		, _K_D_IO	,	FA_STATUS_MDL_BM3		,	0	} ,
	{ "CTC.FA_STATUS_MDL_BM4"		, _K_D_IO	,	FA_STATUS_MDL_BM4		,	0	} ,

	{ "CTC.FA_STATUS_MDL_FAL"		, _K_D_IO	,	FA_STATUS_MDL_FAL		,	0	} ,

	{ "CTC.FA_STATUS_MDL_TM"		, _K_D_IO	,	FA_STATUS_MDL_TM		,	0	} ,
	{ "CTC.FA_STATUS_MDL_TM2"		, _K_D_IO	,	FA_STATUS_MDL_TM2		,	0	} ,
//	{ "CTC.FA_STATUS_MDL_TM3"		, _K_D_IO	,	FA_STATUS_MDL_TM3		,	0	} ,

	{ "CTC.FA_STATUS_MDL_FM"		, _K_D_IO	,	FA_STATUS_MDL_FM		,	0	} ,

	//========================================================================================================
	
	{ "ALIGNER.GetModelID"			, _K_D_IO	,	VAL_GetModelID			,	0	} ,
	{ "ALIGNER.GetModelMode"		, _K_D_IO	,	VAL_GetModelMode		,	0	} ,
	{ "ALIGNER.SetModelID"			, _K_D_IO	,	VAL_SetModelID			,	0	} ,
	{ "ALIGNER.SetModelMode"		, _K_D_IO	,	VAL_SetModelMode		,	0	} ,
	{ "ALIGNER2.GetModelID"			, _K_D_IO	,	VAL2_GetModelID			,	0	} ,
	{ "ALIGNER2.GetModelMode"		, _K_D_IO	,	VAL2_GetModelMode		,	0	} ,
	{ "ALIGNER2.SetModelID"			, _K_D_IO	,	VAL2_SetModelID			,	0	} ,
	{ "ALIGNER2.SetModelMode"		, _K_D_IO	,	VAL2_SetModelMode		,	0	} ,
	{ "TMC_ALGNLOW_CONTROL"			, _K_F_IO	,	TMC_ALGNLOW_CONTROL		,	0	} ,
	{ "TMC_ALGNLOW2_CONTROL"		, _K_F_IO	,	TMC_ALGNLOW2_CONTROL	,	0	} ,

	{ "P1.ALIGN_CONTROL_MODE"		, _K_D_IO	,	P1_ALIGN_CONTROL_MODE	,	0	} ,
	{ "P2.ALIGN_CONTROL_MODE"		, _K_D_IO	,	P2_ALIGN_CONTROL_MODE	,	0	} ,
	{ "TMC_ALIGNER_CONTROL"			, _K_F_IO	,	TMC_ALIGNER_CONTROL		,	0	} ,
	{ "TMC_ALIGNER2_CONTROL"		, _K_F_IO	,	TMC_ALIGNER2_CONTROL	,	0	} ,
	{ "R1_STATE"					, _K_D_IO	,	R1_STATE				,	0	} ,

	//========================================================================================================

	{ "CTC.CAM_BASIS_CONTROL"		, _K_D_IO	,	CAM_BASIS_CONTROL		,	0	} ,
	// �I?�����J���������łł͍폜���遫��
//	{ "TMC_CCD_CONTROL"				, _K_F_IO	,	TMC_CCD_CONTROL			,	0	} , // 2014.08.20 �폜
	// �I?�����J���������łł͍폜���遪��
	// 2014.03.12 suzuki add����
	{ "TMC_CAMERA_CONTROL"			, _K_F_IO	,	TMC_CAMERA_CONTROL		,	0	} ,
	{ "TMC_CAMERA2_CONTROL"			, _K_F_IO	,	TMC_CAMERA2_CONTROL		,	0	} , // 2014.08.20 �R�����g����
	// 2014.03.12 suzuki add����
//	{ "Cam.LL1U.Check"				, _K_D_IO	,	CAM_LL1U_CHECK			,	0	} ,
	{ "Cam.LL1L.Check"				, _K_D_IO	,	CAM_LL1L_CHECK			,	0	} ,
//	{ "Cam.LL2U.Check"				, _K_D_IO	,	CAM_LL2U_CHECK			,	0	} ,
	{ "Cam.LL2L.Check"				, _K_D_IO	,	CAM_LL2L_CHECK			,	0	} ,
	{ "Cam.PMA.Check"				, _K_D_IO	,	CAM_PMA_CHECK			,	0	} ,
	{ "Cam.PMB.Check"				, _K_D_IO	,	CAM_PMB_CHECK			,	0	} ,
	{ "Cam.PME.Check"				, _K_D_IO	,	CAM_PME_CHECK			,	0	} ,
	{ "Cam.PMF.Check"				, _K_D_IO	,	CAM_PMF_CHECK			,	0	} ,
	{ "Cam.PMC.Check"				, _K_D_IO	,	CAM_PMC_CHECK			,	0	} ,
	{ "Cam.PMD.Check"				, _K_D_IO	,	CAM_PMD_CHECK			,	0	} ,
	{ "Cam.PMH.Check"				, _K_D_IO	,	CAM_PMH_CHECK			,	0	} ,
	{ "Cam.PMI.Check"				, _K_D_IO	,	CAM_PMI_CHECK			,	0	} ,
	{ "Cam.PMJ.Check"				, _K_D_IO	,	CAM_PMJ_CHECK			,	0	} ,
	{ "Cam.PMK.Check"				, _K_D_IO	,	CAM_PMK_CHECK			,	0	} ,
	{ "Cam.PML.Check"				, _K_D_IO	,	CAM_PML_CHECK			,	0	} ,
	{ "Cam.PMM.Check"				, _K_D_IO	,	CAM_PMM_CHECK			,	0	} ,
	{ "Cam.PMG.Check"				, _K_D_IO	,	CAM_PMG_CHECK			,	0	} ,
	{ "Cam.PMN.Check"				, _K_D_IO	,	CAM_PMN_CHECK			,	0	} ,

//	{ "Cam.LL1U.Check_A"			, _K_D_IO	,	CAM_LL1U_CHECK_A		,	0	} ,
	{ "Cam.LL1L.Check_A"			, _K_D_IO	,	CAM_LL1L_CHECK_A		,	0	} ,
//	{ "Cam.LL2U.Check_A"			, _K_D_IO	,	CAM_LL2U_CHECK_A		,	0	} ,
	{ "Cam.LL2L.Check_A"			, _K_D_IO	,	CAM_LL2L_CHECK_A		,	0	} ,
	{ "Cam.PMA.Check_A"				, _K_D_IO	,	CAM_PMA_CHECK_A			,	0	} ,
	{ "Cam.PMB.Check_A"				, _K_D_IO	,	CAM_PMB_CHECK_A			,	0	} ,
	{ "Cam.PME.Check_A"				, _K_D_IO	,	CAM_PME_CHECK_A			,	0	} ,
	{ "Cam.PMF.Check_A"				, _K_D_IO	,	CAM_PMF_CHECK_A			,	0	} ,
	{ "Cam.PMC.Check_A"				, _K_D_IO	,	CAM_PMC_CHECK_A			,	0	} ,
	{ "Cam.PMD.Check_A"				, _K_D_IO	,	CAM_PMD_CHECK_A			,	0	} ,
	{ "Cam.PMH.Check_A"				, _K_D_IO	,	CAM_PMH_CHECK_A			,	0	} ,
	{ "Cam.PMI.Check_A"				, _K_D_IO	,	CAM_PMI_CHECK_A			,	0	} ,
	{ "Cam.PMJ.Check_A"				, _K_D_IO	,	CAM_PMJ_CHECK_A			,	0	} ,
	{ "Cam.PMK.Check_A"				, _K_D_IO	,	CAM_PMK_CHECK_A			,	0	} ,
	{ "Cam.PML.Check_A"				, _K_D_IO	,	CAM_PML_CHECK_A			,	0	} ,
	{ "Cam.PMM.Check_A"				, _K_D_IO	,	CAM_PMM_CHECK_A			,	0	} ,
	{ "Cam.PMG.Check_A"				, _K_D_IO	,	CAM_PMG_CHECK_A			,	0	} ,
	{ "Cam.PMN.Check_A"				, _K_D_IO	,	CAM_PMN_CHECK_A			,	0	} ,

//	{ "Cam.LL1U.Check_B"			, _K_D_IO	,	CAM_LL1U_CHECK_B		,	0	} ,
	{ "Cam.LL1L.Check_B"			, _K_D_IO	,	CAM_LL1L_CHECK_B		,	0	} ,
//	{ "Cam.LL2U.Check_B"			, _K_D_IO	,	CAM_LL2U_CHECK_B		,	0	} ,
	{ "Cam.LL2L.Check_B"			, _K_D_IO	,	CAM_LL2L_CHECK_B		,	0	} ,
	{ "Cam.PMA.Check_B"				, _K_D_IO	,	CAM_PMA_CHECK_B			,	0	} ,
	{ "Cam.PMB.Check_B"				, _K_D_IO	,	CAM_PMB_CHECK_B			,	0	} ,
	{ "Cam.PME.Check_B"				, _K_D_IO	,	CAM_PME_CHECK_B			,	0	} ,
	{ "Cam.PMF.Check_B"				, _K_D_IO	,	CAM_PMF_CHECK_B			,	0	} ,
	{ "Cam.PMC.Check_B"				, _K_D_IO	,	CAM_PMC_CHECK_B			,	0	} ,
	{ "Cam.PMD.Check_B"				, _K_D_IO	,	CAM_PMD_CHECK_B			,	0	} ,
	{ "Cam.PMH.Check_B"				, _K_D_IO	,	CAM_PMH_CHECK_B			,	0	} ,
	{ "Cam.PMI.Check_B"				, _K_D_IO	,	CAM_PMI_CHECK_B			,	0	} ,
	{ "Cam.PMJ.Check_B"				, _K_D_IO	,	CAM_PMJ_CHECK_B			,	0	} ,
	{ "Cam.PMK.Check_B"				, _K_D_IO	,	CAM_PMK_CHECK_B			,	0	} ,
	{ "Cam.PML.Check_B"				, _K_D_IO	,	CAM_PML_CHECK_B			,	0	} ,
	{ "Cam.PMM.Check_B"				, _K_D_IO	,	CAM_PMM_CHECK_B			,	0	} ,
	{ "Cam.PMG.Check_B"				, _K_D_IO	,	CAM_PMG_CHECK_B			,	0	} ,
	{ "Cam.PMN.Check_B"				, _K_D_IO	,	CAM_PMN_CHECK_B			,	0	} ,

	{ "FINETUNE_CHECT_PM1"			, _K_D_IO	,	FINETUNE_CHECT_PM1			,	0	} ,
	{ "FINETUNE_CHECT_PM2"			, _K_D_IO	,	FINETUNE_CHECT_PM2			,	0	} ,
	{ "FINETUNE_CHECT_PM3"			, _K_D_IO	,	FINETUNE_CHECT_PM3			,	0	} ,
	{ "FINETUNE_CHECT_PM4"			, _K_D_IO	,	FINETUNE_CHECT_PM4			,	0	} ,
	{ "FINETUNE_CHECT_PM14"			, _K_D_IO	,	FINETUNE_CHECT_PM14			,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_CHECT_PM5"			, _K_D_IO	,	FINETUNE_CHECT_PM5			,	0	} ,
	{ "FINETUNE_CHECT_PM6"			, _K_D_IO	,	FINETUNE_CHECT_PM6			,	0	} ,
	{ "FINETUNE_CHECT_PM7"			, _K_D_IO	,	FINETUNE_CHECT_PM7			,	0	} ,
	{ "FINETUNE_CHECT_PM8"			, _K_D_IO	,	FINETUNE_CHECT_PM8			,	0	} ,
	{ "FINETUNE_CHECT_PM9"			, _K_D_IO	,	FINETUNE_CHECT_PM9			,	0	} ,
	{ "FINETUNE_CHECT_PM10"			, _K_D_IO	,	FINETUNE_CHECT_PM10			,	0	} ,
	{ "FINETUNE_CHECT_PM12_P1_1"	, _K_D_IO	,	FINETUNE_CHECT_PM12_P1_1	,	0	} ,
	{ "FINETUNE_CHECT_PM12_P1_2"	, _K_D_IO	,	FINETUNE_CHECT_PM12_P1_2	,	0	} ,
	{ "FINETUNE_CHECT_PM11"			, _K_D_IO	,	FINETUNE_CHECT_PM11			,	0	} ,
	{ "FINETUNE_CHECT_PM11_2"		, _K_D_IO	,	FINETUNE_CHECT_PM11_2		,	0	} ,
//	{ "FINETUNE_CHECT_PM11_3"		, _K_D_IO	,	FINETUNE_CHECT_PM11_3		,	0	} ,
	{ "FINETUNE_CHECT_PM12"			, _K_D_IO	,	FINETUNE_CHECT_PM12			,	0	} ,
	{ "FINETUNE_CHECT_PM12_2"		, _K_D_IO	,	FINETUNE_CHECT_PM12_2		,	0	} ,
//	{ "FINETUNE_CHECT_PM12_3"		, _K_D_IO	,	FINETUNE_CHECT_PM12_3		,	0	} ,
//	{ "FINETUNE_CHECT_PM13"			, _K_D_IO	,	FINETUNE_CHECT_PM13			,	0	} ,
//	{ "FINETUNE_CHECT_PM14_3"		, _K_D_IO	,	FINETUNE_CHECT_PM14_3		,	0	} ,
//	{ "FINETUNE_CHECT_PM15"			, _K_D_IO	,	FINETUNE_CHECT_PM15			,	0	} ,
	{ "FINETUNE_CHECT_BM1"			, _K_D_IO	,	FINETUNE_CHECT_BM1			,	0	} ,
	{ "FINETUNE_CHECT_BM2"			, _K_D_IO	,	FINETUNE_CHECT_BM2			,	0	} ,
//	{ "FINETUNE_CHECT_BM3"			, _K_D_IO	,	FINETUNE_CHECT_BM3			,	0	} ,
//	{ "FINETUNE_CHECT_BM4"			, _K_D_IO	,	FINETUNE_CHECT_BM4			,	0	} ,

	{ "FINETUNE_STATUS_PM1"			, _K_D_IO	,	FINETUNE_STATUS_PM1			,	0	} ,
	{ "FINETUNE_STATUS_PM2"			, _K_D_IO	,	FINETUNE_STATUS_PM2			,	0	} ,
	{ "FINETUNE_STATUS_PM3"			, _K_D_IO	,	FINETUNE_STATUS_PM3			,	0	} ,
	{ "FINETUNE_STATUS_PM4"			, _K_D_IO	,	FINETUNE_STATUS_PM4			,	0	} ,
	{ "FINETUNE_STATUS_PM14"		, _K_D_IO	,	FINETUNE_STATUS_PM14		,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_STATUS_PM5"			, _K_D_IO	,	FINETUNE_STATUS_PM5			,	0	} ,
	{ "FINETUNE_STATUS_PM6"			, _K_D_IO	,	FINETUNE_STATUS_PM6			,	0	} ,
	{ "FINETUNE_STATUS_PM7"			, _K_D_IO	,	FINETUNE_STATUS_PM7			,	0	} ,
	{ "FINETUNE_STATUS_PM8"			, _K_D_IO	,	FINETUNE_STATUS_PM8			,	0	} ,
	{ "FINETUNE_STATUS_PM9"			, _K_D_IO	,	FINETUNE_STATUS_PM9			,	0	} ,
	{ "FINETUNE_STATUS_PM10"		, _K_D_IO	,	FINETUNE_STATUS_PM10		,	0	} ,
	{ "FINETUNE_STATUS_PM12_P1_1"	, _K_D_IO	,	FINETUNE_STATUS_PM12_P1_1	,	0	} ,
	{ "FINETUNE_STATUS_PM12_P1_2"	, _K_D_IO	,	FINETUNE_STATUS_PM12_P1_2	,	0	} ,
	{ "FINETUNE_STATUS_PM11"		, _K_D_IO	,	FINETUNE_STATUS_PM11		,	0	} ,
	{ "FINETUNE_STATUS_PM11_2"		, _K_D_IO	,	FINETUNE_STATUS_PM11_2		,	0	} ,
//	{ "FINETUNE_STATUS_PM11_3"		, _K_D_IO	,	FINETUNE_STATUS_PM11_3		,	0	} ,
	{ "FINETUNE_STATUS_PM12"		, _K_D_IO	,	FINETUNE_STATUS_PM12		,	0	} ,
	{ "FINETUNE_STATUS_PM12_2"		, _K_D_IO	,	FINETUNE_STATUS_PM12_2		,	0	} ,
//	{ "FINETUNE_STATUS_PM12_3"		, _K_D_IO	,	FINETUNE_STATUS_PM12_3		,	0	} ,
//	{ "FINETUNE_STATUS_PM13"		, _K_D_IO	,	FINETUNE_STATUS_PM13		,	0	} ,
//	{ "FINETUNE_STATUS_PM14_3"		, _K_D_IO	,	FINETUNE_STATUS_PM14_3		,	0	} ,
//	{ "FINETUNE_STATUS_PM15"		, _K_D_IO	,	FINETUNE_STATUS_PM15		,	0	} ,
	{ "FINETUNE_STATUS_BM1"			, _K_D_IO	,	FINETUNE_STATUS_BM1			,	0	} ,
	{ "FINETUNE_STATUS_BM2"			, _K_D_IO	,	FINETUNE_STATUS_BM2			,	0	} ,
//	{ "FINETUNE_STATUS_BM3"			, _K_D_IO	,	FINETUNE_STATUS_BM3			,	0	} ,
//	{ "FINETUNE_STATUS_BM4"			, _K_D_IO	,	FINETUNE_STATUS_BM4			,	0	} ,

	{ "FINETUNE_OLD_R_POS_PM1"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM1		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM2"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM2		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM3"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM3		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM4"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM4		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM14"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM14		,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_OLD_R_POS_PM5"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM5		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM6"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM6		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM7"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM7		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM8"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM8		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM9"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM9		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM10"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM10		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM12_P1_1", _K_A_IO	,	FINETUNE_OLD_R_POS_PM12_P1_1,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM12_P1_2", _K_A_IO	,	FINETUNE_OLD_R_POS_PM12_P1_2,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM11"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM11		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM11_2"	, _K_A_IO	,	FINETUNE_OLD_R_POS_PM11_2	,	0	} ,
//	{ "FINETUNE_OLD_R_POS_PM11_3"	, _K_A_IO	,	FINETUNE_OLD_R_POS_PM11_3	,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM12"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM12		,	0	} ,
	{ "FINETUNE_OLD_R_POS_PM12_2"	, _K_A_IO	,	FINETUNE_OLD_R_POS_PM12_2	,	0	} ,
//	{ "FINETUNE_OLD_R_POS_PM12_3"	, _K_A_IO	,	FINETUNE_OLD_R_POS_PM12_3	,	0	} ,
//	{ "FINETUNE_OLD_R_POS_PM13"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM13		,	0	} ,
//	{ "FINETUNE_OLD_R_POS_PM14_3"	, _K_A_IO	,	FINETUNE_OLD_R_POS_PM14_3	,	0	} ,
//	{ "FINETUNE_OLD_R_POS_PM15"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM15		,	0	} ,
	{ "FINETUNE_OLD_R_POS_BM1"		, _K_A_IO	,	FINETUNE_OLD_R_POS_BM1		,	0	} ,
	{ "FINETUNE_OLD_R_POS_BM2"		, _K_A_IO	,	FINETUNE_OLD_R_POS_BM2		,	0	} ,
//	{ "FINETUNE_OLD_R_POS_BM3"		, _K_A_IO	,	FINETUNE_OLD_R_POS_BM3		,	0	} ,
//	{ "FINETUNE_OLD_R_POS_BM4"		, _K_A_IO	,	FINETUNE_OLD_R_POS_BM4		,	0	} ,
	
	{ "FINETUNE_OLD_T_POS_PM1"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM1		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM2"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM2		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM3"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM3		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM4"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM4		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM14"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM14		,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_OLD_T_POS_PM5"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM5		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM6"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM6		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM7"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM7		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM8"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM8		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM9"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM9		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM10"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM10		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM12_P1_1", _K_A_IO	,	FINETUNE_OLD_T_POS_PM12_P1_1,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM12_P1_2", _K_A_IO	,	FINETUNE_OLD_T_POS_PM12_P1_2,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM11"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM11		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM11_2"	, _K_A_IO	,	FINETUNE_OLD_T_POS_PM11_2	,	0	} ,
//	{ "FINETUNE_OLD_T_POS_PM11_3"	, _K_A_IO	,	FINETUNE_OLD_T_POS_PM11_3	,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM12"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM12		,	0	} ,
	{ "FINETUNE_OLD_T_POS_PM12_2"	, _K_A_IO	,	FINETUNE_OLD_T_POS_PM12_2	,	0	} ,
//	{ "FINETUNE_OLD_T_POS_PM12_3"	, _K_A_IO	,	FINETUNE_OLD_T_POS_PM12_3	,	0	} ,
//	{ "FINETUNE_OLD_T_POS_PM13"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM13		,	0	} ,
//	{ "FINETUNE_OLD_T_POS_PM14_3"	, _K_A_IO	,	FINETUNE_OLD_T_POS_PM14_3	,	0	} ,
//	{ "FINETUNE_OLD_T_POS_PM15"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM15		,	0	} ,
	{ "FINETUNE_OLD_T_POS_BM1"		, _K_A_IO	,	FINETUNE_OLD_T_POS_BM1		,	0	} ,
	{ "FINETUNE_OLD_T_POS_BM2"		, _K_A_IO	,	FINETUNE_OLD_T_POS_BM2		,	0	} ,
//	{ "FINETUNE_OLD_T_POS_BM3"		, _K_A_IO	,	FINETUNE_OLD_T_POS_BM3		,	0	} ,
//	{ "FINETUNE_OLD_T_POS_BM4"		, _K_A_IO	,	FINETUNE_OLD_T_POS_BM4		,	0	} ,
	
	{ "FINETUNE_NEW_R_POS_PM1"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM1		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM2"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM2		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM3"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM3		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM4"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM4		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM14"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM14		,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_NEW_R_POS_PM5"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM5		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM6"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM6		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM7"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM7		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM8"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM8		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM9"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM9		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM10"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM10		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM12_P1_1", _K_A_IO	,	FINETUNE_NEW_R_POS_PM12_P1_1,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM12_P1_2", _K_A_IO	,	FINETUNE_NEW_R_POS_PM12_P1_2,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM11"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM11		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM11_2"	, _K_A_IO	,	FINETUNE_NEW_R_POS_PM11_2	,	0	} ,
//	{ "FINETUNE_NEW_R_POS_PM11_3"	, _K_A_IO	,	FINETUNE_NEW_R_POS_PM11_3	,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM12"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM12		,	0	} ,
	{ "FINETUNE_NEW_R_POS_PM12_2"	, _K_A_IO	,	FINETUNE_NEW_R_POS_PM12_2	,	0	} ,
//	{ "FINETUNE_NEW_R_POS_PM12_3"	, _K_A_IO	,	FINETUNE_NEW_R_POS_PM12_3	,	0	} ,
//	{ "FINETUNE_NEW_R_POS_PM13"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM13		,	0	} ,
//	{ "FINETUNE_NEW_R_POS_PM14_3"	, _K_A_IO	,	FINETUNE_NEW_R_POS_PM14_3	,	0	} ,
//	{ "FINETUNE_NEW_R_POS_PM15"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM15		,	0	} ,
	{ "FINETUNE_NEW_R_POS_BM1"		, _K_A_IO	,	FINETUNE_NEW_R_POS_BM1		,	0	} ,
	{ "FINETUNE_NEW_R_POS_BM2"		, _K_A_IO	,	FINETUNE_NEW_R_POS_BM2		,	0	} ,
//	{ "FINETUNE_NEW_R_POS_BM3"		, _K_A_IO	,	FINETUNE_NEW_R_POS_BM3		,	0	} ,
//	{ "FINETUNE_NEW_R_POS_BM4"		, _K_A_IO	,	FINETUNE_NEW_R_POS_BM4		,	0	} ,
	
	{ "FINETUNE_NEW_T_POS_PM1"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM1		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM2"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM2		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM3"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM3		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM4"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM4		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM14"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM14		,	0	} , // 2015.04.02 PM14�ǉ�
	{ "FINETUNE_NEW_T_POS_PM5"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM5		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM6"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM6		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM7"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM7		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM8"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM8		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM9"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM9		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM10"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM10		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM12_P1_1", _K_A_IO	,	FINETUNE_NEW_T_POS_PM12_P1_1,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM12_P1_2", _K_A_IO	,	FINETUNE_NEW_T_POS_PM12_P1_2,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM11"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM11		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM11_2"	, _K_A_IO	,	FINETUNE_NEW_T_POS_PM11_2	,	0	} ,
//	{ "FINETUNE_NEW_T_POS_PM11_3"	, _K_A_IO	,	FINETUNE_NEW_T_POS_PM11_3	,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM12"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM12		,	0	} ,
	{ "FINETUNE_NEW_T_POS_PM12_2"	, _K_A_IO	,	FINETUNE_NEW_T_POS_PM12_2	,	0	} ,
//	{ "FINETUNE_NEW_T_POS_PM12_3"	, _K_A_IO	,	FINETUNE_NEW_T_POS_PM12_3	,	0	} ,
//	{ "FINETUNE_NEW_T_POS_PM13"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM13		,	0	} ,
//	{ "FINETUNE_NEW_T_POS_PM14_3"	, _K_A_IO	,	FINETUNE_NEW_T_POS_PM14_3	,	0	} ,
//	{ "FINETUNE_NEW_T_POS_PM15"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM15		,	0	} ,
	{ "FINETUNE_NEW_T_POS_BM1"		, _K_A_IO	,	FINETUNE_NEW_T_POS_BM1		,	0	} ,
	{ "FINETUNE_NEW_T_POS_BM2"		, _K_A_IO	,	FINETUNE_NEW_T_POS_BM2		,	0	} ,
//	{ "FINETUNE_NEW_T_POS_BM3"		, _K_A_IO	,	FINETUNE_NEW_T_POS_BM3		,	0	} ,
//	{ "FINETUNE_NEW_T_POS_BM4"		, _K_A_IO	,	FINETUNE_NEW_T_POS_BM4		,	0	} ,

	{ "FINETUNE_DeltaPick_Comp_R"	, _K_A_IO	,	FINETUNE_DPICK_COMP_R		,	0	} ,
	// 2013/05/07 ----------------------------------------------------------------->>
	{ "P1.X_OFFSET"					, _K_A_IO	,	P1_X_OFFSET					,	0	} ,
	{ "P1.Y_OFFSET"					, _K_A_IO	,	P1_Y_OFFSET					,	0	} ,
	// 2013/05/07 -----------------------------------------------------------------<<
	{ "P1.R_OFFSET"					, _K_A_IO	,	P1_R_OFFSET					,	0	} ,
	// 2013/05/07 ----------------------------------------------------------------->>
	{ "P2.X_OFFSET"					, _K_A_IO	,	P2_X_OFFSET					,	0	} ,
	{ "P2.Y_OFFSET"					, _K_A_IO	,	P2_Y_OFFSET					,	0	} ,
	// 2013/05/07 -----------------------------------------------------------------<<
	{ "P2.R_OFFSET"					, _K_A_IO	,	P2_R_OFFSET					,	0	} ,
	{ "FINETUNE_CHECK_PASS1_PASS2"	, _K_D_IO	,	FINETUNE_CHECK_PASS1_PASS2	,	0	} ,
	{ "FINETUNE_CHECK_PASS"			, _K_D_IO	,	FINETUNE_CHECK_PASS			,	0	} ,

	{ "ALIGNER.MesResult"			, _K_D_IO	,	ALIGNER_MESRESULT			,	0	} ,
	{ "ALIGNER.CorrectAngle"		, _K_D_IO	,	ALIGNER_CORRECT_ANGLE		,	0	} ,
	{ "ALIGNER.M_Angle"				, _K_A_IO	,	ALIGNER_M_ANGLE				,	0	} ,
	{ "ALIGNER.GetCorrectAngle"		, _K_A_IO	,	ALIGNER_GET_CORRECT_ANGLE	,	0	} ,
	{ "ALIGNER2.MesResult"			, _K_D_IO	,	ALIGNER2_MESRESULT			,	0	} ,
	{ "ALIGNER2.CorrectAngle"		, _K_D_IO	,	ALIGNER2_CORRECT_ANGLE		,	0	} ,
	{ "ALIGNER2.M_Angle"			, _K_A_IO	,	ALIGNER2_M_ANGLE			,	0	} ,
	{ "ALIGNER2.GetCorrectAngle"	, _K_A_IO	,	ALIGNER2_GET_CORRECT_ANGLE	,	0	} ,
	{ "NOTCH_CORRECT_CHECK_TR"		, _K_D_IO	,	NOTCH_CORRECT_CHECK_TR		,	0	} ,
	{ "NOTCH_CORRECT_CHECK_ARM"		, _K_D_IO	,	NOTCH_CORRECT_CHECK_ARM		,	0	} ,
	{ "NOTCH_CORRECT_STATUS"		, _K_D_IO	,	NOTCH_CORRECT_STATUS		,	0	} ,
	{ "FINETUNE_NOTCH_ANGLE"		, _K_A_IO	,	FINETUNE_NOTCH_ANGLE		,	0	} ,
	{ "FINETUNE_CORRECT_ANGLE_SET"	, _K_A_IO	,	FINETUNE_CORRECT_ANGLE_SET	,	0	} ,
	{ "FINETUNE_CORRECT_ANGLE_GET"	, _K_A_IO	,	FINETUNE_CORRECT_ANGLE_GET	,	0	} ,

	{ "TR.PM1_CLEAR_SKIP"			, _K_D_IO	,	PM1_CLEAR_SKIP				,	0	} ,
	{ "TR.PM2_CLEAR_SKIP"			, _K_D_IO	,	PM2_CLEAR_SKIP				,	0	} ,
	{ "TR.PM3_CLEAR_SKIP"			, _K_D_IO	,	PM3_CLEAR_SKIP				,	0	} ,
	{ "TR.PM4_CLEAR_SKIP"			, _K_D_IO	,	PM4_CLEAR_SKIP				,	0	} ,
	{ "TR.PM5_CLEAR_SKIP"			, _K_D_IO	,	PM5_CLEAR_SKIP				,	0	} ,
	{ "TR.PM6_CLEAR_SKIP"			, _K_D_IO	,	PM6_CLEAR_SKIP				,	0	} ,
	{ "TR.PM7_CLEAR_SKIP"			, _K_D_IO	,	PM7_CLEAR_SKIP				,	0	} ,
	{ "TR.PM8_CLEAR_SKIP"			, _K_D_IO	,	PM8_CLEAR_SKIP				,	0	} ,
	{ "TR.PM9_CLEAR_SKIP"			, _K_D_IO	,	PM9_CLEAR_SKIP				,	0	} ,
	{ "TR.PM10_CLEAR_SKIP"			, _K_D_IO	,	PM10_CLEAR_SKIP				,	0	} ,
	{ "TR.PM11_CLEAR_SKIP"			, _K_D_IO	,	PM11_CLEAR_SKIP				,	0	} ,
	{ "TR.PM12_CLEAR_SKIP"			, _K_D_IO	,	PM12_CLEAR_SKIP				,	0	} ,
	{ "TR.PM13_CLEAR_SKIP"			, _K_D_IO	,	PM13_CLEAR_SKIP				,	0	} ,
	{ "TR.PM14_CLEAR_SKIP"			, _K_D_IO	,	PM14_CLEAR_SKIP				,	0	} ,
	{ "TR.PM15_CLEAR_SKIP"			, _K_D_IO	,	PM15_CLEAR_SKIP				,	0	} ,

	{ "CTC.All_ControlStatus"		, _K_D_IO	,	All_ControlStatus			,	0	} ,
	
	{ "CTC.PM1_ControlStatus"		, _K_D_IO	,	PM1_ControlStatus			,	0	} ,
	{ "CTC.PM2_ControlStatus"		, _K_D_IO	,	PM2_ControlStatus			,	0	} ,
	{ "CTC.PM3_ControlStatus"		, _K_D_IO	,	PM3_ControlStatus			,	0	} ,
	{ "CTC.PM4_ControlStatus"		, _K_D_IO	,	PM4_ControlStatus			,	0	} ,
	{ "CTC.PM5_ControlStatus"		, _K_D_IO	,	PM5_ControlStatus			,	0	} ,
	{ "CTC.PM6_ControlStatus"		, _K_D_IO	,	PM6_ControlStatus			,	0	} ,
	{ "CTC.PM7_ControlStatus"		, _K_D_IO	,	PM7_ControlStatus			,	0	} ,
	{ "CTC.PM8_ControlStatus"		, _K_D_IO	,	PM8_ControlStatus			,	0	} ,
	{ "CTC.PM9_ControlStatus"		, _K_D_IO	,	PM9_ControlStatus			,	0	} ,
	{ "CTC.PM10_ControlStatus"		, _K_D_IO	,	PM10_ControlStatus			,	0	} ,
	{ "CTC.PM11_ControlStatus"		, _K_D_IO	,	PM11_ControlStatus			,	0	} ,
	{ "CTC.PM12_ControlStatus"		, _K_D_IO	,	PM12_ControlStatus			,	0	} ,
	{ "CTC.PM13_ControlStatus"		, _K_D_IO	,	PM13_ControlStatus			,	0	} ,
	{ "CTC.PM14_ControlStatus"		, _K_D_IO	,	PM14_ControlStatus			,	0	} ,
	{ "CTC.PM15_ControlStatus"		, _K_D_IO	,	PM15_ControlStatus			,	0	} ,
	
	{ "CTC.FM_ControlStatus"		, _K_D_IO	,	FM_ControlStatus			,	0	} ,
	
	{ "CTC.TM_ControlStatus"		, _K_D_IO	,	TM_ControlStatus			,	0	} ,
	{ "CTC.TM2_ControlStatus"		, _K_D_IO	,	TM2_ControlStatus			,	0	} ,
	{ "CTC.TM3_ControlStatus"		, _K_D_IO	,	TM3_ControlStatus			,	0	} ,

	{ "CTC.BM1_ControlStatus"		, _K_D_IO	,	BM1_ControlStatus			,	0	} ,
	{ "CTC.BM2_ControlStatus"		, _K_D_IO	,	BM2_ControlStatus			,	0	} ,
	{ "CTC.BM3_ControlStatus"		, _K_D_IO	,	BM3_ControlStatus			,	0	} ,
	{ "CTC.BM4_ControlStatus"		, _K_D_IO	,	BM4_ControlStatus			,	0	} ,

	//========================================================================================================
	{ "TR1.RobotArmShort"			, _K_D_IO	,	TR1_RobotArmShort			,	0	} ,
	{ "TR2.RobotArmShort"			, _K_D_IO	,	TR2_RobotArmShort			,	0	} ,

	//========================================================================================================
 	{ "PM1.MAIN_CONTROL"			, _K_D_IO	,	PM1_MAIN_CONTROL			,	0	} ,
 	{ "PM2.MAIN_CONTROL"			, _K_D_IO	,	PM2_MAIN_CONTROL			,	0	} ,
 	{ "PM3.MAIN_CONTROL"			, _K_D_IO	,	PM3_MAIN_CONTROL			,	0	} ,
 	{ "PM4.MAIN_CONTROL"			, _K_D_IO	,	PM4_MAIN_CONTROL			,	0	} ,
 	{ "PM5.MAIN_CONTROL"			, _K_D_IO	,	PM5_MAIN_CONTROL			,	0	} ,
 	{ "PM6.MAIN_CONTROL"			, _K_D_IO	,	PM6_MAIN_CONTROL			,	0	} ,
 	{ "PM7.MAIN_CONTROL"			, _K_D_IO	,	PM7_MAIN_CONTROL			,	0	} ,
 	{ "PM8.MAIN_CONTROL"			, _K_D_IO	,	PM8_MAIN_CONTROL			,	0	} ,
 	{ "PM9.MAIN_CONTROL"			, _K_D_IO	,	PM9_MAIN_CONTROL			,	0	} ,
 	{ "PM10.MAIN_CONTROL"			, _K_D_IO	,	PM10_MAIN_CONTROL			,	0	} ,
 	{ "PM14.MAIN_CONTROL"			, _K_D_IO	,	PM14_MAIN_CONTROL			,	0	} ,

//2008.10.17 suzuki add
	{ "LL1.CAM_EXISTS"				, _K_D_IO	,	LL1L_CAM_EXISTS				,	0	} ,
	{ "LL2.CAM_EXISTS"				, _K_D_IO	,	LL2L_CAM_EXISTS				,	0	} ,
	{ "PM1.CAM_EXISTS"				, _K_D_IO	,	PM1_CAM_EXISTS				,	0	} ,
	{ "PM2.CAM_EXISTS"				, _K_D_IO	,	PM2_CAM_EXISTS				,	0	} ,
	{ "PM3.CAM_EXISTS"				, _K_D_IO	,	PM3_CAM_EXISTS				,	0	} ,
	{ "PM4.CAM_EXISTS"				, _K_D_IO	,	PM4_CAM_EXISTS				,	0	} ,
	{ "PM11.CAM_EXISTS"				, _K_D_IO	,	PM11_CAM_EXISTS				,	0	} ,
	{ "PM12.CAM_EXISTS"				, _K_D_IO	,	PM12_CAM_EXISTS				,	0	} ,
	{ "PM5.CAM_EXISTS"				, _K_D_IO	,	PM5_CAM_EXISTS				,	0	} ,
	{ "PM6.CAM_EXISTS"				, _K_D_IO	,	PM6_CAM_EXISTS				,	0	} ,
	{ "PM7.CAM_EXISTS"				, _K_D_IO	,	PM7_CAM_EXISTS				,	0	} ,
	{ "PM8.CAM_EXISTS"				, _K_D_IO	,	PM8_CAM_EXISTS				,	0	} ,
	{ "PM9.CAM_EXISTS"				, _K_D_IO	,	PM9_CAM_EXISTS				,	0	} ,
	{ "PM10.CAM_EXISTS"				, _K_D_IO	,	PM10_CAM_EXISTS				,	0	} ,
	{ "PM13.CAM_EXISTS"				, _K_D_IO	,	PM13_CAM_EXISTS				,	0	} ,
	{ "PM14.CAM_EXISTS"				, _K_D_IO	,	PM14_CAM_EXISTS				,	0	} ,
	//============================================================================
	{ "FC_TM_WFRSNS_CONTROL"		, _K_D_IO	,	TM_WFRSNS_CONTROL			,	0	} ,
	{ "FC_TM_CAM_CONTROL"			, _K_D_IO	,	TM_CAM_CONTROL				,	0	} ,
	//20141217 Okabe
	{   "P2.CORRECT_ANGLE_SET"	        , _K_A_IO	,	CORRECT_ANGLE_SET_GUI	,	0	} ,

	{ "CTC.TAKT_mode"				, _K_D_IO	,	CTC_TAKT_mode				,	0	} , // 2015.05.29
	""
};
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
BOOL MODULE_CONTROL_IS_POSSIBLE_CM( int ch ) {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_CM1 + ch - 1 , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}
BOOL MODULE_CONTROL_IS_POSSIBLE_BM( int ch ) {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_BM1 + ch - 1 , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 1 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}
BOOL MODULE_CONTROL_IS_POSSIBLE_PM( int ch ) {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_PM1 + ch - 1 , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 1 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}
BOOL MODULE_CONTROL_IS_POSSIBLE_TM( int ch ) {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_TM + ch - 1 , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 1 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}
BOOL MODULE_CONTROL_IS_POSSIBLE_FM() {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_FM , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 1 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}
BOOL MODULE_CONTROL_IS_POSSIBLE_FAL() {
	int res , CommStatus;
	res = READ_DIGITAL( FA_STATUS_MDL_FAL , &CommStatus );
	if ( res == 0 ) return FALSE;
	if ( res == 3 ) return FALSE;
	return TRUE;
}

BOOL CLEAR_CONTROL_IS_POSSIBLE_PM( int ch ) { // 2007.12.09
	int res , CommStatus;
	res = READ_DIGITAL( PM1_CLEAR_SKIP + ch - 1 , &CommStatus );
	if ( res == 0 ) return TRUE;
	return FALSE;
}

// 2007.03.29 Kornic - Check the module is possible GO_MAINT
BOOL MODULE_CHANGE_MODE_POSSIBLE( int ch , int curr_mode ) {
	int CommStatus;
	int Control_Status;

	Control_Status = READ_DIGITAL( ch , &CommStatus );

	if ( Control_Status != curr_mode ) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Set_Aligner_Mode( int aid , int amode ) 
{
	int CommStatus;

	WRITE_DIGITAL( VAL_SetModelID , aid , &CommStatus );
	WRITE_DIGITAL( VAL_SetModelMode , amode , &CommStatus );

	if ( RUN_FUNCTION( TMC_ALGNLOW_CONTROL , "MODEL_SET" ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( RUN_FUNCTION( TMC_ALGNLOW_CONTROL , "MODEL_READ" ) == SYS_ABORTED ) return SYS_ABORTED;

	if ( ( READ_DIGITAL( VAL_GetModelID , &CommStatus ) != aid ) || ( READ_DIGITAL( VAL_GetModelMode , &CommStatus ) != amode ) )
	{
		printf( "[Fine Tuning] Aligner Model ID & Mode Setting Fail\n" );
		return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Set_Aligner_Mode2( int aid , int amode ) 
{
	int CommStatus;

	WRITE_DIGITAL( VAL2_SetModelID , aid , &CommStatus );
	WRITE_DIGITAL( VAL2_SetModelMode , amode , &CommStatus );

	if ( RUN_FUNCTION( TMC_ALGNLOW2_CONTROL , "MODEL_SET" ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( RUN_FUNCTION( TMC_ALGNLOW2_CONTROL , "MODEL_READ" ) == SYS_ABORTED ) return SYS_ABORTED;

	if ( ( READ_DIGITAL( VAL2_GetModelID , &CommStatus ) != aid ) || ( READ_DIGITAL( VAL2_GetModelMode , &CommStatus ) != amode ) )
	{
		printf( "[Fine Tuning] Aligner2 Model ID & Mode Setting Fail\n" );
		return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Program_Main() {
	int Result = 0 , CommStatus;

	//-------------------------------------------------------------------------------------------
	if     ( STRCMP_L( "MTL_RECV_MAP_CHAMBER" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Map( 0 );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAP_LOCATION" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Map( 1 );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAKE_OCCUPIED" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Map( 2 );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAKE_EMPTY" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Map( 3 );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	//
	else if ( STRCMP_L( "MTL_RECV_MAP_WITHOUT_PM" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_All( FALSE );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAKE_EMPTY_PM" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Empty_All( FALSE );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAP_ALL" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_All( TRUE );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "MTL_RECV_MAKE_EMPTY_ALL" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( MTL_RECV_CONTROL , 1 , &CommStatus );
		Result = Maint_Material_Recovery_Empty_All( TRUE );
		WRITE_DIGITAL( MTL_RECV_CONTROL , 0 , &CommStatus );
	}
	//-------------------------------------------------------------------------------------------
	else if ( STRCMP_L( "SYS_AL_HOME" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 0 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	//==
	else if ( STRCMP_L( "SYS_AL_PICK BM1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK BM2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 1 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK BM3" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 2 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK BM4" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 3 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK LP" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 10 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK FAL_NO" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 11 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	//==
	else if ( STRCMP_L( "SYS_AL_PICK NO" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 4 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL_PICK PREV" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 5 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL_PICK TR1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 6 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL_PICK TR2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 7 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL_PICK TR3" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 8 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_PICK TR1-TR2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 9 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL_PICK TR2-TR1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 10 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P1_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	//==
	else if ( STRCMP_L( "SYS_AL2_PICK BM1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL2_PICK BM2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 1 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL2_PICK BM3" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 2 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL2_PICK BM4" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 3 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	//==
	else if ( STRCMP_L( "SYS_AL2_PICK NO" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 4 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK PREV" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 5 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK TR1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 6 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK TR2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 7 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK TR3" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 8 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL2_PICK TR1-TR2" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 9 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	else if ( STRCMP_L( "SYS_AL2_PICK TR2-TR1" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 1 , 10 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( P2_ALIGN_CONTROL_MODE , 0 , &CommStatus );	// Normal Align
	}
	//==
	else if ( STRCMP_L( "SYS_AL_PLACE" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 2 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_GOTO" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 3 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_EXTEND" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 4 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_RETRACT" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 5 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_UP" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 6 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_DOWN" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = Maint_Sys_Alignment( 7 , 0 );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "SYS_AL_INIT" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		Result = RUN_FUNCTION( TMC_STANDBY_CONTROL , "" );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	//-------------------------------------------------------------------------------------------
	else if ( STRCMP_L( "SYS_FINE_TUNE" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		// 2015.04.16 PASS1���������߃R�����g�A�E�g
		//if ( Set_Aligner_Mode ( 4 , 3 ) == SYS_ABORTED ) Result = 11;	// (4,3) for IARIM2D
		//
		if ( Set_Aligner_Mode2( 3 , 3 ) == SYS_ABORTED ) Result = 12;	// (3,3) for IARIM2D
		if ( Result != 0 ) printf( "FINE_TUNE ERROR_CODE is %d\n" , Result );
		if ( Result == 0 ) Result = Maint_Fine_Tune();
		// 2015.04.16 PASS1���������߃R�����g�A�E�g
		//if ( Set_Aligner_Mode ( 4 , 2 ) == SYS_ABORTED ) Result = 13;	// (4,2) for IARIM2D
		//
		if ( Set_Aligner_Mode2( 3 , 2 ) == SYS_ABORTED ) Result = 14;	// (3,2) for IARIM2D
		if ( Result != 0 ) printf( "FINE_TUNE ERROR_CODE is %d\n" , Result );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		Result = SYS_SUCCESS;
	}
	//-------------------------------------------------------------------------------------------
	else if ( STRCMP_L( "SYS_NOTCH_ANGLE_CORRECT" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		if ( Set_Aligner_Mode ( 4 , 2 ) == SYS_ABORTED ) Result = 11;	// (4,2) for IARIM2D
		if ( Set_Aligner_Mode2( 3 , 3 ) == SYS_ABORTED ) Result = 12;	// (3,3) for IARIM2D
		if ( Result != 0 ) printf( "SYS_NOTCH_ANGLE_CORRECT ERROR_CODE is %d\n" , Result );
		if ( Result == 0 ) Result = Maint_Notch_Angle_Correct();
		if ( Set_Aligner_Mode ( 4 , 2 ) == SYS_ABORTED ) Result = 13;	// (4,2) for IARIM2D
		if ( Set_Aligner_Mode2( 3 , 2 ) == SYS_ABORTED ) Result = 14;	// (3,2) for IARIM2D
		if ( Result != 0 ) printf( "SYS_NOTCH_ANGLE_CORRECT ERROR_CODE is %d\n" , Result );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		Result = SYS_SUCCESS;
	}
	//-------------------------------------------------------------------------------------------
	else if ( STRCMP_L( "SYS_NOTCH_ANGLE_CHECK" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		if ( Set_Aligner_Mode ( 4 , 2 ) == SYS_ABORTED ) Result = 11;	// (4,2) for IARIM2D
		if ( Set_Aligner_Mode2( 3 , 2 ) == SYS_ABORTED ) Result = 12;	// (3,2) for IARIM2D
		if ( Result != 0 ) printf( "SYS_NOTCH_ANGLE_CHECK ERROR_CODE is %d\n" , Result );
		if ( Result == 0 ) Result = Maint_Notch_Angle_Check();
		if ( Set_Aligner_Mode ( 4 , 2 ) == SYS_ABORTED ) Result = 13;	// (4,2) for IARIM2D
		if ( Set_Aligner_Mode2( 3 , 2 ) == SYS_ABORTED ) Result = 14;	// (3,2) for IARIM2D
		if ( Result != 0 ) printf( "SYS_NOTCH_ANGLE_CHECK ERROR_CODE is %d\n" , Result );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		Result = SYS_SUCCESS;
	}
	//-------------------------------------------------------------------------------------------
	else if ( STRCMP_L( "START_TR_MOVE" , PROGRAM_PARAMETER_READ() ) ) {
		Result = Maint_Transfer_Move();
	}
	else if ( STRCMP_L( "START_TR_CLEAR" , PROGRAM_PARAMETER_READ() ) ) {
		Result = Maint_Transfer_Clear();
	}
	else if ( STRCMP_L( "START_BATCH_MOVE" , PROGRAM_PARAMETER_READ() ) ) {
		Result = Maint_Transfer_Batch();
	}
	else if ( STRCMP_L( "BATCH_IO_ALL_CLEAR" , PROGRAM_PARAMETER_READ() ) ) {
		Result = Maint_Batch_IO_All_Clear();
	}
	//===============================================================================
	else if ( STRCMP_L( "CAMERA_BASIS_START" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		WRITE_DIGITAL( CAM_BASIS_CONTROL , 1 , &CommStatus );
		Result = Maint_CAM_Basis( );
		printf( "[SCHEDULER_MAINT_ALL] CAMERA_BASIS_START result : %d\n", Result );
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
		WRITE_DIGITAL( CAM_BASIS_CONTROL , 0 , &CommStatus );
	}
	//===============================================================================
	else if ( STRCMP_L( "GO_INIT" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		//20150115 Okabe
		//if (( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_BM1 , "GO_INIT" );
		//if (( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_BM2 , "GO_INIT" );
		//if (( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_BM3 , "GO_INIT" );
		//if (( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_BM4 , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_BM1 , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_BM2 , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_BM3 , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_BM4 , "GO_INIT" );

		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM1_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM1_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM1_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM1 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM2_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM2_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM2_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM2 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM3_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM3_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM3_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM3 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM4_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM4_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM4_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM4 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM5_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM5_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM5_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM5 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM6_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM6_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM6_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM6 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM7_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM7_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM7_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM7 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM8_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM8_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM8_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM8 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM9_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM9_ControlStatus  , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM9_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM9 , "GO_INIT" );
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM10_ControlStatus , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM10_ControlStatus , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM10_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM10 , "GO_INIT" );
		// 2015.03.26 PM-G �ǉ� ��
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM14_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM14 , "GO_INIT" );
		// ---------------------��
		if (( MODULE_CHANGE_MODE_POSSIBLE( FM_ControlStatus   , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( FM_ControlStatus   , MCM_MAINT ) == TRUE ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_FM  , "GO_INIT" );
		
		//20150115 Okabe
		//if (( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_TM  , "GO_INIT" );
		//if (( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_MAINT ) == TRUE ))
		//RUN_SET_FUNCTION( SCHEDULER_MAINT_TM2  , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_TM  , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_TM2  , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM11_ControlStatus , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM11_ControlStatus , MCM_MAINT ) == TRUE ))

		RUN_FUNCTION( SCHEDULER_MAINT_PM11 , "GO_INIT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM12_ControlStatus , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM12_ControlStatus , MCM_MAINT ) == TRUE ))
		RUN_FUNCTION( SCHEDULER_MAINT_PM12 , "GO_INIT" );


		while( TRUE ) {
			if ( !WAIT_SECONDS( 0.1 ) ) {
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM5 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM6 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM7 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM8 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM9 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM10 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM11 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM12 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM13 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM14 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM15 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_FM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM2 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM3 );
				break;
			}
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM5 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM6 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM7 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM8 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM9 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM10 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM11 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM12 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM13 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM14 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_PM15 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_FM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM2 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_TM3 );	if ( Result == SYS_RUNNING ) continue;
			break;
		}
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "GO_MAINT" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM1 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM2 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM3 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM4 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM1_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM1_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM1 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM2_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM2_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM2 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM3_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM3_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM3 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM4_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM4_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM4 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM5_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM5_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM5 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM6_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM6_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM6 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM7_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM7_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM7 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM8_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM8_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM8 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM9_ControlStatus  , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM9_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM9 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM10_ControlStatus , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM10_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM10 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM11_ControlStatus , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM11 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM12_ControlStatus , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM12 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM13_ControlStatus , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM13 , "GO_MAINT" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_STANDBY ) == TRUE )&&( READ_DIGITAL( PM14_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM14 , "GO_MAINT" );
		//if ( MODULE_CHANGE_MODE_POSSIBLE( PM15_ControlStatus , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM15 , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( FM_ControlStatus   , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_FM  , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM  , "GO_MAINT" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM2  , "GO_MAINT" );
		//if ( MODULE_CHANGE_MODE_POSSIBLE( TM3_ControlStatus  , MCM_STANDBY ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM3  , "GO_MAINT" );
		while( TRUE ) {
			if ( !WAIT_SECONDS( 0.1 ) ) {
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM5 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM6 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM7 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM8 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM9 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM10 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM11 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM12 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM13 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM14 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM15 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_FM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM2 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM3 );
				break;
			}
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM5 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM6 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM7 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM8 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM9 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM10 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM11 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM12 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM13 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM14 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_PM15 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_FM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM2 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_TM3 );	if ( Result == SYS_RUNNING ) continue;
			break;
		}
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else if ( STRCMP_L( "GO_STANDBY" , PROGRAM_PARAMETER_READ() ) ) {
		WRITE_DIGITAL( SYS_AL_CONTROL , 1 , &CommStatus );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM1_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM1 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM2_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM2 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM3_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM3 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( BM4_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_BM4 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM1_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM1_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM1 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM2_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM2_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM2 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM3_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM3_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM3 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM4_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM4_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM4 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM5_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM5_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM5 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM6_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM6_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM6 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM7_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM7_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM7 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM8_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM8_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM8 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM9_ControlStatus  , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM9_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM9 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM10_ControlStatus , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM10_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM10 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM11_ControlStatus , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM11 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM12_ControlStatus , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM12 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( PM13_ControlStatus , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM13 , "GO_STANDBY" );
		if (( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_MAINT ) == TRUE )&&( READ_DIGITAL( PM14_MAIN_CONTROL , &CommStatus ) == 0 )) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM14 , "GO_STANDBY" );
		//if ( MODULE_CHANGE_MODE_POSSIBLE( PM15_ControlStatus , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_PM15 , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( FM_ControlStatus   , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_FM  , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( TM_ControlStatus   , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM  , "GO_STANDBY" );
		if ( MODULE_CHANGE_MODE_POSSIBLE( TM2_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM2  , "GO_STANDBY" );
		//if ( MODULE_CHANGE_MODE_POSSIBLE( TM3_ControlStatus  , MCM_MAINT ) == TRUE ) RUN_SET_FUNCTION( SCHEDULER_MAINT_TM3  , "GO_STANDBY" );
		while( TRUE ) {
			if ( !WAIT_SECONDS( 0.1 ) ) {
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_BM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM1 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM2 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM3 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM4 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM5 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM6 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM7 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM8 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM9 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM10 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM11 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM12 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM13 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM14 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_PM15 );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_FM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM );
				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM2 );
//				RUN_FUNCTION_ABORT( SCHEDULER_MAINT_TM3 );
				break;
			}
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_BM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM1 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM2 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM3 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM4 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM5 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM6 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM7 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM8 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM9 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM10 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM11 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM12 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM13 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_PM14 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_PM15 );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_FM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM );	if ( Result == SYS_RUNNING ) continue;
			Result = READ_FUNCTION( SCHEDULER_MAINT_TM2 );	if ( Result == SYS_RUNNING ) continue;
//			Result = READ_FUNCTION( SCHEDULER_MAINT_TM3 );	if ( Result == SYS_RUNNING ) continue;
			break;
		}
		WRITE_DIGITAL( SYS_AL_CONTROL , 0 , &CommStatus );
	}
	else {
		Result = SYS_ABORTED;
	}
	WRITE_DIGITAL( INFO_SAVE , 1 , &CommStatus );
	return Result;
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void Event_Message_Received() {
	char data1[256];
	char data2[256];
	//
	STR_SEPERATE( PROGRAM_EVENT_READ() , data1 , data2 , 255 );
	//
	if      ( STRCMP_L( "PAUSETR" , data1 ) ) {
		Maint_Transfer_Pause();
	}
	else if ( STRCMP_L( "CONTINUETR" , data1 ) ) {
		Maint_Transfer_Continue();
	}
	else if ( STRCMP_L( "ABORTTR" , data1 ) ) {
		Maint_Transfer_Abort();
	}
	else if ( STRCMP_L( "TR_GUI" , data1 ) ) {
		Maint_Transfer_TR_GUI( data2 );
	}
	else if ( STRCMP_L( "CAMERA_BASIS_PAUSE" , data1 ) ) {
		Maint_CAM_BASIS_Pause();
	}
	else if ( STRCMP_L( "CAMERA_BASIS_RESUME" , data1 ) ) {
		Maint_CAM_BASIS_Continue();
	}
}

//---------------------------------------------------------------------------------------
// Program Init Code
//
// ***************************************************
// **** Canon ANELVA rule of this program upgrade ****
// *
// * Please do the version number in the increment according to the following form if you update the program!
// *
// * (1) Before REGIST_FILE_INFO() is comment out.
// * (2) Add new REGIST_FILE_INFO() at the end of the line.
// * (3) Fill in new version number, date and your name on REGIST_FILE_INFO().
// * (4) Fill in the upgrade content under REGIST_FILE_INFO().
// * (5) Rewrite VS_VERSION_INFO of resource file.
// *
// * Please keep this rule for the version management.
// ***************************************************
//---------------------------------------------------------------------------------------
BOOL Program_Init_Code() {
	int aWafers;
	char aWaferStr[32], aTempStr[32];
	int CommStatus;

	//---------------------------------------------------------------------------------------
	// version infomation
	//---------------------------------------------------------------------------------------
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 0.01(2006.10.14 EHA)" );
	// (1) Kornic��2006/10/10�ł��C���BPM11?PM15��PLACE�O��Wafer?�F�b�N�֐���?���鐔�l������Ă������ߏC���B
	// (2) Kornic��2006/10/10�ł��C���BPM11��GOTO��Station�w�肪����Ă������ߏC���B1->11�B
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 0.02(2006.11.21 EHA)" );
	// (1) ��������v���O��?�ɂ���TR2�ɂ�PASS1(Aligner)��Place����Align����悤�ɕύX(2006�N11��10���ɔ�������Wafer����΍�)
	// (2) ��������v���O��?�ɂ���FAL�ɃE�F�n������Ƃ��ɉ���ł��Ȃ������C��
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.00(2006.12.13 KornicSystems)" );
	// (1) Konic Systems 2006/12/13 version.
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.01(2006.12.22 KornicSystems)" );
	// (1) Konic Systems 2006/12/22 version.
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.02(2006.12.25 EHA)" );
	// (1) TR2�ɂ�Pass1����Pick����Ƃ���PostPosition��2��1�ɏC���B(Kornic�Ђ�2006/12/25�ł���ύX)
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.03(2006.12.26 EHA)" );
	// (1) Alarm number change. 281-287 -> 181-187
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.04(2007.01.05 KornicSystems Hakjun)" );
	// (1) Pass1(Aligner) Finetune Feature Add.
	//---------------------------------------------------------------------------------------
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.90(2007.02.09 KornicSystems)" );
	// (1) Konic Systems 2007/02/09 version.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.91(2007.02.14 EHA)" );
	// (1) LL1U,LL2U,LL3U,LL3L->LL1U,LL1L,LL2U,LL2L change.
	// (2) IO setting modify.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.92(2007.02.15 KornicSystems)" );
	// (1) FINETUNE PM Array was modified (fine_tune.c)
	// (2) Maint_FineTune_SET_MAX_PM, Maint_FineTune_SET_PER_GROUP_PM, Maint_FineTune_SET_PER_GROUP_BM was modified(prg_code.c)
	// (3) TM_Order_Set was modified (transfer.c)
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.93(2007.02.21 KornicSystems)" );
	// (1) For System Alignment Function (Sys_Align.h, Sys_Align.c) , Enum Value was changed , And Switch Sentence.
	// (2) For Material Recovery Function (Mtl_Recv.h, Mtl_Recv.c), Enum Value was Changed, And Switch Sentence.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.94(2007.02.23 KornicSystems)" );
	// (1) For Transfer & Batch Transfer Function (Transfer.h, Transfer.c) , Enum Value was changed , And Code modified.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.95(2007.03.01 EHA)" );
	// refer to "I-1330 Function_Maint_Run 1.06(2007.02.15 EHA)"
	// (1) Maint_Fine_Tune(), FineTuning�ɂ�LoadLock�݂̂��w�肷���PM4��GOTO�������΍�B
	//     tp��-1���Ԃ��Ă���B���̂Ƃ��͈ꕔ�̏������s��Ȃ��B�������ɖ�肪�Ȃ����ŏI�m�F�����邱�ƁB
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.96(2007.03.02 EHA)" );
	// refer to "I-1330 Function_Maint_Run 1.05(2007.02.02 EHA)"
	// (1) Maint_CCD_Basis(), Z axis Basis check additional.
	// (2) Maint_CCD_Basis(), return kind is int -> Module_Status.
	// (3) Maint_Material_Recovery_Empty_All(), FM ArmB not empty bug issue modify.
	// (4) Maint_Fine_Tune(),Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET bug issue modify.
	// (5) Maint_Fine_Tune(),if FineTune for PM11(PASS1) then Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET(11).
	// ...
	// (6) Maint_Sys_Alignment(), Rotate bug fix and arrangement.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.97(2007.03.04 EHA)" );
	// (1) Material Recovery, TR1,TR2��MakeOccupied�����s����Ƃ��ɁCMTR7?Load_Status?��On�ɂ���悤�C��(���̂Ƃ���MakeEmpty�ł�Off�ɂ��Ȃ�)�B *
	// (2) Material Recovery, MakeOccupied�����s�����WaferID��WaferSource���w��ł���悤�ɕύX�B *
	// (3) Material Recovery, WaferSource�ݒ�̎w�肪�Ԉ���Ă����Ƃ�����C���B *
	//     Maint_Material_Recovery_IO_FIND_FM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_PM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_BM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_FAL_WSRC()
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.98(2007.03.13 EHA)" );
	// (1) Program_Main(), "SYS_FINE_TUNE"��AlignerMode�ݒ蕔����I-1230Plus�p�ɕύX
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.99(2007.03.14 EHA)" );
	// (1) Maint_Sys_Alignment(), PASS1(PM11)�ɑ΂���EXTEND,RETRACT�ɑΉ��B
	// (2) Maint_Fine_Tune(),Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET for BM (i+14)->(i+15) change.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.00(2007.03.15 EHA)" );
	// (1) LoadPort�̍ő喇����26������25���ɕύX�B
	// (2) Maint_Transfer_Clear_Sub(), Clear�̂Ƃ�LL1U,LL2U��Wafer�𒼐�EFEM����������s����C���B
	//     LL1U,LL2U��Wafer�́CTR1 Pick->PASS1 Place&DeltaPick->LL1L or LL2L�ɂĉ������悤�ɕύX�B
	// (3) Maint_Transfer_Clear(), SYS_SUCCESS�̂Ƃ�"return SYS_SUCCESS"�ɂȂ��Ă��Ȃ���������������B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.01(2007.03.22 KornicSystems)" );
	// "20070316_fromKornic"����̕ύX
	// (1) CCD_Base.c TM Order and Module Name was changed for I-1230 "2007.03.04 KornicSystems"
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.02(2007.03.30 EHA)" );
	// (1) Maint_Fine_Tune(), PASS1(Aligner)�̂Ƃ���Maint_Material_Recovery_Check_TM()���폜�B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.03(2007.04.02 KornicSystems)" );
	// (1) �uModule��Mode��Uninit�̂Ƃ��CMaint(All)��������GO_MAINT�݂̂��s��Maint�ɂȂ��Ă��܂��B
    //     UnInit�̂Ƃ���́CGO_MAINT���Ȃ��悤�ɂ��Ăق����B�v(ActionItemNo.102)�̑Ή�
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.04(2007.04.04 EHA)" );
	// (1) Maint_CCD_Basis(), ��?�l����̂��߂�Robot���삩��UP���폜�B
	// (2) Maint_CCD_Basis(), ��?�l����̑Ώۂ�LoadLock�̂Ƃ�Pick,Place�����s���Ȃ��悤�ɂ���B
	// (3) Maint_CCD_Basis(), LL1U, LL2U�̂Ƃ��́CCCD�̊�?�l������s��Ȃ�
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.05(2007.04.11 EHA)" );
	// (1) Maint_Transfer_Move_Check(), TR2�̃A??�I����B�A??�ɂ���B�A??��Wafer��H-ch��Place���悤�Ƃ����
	//     "PM(for TM2) Pick Robot has wafer Error[2]"(=1101)��?�������H-ch���I���ł��Ȃ����̑΍�B
	//     "Checking Part 3"��PM��?�F�b�N��"i=0"�̂Ƃ��̂�"TR_Pick_Arm_Check"���s���悤�ɕύX�B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.06(2007.04.17 EHA)" );
	// (1) Maint_Sys_Alignment(), Place����̂Ƃ�TR2��Wafer?�F�b�N�ɊԈႢ���������ߒ����B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.07(2007.04.27 sawatari)" );
	// Clear All����post position�ύX�B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.08(2007.05.08 Chigira)" );
	// (1) Maint_Sys_Alignment(), Pick,Place����ȊO�͑I��惂�W��?���̏�Ԃ����Ȃ��悤�ύX�B
	// (2) �eMaint�pFunction��Ώۃ��W��?����Standby���ɂ͎��s�ł��Ȃ��悤�ύX(����֐��ύX)
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.09(2007.07.18 EHA)" );
	// (1) Maint_Transfer_Move(), SYS_SUCCESS�̑O��return��������������������B
	// (2) Maint_Transfer_Batch(), SYS_SUCCESS�̑O��return��������������������B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.10(2007.07.20 EHA)" );
	// (1) Maint_Material_Simulation_IO_Check(), SIMULATION_MODE�̂Ƃ��CFAL,FM�̃E�F�n?�F�b�N�����������삵�Ȃ����������C���B
	// (2) �X�y��?�X������B"Srouce"->"Source"
	// (3) Program_Init_Code(), Wafer�̖����ݒ��argument����ł���悤�ɉ��P�B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.11(2007.10.11 SuzukiMi)" );
	// (1) Slot�w��?�C�A���O�̍ő�l��MTLRECV_CASSETTE_MAX_SLOT�ŔC�ӂɕύX�ł���悤�ɏC���B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.11(2007.11.21 Sawatari)" );
	// (1) �uInit(All)�v�̎g�p��?�������uUn-Init�v�uMaint�v�ɕύX�B					�� ���nt�Ɨ��(��)t�̕ύX�o?�W�������d�����Ă���B�v���� ��
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.12(2007.12.09 KornicSystems)" );
	// (1) ClearALL�̂Ƃ�?�F�b�N����PM�ȊO������ł���悤�ɕύX�B
	// (1-1) CLEAR_CONTROL_IS_POSSIBLE_PM(), �V�K�쐬
	// (1-2) Maint_TRansfer_Move_Sub(), ClearALL�̂Ƃ���?�F�b�N����PM�ȊO���������悤�ɕύX�B��?�����𑦎���?�ł���悤�ύX�B
	// (1-3) Maint_Transfer_Move_Sub(), ��?�����𑦎���?�ł���悤�ύX�B
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.13(2007.12.16 EHA)" );
	// (1) Maint_Transfer_Clear_Sub(), ClearSkip�̔����PM14�ɂ���Skip�ł��Ȃ������s����C���B
	// (2) Maint_Transfer_Clear_Pre_Check_Error(), PM14�̂ݔ��肩��R��Ă����������C���B
	// (3) Maint_Transfer_Clear(), res=1002�ɑ΂��ďڍׂȃ��b�Z?�W��ǉ��B�� �����ǉ����邱�ƁB
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.14(2008.01.22 EHA)" );
	// (1) ���u?���ɂ�艺�L��2�ɑΉ��������s�t?�C����ʁX�ɍ쐬����悤�ɂ���B
	// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
	// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe
	// �y���Ӂz�F����??�X�����������R���p�C������Ƃ��ɂ̓o�b?�r���h�����s����悤�ɂ��邱�ƁB
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.15(2008.02.07 EHA)" );
	// (1) MaterialRecovery��ʂɂ�ID�̐ݒ�̂Ƃ�LoadPort�̑I����Unuse�̕�����?�����Ȃ��悤�ɕύX�B
	// (1-1) Set_LoadPort_Select_Map(), �V�K�ǉ��BLoadPort�̑I����Unuse�ɂ��킹�ĕύX���邽�߂̊֐��B
	// (1-2) Maint_Material_Recovery_Check_TM(),Maint_Material_Recovery_Check_PM(),Maint_Material_Recovery_Check_BM(),Maint_Material_Recovery_Check_FAL(),Maint_Material_Recovery_Check_FM()
	//        LoadPort�I��?����Set_LoadPort_Select_Map()���g�p����悤�ύX�B
	// (2) �N�����ɃR�A���u?�C�v��LoadPort�̃E�F�n�����ݒ���R��??����?������悤�ɕύX�B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.16(2008.04.23 EHA)" );
	// (1) Maint_Transfer_Batch_Sub(), BatchTransfer��ʂɂ�TR2������LP,LL�ɉ�����邱�Ƃ��ł�����BatchMoveError���N���Ă��܂����̏C���B
	// (2) Maint_Transfer_Batch_Sub(), BatchTransfer��ʂɂ�TR������LP�ɍs����?�g��Unload���ɂȂ��Ă��Ȃ��������̏C���B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.17(2008.05.17 EHA)" );
	// (1) BatchTransfer��ʂɐݒ���e�����Z�b�g����Reset??��ǉ��B
	// (1-1) Program_Main(), "BATCH_IO_ALL_CLEAR"���b�Z?�W���͂�����Maint_Batch_IO_All_Clear��Call����B
	// (1-2) Maint_Batch_IO_All_Clear(), Batch Transfer �� IO�������l�ɖ߂��������s���B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.18(2008.06.12 SAWATARI)" );
	// (1) Module_Status Maint_Material_Recovery_Check_FAL(),Material Recovery��ʂ�AL(ATM)��Make Occupied��Slot�ݒ��IO?���̕����������C���B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.19(2008.08.08 EHA)" );
	// (1) Maint_CCD_Basis(), PASS1(Aligner)�̃A���C������̑O��Robot��Retract���铮���ǉ��B
	// (2) Maint_CCD_Basis(), ��??���蓮�삷��O�ɃA??���k�ʒu�ɂȂ��Ă��Ȃ�������z??��������邱�ƁB
	// (2) Maint_Sys_Alignment(), PASS1(Aligner)�̃A���C������̑O��Robot��Retract���铮���ǉ��B
	// (3) Maint_Transfer_Move_Sub(), PASS1(Aligner)�̃A���C������̑O��Robot��Retract���铮���ǉ��B
	// (4) Maint_Transfer_Clear_Sub(), PASS1(Aligner)�̃A���C������̑O��Robot��Retract���铮���ǉ��B
	// (5) Maint_Transfer_Clear_Sub(), �N���A���삷��O�ɃA??���k�ʒu�ɂȂ��Ă��Ȃ�������z??��������邱��
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.20(2008.08.27 SUZUKIMI)" );
	// (1) Program_Main(), Batch Process��(MAIN_CONTROL=1)�̃��W��?���ɑ΂��Ă�Init(All),Standby(All),Maint(All)�������Ȃ��悤�ɕύX�B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.21(2008.09.19 Chigira)" );
	// (1) Maint_Transfer_Clear_Sub(), ����p��LL���S��MaintenanceMode�łȂ��ꍇ�ɂ͓r���ŏI������悤�ύX�B
	// (1) Maint_Transfer_Clear(), AllClear�̃G��?���b�Z?�W��ǉ��B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.22(2008.10.17 Suzuki)" );
	// (1) Module_Status Maint_CCD_Basis(),CCD�EZ����??�ݒ莞�CCCD�J���������݂��Ȃ��ꍇ��Z���̊�??�̂ݑ��肷��悤�ɕύX�B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.23(2009.06.02 Suzuki)" );
	// (1) Maint_Transfer_Clear_Pre_Check_Error(),Wafer Dummy Scheduler��Clear All�ɂ�Dummy Wafer������ł��Ȃ������C���B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.24(2009.09.23 Sawatari)" );
	// (1) Maint_Material_Recovery_Check_TM(),Maint_Material_Simulation_IO_Check()
	//     Z-axis Sensor��OFF�̎��ATM*.Wafer_Result��?�F�b�N���Ȃ���"RealWafer"���X�V����Ȃ��΍�B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.25(2013.03.27 SUZUKI)" );
	// (1) 2core+2pass�ւ̑Ή�
	// (1-1) IO_Name_String_Map, IO���̂̕ύX
	//       TR2.PM12.CCD_EXISTS��TR1.PM12.CCD_EXISTS, TR1.PM13.CCD_EXISTS��TR2.PM13.CCD_EXISTS
	// (1-2) Maint_Sys_Alignment(), LLC,LLD,PM14�̍폜�BPM12(PASS2)�̒ǉ��B
	// (1-3) ClearAll���ATR1��,TR2���̃E�F�n����PASS1,PASS2�̏��Œu�����B
	// (1-4) Maint_Material_Recovery_Map_Sub(),Maint_Material_Recovery_Map(), LLC,LLD,PM14�̍폜�BPM12(PASS2)�̒ǉ��B
	// (1-5) Maint_Transfer_Batch_Sub(), BatchTransfer�ɂāATR1��TR2��PASS1���ATR2��TR1��PASS2��D�悵�Ďg�p����悤�ɕύX�B
	//       (�D�悷��PASS�ɃE�F�n������A�܂���Maint��?�h�łȂ��ꍇ�́A�����Е���PASS���o�R����B)
	// (2) Maint_Transfer_Batch_Sub �ɂāA�o�H�쐬�̍ۂ�LL1��ʂ�o�H�݂̂��������̂��A
	//     LL1�����LL2�̏��(�E�F�n���Ȃ��A����Maint��?�h��)��?�F�b�N���A�o�H�����肷��悤�ɕύX�B
	//     ������ǂ�����������𖞂����Ă��Ȃ��Ƃ��̓G��?(return 8)��Ԃ��悤�ɕύX�B
	// (3) Source Station,�܂��� Destination Station ��LL1�܂���LL2��ݒ肵���ۂɁABatcthLoadLock�łȂ��ɂ�������炸�A
	//	   SlotNO ��?��ł��Ă��܂����Ƃɂ�蔭������s��ɑΉ��B
	//  �� ��Ђ��Ƃ�if�����̏������ς��̂Œ���(�g�p����BM�̐����قȂ邽��)
	// (4) Material Recovery��ʂ�Map Chamber
	//	   SlotNO ��?��ł��Ă��܂����Ƃɂ�蔭������s��ɑΉ��B
	//  �� ��Ђ��Ƃ�if�����̏������ς��̂Œ���(�g�p����BM�̐����قȂ邽��)
	// (5) Maint_Material_Recovery_Check_TM(), Material Recovery��ʂɂ�TR�A??��Map Chamber�����s����ہA
	//     TMC_RBLOW*_CONTROL��"CHECKLOAD"�R?���h��n���ARotate?�Z���T??�F�b�N���s���Ă������A
	//     CTC��ʂ̃�?�b�g�A�j��?�V�������ω����Ȃ����߁AGOTO���s��Z���T??�F�b�N���s���悤�ɕύX�����B
	// (6) Program_Init_Code(), Material Recovery��ʂɂ�TR�A??��Map Chamber�����s����ہA
	//     TR2���̃�?�b�g��PM4��Z���Z���T?�ŃE�F�n�L��?�F�b�N���s���Ă����B
	//     TR1, TR2�Ƃ���PM11(PASS1)��Z���Z���T?�ɂăE�F�n�L��?�F�b�N���s���悤�ɕύX�����B
	// (7) Maint_Fine_Tune(),�t?�C���e�B??���O??��2core+2pass�ւ̑Ή�
	//     (7-1)  PASS2��TR�̃e�B??���O??��ǉ��B
	//     (7-2)  PASS1��PASS2(PASS1��?)�̃e�B??���O??��ǉ��B
	//            TR�A??�ɃE�F�n��u���APASS2��Place��Align��Delta Pick��R_Offset��0.1mm(IO�ŕύX��?)�ȓ��ɂȂ�܂Ŏ����ŌJ��Ԃ��B
	//            5��J��Ԃ��Ă�NG�̏ꍇ�́A�t?�C���e�B??���O���I������B
	//			  R_Offset��0.1mm�ȓ��ɂȂ�����PASS1��?�Ńt?�C���e�B??���O���s���B
	//     (7-3)  ����܂ł�PASS��TR�̃t?�C���e�B??���O�́ATR1,TR2�̗������I������Ă�����A�ǂ��炩��I�����A�I������Ȃ��������͎�?����Ȃ��������A
	//			  �������I������Ă���ꍇ�ɂ́ATR1��TR2�̏��ŗ����Ƃ���?����悤�ɕύX�����B
	// (8) PASS2�A���C�i�̃m�b?�p�x�␳??��ǉ��B
	//     �g�pTR,�A??��IO�ɂ��ύX��?�B
	//     (8-1) �␳
	//		Maint_Notch_Angle_Correct(), PASS1�ɃE�F�n��u���ĊJ�n����BPASS1�ɂĕ␳�p�x0�x�ɂăA���C�����APASS2�ɔ����B
	//                                   �E�F�n��PASS1�̒��S�ɂƂȂ�悤�ɂ��������߁AAlign��DeltaPick�������R����?�l(�f�t�H���g0.1mm)�ȉ��ɂȂ�܂ŌJ��Ԃ��B
	//                                   5��Align���Ă���?�l�ɓ���Ȃ��ꍇ�́A�m�b?�p�x�␳NG�Ƃ���B(�V?����?�V�����̏ꍇ�ɂ�5��Align�����R����?�l�ɏ���������)
	//									  PASS2�ŃA���C�����m�b?�p�x0�x����̍�����PASS2�̃A���C�iPLC�ɏ������ށB
	//     (8-2) �m�F
	//		Maint_Notch_Angle_Check(),	 �␳���s��APASS2�ɂ�0�x�ŃA���C�������E�F�n��PASS1�ɔ����B
	//                                   �E�F�n��PASS2�̒��S�ɂƂȂ�悤�ɂ��������߁AAlign��DeltaPick�������R����?�l(�f�t�H���g0.1mm)�ȉ��ɂȂ�܂ŌJ��Ԃ��B
	//                                   5��Align���Ă���?�l�ɓ���Ȃ��ꍇ�́A�m�b?�p�x�␳NG�Ƃ���B(�V?����?�V�����̏ꍇ�ɂ�5��Align�����R����?�l�ɏ���������)
	//									  PASS1�ŃA���C�����m�b?�p�x����ʏ��?������B
	// (9) CCD,Z����??�����2core+2pass�ւ̑Ή�
	//	   (9-1) Maint_CCD_Basis(), TR3�̏������폜�B
	//     (9-2) Maint_CCD_Basis(), �uLL1U, LL2U�̂Ƃ��́CCCD�̊�?�l������s��Ȃ��v�������폜�B
	//     (9-3) Module_Name[16][6]�̏��Ԃ���??����̉�ʂɍ��킹�ĕύX�B
	//           prg_code.c����IO_STR_Map_Table�Œ�?���Ă���IO�̏��Ԃ����l�ɕύX���Ă���B��ʂ̃��W��?�����ɍ��킹�Ċ�??������s���悤�ɂ��������߁B
	// (10) Program_Main(), Init(All)���s���APM11(PASS1)��PM12(PASS2)������?�C?���O��Init����Ȃ��悤�ɕύX�BRUN_SET_FUNCTION��RUN_FUNCTION�ɕύX�����B
	//                      PA11��PM12��Init���ɂ́ATMC_ALGNLOW2_CONTROL��READY�����s����ARBLOW*_CONTROL�ɑ΂���READPOS�����s���邪�A
	//                      RBLOW*_CONTROL�ɑ΂���PM11,PM12���瓯����READPOS�����s�����̂�h�����ߏ��������Ƃ����B
	// (11) Maint_Transfer_Move_Sub(), Tranfer, Batch Transfer��ʂ�Wafer��LP�܂���LL�ɔ�������ꍇ�́A��C�A���C�i���o�R���m�b?�ʒu�����킹��悤�ɂ����B
	//                                 SysAlign��ʂł�LP,LL�ւ�Place�͑�C�A���C�i���o�R�����ɂ��̂܂ܒu���B
	// (12) Maint_Transfer_Clear_Sub(), Transfer, Batch Transfer��ʂɂ�Clear All�����s����ƁAEFEM Arm�ɂ���E�F�n�͑�C�A���C�i���o�R���m�b?�ʒu�����킹�Ă���LP�ɉ������悤�ɂ����B
	//                                  �܂��A���܂ł�EFEM Arm����LP�ɉ�����Ă������A��C�A���C�i�ɂ���E�F�n����LP�ɉ������悤�ɕύX�����B��C�A���C�i, EFEM ��Arm�ɃE�F�n�������Clear All���s�s�ƂȂ�B
	// (13) Maint_Sys_Alignment(), SysAlign��ʂő�C�A���C�i����Pick����Ƃ��A"No Align", "LP Align", "LL1 Align", "LL2 Align"����I���ł���悤�ɕύX�����B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.26(2013.05.07 SUZUKI)" );
	// (1) PASS2�̃m�b?�p�x�␳??�̃��O�f??���c���悤�ɂ����B
	// (1-1) NotchAngleCorrect_Log(), Maint_Notch_Angle_Correct(), Maint_Notch_Angle_Check(), \Histroy\NOTCH_ANGLE_CORRECT.log�ɋL?���c���B
	//       ��ʂ�?�����Ă�����̂̂ق��ɁATR�EArm�EPASS1,PASS2�̃A���C������(X,Y,R)���L?����B
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.27(2013.05.14 SUZUKI)" );
	// (1) �A���C�i�̃m�b?�p�x�␳??�ɂāA�␳�l��Set�l,Read�l�̓ǂݏ����pIO��mdeg�P�ʁ�deg�P��(�ŏ��P��0.1deg)�Ƃ��邽�߂̕ύX
	//     Maint_Notch_Angle_Correct(),Maint_Notch_Angle_Check(), PLC����ǂݍ��񂾒l��1/1000���ĉ�ʂ�?�����Ă������A���̂܂܂̒l����ʂ�?������悤�ɕύX�����B
	//                                                            �܂��APC���珑�����񂾒l��PLC����ǂݍ��񂾒l�̐��l��r�́A����?�ȉ�1���ڎl�̌ܓ�������?�ȉ�2���ڎl�̌ܓ�
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.28(2013.07.01 SUZUKI)" );
	// (1) �A���C�i�̃m�b?�p�x�␳??�ɂāAPASS1,PASS2�̃E�F�n�L����?�F�b�N���Ă��邪�A
	//     CTC.PM11_Wafer_Status, CTC.PM12_Wafer_Status����1��������NG�ɂȂ��Ă������߁A
	//     WaferID��101,201,301�ȊO����NG�������B
	//     CTC.PM11_Wafer_Status, CTC.PM12_Wafer_Status��1������������(Wafer�����݂��Ȃ�������)�ANG�ƂȂ�悤�ύX�����B
	//     2013.07.01 suzuki modify�Ō����B
	//---------------------------------------------------------------------------------------
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.29(2013.11.07 EHA)" );
	// (1) Clear All�ɂ�PASS1,PASS2���g�p���悤�Ƃ����Ƃ������Ƃ�Maint mode�łȂ��ꍇ�C"[CLEAR] whole while()"�̖���loop�ɂȂ�s��C���B
	// (1-1) Maint_Transfer_Clear_Sub(), PASS1,PASS2�̂ǂ��炩��Maint��?�h�ł����OK(�ǂ����Maint��?�h�Ŗ������1004��߂�)������ǉ��B
	// (1-2) Maint_Transfer_Clear(), 1004���߂��Ă����Ƃ��̃��b�Z?�W��ǉ��B
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.30(2014.03.19 SUZUKI)" );
	// (1) �I?�����J�����Ή��B
	// (1-1) Maint_CCD_Basis(), ��??�̂��PM-F�̏ꍇ�ɂ́A�I?�����p�̃v���O��?���g�p����悤�ɕύX�B
	// (1-2) Maint_CCD_Basis(), ��??�̂��PM-F�̏ꍇ�ɂ́AZ�Z���T�̊�??���̂�Ȃ��悤�ɕύX�B
	// (1-3) CCD�Ɋ֘A����IO���̂�ύX(CCD.LL1U.Tr1_Check��Cam.LL1U.Check��)
	// (1-4) Program_Main(), CCD_BASIS_START��CAMERA_BASIS_START, CCD_BASIS_PAUSE��CAMERA_BASIS_PAUSE, CCD_BASIS_RESUME��CAMERA_BASIS_RESUME�ɕύX�B
	// (1-5) CCD_Base(), Maint_CCD_MAINT_INTERFACE_RUN��Maint_CAM_MAINT_INTERFACE_RUN, Maint_CCD_Basis��Maint_CAM_Basis, Maint_CCD_BASIS_Pause��Maint_CAM_BASIS_Pause, Maint_CCD_BASIS_Continue��Maint_CAM_BASIS_Continue�ɕύX�B
	// (1-6) CCD_Base.c��Camera_Base.c, CCD_Base.h��Camera_Base.h�ɕύX�B
	// (1-7) Maint_Material_Recovery_Check_TM(), PM-F�̎��̓J�����B�e�ŃE�F�n�L���𔻒肷��悤�ɕύX�B
	// (1-8) Maint_Fine_Tune(), PM-F��Fine Teaching���ǂ����ŁAZ�Z���T?�܂��̓J������Off�̎���?������?�C�A���O���b�Z?�W��ύX�B
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.31(2014.03.27 SUZUKI)" );
	// (1-1) Mint_Material_Recovery_Check(), LL,TR,PASS,���W��?����Map Chamber����?����ہAWafer Sensor��Off�ɂȂ��Ă�����?�C�A���O���o���Ď��s�ł��Ȃ��悤�ɕύX�B
	//                                       PM-F�̏ꍇ�̓J������Off���Ă�����A���b�Z?�W���o���B
	// (1-2) Maint_Fine_Tune(), Fine Teaching�J�n���ɁAPM-F�̏ꍇ�̓J������Off, PM-F�ȊO�̏ꍇ��Wafer Sensor��Off,PM-F�Ƃ��̑����W��?�������̏ꍇ�̓J������Wafer Sensor��Off���Ă���?��?�C�A���O��?������悤�ɕύX�B
	// (1-3) ?�C�A���O��?������郁�b�Z?�W�́uZ-axis sensor�v���uWafer Sensor�v�ɕύX�B
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.32(2014.08.20 ishikawa)" );
	// �I?�����J���������Ή�
	// ����Word�F2014.08.20
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.33(2015.01.14 suzuki)" );
	// (1) Maint_Fine_Tune(), Maint_Notch_Angle_Correct(), Maint_Notch_Angle_Check()
	//     Camera Control��Off��Fine Teaching����?�����Ƃ��A�uCamera is Off...�v�Ƃ������b�Z?�W��?�������B
	//     ���̃��b�Z?�W��?�������܂܁A�ʂ̉�ʂ�?������ƃ��b�Z?�W�E�B���h�E�������Ă��܂��Ă����B
	//     ���b�Z?�W�E�B���h�E���őO�ʂ�?�����A��ʂ�؂�ւ��Ă�?�����ꂽ�܂܂ƂȂ�悤�ɕύX�����B
	// (2) Maint_Fine_Tune(), �R�����g�A�E�g����Ă���s�v�ȏ������폜�B
	// (3) Maint_Material_Simulation_IO_Check(), �V?����?�V�����̂Ƃ��̂�?�������E�F�n�L���m�F?�C�A���O�����l��?�����ꂽ�܂܂ƂȂ�悤�ɕύX�B
	// (3) Maint_Material_Recovery_Check(), Map Chamber�̂Ƃ���?�������?�C�A���O�����l��?�����ꂽ�܂܂ƂȂ�悤�ɕύX�B
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.34(2015.01.16 Okabe)" );
	// (1)ECID�p��IO�ǉ�
	// ����Word�F20141217
	// (2)Program_Main����Init�ɂ�TR,LL����񏈗������Ȃ����߂�Run_Set_Function��Run_Function�ɕύX�B
	// ����Word�F20150115
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.35(2015.03.26 Ishikawa)" );
	// (1) Init(All) �� PM-G �ǉ�
	// (2) Transfer��ʂ́uClear All�v��PM14�̏�����ǉ�
	// (3) System Alignment��ʁAPM14�Ή�
	// (4) Material Recovery��ʁAPM14�Ή�
	// ����Word�F2015.03.26
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.36(2015.04.02 Ishikawa)" );
	// (1) Fine Teaching��ʁAPM14�Ή�
	// ����Word�F2015.04.02
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.37(2015.04.14 Ishikawa)" );
	// (1) CAMERA_BASIS_START���APM12���g�p����悤�ɕύX
	// (2) CAMERA_BASIS_START��PM-G�Ή�
	// ����Word�F2015.04.14
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.38(2015.04.16 Ishikawa)" );
	// (1) "SYS_FINE_TUNE"���ASet_Aligner_Mode()�֐����Ă΂Ȃ��悤�R�����g�A�E�g�iPM11���������߁j
	//     "SYS_NOTCH_ANGLE_CORRECT"�A"SYS_NOTCH_ANGLE_CHECK"��2PASS�Ŗ����ꍇ�g�p����Ȃ��̂ł��̂܂�
	// ����Word�F2015.04.16
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.39(2015.05.29 Ishikawa)" );
	// (1) �uClear All�v����I/O CTC.TAKT_Mode��Off�ɂ���悤�ɕύX
	// ����Word�F2015.05.29
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.40(2015.06.12 Ishikawa)" );
	// (1) �s��C�� ��V0.09.11(NC7900_57582_CTC_20150604)����̃t�B?�h�o�b�N
	//     ��??����"TMC_ALIGNER_CONTROL"->"TMC_ALIGNER2_CONTROL"
	// ����Word�F2015.06.12
	REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.41(2016.03.31 Suzuki)" );
	// (1) ProB semicon_00_OMR-0282 �Ή��̔h��
	//     TM�ւ�Map Chamber���쎞�ɁATM Arm���ᑬ�ŉ�?����悤�ASET LOAD ON�R?���h���M�����ǉ�
	// (2) ProB semicon_00_OMR-0283 �Ή�
	//     Wafer Occupied/Map Chamber���쎞��MTR7�ւ�SET LOAD�R?���h�ɁA���s�����Ƃ��̃A��??��ǉ�
	// (3) Maint_Material_Recovery_Check_TM()���̃R?�h�����EFunction��

	// �y�����z
	// �J�Z�b�g�E�F�n����|
	//
	// �J�Z�b�g�E�F�n�����F�f�t�H���g��25�B
	//==================================================================
	if ( READ_DIGITAL( IO_Driver_Loding , &CommStatus ) == 0 )	SIMULATION_MODE = TRUE;
	else														SIMULATION_MODE = FALSE;

	// argument����E�F�n�̖����𔲂��o���B�f�t�H���g��25���B
	STR_SEPERATE_CHAR( PROGRAM_ARGUMENT_READ() , '|' ,  aWaferStr , aTempStr , 31 );
	aWafers = 25;
	if( strlen( aWaferStr ) > 0 ) { aWafers = atoi( aWaferStr ); }


	if ( !KWIN_DIALOG_DRIVER_LOADING()) printf("***** Maint Run Dialog Driver Loading Error *****\n");
	//==================================================================
	Maint_SysAlign_SET_RUN_MODE( 1 );
	
	//==================================================================
	Maint_Material_Recovery_SET_RUN_MODE( 2 );

	// TR�A??�E�F�n��MapChamber��?�F�b�N����ۂɎg�p����Z���Z���T��PM�ԍ���ݒ肷��B
	Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( 1 , 11 );
	Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( 2 , 11 );
	Maint_Material_Recovery_SET_TM_CHECKLOAD_PM( 3 , 7 );
	//
	Maint_Material_Recovery_SET_CASSETTE_MAXSLOT( aWafers );
	Maint_Material_Recovery_SET_BUFFER_MAXSLOT( 1 );
	Maint_Material_Recovery_SET_FALSNS_CHECK_STYLE( 0 );
	//
	Maint_Material_Recovery_SET_FUNCTION_ROBOT( 1 , "TMC_ROBOT_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_ROBOT( 2 , "TMC_ROBOT2_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_ROBOT( 3 , "TMC_ROBOT3_CONTROL" );

	// TR�A??�E�F�n��MapChamber��?�F�b�N����ۂɎg�p����Function����ݒ肷��B
	Maint_Material_Recovery_SET_FUNCTION_TMSNS( 1 , "TMC_WFRSNS_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_TMSNS( 2 , "TMC_WFRSNS2_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_TMSNS( 3 , "TMC_WFRSNS3_CONTROL" );

	Maint_Material_Recovery_SET_IO_FMASNS( "R1_WAFER_STS_A" );
	Maint_Material_Recovery_SET_IO_FMBSNS( "R1_WAFER_STS_B" );
	Maint_Material_Recovery_SET_IO_FALSNS( "R1_WAFER_STS_AL" );

	Maint_Material_Recovery_SET_FUNCTION_PMSNS( "PMC_WFRSNS_CONTROL" );

	Maint_Material_Recovery_SET_FUNCTION_MAPPING( 1 , "FM_LP1_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_MAPPING( 2 , "FM_LP2_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_MAPPING( 3 , "FM_LP3_CONTROL" );
	Maint_Material_Recovery_SET_FUNCTION_MAPPING( 4 , "FM_LP4_CONTROL" );
	//==================================================================
	Maint_FineTune_SET_RUN_MODE( 3 );

	Maint_FineTune_SET_FUNCTION_ALIGN( "TMC_ALIGNER_CONTROL" );
	Maint_FineTune_SET_FUNCTION_ALIGN2( "TMC_ALIGNER2_CONTROL" );
	Maint_FineTune_SET_AL_STATION( 11 );
	// 2015.04.02 PM14�ǉ�
	Maint_FineTune_SET_MAX_PM( 11 );
	//Maint_FineTune_SET_MAX_PM( 10 );
	//
	Maint_FineTune_SET_MAX_BM( 2 );
	// 2015.04.02 PM14�ǉ�
	Maint_FineTune_SET_PER_GROUP_PM( "1111222222212" );
	//Maint_FineTune_SET_PER_GROUP_PM( "111122222212" );
	//
	Maint_FineTune_SET_PER_GROUP_BM( "11" );

//==================================================================
#ifdef EQ_TYPE_IARIM2A
	//------------------------------------------------------------------------------------------
	// IARIM2(SingleLL�d�l)
	//------------------------------------------------------------------------------------------
	Maint_FineTune_SET_MAX_BM( 2 );
	Maint_FineTune_SET_PER_GROUP_BM( "11" );
	//---------------------------------------------------
	printf("[%s] EQ TYPE=EQ_TYPE_IARIM2A, %dwafers\n", PROGRAM_FUNCTION_READ(), aWafers);
#else
	//------------------------------------------------------------------------------------------
	// IARIM2(QuadroLL�d�l)
	//------------------------------------------------------------------------------------------
	Maint_FineTune_SET_MAX_BM( 4 );
	Maint_FineTune_SET_PER_GROUP_BM( "1111" );
	//---------------------------------------------------
	printf("[%s] EQ TYPE=EQ_TYPE_IARIM2(default), %dwafers\n", PROGRAM_FUNCTION_READ(), aWafers);
#endif
//==================================================================

	Maint_Transfer_SET_RUN_MODE( 1 );

	//==================================================================
	return TRUE;
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

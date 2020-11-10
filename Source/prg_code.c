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
	// オ?ロンカメラ正式版では削除する↓↓
//	{ "TMC_CCD_CONTROL"				, _K_F_IO	,	TMC_CCD_CONTROL			,	0	} , // 2014.08.20 削除
	// オ?ロンカメラ正式版では削除する↑↑
	// 2014.03.12 suzuki add↓↓
	{ "TMC_CAMERA_CONTROL"			, _K_F_IO	,	TMC_CAMERA_CONTROL		,	0	} ,
	{ "TMC_CAMERA2_CONTROL"			, _K_F_IO	,	TMC_CAMERA2_CONTROL		,	0	} , // 2014.08.20 コメント解除
	// 2014.03.12 suzuki add↑↑
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
	{ "FINETUNE_CHECT_PM14"			, _K_D_IO	,	FINETUNE_CHECT_PM14			,	0	} , // 2015.04.02 PM14追加
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
	{ "FINETUNE_STATUS_PM14"		, _K_D_IO	,	FINETUNE_STATUS_PM14		,	0	} , // 2015.04.02 PM14追加
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
	{ "FINETUNE_OLD_R_POS_PM14"		, _K_A_IO	,	FINETUNE_OLD_R_POS_PM14		,	0	} , // 2015.04.02 PM14追加
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
	{ "FINETUNE_OLD_T_POS_PM14"		, _K_A_IO	,	FINETUNE_OLD_T_POS_PM14		,	0	} , // 2015.04.02 PM14追加
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
	{ "FINETUNE_NEW_R_POS_PM14"		, _K_A_IO	,	FINETUNE_NEW_R_POS_PM14		,	0	} , // 2015.04.02 PM14追加
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
	{ "FINETUNE_NEW_T_POS_PM14"		, _K_A_IO	,	FINETUNE_NEW_T_POS_PM14		,	0	} , // 2015.04.02 PM14追加
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
		// 2015.04.16 PASS1が無いためコメントアウト
		//if ( Set_Aligner_Mode ( 4 , 3 ) == SYS_ABORTED ) Result = 11;	// (4,3) for IARIM2D
		//
		if ( Set_Aligner_Mode2( 3 , 3 ) == SYS_ABORTED ) Result = 12;	// (3,3) for IARIM2D
		if ( Result != 0 ) printf( "FINE_TUNE ERROR_CODE is %d\n" , Result );
		if ( Result == 0 ) Result = Maint_Fine_Tune();
		// 2015.04.16 PASS1が無いためコメントアウト
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
		// 2015.03.26 PM-G 追加 ↓
		if ((( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_UNINIT ) == TRUE )||( MODULE_CHANGE_MODE_POSSIBLE( PM14_ControlStatus , MCM_MAINT ) == TRUE ))&&( READ_DIGITAL( PM14_MAIN_CONTROL , &CommStatus ) == 0 ))
		RUN_SET_FUNCTION( SCHEDULER_MAINT_PM14 , "GO_INIT" );
		// ---------------------↑
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
	// (1) Kornic社2006/10/10版より修正。PM11?PM15のPLACE前のWafer?ェック関数に?える数値が誤っていたため修正。
	// (2) Kornic社2006/10/10版より修正。PM11のGOTOのStation指定が誤っていたため修正。1->11。
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 0.02(2006.11.21 EHA)" );
	// (1) 自動回収プログラ?についてTR2にてPASS1(Aligner)にPlaceしてAlignするように変更(2006年11月10日に発生したWafer割れ対策)
	// (2) 自動回収プログラ?についてFALにウェハがあるときに回収できない問題を修正
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.00(2006.12.13 KornicSystems)" );
	// (1) Konic Systems 2006/12/13 version.
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.01(2006.12.22 KornicSystems)" );
	// (1) Konic Systems 2006/12/22 version.
	//REGIST_FILE_INFO( "I-1330 Function_Maint_Run 1.02(2006.12.25 EHA)" );
	// (1) TR2にてPass1からPickするときのPostPositionを2→1に修正。(Kornic社の2006/12/25版から変更)
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
	// (1) Maint_Fine_Tune(), FineTuningにてLoadLockのみを指定するとPM4にGOTOされる問題対策。
	//     tpに-1が返ってくる。このときは一部の処理を行わない。※処理に問題がないか最終確認をすること。
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
	// (1) Material Recovery, TR1,TR2のMakeOccupiedを実行するときに，MTR7?Load_Status?をOnにするよう修正(今のところMakeEmptyではOffにしない)。 *
	// (2) Material Recovery, MakeOccupiedを実行するとWaferIDとWaferSourceを指定できるように変更。 *
	// (3) Material Recovery, WaferSource設定の指定が間違っていたところを修正。 *
	//     Maint_Material_Recovery_IO_FIND_FM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_PM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_BM_WSRC()
	//     Maint_Material_Recovery_IO_FIND_FAL_WSRC()
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.98(2007.03.13 EHA)" );
	// (1) Program_Main(), "SYS_FINE_TUNE"のAlignerMode設定部分をI-1230Plus用に変更
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 0.99(2007.03.14 EHA)" );
	// (1) Maint_Sys_Alignment(), PASS1(PM11)に対するEXTEND,RETRACTに対応。
	// (2) Maint_Fine_Tune(),Maint_FineTune_IO_FINETUNE_CHECK_STATION_SET for BM (i+14)->(i+15) change.
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.00(2007.03.15 EHA)" );
	// (1) LoadPortの最大枚数を26枚から25枚に変更。
	// (2) Maint_Transfer_Clear_Sub(), ClearのときLL1U,LL2UのWaferを直接EFEMから回収する不具合を修正。
	//     LL1U,LL2UのWaferは，TR1 Pick->PASS1 Place&DeltaPick->LL1L or LL2Lにて回収するように変更。
	// (3) Maint_Transfer_Clear(), SYS_SUCCESSのとき"return SYS_SUCCESS"になっていなかった部分を訂正。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.01(2007.03.22 KornicSystems)" );
	// "20070316_fromKornic"からの変更
	// (1) CCD_Base.c TM Order and Module Name was changed for I-1230 "2007.03.04 KornicSystems"
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.02(2007.03.30 EHA)" );
	// (1) Maint_Fine_Tune(), PASS1(Aligner)のときのMaint_Material_Recovery_Check_TM()を削除。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.03(2007.04.02 KornicSystems)" );
	// (1) 「ModuleのModeがUninitのとき，Maint(All)を押すとGO_MAINTのみを行いMaintになってしまう。
    //     UnInitのところは，GO_MAINTしないようにしてほしい。」(ActionItemNo.102)の対応
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.04(2007.04.04 EHA)" );
	// (1) Maint_CCD_Basis(), 基?値測定のためのRobot動作からUPを削除。
	// (2) Maint_CCD_Basis(), 基?値測定の対象がLoadLockのときPick,Placeを実行しないようにする。
	// (3) Maint_CCD_Basis(), LL1U, LL2Uのときは，CCDの基?値測定を行わない
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.05(2007.04.11 EHA)" );
	// (1) Maint_Transfer_Move_Check(), TR2のア??選択をBア??にしてBア??のWaferをH-chにPlaceしようとすると
	//     "PM(for TM2) Pick Robot has wafer Error[2]"(=1101)が?示されてH-chが選択できない問題の対策。
	//     "Checking Part 3"のPMの?ェックで"i=0"のときのみ"TR_Pick_Arm_Check"を行うように変更。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.06(2007.04.17 EHA)" );
	// (1) Maint_Sys_Alignment(), Place動作のときTR2のWafer?ェックに間違いがあっため訂正。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.07(2007.04.27 sawatari)" );
	// Clear All時のpost position変更。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.08(2007.05.08 Chigira)" );
	// (1) Maint_Sys_Alignment(), Pick,Place動作以外は選択先モジュ?ルの状態を見ないよう変更。
	// (2) 各Maint用Functionを対象モジュ?ルがStandby時には実行できないよう変更(判定関数変更)
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.09(2007.07.18 EHA)" );
	// (1) Maint_Transfer_Move(), SYS_SUCCESSの前にreturnが無かった部分を訂正。
	// (2) Maint_Transfer_Batch(), SYS_SUCCESSの前にreturnが無かった部分を訂正。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.10(2007.07.20 EHA)" );
	// (1) Maint_Material_Simulation_IO_Check(), SIMULATION_MODEのとき，FAL,FMのウェハ?ェックが正しく動作しなかった問題を修正。
	// (2) スペル?スを訂正。"Srouce"->"Source"
	// (3) Program_Init_Code(), Waferの枚数設定をargumentからできるように改善。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.11(2007.10.11 SuzukiMi)" );
	// (1) Slot指定?イアログの最大値をMTLRECV_CASSETTE_MAX_SLOTで任意に変更できるように修正。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.11(2007.11.21 Sawatari)" );
	// (1) 「Init(All)」の使用可?条件を「Un-Init」「Maint」に変更。					※ 猿渡tと鈴木(光)tの変更バ?ジョンが重複している。要整理 ※
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.12(2007.12.09 KornicSystems)" );
	// (1) ClearALLのとき?ェックしたPM以外を回収できるように変更。
	// (1-1) CLEAR_CONTROL_IS_POSSIBLE_PM(), 新規作成
	// (1-2) Maint_TRansfer_Move_Sub(), ClearALLのときに?ェックしたPM以外を回収するように変更。停?処理を即時停?できるよう変更。
	// (1-3) Maint_Transfer_Move_Sub(), 停?処理を即時停?できるよう変更。
	//REGIST_FILE_INFO( "I-1230Plus Function_Maint_Run 1.13(2007.12.16 EHA)" );
	// (1) Maint_Transfer_Clear_Sub(), ClearSkipの判定でPM14についてSkipできなかった不具合を修正。
	// (2) Maint_Transfer_Clear_Pre_Check_Error(), PM14のみ判定から漏れていた部分を修正。
	// (3) Maint_Transfer_Clear(), res=1002に対して詳細なメッセ?ジを追加。※ 順次追加すること。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.14(2008.01.22 EHA)" );
	// (1) 装置?成により下記の2つに対応した実行フ?イルを別々に作成するようにする。
	// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
	// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe
	// 【注意】：今後??スを書き換えコンパイルするときにはバッ?ビルドを実行するようにすること。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.15(2008.02.07 EHA)" );
	// (1) MaterialRecovery画面にてIDの設定のときLoadPortの選択をUnuseの部分は?示しないように変更。
	// (1-1) Set_LoadPort_Select_Map(), 新規追加。LoadPortの選択をUnuseにあわせて変更するための関数。
	// (1-2) Maint_Material_Recovery_Check_TM(),Maint_Material_Recovery_Check_PM(),Maint_Material_Recovery_Check_BM(),Maint_Material_Recovery_Check_FAL(),Maint_Material_Recovery_Check_FM()
	//        LoadPort選択?式をSet_LoadPort_Select_Map()を使用するよう変更。
	// (2) 起動時にコア装置?イプとLoadPortのウェハ枚数設定をコン??ルに?示するように変更。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.16(2008.04.23 EHA)" );
	// (1) Maint_Transfer_Batch_Sub(), BatchTransfer画面にてTR2側からLP,LLに回収することができずにBatchMoveErrorが起きてしまう問題の修正。
	// (2) Maint_Transfer_Batch_Sub(), BatchTransfer画面にてTR側からLPに行くル?トがUnload側になっていなかった問題の修正。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.17(2008.05.17 EHA)" );
	// (1) BatchTransfer画面に設定内容をリセットするReset??を追加。
	// (1-1) Program_Main(), "BATCH_IO_ALL_CLEAR"メッセ?ジが届いたらMaint_Batch_IO_All_ClearをCallする。
	// (1-2) Maint_Batch_IO_All_Clear(), Batch Transfer の IOを初期値に戻す処理を行う。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.18(2008.06.12 SAWATARI)" );
	// (1) Module_Status Maint_Material_Recovery_Check_FAL(),Material Recovery画面でAL(ATM)のMake OccupiedでSlot設定のIO?示の文字化けを修正。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.19(2008.08.08 EHA)" );
	// (1) Maint_CCD_Basis(), PASS1(Aligner)のアライン動作の前にRobotをRetractする動作を追加。
	// (2) Maint_CCD_Basis(), 基??測定動作する前にア??が縮位置になっていなかったらホ??動作をすること。
	// (2) Maint_Sys_Alignment(), PASS1(Aligner)のアライン動作の前にRobotをRetractする動作を追加。
	// (3) Maint_Transfer_Move_Sub(), PASS1(Aligner)のアライン動作の前にRobotをRetractする動作を追加。
	// (4) Maint_Transfer_Clear_Sub(), PASS1(Aligner)のアライン動作の前にRobotをRetractする動作を追加。
	// (5) Maint_Transfer_Clear_Sub(), クリア動作する前にア??が縮位置になっていなかったらホ??動作をすること
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.20(2008.08.27 SUZUKIMI)" );
	// (1) Program_Main(), Batch Process中(MAIN_CONTROL=1)のモジュ?ルに対してはInit(All),Standby(All),Maint(All)が効かないように変更。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.21(2008.09.19 Chigira)" );
	// (1) Maint_Transfer_Clear_Sub(), 回収用のLLが全てMaintenanceModeでない場合には途中で終了するよう変更。
	// (1) Maint_Transfer_Clear(), AllClearのエラ?メッセ?ジを追加。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.22(2008.10.17 Suzuki)" );
	// (1) Module_Status Maint_CCD_Basis(),CCD・Z軸基??設定時，CCDカメラが存在しない場合はZ軸の基??のみ測定するように変更。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.23(2009.06.02 Suzuki)" );
	// (1) Maint_Transfer_Clear_Pre_Check_Error(),Wafer Dummy SchedulerでClear AllにてDummy Waferが回収できない問題を修正。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.24(2009.09.23 Sawatari)" );
	// (1) Maint_Material_Recovery_Check_TM(),Maint_Material_Simulation_IO_Check()
	//     Z-axis SensorがOFFの時、TM*.Wafer_Resultを?ェックしない為"RealWafer"が更新されない対策。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.25(2013.03.27 SUZUKI)" );
	// (1) 2core+2passへの対応
	// (1-1) IO_Name_String_Map, IO名称の変更
	//       TR2.PM12.CCD_EXISTS→TR1.PM12.CCD_EXISTS, TR1.PM13.CCD_EXISTS→TR2.PM13.CCD_EXISTS
	// (1-2) Maint_Sys_Alignment(), LLC,LLD,PM14の削除。PM12(PASS2)の追加。
	// (1-3) ClearAll時、TR1側,TR2側のウェハ共にPASS1,PASS2の順で置かれる。
	// (1-4) Maint_Material_Recovery_Map_Sub(),Maint_Material_Recovery_Map(), LLC,LLD,PM14の削除。PM12(PASS2)の追加。
	// (1-5) Maint_Transfer_Batch_Sub(), BatchTransferにて、TR1→TR2はPASS1を、TR2→TR1はPASS2を優先して使用するように変更。
	//       (優先するPASSにウェハがある、またはMaintモ?ドでない場合は、もう片方のPASSを経由する。)
	// (2) Maint_Transfer_Batch_Sub にて、経路作成の際にLL1を通る経路のみだったものを、
	//     LL1およびLL2の状態(ウェハがない、かつMaintモ?ドか)を?ェックし、経路を決定するように変更。
	//     万が一どちらもが条件を満たしていないときはエラ?(return 8)を返すように変更。
	// (3) Source Station,または Destination Station にLL1またはLL2を設定した際に、BatcthLoadLockでないにもかかわらず、
	//	   SlotNO が?作できてしまうことにより発生する不具合に対応。
	//  ※ 会社ごとにif文内の条件が変わるので注意(使用するBMの数が異なるため)
	// (4) Material Recovery画面のMap Chamber
	//	   SlotNO が?作できてしまうことにより発生する不具合に対応。
	//  ※ 会社ごとにif文内の条件が変わるので注意(使用するBMの数が異なるため)
	// (5) Maint_Material_Recovery_Check_TM(), Material Recovery画面にてTRア??のMap Chamberを実行する際、
	//     TMC_RBLOW*_CONTROLに"CHECKLOAD"コ?ンドを渡し、Rotate?センサ??ェックを行っていたが、
	//     CTC画面のロ?ットアニメ?ションが変化しないため、GOTO実行後センサ??ェックを行うように変更した。
	// (6) Program_Init_Code(), Material Recovery画面にてTRア??のMap Chamberを実行する際、
	//     TR2側のロ?ットはPM4のZ軸センサ?でウェハ有無?ェックを行っていた。
	//     TR1, TR2ともにPM11(PASS1)のZ軸センサ?にてウェハ有無?ェックを行うように変更した。
	// (7) Maint_Fine_Tune(),フ?インティ??ング??の2core+2passへの対応
	//     (7-1)  PASS2⇔TRのティ??ング??を追加。
	//     (7-2)  PASS1⇔PASS2(PASS1基?)のティ??ング??を追加。
	//            TRア??にウェハを置き、PASS2にPlace→Align→Delta PickをR_Offsetが0.1mm(IOで変更可?)以内になるまで自動で繰り返す。
	//            5回繰り返してもNGの場合は、フ?インティ??ングを終了する。
	//			  R_Offsetが0.1mm以内になったらPASS1基?でフ?インティ??ングを行う。
	//     (7-3)  これまではPASS⇔TRのフ?インティ??ングは、TR1,TR2の両方が選択されていたら、どちらかを選択し、選択されなかった方は実?されなかったが、
	//			  両方が選択されている場合には、TR1→TR2の順で両方とも実?するように変更した。
	// (8) PASS2アライナのノッ?角度補正??を追加。
	//     使用TR,ア??はIOにより変更可?。
	//     (8-1) 補正
	//		Maint_Notch_Angle_Correct(), PASS1にウェハを置いて開始する。PASS1にて補正角度0度にてアラインし、PASS2に搬送。
	//                                   ウェハがPASS1の中心にとなるようにしたいため、Align→DeltaPickをずれ量Rが基?値(デフォルト0.1mm)以下になるまで繰り返す。
	//                                   5回Alignしても基?値に入らない場合は、ノッ?角度補正NGとする。(シ?ュレ?ションの場合には5回AlignするとRを基?値に書き換える)
	//									  PASS2でアラインしノッ?角度0度からの差分をPASS2のアライナPLCに書き込む。
	//     (8-2) 確認
	//		Maint_Notch_Angle_Check(),	 補正実行後、PASS2にて0度でアラインしたウェハをPASS1に搬送。
	//                                   ウェハがPASS2の中心にとなるようにしたいため、Align→DeltaPickをずれ量Rが基?値(デフォルト0.1mm)以下になるまで繰り返す。
	//                                   5回Alignしても基?値に入らない場合は、ノッ?角度補正NGとする。(シ?ュレ?ションの場合には5回AlignするとRを基?値に書き換える)
	//									  PASS1でアラインしノッ?角度を画面上に?示する。
	// (9) CCD,Z軸基??測定の2core+2passへの対応
	//	   (9-1) Maint_CCD_Basis(), TR3の処理を削除。
	//     (9-2) Maint_CCD_Basis(), 「LL1U, LL2Uのときは，CCDの基?値測定を行わない」処理を削除。
	//     (9-3) Module_Name[16][6]の順番を基??測定の画面に合わせて変更。
	//           prg_code.c内のIO_STR_Map_Tableで定?しているIOの順番も同様に変更している。画面のモジュ?ル順に合わせて基??測定を行うようにしたいため。
	// (10) Program_Main(), Init(All)実行時、PM11(PASS1)とPM12(PASS2)が同じ?イ?ングでInitされないように変更。RUN_SET_FUNCTION→RUN_FUNCTIONに変更した。
	//                      PA11とPM12のInit時には、TMC_ALGNLOW2_CONTROLでREADYが実行され、RBLOW*_CONTROLに対してREADPOSを実行するが、
	//                      RBLOW*_CONTROLに対してPM11,PM12から同時にREADPOSが実行されるのを防ぐため順次処理とした。
	// (11) Maint_Transfer_Move_Sub(), Tranfer, Batch Transfer画面でWaferをLPまたはLLに搬送する場合は、大気アライナを経由しノッ?位置を合わせるようにした。
	//                                 SysAlign画面でのLP,LLへのPlaceは大気アライナを経由せずにそのまま置く。
	// (12) Maint_Transfer_Clear_Sub(), Transfer, Batch Transfer画面にてClear Allを実行すると、EFEM Armにあるウェハは大気アライナを経由しノッ?位置を合わせてからLPに回収するようにした。
	//                                  また、今まではEFEM ArmからLPに回収していたが、大気アライナにあるウェハからLPに回収するように変更した。大気アライナ, EFEM 両ArmにウェハがあるとClear All実行不可となる。
	// (13) Maint_Sys_Alignment(), SysAlign画面で大気アライナからPickするとき、"No Align", "LP Align", "LL1 Align", "LL2 Align"から選択できるように変更した。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.26(2013.05.07 SUZUKI)" );
	// (1) PASS2のノッ?角度補正??のログデ??を残すようにした。
	// (1-1) NotchAngleCorrect_Log(), Maint_Notch_Angle_Correct(), Maint_Notch_Angle_Check(), \Histroy\NOTCH_ANGLE_CORRECT.logに記?を残す。
	//       画面に?示しているもののほかに、TR・Arm・PASS1,PASS2のアライン結果(X,Y,R)を記?する。
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.27(2013.05.14 SUZUKI)" );
	// (1) アライナのノッ?角度補正??にて、補正値のSet値,Read値の読み書き用IOをmdeg単位→deg単位(最小単位0.1deg)とするための変更
	//     Maint_Notch_Angle_Correct(),Maint_Notch_Angle_Check(), PLCから読み込んだ値を1/1000して画面に?示していたが、そのままの値を画面に?示するように変更した。
	//                                                            また、PCから書き込んだ値とPLCから読み込んだ値の数値比較は、少数?以下1桁目四捨五入→小数?以下2桁目四捨五入
	//REGIST_FILE_INFO( "IARIM2 Function_Maint_Run 1.28(2013.07.01 SUZUKI)" );
	// (1) アライナのノッ?角度補正??にて、PASS1,PASS2のウェハ有無を?ェックしているが、
	//     CTC.PM11_Wafer_Status, CTC.PM12_Wafer_Statusが≠1だったらNGになっていたため、
	//     WaferIDが101,201,301以外だとNGだった。
	//     CTC.PM11_Wafer_Status, CTC.PM12_Wafer_Statusが1未満だったら(Waferが存在しなかったら)、NGとなるよう変更した。
	//     2013.07.01 suzuki modifyで検索可。
	//---------------------------------------------------------------------------------------
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.29(2013.11.07 EHA)" );
	// (1) Clear AllにてPASS1,PASS2を使用しようとしたとき両方ともMaint modeでない場合，"[CLEAR] whole while()"の無限loopになる不具合修正。
	// (1-1) Maint_Transfer_Clear_Sub(), PASS1,PASS2のどちらかがMaintモ?ドであればOK(どちらもMaintモ?ドで無ければ1004を戻す)処理を追加。
	// (1-2) Maint_Transfer_Clear(), 1004が戻ってきたときのメッセ?ジを追加。
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.30(2014.03.19 SUZUKI)" );
	// (1) オ?ロンカメラ対応。
	// (1-1) Maint_CCD_Basis(), 基??採りでPM-Fの場合には、オ?ロン用のプログラ?を使用するように変更。
	// (1-2) Maint_CCD_Basis(), 基??採りでPM-Fの場合には、Zセンサの基??を採らないように変更。
	// (1-3) CCDに関連するIO名称を変更(CCD.LL1U.Tr1_Check→Cam.LL1U.Check等)
	// (1-4) Program_Main(), CCD_BASIS_START→CAMERA_BASIS_START, CCD_BASIS_PAUSE→CAMERA_BASIS_PAUSE, CCD_BASIS_RESUME→CAMERA_BASIS_RESUMEに変更。
	// (1-5) CCD_Base(), Maint_CCD_MAINT_INTERFACE_RUN→Maint_CAM_MAINT_INTERFACE_RUN, Maint_CCD_Basis→Maint_CAM_Basis, Maint_CCD_BASIS_Pause→Maint_CAM_BASIS_Pause, Maint_CCD_BASIS_Continue→Maint_CAM_BASIS_Continueに変更。
	// (1-6) CCD_Base.c→Camera_Base.c, CCD_Base.h→Camera_Base.hに変更。
	// (1-7) Maint_Material_Recovery_Check_TM(), PM-Fの時はカメラ撮影でウェハ有無を判定するように変更。
	// (1-8) Maint_Fine_Tune(), PM-FのFine Teachingかどうかで、Zセンサ?またはカメラがOffの時に?示する?イアログメッセ?ジを変更。
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.31(2014.03.27 SUZUKI)" );
	// (1-1) Mint_Material_Recovery_Check(), LL,TR,PASS,モジュ?ルのMap Chamberを実?する際、Wafer SensorがOffになっていたら?イアログを出して実行できないように変更。
	//                                       PM-Fの場合はカメラがOffしていたら、メッセ?ジを出す。
	// (1-2) Maint_Fine_Tune(), Fine Teaching開始時に、PM-Fの場合はカメラがOff, PM-F以外の場合はWafer SensorがOff,PM-Fとその他モジュ?ル同時の場合はカメラとWafer SensorがOffしている?の?イアログを?示するように変更。
	// (1-3) ?イアログに?示されるメッセ?ジの「Z-axis sensor」を「Wafer Sensor」に変更。
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.32(2014.08.20 ishikawa)" );
	// オ?ロンカメラ正式対応
	// 検索Word：2014.08.20
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.33(2015.01.14 suzuki)" );
	// (1) Maint_Fine_Tune(), Maint_Notch_Angle_Correct(), Maint_Notch_Angle_Check()
	//     Camera ControlがOffでFine Teachingを実?したとき、「Camera is Off...」というメッセ?ジが?示される。
	//     このメッセ?ジを?示したまま、別の画面を?示するとメッセ?ジウィンドウが消えてしまっていた。
	//     メッセ?ジウィンドウを最前面に?示し、画面を切り替えても?示されたままとなるように変更した。
	// (2) Maint_Fine_Tune(), コメントアウトされている不要な処理を削除。
	// (3) Maint_Material_Simulation_IO_Check(), シ?ュレ?ションのときのみ?示されるウェハ有無確認?イアログも同様に?示されたままとなるように変更。
	// (3) Maint_Material_Recovery_Check(), Map Chamberのときに?示される?イアログも同様に?示されたままとなるように変更。
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.34(2015.01.16 Okabe)" );
	// (1)ECID用のIO追加
	// 検索Word：20141217
	// (2)Program_Main内のInitにてTR,LLを並列処理させないためにRun_Set_FunctionをRun_Functionに変更。
	// 検索Word：20150115
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.35(2015.03.26 Ishikawa)" );
	// (1) Init(All) に PM-G 追加
	// (2) Transfer画面の「Clear All」にPM14の処理を追加
	// (3) System Alignment画面、PM14対応
	// (4) Material Recovery画面、PM14対応
	// 検索Word：2015.03.26
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.36(2015.04.02 Ishikawa)" );
	// (1) Fine Teaching画面、PM14対応
	// 検索Word：2015.04.02
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.37(2015.04.14 Ishikawa)" );
	// (1) CAMERA_BASIS_START時、PM12を使用するように変更
	// (2) CAMERA_BASIS_STARTのPM-G対応
	// 検索Word：2015.04.14
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.38(2015.04.16 Ishikawa)" );
	// (1) "SYS_FINE_TUNE"時、Set_Aligner_Mode()関数を呼ばないようコメントアウト（PM11が無いため）
	//     "SYS_NOTCH_ANGLE_CORRECT"、"SYS_NOTCH_ANGLE_CHECK"は2PASSで無い場合使用されないのでそのまま
	// 検索Word：2015.04.16
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.39(2015.05.29 Ishikawa)" );
	// (1) 「Clear All」時にI/O CTC.TAKT_ModeをOffにするように変更
	// 検索Word：2015.05.29
	//REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.40(2015.06.12 Ishikawa)" );
	// (1) 不具合修正 ※V0.09.11(NC7900_57582_CTC_20150604)からのフィ?ドバック
	//     基??測定"TMC_ALIGNER_CONTROL"->"TMC_ALIGNER2_CONTROL"
	// 検索Word：2015.06.12
	REGIST_FILE_INFO( "IARIM-NX Function_Maint_Run 1.41(2016.03.31 Suzuki)" );
	// (1) ProB semicon_00_OMR-0282 対応の派生
	//     TMへのMap Chamber動作時に、TM Armが低速で回?するよう、SET LOAD ONコ?ンド送信動作を追加
	// (2) ProB semicon_00_OMR-0283 対応
	//     Wafer Occupied/Map Chamber動作時のMTR7へのSET LOADコ?ンドに、失敗したときのアラ??を追加
	// (3) Maint_Material_Recovery_Check_TM()内のコ?ド整理・Function化

	// 【書式】
	// カセットウェハ枚数|
	//
	// カセットウェハ枚数：デフォルトは25。
	//==================================================================
	if ( READ_DIGITAL( IO_Driver_Loding , &CommStatus ) == 0 )	SIMULATION_MODE = TRUE;
	else														SIMULATION_MODE = FALSE;

	// argumentからウェハの枚数を抜き出す。デフォルトは25枚。
	STR_SEPERATE_CHAR( PROGRAM_ARGUMENT_READ() , '|' ,  aWaferStr , aTempStr , 31 );
	aWafers = 25;
	if( strlen( aWaferStr ) > 0 ) { aWafers = atoi( aWaferStr ); }


	if ( !KWIN_DIALOG_DRIVER_LOADING()) printf("***** Maint Run Dialog Driver Loading Error *****\n");
	//==================================================================
	Maint_SysAlign_SET_RUN_MODE( 1 );
	
	//==================================================================
	Maint_Material_Recovery_SET_RUN_MODE( 2 );

	// TRア??ウェハをMapChamberで?ェックする際に使用するZ軸センサのPM番号を設定する。
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

	// TRア??ウェハをMapChamberで?ェックする際に使用するFunction名を設定する。
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
	// 2015.04.02 PM14追加
	Maint_FineTune_SET_MAX_PM( 11 );
	//Maint_FineTune_SET_MAX_PM( 10 );
	//
	Maint_FineTune_SET_MAX_BM( 2 );
	// 2015.04.02 PM14追加
	Maint_FineTune_SET_PER_GROUP_PM( "1111222222212" );
	//Maint_FineTune_SET_PER_GROUP_PM( "111122222212" );
	//
	Maint_FineTune_SET_PER_GROUP_BM( "11" );

//==================================================================
#ifdef EQ_TYPE_IARIM2A
	//------------------------------------------------------------------------------------------
	// IARIM2(SingleLL仕様)
	//------------------------------------------------------------------------------------------
	Maint_FineTune_SET_MAX_BM( 2 );
	Maint_FineTune_SET_PER_GROUP_BM( "11" );
	//---------------------------------------------------
	printf("[%s] EQ TYPE=EQ_TYPE_IARIM2A, %dwafers\n", PROGRAM_FUNCTION_READ(), aWafers);
#else
	//------------------------------------------------------------------------------------------
	// IARIM2(QuadroLL仕様)
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

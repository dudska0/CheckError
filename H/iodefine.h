//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe  = IARIM-NX
//
// File Name : iodefine.h
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#ifndef IODEFINE_H
#define IODEFINE_H
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
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------
#define RUNMODE_TMSIDE_WHEN_BM_PICK		4	// 2006.10.25
//------------------------------------------------------------------------------------------
BOOL MODULE_CONTROL_IS_POSSIBLE_CM( int ch );
BOOL MODULE_CONTROL_IS_POSSIBLE_BM( int ch );
BOOL MODULE_CONTROL_IS_POSSIBLE_PM( int ch );
BOOL MODULE_CONTROL_IS_POSSIBLE_TM( int ch );
BOOL MODULE_CONTROL_IS_POSSIBLE_FM();
BOOL MODULE_CONTROL_IS_POSSIBLE_FAL();

BOOL CLEAR_CONTROL_IS_POSSIBLE_PM( int ch ); // 2007.12.09

Module_Status Set_Aligner_Mode2( int id , int mode );
//------------------------------------------------------------------------------------------

enum {
	CTL_IDLE ,
	CTL_RUNNING ,
	CTL_PAUSING ,
	CTL_PAUSED ,
	CTL_ABORTING ,
	CTL_DISABLE ,
	CTL_WAITING ,
	CTL_WAIT_HANDOFF
};

// 2007.03.29 Kornic - Module Control Mode
enum {
	MCM_UNUSE ,
	MCM_UNINIT ,
	MCM_GO_INIT ,
	MCM_MAINT ,
	MCM_GO_STANDBY ,
	MCM_STANDBY , 
	MCM_GO_MAINT ,
	MCM_CTCINUSE ,
	MCM_CTCMAINT ,
	MCM_RUNPROCESS ,
	MCM_RUNMAINT ,
	MCM_OFFLINE
};

typedef enum {
	IO_Driver_Loding	,
	//============================================================================
	SCHEDULER			,
	CTC_TR_STATUS		,

	INFO_SAVE			,
	//------------------------------------------------------------------------------------------
	SCHEDULER_ERROR		,
	TMC_STANDBY_CONTROL	,
	//------------------------------------------------------------------------------------------
	SCHEDULER_MAINT_BM1	,
	SCHEDULER_MAINT_BM2	,	
	SCHEDULER_MAINT_BM3	,	
	SCHEDULER_MAINT_BM4	,	
	SCHEDULER_MAINT_PM1	,
	SCHEDULER_MAINT_PM2	,
	SCHEDULER_MAINT_PM3	,
	SCHEDULER_MAINT_PM4	,
	SCHEDULER_MAINT_PM5	,
	SCHEDULER_MAINT_PM6	,
	SCHEDULER_MAINT_PM7	,
	SCHEDULER_MAINT_PM8	,
	SCHEDULER_MAINT_PM9	,
	SCHEDULER_MAINT_PM10	,
	SCHEDULER_MAINT_PM11	,
	SCHEDULER_MAINT_PM12	,
	SCHEDULER_MAINT_PM13	,
	SCHEDULER_MAINT_PM14	,
//	SCHEDULER_MAINT_PM15	,
	SCHEDULER_MAINT_FM	,
	SCHEDULER_MAINT_TM	,
	SCHEDULER_MAINT_TM2	,
//	SCHEDULER_MAINT_TM3	,
	//------------------------------------------------------------------------------------------
	TMC_WFRSNS_CONTROL	,
	//------------------------------------------------------------------------------------------
	SYS_AL_CONTROL		,

	SYS_AL_Arm			,
	SYS_AL_Station		,
	SYS_AL_Slot			,

	//------------------------------------------------------------------------------------------
	MTL_RECV_CONTROL	,

	MTL_RECV_Arm		,
	MTL_RECV_Station	,
	MTL_RECV_Slot		,
	MTL_RECV_Message	,

	//------------------------------------------------------------------------------------------
	MTR_CONTROL			,

	TR_CM1_ORDER		,
	TR_CM2_ORDER		,
	TR_CM3_ORDER		,
	TR_CM4_ORDER		,

	TR_FAL_ORDER		,

	TR_BM1_ORDER		,
	TR_BM2_ORDER		,
	TR_BM3_ORDER		,
	TR_BM4_ORDER		,

	TR_PM1_ORDER		,
	TR_PM2_ORDER		,
	TR_PM3_ORDER		,
	TR_PM4_ORDER		,
	TR_PM5_ORDER		,
	TR_PM6_ORDER		,
	TR_PM7_ORDER		,
	TR_PM8_ORDER		,
	TR_PM9_ORDER		,
	TR_PM10_ORDER		,

	TR_PM11_ORDER		,
	TR_PM12_ORDER		,
//	TR_PM13_ORDER		,
	TR_PM14_ORDER		,
//	TR_PM15_ORDER		,

	TR_PM11_2_ORDER		,
	TR_PM12_2_ORDER		,
//	TR_PM13_2_ORDER		,
//	TR_PM14_2_ORDER		,
//	TR_PM15_2_ORDER		,

//	TR_PM11_3_ORDER		,
//	TR_PM12_3_ORDER		,
//	TR_PM13_3_ORDER		,
//	TR_PM14_3_ORDER		,
//	TR_PM15_3_ORDER		,

	TR_FM_ORDER			,
	TR_TM1_ORDER		,
	TR_TM2_ORDER		,
//	TR_TM3_ORDER		,

	TR_CM1_ORDER2		,
	TR_CM2_ORDER2		,
	TR_CM3_ORDER2		,
	TR_CM4_ORDER2		,

	TR_FAL_ORDER2		,

	TR_BM1_ORDER2		,
	TR_BM2_ORDER2		,
	TR_BM3_ORDER2		,
	TR_BM4_ORDER2		,

	TR_PM1_ORDER2		,
	TR_PM2_ORDER2		,
	TR_PM3_ORDER2		,
	TR_PM4_ORDER2		,
	TR_PM5_ORDER2		,
	TR_PM6_ORDER2		,
	TR_PM7_ORDER2		,
	TR_PM8_ORDER2		,
	TR_PM9_ORDER2		,
	TR_PM10_ORDER2		,
	TR_PM11_ORDER2		,
	TR_PM12_ORDER2		,
//	TR_PM13_ORDER2		,
	TR_PM14_ORDER2		,
//	TR_PM15_ORDER2		,

	TR_PM11_2_ORDER2		,
	TR_PM12_2_ORDER2		,
//	TR_PM13_2_ORDER2		,
//	TR_PM14_2_ORDER2		,
//	TR_PM15_2_ORDER2		,

//	TR_PM11_3_ORDER2		,
//	TR_PM12_3_ORDER2		,
//	TR_PM13_3_ORDER2		,
//	TR_PM14_3_ORDER2		,
//	TR_PM15_3_ORDER2		,

	TR_FM_ORDER2		,
	TR_TM1_ORDER2		,
	TR_TM2_ORDER2		,
//	TR_TM3_ORDER2		,

	TR_CM1_SLOT			,
	TR_CM2_SLOT			,
	TR_CM3_SLOT			,
	TR_CM4_SLOT			,

	TR_FM_ARM			,
	TR_TM1_ARM			,
	TR_TM2_ARM			,
//	TR_TM3_ARM			,

	TR_ALIGNING			,
	TR_STATUS			,

	//========================================================================================================
	BatchTR_SrcStn1		,
	BatchTR_SrcStn2		,
	BatchTR_SrcStn3		,
	BatchTR_SrcStn4		,
	BatchTR_SrcStn5		,
	BatchTR_SrcStn6		,
	BatchTR_SrcStn7		,
	BatchTR_SrcStn8		,
	BatchTR_SrcStn9		,
	BatchTR_SrcStn10	,

	BatchTR_SrcSlot1	,
	BatchTR_SrcSlot2	,
	BatchTR_SrcSlot3	,
	BatchTR_SrcSlot4	,
	BatchTR_SrcSlot5	,
	BatchTR_SrcSlot6	,
	BatchTR_SrcSlot7	,
	BatchTR_SrcSlot8	,
	BatchTR_SrcSlot9	,
	BatchTR_SrcSlot10	,

	BatchTR_DestStn1	,
	BatchTR_DestStn2	,
	BatchTR_DestStn3	,
	BatchTR_DestStn4	,
	BatchTR_DestStn5	,
	BatchTR_DestStn6	,
	BatchTR_DestStn7	,
	BatchTR_DestStn8	,
	BatchTR_DestStn9	,
	BatchTR_DestStn10	,

	BatchTR_DestSlot1	,
	BatchTR_DestSlot2	,
	BatchTR_DestSlot3	,
	BatchTR_DestSlot4	,
	BatchTR_DestSlot5	,
	BatchTR_DestSlot6	,
	BatchTR_DestSlot7	,
	BatchTR_DestSlot8	,
	BatchTR_DestSlot9	,
	BatchTR_DestSlot10	,

	FA_STATUS_MDL_CM1	,
	FA_STATUS_MDL_CM2	,
	FA_STATUS_MDL_CM3	,
	FA_STATUS_MDL_CM4	,

	FA_STATUS_MDL_PM1	,
	FA_STATUS_MDL_PM2	,
	FA_STATUS_MDL_PM3	,
	FA_STATUS_MDL_PM4	,
	FA_STATUS_MDL_PM5	,
	FA_STATUS_MDL_PM6	,
	FA_STATUS_MDL_PM7	,
	FA_STATUS_MDL_PM8	,
	FA_STATUS_MDL_PM9	,
	FA_STATUS_MDL_PM10	,
	FA_STATUS_MDL_PM11	,
	FA_STATUS_MDL_PM12	,
	FA_STATUS_MDL_PM13	,
	FA_STATUS_MDL_PM14	,
//	FA_STATUS_MDL_PM15	,

	FA_STATUS_MDL_BM1	,
	FA_STATUS_MDL_BM2	,
	FA_STATUS_MDL_BM3	,
	FA_STATUS_MDL_BM4	,

	FA_STATUS_MDL_FAL	,

	FA_STATUS_MDL_TM	,
	FA_STATUS_MDL_TM2	,
//	FA_STATUS_MDL_TM3	,

	FA_STATUS_MDL_FM	,

	//========================================================================================================

	VAL_GetModelID		,	
	VAL_GetModelMode	,	
	VAL_SetModelID		,
	VAL_SetModelMode	,
	VAL2_GetModelID		,	
	VAL2_GetModelMode	,	
	VAL2_SetModelID		,
	VAL2_SetModelMode	,
	TMC_ALGNLOW_CONTROL	,
	TMC_ALGNLOW2_CONTROL,

	P1_ALIGN_CONTROL_MODE	,
	P2_ALIGN_CONTROL_MODE	,
	TMC_ALIGNER_CONTROL	,
	TMC_ALIGNER2_CONTROL,
	R1_STATE			,

	//========================================================================================================

	CAM_BASIS_CONTROL		,
	// オムロンカメラ正式版では削除する↓↓
//	TMC_CCD_CONTROL			, // 2014.08.20 削除
	// オムロンカメラ正式版では削除する↑↑
	// 2014.03.12 suzuki add↓↓
	TMC_CAMERA_CONTROL		,
	TMC_CAMERA2_CONTROL		, // 2014.08.20 コメント解除
	// 2014.03.12 suzuki add↑↑
//	CAM_LL1U_CHECK			,
	CAM_LL1L_CHECK			,
//	CAM_LL2U_CHECK			,
	CAM_LL2L_CHECK			,
	CAM_PMA_CHECK			,
	CAM_PMB_CHECK			,
	CAM_PME_CHECK			,
	CAM_PMF_CHECK			,
	CAM_PMC_CHECK			,
	CAM_PMD_CHECK			,
	CAM_PMH_CHECK			,
	CAM_PMI_CHECK			,
	CAM_PMJ_CHECK			,
	CAM_PMK_CHECK			,
	CAM_PML_CHECK			,
	CAM_PMM_CHECK			,
	CAM_PMG_CHECK			,
	CAM_PMN_CHECK			,

//	CAM_LL1U_CHECK_A		,
	CAM_LL1L_CHECK_A		,
//	CAM_LL2U_CHECK_A		,
	CAM_LL2L_CHECK_A		,
	CAM_PMA_CHECK_A			,
	CAM_PMB_CHECK_A			,
	CAM_PME_CHECK_A			,
	CAM_PMF_CHECK_A			,
	CAM_PMC_CHECK_A			,
	CAM_PMD_CHECK_A			,
	CAM_PMH_CHECK_A			,
	CAM_PMI_CHECK_A			,
	CAM_PMJ_CHECK_A			,
	CAM_PMK_CHECK_A			,
	CAM_PML_CHECK_A			,
	CAM_PMM_CHECK_A			,
	CAM_PMG_CHECK_A			,
	CAM_PMN_CHECK_A			,

//	CAM_LL1U_CHECK_B		,
	CAM_LL1L_CHECK_B		,
//	CAM_LL2U_CHECK_B		,
	CAM_LL2L_CHECK_B		,
	CAM_PMA_CHECK_B			,
	CAM_PMB_CHECK_B			,
	CAM_PME_CHECK_B			,
	CAM_PMF_CHECK_B			,
	CAM_PMC_CHECK_B			,
	CAM_PMD_CHECK_B			,
	CAM_PMH_CHECK_B			,
	CAM_PMI_CHECK_B			,
	CAM_PMJ_CHECK_B			,
	CAM_PMK_CHECK_B			,
	CAM_PML_CHECK_B			,
	CAM_PMM_CHECK_B			,
	CAM_PMG_CHECK_B			,
	CAM_PMN_CHECK_B			,

	FINETUNE_CHECT_PM1			,
	FINETUNE_CHECT_PM2			,
	FINETUNE_CHECT_PM3			,
	FINETUNE_CHECT_PM4			,
	FINETUNE_CHECT_PM14			, // 2015.04.02 PM14追加
	FINETUNE_CHECT_PM5			,
	FINETUNE_CHECT_PM6			,
	FINETUNE_CHECT_PM7			,
	FINETUNE_CHECT_PM8			,
	FINETUNE_CHECT_PM9			,
	FINETUNE_CHECT_PM10			,
	FINETUNE_CHECT_PM12_P1_1	,
	FINETUNE_CHECT_PM12_P1_2	,
	FINETUNE_CHECT_PM11			,
	FINETUNE_CHECT_PM11_2		,
//	FINETUNE_CHECT_PM11_3		,
	FINETUNE_CHECT_PM12			,
	FINETUNE_CHECT_PM12_2		,
//	FINETUNE_CHECT_PM12_3		,
//	FINETUNE_CHECT_PM13			,
//	FINETUNE_CHECT_PM14_3		,
//	FINETUNE_CHECT_PM15			,
	FINETUNE_CHECT_BM1			,
	FINETUNE_CHECT_BM2			,
//	FINETUNE_CHECT_BM3			,
//	FINETUNE_CHECT_BM4			,

	FINETUNE_STATUS_PM1			,
	FINETUNE_STATUS_PM2			,
	FINETUNE_STATUS_PM3			,
	FINETUNE_STATUS_PM4			,
	FINETUNE_STATUS_PM14		, // 2015.04.02 PM14追加
	FINETUNE_STATUS_PM5			,
	FINETUNE_STATUS_PM6			,
	FINETUNE_STATUS_PM7			,
	FINETUNE_STATUS_PM8			,
	FINETUNE_STATUS_PM9			,
	FINETUNE_STATUS_PM10		,
	FINETUNE_STATUS_PM12_P1_1	,
	FINETUNE_STATUS_PM12_P1_2	,
	FINETUNE_STATUS_PM11		,
	FINETUNE_STATUS_PM11_2		,
//	FINETUNE_STATUS_PM11_3		,
	FINETUNE_STATUS_PM12		,
	FINETUNE_STATUS_PM12_2		,
//	FINETUNE_STATUS_PM12_3		,
//	FINETUNE_STATUS_PM13		,
//	FINETUNE_STATUS_PM14_3		,
//	FINETUNE_STATUS_PM15		,
	FINETUNE_STATUS_BM1			,
	FINETUNE_STATUS_BM2			,
//	FINETUNE_STATUS_BM3			,
//	FINETUNE_STATUS_BM4			,

	FINETUNE_OLD_R_POS_PM1		,
	FINETUNE_OLD_R_POS_PM2		,
	FINETUNE_OLD_R_POS_PM3		,
	FINETUNE_OLD_R_POS_PM4		,
	FINETUNE_OLD_R_POS_PM14		, // 2015.04.02 PM14追加
	FINETUNE_OLD_R_POS_PM5		,
	FINETUNE_OLD_R_POS_PM6		,
	FINETUNE_OLD_R_POS_PM7		,
	FINETUNE_OLD_R_POS_PM8		,
	FINETUNE_OLD_R_POS_PM9		,
	FINETUNE_OLD_R_POS_PM10		,
	FINETUNE_OLD_R_POS_PM12_P1_1,
	FINETUNE_OLD_R_POS_PM12_P1_2,
	FINETUNE_OLD_R_POS_PM11		,
	FINETUNE_OLD_R_POS_PM11_2	,
//	FINETUNE_OLD_R_POS_PM11_3	,
	FINETUNE_OLD_R_POS_PM12		,
	FINETUNE_OLD_R_POS_PM12_2	,
//	FINETUNE_OLD_R_POS_PM12_3	,
//	FINETUNE_OLD_R_POS_PM13		,
//	FINETUNE_OLD_R_POS_PM14_3	,
//	FINETUNE_OLD_R_POS_PM15		,
	FINETUNE_OLD_R_POS_BM1		,
	FINETUNE_OLD_R_POS_BM2		,
//	FINETUNE_OLD_R_POS_BM3		,
//	FINETUNE_OLD_R_POS_BM4		,

	FINETUNE_OLD_T_POS_PM1		,
	FINETUNE_OLD_T_POS_PM2		,
	FINETUNE_OLD_T_POS_PM3		,
	FINETUNE_OLD_T_POS_PM4		,
	FINETUNE_OLD_T_POS_PM14		, // 2015.04.02 PM14追加
	FINETUNE_OLD_T_POS_PM5		,
	FINETUNE_OLD_T_POS_PM6		,
	FINETUNE_OLD_T_POS_PM7		,
	FINETUNE_OLD_T_POS_PM8		,
	FINETUNE_OLD_T_POS_PM9		,
	FINETUNE_OLD_T_POS_PM10		,
	FINETUNE_OLD_T_POS_PM12_P1_1,
	FINETUNE_OLD_T_POS_PM12_P1_2,
	FINETUNE_OLD_T_POS_PM11		,
	FINETUNE_OLD_T_POS_PM11_2	,
//	FINETUNE_OLD_T_POS_PM11_3	,
	FINETUNE_OLD_T_POS_PM12		,
	FINETUNE_OLD_T_POS_PM12_2	,
//	FINETUNE_OLD_T_POS_PM12_3	,
//	FINETUNE_OLD_T_POS_PM13		,
//	FINETUNE_OLD_T_POS_PM14_3	,
//	FINETUNE_OLD_T_POS_PM15		,
	FINETUNE_OLD_T_POS_BM1		,
	FINETUNE_OLD_T_POS_BM2		,
//	FINETUNE_OLD_T_POS_BM3		,
//	FINETUNE_OLD_T_POS_BM4		,

	FINETUNE_NEW_R_POS_PM1		,
	FINETUNE_NEW_R_POS_PM2		,
	FINETUNE_NEW_R_POS_PM3		,
	FINETUNE_NEW_R_POS_PM4		,
	FINETUNE_NEW_R_POS_PM14		, // 2015.04.02 PM14追加
	FINETUNE_NEW_R_POS_PM5		,
	FINETUNE_NEW_R_POS_PM6		,
	FINETUNE_NEW_R_POS_PM7		,
	FINETUNE_NEW_R_POS_PM8		,
	FINETUNE_NEW_R_POS_PM9		,
	FINETUNE_NEW_R_POS_PM10		,
	FINETUNE_NEW_R_POS_PM12_P1_1,
	FINETUNE_NEW_R_POS_PM12_P1_2,
	FINETUNE_NEW_R_POS_PM11		,
	FINETUNE_NEW_R_POS_PM11_2	,
//	FINETUNE_NEW_R_POS_PM11_3	,
	FINETUNE_NEW_R_POS_PM12		,
	FINETUNE_NEW_R_POS_PM12_2	,
//	FINETUNE_NEW_R_POS_PM12_3	,
//	FINETUNE_NEW_R_POS_PM13		,
//	FINETUNE_NEW_R_POS_PM14_3	,
//	FINETUNE_NEW_R_POS_PM15		,
	FINETUNE_NEW_R_POS_BM1		,
	FINETUNE_NEW_R_POS_BM2		,
//	FINETUNE_NEW_R_POS_BM3		,
//	FINETUNE_NEW_R_POS_BM4		,

	FINETUNE_NEW_T_POS_PM1		,
	FINETUNE_NEW_T_POS_PM2		,
	FINETUNE_NEW_T_POS_PM3		,
	FINETUNE_NEW_T_POS_PM4		,
	FINETUNE_NEW_T_POS_PM14		, // 2015.04.02 PM14追加
	FINETUNE_NEW_T_POS_PM5		,
	FINETUNE_NEW_T_POS_PM6		,
	FINETUNE_NEW_T_POS_PM7		,
	FINETUNE_NEW_T_POS_PM8		,
	FINETUNE_NEW_T_POS_PM9		,
	FINETUNE_NEW_T_POS_PM10		,
	FINETUNE_NEW_T_POS_PM12_P1_1,
	FINETUNE_NEW_T_POS_PM12_P1_2,
	FINETUNE_NEW_T_POS_PM11		,
	FINETUNE_NEW_T_POS_PM11_2	,
//	FINETUNE_NEW_T_POS_PM11_3	,
	FINETUNE_NEW_T_POS_PM12		,
	FINETUNE_NEW_T_POS_PM12_2	,
//	FINETUNE_NEW_T_POS_PM12_3	,
//	FINETUNE_NEW_T_POS_PM13		,
//	FINETUNE_NEW_T_POS_PM14_3	,
//	FINETUNE_NEW_T_POS_PM15		,
	FINETUNE_NEW_T_POS_BM1		,
	FINETUNE_NEW_T_POS_BM2		,
//	FINETUNE_NEW_T_POS_BM3		,
//	FINETUNE_NEW_T_POS_BM4		,

	FINETUNE_DPICK_COMP_R		,
	// 2013/05/07 ----------------------------------------------------------------->>
	P1_X_OFFSET					,
	P1_Y_OFFSET					,
	// 2013/05/07 -----------------------------------------------------------------<<
	P1_R_OFFSET					,
	// 2013/05/07 ----------------------------------------------------------------->>
	P2_X_OFFSET					,
	P2_Y_OFFSET					,
	// 2013/05/07 -----------------------------------------------------------------<<
	P2_R_OFFSET					,
	FINETUNE_CHECK_PASS1_PASS2	,
	FINETUNE_CHECK_PASS			,

	ALIGNER_MESRESULT			,
	ALIGNER_CORRECT_ANGLE		,
	ALIGNER_M_ANGLE				,
	ALIGNER_GET_CORRECT_ANGLE	,
	ALIGNER2_MESRESULT			,
	ALIGNER2_CORRECT_ANGLE		,
	ALIGNER2_M_ANGLE			,
	ALIGNER2_GET_CORRECT_ANGLE	,
	NOTCH_CORRECT_CHECK_TR		,
	NOTCH_CORRECT_CHECK_ARM		,
	NOTCH_CORRECT_STATUS		,
	FINETUNE_NOTCH_ANGLE		,
	FINETUNE_CORRECT_ANGLE_SET	,
	FINETUNE_CORRECT_ANGLE_GET	,

	PM1_CLEAR_SKIP				,
	PM2_CLEAR_SKIP				,
	PM3_CLEAR_SKIP				,
	PM4_CLEAR_SKIP				,
	PM5_CLEAR_SKIP				,
	PM6_CLEAR_SKIP				,
	PM7_CLEAR_SKIP				,
	PM8_CLEAR_SKIP				,
	PM9_CLEAR_SKIP				,
	PM10_CLEAR_SKIP				,
	PM11_CLEAR_SKIP				,
	PM12_CLEAR_SKIP				,
	PM13_CLEAR_SKIP				,
	PM14_CLEAR_SKIP				,
	PM15_CLEAR_SKIP				,

	All_ControlStatus			,

	PM1_ControlStatus			,
	PM2_ControlStatus			,
	PM3_ControlStatus			,
	PM4_ControlStatus			,
	PM5_ControlStatus			,
	PM6_ControlStatus			,
	PM7_ControlStatus			,
	PM8_ControlStatus			,
	PM9_ControlStatus			,
	PM10_ControlStatus			,
	PM11_ControlStatus			,
	PM12_ControlStatus			,
	PM13_ControlStatus			,
	PM14_ControlStatus			,
	PM15_ControlStatus			,

	FM_ControlStatus			,

	TM_ControlStatus			,
	TM2_ControlStatus			,
	TM3_ControlStatus			,

	BM1_ControlStatus			,
	BM2_ControlStatus			,
	BM3_ControlStatus			,
	BM4_ControlStatus			,
	//========================================================================================================
	TR1_RobotArmShort			,
	TR2_RobotArmShort			,

	PM1_MAIN_CONTROL			,
	PM2_MAIN_CONTROL			,
	PM3_MAIN_CONTROL			,
	PM4_MAIN_CONTROL			,
	PM5_MAIN_CONTROL			,
	PM6_MAIN_CONTROL			,
	PM7_MAIN_CONTROL			,
	PM8_MAIN_CONTROL			,
	PM9_MAIN_CONTROL			,
	PM10_MAIN_CONTROL			,
	PM14_MAIN_CONTROL			,

	//2008.10.16 suzuki add
	LL1L_CAM_EXISTS				,
	LL2L_CAM_EXISTS				,
	PM1_CAM_EXISTS				,
	PM2_CAM_EXISTS				,
	PM3_CAM_EXISTS				,
	PM4_CAM_EXISTS				,
	PM11_CAM_EXISTS				,
	PM12_CAM_EXISTS				,
	PM5_CAM_EXISTS				,
	PM6_CAM_EXISTS				,
	PM7_CAM_EXISTS				,
	PM8_CAM_EXISTS				,
	PM9_CAM_EXISTS				,
	PM10_CAM_EXISTS				,
	PM13_CAM_EXISTS				,
	PM14_CAM_EXISTS				,
	//========================================================================================================
	TM_WFRSNS_CONTROL			,
	TM_CAM_CONTROL				,
	//20141217 Okabe
	CORRECT_ANGLE_SET_GUI	,

	CTC_TAKT_mode				, // 2015.05.29

} IOPointIndex;
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#endif

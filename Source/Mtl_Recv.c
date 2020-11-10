//-----------------------------------------------------------------------------------
// IARIM Function_Maint_Run
// 
// [TYPE]
// EQ_TYPE_IARIM2  : 2core+4LoadLock(QuadroLL) === default , Sequence.exe
// EQ_TYPE_IARIM2A : 2core+2LoadLock(SingleLL)             , Sequence2a.exe = IARIM-NX
//
// File Name : Mtl_Recv.c
//
// (C) 2001-2013 Canon ANELVA Corporation
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
#include "iodefine.h"

#include "Mtl_Recv_Sub.h"
#include "Mtl_Recv.h"
#include "cimseqnc.h"
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Map_Sub( int type , int Station , int Arm , int Slot , int *Rec_Arm ) {
	int RunPart , CheckType , TmSide , ModuleIndex , RunArm , RunSlot , PresentSetValue;
	//========================================================================================
	RunPart = -1;
	CheckType = -1;
	TmSide = -1;
	ModuleIndex = -1;
	RunArm = -1;
	RunSlot = -1;
	PresentSetValue = -1;
	//========================================================================================
	if      ( type == 0 ) CheckType = MTL_SUB_REAL_CHECK;
	else if ( type == 1 ) CheckType = MTL_SUB_REAL_CHECK;
	else if ( type == 2 ) CheckType = MTL_SUB_WAFER_SET;
	else                  CheckType = MTL_SUB_WAFER_CLEAR;
	//========================================================================================
	switch( Station ) {
	case MTL_LPMA :	//	LPMA
	case MTL_LPMB :	//	LPMB
	case MTL_LPMC :	//	LPMC
	case MTL_LPMD :	//	LPMD
		RunPart = MTL_PART_CM;
		ModuleIndex = Station - MTL_LPMA + 1;
		RunSlot = ( type == 0 ) ? -1 : Slot;
		PresentSetValue = Slot;
		break;

	case MTL_FM :	// FM
		RunPart = MTL_PART_FM;
		RunArm = Arm;
		PresentSetValue = Slot;
		break;

	case MTL_Aligner :	//	Aligner
		RunPart = MTL_PART_FAL;
		PresentSetValue = Slot;
		break;

	case MTL_LLA_ATM :	//	LLA(A)
	case MTL_LLB_ATM :	//	LLB(A)
		RunPart = MTL_PART_BM_F;
		TmSide = 0;
		ModuleIndex = Station - MTL_LLA_ATM + 1;
		RunArm = Arm;
		RunSlot = ( type == 0 ) ? -1 : Slot;
		PresentSetValue = Slot;
		break;

	case MTL_LLA_VAC :	//	LLA(V)
	case MTL_LLB_VAC :	//	LLB(V)
		RunPart = MTL_PART_BM_F;
		TmSide = 1;
		ModuleIndex = Station - MTL_LLA_VAC + 1;
		RunArm = Arm;
		RunSlot = ( type == 0 ) ? -1 : Slot;
		PresentSetValue = Slot;
		break;

	case MTL_TM :	//	TM
	case MTL_TM2 :	//	TM2
		RunPart = MTL_PART_TM;
		TmSide = Station - MTL_TM + 1;
		ModuleIndex = -1;
		RunArm = Arm;
		RunSlot = Slot;
		PresentSetValue = Slot;
		break;

	case MTL_PM1 :	//	PM1
	case MTL_PM2 :	//	PM2
	case MTL_PM3 :	//	PM3
	case MTL_PM4 :	//	PM4
		RunPart = MTL_PART_PM;
		TmSide = 1;
		ModuleIndex = Station - MTL_PM1 + 1;
	
		RunArm = Arm;
		RunSlot = Slot;
		PresentSetValue = Slot;
		break;

	case MTL_PM5 :	//	PM5
	case MTL_PM6 :	//	PM6
	case MTL_PM7 :	//	PM7
	case MTL_PM8 :	//	PM8
	case MTL_PM9 :	//	PM9
	case MTL_PM10 :	//	PM10
		RunPart = MTL_PART_PM;
		TmSide = 2;
		// 2015.03.26 enum Ç…PM14Ç™ì¸Ç¡ÇΩÇΩÇﬂ"+1"ÇçÌèú
		ModuleIndex = Station - MTL_PM1;
		//ModuleIndex = Station - MTL_PM1 + 1;
	
		RunArm = Arm;
		RunSlot = Slot;
		PresentSetValue = Slot;
		break;

	// 2015.03.26 PM14í«â¡
	case MTL_PM14 : //	PM14
		RunPart = MTL_PART_PM;
		TmSide = 2;
		ModuleIndex = 14;
	
		RunArm = Arm;
		RunSlot = Slot;
		PresentSetValue = Slot;
		break;
	//

	// 2015.03.26 PASS1(PM11)çÌèú
	//case MTL_PM11_1 :	//	PM11(TM1)
	//	RunPart = MTL_PART_PM_F;
	//	TmSide = 1;
	//	ModuleIndex = 11;
	//	RunArm = Arm;
	//	RunSlot = Slot;
	//	PresentSetValue = Slot;
	//	break;
	//

	case MTL_PM12_1 :	//	PM12(TM1)
		RunPart = MTL_PART_PM_F;
		TmSide = 1;
		ModuleIndex = 12;
		RunArm = Arm;
		RunSlot = Slot;
		PresentSetValue = Slot;
		break;

	default :
		return SYS_ABORTED;
		break;
	}
	if ( PresentSetValue == 0 ) PresentSetValue = 1;
	return Maint_Material_Recovery_Check( RunPart , CheckType , TmSide , ModuleIndex , RunArm , RunSlot , PresentSetValue , Rec_Arm );
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Map( int type ) {
	int CommStatus;
	int Arm , Station , Slot;
	int Rec_Arm;
	//========================================================================================
	Arm     = READ_DIGITAL( MTL_RECV_Arm		, &CommStatus );
	Station = READ_DIGITAL( MTL_RECV_Station	, &CommStatus );

	Slot    = READ_DIGITAL( MTL_RECV_Slot		, &CommStatus ) + 1;
	//========================================================================================
	return Maint_Material_Recovery_Map_Sub( type , Station , Arm , Slot , &Rec_Arm );
	//========================================================================================
}
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_Empty_All( BOOL all ) {
	int Rec_Arm;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM1 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM2 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM3 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM4 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM5 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM6 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM7 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM8 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM9 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM10 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM14 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;   // 2015.03.26 PM14í«â¡
//	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM11_1 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED; // 2015.03.26 PM11çÌèú
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_PM12_1 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;

	if ( all ) {
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LPMA , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LPMB , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LPMC , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LPMD , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		//
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_FM , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_FM , 1 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		//
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_Aligner , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		//
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_TM , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_TM , 1 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_TM2 , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_TM2 , 1 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		//
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LLA_ATM , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_CLEAR , MTL_LLB_ATM , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	}
	return SYS_SUCCESS;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Module_Status Maint_Material_Recovery_All( BOOL all ) {
	int Rec_Arm , Rec_ArmF;
	int i;

	//---------------------------------------------------------------------------------------------------------------------
	// CM Check
	//---------------------------------------------------------------------------------------------------------------------
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_LPMA , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_LPMB , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_LPMC , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_LPMD , 0 , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;

	//---------------------------------------------------------------------------------------------------------------------
	// AL Check
	//---------------------------------------------------------------------------------------------------------------------
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_Aligner , 0 , 1 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	//---------------------------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------------------------
	// FM Robot Arm Check
	//---------------------------------------------------------------------------------------------------------------------
	Rec_ArmF = -1;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_FM , 0 , 0 , &Rec_ArmF ) == SYS_ABORTED ) return SYS_ABORTED;
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_FM , 1 , 0 , &Rec_ArmF ) == SYS_ABORTED ) return SYS_ABORTED;
	//-------------------------------------------------------
//	if ( Rec_ArmF < 0 ) return SYS_ABORTED; // 2006.10.25
	//-------------------------------------------------------
	
	//---------------------------------------------------------------------------------------------------------------------
	// BM All Check
	//---------------------------------------------------------------------------------------------------------------------
	Rec_ArmF = 0;
	for ( i = 0 ; i < 2 ; i++ ) {
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_LLA_ATM + i , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	}

	//---------------------------------------------------------------------------------------------------------------------
	// TM1 Robot Arm Check
	//---------------------------------------------------------------------------------------------------------------------
	Rec_ArmF = -1;
	for ( i = 0 ; i < 2 ; i++ ) {
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_TM  , i , 0 , &Rec_ArmF ) == SYS_ABORTED ) return SYS_ABORTED;
	}
	if ( all ) {
		//-------------------------------------------------------
	
		if ( Rec_ArmF < 0 ) return SYS_ABORTED;

		
		//-------------------------------------------------------
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM1 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM2 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM3 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM4 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		
	}
	//if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM11_1 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED; // 2015.03.26 PASS1(PM11)çÌèú
	if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM12_1 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
	//-------------------------------------------------------

	//---------------------------------------------------------------------------------------------------------------------
	// TM2 Robot Arm Check
	//---------------------------------------------------------------------------------------------------------------------
	Rec_ArmF = -1;
	for ( i = 0 ; i < 2 ; i++ ) {
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_TM2 , i , 0 , &Rec_ArmF ) == SYS_ABORTED ) return SYS_ABORTED;
	}
	if ( all ) {
		//-------------------------------------------------------
		if ( Rec_ArmF < 0 ) return SYS_ABORTED;
		//-------------------------------------------------------
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM5 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM6 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM7 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM8 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM9 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM10 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED;
		if ( Maint_Material_Recovery_Map_Sub( MTL_TYPE_REAL_ALL , MTL_PM14 , Rec_ArmF , 0 , &Rec_Arm ) == SYS_ABORTED ) return SYS_ABORTED; // 2015.03.26 PM14
	}
	//-------------------------------------------------------

	return SYS_SUCCESS;
}

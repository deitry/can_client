/*
 * can_par_id.h
 *
 * �������� ����������� ��������������� ��� �������� ���������� ����� CAN.
 *
 * ������� ���������� ��������� �������:
 * - �������� ������������� ���������� ��� �������,
 * - �������������� - ������ �������� �������� � ���� �������
 * (����������� ����� ���� �� ��� ��������, �.�. �� ����� ���������� ��������� �������)
 *
 * ����� �� ������� ����� �������� ������ ����������.
 * � �������� ����� ������ ����� ���� �������� 256 ���������������.
 *
 *  Created on: 18.03.2015
 *      Author: ����
 */

#ifndef CAN_PAR_ID_H_
#define CAN_PAR_ID_H_

/*struct PAR_ID_BYTES
{
	Uint8 P:8;
	Uint8 S:8;
};

union EC_CAN_PAR_ID
{
	Uint16 all;
	PAR_ID_BYTES bytes;
};*/

/**
 * ������ �� ��������� ���������. ������ ������ � ����� ������:
 * (0xFF) - (P) - (S) - (SS) - (SSS)
 */
#define EC_PREQ		0xFB		// ��������� ������ ���������
#define EC_PQUE		0xFA		// ���������� ��������� � ������ ���������� ��������
#define EC_PCLR		0xF9		// ��������� ������ ���������� ��������

#define EC_P0		0x00
#define EC_BAD		0xFF
/**
 * ����������� ����������:
 * - EC = Electronic Control
 * - P - Parameter - ��������
 * - G - ������ ����������
 * - T - Table - �������. ����� ������������ ��� �������������
 * ���������� ��� ������� �� ���������
 * - S - Sub-parameter / Sub-index 1
 * ���������� ������������� ���������� � 1,
 * ����������� � �������� � ������� � 0
 * - SS - Sub-index 2
 */


#define EC_TIME			0xFE		// ����� ������� �� ������ ������� ���������� �� ����
#define EC_TINJ			0xFD		// ����� ������� �� ������ �������
#define EC_TPROG		0xFC		// ����� ������� �� ����� ����� ���������
#define EC_P_MODE		0x01		// �����
#define EC_G_N			0x02		// ������ ���������� ������� ��������
#define 	EC_S_NR			0x00		// float ������� �������� ��/���
#define 	EC_S_NU			0x01		// float ������� ������� �������� ��/���
#define 	EC_S_OMEGA		0x02		// float ���/�
#define 	EC_S_DTIME		0x03		// float ����� ����� ������������ �� ������� � �

#define EC_G_QC			0x03			// ������ ���������� ������
#define 	EC_S_QC_T			0x00	// int ����� �������� ��������� � ���
#define 	EC_S_QC_AN			0x01	// float ����� ������� � �����
#define 	EC_S_QC				0x02	// float ���������� �������, ������� ������� � �������
#define		EC_S_ADOP			0x03	// float ����� - �����������
#define		EC_S_QC_ADOP		0x04	// float ������ - ������������ �� �����
#define EC_P_NCYL		0x04			// int ���������� ���������
#define EC_P_PED		0x05			// float ��������� ������
#define 	EC_S_PEDST			0x01	// float ��������� ���������� �������� ������
#define EC_P_VMT		0x06		// float ���� �������� ��� ������������ ����������� ������

#define EC_G_INJ		0x10		// ��������� �������
#define 	EC_S_INJT1			0x00	// int �����������������
#define 	EC_S_INJT2			0x01	// int ����������������� 
#define 	EC_S_INJD1			0x02	// int ����������
#define 	EC_S_INJD2			0x03	// int ����������

// ��������� - ����� �������� 0..NCYL
#define EC_T_INJPHI		0x11		// float ����, ������������ ������ �������
#define EC_T_INJZ		0x12		// int ���, �� �������� ������ ������ ������� �� ������� �������
#define EC_T_INJN		0x13		// int ���������� �������� � ������ ������� � ������� ������� ���������
#define EC_T_INJT		0x14		// float ����� �� �������, ������������� �� ���� injZ
#define EC_T_INJCNT		0x15

#define EC_P_M_MODE		0x21                // ���� - ��������� ������ ������� ������ ������ �����
#define EC_P_M_QC		0x22                // ���� manQC - ��������� ������ ���������� �������
#define EG_MANQC_AUTO	0					// 0 - ������ �������������� ������������� �� ���-������
#define EG_MANQC_TIME	1					// 1 - ������ ����� �� ��������������, ������������ ����� g_step2Us
#define EG_MANQC_ANGLE	2					// 2 - ����������������� ������ ������������ �� ���� injAngle
#define EG_MANQC_QC		3					// 3 - ����������������� ������ �������������� ������ �� �������� QC
// ��-�������
//#define 	EC_S_M_AN			0x01        // ���� manAngle - ����� ������� ������ � �����
#define 	EC_S_M_IAN			0x02        // ����� injAngle - ����������������� ������� � ����� ����������� ����
//#define 	EC_S_M_QCT			0x03        // ���� manQCt - ������� ������ � �������������
// --
#define EC_P_M_INJ		0x23                // ���� manInj - ������ ���������� �������� � ������� ������� 
#define 	EC_S_M_IONCE		0x01        // ���� injOnce - ����������� ����������� ��� ������������� (���� manN != 0) ������ � �������
#define 	EC_S_M_IN			0x02        // ����� manN - ������� �������� � ������ �����������
#define 	EC_S_M_INJCYL		0x03		// �������, � ������� �������������� ������
#define 	EC_S_FDBKCYL		0x04		// �������, � �������� ����� ����������� �������� �����
#define EC_P_M_PED		0x24                // ���� manPed - ������ ��������� �������� ������
#define EC_P_M_CANS		0x25                // ���� CanSend - ��������� ����������
#define		EC_S_M_CANST		0x01		// ���� CanTime - ��������� ��������� �����
#define EC_P_M_UOVT		0x26                // ���� manUOVT - ������ ������� ����
#define 	EC_S_M_UOVT			0x01        // ����� injUOVT - ���� ���������� ������� �������
#define EC_P_M_FDBK		0x27                // ���� manFdbk - �������� ����� �� ����.
	// �������� ��������. ��������� ���������� ����� ��������, ���������� ����� ����� �������
#define EC_P_M_LED		0x28				// ���� ��������� �����������
#define EC_P_M_SENS		0x29				// ������ �� ��������� ��������
#define 	EC_S_PK				0x01		// Pkompr
#define		EC_S_TV				0x02		// Tvozd
#define 	EC_S_D_PINJ			0x04		// Pinj �������� �������

#define EC_T_UOVT		0x31	// ������� ����� ���������� �������
#define EC_T_SPCHAR		0x32	// ������� ���������� ��������������
#define EC_T_NSTEADY	0x33	// ������� ������� �������� ��������� ���� � ���-�� �� �����������
#define EC_T_QSTART		0x34	// ������� ��������� ������ ������� � ���-�� �� �����������

#define EC_P_KP			0x41	// float ���������������� �-�
#define EC_P_KI			0x42	// float �-� ��� ������������ ������������
#define EC_P_KD			0x43	// float �-� ��� ���������������� ������������
#define EC_P_ERR		0x44	// float ���������������� ������ �������������
#define EC_P_ERRI		0x45	// float ������������ ������ �������������
#define EC_P_ERRD		0x46	// float ���������������� ������ �������������

#define EC_P_MUN		0x47	// float ����������� ����� ������ �������
#define EC_P_DZONE		0x48	// float ���� ������������������ ����������

#define EC_P_PTIME		0x51	// int ����� ���������� ��������� ���� ��������� � ���
#define EC_P_ITIME		0x52
#define EC_P_ITIME1		0x53

#endif /* CAN_PAR_ID_H_ */


/*void sendCanMsg(PAR_ID_BYTES id)
{
	CAN_DATA data;

	for (int i = 0; i < 6; i++)
	{
		data.all[i] = 0;
	}

	data.f.PARID = id.P;
	data.f.R1 = id.S;

	switch (id.P)
	{
	case EC_P_MODE: data.f.val.i = engine->mode; break;
	case EC_G_N:
		switch (id.S)
		{
		case EC_S_NR: data.f.val.f = EG::nR; break;
		case EC_S_NU: data.f.val.f = EG::nU; break;
		case EC_S_OMEGA: data.f.val.f = EG::omegaR; break;
		case EC_S_DTIME: data.f.val.i = delta_time; break;
		}
		break;
	case EC_G_QC:
		switch (id.S)
		{
		case EC_S_QC_T: data.f.val.f = EG::g_step2Us; break;
		case EC_S_QC_AN: data.f.val.f = EG::injAngle; break;
		case EC_S_QC: data.f.val.f = EG::QC; break;
		}
		break;
	case EC_P_NCYL: data.f.val.i = DIESEL_N_CYL; break;
	case EC_P_PED:
		switch (id.S)
		{
		case EC_P0: data.f.val.f = EG::pedal; break;
		case EC_S_PEDST: data.f.val.i = EG::pedStep; break;
		}
		break;
	case EC_P_VMT: data.f.val.i = EG::anVMT; break;
	case EC_G_INJ:
		switch (id.S)
		{
		case EC_S_INJT1: data.f.val.i = EG::g_step1Us; break;
		case EC_S_INJT2: data.f.val.i = EG::g_step2Us; break;
		case EC_S_INJD1: data.f.val.i = EG::g_duty1; break;
		case EC_S_INJD2: data.f.val.i = EG::g_duty2; break;
		}
		break;
	case EC_T_INJPHI: data.f.val.f = EG::injPhi[id.S]; break;
	case EC_T_INJZ:	data.f.val.f = EG::injZ[id.S]; break;
	case EC_T_INJN:	data.f.val.f = EG::injN[id.S]; break;
	case EC_T_INJT:	data.f.val.f = EG::injT[id.S]; break;
	case EC_P_M_MODE: data.f.val.i = EG::manMode; break;
	case EC_P_M_QC:
		switch (id.S)
		{
		case EC_P0: data.f.val.i = EG::manQC; break;
		case EC_S_M_AN: data.f.val.i = EG::manAngle; break;
		case EC_S_M_IAN: data.f.val.f = EG::injAngle; break;
		}
		break;
	case EC_P_M_INJ:
		switch (id.S)
		{
		case EC_P0: data.f.val.i = EG::manInj; break;
		case EC_S_M_IONCE: data.f.val.i = EG::injOnce; break;
		case EC_S_M_IN: data.f.val.i = EG::manN; break;
		}
		break;
	case EC_P_M_PED: data.f.val.i = EG::manPed; break;
	case EC_P_M_CANS: data.f.val.i = EG::canSend; break;
	case EC_P_M_UOVT:
		switch (id.S)
		{
		case EC_P0: data.f.val.i = EG::manOUVT; break;
		case EC_S_M_UOVT: data.f.val.f = EG::injOuvt; break;
		}
		break;
	}

	sendCanMsgX(&data);
}*/

/*void recieveCanMsg(tCANMsgObject* msg)
{
	can_data.all = msg->pucMsgData;
	switch (msg->pucMsgData[0])
	{
	case EC_P_MODE: engine->mode = can_data.f.val.i; break;
	case EC_G_N:
		switch (msg->pucMsgData[1])
		{
		case EC_S_NR: EG::nR = can_data.f.val.f; break;
		case EC_S_NU: EG::nU = can_data.f.val.f; break;
		case EC_S_OMEGA: EG::omegaR = can_data.f.val.f; break;
		case EC_S_DTIME: delta_time = can_data.f.val.f; break;
		}
		break;
	case EC_G_QC:
		switch (msg->pucMsgData[1])
		{
		case EC_S_QC_T: EG::g_step2Us = can_data.f.val.f; break;
		case EC_S_QC_AN: EG::injAngle = can_data.f.val.f; break;
		case EC_S_QC: EG::QC = can_data.f.val.f; break;
		}
		break;
	case EC_P_NCYL: DIESEL_N_CYL = can_data.f.val.i; break;
	case EC_P_PED:
		switch (msg->pucMsgData[1])
		{
		case EC_P0: EG::pedal = can_data.f.val.f; break;
		case EC_S_PEDST: EG::pedStep = can_data.f.val.i; break;
		}
		break;
	case EC_P_VMT: EG::anVMT = can_data.f.val.f; break;
	case EC_G_INJ:
		switch (msg->pucMsgData[1])
		{
		case EC_S_INJT1: EG::g_step1Us = can_data.f.val.i; break;
		case EC_S_INJT2: EG::g_step2Us = can_data.f.val.i; break;
		case EC_S_INJD1: EG::g_duty1 = can_data.f.val.i; break;
		case EC_S_INJD2: EG::g_duty2 = can_data.f.val.i; break;
		}
		break;
	case EC_T_INJPHI: EG::injPhi[msg->pucMsgData[1]] = can_data.f.val.f; break;
	case EC_T_INJZ:	EG::injZ[msg->pucMsgData[1]] = can_data.f.val.f; break;
	case EC_T_INJN:	EG::injN[msg->pucMsgData[1]] = can_data.f.val.f; break;
	case EC_T_INJT:	EG::injT[msg->pucMsgData[1]] = can_data.f.val.f; break;
	case EC_P_M_MODE: EG::manMode = can_data.f.val.i; break;
	case EC_P_M_QC:
		switch (msg->pucMsgData[1])
		{
		case EC_P0: EG::manQC = can_data.f.val.i; break;
		case EC_S_M_AN: EG::manAngle = can_data.f.val.i; break;
		case EC_S_M_IAN: EG::injAngle = can_data.f.val.f; break;
		}
		break;
	case EC_P_M_INJ:
		switch (msg->pucMsgData[1])
		{
		case EC_P0: EG::manInj = can_data.f.val.i; break;
		case EC_S_M_IONCE: EG::injOnce = can_data.f.val.i; break;
		case EC_S_M_IN: EG::manN = can_data.f.val.i; break;
		}
		break;
	case EC_P_M_PED: EG::manPed = can_data.f.val.i; break;
	case EC_P_M_CANS: EG::canSend = can_data.f.val.i; break;
	case EC_P_M_UOVT:
		switch (msg->pucMsgData[1])
		{
		case EC_P0: EG::manOUVT = can_data.f.val.i; break;
		case EC_S_M_UOVT: EG::injOuvt = can_data.f.val.f; break;
		}
		break;
	}
}*/

#include "stdafx.h"
#include "form1.h"
#include "include/Usbcan32.h"
#include "can_par_id.h"

tUcanHandle m_UcanHandle;

unsigned char can_client::data[8] = {0};

float fdbkData[30] = {0};

static tCanMsgStruct can_client::TxCanMsg_l =
{
    0x001,
    0,
    15, //8,
    {0x00, 0x00, 0x00, 0x00, 0xFF, 0xEE, 0xDD, 0xCC},
    0
};

void PUBLIC UcanCallbackFktEx (tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p);

void can_client::Form1::can_init(void)
{	
	BYTE bRet = USBCAN_SUCCESSFUL;
	tUcanInitCanParam   InitParam;
	BYTE bDeviceNr_p = USBCAN_ANY_MODULE;
	WORD wBTR_p = USBCAN_BAUD_500kBit;

	// инициализация устройства
	bRet = ::UcanInitHardwareEx (&m_UcanHandle, 1, UcanCallbackFktEx, static_cast<HWND>(Handle.ToPointer()));
            
	// инициализация can
	InitParam.m_dwSize               = sizeof (InitParam);           // size of this struct
    InitParam.m_bMode                = kUcanModeNormal;              // normal operation mode
    InitParam.m_bBTR0                = HIBYTE (wBTR_p);              // baudrate
    InitParam.m_bBTR1                = LOBYTE (wBTR_p);
    InitParam.m_bOCR                 = 0x1A;                         // standard output
    InitParam.m_dwAMR                = USBCAN_AMR_ALL;               // receive all CAN messages
    InitParam.m_dwACR                = USBCAN_ACR_ALL;
    InitParam.m_dwBaudrate           = USBCAN_BAUDEX_USE_BTR01;
    InitParam.m_wNrOfRxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;
    InitParam.m_wNrOfTxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;

    // initialize CAN interface
	bRet = ::UcanInitCanEx (m_UcanHandle, &InitParam);
	
	m_fIsInitialized = TRUE;
}

System::Void can_client::Form1::form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	// деинициализация can 
	::UcanDeinitCan (m_UcanHandle);
        
	// деинициализация устройства
	::UcanDeinitHardware (m_UcanHandle);

	m_fIsInitialized = FALSE;

}

void can_client::Form1::onCanRecieve(void)
{
	BOOL            fRet;
	tCanMsgStruct   RxCanMsg;

    //if (m_fInitOk != FALSE)
    //{
        // read CAN messages until the buffer is empty
        do
        {
            // read CAN message
            fRet = readMsg (&RxCanMsg);
            if (fRet != FALSE)
            {
                printMsg (&RxCanMsg);
            }

        } while (fRet != FALSE);
    //}

    //return 0;
}

BOOL can_client::Form1::readMsg(tCanMsgStruct* pCanMsg_p)
{
	BOOL    fRet    = m_fIsInitialized;
	BYTE    bRet;

    //ASSERT (pCanMsg_p != NULL);

    // check if USB-CANmodul already is initialized
    if (m_fIsInitialized != FALSE)
    {
        fRet = FALSE;

        // read CAN message
        bRet = ::UcanReadCanMsg (m_UcanHandle, pCanMsg_p);
        if (bRet != USBCAN_SUCCESSFUL)
        {
            return fRet;
        }

        fRet = TRUE;
    }

    return fRet;
}

void can_client::Form1::printMsg(tCanMsgStruct *pCanMsg_p)
{
	CAN_DATA d;// = { pCanMsg_p->m_bData };
	for (int counter = 0; counter < 8; counter ++ )
		d.all[counter] = pCanMsg_p->m_bData[counter];
	unsigned char id = d.f.PARID;
	nMessage++;
	//unsigned char val[4];

	textBox3->Text = Convert::ToString((byte)pCanMsg_p->m_bData[0],16);
	/*textBox4->Text = Convert::ToString((byte)pCanMsg_p->m_bData[1],16);
	textBox5->Text = Convert::ToString((byte)pCanMsg_p->m_bData[2],16);
	textBox6->Text = Convert::ToString((byte)pCanMsg_p->m_bData[3],16);
	textBox7->Text = Convert::ToString((byte)d.all[4],16);
	textBox8->Text = Convert::ToString((byte)d.all[5],16);
	textBox9->Text = Convert::ToString((byte)d.all[6],16);
	textBox10->Text = Convert::ToString((byte)d.all[7],16);*/
	//valTextBox->Text = Convert::ToString(d.all);

	// TODO : свич по ид
	eng_mod a;
	
	switch (id)
	{
	case EC_TIME:
	case EC_TINJ:
	case EC_TPROG:
		break;
	case EC_P_MODE:
		try { this->comboMode->SelectedIndex = d.f.val.i - 1; } catch (Exception^ e) {}
		if (this->comboModeOut->SelectedIndex == 0)
		{
			this->comboModeOut->SelectedIndex = this->comboMode->SelectedIndex;
		}
		break;
	case EC_G_N:
		switch (d.f.R1)
		{
		case EC_S_NR:
			this->RPM->Text = Convert::ToString(d.f.val.f);
			break;
		case EC_S_NU:
			this->textnUIn->Text = Convert::ToString(d.f.val.f);
			if (this->textnUOut->Text == "")
			{
				this->textnUOut->Text = this->textnUIn->Text;
			}
			break;
		case EC_S_DTIME:
			this->dT_ms->Text = Convert::ToString(d.f.val.f);
			break;
		}
		break;
	case EC_G_QC:
		switch (d.f.R1)
		{
		case EC_S_QC:
			break;
		case EC_S_QC_T:
			this->Tvprysk->Text = Convert::ToString((System::Object^)d.f.val.i);
			this->textQCtIn->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		case EC_S_QC_AN:
			this->textQCAnIn->Text = Convert::ToString((System::Object^)d.f.val.f);
			this->textQCAn->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		case EC_S_QC_ADOP:
			this->textBox1->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		}
		break;
	case EC_G_INJ:
		switch (d.f.R1)
		{
		case EC_S_INJT1:
			this->textInjT1In->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		case EC_S_INJT2:
			this->textInjT2In->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		case EC_S_INJD1:
			this->textInjD1In->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		case EC_S_INJD2:
			this->textInjD2In->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		}
		break;
	case EC_P_VMT:
		this->textVMTIn->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_M_MODE:
		this->checkManModeIn->Checked = d.f.val.i;
		break;
	case EC_P_M_QC:
		switch (d.f.R1)
		{
		case EC_P0:
			this->checkmanQCIn->Checked = d.f.val.i;
			break;
		case EC_S_M_AN:
			this->checkmanAngleIn->Checked = d.f.val.i;
			break;
		case EC_S_M_IAN:
			this->textQCAnIn->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		case EC_S_M_QCT:
			this->checkManQCtIn->Checked = d.f.val.i;
			break;
		}
		break;
	case EC_P_M_INJ:
		switch (d.f.R1)
		{
		case EC_S_QC_T:
			this->checkmanInjIn->Checked = d.f.val.i;
			break;
		case EC_S_M_IONCE:
			this->checkinjOnceIn->Checked = d.f.val.i;
			break;
		}
		break;
	case EC_P_M_PED:
		this->checkmanPedIn->Checked = d.f.val.i;
		break;
	case EC_P_M_LED:
		this->checkManLedIn->Checked = d.f.val.i;
		break;
	case EC_P_M_CANS:
		switch (d.f.R1)
		{
		case EC_P0:
			this->checkCanSendIn->Checked = d.f.val.i;
			break;
		case EC_S_M_CANST:
			this->checkCanTimeIn->Checked = d.f.val.i;
			break;
		}
		break;
	case EC_P_M_UOVT:
		switch (d.f.R1)
		{
		case EC_P0:
			this->checkmanUOVTIn->Checked = d.f.val.i;
			break;
		case EC_S_M_UOVT:
			this->textinjUOVTIn->Text = Convert::ToString(d.f.val.f);
			this->UOVT->Text = Convert::ToString(d.f.val.f);
			break;
		}
		break;
	case EC_P_M_FDBK:
		if (d.f.R1 == 0)
		{
			this->checkManFdbkIn->Checked = d.f.val.i;
		} else {
			fdbkData[d.f.R1-1] = d.f.val.f;
			gridFdbk->Rows[0]->Cells[d.f.R1-1]->Value = d.f.val.f;
		}
		break;
	case EC_P_PTIME:
		this->textProgTime->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_ITIME:
		this->textIntTime->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_ITIME1:
		this->textIntTime1->Text = Convert::ToString(d.f.val.f);
		break;
	}

	if (isLogWrite)
	{
		printMessageToFile(&d,&(SysToStd(logFileName->Text+".txt")));
	}

	if ((this->textId1->Text != "") && (this->textId2->Text != "") 
	 && (d.f.PARID == System::Byte::Parse(this->textId1->Text))
		&& ((d.f.PARID == EC_TIME) || (d.f.PARID == EC_TINJ) || (d.f.PARID == EC_TPROG)
			|| (d.f.R1 == System::Byte::Parse(this->textId2->Text))))
		{
			if (isParFloat(&d))
			{
				this->textRandIn->Text = Convert::ToString(d.f.val.f);
			} else {
				this->textRandIn->Text = Convert::ToString(d.f.val.i);
			}
		}
}

void can_client::Form1::canWrite(int id1, int id2, int id3, float a)
{
	CAN_DATA data;
	BOOL fRet;

	for (int i = 0; i < 8; i++)
	{
		data.all[i] = 0;
	}

	data.f.PARID = id1;
	data.f.R1 = id2;
	data.f.val.f = a;

	for (int i = 0; i < 8; i++)
	{
		TxCanMsg_l.m_bData[i] = data.all[i];
	}
		
	fRet = writeMsg (&TxCanMsg_l);
}

void can_client::Form1::canWrite(int id1, int id2, int id3, int a)
{
	CAN_DATA data;
	BOOL fRet;

	for (int i = 0; i < 8; i++)
	{
		data.all[i] = 0;
	}

	data.f.PARID = id1;
	data.f.R1 = id2;
	data.f.R2 = id3;
	data.f.val.i = a;

	for (int i = 0; i < 8; i++)
	{
		TxCanMsg_l.m_bData[i] = data.all[i];
	}
		
	fRet = writeMsg (&TxCanMsg_l);
}

void can_client::Form1::onCanTransmit() 
{
	// Сейчас - копипаст из демо
	// TODO :
	// - проход по всем полям ввода
	// - сравнение содержимого с сохранённым представлением о текущих 
	// значениях параметров работы СКАУД
	// - отправка всех изменившихся значений

	float tmpf;
	int tmpi;

	BOOL fRet;

	try { canWrite(EC_P_M_MODE, 0, 0, static_cast<System::Int32>(this->checkManModeOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_MODE, 0, 0, static_cast<System::Int32>(this->comboModeOut->SelectedIndex + 1)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_QC, 0, 0, static_cast<System::Int32>(this->checkmanQCOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_PED, 0, 0, static_cast<System::Int32>(this->checkmanPedOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_LED, 0, 0, static_cast<System::Int32>(this->checkManLedOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_UOVT, 0, 0, static_cast<System::Int32>(this->checkmanUOVTOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_INJ, 0, 0, static_cast<System::Int32>(this->checkmanInjOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_CANS, 0, 0, static_cast<System::Int32>(this->checkCanSendOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_CANS, EC_S_M_CANST, 0, static_cast<System::Int32>(this->checkCanTimeOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_INJ, EC_S_M_IONCE, 0, static_cast<System::Int32>(this->checkinjOnceOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_INJ, EC_S_M_IN, 0, System::Int32::Parse(this->textmanNOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_QC, EC_S_M_AN, 0, static_cast<System::Int32>(this->checkmanAngleOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_QC, EC_S_M_IAN, 0, System::Single::Parse(this->textQCAnOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_QC, EC_S_M_QCT, 0, static_cast<System::Int32>(this->checkManQCtOut->Checked)); } catch (Exception^ e) {}
	//try { canWrite(EC_G_QC, EC_S_QC_T, 0, System::Single::Parse(this->textQCtOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_G_N, EC_S_NU, 0, System::Single::Parse(this->textnUOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_UOVT, EC_S_M_UOVT, 0, System::Single::Parse(this->textinjUOVTOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_G_QC, EC_S_QC_T, 0, System::Int32::Parse(this->textQCtOut->Text)); } catch (Exception^ e) {}
	try { canWrite(EC_P_M_FDBK, 0, 0, static_cast<System::Int32>(this->checkManFdbkOut->Checked)); } catch (Exception^ e) {}
	try { canWrite(EC_P_VMT, 0, 0, System::Decimal::ToSingle(this->numVMTOut->Value)); } catch (Exception^ e) {}

	/*if ((System::Int32) eng->mode != (tmpi = System::Int32::Parse(this->Mode_SKAUD->Text)))
	{
		data.f.PARID = 1;
		data.f.val.i = tmpi;
		
		for (int i = 0; i < 8; i++)
		{
			TxCanMsg_l.m_bData[i] = data.all[i];
		}
		
		fRet = writeMsg (&TxCanMsg_l);
	}
	if ((float) eng->nR = (tmpf = System::Single::Parse(this->RPM->Text)))
	{
		data.f.PARID = 2;
		data.f.val.f = tmpf;
		
		for (int i = 0; i < 8; i++)
		{
			TxCanMsg_l.m_bData[i] = data.all[i];
		}
		
		fRet = writeMsg (&TxCanMsg_l);
	}
	if ((int) eng->QCt != (tmpi = System::Int32::Parse(this->Tvprysk->Text)))
	{
		data.f.PARID = 3;
		data.f.val.i = tmpi;
		
		for (int i = 0; i < 8; i++)
		{
			TxCanMsg_l.m_bData[i] = data.all[i];
		}
		
		fRet = writeMsg (&TxCanMsg_l);
	}*/
}

BOOL can_client::Form1::writeMsg (tCanMsgStruct *pCanMsg_p)
{

BOOL    fRet    = m_fIsInitialized;
BYTE    bRet;

    //ASSERT (pCanMsg_p != NULL);

    // check if USB-CANmodul already is initialized
    if (m_fIsInitialized != FALSE)
    {
        fRet = FALSE;

        // write CAN message
        bRet = ::UcanWriteCanMsg (m_UcanHandle, pCanMsg_p);
        if (bRet != USBCAN_SUCCESSFUL)
        {
            goto Exit;
        }

        fRet = TRUE;
    }

Exit:
    return fRet;

}


extern "C" void PUBLIC UcanCallbackFktEx (tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p)
{
	HWND pEventWnd = (HWND) pArg_p;
	
    //ASSERT (pEventWnd != NULL);

    //----------------------------------------------------------------------------
    // NOTE:
    // Do not call functions of USBCAN32.DLL directly from this callback handler.
    // Use events or windows messages to notify the event to the application.
    //----------------------------------------------------------------------------

    // check event
    switch (dwEvent_p)
    {
        // hardware initialized
        case USBCAN_EVENT_INITHW:
            break;

        // CAN interface initialized
        case USBCAN_EVENT_INITCAN:
            break;

        // CAN message received
        case USBCAN_EVENT_RECEIVE:

			::PostMessage(pEventWnd, WM_UCAN_RECEIVE, (WPARAM) UcanHandle_p, 0);
            break;

        // status message received
        case USBCAN_EVENT_STATUS:
			//pEventWnd->
			::PostMessage (pEventWnd, WM_UCAN_STATUS, (WPARAM) UcanHandle_p, 0);
            break;

        // CAN interface deinitialized
        case USBCAN_EVENT_DEINITCAN:
            break;

        // hardware deinitialized
        case USBCAN_EVENT_DEINITHW:
            break;

        // unknown event
        default:
            break;
    }

}

System::Void can_client::Form1::sendButton_Click(System::Object^  sender, System::EventArgs^  e) {
	onCanTransmit();	
}

System::Void can_client::Form1::buttonRandIn_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		canWrite(	EC_PREQ,
					System::Byte::Parse(this->textId1->Text),
					System::Byte::Parse(this->textId2->Text),
					0); 
	} catch (Exception^ e) {}
}

System::Void can_client::Form1::buttonRandOut_Click(System::Object^  sender, System::EventArgs^  e) {
	try { 
		CAN_DATA dat;
		dat.f.PARID = System::Byte::Parse(this->textId1->Text);
		dat.f.R1 = System::Byte::Parse(this->textId2->Text);
		dat.f.val.f = System::Single::Parse(this->textRandOut->Text);

		if (isParFloat(&dat))
		{
			canWrite(	dat.f.PARID,
						dat.f.R1,
						0,
						dat.f.val.f);
		} else {
			canWrite(	System::Byte::Parse(this->textId1->Text),
						System::Byte::Parse(this->textId2->Text),
						0,
						System::Int32::Parse(this->textRandOut->Text));
		}
	} catch (Exception^ e) {}
}


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

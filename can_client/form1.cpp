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

    do
    {
        // read CAN message
        fRet = readMsg (&RxCanMsg);
        if (fRet != FALSE)
        {
            printMsg (&RxCanMsg);
        }

    } while (fRet != FALSE);

	if (!isInitialized)
	{
		// очистить список
		canWrite(EC_PCLR,0,0,0);		
		// запрашиваем все параметры - добавляем их в список "запроса"
		canWrite(EC_PQUE, EC_G_N, EC_S_NR,0);		
		canWrite(EC_PQUE, EC_G_N, EC_S_NU,0);		
		canWrite(EC_PQUE, EC_G_N, EC_S_DTIME,0);		
		canWrite(EC_PQUE, EC_G_QC, EC_S_QC_AN,0);		
		canWrite(EC_PQUE, EC_G_QC, EC_S_QC,0);		
		canWrite(EC_PQUE, EC_G_QC, EC_S_ADOP,0);		
		canWrite(EC_PQUE, EC_G_N, EC_S_NR,0);		
		canWrite(EC_PQUE, EC_P_VMT, 0,0);		
		canWrite(EC_PQUE, EC_G_INJ, EC_S_INJT1,0);		
		canWrite(EC_PQUE, EC_G_INJ, EC_S_INJT2,0);		
		canWrite(EC_PQUE, EC_G_INJ, EC_S_INJD1,0);		
		canWrite(EC_PQUE, EC_G_INJ, EC_S_INJD2,0);		
		canWrite(EC_PQUE, EC_T_INJPHI, EC_S_NR,0);		
		canWrite(EC_PQUE, EC_T_INJZ, 0,0);		
		canWrite(EC_PQUE, EC_T_INJN, 0,0);		
		canWrite(EC_PQUE, EC_T_INJT, 0,0);		
		canWrite(EC_PQUE, EC_T_INJCNT, 0,0);		
		canWrite(EC_PQUE, EC_P_KP, 0,0);		
		canWrite(EC_PQUE, EC_P_KI, 0,0);		
		canWrite(EC_PQUE, EC_P_KD, 0,0);		
		canWrite(EC_PQUE, EC_P_ERR, 0,0);		
		canWrite(EC_PQUE, EC_P_ERRI, 0,0);		
		canWrite(EC_PQUE, EC_P_ERRD, 0,0);		
		canWrite(EC_PQUE, EC_P_PTIME, 0,0);		
		canWrite(EC_PQUE, EC_P_ITIME, 0,0);		
		canWrite(EC_PQUE, EC_P_ITIME1, 0,0);		
		canWrite(EC_PQUE, EC_P_M_UOVT, EC_S_M_UOVT,0);
		canWrite(EC_PQUE, EC_P_M_INJ, 0,0);		
		canWrite(EC_PQUE, EC_P_M_QC, 0,0);		
		canWrite(EC_PQUE, EC_P_M_INJ, EC_S_M_IONCE,0);		
		
		isInitialized = true;
	}
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
	CAN_DATA d;
	for (int counter = 0; counter < 8; counter ++ )
		d.all[counter] = pCanMsg_p->m_bData[counter];
	unsigned char id = d.f.PARID;
	nMessage++;

	//textBox3->Text = Convert::ToString((byte)pCanMsg_p->m_bData[0],16);

	eng_mod a;
	float tmpf;

	switch (id)
	{
	case EC_TIME:
		cbHall->Checked = !cbHall->Checked;
		break;
	case EC_TINJ:
		cbInjection->Checked = !cbInjection->Checked;
		break;
	case EC_TPROG:
		cbConnection->Checked = !cbConnection->Checked;
		break;
	case EC_P_MODE:
		/*try { this->comboMode->SelectedIndex = d.f.val.i - 1; } catch (Exception^ e) {}
		if (this->comboModeOut->SelectedIndex == 0)
		{
			this->comboModeOut->SelectedIndex = this->comboMode->SelectedIndex;
		}*/
		break;
	case EC_G_N:
		switch (d.f.R1)
		{
		case EC_S_NR:
			NCurrentBox->Text = Convert::ToString(d.f.val.f);
			NCurrentValue->Text = Convert::ToString(d.f.val.f);
			if (d.f.val.f > NCurrentProgress->Maximum)
			{
				NCurrentProgress->Value = NCurrentProgress->Maximum;
			}
			else if (d.f.val.f < NCurrentProgress->Minimum)
			{
				NCurrentProgress->Value = NCurrentProgress->Minimum;
			}
			else
			{
				NCurrentProgress->Value = d.f.val.f;
			}
			break;
		case EC_S_NU:
			//this->NSetpoint->Text = Convert::ToString(d.f.val.f);
			break;
		case EC_S_DTIME:
			//this->gStep2->Text = Convert::ToString(d.f.val.f);			
			break;
		}
		break;
	case EC_G_QC:
		switch (d.f.R1)
		{
		case EC_S_QC:
			break;
		case EC_S_QC_T:
			//this->gStep2->Text = Convert::ToString((System::Object^)d.f.val.i);
			break;
		case EC_S_QC_AN:
			//this->textQCAnIn->Text = Convert::ToString((System::Object^)d.f.val.f);
			//this->textQCAn->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		case EC_S_QC_ADOP:
			//this->textBox1->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		}
		break;
	case EC_G_INJ:
		switch (d.f.R1)
		{
		case EC_S_INJT1:
			if (gStep1 == -1)
			{
				gStep1 = d.f.val.i;
				this->gStep1Box->Text = Convert::ToString((System::Object^)d.f.val.i);
			}
			break;
		case EC_S_INJT2:
			//if (gStep2 == -1)
			//{
				gStep2 = d.f.val.i;
				this->gStep2Box->Text = Convert::ToString((System::Object^)d.f.val.i);
			//}
			break;
		case EC_S_INJD1:
			if (gDuty1 == -1)
			{
				gDuty1 = d.f.val.i;
				this->gDuty1Box->Text = Convert::ToString((System::Object^)d.f.val.i);
			}
			break;
		case EC_S_INJD2:
			if (gDuty2 == -1)
			{
				gDuty2 = d.f.val.i;
				this->gDuty2Box->Text = Convert::ToString((System::Object^)d.f.val.i);
			}
			break;
		}
		break;
	case EC_P_VMT:
		if (this->VMTBox->Text == "")
		{
			this->VMTBox->Text = Convert::ToString(d.f.val.f);
		}
		break;
	case EC_P_M_MODE:
		//this->checkManModeIn->Checked = d.f.val.i;
		break;
	case EC_P_M_QC:
		switch (d.f.R1)
		{
		case EC_P0:
			manQC = d.f.val.i;
			refreshMode();
			
			switch(d.f.val.i)
			{
			case EG_MANQC_AUTO:
			case EG_MANQC_TIME:
			case EG_MANQC_ANGLE:
			case EG_MANQC_QC:
				break;
			}
			break;
		//case EC_S_M_AN:
			//this->checkmanAngleIn->Checked = d.f.val.i;
			//break;
		case EC_S_M_IAN:
			//this->textQCAnIn->Text = Convert::ToString((System::Object^)d.f.val.f);
			break;
		//case EC_S_M_QCT:
			//this->checkManQCtIn->Checked = d.f.val.i;
			//break;
		}
		break;
	case EC_P_M_INJ:
		switch (d.f.R1)
		{
		case EC_S_QC_T:
			manInj = d.f.val.i;
			refreshMode();
			break;
		case EC_S_M_IONCE:
			injOnce = d.f.val.i;
			refreshMode();
			break;
		}
		break;
	case EC_P_M_PED:
		//this->checkmanPedIn->Checked = d.f.val.i;
		break;
	case EC_P_M_LED:
		//this->checkManLedIn->Checked = d.f.val.i;
		break;
	case EC_P_M_CANS:
		switch (d.f.R1)
		{
		case EC_P0:
			//this->checkCanSendIn->Checked = d.f.val.i;
			break;
		case EC_S_M_CANST:
			//this->checkCanTimeIn->Checked = d.f.val.i;
			break;
		}
		break;
	case EC_P_M_UOVT:
		switch (d.f.R1)
		{
		case EC_P0:
			//this->checkmanUOVTIn->Checked = d.f.val.i;
			break;
		case EC_S_M_UOVT:
			//this->textinjUOVTIn->Text = Convert::ToString(d.f.val.f);
			//this->UOVT->Text = Convert::ToString(d.f.val.f);
			break;
		}
		break;
	case EC_P_M_FDBK:
		/*if (d.f.R1 == 0)
		{
			this->checkManFdbkIn->Checked = d.f.val.i;
		} else {
			fdbkData[d.f.R1-1] = d.f.val.f;
			gridFdbk->Rows[0]->Cells[d.f.R1-1]->Value = d.f.val.f;
		}*/
		break;
	case EC_P_PTIME:
		tProgTime->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_ITIME:
		tIntTime->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_ITIME1:
		tInt1Time->Text = Convert::ToString(d.f.val.f);
		break;
	case EC_P_KP:
		// TODO : если не совпадает с текущим значением, выделить жёлтым
		if (Kp == -1)
		{
			Kp = d.f.val.f;
			if ((this->KpMult->Text != "") && (Single::TryParse(this->KpMult->Text, tmpf)))
			{
				this->KpVal->Text = Convert::ToString(d.f.val.f / tmpf);
			}
			else this->KpVal->Text = Convert::ToString(d.f.val.f);
		}
		break;
	case EC_P_KI:
		if (Ki == -1)
		{
			Ki = d.f.val.f;
			if ((this->KiMult->Text != "") && (Single::TryParse(this->KiMult->Text, tmpf)))
			{
				this->KiVal->Text = Convert::ToString(d.f.val.f / tmpf);
			}
			else this->KiVal->Text = Convert::ToString(d.f.val.f);
		}
		break;
	case EC_P_KD:
		if (Kd == -1)
		{
			Kd = d.f.val.f;
			if ((this->KdMult->Text != "") && (Single::TryParse(this->KdMult->Text, tmpf)))
			{
				this->KdVal->Text = Convert::ToString(d.f.val.f / tmpf);
			}
			else this->KdVal->Text = Convert::ToString(d.f.val.f);
		}
		break;
	}

	if (isLogWrite)
	{
		printMessageToFile(&d,&(SysToStd(logFileName->Text+".txt")));
	}

	Byte id0, id1;

	if (Byte::TryParse(this->textId1->Text, id0) && Byte::TryParse(this->textId2->Text, id1) 
	 && (d.f.PARID == id0)
		&& ((d.f.PARID == EC_TIME) || (d.f.PARID == EC_TINJ) || (d.f.PARID == EC_TPROG)
			|| (d.f.R1 == id1)))
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

void can_client::Form1::onVmtSearch() 
{
	/*
	try { canWrite(EC_P_VMT, 0, 0, System::Decimal::ToSingle(this->numVMTOut->Value)); } catch (Exception^ e) {}
	for (int i = 0; i < 5000; i++);
	*/
}

void can_client::Form1::onCanTransmit() 
{
	// Сейчас - копипаст из демо
	// TODO :
	// - проход по всем полям ввода
	// - сравнение содержимого с сохранённым представлением о текущих 
	// значениях параметров работы СКАУД
	// - отправка всех изменившихся значений

	/*
	float tmpf;
	int tmpi;

	BOOL fRet;
	float res;

	canWrite(EC_P_M_MODE, 0, 0, static_cast<System::Int32>(this->checkManModeOut->Checked));
	canWrite(EC_P_MODE, 0, 0, static_cast<System::Int32>(this->comboModeOut->SelectedIndex + 1));
	canWrite(EC_P_M_QC, 0, 0, static_cast<System::Int32>(this->checkmanQCOut->Checked));
	canWrite(EC_P_M_PED, 0, 0, static_cast<System::Int32>(this->checkmanPedOut->Checked));
	canWrite(EC_P_M_LED, 0, 0, static_cast<System::Int32>(this->checkManLedOut->Checked));
	canWrite(EC_P_M_UOVT, 0, 0, static_cast<System::Int32>(this->checkmanUOVTOut->Checked));
	canWrite(EC_P_M_INJ, 0, 0, static_cast<System::Int32>(this->checkmanInjOut->Checked));
	canWrite(EC_P_M_CANS, 0, 0, static_cast<System::Int32>(this->checkCanSendOut->Checked));
	canWrite(EC_P_M_CANS, EC_S_M_CANST, 0, static_cast<System::Int32>(this->checkCanTimeOut->Checked));
	canWrite(EC_P_M_INJ, EC_S_M_IONCE, 0, static_cast<System::Int32>(this->checkinjOnceOut->Checked));
	canWrite(EC_P_M_QC, EC_S_M_AN, 0, static_cast<System::Int32>(this->checkmanAngleOut->Checked));
	canWrite(EC_P_M_QC, EC_S_M_QCT, 0, static_cast<System::Int32>(this->checkManQCtOut->Checked));
	canWrite(EC_P_M_FDBK, 0, 0, static_cast<System::Int32>(this->checkManFdbkOut->Checked));
	canWrite(EC_P_M_FDBK, 0, 0, static_cast<System::Int32>(this->checkManFdbkOut->Checked));
	
	if (Single::TryParse(this->textQCAnOut->Text, res))
		canWrite(EC_P_M_QC, EC_S_M_IAN, 0, res);
	if (Single::TryParse(this->textnUOut->Text, res))
		canWrite(EC_G_N, EC_S_NU, 0, res);
	if (Single::TryParse(this->textinjUOVTOut->Text, res))
		canWrite(EC_P_M_UOVT, EC_S_M_UOVT, 0, res);
	Int32 resi;
	if (Int32::TryParse(this->textQCtOut->Text, resi))
		canWrite(EC_G_QC, EC_S_QC_T, 0, resi);
	if (Int32::TryParse(this->textmanNOut->Text, resi))
		canWrite(EC_P_M_INJ, EC_S_M_IN, 0, resi);
	
	float KV;
	float KM;
	if (Single::TryParse(this->KpValOut->Text, KV))
	{
		if (Single::TryParse(this->KpMultOut->Text,KM))
		{
			KV *= KM;
		}
		canWrite(EC_P_KP, 0, 0, KV);
	}
	if (Single::TryParse(this->KiValOut->Text, KV))
	{
		if (Single::TryParse(this->KiMultOut->Text,KM))
		{
			KV *= KM;
		}
		canWrite(EC_P_KI, 0, 0, KV);
	}
	if (Single::TryParse(this->KdValOut->Text, KV))
	{
		if (Single::TryParse(this->KdMultOut->Text,KM))
		{
			KV *= KM;
		}
		canWrite(EC_P_KD, 0, 0, KV);
	}
	*/
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
		for (int i = 0; i < 5000; i++);	// ожидание нужно, чтобы всё успешно дошло и обработалось
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
	Byte id0;
	Byte id1;

	System::Byte::TryParse(this->textId1->Text, id0);
	System::Byte::TryParse(this->textId2->Text, id1);

	canWrite(	EC_PREQ, id0, id1, 0);
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


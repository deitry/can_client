// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// can_client.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"
#include <iostream>
#include "can_par_id.h"

using namespace System;
using namespace System::Runtime::InteropServices;

long int nMessage = 0;

System::String^ StdToSys(std::string StdStr){
	return gcnew System::String(StdStr.c_str());        
}

std::string SysToStd(System::String^ SysStr){
     using namespace Runtime::InteropServices;       
     char *v = (char*) (Marshal::StringToHGlobalAnsi(SysStr)).ToPointer();
                 std::string result = std::string(v);
                 Marshal::FreeHGlobal(System::IntPtr((void*)v));
                 return result;
 }

int isParFloat(CAN_DATA* data)
{
	switch (data->f.PARID)
	{
	case EC_G_N:
		switch (data->f.R1)
		{
		case EC_S_NR: 
		case EC_S_NU: 
		case EC_S_OMEGA:
		case EC_S_DTIME:
		case EC_S_NMIN:
		case EC_S_NMAX:
			return 1;
		}
		break;
	case EC_G_QC:
		switch (data->f.R1)
		{
		case EC_S_QC_AN:
		case EC_S_QC:
		case EC_S_ADOP:
		case EC_S_QC_ADOP:
		case EC_S_QC_MAX:
		case EC_S_QC_MIN:
		case EC_S_KQC:
		case EC_S_START:
			return 1;
		}
		break;
	case EC_P_PED:
		switch (data->f.R1)
		{
		case EC_P0: 
			return 1;
		}
		break;
	case EC_P_M_QC:
		switch (data->f.R1)
		{
		case EC_S_M_IAN: return 1;
		}
		break;
	case EC_P_M_UOVT:
		switch (data->f.R1)
		{
		case EC_S_M_UOVT: return 1;
		}
		break;
	case EC_P_M_SENS:
		switch (data->f.R1)
		{
		case EC_S_PK:
		case EC_S_TV: 
		case EC_S_D_PINJMAX:
		case EC_S_D_PINJMIN:
			return 1;
		}
		break;
	case EC_P_M_FDBK:
		if (data->f.R1 != EC_P0)
		{
			return 1;
		}
		break;
	case EC_P_KP:
	case EC_P_KI:
	case EC_P_KD:
	case EC_P_ERR:
	case EC_P_ERRI:
	case EC_P_ERRD:
	case EC_P_VMT:
	case EC_T_INJPHI:
	case EC_T_INJZ:
	case EC_T_INJN:
	case EC_T_INJT:
	case EC_P_PTIME:
	case EC_P_ITIME:
	case EC_P_ITIME1:
	case EC_P_MUN:
	case EC_P_DZONE:
		return 1;

	default:
		return 0;
	}
	return 0;
}
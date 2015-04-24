// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
#pragma once

#include <windows.h>

// ����� ���������� C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>

#include "eng_virt.h"
#include "can_par_id.h"

#define WM_UCAN_RECEIVE             (WM_USER + 1)
#define WM_UCAN_STATUS              (WM_USER + 2)
#define WM_UCAN_CONNECT             (WM_USER + 10)
#define WM_UCAN_DISCONNECT          (WM_USER + 11)
#define WM_UCAN_FATAL_DISCONNECT    (WM_USER + 12)

union CAN_DATA_VAL {
	float f;
	UINT32 i;
};

struct CAN_DATA_FIELDS {                      // bits description
    BYTE PARID;
    BYTE R1;
    BYTE R2;
    BYTE R3;
    CAN_DATA_VAL val;
};

union CAN_DATA {
    BYTE  all[8];
    CAN_DATA_FIELDS f;
};

struct TwoBytes
{
	BYTE one;
	BYTE two;
};

union PAR_HELPER
{
	WORD w;
	TwoBytes b;
};

#define DARR_SIZE	500000

extern CAN_DATA dataArr[DARR_SIZE];
extern int curI;

extern char* outFileName;
extern long int nMessage;

int printMessageToFile(CAN_DATA *data, std::string* FileName);
int printMessageToFileX(CAN_DATA *data, std::ofstream* out, int* cur_i);
void clearFile(std::string* str);
void flushToFile(std::string* FileName);

enum eng_mod { 	EC_Start = 1,		// ����
				EC_Steady,			// �������� ���
				EC_Transient,		// ������-�������
				EC_Automotive,		// ������-������
				EC_Econom,			// �������������
				EC_MaxDyn,			// ������������ ��������
				EC_Finish,			// �������
				EC_Failure,			// ������
				EC_Crash,			// ����
				EC_End};			// �����

// TODO. ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

System::String^ StdToSys(std::string StdStr);

std::string SysToStd(System::String^ SysStr);
int isParFloat(CAN_DATA* data);



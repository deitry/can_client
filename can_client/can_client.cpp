// can_client.cpp: ������� ���� �������.

#include "stdafx.h"
#include "Form1.h"

using namespace can_client;
char* outFileName = "out_log.txt";

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	
	return 0;
}

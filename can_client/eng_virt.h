#ifndef CAN_CLIENT_ENG_VIRT_H_
#define CAN_CLIENT_ENG_VIRT_H_

/**
 * �����, ������������ ����������� ������������� ������������ �����.
 * �� � ���� ���������� ��� �������� ��������. ����� �������� ���������
 * �� ���������� ���������� ����� ����� � ���������� ������� �����
 * ������ � ������ ��������� ���������� �����
 */


class CC_VInt
{
public:
	int val;
	int changed;
	
	void Set(int v, int c) {val = v; changed = c;}
};

class CC_VFloat
{
public:
	float val;
	int changed;

	void Set(float v, int c) {val = v; changed = c;}
};

class CC_VEngine
{
public:
	CC_VInt mode;
	CC_VFloat nR;
	CC_VInt QCt;

	CC_VEngine()
	{
		mode.Set(0,0);
		nR.Set(0,0);
		QCt.Set(0,0); 
	}
};

#endif
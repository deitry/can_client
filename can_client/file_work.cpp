#include "stdafx.h"
#include <ios>
#include <fstream>

int curI = 0;
CAN_DATA dataArr[DARR_SIZE];

int printMessageToFile(CAN_DATA *data, std::string *FileName)
{
	dataArr[curI++] = *data;
	
	if (curI == DARR_SIZE)
	{
		// прекращаем запись в лог
		flushToFile(FileName);
	}
	return 0;
}

PAR_HELPER h;	   

int printMessageToFileX(CAN_DATA *data, std::ofstream *out, int *cur_i)
{
   
   //if (out.fail())
   //{
   //   return 1;
   //}

   if ((data->f.PARID == EC_TIME)
	   || (data->f.PARID == EC_TPROG)
	   || (data->f.PARID == EC_TINJ)) 
   {
	   h.b.one = data->f.R2;
	   h.b.two = data->f.R3;
	   
	   *out << nMessage - curI + *cur_i << '\t'
		   << std::hex
		   << static_cast<int>(data->f.PARID) << '\t'			// метка времени
		   << std::dec
		   << static_cast<int>(data->f.R1) << '\t'
		   << h.w << '\t'
		   << data->f.val.i << '\t'
		   << std::endl;
   } else {
	   *out << nMessage - curI + *cur_i << '\t'
		   << std::hex
		   << static_cast<int>(data->f.PARID) << '\t'
		   << std::dec
		   << static_cast<int>(data->f.R1) << '\t'
		   << static_cast<int>(data->f.R2) << '\t'
		   << static_cast<int>(data->f.R3) << '\t';

	   if (isParFloat(data))
	   {
		   *out << data->f.val.f << '\t';
	   } else {
		   *out << data->f.val.i << '\t';
	   }
	   *out << std::endl;
   }
   return 0;
}

void clearFile(std::string* FileName)
{
   // очищаем файл вывода
   std::ofstream f;
   f.open(FileName->c_str());
   f.close();
}

void flushToFile(std::string* FileName)
{
	std::ofstream out;
	out.open(FileName->c_str(),std::ios_base::app);
   
	for (int i = 0; i < curI; i++)
	{
		printMessageToFileX(&(dataArr[i]), &out, &i);
	}
	curI = 0;

	out.close();
}
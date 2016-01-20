#include "stdafx.h"
#include <ios>
#include <fstream>
#include <vector>

int curI = 0;
//int setI = 0;	// счётчик настроек
CAN_DATA dataArr[DARR_SIZE];
//std:111:map<CAN_ID_FIELDS, CAN_DATA_VAL> mpParameters;
std::vector<CAN_DATA> settings;

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

// ---

int saveSetting(CAN_DATA *data)
{
	if ((data->f.PARID == EC_TIME)
		|| (data->f.PARID == EC_TINJ)
		|| (data->f.PARID == EC_TPROG)
		|| (data->f.PARID == EC_PREQ)
		|| (data->f.PARID == EC_PQUE)
		|| (data->f.PARID == EC_PCLR))
		return 0;

	// проходимся по массиву
	for (int i = 0; i < settings.size(); i ++)
	{
		// - если такой параметр уже есть - перезаписываем его значение
		if ((settings[i].f.PARID == data->f.PARID)
			&& (settings[i].f.R1 == data->f.R1)
			&& (settings[i].f.R2 == data->f.R2)
			&& (settings[i].f.R3 == data->f.R3))
		{
			settings[i].f.val = data->f.val;
			return 0;
		}
	}

	// - если нету - добавляем в конец
	settings.push_back(*data);
	
	return 0;
}

// работа с настройками - по сути недалеко уходит от лога, но не имеет привязки ко времени
int printSettingsToFile(std::string *FileName)
{
	// TODO : запрашивать все параметры и записывать их
	std::ofstream out;
	out.open(FileName->c_str());

	if (out.fail())
	{
		return 1;
	}

	for (int i = 0; i < settings.size(); i++)
	{
		int a = printSettingToFileX(&(settings[i]), &out);
		int b = a;
	}

	out.close();

	settings.clear();
	
	return 0;
}

int printSettingToFileX(CAN_DATA *data, std::ofstream *out)
{
   
   //if (out.fail())
   //{
   //   return 1;
   //}

   if ((data->f.PARID == EC_TIME)
	   || (data->f.PARID == EC_TPROG)
	   || (data->f.PARID == EC_TINJ)) 
   {
	   return 0;
   } else {
	   *out << std::hex
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
	   // TODO : комментарии к параметрам, чтобы быстрее их находить
   }
   return 0;
}

int loadSettingsFromFile(CAN_DATA *data)
{   
  return 0;
}
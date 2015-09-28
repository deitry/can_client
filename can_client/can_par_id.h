/*
 * can_par_id.h
 *
 * Содержит определения идентификаторов для передачи параметров через CAN.
 *
 * Таблицы передаются следующим образом:
 * - основной идентификатор обозначает вид таблицы,
 * - второстепенные - индекс текущего значения в этой таблице
 * (максимально может быть до трёх индексов, т.е. мы можем передавать трёхмерные таблицы)
 *
 * Таким же образом можно выделять группы параметров.
 * В пределах одной группы может быть выделено 256 идентификаторов.
 *
 *  Created on: 18.03.2015
 *      Author: Дима
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
 * Запрос на получение параметра. Формат данных в таком случае:
 * (0xFF) - (P) - (S) - (SS) - (SSS)
 */
#define EC_PREQ		0xFB		// одиночный запрос параметра
#define EC_PQUE		0xFA		// добавление параметра в список постоянной передачи
#define EC_PCLR		0xF9		// обнуление списка постоянной передачи

#define EC_P0		0x00
#define EC_BAD		0xFF
/**
 * Расшифровка сокращений:
 * - EC = Electronic Control
 * - P - Parameter - параметр
 * - G - группа параметров
 * - T - Table - таблица. Также используется для группирования
 * параметров для каждого из цилиндров
 * - S - Sub-parameter / Sub-index 1
 * индексация подпараметров начинается с 1,
 * подиндексов в таблицах и группах с 0
 * - SS - Sub-index 2
 */


#define EC_TIME			0xFE		// метка времени на момент прихода прерывания от зуба
#define EC_TINJ			0xFD		// метка времени на момент впрыска
#define EC_TPROG		0xFC		// метка времени на новом цикле программы
#define EC_P_MODE		0x01		// режим
#define EC_G_N			0x02		// группа параметров частоты вращения
#define 	EC_S_NR			0x00		// float частота вращения об/мин
#define 	EC_S_NU			0x01		// float уставка частоты вращения об/мин
#define 	EC_S_OMEGA		0x02		// float рад/с
#define 	EC_S_DTIME		0x03		// float время между прерываниями по зубьями в с

#define EC_G_QC			0x03			// группа параметров подачи
#define 	EC_S_QC_T			0x00	// int время импульса удержания в мкс
#define 	EC_S_QC_AN			0x01	// float время впрыска в углах
#define 	EC_S_QC				0x02	// float количество топлива, которое подаётся в цилиндр
#define		EC_S_ADOP			0x03	// float альфа - ограничение
#define		EC_S_QC_ADOP		0x04	// float подача - ограниченная по альфе
#define EC_P_NCYL		0x04			// int количество цилиндров
#define EC_P_PED		0x05			// float положение педали
#define 	EC_S_PEDST			0x01	// float кратность округления значений педали
#define EC_P_VMT		0x06		// float угол смещения ВМТ относительно пропущенных зубьев

#define EC_G_INJ		0x10		// параметры впрыска
#define 	EC_S_INJT1			0x00	// int продолжительность
#define 	EC_S_INJT2			0x01	// int продолжительность 
#define 	EC_S_INJD1			0x02	// int скважность
#define 	EC_S_INJD2			0x03	// int скважность

// подиндекс - номер цилиндра 0..NCYL
#define EC_T_INJPHI		0x11		// float углы, обозначающие момент впрыска
#define EC_T_INJZ		0x12		// int зуб, от которого ведётся отсчёт времени до момента впрыска
#define EC_T_INJN		0x13		// int количество впрысков в данный цилиндр с момента запуска программы
#define EC_T_INJT		0x14		// float время до впрыска, отсчитываемое от зуба injZ
#define EC_T_INJCNT		0x15

#define EC_P_M_MODE		0x21                // Флаг - разрешить ручное задание режима работы СКАУД
#define EC_P_M_QC		0x22                // Флаг manQC - разрешить ручное управление подачей
#define EG_MANQC_AUTO	0					// 0 - подача рассчитывается автоматически по ПИД-закону
#define EG_MANQC_TIME	1					// 1 - подача никак не рассчитывается, используется число g_step2Us
#define EG_MANQC_ANGLE	2					// 2 - продолжительность подачи определяется по углу injAngle
#define EG_MANQC_QC		3					// 3 - продолжительность подачи рассчитывается исходя из величины QC
// по-старому
//#define 	EC_S_M_AN			0x01        // Флаг manAngle - режим задания подачи в углах
#define 	EC_S_M_IAN			0x02        // Число injAngle - продолжительность впрыска в углах коленчатого вала
//#define 	EC_S_M_QCT			0x03        // Флаг manQCt - задание подачи в микросекундах
// --
#define EC_P_M_INJ		0x23                // Флаг manInj - ручное управление впрыском в нулевой цилиндр 
#define 	EC_S_M_IONCE		0x01        // Флаг injOnce - осуществить однократный или периодический (если manN != 0) впрыск в цилиндр
#define 	EC_S_M_IN			0x02        // Число manN - частота впрысков в сотнях микросекунд
#define 	EC_S_M_INJCYL		0x03		// цилиндр, в который осуществляется впрыск
#define 	EC_S_FDBKCYL		0x04		// цилиндр, с которого будет считываться обратная связь
#define EC_P_M_PED		0x24                // Флаг manPed - ручная установка значения педали
#define EC_P_M_CANS		0x25                // Флаг CanSend - пересылка параметров
#define		EC_S_M_CANST		0x01		// Флаг CanTime - пересылка временных меток
#define EC_P_M_UOVT		0x26                // Флаг manUOVT - ручное задание УОВТ
#define 	EC_S_M_UOVT			0x01        // Число injUOVT - угол опережения впрыска топлива
#define EC_P_M_FDBK		0x27                // Флаг manFdbk - обратная связь по току.
	// Является таблицей. Подиндекс обозначает номер значения, считанного сразу после впрыска
#define EC_P_M_LED		0x28				// флаг включение светодиодов
#define EC_P_M_SENS		0x29				// данные от оцифровки датчиков
#define 	EC_S_PK				0x01		// Pkompr
#define		EC_S_TV				0x02		// Tvozd
#define 	EC_S_D_PINJ			0x04		// Pinj давление впрыска

#define EC_T_UOVT		0x31	// таблица углов опережения впрыска
#define EC_T_SPCHAR		0x32	// внешняя скоростная характеристика
#define EC_T_NSTEADY	0x33	// таблица частоты вращения холостого хода в зав-ти от температуры
#define EC_T_QSTART		0x34	// таблица стартовой подачи топлива в зав-ти от температуры

#define EC_P_KP			0x41	// float пропорциональный к-т
#define EC_P_KI			0x42	// float к-т при интегральной составляющей
#define EC_P_KD			0x43	// float к-т при дифференциальной составляющей
#define EC_P_ERR		0x44	// float пропорциональная ошибка регулирования
#define EC_P_ERRI		0x45	// float интегральная ошибка регулирования
#define EC_P_ERRD		0x46	// float дифференциальная ошибка регулирования

#define EC_P_MUN		0x47	// float коэффициент темпа набора частоты
#define EC_P_DZONE		0x48	// float зона нечувствительности регулятора

#define EC_P_PTIME		0x51	// int время выполнения основного тела программы в мкс
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

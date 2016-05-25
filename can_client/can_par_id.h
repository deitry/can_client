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
#define 	EC_S_NR				0x00	// float частота вращения об/мин
#define 	EC_S_NU				0x01	// float уставка частоты вращения об/мин
#define 	EC_S_OMEGA			0x02	// float рад/с
#define 	EC_S_DTIME			0x03	// float время между прерываниями по зубьями в с
#define		EC_S_NMIN			0x04	// минимальное значение частоты, ниже которого система перестаёт впрыскивать
#define 	EC_S_NMAX			0x05	// верхнее ограничение частоты вращения
#define		EC_S_NRESTR			0x06	// ограничение
#define		EC_S_N_LOW			0x07	// частота вращения, ниже которой она считается "маленькой"

#define EC_G_QC			0x03			// группа параметров подачи
#define 	EC_S_QC_T			0x00	// int время импульса удержания в мкс
#define 	EC_S_QC_AN			0x01	// float время впрыска в углах
#define 	EC_S_QC				0x02	// float количество топлива, которое подаётся в цилиндр
#define		EC_S_ADOP			0x03	// float альфа - ограничение
#define		EC_S_QC_ADOP		0x04	// float подача - ограниченная по альфе
#define 	EC_S_QC_MAX			0x05	// максимальное значение подачи
#define 	EC_S_QC_MIN			0x06	// минимальное значение подачи
#define		EC_S_KQC			0x07	// переводной коэффициент кг/л -> мкс
#define 	EC_S_START			0x08	// стартовое значение подачи в мм3/цикл
#define		EC_S_QC_MAX_LOW		0x09	// верхнее ограничение подачи при низких частотах
#define		EC_S_SP_CHAR		0x0A	// включение/выключение скоростной характеристики
#define 		EC_S_SP_CHAR_CNT	0x0B	// количество точек в скоростной характеристике

#define EC_P_NCYL		0x04			// int количество цилиндров
#define EC_P_PED		0x05			// float положение педали
#define 	EC_S_PEDST			0x01	// float кратность округления значений педали
#define EC_P_VMT		0x06		// float угол смещения ВМТ относительно пропущенных зубьев

#define EC_G_INJ		0x10		// параметры впрыска
#define 	EC_S_INJT1			0x00	// int продолжительность
#define 	EC_S_INJT2			0x01	// int продолжительность 
#define 	EC_S_INJD1			0x02	// int скважность
#define 	EC_S_INJD2			0x03	// int скважность
#define		EC_S_CUR_MAX		0x04	// int значение ацп макс предел регулирования тока
#define		EC_S_CUR_MIN		0x05	// int значение ацп мин предел регулирования тока
#define		EC_S_ADC_THRESH		0x06	// int значение ацп пороговое значение для снятия значения с ацп
#define		EC_S_ADC_VAL		0x07	// int значение ацп значение с АЦП

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
#define 	EC_S_M_QALPHA		0x04	// вкл/выкл пневмокоррекции

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
#define 	EC_S_M_UOVTMAN			0x02        // Число injUOVT - угол опережения впрыска топлива
#define EC_P_M_FDBK		0x27                // Флаг manFdbk - обратная связь по току.
	// Является таблицей. Подиндекс обозначает номер значения, считанного сразу после впрыска
#define EC_P_M_LED		0x28				// флаг включение светодиодов
#define EC_P_M_SENS		0x29				// данные от оцифровки датчиков
#define 	EC_S_D_PEDAL		0x01	// педаль
#define 	EC_S_D_KEY			0x02	// ключ
#define 	EC_S_PK				0x03		// Pkompr
#define 	EC_S_D_PINJ			0x04		// Pinj давление впрыска
#define		EC_S_TV				0x05		// Tvozd
#define 	EC_S_D_PINJMAX		0x06	// верхнее ограничение давления масла
#define 	EC_S_D_PINJMIN		0x07	// нижнее ограничение давления масла
#define 	EC_S_D_PINJRESTR	0x08	// вкл/выкл ограничения по давлению масла
#define 	EC_S_PV				0x09		// давление воздуха

#define EC_T_UOVT		0x31	// таблица углов опережения впрыска
#define EC_T_SPCHAR		0x32	// внешняя скоростная характеристика
#define EC_T_NSTEADY	0x33	// таблица частоты вращения холостого хода в зав-ти от температуры
#define EC_T_QSTART		0x34	// таблица стартовой подачи топлива в зав-ти от температуры

#define EC_P_KP			0x41	// float пропорциональный к-т
#define EC_P_KI			0x42	// float к-т при интегральной составляющей
#define EC_P_KD			0x43	// float к-т при дифференциальной составляющей
#define EC_P_ERR		0x44	// float пропорциональная ошибка регулирования
#define EC_P_ERRI		0x45	// float интегральная ошибка регулирования
#define 	EC_S_ERRIMAX	0x01
#define		EC_S_CILOW		0x02;
#define EC_P_ERRD		0x46	// float дифференциальная ошибка регулирования

#define EC_P_MUN		0x47	// float коэффициент темпа набора частоты
#define		EC_S_MUN_LOW	0x01
#define EC_P_DZONE		0x48	// float зона нечувствительности регулятора

#define EC_P_PTIME		0x51	// int время выполнения основного тела программы в мкс
#define EC_P_ITIME		0x52
#define EC_P_ITIME1		0x53

#endif /* CAN_PAR_ID_H_ */

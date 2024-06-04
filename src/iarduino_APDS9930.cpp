#include "iarduino_APDS9930.h"																										//
																																	//
//		Инициализация датчика:																										//	Возвращаемое значение: результат инициализации.
bool	iarduino_APDS9930::_begin(void){																							//	Параметр: отсутствует
//			Инициируем работу с шиной I2C:																							//
			selI2C->begin();																										//	Инициируем работу с выбранной шиной I2C в качестве мастера.
//			Ждём завершение переходных процессов при включении питания:																//
			delay(5);																												//
//			Задаём параметры датчика:																								//
			if( _readByte ( APDS9930_REG_ID      ,     &val_Reg_8	) == false ){ return false; }									//	Читаем идентификатор датчика (проверяя подключён ли он).
			if( _writeByte( APDS9930_REG_ENABLE  ,		0			) == false ){ return false; }									//	Отключаем все функции датчика (включая тактирование).
			if( _writeByte( APDS9930_REG_ATIME   , (256-val_aTime)	) == false ){ return false; }									//	Задаём количество циклов интеграции АЦП освещённости.  Один цикл занимает 2,73 мс.
			if( _writeByte( APDS9930_REG_PTIME   , (256-val_pTime)	) == false ){ return false; }									//	Задаём количество циклов интеграции АЦП близости.   Один цикл занимает 2,73 мс.
			if( _writeByte( APDS9930_REG_WTIME   , (256-val_wTime)	) == false ){ return false; }									//	Задаём количество циклов до выхода из режима ожижания. Один цикл занимает 2,73 мс.
			if( _writeByte( APDS9930_REG_PPULSE  ,      val_pPulse	) == false ){ return false; }									//	Задаём количество импульсов светодиода для вычисления близости. F=62,5кГц => T=16мкс.
			if( _writeByte( APDS9930_REG_POFFSET ,		0			) == false ){ return false; }									//	Удаляем смещение показаний близости.
			if( _writeByte( APDS9930_REG_CONFIG  ,		0			) == false ){ return false; }									//	Сбрасываем конфигурацию датчика.
														val_Reg_8	   = 0;															//	Готовим переменную для записи в регистр управления.
														val_Reg_8	  |= APDS9930_VAL_CONTROL_PDIODE_ON;							//	Включаем фотодиод CH1 для вычисления близости.
			if( val_pDrive == 12  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PDRIVE_12; }else		// p 12.5мА		//	Задаём мощьность драйвера светодиода на ток в 12,5 мА.
			if( val_pDrive == 25  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PDRIVE_25; }else		// p   25мА		//	Задаём мощьность драйвера светодиода на ток в 25   мА.
			if( val_pDrive == 50  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PDRIVE_50; }else		// p   50мА		//	Задаём мощьность драйвера светодиода на ток в 50   мА.
			if( val_pDrive == 100 ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PDRIVE_100;}			// p  100мА		//	Задаём мощьность драйвера светодиода на ток в 100  мА.
			if( val_aGain  ==  1  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PGAIN_1X;  }else		// a   1X		//	Задаём коэффициент усиления при вычислении освещённости в значение 1x.
			if( val_aGain  ==  8  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_AGAIN_8X;  }else		// a   8X		//	Задаём коэффициент усиления при вычислении освещённости в значение 8x.
			if( val_aGain  == 16  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_AGAIN_16X; }else		// a  16X		//	Задаём коэффициент усиления при вычислении освещённости в значение 16x.
			if( val_aGain  == 120 ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_AGAIN_120X;}			// a 120X		//	Задаём коэффициент усиления при вычислении освещённости в значение 120x.
			if( val_pGain  ==  1  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PGAIN_1X;  }else		// p   1X		//	Задаём коэффициент усиления при вычислении близости в значение 1x.
			if( val_pGain  ==  2  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PGAIN_2X;  }else		// p   2X		//	Задаём коэффициент усиления при вычислении близости в значение 2x.
			if( val_pGain  ==  4  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PGAIN_4X;  }else		// p   4X		//	Задаём коэффициент усиления при вычислении близости в значение 4x.
			if( val_pGain  ==  8  ){					val_Reg_8	  |= APDS9930_VAL_CONTROL_PGAIN_8X;  }			// p   8X		//	Задаём коэффициент усиления при вычислении близости в значение 8x.
			if( _writeByte( APDS9930_REG_CONTROL ,		val_Reg_8	) == false ){ return false; }									//	Записываем значение переменной val_Reg_8 в регистр управления.
														val_Reg_8	   = 0;															//	Готовим переменную для записи в регистр разрешений
			//											val_Reg_8	  |= APDS9930_BIT_ENABLE_SAI									//	Указываем перейти в спящий режим если сгенерированы прерывания Proximity или ALS.
			//											val_Reg_8	  |= APDS9930_BIT_ENABLE_PIEN									//	Разрешаем генерацию прерываний (Proximity) по достижению границ близости.
			//											val_Reg_8	  |= APDS9930_BIT_ENABLE_AIEN									//	Разрешаем генерацию прерываний (ALS)       по достижению границ освещённости.
														val_Reg_8	  |= APDS9930_BIT_ENABLE_WEN;									//	Разрешаем переход в состояние ожидания между рассчётами близости и освещённости.
														val_Reg_8	  |= APDS9930_BIT_ENABLE_PEN;									//	Активируем функцию вычислений близости.
														val_Reg_8	  |= APDS9930_BIT_ENABLE_AEN;									//	Активируем функцию вычислений освещённости.
														val_Reg_8	  |= APDS9930_BIT_ENABLE_PON;									//	Включаем внутренний генератор датчика для тактирования таймеров и каналов АЦП.
			if( _writeByte( APDS9930_REG_ENABLE ,		val_Reg_8	) == false ){ return false; }									//	Записываем значение переменной val_Reg_8 в регистр разрешений.
//			Определяем минимальный период опроса датчика:																			//	
			tmr_Period	= 0;																										//	Сбрасываем период опроса датчика.
			tmr_Period += 3;																										//	Время (мс) инициализации вычислений близости.
			tmr_Period += (float)val_pPulse * 0.016;																				//	Время (мс) передачи импульсов светодиода (зависит от количества импульсов).
			tmr_Period += 3;																										//	Время (мс) ожидания перед началом интеграции АЦП.
			tmr_Period += (float)val_pTime * 3;																						//	Время (мс) выполнения циклов интеграции АЦП близости (зависит от количества циклов).
			tmr_Period += (float)val_wTime * 3;																						//	Время (мс) ожидания между вычислениями близости и освещённости. (зависит от количества циклов).
			tmr_Period += 3;																										//	Время (мс) инициализации вычислений освещённости.
			tmr_Period += (float)val_aTime * 3;																						//	Время (мс) выполнения циклов интеграции АЦП освещённости (зависит от количества циклов).
//			Сохраняем текущее время:																								//
			tmr_Start   = millis();																									//	Время (мс) завершения инициализации.
			return true;																											//	Возвращаем флаг успешной инициализаии.
}																																	//
																																	//
//		Получение освещённости в люксах:																							//	Возвращаемое значение:	освещённость (лк).
uint16_t iarduino_APDS9930::getLight(void){																							//	Параметр:				отсутствует.
//			Не позволяем опрашивать датчик чаще чем он обновит свои показания:														//
			if( millis()<tmr_Start ){ while(millis()<tmr_Start){;} }																//	Ждём
//			Cчитываем показания АЦП освещённости:																					//	
			if( _readBytes(APDS9930_REG_CH0DATA_L, arr_Reg, 4) == false ){ return 0; }												//	Читаем 4 байта в массив arr_Reg начиная с регистра APDS9930_REG_CH0DATA_L.
			uint16_t val_CH0 = arr_Reg[1]; val_CH0  <<=8; val_CH0  |= arr_Reg[0];													//	Определяем значение АЦП для фотодиода CH0 (обычный).
			uint16_t val_CH1 = arr_Reg[3]; val_CH1  <<=8; val_CH1  |= arr_Reg[2];													//	Определяем значение АЦП для фотодиода CH1 (ИК).
//			Обновряем минимальное время следующего опроса датчика.																	//	
			tmr_Start = millis()+tmr_Period;																						//	Сохраняем текущее время + время минимального периода опроса датчика.
			return _ADCtoLux(val_CH0, val_CH1);																						//	Возвращаем освещённость в люксах.
}																																	//	
																																	//
//		Получение коэффициента пульсаций источника света:																			//	Возвращаемое значение:	коэффициент пульсаций (%).
uint8_t iarduino_APDS9930::getPulsation(void){																						//	Параметр:				отсутствует.
//			Задаём параметры датчика:																								//
			val_aTime   = 2;																										//	Задаём количество циклов интеграции АЦП освещённости.  Один цикл занимает 2,73 мс.
			tmr_Period	= 0;																										//	Сбрасываем период опроса датчика.
			tmr_Period += 3;																										//	Время (мс) инициализации вычислений освещённости.
			tmr_Period += (float)val_aTime * 3;																						//	Время (мс) выполнения циклов интеграции АЦП освещённости (зависит от количества циклов).
			if( _writeByte( APDS9930_REG_ATIME, (256-val_aTime) )==false )															//	Записываем новое количество циклов интеграции АЦП освещённости.
				{val_aTime = APDS9930_DEF_ATIME; reset(); return false; }															//	В случае провала, перезагружаем все параметры.
			if( _writeByte( APDS9930_REG_ENABLE, APDS9930_BIT_ENABLE_AEN|APDS9930_BIT_ENABLE_PON )==false )							//	Оставляем активными только тактирование и функцию вычислений освещённости.
				{val_aTime = APDS9930_DEF_ATIME; reset(); return false; }															//	В случае провала, перезагружаем все параметры.
//			Определяем переменные для расчетов:																						//
			float ths_Lux  = 0;																										//	Текущая освещённость.
			float min_Lux  = 65535.0;																								//	Минимальная освещённость.
			float max_Lux  = 0;																										//	Максимальная освещённость.
			float cen_Lux  = 0;																										//	Среднее значение освещённости.
//			Выполняем чтение освещённости APDS9930_DEF_CYCLE раз:																	//
			for(uint8_t i=0; i<APDS9930_DEF_CYCLE; i++){																			//	Выполняем цикл for в течении APDS9930_DEF_CYCLE раз.
//				Определяем текущее и среднее значение освещённости, минимум, и максимум за всё время чтений:						//
				ths_Lux = getLight();																								//	Получаем текущую освещённость.
				if( min_Lux > ths_Lux ){ min_Lux = ths_Lux; }																		//	Минимальная    освещённость за все время чтений.
				if( max_Lux < ths_Lux ){ max_Lux = ths_Lux; }																		//	Максимальная   освещённость за все время чтений.
				cen_Lux += ths_Lux;																									//	Сумма значений освещённости за все время чтений.
			}	cen_Lux /= APDS9930_DEF_CYCLE;																						//	Усреднённая    освещённость за все время чтений.
//			Вычисляем коэффициент пульсаций:																						//
			ths_Lux  = max_Lux-min_Lux;																								//	    max_Lux - min_Lux
			ths_Lux /= cen_Lux*2;																									//	K = ----------------- * 100%
			ths_Lux *= 100;																											//	       2 * cen_Lux
//			Восстанавливаем параметры датчика:																						//
			val_aTime = APDS9930_DEF_ATIME;																							//	Восстанавливаем количество циклов интеграции АЦП при измерении освещённости.
			reset();																												//	Перезагружаем все параметры.
//			Корректируем и выводим полученный коэффициент пульсаций:																//
			if(ths_Lux>100){ths_Lux=100;}																							//	Результат не может превышать 100%.
			if(ths_Lux<=0 ){ths_Lux=0;  }																							//	Результат не может быть отрицательным.
			return ths_Lux;																											//	Возвращаем результат.
}																																	//	
																																	//
//		Получение близости в абстрактных единицах:																					//	Возвращаемое значение:	близость.
uint16_t iarduino_APDS9930::getProximity(void){																						//	Параметр:				отсутствует.
//			Не позволяем опрашивать датчик чаще чем он обновит свои показания:														//
			if( millis()<tmr_Start ){ while(millis()<tmr_Start){;} }																//	Ждём
//			Cчитываем показания АЦП близости:																						//	
			if( _readBytes(APDS9930_REG_PDATA_L, arr_Reg, 2) == false ){ return 0; }												//	Читаем 2 байта в массив arr_Reg начиная с регистра APDS9930_REG_PDATA_L.
			uint16_t val_CH1 = arr_Reg[1]; val_CH1  <<=8; val_CH1  |= arr_Reg[0];													//	Определяем значение АЦП для фотодиода CH1 (ИК).
//			Обновряем минимальное время следующего опроса датчика.																	//	
			tmr_Start = millis()+tmr_Period;																						//	Сохраняем текущее время + время минимального периода опроса датчика.
			return _ADCtoLen(val_pPulse, val_CH1);																					//	Возвращаем значение АЦП скорректированное по количеству импульсов светодиода.
}																																	//	
																																	//
//		Установка тока светодиода:																									//	Возвращаемое значение:	результат установки.
bool	iarduino_APDS9930::setCurrentDiode(uint8_t current){																		//	Параметр:				ток светодиода.
			if( (current == APDS9930_VAL_CONTROL_PDRIVE_12 )||																		//	Если мощьность драйвера светодиода задана на ток в 12,5 мА.
				(current == APDS9930_VAL_CONTROL_PDRIVE_25 )||																		//	или  мощьность драйвера светодиода задана на ток в 25   мА.
				(current == APDS9930_VAL_CONTROL_PDRIVE_50 )||																		//	или  мощьность драйвера светодиода задана на ток в 50   мА.
				(current == APDS9930_VAL_CONTROL_PDRIVE_100)){																		//	или  мощьность драйвера светодиода задана на ток в 100  мА, то ...
											val_Reg_8	 = current;																	//	Задаём мощьность драйвера светодиода.
											val_Reg_8	|= APDS9930_VAL_CONTROL_PDIODE_ON;											//	Включаем фотодиод CH1 для вычисления близости.
				if( val_aGain  ==  1  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_PGAIN_1X;  }else		// a   1X					//	Задаём коэффициент усиления при вычислении освещённости в значение 1x.
				if( val_aGain  ==  8  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_AGAIN_8X;  }else		// a   8X					//	Задаём коэффициент усиления при вычислении освещённости в значение 8x.
				if( val_aGain  == 16  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_AGAIN_16X; }else		// a  16X					//	Задаём коэффициент усиления при вычислении освещённости в значение 16x.
				if( val_aGain  == 120 ){	val_Reg_8	|= APDS9930_VAL_CONTROL_AGAIN_120X;}			// a 120X					//	Задаём коэффициент усиления при вычислении освещённости в значение 120x.
				if( val_pGain  ==  1  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_PGAIN_1X;  }else		// p   1X					//	Задаём коэффициент усиления при вычислении близости в значение 1x.
				if( val_pGain  ==  2  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_PGAIN_2X;  }else		// p   2X					//	Задаём коэффициент усиления при вычислении близости в значение 2x.
				if( val_pGain  ==  4  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_PGAIN_4X;  }else		// p   4X					//	Задаём коэффициент усиления при вычислении близости в значение 4x.
				if( val_pGain  ==  8  ){	val_Reg_8	|= APDS9930_VAL_CONTROL_PGAIN_8X;  }			// p   8X					//	Задаём коэффициент усиления при вычислении близости в значение 8x.
				if( _writeByte( APDS9930_REG_CONTROL, val_Reg_8	) == false ){ return false; }										//	Записываем значение переменной val_Reg_8 в регистр управления.
			}	else														{ return false; }										//	Если мощьность драйвера светодиода задана не корректно, то возвращаем ошибку.
}																																	//	
																																	//
//		Преобразование значений АЦП в люксы:																						//	Возвращаемое значение:	освещённость (лк).
uint16_t iarduino_APDS9930::_ADCtoLux(uint16_t Ch0, uint16_t Ch1){																	//	Параметры:				АЦП фотодиода CH0, АЦП фотодиода CH1.
			float    ALSIT  = 2.73 * (float)val_aTime;																				//	Определяем время интеграции показаний АЦП освещённости.
			float    iac    = 0;																									//	Определяем ИК скорректированное показание АЦП.
			float    iac1	= (Ch0        ) - (Ch1 * cft_B); if(iac1>iac){iac=iac1;}												//	iac = max (iac1,iac2,0);
			float    iac2	= (Ch0 * cft_C) - (Ch1 * cft_D); if(iac2>iac){iac=iac2;}												//	iac = max (iac1,iac2,0);
			float    lpc    = (cft_GA * cft_DF) / (ALSIT * val_aGain);																//	Определяем количество люкс на цикл.
			return			  (iac * lpc);																							//	Возвращаем показания в люксах.
}																																	//
																																	//
//		Корректировка значения АЦП по количеству импульсов светодиода.																//	Возвращаемое значение:	близость (0...1023).
uint16_t iarduino_APDS9930::_ADCtoLen(uint8_t pulse, uint16_t Ch1){																	//	Параметр:				АЦП фотодиода CH1.
			float len = (float)Ch1;																									//
			len = len - (((1023.0-len)*(float)pulse)/100.0);																		//
			if( len<0 ){len=0;}																										//
			return len;																												//
}																																	//
																																	//
//		Запись байта в один регистр:																								//	Возвращаемое значение:	результат записи (true/false).
bool	iarduino_APDS9930::_writeByte(uint8_t reg, uint8_t data){																	//	Параметры:				reg - номер регистра, data - байт данных для записи.
			bool	result=false;																									//	Определяем флаг для хранения результата записи.
			uint8_t	sumtry=10;																										//	Определяем переменную для подсчёта количества оставшихся попыток записи.
			do{	result = selI2C->writeByte(val_Addr, reg|APDS9930_BIT_ADDRESS_COMMAND|APDS9930_VAL_ADDRESS_TYPE_INC, data);			//	Записываем в регистр reg модуля val_Addr байт данных data.
				sumtry--;	if(!result){delay(1);}																					//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
			}	while		(!result && sumtry>0);																					//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
			delay(2);																												//	Ждём применения модулем записанных данных.
			return result;																											//	Возвращаем результат записи (true/false).
}																																	//
																																	//
//		Чтение нескольких байт данных из регистров в массив:																		//	Возвращаемое значение:	результат чтения (true/false).
bool	iarduino_APDS9930::_readBytes(uint8_t reg, uint8_t *data, uint8_t sum){														//	Параметры:				reg - номер первого регистра, data - указатель на массив получающий данные, sum - количество читаемых байт.
			bool	result=false;																									//	Определяем флаг для хранения результата чтения.
			uint8_t	sumtry=10;																										//	Определяем переменную для подсчёта количества оставшихся попыток чтения.
			do{	result = selI2C->readBytes(val_Addr, reg|APDS9930_BIT_ADDRESS_COMMAND|APDS9930_VAL_ADDRESS_TYPE_INC, data, sum);	//	Считываем из модуля val_Addr, начиная с регистра reg, в массив data, sum байт.
				sumtry--;	if(!result){delay(1);}																					//	Уменьшаем количество попыток чтения и устанавливаем задержку при неудаче.
			}	while		(!result && sumtry>0);																					//	Повторяем чтение если оно завершилось неудачей, но не более sumtry попыток.
			return result;																											//	Возвращаем результат чтения (true/false).
}																																	//
																																	//


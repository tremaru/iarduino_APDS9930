//  ОПРЕДЕЛЕНИЕ ОСВЕЩЁННОСТИ, ПУЛЬСАЦИЙ И БЛИЗОСТИ ПРЕПЯТСТВИЙ:           //
//  Требуется установить библиотеку <iarduino_I2C_Software.h>             //  https://iarduino.ru/file/627.html
                                                                          //
//  Датчик освещенности и приближения APDS-9930 (Trema-модуль):           //  https://iarduino.ru/shop/Sensory-Datchiki/datchik-osveschennosti-i-priblizheniya-apds-9930-trema-modul-v2-0.html
//  Информация о подключении модулей к шине I2C:                          //  https://wiki.iarduino.ru/page/i2c_connection/
//  Информация о датчике и описание библиотеки:                           //  https://wiki.iarduino.ru/page/trema-APDS-9930/
                                                                          //
#include <iarduino_I2C_Software.h>                                        //  Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_APDS9930.
SoftTwoWire sWire(3,4);                                                   //  Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                                          //
#include <iarduino_APDS9930.h>                                            //  Подключаем библиотеку для работы с датчиком APDS-9930.
iarduino_APDS9930 apds;                                                   //  Объявляем объект apds для работы с датчиком APDS-9930.
                                                                          //  Если у датчика не стандартный адрес, то его нужно указать: iarduino_APDS9930 apds(0xFF);
void setup(){                                                             //
//  Инициируем передачу данных в монитор последовательного порта:         // 
    Serial.begin(9600);                                                   //  Инициируем работу с шиной UART на скорости 9600 бит/сек.
//  Инициируем работу датчика:                                            //
    bool i = apds.begin(&sWire);                                          //  Инициируем работу с датчиком APDS-9930, указав ссылку на объект для работы с шиной I2C на которой находится датчик.
    if(i){                                                                //  Если инициализация прошла успешно, то ...
           Serial.println("Initialization OK!");                          //  Выводим сообщение об успешной инициализации датчика.
    }else{ Serial.println("Initialization ERROR!"); while(1); }           //  Иначе, выводим сообщение об ошибке инициализации датчика.
}                                                                         //  Инициировать датчик можно без проверки: apds.begin(&sWire);
                                                                          //
void loop(){                                                              //
    Serial.print((String) "Light="     + apds.getLight()     + " lx, " ); //  Выводим освещённость в люксах.
    Serial.print((String) "Proximity=" + apds.getProximity() + ", "    ); //  Выводим близость препятствий от 0 (нет препятствий), до 1023 (минимальное расстояние до препятствия).
    Serial.print((String) "Pulsation=" + apds.getPulsation() + "%.\r\n"); //  Выводим коэффициент пульсаций источника света в %.
//  Приостанавливаем выполнение скетча на десятую долю секунды:           //
    delay(100);                                                           //
}                                                                         //
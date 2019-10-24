[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino\_APDS9930

**This is a library for Arduino IDE. It allows to work with [APDS-9930 Distance and Light Sensor](https://iarduino.ru/shop/Sensory-Datchiki/datchik-toka-5a-trema-modul-v2-0.html), module made by iArduino.ru**

**Данная библиотека для Arduino IDE позволяет работать с [Trema датчиком освещенности и приближения APDS-9930](https://iarduino.ru/shop/Sensory-Datchiki/datchik-toka-5a-trema-modul-v2-0.html) от [iArduino.ru](https://iarduino.ru)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/trema-APDS-9930/#h3_3)


## Назначение функций:

**Подключаем библиотеку** 

```C++
#include <iarduino_APDS9930> // Подключаем библиотеку iarduino_APDS9930 для работы с модулем.
```

**Создаём объект** 

```C++
iarduino_APDS9930 ОБЪЕКТ; // Создаём объект для работы с методами библиотеки.
```

**Инициализация работы** 

```C++
ОБЪЕКТ.begin(); // Инициализация работы модуля.
```

**Перезагрузка модуля**

```C++
ОБЪЕКТ.reset(); // Перезагрузка модуля.
```

**Чтение освещённости** 

```C++
ОБЪЕКТ.getLight(); // Чтение освещённости в люксах.
```

**Чтение коэффициента пульсаций** 

```C++
ОБЪЕКТ.getPulsation(); // Чтение коэффициента пульсаций источника света в %..
```

**Чтение близости к препятствию** 

```C++
ОБЪЕКТ.getProximity(); // Чтение близости к препятствию.
```

**Задать ток светодиода** 

```C++
ОБЪЕКТ.setCurrentDiode( ТОК ); // Задать ток протекающий через светодиод датчика.
```


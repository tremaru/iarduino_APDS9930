[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino\_APDS9930

Библиотека iarduino\_APDS9930 позволяет работать с [Trema датчиком освещенности и приближения APDS-9930](https://iarduino.ru/shop/Sensory-Datchiki/datchik-osveschennosti-i-priblizheniya-apds-9930-trema-modul-v2-0.html), получать освещённость, коэффициент пульсаций источника света и близость препятствий.

Данная библиотека может использовать как аппаратную, так и программную реализацию шины I2C.

Подробное описание работы с библиотекой, находится в разделе [Wiki - Датчик освещенности и приближения APDS-9930 (Trema-модуль v2.0)](https://wiki.iarduino.ru/page/trema-APDS-9930/).

Назначение функций:

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

**Чтение коэффициента** 

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


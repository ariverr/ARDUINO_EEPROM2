#include <EEPROM2.h>
//  Sample for EEPROM library v2
//  see http://freeduino.ru for details

void setup() {

  // Будем считать количество сбросов платы Ардуино.
  // Создадим счетчик типа 'unsigned long',
  // который занимает 4 ячейки памяти. Запишем значение в EEPROM по адресу 8  -
  // Это займет 4 адреса 8, 9, 10, 11.
  // Как мы знаем, setup() вызывается один раз после сброса Arduino. Мы прочтем
  // Счетчик из EEPROM, увеличим его, и запишем обратно в EEPROM.
  // Затем напечатаем счетчик в последовательный порт.
  long counter;
  // Переменную long прочтем из EEPROM так:
  //EEPROM_read_mem(8, &counter, sizeof(counter));
  //                ^  ^         ^- размер данных (4 байта для 'long' )
  //                |  \- адрес переменной в RAM
  //                \-EEPROM адрес
  // Или можносделать проще:
  EEPROM_read(8, counter);

  counter++;

  // Запишем счетчик в EEPROM. Можно использовать команду EEPROM_write_mem
  // аналог EEPROM_read_mem, или EEPROM_write

  EEPROM_write(8, counter);

  Serial.begin(9600);
  Serial.print("It's reset #"); Serial.println(counter, DEC);

  // --- другой пример ---
  // Здесь мы покажем, что EEPROM_write и EEPROM_read могут
  // работать с любыми типами данных, включая массивы.
  // Запишем массив чисел [8] 'INT' в EEPROM по адресу 32.
  //Это займет 16 байт (потому что 'INT' обладает размером 2 байта)
  // От 32 до 47.
  int my_array[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  EEPROM_write(32, my_array);
  // заполним массив нулями
  int i;
  for (i = 0; i < 8; i++) {
    my_array[i] = 0;
  }

  // напечатаем в порт наши нули
  for (i = 0; i < 8; i++) {
    Serial.print(my_array[i], DEC); Serial.print(" ");
  }
  Serial.println();
  // заполним массив значениями из EEPROM:
  EEPROM_read(32, my_array);
 
  for (i = 0; i < 8; i++) {
    Serial.print(my_array[i], DEC); Serial.print(" ");
  }
  Serial.println();
  // after running this sketch you can remove 'EEPROM_write(32, my_array);' line,
  // and see, that contents of EEPROM is saved after reset or power loss.
}

void loop() {
}

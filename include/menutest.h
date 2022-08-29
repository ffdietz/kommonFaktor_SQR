// /**
//  * Name:     Arduino - Menu for LCD I2C + Encoder
//  * Autor:    Alberto Gil Tesa
//  * Web:      http://giltesa.com
//  * License:  CC BY-NC-SA 3.0
//  * Date:     2017/07/29
//  *
//  * Arduino pinout:
//  *         _______________
//  *        |      USB      |
//  *        |13           12|
//  *        |3V3          11|
//  *        |AREF         10|
//  *        |A0            9|
//  *        |A1            8|
//  *        |A2            7|
//  *        |A3            6|
//  *    LCD |A4            5|
//  *    LCD |A5            4| ENCODER CLK
//  *        |              3| ENCODER DT
//  *        |              2| ENCODER SW
//  *        |5V          GND|
//  *        |RST         RST|
//  *        |GND   1/INT2/RX|
//  *        |VIN   0/INT3/TX|
//  *        |MISO         SS|
//  *        |SCK        MOSI|
//  *        |_______________|
//  *
//  */

// /**
//  *  LIBRERIAS NECESARIAS PARA EL FUNCIONAMIENTO DEL CODIGO
//  */


// /**
//  *  OBJETOS DE LAS LIBRERIAS
//  */
// LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Configuracion del LCD I2C (puede ser necesario cambiar el primer valor con la direccion del LCD)

// /**
//  *  MACROS, CONSTANTES, ENUMERADORES, ESTRUCTURAS Y VARIABLES GLOBALES
//  */

// #define COUNT(x) sizeof(x) / sizeof(*x) // Macro para contar el numero de elementos de un array
// const byte pENCO_SW = 2;                // Pin encoder SW
// const byte pENCO_DT = 3;                // Pin encoder DT
// const byte pENCO_CLK = 4;               // Pin encoder CLK
// const byte rowsLCD = 4;                 // Filas del LCD
// const byte columnsLCD = 20;             // Columnas del LCD
// const byte iARROW = 0;                  // ID icono flecha
// const byte bARROW[] = {                 // Bits icono flecha
//     B00000, B00100, B00110, B11111,
//     B00110, B00100, B00000, B00000};

// enum Button
// {
//   Unknown,
//   Ok,
//   Left,
//   Right
// } btnPressed; // Enumerador con los diferentes botones disponibles
// enum Screen
// {
//   Menu1,
//   Menu2,
//   Flag,
//   Number
// }; // Enumerador con los distintos tipos de submenus disponibles

// const char *txMENU[] = { // Los textos del menu principal, la longitud maxima = columnsLCD-1, rellenar caracteres sobrantes con espacios.
//     "Ver tiempo         ",
//     "Unid. tiempo       ",
//     "Eje X tiempo       ",
//     "Eje Y tiempo       ",
//     "Ver temperatura    ",
//     "Unid. temp.        ",
//     "Eje X temp.        ",
//     "Eje Y temp.        ",
//     "Guardar y salir    ",
//     "Salir              "};
// const byte iMENU = COUNT(txMENU); // Numero de items/opciones del menu principal

// enum eSMENU1
// {
//   Milliseconds,
//   Seconds,
//   Minutes,
//   Hours
// };                         // Enumerador de las opciones disponibles del submenu 1 (tienen que seguir el mismo orden que los textos)
// const char *txSMENU1[] = { // Textos del submenu 1, longitud maxima = columnsLCD-2, rellenar caracteres sobrantes con espacios
//     "   Milisegundos   ",
//     "     Segundos     ",
//     "     Minutos      ",
//     "      Horas       "};

// enum eSMENU2
// {
//   GradeC,
//   GradeF
// };                         // Enumerador de las opciones disponibles del submenu 2 (tienen que seguir el mismo orden que los textos)
// const char *txSMENU2[] = { // Textos del submenu 1, longitud maxima = columnsLCD-2, rellenar caracteres sobrantes con espacios
//     "     Grados C     ",
//     "     Grados F     "};

// /* ESTRUCTURAS CONFIGURACION */
// struct MYDATA
// { // Estructura STRUCT con las variables que almacenaran los datos que se guardaran en la memoria EEPROM
//   int initialized;
//   int time_show;
//   int time_unit;
//   int time_x;
//   int time_y;
//   int temp_show;
//   int temp_unit;
//   int temp_x;
//   int temp_y;
// };
// union MEMORY
// { // Estructura UNION para facilitar la lectura y escritura en la EEPROM de la estructura STRUCT
//   MYDATA d;
//   byte b[sizeof(MYDATA)];
// } memory;

// /**
//  * INICIO Y CONFIGURACION DEL PROGRAMA
//  */
// void start()
// {
//   pinMode(pENCO_SW, INPUT_PULLUP);
//   pinMode(pENCO_DT, INPUT_PULLUP);
//   pinMode(pENCO_CLK, INPUT_PULLUP);

//   // Carga la configuracion de la EEPROM, y la configura la primera vez:
//   readConfiguration();

//   // Inicia el LCD:
//   lcd.begin(columnsLCD, rowsLCD);
//   lcd.createChar(iARROW, bARROW);

//   // Imprime la informacion del proyecto:
//   lcd.setCursor(0, 0);
//   lcd.print(" Menu LCD + Encoder ");
//   lcd.setCursor(0, 1);
//   lcd.print("    giltesa.com     ");
//   lcd.setCursor(0, 2);
//   lcd.print("   Ver.  2017/07    ");
//   lcd.setCursor(0, 4);
//   for (int i = 0; i < columnsLCD; i++)
//   {
//     lcd.print(".");
//     delay(150);
//   }
//   lcd.clear();
// }

// /**
//  * PROGRAMA PRINCIPAL
//  */
// void run()
// {
//   static unsigned long tNow = 0;
//   static unsigned long tPrevious = 0;

//   tNow = millis();
//   btnPressed = readButtons();

//   if (btnPressed == Button::Ok)
//     openMenu();

//   // Pinta la pantalla principal cada 1 segundo:
//   if (tNow - tPrevious >= 1000)
//   {
//     tPrevious = tNow;

//     if (memory.d.time_show == 1 || memory.d.temp_show == 1)
//       lcd.clear();

//     if (memory.d.time_show == 1)
//     {
//       lcd.setCursor(memory.d.time_x, memory.d.time_y);
//       switch (memory.d.time_unit)
//       {
//       case eSMENU1::Milliseconds:
//         lcd.print(tNow);
//         lcd.print(" Mil");
//         break;
//       case eSMENU1::Seconds:
//         lcd.print(tNow / 1000);
//         lcd.print(" Seg");
//         break;
//       case eSMENU1::Minutes:
//         lcd.print(tNow / 1000 / 60);
//         lcd.print(" Min");
//         break;
//       case eSMENU1::Hours:
//         lcd.print(tNow / 1000 / 60 / 60);
//         lcd.print(" Hor");
//         break;
//       }
//     }

//     if (memory.d.temp_show == 1)
//     {
//       lcd.setCursor(memory.d.temp_x, memory.d.temp_y);
//       switch (memory.d.temp_unit)
//       {
//       case eSMENU2::GradeC:
//         lcd.print(getTemp());
//         lcd.print(" C");
//         break;
//       case eSMENU2::GradeF:
//         lcd.print(1.8 * getTemp() + 32);
//         lcd.print(" F");
//         break;
//       }
//     }
//   }
// }

// /**
//  *  MUESTRA EL MENU PRINCIPAL EN EL LCD.
//  */
// void openMenu()
// {
//   byte idxMenu = 0;
//   boolean exitMenu = false;
//   boolean forcePrint = true;

//   lcd.clear();

//   while (!exitMenu)
//   {
//     btnPressed = readButtons();

//     if (btnPressed == Button::Left && idxMenu - 1 >= 0)
//     {
//       idxMenu--;
//     }
//     else if (btnPressed == Button::Right && idxMenu + 1 < iMENU)
//     {
//       idxMenu++;
//     }
//     else if (btnPressed == Button::Ok)
//     {
//       switch (idxMenu)
//       {
//       case 0:
//         openSubMenu(idxMenu, Screen::Flag, &memory.d.time_show, 0, 1);
//         break;
//       case 1:
//         openSubMenu(idxMenu, Screen::Menu1, &memory.d.time_unit, 0, COUNT(txSMENU1) - 1);
//         break;
//       case 2:
//         openSubMenu(idxMenu, Screen::Number, &memory.d.time_x, 0, columnsLCD - 1);
//         break;
//       case 3:
//         openSubMenu(idxMenu, Screen::Number, &memory.d.time_y, 0, rowsLCD - 1);
//         break;
//       case 4:
//         openSubMenu(idxMenu, Screen::Flag, &memory.d.temp_show, 0, 1);
//         break;
//       case 5:
//         openSubMenu(idxMenu, Screen::Menu2, &memory.d.temp_unit, 0, COUNT(txSMENU2) - 1);
//         break;
//       case 6:
//         openSubMenu(idxMenu, Screen::Number, &memory.d.temp_x, 0, columnsLCD - 1);
//         break;
//       case 7:
//         openSubMenu(idxMenu, Screen::Number, &memory.d.temp_y, 0, rowsLCD - 1);
//         break;
//       case 8:
//         writeConfiguration();
//         exitMenu = true;
//         break; // Salir y guardar
//       case 9:
//         readConfiguration();
//         exitMenu = true;
//         break; // Salir y cancelar cambios
//       }
//       forcePrint = true;
//     }

//     if (!exitMenu && (forcePrint || btnPressed != Button::Unknown))
//     {
//       forcePrint = false;

//       static const byte endFor1 = (iMENU + rowsLCD - 1) / rowsLCD;
//       int graphMenu = 0;

//       for (int i = 1; i <= endFor1; i++)
//       {
//         if (idxMenu < i * rowsLCD)
//         {
//           graphMenu = (i - 1) * rowsLCD;
//           break;
//         }
//       }

//       byte endFor2 = graphMenu + rowsLCD;

//       for (int i = graphMenu, j = 0; i < endFor2; i++, j++)
//       {
//         lcd.setCursor(1, j);
//         lcd.print((i < iMENU) ? txMENU[i] : "                    ");
//       }

//       for (int i = 0; i < rowsLCD; i++)
//       {
//         lcd.setCursor(0, i);
//         lcd.print(" ");
//       }
//       lcd.setCursor(0, idxMenu % rowsLCD);
//       lcd.write(iARROW);
//     }
//   }

//   lcd.clear();
// }

// /**
//  * MUESTRA EL SUBMENU EN EL LCD.
//  *
//  * @param menuID    ID del menu principal para usarlo como titulo del submenu
//  * @param screen    Segun el tipo, se representara el submenu de una forma u otra.
//  * @param value     Puntero a la variable que almacena el dato, y que se modificara.
//  * @param minValue  Valor minimo que puede tener la variable.
//  * @param maxValue  Valor maximo que puede tener la variable.
//  */
// void openSubMenu(byte menuID, Screen screen, int *value, int minValue, int maxValue)
// {
//   boolean exitSubMenu = false;
//   boolean forcePrint = true;

//   lcd.clear();

//   while (!exitSubMenu)
//   {
//     btnPressed = readButtons();

//     if (btnPressed == Button::Ok)
//     {
//       exitSubMenu = true;
//     }
//     else if (btnPressed == Button::Left && (*value) - 1 >= minValue)
//     {
//       (*value)--;
//     }
//     else if (btnPressed == Button::Right && (*value) + 1 <= maxValue)
//     {
//       (*value)++;
//     }

//     if (!exitSubMenu && (forcePrint || btnPressed != Button::Unknown))
//     {
//       forcePrint = false;

//       lcd.setCursor(0, 0);
//       lcd.print(txMENU[menuID]);

//       lcd.setCursor(0, 1);
//       lcd.print("<");
//       lcd.setCursor(columnsLCD - 1, 1);
//       lcd.print(">");

//       if (screen == Screen::Menu1)
//       {
//         lcd.setCursor(1, 1);
//         lcd.print(txSMENU1[*value]);
//       }
//       else if (screen == Screen::Menu2)
//       {
//         lcd.setCursor(1, 1);
//         lcd.print(txSMENU2[*value]);
//       }
//       else if (screen == Screen::Flag)
//       {
//         lcd.setCursor(columnsLCD / 2 - 1, 1);
//         lcd.print(*value == 0 ? "NO" : "SI");
//       }
//       else if (screen == Screen::Number)
//       {
//         lcd.setCursor(columnsLCD / 2 - 1, 1);
//         lcd.print(*value);
//         lcd.print(" ");
//       }
//     }
//   }

//   lcd.clear();
// }

// /**
//  *  LEE (Y CONFIGURA LA PRIMERA VEZ) LA MEMORIA EEPROM CON LA CONFIGURACION DE USUARIO
//  */
// void readConfiguration()
// {
//   for (int i = 0; i < sizeof(memory.d); i++)
//     memory.b[i] = EEPROM.read(i);

//   if (memory.d.initialized != 'Y')
//   {
//     memory.d.initialized = 'Y';
//     memory.d.time_show = 1;
//     memory.d.time_unit = 1;
//     memory.d.time_x = 0;
//     memory.d.time_y = 0;
//     memory.d.temp_show = 1;
//     memory.d.temp_unit = 0;
//     memory.d.temp_x = 0;
//     memory.d.temp_y = 1;
//     writeConfiguration();
//   }
// }

// /**
//  *  ESCRIBE LA MEMORIA EEPROM CON AL CONFIGURACION DE USUARIO
//  */
// void writeConfiguration()
// {
//   for (int i = 0; i < sizeof(memory.d); i++)
//     EEPROM.write(i, memory.b[i]);
// }

// /**
//  *  LEE LOS DISTINTOS BOTONES DISPONIBLES Y DEVUELVE EL QUE HAYA SIDO PULSADO
//  *      Este bloque de codigo varia dependiendo del tipo de teclado conectado, en mi blog estan
//  *      disponibles los ejemplos para teclados digitales, analogicos, y este para encoder rotatorio.
//  *      Al cambiar de tipo de teclado hay que adaptar tambien el resto de codigo para que haga uso de cada boton segun queramos.
//  */
// Button readButtons()
// {
//   static boolean oldA = HIGH;
//   static boolean newA = LOW;
//   static boolean newB = LOW;

//   btnPressed = Button::Unknown;
//   newA = digitalRead(pENCO_DT);
//   newB = digitalRead(pENCO_CLK);

//   if (!oldA && newA)
//   {
//     btnPressed = !newB ? Button::Left : Button::Right;
//     delay(50);
//   }
//   else if (!digitalRead(pENCO_SW))
//   {
//     while (!digitalRead(pENCO_SW))
//       ;
//     btnPressed = Button::Ok;
//     delay(50);
//   }

//   oldA = newA;
//   return btnPressed;
// }

// /**
//  *  DEVUELVE LA TEMPERATURA DEL SENSOR INTERNO DEL MICROCONTROLADOR (NO TODOS LOS MODELOS DE ARDUINO LO TIENEN)
//  */
// double getTemp()
// {
//   ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
//   ADCSRA |= _BV(ADEN);
//   delay(20);
//   ADCSRA |= _BV(ADSC);
//   while (bit_is_set(ADCSRA, ADSC))
//     ;
//   return (ADCW - 324.31) / 1.22;
// }
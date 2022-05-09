#include <LiquidCrystal_I2C.h>
//inisialisasi LCD
LiquidCrystal_I2C lcd(0x27,16,2);//menggunakan LCD 16x2
#include <Arduino_FreeRTOS.h> //library Free Real Time Operation System

//prototipe adalah sebuah fungsi tanpa isi karena memang hanya sebuah deklarasi saja.
//manfaat dari prototipe fungsi, pertama kita tahu bahwa setiap fungsi dalam bahasa C harus didefinisikan
//sebelum digunakan. Jadi jika sebuah fungsi akan dipakai dalam rutin utama main()

//maka fungsi tersebut harus didefinisikan diatas fungsi main()
void TaskBlink1(void*pvParameters); //prototipe fungsi blink1
void TaskBlink2(void*pvParameters); //prototipe fungsi blink2
void TaskBlink3(void*pvParameters); //prototipe fungsi blink2
void Taskprint(void*pvParameters);  //prototipe fungsi print text
void Taskpotensio(void*pvParameters); //prototipe fungsi analogRead pada A0
void Taskpotensio(void*pvParameters); //prototipe fungsi analogRead pada A0

int LED1=5;int LED2=6;int LED3=7; //pendefinisian OUTPUT 
void setup() {
  lcd.init(); //inisialisasi lcd
  lcd.backlight();
//=============================
Serial.begin(9600);
//xTaskCreate(TaskFunction_t pvTaskCode, const char * const pcName, uint16_t uStackDepth, void*pvParameters, UBaseType_t uxPriority, TaskHandle*pxCreatedTask)
//pembuatan task, dengan argument (memanggil fungsi, "nama dari task", 128, NULL, number priority, NULL)
xTaskCreate(TaskBlink1,"Task1",128,NULL,1,NULL); 
xTaskCreate(TaskBlink2,"Task2",128,NULL,1,NULL);
xTaskCreate(TaskBlink3,"Task3",128,NULL,1,NULL);
xTaskCreate(Taskprint,"Task4",128,NULL,1,NULL);
xTaskCreate(Taskpotensio,"task5",128,NULL,1,NULL);
vTaskStartScheduler();
}
void loop() 
{}
/*
   perbedaan while(1) dan while(0) di C atau C++, apabila statemen dalam sebuah while
   masih benar maka isi dari sebuah fungsi while akan melakukan eksekusi kembali
   while(1) atau while selain nilai 0 maka digunakan untuk infinite loop. 
   tidak ada syarat untuk while, karena 1 atau nilai bukan nol ada, maka kondisinya selalu benar      
*/
//===========================================

/*
 * vTaskDelay(waktu dalam milisecond/portTICK_PERIOD_MS)
 * portTICK_PERIOD_MS berfunsi sebagai nilai pembagi dalam fungsi vTaskDelay, agar menjadi realtime
 * 
 * 
 */
  void TaskBlink1(void*pvParameters)//membuat fungsi void untuk blink1 
  {
    pinMode(LED1, OUTPUT);//setiap 2 detik mati dan 2 detik nyala
    while(1)
    {
      digitalWrite(LED1,HIGH);
      vTaskDelay(2000/portTICK_PERIOD_MS);
      digitalWrite(LED1,LOW);
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }
  }

    void TaskBlink2(void*pvParameters)
  {
    pinMode(LED2, OUTPUT); //setiap 0.5 detik 
    while(1)
    {
      digitalWrite(LED2,HIGH);
      vTaskDelay(500/portTICK_PERIOD_MS);
      digitalWrite(LED2,LOW);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
  }
    void TaskBlink3(void*pvParameters)
  {
    pinMode(LED3, OUTPUT); //setiap 1 detik
    while(1){
      digitalWrite(LED3,HIGH);
      vTaskDelay(1000/portTICK_PERIOD_MS);
      digitalWrite(LED3,LOW);
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
    void Taskprint(void*pvParameters)
  {
      int counter=0;
      while(1)
      {
        counter++;
        lcd.setCursor(0,0);
        lcd.print("counter=");
        lcd.setCursor(9,0);
        lcd.print(counter);
        vTaskDelay(500/portTICK_PERIOD_MS);
        lcd.clear();
      }
   }
    void Taskpotensio(void*pvParameters)
    {
      pinMode(A1,INPUT);
      while(1){
        int i=map(analogRead(A1),0,1023,0,100);
        lcd.setCursor(0,1);
        lcd.print("nilai_pot=");
        lcd.setCursor(10,1);
        lcd.print(int(i));
        vTaskDelay(500/portTICK_PERIOD_MS);
      }
    }

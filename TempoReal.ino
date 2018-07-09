#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void TSK_A( void *pvParameters ); // Declara a funcao da Tarefa A
void TSK_B( void *pvParameters ); // Declara a funcao da Tarefa B


#define CAPACITY  3 // burst time de A e B
#define A_PERIOD  5 //periodo da tarefa A
#define B_PERIOD  8 //periodo da tarefa B

void setup() {
  Serial.begin (9600); // Define o baud rate em 9600
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  // put your setup code here, to run once:
  // Cria-se as Tarefas
     xTaskPeriodicCreate( TSK_A, ( const char * ) "A", configMINIMAL_STACK_SIZE, NULL, 1, NULL, A_PERIOD);      
     xTaskPeriodicCreate( TSK_B, ( const char * ) "B", configMINIMAL_STACK_SIZE, NULL, 1, NULL, B_PERIOD);
     vTaskStartScheduler(); 
           
}

void loop() {
  // put your main code here, to run repeatedly: 
}

// Função executada pela tarefa A
static void TSK_A( void *pvParameters )
{
   unsigned int i = 0;
   TickType_t xLastWakeTimeA;
   const TickType_t xFrequency = A_PERIOD;
   volatile int count = CAPACITY;
   xLastWakeTimeA = 0;
   
   while(1)
   {   
    TickType_t xTime = xTaskGetTickCount ();

    TickType_t x;
    Serial.println("TSK_A Executing\n");
    while(count != 0)
    {
      if(( x = xTaskGetTickCount() ) > xTime)
      {
        xTime = x;
      }
    }
      
    count = CAPACITY;
    vTaskDelayUntil( &xLastWakeTimeA, xFrequency );
     
  }
}

// Função executada pela tarefa A
static void TSK_B( void *pvParameters )
{
   unsigned int i = 0;
   TickType_t xLastWakeTimeB;
   const TickType_t xFrequency = B_PERIOD;
   volatile int count = CAPACITY;
   xLastWakeTimeB = 0;
   
   while(1)
   {   
    TickType_t xTime = xTaskGetTickCount ();

    TickType_t x;
    Serial.println("TSK_B Executing\n");
    while(count != 0)
    {
      if(( x = xTaskGetTickCount() ) > xTime)
      {
        xTime = x;
      }
    }
      
    count = CAPACITY;
    vTaskDelayUntil( &xLastWakeTimeB, xFrequency );
     
  }
}



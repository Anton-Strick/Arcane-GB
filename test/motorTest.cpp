#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>

#define RXD2 16
#define TXD2 17
#define DIAG_PIN           15         // STALL motor 2
#define EN_PIN             14         // Enable
#define DIR_PIN            4          // Direction
#define STEP_PIN           2          // Step
#define SERIAL_PORT        Serial2    // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS     0b00       // TMC2209 Driver address according to MS1 and MS2
#define R_SENSE            0.11f      // E_SENSE for current calc.  
#define STALL_VALUE        2          // [0..255]

hw_timer_t * timer1 = NULL;
TMC2209Stepper driver(&SERIAL_PORT, R_SENSE , DRIVER_ADDRESS );


void IRAM_ATTR onTimer() {
  // Serial.println("Timer");
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
} 

void activate_interrupt();

void setup() {
  Serial.begin(115200);         // Init serial port and set baudrate
  while(!Serial);               // Wait for serial port to connect
  Serial.println("\nStart...");
  SERIAL_PORT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(DIAG_PIN ,INPUT);
  pinMode(EN_PIN ,OUTPUT);
  pinMode(STEP_PIN ,OUTPUT);
  pinMode(DIR_PIN ,OUTPUT);

  digitalWrite(EN_PIN ,LOW);
  digitalWrite(DIR_PIN ,HIGH);

  driver.begin();
  driver.toff(4);
  driver.blank_time(24);
  driver.rms_current(500); 
  driver.microsteps(8);
  driver.TCOOLTHRS(0xFFFFF); // 20bit max
  driver.semin(0);
  driver.semax(2);
  driver.shaft(false);
  driver.sedn(0b01);
  driver.SGTHRS(STALL_VALUE);

  activate_interrupt();
}

void loop() {
 static uint32_t last_time=0;
 static uint32_t iteration = 0;
 uint32_t ms = millis();
 if(((ms-last_time) > 100)) { //run every 0.1s
    last_time = ms;

    Serial.printf("%d ", iteration);
    Serial.print(driver.SG_RESULT(), DEC);
    Serial.print(" ");
    Serial.println(driver.cs2rms(driver.cs_actual()), DEC);
    if (iteration > 250) {
      digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
      iteration = 0;
    }
    else iteration++;
  }
}

void activate_interrupt() {
  {
    cli();//stop interrupts
    timer1 = timerBegin(3, 16, true); // Initialize timer 4. Se configura el timer,  ESP(0,1,2,3)
                                 // prescaler of 8, y true es una bandera que indica si la interrupcion se realiza en borde o en nivel
    timerAttachInterrupt(timer1, &onTimer, true); //link interrupt with function onTimer
    timerAlarmWrite(timer1, 10000, true); //En esta funcion se define el valor del contador en el cual se genera la interrupción del timer
    timerAlarmEnable(timer1);    //Enable timer        
    sei();//allow interrupts
  }
}
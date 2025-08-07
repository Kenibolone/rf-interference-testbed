#include <SPI.h>
#include <RF24.h>

SPIClass SPI1(FSPI);  
SPIClass SPI2(HSPI);  

// NRF Module 1 (on SPI1)
#define CE1 3
#define CSN1 4
RF24 radio1(CE1, CSN1);

// NRF Module 2 (on SPI2)
#define CE2 8
#define CSN2 9
RF24 radio2(CE2, CSN2);

enum JammerMode {
  IDLE,
  TARGET_CHANNEL,
  RANDOM_SWEEP,
  AGGRESSIVE_BLAST
};

JammerMode currentMode = IDLE;

void setupNRF(RF24 &radio, uint8_t ce_pin, uint8_t channel) {
  pinMode(ce_pin, OUTPUT);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(false);
  radio.setRetries(0, 0);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.setChannel(channel);

  radio.write_register(0x1D, 0x06);
  radio.write_register(0x00, 0x3E); 

  delay(2);
  digitalWrite(ce_pin, HIGH);  
}

//First thing that the person will see in the cmd prompt
void showMenu()
{
  Serial.println(F("===== CYPHER JAMMER ====="));
  Serial.println(F("1. Target specific wifi channel"));
  Serial.println(F("2. Random sweep (Wi-Fi + BLE)"));
  Serial.println(F("3. BLE flood spoof [coming soon]"));
  Serial.println(F("4. Aggressive static flood"));
  Serial.println(F("5. Exit"));
  Serial.println(F(">> "));
}


void setup() {
  Serial.begin(115200);
  delay(500);
  
  // SPI1 (VSPI)
  SPI1.begin(5, 7, 6, CSN1);
  radio1.begin(&SPI1);
  setupNRF(radio1, CE1, 44);  

  // SPI2 (HSPI)
  SPI2.begin(10, 12, 11, CSN2);
  radio2.begin(&SPI2);
  setupNRF(radio2, CE2, 69); 

  Serial.println("Jammer online."); //Well technically this is the first thing the user will see
  showMenu();
}


void loop() {
  if (Serial.available()){
    String input = Serial.readStringUntil('\n');

    if (input=="1"){
      Serial.print("Enter Wifi channel (1-13): ");
      while (!Serial.available());
      int wifiCh = Serial.readStringUntil('\n').toInt();
      uint8_t nrfCh = constrain((wifiCh - 1)*5 + 2, 0, 83);
      Serial.printf("Target Wifi CH %d (NRF CH %d)\n", wifiCh, nrfCh);
      radio1.setChannel(nrfCh);
      radio2.setChannel(nrfCh);
      currentMode = TARGET_CHANNEL;
    }

    else if (input == "2"){
      Serial.println("Start random sweep...");
      currentMode = RANDOM_SWEEP;
    }

    else if (input == "4"){
      Serial.println("Aggressive flood started.");
      radio1.setChannel(3);
      radio2.setChannel(3);
      currentMode = AGGRESSIVE_BLAST;
    }

    else if (input == "5"){
      Serial.println("Stopping jamming.");
      currentMode = IDLE;
    }
    showMenu();
  }

  switch (currentMode){
    case TARGET_CHANNEL:
      break;
    case RANDOM_SWEEP:{
      uint8_t ch1 = random(1, 84);
      uint8_t ch2 = random(1, 84);
      radio1.setChannel(ch1);
      radio2.setChannel(ch2);
      Serial.printf("Sweep: Ch1=%d, Ch2=%d\n", ch1, ch2);
      delay(100);
      break;
    }
    case AGGRESSIVE_BLAST:{
      radio1.setChannel(3 + random(0, 2));
      radio2.setChannel(3 + random(0, 2));
      delay(5);
      break;
    }
    case IDLE:
    default:
      delay(100);
      break;
  }
}




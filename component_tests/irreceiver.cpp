#include <IRremote.h>

#define RECV_PIN 9 

void setup() {
    Serial.begin(9600);
    Serial.println("IR Receiver ready,");
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); 
}

void loop() {
    if (IrReceiver.decode()) { 
        Serial.print("IR Code received: ");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 
        IrReceiver.resume(); 
    }
}

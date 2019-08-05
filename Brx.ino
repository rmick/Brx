//------------------------------------------------------------------------------
// Include the IRremote library header
//
#include <IRremote.h>

//------------------------------------------------------------------------------
// Tell IRremote which Arduino pin is connected to the IR Receiver (TSOP4838)
//
int recvPin = 11;
IRrecv irrecv(recvPin);



#define TEAM_RED            0
#define TEAM_BLUE           1
#define TEAM_YELLOW         2
#define TEAM_GREEN          3

#define BITMASK_TAGS        0x78000
#define BITMASK_PLAYERID    0x7E000
#define BITMASK_DAMAGE      0x1FE0
#define BITMASK_UNKNOWN     0x1C
#define BITMASK_PARITY      0x3

//------------------------------------------------------------------------------
// Create some variables
//
unsigned int teamID     = 255;
unsigned int playerID   = 255;
unsigned int tagDamage  = 0;
unsigned int tagType    = 255;
unsigned int parity     = 255;
unsigned int unknown    = 255;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115000);   // Status message will be sent to PC at 115000 baud
    irrecv.enableIRIn();  // Start the receiver
}

void loop() { 
    // put your main code here, to run repeatedly:
    decode_results  results;        // Somewhere to store the results

  if (irrecv.decode(&results)) 
  {  // Grab an IR code
     if (results.decode_type == BRX)
     {
        Serial.println("----------------------------------------------");
        Serial.print("New BRX packet received: ");
        Serial.print(results.value, HEX);
        Serial.print("\t("); Serial.print(results.bits, DEC); Serial.println(" bits)");
        
        decodeBrx(results.value);
     }
     irrecv.resume();              // Prepare for the next value
  }
}


//------------------------------------------------------------------------------
// Decode BRX packet
//
void decodeBrx(unsigned long data32bit)
{
    parity      = data32bit & B00000011;
    unknown     = data32bit & B00011100;
    tagDamage   = data32bit & 0x1FE0;
    teamID      = data32bit & 0x6000;
    playerID    = data32bit & 0x1F8000;
    tagType     = data32bit & 0x1e00000;
    Serial.print("Team ID    = "); Serial.println(teamID);
    Serial.print("Player ID  = "); Serial.println(playerID);
    Serial.print("TagT ype   = "); Serial.println(tagType);
    Serial.print("Tag Damage = "); Serial.println(tagDamage);
    Serial.print("Unknown    = "); Serial.println(unknown);
    Serial.print("Parity     = "); Serial.println(parity);
    Serial.println("");
}

#include <IRremote.h>

#define IR_RIGHT    0xE9B51828
#define IR_LEFT     0xA574865B
#define IR_UP       0x3E0C7005
#define IR_DOWN     0x503D6F71
#define IR_ENTER    0x25D2E369
#define IR_PLAY     0xC578C8FD  //Space  play
#define IR_STOP     0x9FFBF334  //x      0
#define IR_ESC      0x6463F65D  //Esc
#define IR_VOL_DOWN 0x47071827
#define IR_VOL_UP   0xAA849FD1

#define KEY_UP_ARROW       82
#define KEY_DOWN_ARROW     81
#define KEY_LEFT_ARROW     80
#define KEY_RIGHT_ARROW    79
#define KEY_RETURN         40
#define KEY_ESC            41
#define KEY_SPACE          44
#define KEY_MINUS          45
#define KEY_PLUS           46
#define KEY_X              27

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
uint8_t buf[8] = { 0 };

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
    unsigned long code = results.value;
    //Serial.println(code, HEX);
    switch(code) {
      case IR_UP:
        sendKey(KEY_UP_ARROW);
        break;
      case IR_DOWN:
        sendKey(KEY_DOWN_ARROW);
        break;
      case IR_LEFT:
        sendKey(KEY_LEFT_ARROW);
        break;
      case IR_RIGHT:
        sendKey(KEY_RIGHT_ARROW);
        break;
      case IR_ENTER:
        sendKey(KEY_RETURN);
        break;
      case IR_PLAY:
        sendKey(KEY_SPACE);
        break;
      case IR_STOP:
        sendKey(KEY_X);
        break;
      case IR_ESC:
        sendKey(KEY_ESC);
        break;
      case IR_VOL_DOWN:
        sendKey(KEY_MINUS);
        break;
      case IR_VOL_UP:
        sendKey(KEY_PLUS);
        break;
    }
    irrecv.resume();
  }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  // Release key  
}

void sendKey(int keyNum){
  buf[2] = keyNum;
  Serial.write(buf, 8);
  releaseKey();
}

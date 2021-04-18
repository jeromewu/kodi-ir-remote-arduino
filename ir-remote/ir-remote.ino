#include <IRremote.h>

#define IR_RIGHT    0xF80700DF
#define IR_LEFT     0xB84700DF
#define IR_UP       0xE51A00DF
#define IR_DOWN     0xB74800DF
#define IR_ENTER    0xF90600DF
#define IR_PLAY     0xA55A00DF  //Space  play
#define IR_STOP     0xA25D00DF  //x      0
#define IR_ESC      0xE81700DF  //Esc
#define IR_EXIT     0xFC0300DF  //Alt+F4
#define IR_BS       0xF50A00DF  //Backspace
#define IR_MENU     0xE71800DF  //c
/*
 *#define IR_VOL_DOWN 0x240C9161
 *#define IR_VOL_UP   0xA26409C9
 */

#define IR_INTERNAL_MONITOR_ONLY   0xA95600DF
#define IR_EXTERNAL_MONITOR_ONLY   0xA85700DF
#define IR_START_KODI              0xA45B00DF
#define IR_OUTPUT_AUDIO            0xE01F00DF

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
#define KEY_1              30
#define KEY_2              31 
#define KEY_K              14
#define KEY_A              4
#define KEY_C              6
#define KEY_F4             61
#define KEY_BS             42

#define LEFT_CTRL   0
#define LEFT_SHIFT  1
#define LEFT_ALT    2
#define LEFT_GUI    3
#define RIGHT_CTRL  4
#define RIGHT_SHIFT 5
#define RIGHT_ALT   6
#define RIGHT_GUI   7

const int RECV_PIN = 7;
const uint8_t MODIFIER_MASKS[8] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};
IRrecv irrecv(RECV_PIN);
// decode_results results;
uint8_t buf[8] = { 0 };
int altAndCtrl[] = {LEFT_ALT, LEFT_CTRL};
int alt[] = {LEFT_ALT};

void setup(){
  pinMode(13, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
  // irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode()){
    unsigned long code = irrecv.decodedIRData.decodedRawData;
    //Serial.println(code, HEX);
    switch(code) {
      case IR_UP:
        sendKey(KEY_UP_ARROW, 0, 0);
        break;
      case IR_DOWN:
        sendKey(KEY_DOWN_ARROW, 0, 0);
        break;
      case IR_LEFT:
        sendKey(KEY_LEFT_ARROW, 0, 0);
        break;
      case IR_RIGHT:
        sendKey(KEY_RIGHT_ARROW, 0, 0);
        break;
      case IR_ENTER:
        sendKey(KEY_RETURN, 0, 0);
        break;
      case IR_PLAY:
        sendKey(KEY_SPACE, 0, 0);
        break;
      case IR_STOP:
        sendKey(KEY_X, 0, 0);
        break;
      case IR_ESC:
        sendKey(KEY_ESC, 0, 0);
        break;
      case IR_MENU:
        sendKey(KEY_C, 0, 0);
        break;
      case IR_BS:
        sendKey(KEY_BS, 0, 0);
        break;
      case IR_INTERNAL_MONITOR_ONLY:
        sendKey(KEY_1, altAndCtrl, 2);
        break;
      case IR_EXTERNAL_MONITOR_ONLY:
        sendKey(KEY_2, altAndCtrl, 2);
        break;
      case IR_START_KODI:
        sendKey(KEY_K, altAndCtrl, 2);
        break;
      case IR_OUTPUT_AUDIO:
        sendKey(KEY_A, altAndCtrl, 2);
        break;
      case IR_EXIT:
        sendKey(KEY_F4, alt, 1);
        break;
      /*
       *case IR_VOL_DOWN:
       *  sendKey(KEY_MINUS);
       *  break;
       *case IR_VOL_UP:
       *  sendKey(KEY_PLUS);
       *  break;
       */
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

void sendKey(int keyNum, int *modifiers, int modifiersLen) {
  for (int i = 0; i < modifiersLen; i++) {
    buf[0] = buf[0] | MODIFIER_MASKS[modifiers[i]];
  }
  buf[2] = keyNum;
  Serial.write(buf, 8);
  releaseKey();
}

// How to send AT command easily

//you may use software serial or other serial
#define ATSerial Serial
#define DEBUGSerial Serial1

#define isDEBUG true

void setup(){
    ATSerial.begin(115200);
    DEBUGSerial.begin(115200);
}

void loop(){
    String tempSerial;
    ATReturnCheck("Sending AT...",
                    "AT\r\n", 
                    "AT\r\r\n\r\nOK\r\n", 
                    isDEBUG, true, 1000,
                    tempSerial);
    
}


/**
 * Function desctiption
 * ATReturnCheck: 
 *      fun: Send the AT command and check the return message
 *      var: DEBUG_Message [in] String to display in debug terminal (for viewing stage)
 *      var: Command [in] String to be send, no need \r\n at the end
 *      var: checkMessage [in] String to be check with the return message
 *                 --> Optional when bool forcePass [in] = false;
 *      var: isPrintDEBUG [in] bool to decide show DEBUG_Message or not
 *      var: forcePass [in] true: it will keep sending Command with timeout interval (deadlock may occur)
 *                             --> useful to ensure some setting is donw successfully
 *      var: timeout [in] in millisecond, Allow time for the target device response
 *                             --> depend on the speed of the target device
 *      var &returnedSerial [out] Address of String when return the AT return back to user.
 *      return [out] bool, ture: checkMessage is same
 *      eg:
 *      ATReturnCheck("Sending AT...",
                    "AT\r\n", 
                    "AT\r\r\n\r\nOK\r\n", 
                    isDEBUG, true, 1000,
                    tempSerial);

        - The function will do the job of Sending AT....
        It will send "AT\r\n" to the target device and wait 1000 message
        Since forcePass is set to be true, 
        will check the return message from the target device whether is "AT\r\r\n\r\nOK\r\n" or not
            if yes; break the loop
            if no; keep sending AT\r\n
        User can get back the return message from tempSerial String.
 */
bool ATReturnCheck(
  String DEBUG_Message,  String Command, String checkMessage, 
  bool isPrintDEBUG,  bool forcePass, int timeout,
  String& returnedSerial
  ){

  bool isReturnSame;
  bool whileLoopFlag = true;

  DEBUGSerial.print(DEBUG_Message);
  while(true){
    ATSerial.print(Command);
    ATSerial.flush();
    delay(timeout); 
    returnedSerial = ATSerial.readString();   
    if (isPrintDEBUG){
      DEBUGSerial.println();
      //DEBUGSerial.println(Serial1.readString());
      DEBUGSerial.print(returnedSerial);
    }

    isReturnSame = (returnedSerial == checkMessage);
    if(isReturnSame){ 
      //Serial.println("done"); 
      return true;
    }
    
    if(!forcePass){
      return isReturnSame;
    }
    Serial.print("."); 
    }
}


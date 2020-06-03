#include "SIM900.h"
 
#include <SoftwareSerial.h>
 
#include "sms.h"
 
#include "call.h"
 
CallGSM call;
 
SMSGSM sms;
 
char number[20];
 
byte stat = 0;
 
char value_str[5];
 
int trangthai = 0; //dùng xác định trạng thái thiết bị
 
void setup()
 
{
 
    pinMode(12, OUTPUT);
 
    digitalWrite(12, LOW);
 
    Serial.begin(9600);
 
    Serial.println("GSM Shield testing.");
 
    if (gsm.begin(2400))
 
        Serial.println("\nstatus=READY");
 
    else Serial.println("\nstatus=IDLE");
 
}
 
void loop()
 
{
 
    stat = call.CallStatusWithAuth(number, 1, 5); //kiểm tra trạng thái xem có cuộc gọi nào đến không
 
    //Nếu có số được lưu trong sim từ vị trí 1 đến 5
 
    if (stat == CALL_INCOM_VOICE_AUTH) {
 
        call.HangUp(); //gác máy khỏi tốn hehehe!
 
 
        if (trangthai == 0)
 
        {
 
            digitalWrite(12, HIGH);
 
            //sms.SendSMS(number, "Da bat"); //gửi tin nhắn phản hồi trạng thái, cái này tốn tiền,mọi người có thể bỏ đi!
 
            trangthai = 1;
 
        } else
 
        {
 
            if (trangthai == 1)
 
            {
 
                digitalWrite(12, LOW);
 
               // sms.SendSMS(number, "Da tat");
 
                trangthai = 0;
 
            }
 
        }
 
    }
 
 
}

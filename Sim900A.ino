#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
 
SMSGSM sms;
 
int numdata;
boolean started = false; //trạng thái modul sim
char smstext[160]; // nội dung tin nhắn
char number[20]; // số điện thoại format theo định dạng quốc tế
 
void setup(){
  Serial.begin(9600);
  Serial.println("Gui va nhan tin nhan");
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");
  
  if(started){
    sms.SendSMS("+841662266559", "Online");
  }
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
}
 
void loop() {
  if(started){
    char pos; //địa chỉ bộ nhớ sim (sim luu tối đa 40 sms nên max pos = 40)
    pos = sms.IsSMSPresent(SMS_UNREAD); // kiểm tra tin nhắn chưa đọc trong bộ nhớ
    //hàm này sẽ trả về giá trị trong khoảng từ 0-40
    if((int)pos){//nêu có tin nhắn chưa đọc
      if(sms.GetSMS(pos, number, smstext, 160)){
        Serial.print("So dien thoại: ");
        Serial.println(number);
        Serial.print("Noi dung tin nhan: ");
        Serial.println(smstext);
        if(strcmp(smstext,"LEDON")==0){//so sánh 2 chuỗi
          digitalWrite(12, HIGH);
          Serial.println("Bat led");
        } else {
          Serial.println("Co tin nhan den nhung sai cu phap");
        }
      }
      sms.DeleteSMS(byte(pos));//xóa sms vừa nhận
    }
    
    delay(1000);
  }
}

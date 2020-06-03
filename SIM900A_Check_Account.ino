#include "SIM900.h"
#include "SoftwareSerial.h"
#include "sms.h"
#include "call.h"
CallGSM call;
SMSGSM sms;
char state[50], msg[50], resp[50], c2[20]="NAPTIEN", phong[100], ahihi[100]="AT+CUSD=1,\"*100*",ohoho[100]="#\"", so[30];//khoi tao cac xau ki tu
char smstext[160];//noi dung tin nhan den
char number[20]= "+841662266559";//so dien thoai tin nhan den theo dinh dang quoc te
int numdata;//bien nay dung cho doc du lieu
int flag=0;   
 
void setup() 
{
  Serial.begin(9600);
 
  Serial.println("GSM Shield testing.");
 
  if (gsm.begin(2400))
 
    Serial.println("\nstatus=READY");
 
  else Serial.println("\nstatus=IDLE");
  delay(200);
  sms.SendSMS("01662266559", "Hello Anh Tung");
}
 
void loop() {
 
    char pos; //địa chỉ bộ nhớ sim (sim luu tối đa 40 sms nên max pos = 40)
    pos = sms.IsSMSPresent(SMS_UNREAD); // kiểm tra tin nhắn chưa đọc trong bộ nhớ
    //hàm này sẽ trả về giá trị trong khoảng từ 0-40
    if((int)pos){//nêu có tin nhắn chưa đọc
      if(sms.GetSMS(pos, number, smstext, 160)){
        Serial.print("So dien thoai: ");
        Serial.println(number);
        Serial.print("Noi dung tin nhan: ");
        Serial.println(smstext);
        if(strstr (smstext, c2)!=NULL){
          strncpy(so, smstext+7, 13);
          so[30]='\0';
          Serial.println(so);
          strcat(ahihi, so);
          strcat(ahihi, ohoho);
          Serial.println(ahihi);
          delay(100);
          gsm.SimpleWriteln(ahihi);   
          delay(5000);//phai doi 5 giay moi gui va doc het du lieu
          char resp[100];//khoi tao xau cho noi dung tra ve
          gsm.read(resp, 100); //lay no
          Serial.println(resp);//in ra lan 2
          delay(100);          
          strncpy(phong, resp+17, 100);
          Serial.println(phong);//in ra thanh cong
          delay(100);
          sms.SendSMS(number, phong); //nhan tin tra ve noi dung
          delay(100);
        } 
      
        else 
        {
          if(strcmp(smstext,"KIEMTRA")==0)//so sánh 2 chuỗi,neu trong SMS gui toi co cuoi ky tu KIEMTRA moi thuc hien kiem tra
          {
            delay(100);
            gsm.SimpleWriteln("AT+CUSD=1,\"*101#\""); 
            delay(5000);
            char resp[100];
            gsm.read(resp, 100);
            delay(100);
            strncpy(phong, resp+17, 100);
            Serial.println(phong);//in ra thanh cong
            delay(100);
            sms.SendSMS(+841662266559, phong); //nhan tin tra ve noi dung
            delay(100);
          }
         }
      }
      sms.DeleteSMS(byte(pos));//xóa sms vừa nhận     
  }
  delay(1000);
}

//arduino

#include "Arduino.h"
#include "SoftwareSerial.h"
void printDetail(uint8_t type, int value);

// Pour  la DFPlayer

#include "DFRobotDFPlayerMini.h"         // bibliothèque du DF PLAYER mini
SoftwareSerial mySoftwareSerial(11,10); // on associe les entrée de RX et TX 
DFRobotDFPlayerMini myDFPlayer;

//  Pour les led

int Led1 = 22;  // assosciation de variables aux sorties digitales
int Led2 = 25;
int Led3 = 28;
int Led4 = 31;
int Led5 = 34;
int Led6 = 37;


//  Pour l'écran

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
                                   
//  Pour les capteurs de force

int fsrAnalogPin1 = A0;    // associations de variables aux entrées analogique
int fsrAnalogPin2 = A2;
int fsrAnalogPin3 = A4;
int fsrAnalogPin4 = A6;
int fsrAnalogPin5 = A8;
int fsrAnalogPin6 = A10;

int fsrReading1;   // variable prenant les valeurs des entrées analogues
int fsrReading2; 
int fsrReading3;
int fsrReading4; 
int fsrReading5; 
int fsrReading6; 

//button

int pushButton1 = 43;     // variable prenant les valeurs des sorties digitale des boutons
int pushButton2 = 46;
int pushButton3 = 51;  


// Variable dont l'initialisation et la définition est obligatoire

int kit = 1 ;

int Vnb=20 ;

int rif = 1 ;

int n = 0;




void Volume(){                                              // La Fonction Volume retourne une nouvelle valeur choisie pour le volume (de 10 à 30)
  
  int buttonState2 = digitalRead(pushButton2);               // la fonction est appelé par le boutons 2
     
  while (buttonState2 == 0){

    lcd.setCursor(3,0);
    lcd.print("Volume:");
    lcd.setCursor(11,0);  
    lcd.print(Vnb);
 
    
    buttonState2 = digitalRead(pushButton2);                      
  
    int buttonState3 = digitalRead(pushButton3);                 //le boutons 3 permet de monter le volume
      
    if (buttonState3 == 1 and Vnb<30){
      delay(300);
      Vnb=Vnb+1;
      Serial.println(Vnb);
      }
    int buttonState1 = digitalRead(pushButton1);
        
    if (buttonState1 == 1 and Vnb>10){                               // le bouton 3 permet de baisser le volume
      delay(300);
      Vnb=Vnb-1;
      Serial.println(Vnb);
      }
      
        }
  buttonState2 = 0;                                   // en rappuyant sur le bouton 2 on sort de la fonction et renvoie la valeur final
  delay(500);
  Serial.println(F("sortie")); 
  lcd.clear();
  myDFPlayer.volume(Vnb);
         
    }
  

  
  
void kitnumb(){                                         // Fonction retournant le numéro du kit choisi par l'utilisateur
  
  int buttonState1 = digitalRead(pushButton1);
  
  if (buttonState1 == 1){                              //  quand le boutons 1 est pressé la numéro du kit passe au suivant ( de 1 à 3 )
    
    if (kit == 1){
      kit = 2;
      Serial.println(F("kit2"));
      
      while(buttonState1 == 1){
        
        buttonState1 = digitalRead(pushButton1);
    }
    
    }
    
     
    else if (kit == 2){
      kit = 3;
      Serial.println(F("kit3"));
      while(buttonState1 == 1){
        buttonState1 = digitalRead(pushButton1);
        }
      
      }

    else if (kit== 3){
      kit = 1;
      Serial.println(F("kiit1"));
      while(buttonState1 == 1){
        buttonState1 = digitalRead(pushButton1);
    }
    }
    }
    }
    

      


void Modelibre(){                                               // La fonction Mode libre est 1 des mode de jeu, ou l'on joue librement 
  
  n = 0;
  
  lcd.setCursor(0,0);
  lcd.print("   Mode Libre");
  lcd.setCursor(0,1);  
  lcd.print("kit");
  lcd.setCursor(3,1);  
  lcd.print(kit);
  lcd.setCursor(5,1);
  lcd.print(" Vol");
  lcd.setCursor(12,1);
  lcd.print("Rifs");
  
  fsrReading1 = analogRead(fsrAnalogPin1);
  fsrReading2 = analogRead(fsrAnalogPin2);
  fsrReading3 = analogRead(fsrAnalogPin3);
  fsrReading4 = analogRead(fsrAnalogPin4);
  fsrReading5 = analogRead(fsrAnalogPin5);
  fsrReading6 = analogRead(fsrAnalogPin6);
  

  kitnumb();                                          // La fonction est appelé pour le choix de kit et son utilisation dans le code       
  
 
  if (fsrReading1>200){                                  // à chaque capteur  on attribue une LED et un son provenant d"un kit
    myDFPlayer.playFolder(kit,1);                         // Lorsque le capteur s'active la Led s'alume et le Modul DFPlayer envoie le son à l'enceinte
    digitalWrite(Led1, HIGH);
    Serial.println(F("1joué"));
    while (fsrReading1>200){
      fsrReading1 = analogRead(fsrAnalogPin1); 
    }
    digitalWrite(Led1, LOW);
    }
    
  else if (fsrReading2>200){
    
    myDFPlayer.playFolder(kit,2);
    digitalWrite(Led2, HIGH);
    Serial.println(F("2joué"));
    while (fsrReading2>200){
      fsrReading2 = analogRead(fsrAnalogPin2); 
    }
    digitalWrite(Led2, LOW);
    }
  
  else if (fsrReading3>200){
    myDFPlayer.playFolder(kit,3);
    digitalWrite(Led3, HIGH);
    Serial.println(F("3joué"));
    while (fsrReading3>200){
      fsrReading3 = analogRead(fsrAnalogPin3); 
    }
    digitalWrite(Led3, LOW);
  }
  else if (fsrReading4>200){
    myDFPlayer.playFolder(kit,4);
    digitalWrite(Led4, HIGH);
    Serial.println(F("4joué"));
    while (fsrReading4>200){
      fsrReading4 = analogRead(fsrAnalogPin4); 
    }
    digitalWrite(Led4, LOW);
    }
    
  else if (fsrReading5>200){
    myDFPlayer.playFolder(kit,5);
    digitalWrite(Led5, HIGH);
    delay(300);
    Serial.println(F("5joué"));
    while (fsrReading5>200){
      fsrReading5 = analogRead(fsrAnalogPin5); 
    }
    digitalWrite(Led5, LOW);
  }
  
  else if (fsrReading6>200){
    myDFPlayer.playFolder(kit,6);
    digitalWrite(Led6, HIGH);
    
    Serial.println(F("6joué"));
    while (fsrReading6>200){
      fsrReading6 = analogRead(fsrAnalogPin6); 
    }
    digitalWrite(Led6, LOW);
  }
  
  
}

void rifnumb1(){                                          // // Fonction retournant le numéro du kit choisi par l'utilisateur
  
  int buttonState3 = digitalRead(pushButton3);
  
  if (buttonState3 == 1){                               //  quand le boutons 1 est pressé la numéro du rif passe au suivant ( de 1 à 2 )
    
         
    if (rif == 2){
      rif = 1;
      Serial.println(F("rit1"));
      while(buttonState3 == 1){
        buttonState3 = digitalRead(pushButton3);
        }
      
      }
    else if (rif == 1){
      rif = 2;
      Serial.println(F("rit2"));
      
      while(buttonState3 == 1){
        
        buttonState3 = digitalRead(pushButton3);
    }
    
    }

   
    }
    }


    



void Rif1 (){                                                      // La Fonction du jeu RIF correspondnt au 1er RIF disponible          
  fsrReading1 = analogRead(fsrAnalogPin1);                                
  fsrReading2 = analogRead(fsrAnalogPin2);
  fsrReading3 = analogRead(fsrAnalogPin3);
  fsrReading4 = analogRead(fsrAnalogPin4);
  fsrReading5 = analogRead(fsrAnalogPin5);
  fsrReading6 = analogRead(fsrAnalogPin6);
  float x=0.95;
  
  int n=0;
  
  if (fsrReading1>200 or fsrReading2>200 or fsrReading3>200 or fsrReading4>200 or fsrReading5>200 or fsrReading6>200){
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500); 

    while (n != 2 ){
      
      myDFPlayer.playFolder(2,1); 
      digitalWrite(Led1, HIGH);
      delay(x*500);
      
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2); 
      delay(x*500);

      digitalWrite(Led2, LOW);
      digitalWrite(Led3, HIGH);
      myDFPlayer.playFolder(2,3);
      delay(x*500);

      digitalWrite(Led3, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2);
      delay(x*210);

      digitalWrite(Led2, LOW);
      digitalWrite(Led4, HIGH);
      myDFPlayer.playFolder(2,4);
      delay(x*500);
      
      digitalWrite(Led4, LOW);
      digitalWrite(Led4, HIGH);
      myDFPlayer.playFolder(2,4);
      delay(x*460);

      digitalWrite(Led4, LOW);
      digitalWrite(Led1, HIGH);
      myDFPlayer.playFolder(2,1);
      delay(x*210);

      digitalWrite(Led1, LOW);
      digitalWrite(Led3, HIGH);
      myDFPlayer.playFolder(2,3);
      delay(x*500);

      digitalWrite(Led3, LOW);
      digitalWrite(Led6, HIGH);
      myDFPlayer.playFolder(2,6);
      delay(x*210);

      digitalWrite(Led6, LOW);
      digitalWrite(Led5, HIGH);
      myDFPlayer.playFolder(2,5);
      delay(x*250)   ;
      digitalWrite(Led5,LOW);
      n=n+1;
    } 
    
   int buttonState2 = digitalRead(pushButton2);

   
   while (  buttonState2 ==0){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RIF1:You're Turn");
    lcd.setCursor(6,1);
    lcd.print("QUIT");

// SON 1
    digitalWrite(Led1, HIGH);
    
    //buttonState2 = digitalRead(pushButton2);
     
    buttonState2 = 0;
    
    if (buttonState2 == 0){
    fsrReading1 = analogRead(fsrAnalogPin1);
    
    while (fsrReading1<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading1 = analogRead(fsrAnalogPin1); 
       } 
       
    
    Serial.println(F("sortie"));
    
    digitalWrite(Led1, LOW);
    
    
    if (buttonState2 == 0){  
    myDFPlayer.playFolder(2,1);
    
    Serial.println(F("son 1"));
    }
    }
// SON 2  
    if (buttonState2 == 0){  
    digitalWrite(Led2, HIGH);
    
    fsrReading2 = analogRead(fsrAnalogPin2);
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); }
       
    digitalWrite(Led2, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,2);

    Serial.println(F("son 2"));
    }
    }
// SON 3
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);
    
    fsrReading3 = analogRead(fsrAnalogPin3);
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3); }
       
    digitalWrite(Led3, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,3);

    Serial.println(F("son 3"));
   }
    }
 // SON 2
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);

    fsrReading2 = analogRead(fsrAnalogPin2);
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2);}
       
    digitalWrite(Led2, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,2);

    Serial.println(F("son 2"));
    }
    }
 // SON 4 
    if (buttonState2 == 0){
    digitalWrite(Led4, HIGH);

    fsrReading4 = analogRead(fsrAnalogPin4);
    
    while (fsrReading4<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading4 = analogRead(fsrAnalogPin4);}

    
    fsrReading4 = analogRead(fsrAnalogPin4);
    
    digitalWrite(Led4, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,4);
    
    while(fsrReading4>200){fsrReading4 = analogRead(fsrAnalogPin4);}

    Serial.println(F("son 4"));
    }
    }
// Son 4
    if (buttonState2 == 0){
    digitalWrite(Led4, HIGH);

    fsrReading4 = 0;
   
    while (fsrReading4<200 and buttonState2 ==0){
       
      buttonState2 = digitalRead(pushButton2); 
      fsrReading4 = analogRead(fsrAnalogPin4);}
      Serial.println(F("dans la boucle"));
       
    digitalWrite(Led4, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,4);

    Serial.println(F("son 4"));
    }
    }
 // SON 1   
    if (buttonState2 == 0){
    digitalWrite(Led1, HIGH);

    fsrReading1 = analogRead(fsrAnalogPin1);
    
    while (fsrReading1<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading1 = analogRead(fsrAnalogPin1); 
       }
       
    digitalWrite(Led1, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,1);
    
    Serial.println(F("son 1"));
    }
    }
 // SON 3
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);

    fsrReading3 = analogRead(fsrAnalogPin3); 
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3); 
       }
    digitalWrite(Led3, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,3);

    Serial.println(F("son 3"));
    }
    }
 // SON 6
    if (buttonState2 == 0){
    digitalWrite(Led6, HIGH);

    fsrReading6 = analogRead(fsrAnalogPin6);
    
    while (fsrReading6<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading6 = analogRead(fsrAnalogPin6); }
       
    digitalWrite(Led6, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,6);

    Serial.println(F("son 6"));
    }
    }
 // SON 5
    if (buttonState2 == 0){
    digitalWrite(Led5, HIGH);
    
    fsrReading5 = analogRead(fsrAnalogPin5);
    
    while (fsrReading5<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading5 = analogRead(fsrAnalogPin5);}
       
    digitalWrite(Led5, LOW);
    if (buttonState2 == 0){
    Serial.println(F("son 5"));
    
    myDFPlayer.playFolder(2,5);
    }
    
   }
  
  Serial.println(F("sortie2"));
  }
delay(1000);
Serial.println(F("delay"));
lcd.clear();
}

}   
    
    
void Rif2 (){
  
  fsrReading1 = analogRead(fsrAnalogPin1);
  fsrReading2 = analogRead(fsrAnalogPin2);
  fsrReading3 = analogRead(fsrAnalogPin3);
  fsrReading4 = analogRead(fsrAnalogPin4);
  fsrReading5 = analogRead(fsrAnalogPin5);
  fsrReading6 = analogRead(fsrAnalogPin6);
  float x=1.1;
  
  int n=0;
  
  if (fsrReading1>200 or fsrReading2>200 or fsrReading3>200 or fsrReading4>200 or fsrReading5>200 or fsrReading6>200){
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500);
    myDFPlayer.playFolder(4,2);
    delay(x*500); 
    

    while (n != 2 ){
      
      myDFPlayer.playFolder(2,1); 
      digitalWrite(Led1, HIGH);
      delay(x*370);
      
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2); 
      delay(x*120);

      digitalWrite(Led2, LOW);
      digitalWrite(Led4, HIGH);
      myDFPlayer.playFolder(2,4);
      delay(x*495);

      digitalWrite(Led4, LOW);
      digitalWrite(Led3, HIGH);
      myDFPlayer.playFolder(2,3);
      delay(x*370);

      digitalWrite(Led3, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2);
      delay(x*120);
      
      digitalWrite(Led2, LOW);
      digitalWrite(Led4, HIGH);
      myDFPlayer.playFolder(2,4);
      delay(x*370);

      digitalWrite(Led4, LOW);
      digitalWrite(Led6, HIGH);
      myDFPlayer.playFolder(2,6);
      delay(x*120);

      digitalWrite(Led6, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2);
      delay(x*370);

      digitalWrite(Led2, LOW);
      digitalWrite(Led6, HIGH);
      myDFPlayer.playFolder(2,1);
      delay(x*120);

      digitalWrite(Led6, LOW);
      digitalWrite(Led1, HIGH);
      myDFPlayer.playFolder(2,6);
      delay(x*495)   ;

      digitalWrite(Led1, LOW);
      digitalWrite(Led3, HIGH);
      myDFPlayer.playFolder(2,3);
      delay(x*370);

      digitalWrite(Led3, LOW);
      digitalWrite(Led2, HIGH);
      myDFPlayer.playFolder(2,2);
      delay(x*150);

      myDFPlayer.playFolder(2,2);
      delay(x*150);

      digitalWrite(Led2, LOW);
      digitalWrite(Led3, HIGH);
      myDFPlayer.playFolder(2,3);
      delay(x*150);

      myDFPlayer.playFolder(2,3);
      delay(x*150);
      digitalWrite(Led3,LOW);
      n=n+1;
    }

    int buttonState2 = digitalRead(pushButton2);
    
    while (  buttonState2 ==0){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RIF2:You're Turn");
    lcd.setCursor(6,1);
    lcd.print("QUIT");

// SON 1     1
    if (buttonState2 == 0){
    digitalWrite(Led1, HIGH);
    
    buttonState2 = digitalRead(pushButton2); 
    
    fsrReading1 = analogRead(fsrAnalogPin1);
    
    while (fsrReading1<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading1 = analogRead(fsrAnalogPin1); } 
       
    buttonState2 = digitalRead(pushButton2);
       
    digitalWrite(Led1, LOW);
    if (buttonState2 == 0){
    myDFPlayer.playFolder(2,1);
    
    Serial.println(F("son 1"));
    }
    
// SON 2      2 
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);
    
    fsrReading2 = analogRead(fsrAnalogPin2);
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); }
       
    buttonState2 = digitalRead(pushButton2);  
     
    digitalWrite(Led2, LOW);
    
    myDFPlayer.playFolder(2,2);

    Serial.println(F("son 2"));
    }
// SON 4   3
    if (buttonState2 == 0){
    digitalWrite(Led4, HIGH);
    
    fsrReading4 = analogRead(fsrAnalogPin4);
    
    while (fsrReading4<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading4 = analogRead(fsrAnalogPin4); }

    buttonState2 = digitalRead(pushButton2);
       
    digitalWrite(Led4, LOW);
    
    myDFPlayer.playFolder(2,4);

    Serial.println(F("son 4"));
    }
    
 // SON 3   4
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);

    fsrReading3 = analogRead(fsrAnalogPin3);
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3);}

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led3, LOW);
    
    myDFPlayer.playFolder(2,3);

    Serial.println(F("son 3"));
    }
// SON 2    5
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);
    
    fsrReading2 = analogRead(fsrAnalogPin2);
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led2, LOW);
    
    myDFPlayer.playFolder(2,2);

    Serial.println(F("son 2"));
    }
// SON 4   6
    if (buttonState2 == 0){
    digitalWrite(Led4, HIGH);
    
    fsrReading4 = analogRead(fsrAnalogPin4);
    
    while (fsrReading4<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading4 = analogRead(fsrAnalogPin4); }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led4, LOW);
    
    myDFPlayer.playFolder(2,4);

    Serial.println(F("son 4"));
    }
 // SON 6   7
    if (buttonState2 == 0){
    digitalWrite(Led6, HIGH);

    fsrReading6 = analogRead(fsrAnalogPin6);
    
    while (fsrReading6<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading6 = analogRead(fsrAnalogPin6); 
       }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led6, LOW);
    
    myDFPlayer.playFolder(2,6);
    
    Serial.println(F("son 6"));
    }
 // SON 2    8
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);

    fsrReading2 = analogRead(fsrAnalogPin2); 
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); 
       }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led2, LOW);
    
    myDFPlayer.playFolder(2,2);

    Serial.println(F("son 2"));
    }
 // SON 1   9
    if (buttonState2 == 0){
    digitalWrite(Led1, HIGH);

    fsrReading1 = analogRead(fsrAnalogPin1);
    
    while (fsrReading1<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading1 = analogRead(fsrAnalogPin1); }

    buttonState2 = digitalRead(pushButton2);
       
    digitalWrite(Led1, LOW);
    
    myDFPlayer.playFolder(2,1);

    Serial.println(F("son 1"));
    }
 // SON 6   10
    if (buttonState2 == 0){
    digitalWrite(Led6, HIGH);

    fsrReading6 = analogRead(fsrAnalogPin6);
    
    while (fsrReading6<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading6 = analogRead(fsrAnalogPin6); 
       }

    buttonState2 = digitalRead(pushButton2);
       
    digitalWrite(Led6, LOW);
    
    myDFPlayer.playFolder(2,6);
    
    Serial.println(F("son 6"));
    }
 // SON 3   11
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);

    fsrReading3 = analogRead(fsrAnalogPin3);
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3); 
       }
       
    buttonState2 = digitalRead(pushButton2);
       
    digitalWrite(Led3, LOW);
    
    myDFPlayer.playFolder(2,3);
    
    Serial.println(F("son 3"));
    }
 // SON 2   12
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);

    fsrReading2 = analogRead(fsrAnalogPin2);
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); 
       }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led2, LOW);
    
    myDFPlayer.playFolder(2,2);

    fsrReading2 =500;

    while(fsrReading2>200){
      fsrReading2 = analogRead(fsrAnalogPin2);
      Serial.println(F("boucle vide son2"));}
    
    Serial.println(F("son 2"));
    }
 // SON 2   13
    if (buttonState2 == 0){
    digitalWrite(Led2, HIGH);

    fsrReading2 =0;
    
    while (fsrReading2<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading2 = analogRead(fsrAnalogPin2); 
       }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led2, LOW);
    
    myDFPlayer.playFolder(2,2);
    
    Serial.println(F("son 2"));
    }

 // SON 3   14
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);

    fsrReading3 = analogRead(fsrAnalogPin3);
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3); 
       }

    buttonState2 = digitalRead(pushButton2);
    
    digitalWrite(Led3, LOW);
    
    myDFPlayer.playFolder(2,3);
    
    fsrReading3 =500;
    
    while(fsrReading3>200){
      fsrReading3 = analogRead(fsrAnalogPin3);
      Serial.println(F("boucle vide son 3"));}

    buttonState2 = digitalRead(pushButton2);
    
    Serial.println(F("son 3"));
    }
 // SON 3   15
    if (buttonState2 == 0){
    digitalWrite(Led3, HIGH);

    fsrReading3 = 0;
    
    while (fsrReading3<200 and buttonState2 ==0){
       buttonState2 = digitalRead(pushButton2); 
       fsrReading3 = analogRead(fsrAnalogPin3); 
       }

   
    
    digitalWrite(Led3, LOW);
    
    myDFPlayer.playFolder(2,3);
    
    Serial.println(F("son 3"));
    
    }
   } 
delay(1000);
lcd.clear();} 
}

}

void Moderif(){
 
  n= 1  ;

  lcd.setCursor(3,0);
  lcd.print("Mode Rifs");
  lcd.setCursor(0,1);
  lcd.print("Libre  Vol  Rif");
  lcd.setCursor(15,1);
  lcd.print(rif);
  
  rifnumb1();
  
  if (rif == 1){
    Rif1();
  }
  else if (rif == 2){
    Rif2();
  }
  }


void setup() {
  
  mySoftwareSerial.begin(9600);                                     //CONNECTION MP3
  Serial.println();
  Serial.println(F("INITIALISATION DU MODULE MP3"));

  Serial.begin(9600); 

  myDFPlayer.begin(mySoftwareSerial); 
  Serial.println(F("MODULE MP3 CONNECTE"));
  myDFPlayer.volume(Vnb);  
  
  lcd.begin(16, 2);
  
  lcd.print("      TAPX");
  
  myDFPlayer.playFolder(4,1);
  
  delay(200);
  
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led5, OUTPUT);
  pinMode(Led6, OUTPUT);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);
  

  digitalWrite(Led1, HIGH);
  delay(200);
  digitalWrite(Led2, HIGH);
  delay(200);
  digitalWrite(Led3, HIGH);
  delay(200);
  digitalWrite(Led4, HIGH);
  delay(200);
  digitalWrite(Led5, HIGH);
  delay(200);
  digitalWrite(Led6, HIGH);
  delay(200);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);
  
}

void loop() {
  
  int buttonState1 = digitalRead(pushButton1);
  int buttonState2 = digitalRead(pushButton2);
  int buttonState3 = digitalRead(pushButton3);

  if (buttonState2 == 1){
    delay(500);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Volume:");
    lcd.setCursor(11,0);  
    lcd.print(Vnb);
    lcd.setCursor(0,1);
    lcd.print("< -   QUIT   + >");
    Volume();
    
    }
    
    
  else if (buttonState3 == 1 and n == 0){
    
    lcd.clear();
    delay(500);
    Moderif();
    while(buttonState3 == 1){
      buttonState3 = digitalRead(pushButton3);  
    }
  }
  if (n == 0){
    Modelibre();
  }
  if (buttonState1 == 1 and n == 1){
    lcd.clear();
    delay(500);
    Modelibre();
    while(buttonState1 == 1){
      buttonState1 = digitalRead(pushButton1); 
    }
  }
  if (n == 1){ 
    Moderif();  
  }
  }

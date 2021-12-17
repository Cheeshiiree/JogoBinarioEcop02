#include "adc.h"
#include "bits.h"//
#include "config.h"  //
#include "ds1307.h"
#include "io.h"
#include "keypad.h"//
#include "lcd.h"//
#include "pwm.h"//
#include "serial.h"
#include "ssd.h"//
#include "timer.h"//
#include "so.h"
#include "rgb.h"
#include "atraso.h"

#include <pic18f4520.h>

int aux[8]={0,0,0,0,0,0,0,0};
int Acertos=3000;

void AperteStart();
void Acertou();
void Limpar();
int Q=0,Vidas=3; 


void main(void) {
    
    TRISA=0;
    TRISD=0;
    TRISE=0;
      
   
 int numb[14]={14, 5, 7, 49, 25, 76, 52, 98, 2, 70, 64, 45, 89, 8};
    

    lcdInit();
    int i, tecla;
    
    rgbInit();
    pwmInit();
    ssdInit();
    kpInit();
    adcInit();
    dsInit();
    dsStartClock();
    serialInit();
    pwmInit();
    timerInit();
    i = 0;
    int seg = 0;
    char t;

    
   
    


    char slot =1;
    for (;;) {
        
      
        timerReset(20000);
        i++;
        switch(slot){
            case 1:
                
                lcdPosition(0, 0);
                lcdString("Seu numero e  "); 

                
                lcdPosition(1, 0);
                lcdNumber(numb[Q]);
                
                lcdPosition(1, 7);
                lcdChar(aux[7]+48);

                lcdPosition(1, 8);
                lcdChar(aux[6]+48);

                lcdPosition(1, 9);
                lcdChar(aux[5]+48);

                lcdPosition(1, 10);
                lcdChar(aux[4]+48);

                lcdPosition(1, 12);
                lcdChar(aux[3]+48);

                lcdPosition(1, 13);
                lcdChar(aux[2]+48);

                lcdPosition(1, 14);
                lcdChar(aux[1]+48);

                lcdPosition(1, 15);
                lcdChar(aux[0]+48);
                slot = 2;
                
                 switch(Vidas){
                        case 3:
                            PORTD=0b00111000;
                        break;
                        
                         case 2:
                            PORTD=0b00011000;
                        break;
                
                        case 1:
                            PORTD=0b00001000;
                        break;}
                
              
                break;
            case 0:
                kpDebounce();
                
            
                if (kpRead() != tecla) {
                     tecla = kpRead(); 
                
                    if (bitTst(tecla, 0)){ 
                        aux[7]=!aux[7];
                       
                    }    

                    if (bitTst(tecla, 3)){ 
                        aux[6]=!aux[6];

                    }

                    if (bitTst(tecla, 2)){ 
                        aux[5]=!aux[5];
                    }

                    if (bitTst(tecla, 1)){ 
                        aux[4]=!aux[4];
                     
                    }

                    if (bitTst(tecla, 5)){ 
                        aux[3]=!aux[3];
                    
                    }

                    if (bitTst(tecla, 6)){ 
                        aux[2]=!aux[2];
                     
                    }

                    if (bitTst(tecla, 7)){ 
                        aux[1]=!aux[1];
                 
                    }

                    if (bitTst(tecla, 8)){ 
                        aux[0]=!aux[0];
                    }

                     if (bitTst(tecla, 9)){ 

                  
                       confir(aux,numb[Q]);
                       Q++;
                        

                      
                    }
                     
                     
                slot = 1;
                }      
                else
                    slot = 2;
                
                
                break;
            case 2:
               
                ssdDigit(((Acertos/1)%10),3);
                ssdDigit(((Acertos/10)%10),2);
                ssdDigit(((Acertos/100)%10),1);
                ssdDigit(((Acertos/1000)%10),0);
                
                slot =0 ;
                break;
            default :
                slot = 0;
                break;
        }
        
        ssdUpdate();
        timerWait();  
        
    }
}

  int confir(int aux[],int num){

    int auxB=0;
    
    Limpar();
    lcdPosition(0, 0);
    lcdString("Teste: ");
    
    
   
    
    auxB= aux[0]*1 + aux[1]*2 + aux[2]*4 + aux[3]*8 + aux[4]*16 + aux[5]*32 + aux[6]*64 + aux[7]*128;
    
    if(auxB==num){
       
        lcdPosition(0, 9);
        lcdString("Acertou"); 
        Acertos++;
        
        if(((Acertos/10)%10)>0){
        
            lcdPosition(0, 0);
            lcdString("Voce Ganhou!      ");        
            TRISC=255;
            atraso_ms(2000);
            TRISC=0;
            lcdPosition(1, 0);
            lcdString("Jogue Novamente!  ");
                    
            while(1){
            }
            
           

        
        }
        
        AperteStart();
      
        
      
    }

    else{
        
        lcdPosition(0, 9);
        lcdString(" Errou");
        Acertos -=1000;
        Vidas--;
        
        if(((Acertos/1000)%10)<1){
        
            lcdPosition(0, 0);
            lcdString("Voce Perdeu!      ");        
            TRISC=255;
            atraso_ms(2000);
            lcdPosition(1, 0);
            TRISC=0;
            lcdString("Tente de novo!");
            PORTD=0;  
           
            while(1){
            }
            
           

        
        }
        
        AperteStart();
        
        
    
    }
    return 0;
}

void AperteStart(){

    unsigned int T=0;
    
   
    lcdPosition(1, 7);
    lcdString("Press. S");
    
   
    
    while(1){
             
            kpInit();
            kpDebounce(); 
            T = kpRead(); 
           
            if (bitTst(T, 4)){ 
                     
                break;
                }
          
    }
    
        Limpar();
}


void Limpar(){
    
    lcdPosition(1, 0);
    lcdString("                ");
    lcdPosition(0, 0);
    lcdString("                ");


}
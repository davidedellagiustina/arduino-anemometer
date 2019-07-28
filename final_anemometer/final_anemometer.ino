#include <LiquidCrystal.h> // importazione libreria lcd
LiquidCrystal lcd(7,6,5,4,3,2); // settaggio pin lcd

int giri=-1 /* si azzera ogni 5, serve per fre il refresh sul display */,girirefresh=5 /* ogni quanti giri avviene il refresh */,giritot=-1 /* giri compiuti in totale (stampati sul display) */, state=0 /* stato del reed */;
float velocitams=0 /* velocità in m/s */,velocitakmh=0 /* velocità in km/h */,circonferenza=0.83786276071239785669798699032064 /*0.204203522483336560500071819913117 errato!*/ /* circonferenza del cerchio sll'altezza del magnete */;
unsigned long int tini=0 /* tempo iniziale preso al primo giro in assoluto */,tfin=0 /* tempo finale aggiornato ogni "girirefresh" giri */,deltat=0 /* differenza tra "tfin" e "tini" */;

void setup() {
  lcd.begin (16, 2); // dichiarazione dimensione lcd
  pinMode(8,INPUT); // dichiarazione pin 8 come input
}

void stampa() { // funzione di stampa sul display, richiamata alla fine di ogni loop
  lcd.setCursor(5, 0); // posizionamento cursore
  lcd.print(velocitams); // stampa variabile
  lcd.print(" m/s   ");
  lcd.setCursor(5, 1);
  lcd.print(velocitakmh);
  lcd.print(" km/h  ");
}

void loop() {
  if (digitalRead(8)==1 && giri==-1 && state==0) { // questo ciclo viene eseguito solo al primo giro in assoluto per essere sicuri di non contare il "meno di un giro" iniziale
    tini=millis();
    giri++;
    giritot++;
    lcd.setCursor(0, 1);
    lcd.print("0");
    state=1;
  }
  else if (digitalRead(8)==1 && giri>=0 && state==0) { // questo ciclo viene eseguito tutte le altre volte, cioè ad ogni giro effettuato
    giri++;
    giritot++;
    lcd.setCursor(0, 1);
    lcd.print(giritot);
    state=1;
  }
  else if (digitalRead(8)==0) {
    state=0;
  }
  if (giri==girirefresh) { // quando il numero di giri è = a "girirefresh" questo ciclo calcola le velocità in m/s e km/h
    tfin=millis();
    deltat=(tfin-tini)/1000;
    velocitams=(circonferenza*giritot)/deltat;
    velocitakmh=velocitams*3.6;
    giri=0;
  }
  stampa(); // richiamo della funzione di stampa
  //delay(7); // piccolo delay per il debounce
}

/**
 *  Description: jeu de rapiter, objectif appyuer sur un bouton avant que
 *               le minuteur sois espérer.
 * fonction: ISR(minuteur)
 *           description: change la valeur de minuteur expirer a 1 lorsque le temps
 *                        est expirer
 *           ISR(bouton)
 *            description change la valeur de boutton pousoir a 1
 **/
 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #define F_CPU 8000000
 #include <util/delay.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR( TIMER1_COMPA_vect){
    minuterieExpiree = 1;
}

ISR (INT0_vect) {
    // anti-rebond
    _delay_ms ( 30 );
    if(PIND & ( 1 << PIND2)){
        boutonPoussoir = 1;
    }
}


void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; //definie PORTA comme des sortie
    DDRD = 0x00; //definie PORTD comme des entrée
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) | (1 << INT1);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    //// Permet de faire un interuption lorsque le front est montant
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}


void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    //initialisation du timer a zero
    TCNT1 = 0;

    OCR1A = duree;
    //on le met egal a zero etant donner que nous ne prenons pas
    //valeur provenant des PORT pour l'instant
    TCCR1A = 0;
    //set mode to 1024(divise le clock par 1024)
    // on veut modifier CS12 et CS10
    //Registre a 8 bit
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;
    //set flags interrupt timer 
    //on veut que le timer arrète quand il arrive a sa fin
    //ou lorsque nous somme arrivée a OCR1A donc on veut les deux 
    //OCIE1A Fait une intéruption lorsque OCR1A = TCNT1
    //TOIE1 en cas d'overflow fait une intéruption    
    TIMSK1 = (1 << OCIE1A) | (1 << TOIE1);
}

void debuter(){
    for(uint8_t i = 0; i < 10; i++){
        for(uint8_t j = 0; j < 5; j++){
            PORTA = (1 << PORTA0);
            _delay_ms (100);
            PORTA = 0;
            _delay_ms (100);
        }
    }
}

int main(){
    initialisation();
    //Annule les interuption lorsque la del clignote
    cli();

    debuter();

    //active les interuption lorsque la del fini de clignoter
    sei();
    //Durée équivalent a 1 seconde normalement
    // 7813 puisque fréquence processeur = 8 MHz
    //qui est diviser par 1024
    partirMinuterie(7813);
    do {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
        
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
      
    // Verifier la réponse 
    if(minuterieExpiree == 1)
    {
        PORTA = (1 << PORTA0);
    }  
    else{
        PORTA = (1 << PORTA1);
    }
    
}
#include <avr/io.h>
#include <avr/eeprom.h>
#define F_CPU 8000000

void initialisationUART ( void )
{
    //2400 bauds. nous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;

    UBRR0L = 0xCF;
    // Permettre la réception et la transmision par le UART0
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format des trames : 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// De l'USART vers le PC
void transmissionUART ( uint8_t donnee ) {
    //attendre tant que la donnee est entrée
    while(!(UCSR0A & (1<<UDRE0)));

    UDR0 = donnee;
}

int main()
{
    DDRA = 0xff;
    initialisationUART();
    char mot[47] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t* adresse = 0x00;

    for(uint8_t i = 0; i < 47; i++){
        //transmission de notre mot dans la memoire eeprom
        eeprom_write_byte(adresse, mot[i]);
        //nous ecrivons un byte qui prend 8 bit ce qui explique 
        //que nous changons de 8 l'adresse.
        adresse = adresse + 0x08;
    }
    //Placons 0xFF a la derniere adresse pour détreminer la fin 
    //des donnee inscrit dans la memoire
    eeprom_write_byte(adresse, 0xFF);

    //leture de memoire et transmission UART
    adresse = 0x00;
    while(eeprom_read_byte(adresse) != 0xFF){
        //nous ecrivons un byte qui prend 8 bit ce qui explique 
        //que nous changons de 8 l'adresse.
        transmissionUART(eeprom_read_byte(adresse));
        adresse = adresse + 0x08;
    }

    //verification que le programme a termine et ne reste pas prit
    //dans la boucle antérieur
    PORTA = (1 << PORTA0);

}
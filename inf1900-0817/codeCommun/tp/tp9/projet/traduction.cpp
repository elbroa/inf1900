#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "PWM.h"
#include "Debug.h"
#include "UART.h"

// DEFINITION DES INSTRUCTIONS
const uint8_t DBT = 0x01;
const uint8_t ATT = 0x02;
const uint8_t DAL = 0x44;
const uint8_t DET = 0x45;
const uint8_t MON = 0x18;
const uint8_t MOF = 0x19;
const uint8_t MAR1 = 0x60;
const uint8_t MAR2 = 0x61;
const uint8_t MAV = 0x62;
const uint8_t MRE = 0x63;
const uint8_t TRD = 0x64;
const uint8_t TRG = 0x65;
const uint8_t DBC = 0xC0;
const uint8_t FBC = 0xC1;
const uint8_t FIN = 0xFF;

const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 1 << PORTA0;
const uint8_t VERT = 1 << PORTA1;

const uint8_t NORD = (1 << PORTB5) | (1 << PORTB0) | (1 << PORTB2);
const uint8_t SUD = (1 << PORTB3) | (1 << PORTB2) | (1 << PORTB0);
const uint8_t EST = (1 << PORTB4) | (1 << PORTB2) | (1 << PORTB1);
const uint8_t OUEST = (1 << PORTB4) | (1 << PORTB0) | (1 << PORTB1);

uint8_t appelerOperande(uint8_t *adresse)
{
	adresse++;
	return eeprom_read_byte(adresse);
}

void lireInstruction(uint8_t *adresse)
{
    uint8_t instruction = eeprom_read_byte(adresse);
    uint8_t vitesse;

    switch (instruction)
    {
        case ATT:
        {
            DEBUG_PRINT(("Instruction: ATT \n"));
            for (uint8_t i = 0; i < appelerOperande(adresse); i++)
            {
                _delay_ms(25);
            }
            break;
        
        }

        case DAL:
        {
            DEBUG_PRINT(("Instruction: DAL \n"));
            if (appelerOperande(adresse) >= 0 && appelerOperande(adresse) <= 127)
            {
                PORTA = VERT;
            }
            
            PORTA = ROUGE;
            break;
        }

        case DET:
        {
            DEBUG_PRINT(("Instruction: DET \n"));
            PORTA = ETEINT;
            break;
        }

        case MON:
        {
            DEBUG_PRINT(("Instruction: MON \n"));
            PORTC = appelerOperande(adresse);
            break;
        }

        case MOF:
        {
            DEBUG_PRINT(("Instruction: MOF \n"));
            PORTC = ETEINT;
            break;
        }

        case MAR1:
        {
            DEBUG_PRINT(("Instruction: MAR \n"));
            ajustementPWM(0, 0);
            PORTB = ETEINT;
            break;
        }

        case MAR2:
        {
            DEBUG_PRINT(("Instruction: MAR \n"));
            ajustementPWM(0, 0);
            PORTB = ETEINT;
            break;
        }

        case MAV:
        {
            DEBUG_PRINT(("Instruction: MAV \n"));
            vitesse = (appelerOperande(adresse));
            ajustementPWM(vitesse, vitesse);
            PORTD = (1 << PORTD0);
            PORTB = NORD;
            break;
        }

        case MRE:
        {
            DEBUG_PRINT(("Instruction: MRE \n"));
            vitesse = (appelerOperande(adresse));
            ajustementPWM(vitesse, vitesse);
            PORTD = (0 << PORTD0);
            PORTB = SUD;
            break;
        }

        case TRD:
        {
            DEBUG_PRINT(("Instruction: TRD \n"));
            ajustementPWM(0, 254);
            PORTD = (1 << PORTD0);
            PORTB = EST;
            break;
        }

        case TRG:
        {
            DEBUG_PRINT(("Instruction: TRG \n"));
            ajustementPWM(254, 0);
            PORTD = (1 << PORTD0);
            PORTB = OUEST;
            break;
        }

        case FIN:
        {
            DEBUG_PRINT(("Instruction: FIN \n"));
            PORTA = ETEINT;
			PORTB = ETEINT;
			PORTC = ETEINT;
			PORTD = ETEINT;
            break;
        }
    }
}

int main()
{
    // INITIALISATION DES VARIABLES
    uint8_t operandeMain;
    uint8_t *adresse = 0x00;
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // VÉRIFIE L'ENTRÉE DANS LE MAIN
    initialisationUART();
    transmissionUART('a');

    // RÉCEPTION DU RS232 & ÉCRITURE DANS EEPROM
	uint8_t donnee = 0;
	do
	{   donnee = receptionUART();
		eeprom_write_byte(adresse, donnee);
		adresse++;
	}   while (donnee != FIN);
    
 
    // RÉINITIALISER ADRESSE
	adresse = 0x00;

    // LECTURE DE EEPROM
	while (eeprom_read_byte(adresse) != DBT){
        adresse++;
    }

    // DEBUT DE LA TRADUCTION
	while (eeprom_read_byte(adresse) != FIN) 
	{
        // SI ON SE TROUVE AU DEBUT D'UNE BOUCLE
        if (eeprom_read_byte(adresse) == DBC)
        {
            DEBUG_PRINT(("Instruction: DBC"));
            DEBUG_PRINT(('\n'));
            // INITIALISATION DE LA BOUCLE
            operandeMain = appelerOperande(adresse);
			adresse += 0x02;
			uint8_t compteur = 0;
            // DEBUT DE LA BOUCLE
			do
			{
                // SI ON SE TROUVE A LA FIN DE LA BOUCLE
                if (eeprom_read_byte(adresse) == FBC)
                {
                    DEBUG_PRINT(("Instruction: FBC"));
                    DEBUG_PRINT(('\n'));
                    // ON REMONTE A L'ADRESSE DU DEBUT
                    do{
						adresse--;
					}
					while (eeprom_read_byte(adresse) != DBC);
					adresse += 0x02;
                    compteur++;
					}

				lireInstruction(adresse);
				adresse += 0x02;

			} while (compteur != (operandeMain + 1));
		}
        lireInstruction(adresse);
		adresse += 0x02;
	}
    lireInstruction(adresse);
}
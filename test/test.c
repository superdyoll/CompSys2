#include <avr/io.h>
#include <util/delay.h>

int main()
{
  /* Turn off default prescaling of clock (AT90USB DS, p. 48) */
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;
  DDRB=_BV(PB7); //sets the data direction register of Port B to output on PB7
  while(1)
  {
    PORTB=_BV(PB7); //Outputs 1 on PB7
    _delay_ms(200);
    PORTB=0; //Stops output on port B
    _delay_ms(200);
  }
}

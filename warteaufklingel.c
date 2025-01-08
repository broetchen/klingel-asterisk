#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


#define	BUTTON_PIN	0

static volatile short int i = 0 ;
volatile short int e = 0 ;
volatile short int k = 0 ;


void myInterrupt (void)
{
	i=1 ;
}

int main (void)
{
	int myCounter = 0 ;
	 if (wiringPiSetup () < 0) {
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

	pullUpDnControl (BUTTON_PIN, PUD_OFF) ;

if (wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &myInterrupt) < 0) {
	fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
	return 1 ;
}

while(k==0){
	while(i==0) {
		delay (10);
	}

	for (e=0; (e<10 && i==1); e++) {
		delay (10);
		k=digitalRead(BUTTON_PIN);
		if (k==0)
			i=0;
	}

}

return 0 ;
}

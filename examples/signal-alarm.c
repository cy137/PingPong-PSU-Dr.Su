#include <stdio.h>
#include <signal.h>

void MyAlarm();

main() {

  /* Catch ALARM signal.  If not caught, process terminates. */
  signal(SIGALRM, MyAlarm);
  alarm(3);

  while (1) {

    pause();			/* hangout until signal happens */

    printf("We got a signal!\n");

  }

}

void MyAlarm()
{
   printf("Alarm went off!\n");

   alarm(5);
}

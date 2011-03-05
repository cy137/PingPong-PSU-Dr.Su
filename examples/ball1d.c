/* ball1d.c
 *	purpose	animation with user controlled speed and direction
 *	note the handler does the animation
 *		the main program reads keyboard input
 *	gcc ball1d.c  -lcurses -o ball1d
 */
#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>
#include	<string.h>

/* some global settings main and the handler use */

#define	MESSAGE	"hello"
#define BLANK   "     "

int	row;	/* current row		*/
int	col;	/* current column	*/
int	dir;	/* where we are going	*/

int main()
{
	int	delay;		/* bigger => slower	*/
	int	ndelay;		/* new delay		*/
	int	c;		/* user input		*/
	void	move_msg(int);	/* handler for timer	*/

	initscr();
	cbreak();
	noecho();
	clear();

	row   = 10;		/* start here		*/
	col   = 0;
	dir   = 1;		/* add 1 to row number	*/
	delay = 10000;		/* 200ms = 0.2 seconds  */

	move(row,col);		/* get into position	*/
	addstr(MESSAGE);	/* draw message		*/
	curs_set(0);
	signal(SIGALRM, move_msg );
    ualarm(delay, delay);  /* send signal SIGALRM */

	while(1)
	{
		ndelay = 0;
		c = getch();
		if ( c == 'Q' ) break;
		if ( c == ' ' ) dir = -dir;
		if ( c == 'f' && delay > 2 ) ndelay = delay/2;  /* speed up */
		if ( c == 's' ) ndelay = delay * 2 ;    /* slow down */
		if ( ndelay > 0 ){
		    delay = ndelay;
			ualarm(ndelay,ndelay);
			}
	}
	endwin();
	return 0;
}

void move_msg(int signum)
{
	move( row, col );
	addstr( BLANK );
	col += dir;			/* move to new column	*/
	move( row, col );		/* then set cursor	*/
	addstr( MESSAGE );		/* redo message		*/
	refresh();			/* and show it		*/

	/*
	 * now handle borders
	 */
	if ( dir == -1 && col <= 0 )
		dir = 1;
	else if ( dir == 1 && (col+strlen(MESSAGE)) >= COLS )
		dir = -1;
}

/* 
 * framepaddle.c 
 * hows how to draw the frame and paddle, how to get the size of the window, etc..
 */

#include	<curses.h>
#include	<signal.h>
#include	<string.h>

#define	BLANK		' '
#define	DFL_SYMBOL	'O'
#define	TOP_ROW		2

#define	LEFT_EDGE	1
#define	X_INIT		10		/* starting col		*/
#define	Y_INIT		10		/* starting row		*/

/** the ping pong ball **/

struct ppball {
		int	y_pos, x_pos,
			y_dir, x_dir;
		char	symbol ;

	} ;


struct ppball the_ball ;

int winrows, wincols;
int padsize = 3;
int padposL =1,  padposR = 11;
int score =0;


/**  the main loop  **/

void set_up();

void drawpadels();

void ball_move(int );

int main()
{
	int	c;

	set_up();
	
	ball_move(0);
	
	while ( ( c = getchar()) != 'Q' );   /* type Q to quit */

	endwin();		/* put back to normal	*/
}

void drawpadels()
 {
 int c;
  for(c=25; c--; ) {
    if(c < 2 || c >= 24)
      continue;
    if(c >= 11 && c <= 14)
        mvaddch(c, 0, ' ' | A_REVERSE); /* draw the paddle */
    else 
        mvaddch(c, 0, ' ');
    }
}


void set_up()
/*
 *	init structure and other stuff
 */
{

	the_ball.y_pos = Y_INIT;
	the_ball.x_pos = X_INIT;
	the_ball.y_dir = 1  ;
	the_ball.x_dir = 1  ;
	the_ball.symbol = DFL_SYMBOL ;

	initscr();
	noecho();
	cbreak();
      curs_set(0);   /* hide the cursor */
      getmaxyx(stdscr, winrows, wincols); /* get the size of the current window */
	move(1, 0);
	hline(ACS_HLINE, wincols);   /* draw the boundary */
	move( winrows-1, 0);
	hline(ACS_HLINE,  wincols);
	mvaddch( the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
	drawpadels();
	
	/* draw the score board */
	char scl[10];
      sprintf(scl, "Score: %02d", score);
	mvaddstr(0, 12, scl);

	refresh();
	
}


void ball_move(int signum)
{
	int	y_cur, x_cur, moved;

	y_cur = the_ball.y_pos ;		/* old spot		*/
	x_cur = the_ball.x_pos ;
	moved = 0 ;
	
	the_ball.y_pos += the_ball.y_dir ;	/* move	*/
	the_ball.x_pos += the_ball.x_dir ;	/* move	*/
	
	moved = 1;


	curs_set(0);  /* hide the cursor */
	
	if ( moved ){
		mvaddch( y_cur, x_cur, BLANK );
	
		mvaddch( the_ball.y_pos, the_ball.x_pos, the_ball.symbol );

		refresh();
	}

}




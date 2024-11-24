/*
	 _______________
	|		|
	|sdi1400009 Erg4|  
	|		|
	|_______________|  		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ABS(x) ( ((x)<0 ? -(x) : (x)) )

typedef struct {
	int x;
	int y;
} point;

typedef enum {
	BLACK, WHITE
} color;

typedef enum {
	NO_WALL, HORIZONTAL, VERTICAL
} orientation;

typedef struct{
	orientation dir;
} wall;

typedef struct {
	point position;
	color player_color;
	int available_walls;
} player ;

typedef struct {
	player player1;
	player player2;

	int size;
	wall** walls;

} board;


const char space[] = " \t\n"; //where to split each command's words (tokens)


char* protocol_commands[] = {
	"",
	"name",
	"known_command",
	"list_commands",
	"quit",
	"boardsize",
	"clear_board",
	"walls",
	"playmove",
	"playwall",
	"genmove",
	"undo",
	"winner",
	"showboard"
};

void convert(char* coordinates, int *x, int *y, int size)
{	//used for my board's coordinates
	char c1= coordinates[0];
	char c2= coordinates[1];

	*y = (int)c1 - 'a'; *x = size - ( (int)c2 - '0') ;
}
int get_command_id(char* buff) {    
	
	char* buff_ptr = buff;
	char temp[101];
	
	strcpy (temp, buff);
	int i;
	while (*buff_ptr != '\n' )
	{
		if(*buff_ptr == ' ' || *buff_ptr == '\t') // spaces found, ignore
			buff_ptr++;
		else break;
	}

	char *token;
	token = strtok(temp, space);   
	
	for (i=1; i< ( sizeof(protocol_commands) / sizeof(char *) );  i++) //find the command via strcmp
		if (! strcmp(protocol_commands[i], token))		//return its id
			return i;					//(success)
	return 0;							//no command found (failure)
}

void name (){
	printf("\n=Game Quoridor made by Ted (sdi1400009)\n");
	fflush(stdout);
}	

void known_command (char * buff){

	char *token;
	token = strtok(buff, space);   
	
	token = strtok(NULL, space);
	if (token == NULL){
		printf( "? No arguments\n\n");
		fflush(stdout);
		return;
	}

	if (get_command_id(token)) printf ("= True\n\n");
	else printf ("= False\n\n"); 
	
	fflush(stdout);
}

void list_commands(){
	int i;
	printf("=\n");
	for (i=1; i<13;/**/ i++)
		printf("%s\n",protocol_commands[i]);
	printf("\n");
	fflush(stdout);
}

void showboard(board *b){

	int i,j,k;
	printf("=\n  ");
	for (i=0; i<b->size; i++) 
		printf("   %c", i+'A');
	fflush(stdout);


	for (i=0; i<b->size; i++) 
	{
		printf("\n   +");     //new line   		check only for horizontals
		for(j=0; j<b->size; j++) 
		{
			if( i<b->size && i>0 
					&& ( j<b->size-1 && b->walls[i-1][j].dir==HORIZONTAL||(j>0 && b->walls[i-1][j-1].dir==HORIZONTAL) )  )
				printf("===");
			else printf("---");

			if (i>0 &&  i<b->size && j<b->size && b->walls[i-1][j].dir == HORIZONTAL ) printf("=");
			else if (i != 0 && b->walls[i-1][j].dir == VERTICAL) {putchar(0xE2);putchar(0x80);putchar(0x96);}
			else printf("+");
			fflush(stdout);
		}
		
		printf("\n");  //end of horizontal line


		printf("%2d |",b->size - i); 			// new line (reversed j)   check only for verticals 
		for(j=0; j < b->size; j++)                     	// ************: a |:***********
		{						//  **********: W :********** 
			printf(" "); 
			if	 	(b->player1.position.x == i &&  b->player1.position.y == j ) printf("B");
			else if (b->player2.position.x == i &&  b->player2.position.y == j ) printf("W");   //  <<<<<<  paixths
			else printf(" ");
			printf(" ");

			if(  j < b->size -1 
			    && (i < b->size -1  && (b->walls[i][j].dir == VERTICAL)) 
			    || ( i>0 && i< b->size && b->walls[i-1][j].dir == VERTICAL) )  
			{
				putchar(0xE2);putchar(0x80);putchar(0x96);
			}						//   *********:||:********
			else printf("|");				//   ***********:|:************
			
			fflush(stdout);		
		}
		printf(" %d",b->size - i);

		if(i==0)printf("  black walls: %d",b->player1.available_walls);
		if(i==1)printf("  white walls: %d",b->player2.available_walls);
		
		fflush(stdout);

	}

	printf("\n   +");
	for(j=0;j<b->size;++j) printf("---+");
	printf("\n  ");
	for(j=0;j<b->size;++j)printf("   %c", 'A'+j);
	printf("\n");
	fflush(stdout);
}

void walls(char* buff,player* p1, player *p2 ){

	char* token;

	token = strtok(buff, space);
	token = strtok(NULL, space);

	p1->available_walls = p2->available_walls = atoi(token);


	printf("=\n\n");
	fflush(stdout);
}

void clear_board(board* b){

	int i,j;

	for (i=0;  i< b->size-1; i++)
		for(j=0; j< b->size-1; j++)
			b->walls[i][j].dir = NO_WALL;

	b->player1.player_color = BLACK;
	b->player2.player_color = WHITE;

	b->player1.position.x=0 ; b->player1.position.y= b->size /2;
	b->player2.position.x=b->size -1 ; b->player2.position.y=b->size/2 ;

	b->player1.available_walls = b->player2.available_walls = 10;

	printf("=\n\n");
	fflush(stdout);
}

void boardsize(char* buff, board* b){

	char* token;
	int i,j;	

	token = strtok(buff, space);
	token = strtok(NULL, space);

	b->size = atoi(token);
	//......NEW ARRAY FOR WALLS
	if(  (b->walls = malloc( (b->size-1) * sizeof (int *)) ) == NULL  )
		printf("unacceptable size 1\n\n");
	for (i=0; i< b->size -1; i++) 
		if( (b->walls[i] = malloc( (b->size-1) * sizeof(wall)) ) == NULL)
			printf("unacceptable size 2\n\n");
	//......		
	clear_board(b);

	fflush(stdout);
}

int wall_left(board* b, point p){
	
	//printf("is wall?? <(%d,%d)\n",p.x, p.y);
	if(p.y == 0) return 0;

	if(p.x>0 && p.x< b->size -1 && (b->walls[p.x-1][p.y-1].dir==VERTICAL || b->walls[p.x][p.y-1].dir==VERTICAL) )
		return 1;
	else if(p.x>0 && (b->walls[p.x-1][p.y-1].dir == VERTICAL) )
		return 1;
	else if(p.x< b->size -1 && (b->walls[p.x][p.y-1].dir == VERTICAL) )
		return 1;	
	else return 0;
}

int wall_up(board* b, point p){

//	printf("is wall?? ^(%d,%d)\n",p.x, p.y);
	if(p.x==0) return 0;
	
	if(p.y>0 && p.y< b->size -1 && (b->walls[p.x-1][p.y-1].dir==HORIZONTAL || b->walls[p.x-1][p.y].dir==HORIZONTAL) )
		return 1;
	else if(p.y>0 && (b->walls[p.x-1][p.y-1].dir == HORIZONTAL) )
		return 1;
	else if(p.y< b->size -1 && (b->walls[p.x-1][p.y].dir == HORIZONTAL) )
		return 1;
	else return 0;
}
int wall_right(board* b, point p){

//	printf("is wall?? >(%d,%d)\n",p.x, p.y);
	if(p.y == b->size -1) return 0;

	if(p.x>0 && p.x< b->size -1 && (b->walls[p.x-1][p.y].dir==VERTICAL || b->walls[p.x][p.y].dir==VERTICAL) )
		return 1;
	else if(p.x>0 && (b->walls[p.x-1][p.y].dir == VERTICAL) )
		return 1;
	else if(p.x< b->size -1 && (b->walls[p.x][p.y].dir == VERTICAL) )
		return 1;
	else return 0;
		
}
int wall_down(board* b, point p){

//	printf("is wall?? .(%d,%d)\n",p.x, p.y);
	if(p.x == b->size -1) return 0;
	
	if(p.y>0 && p.y< b->size -1 && (b->walls[p.x][p.y-1].dir==HORIZONTAL || b->walls[p.x][p.y].dir==HORIZONTAL) )
		return 1;
	else if(p.y>0 && (b->walls[p.x][p.y-1].dir == HORIZONTAL) )
		return 1;
	else if(p.y< b->size -1 && (b->walls[p.x][p.y].dir == HORIZONTAL) )
		return 1;
	else return 0;
}

// https://en.wikipedia.org/wiki/Maze_solving_algorithm#Recursive_algorithm  youtube: simple recursive maze solve
int there_is_path(board *b, point p, player* pl, int ** map){

	//go_to(char* where, &p, map){map[p.x][p.y] =1 p}

	point n; n.x = p.x; n.y = p.y;	
	map[p.x][p.y] = 1;
	
	if(pl->player_color == BLACK)  //black
	{	

		if(p.x == b->size -1) return 1;

		if ( legal_move(b, p, p.x +1, p.y) && !map[p.x+1][p.y]){
			n.x += 1 ;
			if( there_is_path(b, n, pl,map))
				return 1;
		}
		if ( legal_move(b, p, p.x, p.y +1) && !map[p.x][p.y +1] ){
			n.y += 1;
			if( there_is_path( b, n, pl, map))
				return 1;
		}
		if ( legal_move(b, p, p.x, p.y -1) && !map[p.x][p.y -1] ){
			n.y += -1;
			if( there_is_path( b, n, pl, map))
				return 1;
		}
		if ( legal_move(b, p, p.x -1, p.y) && !map[p.x -1][p.y]   ){
			n.x += -1;
			if( there_is_path( b, n,pl, map))
				return 1;
		}
		return 0;
	}
	
	else 
	{	

		if(p.x == 0) return 1;

		if ( legal_move(b, p, p.x -1, p.y) && !map[p.x -1][p.y]){
			n.x += -1 ;
			if( there_is_path(b, n, pl,map))
				return 1;
		}
		if ( legal_move(b, p, p.x, p.y +1) && !map[p.x][p.y +1] ){
			n.y += 1;
			if( there_is_path( b, n, pl, map))
				return 1;
		}
		if ( legal_move(b, p, p.x, p.y -1) && !map[p.x][p.y -1] ){
			n.y += -1;
			if( there_is_path( b, n, pl, map))
				return 1;
		}
		if ( legal_move(b, p, p.x +1, p.y) && !map[p.x +1][p.y]   ){
			n.x += 1;
			if( there_is_path( b, n,pl, map))
				return 1;
		}
		return 0;
	}

	
}

int check_for_path(board* b,player* pl){


	int i=0,j=0;
	point current;
	//map is a 2D array keeping track where the recursive algorithm have visited
	int **map = malloc(b-> size *sizeof(int*)  );
	for (i=0; i< b->size ; i++)
	{
		map[i] = malloc(b-> size*sizeof(int)  );
		for (j=0; j< b->size; j++)
			map[i][j] = 0;
	}

	current.x = pl->position.x; current.y = pl->position.y;
	
	int is_path= there_is_path(b,current,pl,map);

	for (i=0; i< b->size; i++)
		free(map[i]);
	free(map);

	return is_path;

}

int is_player_between(board *b, player pl, int x , int y){
//	used for jumps

	player* in_between;
	if (pl.player_color == 1)
		in_between = &b->player2;
	else in_between = &b->player1;

	return ( in_between->position.x == (x- pl.position.x)/2 && in_between->position.y == (y - pl.position.y)/2 );
}

int legal_move(board* b, point p,int x, int y){

	//printf("MOVE :(%d,%d) ->  (%d,%d)\n",pl->position.x, pl->position.y, x, y);

	int xchange=x - p.x;
	int ychange=y - p.y;
	point jump; jump.x = p.x; jump.y = p.y;

	if (x > b->size - 1 || y > b->size - 1 || x<0 || y<0) 
		return 0;	

	if ( ABS(ychange) == 0 )
	{
		
		if( xchange == 1) return !wall_down(b,p);
		else if( xchange == -1) return !wall_up(b,p);	
		else if( ABS(xchange) == 2 ){
			jump.x += (xchange)/2;
			if ( legal_move(b,jump,x,y) )
				return 2;
		}
		else return 0;
	}
	if ( ABS(xchange)== 0 )
	{	

		if( ychange == 1) return !wall_right(b,p);
		else if( ychange == -1) return !wall_left(b,p);	
		else if( ABS(ychange) == 2 ){
			jump.y += (ychange)/2;
			if (legal_move(b,jump,x,y) )
				return 2;
		}else return 0;
	}

//!!!return some other value to jump over player;	
	return 0;			
}

void placeplayer(player* pl, int x, int y){
	pl->position.x = x;
	pl->position.y = y;
}

void playmove(char* buff, board* b){

	char* token;
	int x,y;	

	token = strtok(buff, space);

//	get player to move		
	token = strtok(NULL, space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }

	player *p ;
	if (!strcmp(token,"black"))  p = &b->player1;
	else if ( !strcmp(token,"white" )  )p= &b->player2;
//**************************************

//	get point to move	
	token = strtok(NULL, space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }
	convert(token,&x,&y,b->size); //convert coordinates to my point	
	point current; current.x=p->position.x; current.y=p->position.y;
//**************************************

//	check if legal	
	int is_legal = legal_move(b,current,x,y);
	if (!is_legal || (is_legal==2 && is_player_between(b,*p,x,y))  )
	{
		printf("\n? illegal move\n\n");
		fflush(stdout);
		return;
	}
//**************************************

//	 move player	
	placeplayer(p, x , y);

}

int legal_wall(board* b,int x, int y,char d){

	if (x < 0 || x > b->size -2 || y > b->size -2 || y<0) //out of board
		return 0;
	if (b->walls[x][y].dir != NO_WALL)  //already a wall there
		return 0;
	if (d=='v')			//check for vertical walls (up) and/or (down)
	{
		if (x==0){
			if (b->walls[x+1][y].dir == VERTICAL) return 0;
		}
		else if (x== b->size -2){
			if (b->walls[x-1][y].dir == VERTICAL) return 0; 
		}
		else {
			if ( (b->walls[x-1][y].dir == VERTICAL) || ( b->walls[x+1][y].dir == VERTICAL) )
				return 0;
		}

	}

		
	else if (d=='h')       		//check for horizontal walls (left) and/or (right)
	{
		if (y==0){
			if (b->walls[x][y+1].dir == HORIZONTAL) return 0;
		}
		else if (y== b->size -2){
			if (b->walls[x][y-1].dir == HORIZONTAL) return 0; 
		}
		else {
			if (b->walls[x][y-1].dir == HORIZONTAL || b->walls[x][y+1].dir == HORIZONTAL)
				return 0;
		}
	}

	return 1;
}

int placewall(board* b, player* pl, int x, int y, char direction){
	
	if ( pl->available_walls  &&  legal_wall(b,x,y,direction) )	
	{
		if (direction == 'h') b->walls[x][y].dir = HORIZONTAL; //place temp wall
		else if (direction == 'v') b->walls[x][y].dir = VERTICAL;

		if(check_for_path( b,&b->player1) && check_for_path( b,&b->player2) )
			pl->available_walls --;  		//wall placed!  (leave temp wall^^ there)
		else b->walls[x][y].dir = NO_WALL;		 //wall not placed!
		
		return 1;
	}
	else return 0;
		
}

void playwall(char* buff, board* b){

	char* token;
	int x,y; char direction='?';	

	token = strtok(buff, space);

//	get the player who moves
	player* player_ptr;	
	token = strtok(NULL, space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }
	
	if ( !strcmp(token,"black") ) {player_ptr= &b->player1;}
	else if ( !strcmp(token,"white") ) {player_ptr= &b->player2;}
//*******************************

//	get the point of the wall
	token= strtok(NULL, space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }

	convert(token,&x,&y,b->size);
//*******************************

//	get direction of the wall
	token= strtok(NULL, space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }

	if      (!strcmp(token, "h") || !strcmp(token, "horizontal") ) direction = 'h';
	else if ( !strcmp(token, "v") || !strcmp(token, "vertical")  ) direction = 'v';
	else { printf("? syntax error\n\n"); fflush(stdout); return; }
//*******************************

//  	place wall if legal
	if (placewall(b,player_ptr, x, y, direction))
		printf("=\n\n");
	else printf("?illegal move\n\n");
//********************************
	
	fflush(stdout);
}

int is_winner(board *b,player p){

	if (p.player_color == 0)
		if( p.position.x == b->size -1)return 1;
	if (p.player_color == 1)
		if( p.position.x == 0) return 1;

	return 0;
}
void winner(board* b){

	if (is_winner(b,b->player1))
		printf("\n=true black\n");
	else if (is_winner(b,b->player2))
		printf("\n=true white\n");
	else printf("\n=false\n");
	fflush(stdout);
}

void genmove(char* buff, board* b,int* ai_wall, int* ai_blocked){

/***************************** Very Basic A.I ************************************
>path= where is upwards for the current player? 1=black/down  |  -1=white/up
>p = temp point for enemy
>curr = current position for me
>me = current player, enemy = the other player
>ai_wall = flag, place some walls in the begining or when u cant proceed to end
>ai_blocked = prolly useless, flag for not going into a blocked path again
**********************************************************************************/

	player *me,*enemy;
	point p,curr;
	char* token = strtok(buff,space);
	int path , i ,j; 
	token = strtok(NULL,space);
	if (token == NULL) { printf("? syntax error\n\n"); fflush(stdout); return; }

	if     (!strcmp(token,"black")) {me = &b->player1; path=1;  enemy= &b->player2;}
	else if(!strcmp(token,"white")) {me = &b->player2; path=-1; enemy= &b->player1;}
	else { printf("? syntax error\n\n"); fflush(stdout); return; }

	curr.x = me->position.x;
	curr.y = me->position.y;

	if(is_winner(b,*me)) return;
	if(*ai_wall && me->available_walls)
	{
		p.x=enemy->position.x; p.y=enemy->position.y;	
		if(path==1)			
		{	
			
			p.x += -path;
			if(!wall_up(b,p))
				if(placewall(b, me, p.x -1, p.y, 'h'))
				{
					printf("= %c%d h\n\n", curr.y+'A',  b->size +1 - (p.x -1 +path));
					fflush(stdout);
					*ai_wall --;
					return;	
				}			
		}
		if(path==-1)			
		{
			p.x += -path;
			if(!wall_down(b,p))
				if(placewall(b, me, p.x, p.y, 'h'))
				{
					printf("= %c%d h\n\n", curr.y+'A',  b->size -1- (p.x+path));
					fflush(stdout);
					*ai_wall --;
					return;	
				}					
		}
	}
	
	if( legal_move(b, curr, curr.x+path, curr.y))
	{
		placeplayer(me,curr.x+path , curr.y);
		printf("= %c%d\n\n", curr.y+'A',  b->size - (curr.x+path) );
		fflush(stdout);
		return;	
	}

	if(*ai_wall && me->available_walls && ( (path==-1 && !wall_down(b,curr)) || (path==1 && !wall_up(b,curr)) ) )
	{

		if ( (path== -1 && placewall(b, me , curr.x, curr.y, 'h')) 
		 || (path==1 && placewall(b, me , curr.x -1, curr.y, 'h')) ){
			printf("= %c%d h\n\n", curr.y+'A',  b->size - (curr.x+path));
			fflush(stdout);
			ai_wall --;
			return;	
		} 
	}

	if(*ai_blocked!='r' && legal_move(b, curr, curr.x, curr.y+1))
	{
		placeplayer(me,curr.x , curr.y +1);
		printf("= %c%d\n\n", curr.y+ 1 + 'A',  b->size - curr.x);
		fflush(stdout);
		return;	
	}
	else *ai_blocked = 'r';
	
	if(*ai_blocked != 'l' && legal_move(b, curr, curr.x, curr.y-1))
	{
		placeplayer(me,curr.x , curr.y -1);
		printf("= %c%d\n\n", curr.y -1 +'A',  b->size - curr.x);
		fflush(stdout);
		return;	
	}
	else *ai_blocked = 'l';
	
	// gg wp
	fflush(stdout);		
}


int main (void){

	char buff[101];  board  b;
	int ai_wall=2,ai_blocked=' ';
	int i,j; 

	while ( fgets(buff, 100, stdin) )
	{	
		if( buff[0] == '#' || buff[0] == '\n' || buff[0]=='\t') continue; //goto next fgets

		switch (get_command_id(buff)) {
			case 0:
				printf("? unknown command\n\n");
				fflush(stdout);
				break;
			case 1:
				name();
				break;
			case 2:
				known_command(buff);
				break;
			case 3:
				list_commands();
				break;
			case 4:
				for (i=0; i<b.size; i++)
					free(b.walls[i]);
				free(b.walls);
				printf("=\n\n");
				return 0;
				break;
			case 5:
				boardsize(buff, &b);
				break;
			case 6:
				clear_board(&b);
				break;
			case 7:
				walls(buff,&b.player1, &b.player2 );
				break;
			case 8:
				playmove(buff, &b);
				break;
			case 9:
				playwall(buff, &b);
				break;
			case 10:
				genmove(buff, &b,&ai_wall,&ai_blocked);
				break;
			case 11:
				// undo :'(   //list with head node    (1 node = 1 game_snapshot)
				break;
			case 12:
				winner(&b);
				break;
			case 13:
				showboard(&b);
				break;
			default:
				break;
		}
		fflush(stdout);
	}	
	return 0;
}

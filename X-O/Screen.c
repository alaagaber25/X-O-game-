#include "Nokia5110.h"
#include "game.h"
#include "draws.h"
#include "tm4c123gh6pm.h"
#include "Screen.h"
#include "Timer.h"
char turn;
void showIntro(void){
	Nokia5110_PrintBMP(0, 47, intro, 0);
	Nokia5110_DisplayBuffer();  
	Timer2_Init(15);
	Nokia5110_Clear();
	Nokia5110_PrintBMP(0, 47, intro2, 0);
	Nokia5110_DisplayBuffer();  
	Timer2_Init(15);
	Nokia5110_Clear();
}

void winner(char player){
	Nokia5110_ClearBuffer();
	
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 1);
	if(player=='X'){
	xWins++;
		Nokia5110_OutString("Player-1");
	}
	else{
	oWins++;
		Nokia5110_OutString("Player-2");
	}
	Nokia5110_SetCursor(4, 2);
	Nokia5110_OutString("wins");
	Nokia5110_SetCursor(1, 3);
	Nokia5110_OutString("P-1:");
	Nokia5110_OutUDec(xWins);
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString("P-2:");
	Nokia5110_OutUDec(oWins);
	Timer2_Init(15);
	Nokia5110_Clear();
}


void draw(){
	Timer2_Init(15);
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 2);
	Nokia5110_OutString("Game is");
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("a draw");
	Timer2_Init(15);
	Nokia5110_Clear();
	return;
}




void playerTurn(){
	Nokia5110_SetCursor(8, 1);
	if(turn == 'X'){
	Nokia5110_OutString("P-1");
	}
	else{
	Nokia5110_OutString("P-2");
	}
	Nokia5110_SetCursor(8, 2);
	Nokia5110_OutString("Turn");
	
}



void showOutro(){
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(1, 2);
	Nokia5110_OutString("GoodBye");
	Timer2_Init(15);
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(0, 0);
	Nokia5110_OutString("Made By:");
	Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString("Alaa Gaber");
	Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString("Ali Abdelmonim");
	Nokia5110_SetCursor(0, 4);
	Nokia5110_OutString("Ahmed Goda");
	Nokia5110_SetCursor(0, 5);
	Nokia5110_OutString("Abdallah");
	Timer2_Init(20);
	Nokia5110_Clear();
}


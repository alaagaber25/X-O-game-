#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "game.h"
#include "Screen.h"
#include "draws.h"
#include "Timer.h"
int  xWins = 0;
int oWins = 0;
int playedCells;
int currentCell;
char matrix[9];
int SW1, SW2; 
int replay(){
	Nokia5110_ClearBuffer();
	Nokia5110_SetCursor(0, 1);
	Nokia5110_OutString("Play again ?");
	Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString("SW1 for YES");
	Nokia5110_SetCursor(0, 4);
	Nokia5110_OutString("Sw2 for No");
	while(1){
		int  SW1=0,SW2=0;
		while(!(GPIO_PORTB_DATA_R&0x10))SW1=1;      
		if(SW1)return 1;
		while(!(GPIO_PORTB_DATA_R&0x01))SW2=1;      
		if(SW2)return 0;
	}
}

void reset(){
	int i;
	playedCells=0;
	turn='X';
	currentCell=-1;
	for(i=0;i<9;i++){
		matrix[i]=' ';
}
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 15, square, 0);
	Nokia5110_PrintBMP(0, 30, square, 0);
	Nokia5110_PrintBMP(0, 45, square, 0);
	
	Nokia5110_PrintBMP(16, 15, square, 0);
	Nokia5110_PrintBMP(16, 30, square, 0);
	Nokia5110_PrintBMP(16, 45, square, 0);

	Nokia5110_PrintBMP(32, 15, square, 0);
	Nokia5110_PrintBMP(32, 30, square, 0);
	Nokia5110_PrintBMP(32, 45, square, 0);
	Nokia5110_DisplayBuffer();
	playerTurn();
	}


int checkWinner(char player){
	int finished, i;
	if(matrix[0]==player && matrix[1]==player && matrix[2]==player){
		finished=1;
		i=0;
	}
	else if(matrix[3]==player && matrix[4]==player && matrix[5]==player){
		finished=1;
		i=1;
	}
	else if(matrix[6]==player && matrix[7]==player && matrix[8]==player){
		finished=1;
		i=2;
	}
	else if(matrix[0]==player && matrix[3]==player && matrix[6]==player){
		finished=1;
		i=3;
	}
	else if(matrix[1]==player && matrix[4]==player && matrix[7]==player){
		finished=1;
		i=4;
	}
	else if(matrix[2]==player && matrix[5]==player && matrix[8]==player){
		finished=1;
		i=5;
	}
	else if(matrix[0]==player && matrix[4]==player && matrix[8]==player){
		finished=1;
		i=6;
	}
	else if(matrix[2]==player && matrix[4]==player && matrix[6]==player){
		finished=1;
		i=7;
	}
	if(finished){
		if(i==0){
			for(i=0;i<48;i++)Nokia5110_SetPixel(i,6);
		}
		else if(i==1){
			for(i=0;i<48;i++)Nokia5110_SetPixel(i,23);
		}
		else if(i==2){
			for(i=0;i<48;i++)Nokia5110_SetPixel(i,40);
		}
		else if(i==3){
			for(i=0;i<48;i++)Nokia5110_SetPixel(6,i);
		}
		else if(i==4){
			for(i=0;i<48;i++)Nokia5110_SetPixel(23,i);
		}
		else if(i==5){
			for(i=0;i<48;i++)Nokia5110_SetPixel(40,i);
		}
		else if(i==6){
			for(i=0;i<48;i++)Nokia5110_SetPixel(i,i);
		}
		else if(i==7){
			for(i=0;i<48;i++)Nokia5110_SetPixel(i,47-i);
		}
		Nokia5110_DisplayBuffer();
		Timer2_Init(10);  
		return 1;
	}
	return 0;
}




void play(){
	int row, col, prevRow, prevCol, prevCell;
	if(SW2 && currentCell!=-1){           
		if(matrix[currentCell]==' '){
			row = currentCell/3;
			col = currentCell%3;
			if(turn=='X'){
				Nokia5110_PrintBMP(col*16, (row+1)*15, X, 0);
				matrix[currentCell]=turn;
				if(checkWinner(turn)){
					winner(turn);
					if(replay()){
						reset();
						return;
					}
					else{
						showOutro();
						while(1);
					}
				}
				turn='O';
			}
			else{
				Nokia5110_PrintBMP(col*16, (row+1)*15, O, 0);
				matrix[currentCell]=turn;
				if(checkWinner(turn)){
					winner(turn);
					if(replay()){
						reset();
						return;
					}
					else{
						showOutro();
						while(1);
					}
				}
				turn='X';
			}
			Nokia5110_DisplayBuffer();
			playerTurn();
			currentCell=-1;
			playedCells++;
			if(playedCells==9){
				draw();
				if(replay()){
						reset();
						return;
				}
				else{
					showOutro();
					while(1);
				}
			}
		}
	}
	if(SW1){
		prevCell=currentCell;
		currentCell++;
		while(matrix[currentCell] != ' '){
		currentCell++;
		currentCell %=9;
		}
		row = currentCell/3;
		col = currentCell%3;
		if(matrix[currentCell]==' '){
			Nokia5110_PrintBMP(col*16, (row+1)*15, select, 0);
		}
			prevRow = (prevCell)/3;
		  prevCol = (prevCell)%3;
		if(matrix[currentCell]==' '){
			Nokia5110_PrintBMP(prevCol*16, (prevRow+1)*15, square, 0);
		}
		Nokia5110_DisplayBuffer();
		playerTurn();
	}
}

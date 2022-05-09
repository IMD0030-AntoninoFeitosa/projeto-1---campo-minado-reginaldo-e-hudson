#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <fstream>

typedef struct{
  std::string nome;
  int tempo;
}Record;

int readRow(int r, int r_in, bool &erro);

char readCol(int c,char aux_c_in, bool &erro);

void markSquares(int r, int c, int **tabuleiro,int **tabuleiro_aux);

void showNearbySquares(int linhaAtual, int colunaAtual, int linhaMax, int colunaMax,int **tabuleiro,int **tabuleiro_aux);

void backtracking(int linhaAtual, int colunaAtual, int linhaMax, int colunaMax,int **tabuleiro,int **tabuleiro_aux);

bool endGame(int r, int c, int minas, int **tabuleiro, int **tabuleiro_aux);

void showSquares(int r, int c, int **tabuleiro,int **tabuleiro_aux);
void showTime(time_t tempo_inicial);

std::string timeToString(int sec);

void gameAction(int r,int c, int **tabuleiro,int **tabuleiro_aux, time_t tempo_inicial);

void switch_dif(char dif, int &row, int &col, int &minas);

void PrintAuxBoard(int row, int col, int **tabuleiro, int **tabuleiro_aux);

void PrintBoard(int row, int col, int **tabuleiro, int **tabuleiro_aux);

void CreateBoard(int row, int col, int **tabuleiro, int **tabuleiro_aux);

void ordenarTabela(Record *record);

void startGame(int dif);

#endif

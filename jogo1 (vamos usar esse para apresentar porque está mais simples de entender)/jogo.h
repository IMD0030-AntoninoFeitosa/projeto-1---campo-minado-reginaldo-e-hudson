#ifndef JOGO
#define JOGO
#include <iostream>

typedef struct{
  std::string nome; //nome da pessoa que está entre os 10 melhores tempos
  int tempo; // tempo do jogo
}Record;

void mudarDificuldade(int dif);
//Função para verificar se um par de coordenadas é válido ou não (1 é válido e 0 não é válido)
int coordenadaValida(int l, int c);

//Função para retonar a quantidade de bombas de l c
int bombasVizinhas(int l, int c);

//procedimento para contar as bombas vizinhas
void contarBombas();

//procedimento para gerar bombas randomicamente
void gerarBombas(int b);

void inicializarJogo();

//procedimento para imprimir o jogo
void imprimirTabuleiro();

//Função para verificar vitória (1 - ganhou, 0 - perdeu)
int resultadoJogo();

//procedimento para abrir a celula pelas coordenadas dadas
void abrirCelula(int l, int c);

void leituraCoordenadas();

void marcarBandeira(int linha, int coluna);

void lerCoordenadaBandeira();

std::string tempoFormatado(int seg);

double tempoAtualEmSegundos();

void verificarTempo();

void acaoJogo();

//procedimento que ordena os records de acordo com o tempo, utilizando o método "bubblesort"
void ordenarTabela(Record *record);

//procedimento principal para o funcionamento do jogo
void jogoPrincipal();

#endif
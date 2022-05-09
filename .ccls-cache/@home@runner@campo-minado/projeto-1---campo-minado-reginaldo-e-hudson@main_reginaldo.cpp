#include<iostream>
#include<time.h>


typedef struct{
  int bomba; //Indica se há bomba na célula (0 - sem bomba ou 1 - com bomba)
  int aberta; //Indica se a célula já foi aberta (0 - fechada ou 1 - aberta)
  int vizinhos; //Indica quantas bombas há na vizinhança (0 a 4) 

}Celula;

Celula jogo[10][10];
int l, c, tam = 10;

//Inicializar a matriz do jogo
void inicializarJogo()
{
  for(l = 0; l < tam; l++)
  {
    for(c = 0; c < tam; c++)
    {
      jogo[l][c].bomba = 0;
      jogo[l][c].aberta = 0;
      jogo[l][c].vizinhos = 0;
    }
  }
}

//Gerar bombas
void gerarBombas(int b)
{
  int i;
  srand(time(NULL));
  for(i = 1; i <= b; i++)
  {
    l = rand() % tam;
    c = rand() % tam;
    if(jogo[l][c].bomba == 0)
      jogo[l][c].bomba = 1;
    else
      i--;
  }
  
}

//Fun�o para verificar se um par de coordenadas � v�lido ou n�o (1 � v�lido e 0 n�o � v�lido)

int coordenadaValida(int l, int c)
{
  if(l >= 0 && l < tam && c >= 0 && c < tam)
    return 1;
  else
    return 0;
}
  

//Fun�o para retonar a quantidade de bombas de l c
int bombasVizinhas(int l, int c)
{
  int qtd = 0; //vari�vel para guardar a quantidade de bombas na vizinhan�a

  if(coordenadaValida(l - 1, c) && jogo[l-1][c].bomba)
    qtd++;
  if(coordenadaValida(l + 1, c) && jogo[l+1][c].bomba)
    qtd++;
  if(coordenadaValida(l, c + 1) && jogo[l][c+1].bomba)
    qtd++;
  if(coordenadaValida(l, c - 1) && jogo[l][c-1].bomba)
    qtd++;
  return qtd;  
}

//Contar as bombas vizinhas
void contarBombas()
{
  for(l = 0; l < tam; l++)
    for(c = 0; c < tam; c++)
      jogo[l][c].vizinhos = bombasVizinhas(l, c);
}

//Imprimir o jogo

void imprimirTabuleiro()
{
  for(l = 1; l <= tam; l++)
    std::cout << "\t" << l;
    std::cout << std::endl;
   for(l = 0; l < tam; l++)
   {
    std::cout << l + 1 << " ";
    for(c = 0; c < tam; c++)
    {
      if(jogo[l][c].aberta){
        if(jogo[l][c].bomba)
          std::cout << "?";
        else
          std::cout << jogo[l][c].vizinhos;
    }
      else
        std:: cout << "\t?";
    }
     std::cout << "\n";
  }
}
//Abrir a celula pelas coordenadas do jogador

void abrirCelula(int l, int c)
{
  if(coordenadaValida(l, c) == 1 && jogo[l][c].aberta == 0)
  {
    jogo[l][c].aberta = 1;
    if(jogo[l][c].vizinhos == 0)
    {
      abrirCelula(l-1, c);
      abrirCelula(l+1, c);
      abrirCelula(l, c-1);
      abrirCelula(l, c+1);
    }
  }
}
//Leitura das coordenadas

void leituraCoordenadas()
{
  int linha, coluna;
  do{
    std::cout << "Digite as coordenadas de uma linha e uma  coluna: "  << std::endl;
    std::cin >> linha >> coluna;
    if(coordenadaValida(linha, coluna) == 0)
      std::cout << "\nCoordenada inv�lida!\n\n";
      }while(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].aberta == 1);
  
  abrirCelula(linha, coluna);
  
}


int main(){
  int b = 10;
  inicializarJogo();
  gerarBombas(b);
  contarBombas();
  std::cout << "CAMPO MINADO" << std::endl;
  std::cout << std::endl;
  imprimirTabuleiro();
  std::cout << std::endl;
  leituraCoordenadas();
  
  
  return 0;
}

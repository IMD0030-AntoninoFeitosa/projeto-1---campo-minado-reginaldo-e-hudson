#include<iostream>
#include <fstream>
#include <iostream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

typedef struct{
  int bomba; //Indica se há bomba na célula (0 - sem bomba ou 1 - com bomba)
  int aberta; //Indica se a célula já foi aberta (0 - fechada ou 1 - aberta)
  int vizinhos; //Indica quantas bombas há na vizinhança (0 a 4) 
  int bandeira; //Indica se a célula tem uma bandeira (0 - não tem ou 1 - tem bandeira)
}Celula;

typedef struct{
  std::string nome; //nome da pessoa que está entre os 10 melhores tempos
  int tempo; // tempo do jogo
}Record;

Celula jogo[10][10];
int l, c, tam = 10, b;
time_t tempo_inicial;
std::string diretorio; //variável global que armazena o diretório dos records de acordo com a dificuldade


void mudarDificuldade(int dif){
  switch(dif){
    //iniciante
    case 'b':
      l = 10;
      c = 10;
      b = 10;
      diretorio = "records/b.txt";
      break;
    
    //intermediário
    case 'i':
      l = 15;
      c = 15;
      b = 40;
      diretorio = "records/i.txt";
      break;
    
    //avançado
    case 'a':
      l = 15;
      c = 30;
      b = 100;
      diretorio = "records/a.txt";
      break;
    
    //Padrão
    default:
      l = 10;
      c = 10;
      b = 10;
      diretorio = "records/b.txt";
  }
}


//void leituraCoordenadas();

//Função para verificar se um par de coordenadas é válido ou não (1 é válido e 0 não é válido)

int coordenadaValida(int l, int c)
{
  if(l >= 0 && l < tam && c >= 0 && c < tam)
    return 1;
  else
    return 0;
}

//Função para retonar a quantidade de bombas de l c
int bombasVizinhas(int l, int c)
{
  int qtd = 0; //variável para guardar a quantidade de bombas na vizinhança

  for(int lAux=l-1;lAux<=l+1;lAux++){
    for(int cAux=c-1;cAux<=c+1;cAux++){
      if(coordenadaValida(lAux, cAux) && jogo[lAux][cAux].bomba)
        qtd++;
    }
  }
  
  return qtd;  
}

//procedimento para contar as bombas vizinhas
void contarBombas()
{
  for(l = 0; l < tam; l++)
    for(c = 0; c < tam; c++)
      jogo[l][c].vizinhos = bombasVizinhas(l, c);
}


//procedimento para gerar bombas randomicamente
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
  contarBombas();
}

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
  gerarBombas(b);
}

//procedimento para imprimir o jogo

void imprimirTabuleiro()
{
  std::cout << "\n\n\t   ";
  for(l = 0; l < tam; l++)
    std::cout << "  " << l << " ";//índices das colunas
    std::cout << "\n\t   ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n";
   for(l = 0; l < tam; l++)
   {
     //índice das linhas
      std::cout << "\t";
      std::cout <<  " " << l << " ";
      std::cout << "▐";
    for(c = 0; c < tam; c++)
    {
      if(jogo[l][c].aberta){
        if(jogo[l][c].vizinhos == 0){
          std::cout << "   ▐";
        } else if(jogo[l][c].bomba){
          std::cout << " ✸ ▐";
        }
        else{
          std::cout << " " << jogo[l][c].vizinhos << " ▐";
        }
      } else {
        if(jogo[l][c].bandeira == 1){
          std:: cout << " ✜ ";
          std::cout << "▐";
        } else {
          std:: cout << " ■ ";
          std::cout << "▐";
        }
      }
    }
    std::cout << "\n\t   ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n";
  }
}



//Função para verificar vitória (1 - ganhou, 0 - perdeu)

int resultadoJogo()
{
  int quantidade = 0;
  for(l = 0; l < tam; l++)
  {
    for(c = 0; c < tam; c++)
    { 
      if(jogo[l][c].aberta == 0 && jogo[l][c].bomba == 0)//verificando se a posição não está fechada e se não é uma bomba
      quantidade++;
    }
  }
  return quantidade;
}

//procedimento para abrir a celula pelas coordenadas dadas

void abrirCelula(int l, int c)
{
  if(coordenadaValida(l, c) == 1 && jogo[l][c].aberta == 0)//verificar se as coordenadas da célula são válidas e está fechada
  {
    jogo[l][c].aberta = 1;
    if(jogo[l][c].vizinhos == 0)
    {  //chamada recursisva para verificar para as células vizinhas

      for(int lAux=l-1;lAux<=l+1;lAux++){
        for(int cAux=c-1;cAux<=c+1;cAux++){
          abrirCelula(lAux, cAux);
        }
      }
      
    }
  }
}

void leituraCoordenadas()
{
  int linha, coluna;
  std::cout << std::endl;
    do{
      std::cout << "Digite as coordenadas de uma linha e uma  coluna: "  << std::endl;
      std::cin >> linha >> coluna;
      if(coordenadaValida(linha, coluna) == 0) // teste para caso a coordenada seja inválida
        std::cout << "\nCoordenada inválida!\n\n";
    }while(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].aberta == 1); // repetir a leitura enquanto a coordenada for válida e fechada
    
    abrirCelula(linha, coluna);
 
}

void marcarBandeira(int linha, int coluna)
{
  jogo[linha][coluna].bandeira = 1;
  
}

void lerCoordenadaBandeira()
{
  int linha, coluna;
  std::cout << std::endl;
  do{
    std::cout << "Digite as coordenadas de uma linha e uma  coluna da bandeira: "  << std::endl;
    std::cin >> linha >> coluna;
    if(coordenadaValida(linha, coluna) == 0) // teste para caso a coordenada seja inválida
    std::cout << "\nCoordenada inválida!\n\n";
  }while(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].aberta == 1); // repetir a leitura enquanto a coordenada for válida e fechada

  marcarBandeira(linha, coluna);
}

std::string tempoFormatado(int seg){
  int min=0;
  std::string tempo;
  
  if(seg>=60){
    min=seg/60;
    seg=static_cast<int>(seg)%60; 
  }
  if(min==0){
    if(seg>0 && seg<10){
      tempo = "00:0" + std::to_string(seg);
    }else {
      tempo = "00:" + std::to_string(seg);
    }
  } else if(min>0 && min<10){
    if(seg>0 && seg<10){
      tempo = "0" + std::to_string(min) +":0" + std::to_string(seg);
    }else {
      tempo = std::to_string(min) + ":" + std::to_string(seg);
    }
  } else if(min>=10){
    std::cout << min;
    if(seg>0 && seg<10){
      tempo = std::to_string(min) + ":0" + std::to_string(seg);
    }else {
      tempo = std::to_string(min) + ":" + std::to_string(seg);
    }
  }
  
  return tempo;
}

double tempoAtualEmSegundos(){
  time_t tempo_atual;
  time(&tempo_atual);
  
  tm *tempo_final_info=localtime(&tempo_atual);
  tempo_atual=mktime(tempo_final_info);
  double seg=difftime(tempo_atual, tempo_inicial);
  
  return seg;
}

void verificarTempo(){
  
  double seg=tempoAtualEmSegundos();
  
  std::cout << "tempo decorrido: " << tempoFormatado(seg);
}

void acaoJogo()
{
  int op;

  std::cout << "Escolha sua opçao: " << std::endl;
  std::cout << "1. Fazer jogada." << std::endl;
  std::cout << "2. Marcar bandeira." << std::endl;
  std::cout << "3. Tempo." << std::endl << std::endl;
  std::cout << "opção: ";

  std::cin >> op;
  switch(op){
    case 1:
      leituraCoordenadas();
      break;
    
    case 2:
      lerCoordenadaBandeira();
      break;
    
    case 3:
      verificarTempo();
      break;
  }

}

//procedimento que ordena os records de acordo com o tempo, utilizando o método "bubblesort"
void ordenarTabela(Record *record){
  std::string aux_nome;
  int aux_tempo;
  for(int i=1;i<10;i++){
    for(int j=0;j<9;j++){
      if(record[j].tempo >= record[j+1].tempo || record[j].tempo == 0){

        aux_nome = record[j].nome;
        record[j].nome = record[j+1].nome;
        record[j+1].nome = aux_nome;

        aux_tempo = record[j].tempo;
        record[j].tempo = record[j+1].tempo;
        record[j+1].tempo = aux_tempo;
      }
    }
  }
}

//procedimento principal para o funcionamento do jogo
void jogoPrincipal()
{
  int linha, coluna;

  //marca o tempo inicial
  time(&tempo_inicial);
  tm *tempo_inicial_info=localtime(&tempo_inicial);
  tempo_inicial=mktime(tempo_inicial_info);

  //loop do jogo
  do{
    imprimirTabuleiro();
    acaoJogo();
  }while(resultadoJogo() != 0);//Laço que acontece enquanto o jogador não ganhar e enquanto não abrir uma bomba
   
    
  if(jogo[linha][coluna].bomba == 1)
    std::cout << "\nQue pena! Você perdeu! ☹\n\n";
  else
    std::cout << "\nPARABÉNS! VOCÊ GANHOU! ✌\n\n"; 
  
  verificarTempo();
  
  imprimirTabuleiro();

  //SE O JOGADOR GANHOU VAI EXECUTAR ESSE BLOCO
  if(jogo[linha][coluna].bomba != 1) {
    //tempo do fim de partida
    double tempo_final=tempoAtualEmSegundos();
  
    std::fstream arquivo;
    std::string texto_arquivo;
    arquivo.open(diretorio, std::ios::in); // abre o arquivo para leitura
    
    int r_indice=0;
    int r_quant=0;
    Record record[10];
    
    if(arquivo.is_open()){

      for(int i=0;i<10;i++){
        record[i].nome = "-";
        record[i].tempo = 0;
      }
      
      while(getline(arquivo,texto_arquivo)){ //enquanto tiver records no arquivo vai armazenar as informações na struct "record"

          if(r_indice==0){ //armazena o nome do jogador
            record[r_quant].nome = texto_arquivo;
            r_indice++;
          } else { //armazena o tempo do jogador
            record[r_quant].tempo = std::stoi(texto_arquivo); //stoi transforma uma string em um inteiro
            r_indice=0;
            r_quant++;
          }
      }
    }
    arquivo.close();
    
    //ORDENAR RECORDS
    ordenarTabela(record);
    
    if(r_quant<=10 && (tempo_final < record[9].tempo || record[9].tempo == 0)){
      std::string nome;
      std::cout << std::endl << "Você está entre os 10 jogadores com o melhor tempo.\n\n Digite o seu nome para entrar nos records: ";
      std::cin >> nome;

      record[9].nome = nome;
      record[9].tempo = tempo_final;
      
      //ORDENAR RECORDS
      ordenarTabela(record);
    }
    
    remove("records/"); // limpa o arquivo para inserir os novos records
    
    arquivo.open(diretorio, std::ios::out);
    for(int i=0;i<10;i++){ //percorre os records e armazena as informações novamente
      arquivo << record[i].nome << "\n";
      arquivo << record[i].tempo << "\n";
    }
    
    arquivo.close();  
    
  }
  
}
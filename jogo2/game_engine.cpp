#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "game_engine.h"


//--------------------------------------------------------------------
//VARIÁVEL GLOBAL PARA VERIFICAR SE A PARTIDA ESTÁ ROLANDO
//--------------------------------------------------------------------
bool game_control = true;


//--------------------------------------------------------------------
//FAZ A LEITURA DA LINHA DIGITADA
//--------------------------------------------------------------------
int readRow(int r, int r_in, bool &erro){
  
  //verifica se a linha é válida
  if(!(r_in > 0 && r_in < r+1)){
    erro = true;
  } else {
    r_in--;
  }
  
  return r_in;
}


//--------------------------------------------------------------------
//FAZ A LEITURA DA COLUNA DIGITADA
//--------------------------------------------------------------------
char readCol(int c,char aux_c_in, bool &erro){
  int c_in;
  //identifica a coluna, trocando de char para int
  if(static_cast<int>(aux_c_in) > 48 && static_cast<int>(aux_c_in) <= 52){
    c_in = static_cast<int>(aux_c_in)-23;
  }else if(static_cast<int>(aux_c_in) > 64 && static_cast<int>(aux_c_in) <= 90){
    c_in = static_cast<int>(aux_c_in)-65;
  }else if(static_cast<int>(aux_c_in) > 96 && static_cast<int>(aux_c_in) <= 122){
    c_in = static_cast<int>(aux_c_in)-97;
  }

  //verifica se a coluna é válida
  if(!(c_in >= 0 && c_in < c)){
    erro = true;
  }
  
  return c_in;
}


//--------------------------------------------------------------------
//MARCA UMA CASA COM UMA BANDEIRA, INDICANDO QUE TEM UMA MINA
//--------------------------------------------------------------------
void markSquares(int r, int c, int **tabuleiro,int **tabuleiro_aux){
  int r_in, c_in;
  char aux_c_in;
  bool erro=false;
  
  std::cout << std::endl;
  std::cout << "Digite a linha e a coluna respectivamente:" << std::endl;
  std::cin >> r_in;
  std::cin >> aux_c_in;

  r_in = readRow(r, r_in, erro);
  c_in = readCol(c, aux_c_in, erro);
  
  if(erro==false){
    int &ref = tabuleiro[r_in][c_in];
    if(tabuleiro[r_in][c_in] == 0){
      ref = -2;
    } else if(tabuleiro[r_in][c_in] == -2){
      ref = 0;
    }
    
  } else {
    std::cout << "LINHA OU COLUNA INVÁLIDA";
  }
  
}


//--------------------------------------------------------------------
//REVELA AS CASAS COM NÚMEROS PRÓXIMAS DA CASA QUE O BACKTRACKING ESTÁ
//--------------------------------------------------------------------
void showNearbySquares(int linhaAtual, int colunaAtual, int linhaMax, int colunaMax,int **tabuleiro,int **tabuleiro_aux){

  for(int i=linhaAtual-1;i<=linhaAtual+1;i++){
    for(int j=colunaAtual-1;j<=colunaAtual+1;j++){
      
      if((i >= 0 && i <= linhaMax-1) && (j >= 0 && j <= colunaMax-1)){
        if(tabuleiro_aux[i][j] > 0){
          int &ref_tabuleiro = tabuleiro[i][j];
          ref_tabuleiro = 1;
        }
      }
      
    }
  }
}


//--------------------------------------------------------------------
//REVELA TODAS AS CASAS ADJACENTES QUE SÃO VAZIAS
//--------------------------------------------------------------------
void backtracking(int linhaAtual, int colunaAtual, int linhaMax, int colunaMax,int **tabuleiro,int **tabuleiro_aux){
  
  int &ref_tabuleiro = tabuleiro[linhaAtual][colunaAtual];
  ref_tabuleiro = 1;
  
  //verifica uma casa vazia para CIMA
  if(linhaAtual-1>=0
  && tabuleiro_aux[linhaAtual-1][colunaAtual]==0
  && tabuleiro[linhaAtual-1][colunaAtual]==0){
    
      //chamar backtracking
      backtracking(linhaAtual-1,colunaAtual,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
      //revelar casa do tabuleiro principal
      showNearbySquares(linhaAtual-1,colunaAtual,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
  }  
    
  //verifica uma casa vazia para BAIXO
  if(linhaAtual+1<linhaMax
  && tabuleiro_aux[linhaAtual+1][colunaAtual]==0
  && tabuleiro[linhaAtual+1][colunaAtual]==0){
    
      //chamar backtracking
      backtracking(linhaAtual+1,colunaAtual,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
      //revelar casa do tabuleiro principal
      showNearbySquares(linhaAtual+1,colunaAtual,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
  }
  
  //verifica uma casa vazia para ESQUERDA
  if(colunaAtual-1>=0
  && tabuleiro_aux[linhaAtual][colunaAtual-1]==0
  && tabuleiro[linhaAtual][colunaAtual-1]==0){
    
      //chamar backtracking
      backtracking(linhaAtual,colunaAtual-1,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
      //revelar casa do tabuleiro principal
      showNearbySquares(linhaAtual,colunaAtual-1,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
  }
  
  //verifica uma casa vazia para DIREITA
  if(colunaAtual+1<colunaMax
  && tabuleiro_aux[linhaAtual][colunaAtual+1]==0
  && tabuleiro[linhaAtual][colunaAtual+1]==0){
    
      //chamar backtracking
      backtracking(linhaAtual,colunaAtual+1,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
      //revelar casa do tabuleiro principal
      showNearbySquares(linhaAtual,colunaAtual+1,linhaMax,colunaMax,tabuleiro, tabuleiro_aux);
  }
}

bool endGame(int r, int c, int minas, int **tabuleiro, int **tabuleiro_aux){
  
  int quantMians=0;
  
  for(int i=0;i<r;i++){
    for(int j=0;j<c;j++){
      if(tabuleiro[i][j] == 0){
        quantMians++;
      }
    }
  }

  if(minas == quantMians){
    return true;
  } else {
    return false;
  }
}


//--------------------------------------------------------------------
//REVELA ALGUMA CASA SELECIONADA
//--------------------------------------------------------------------
void showSquares(int r, int c, int **tabuleiro,int **tabuleiro_aux){
  int r_in, c_in;
  char aux_c_in;
  bool erro=false;
  bool &ref_game_control = game_control;
  
  std::cout << std::endl;
  std::cout << "Digite a linha e a coluna respectivamente:" << std::endl;
  std::cin >> r_in;
  std::cin >> aux_c_in;

  r_in = readRow(r, r_in, erro);
  c_in = readCol(c, aux_c_in, erro);

  //se o usuário digitou as coordenadas corretamente
  if(erro==false){
    int &ref_tabuleiro = tabuleiro[r_in][c_in];

    //Se a casa selecionada for vazia
    if(tabuleiro_aux[r_in][c_in] == 0){
      ref_tabuleiro = 1;
      backtracking(r_in,c_in,r,c,tabuleiro, tabuleiro_aux);
      
    //Se a casa selecionada tiver uma bomba próxima
    } else if(tabuleiro_aux[r_in][c_in] > 0){
      if(tabuleiro[r_in][c_in] == 0){
        ref_tabuleiro = 1;
      } else {
        int quantMinas=0;
        
        for(int i=r_in-1;i<=r_in+1;i++){
          for(int j=c_in-1;j<=c_in+1;j++){
            if((i >= 0 && i <= r-1) && (j >= 0 && j <= c-1)){
              if(tabuleiro[i][j] == -2){
                quantMinas++;
              }
            }
          }
        }
        if(quantMinas == tabuleiro_aux[r_in][c_in]){
          for(int i=r_in-1;i<=r_in+1;i++){
            for(int j=c_in-1;j<=c_in+1;j++){
              if((i >= 0 && i <= r-1) && (j >= 0 && j <= c-1)){
                if(tabuleiro_aux[i][j] != -1){
                  int &ref_tabuleiro_aux = tabuleiro[i][j];
                  ref_tabuleiro_aux = 1;
                }
              }
            }
          }
          
          ///verifica se o usuário marcou as bombas corretamente
          int quantMinasMarcadas = 0;
          
          for(int i=r_in-1;i<=r_in+1;i++){
            for(int j=c_in-1;j<=c_in+1;j++){
              if((i >= 0 && i <= r-1) && (j >= 0 && j <= c-1)){
                if(tabuleiro_aux[i][j] == -1 && tabuleiro[i][j] == -2){
                  quantMinasMarcadas++;
                }
              }
            }
          }
          
          if(quantMinas != quantMinasMarcadas){
            ref_game_control = false;
          }
        }
        
      }
      
    //Se a casa selecionada for uma bomba
    } else if(tabuleiro_aux[r_in][c_in] == -1){
      ref_game_control = false;
    }
    
  } else {
    std::cout << "LINHA OU COLUNA INVÁLIDA";
  }
  
}

std::string timeToString(int sec){
  int min=0;
  std::string tempo;
  
  if(sec>=60){
    min=sec/60;
    sec=static_cast<int>(sec)%60; 
  }
  if(min==0){
    if(sec>0 && sec<10){
      tempo = "00:0" + std::to_string(sec);
    }else {
      tempo = "00:" + std::to_string(sec);
    }
  } else if(min>0 && min<10){
    if(sec>0 && sec<10){
      tempo = "0" + std::to_string(min) +":0" + std::to_string(sec);
    }else {
      tempo = std::to_string(min) + ":" + std::to_string(sec);
    }
  } else if(min>=10){
    std::cout << min;
    if(sec>0 && sec<10){
      tempo = std::to_string(min) + ":0" + std::to_string(sec);
    }else {
      tempo = std::to_string(min) + ":" + std::to_string(sec);
    }
  }
  
  return tempo;
}

//--------------------------------------------------------------------
//MOSTRA O TEMPO DA PARTIDA
//--------------------------------------------------------------------
void showTime(time_t tempo_inicial){
  system("clear");
  time_t tempo_atual;
  time(&tempo_atual);
  
  tm *tempo_final_info=localtime(&tempo_atual);
  tempo_atual=mktime(tempo_final_info);
  double sec=difftime(tempo_atual, tempo_inicial);
  std::cout << "tempo decorrido: " << timeToString(sec);
  
  char continuar;
  std::cout << std::endl << std::endl << "Pressione qualquer tecla para continuar..." << std::endl;
  std::cin >> continuar;
}


//--------------------------------------------------------------------
//DEFINE AS A AÇÃO DA RODADA
//--------------------------------------------------------------------
void gameAction(int r,int c, int **tabuleiro,int **tabuleiro_aux, time_t tempo_inicial){
  int acao;
  std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
  std::cout << "┃ (1) - Revelar uma casa ┃" << std::endl;
  std::cout << "┃ (2) - Marcar uma casa  ┃" << std::endl;
  std::cout << "┃ (3) - Tempo de partida ┃" << std::endl;
  std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
  std::cout << std::endl << "Digite uma ação: ";
  std::cin >> acao;
  
  switch(acao){
    case 1:
      showSquares(r, c, tabuleiro, tabuleiro_aux);
      
      break;
    case 2:
      markSquares(r, c, tabuleiro, tabuleiro_aux);
      break;
    case 3:
      showTime(tempo_inicial);
      break;
    default:
      showSquares(r, c, tabuleiro, tabuleiro_aux);
  }  
}


//--------------------------------------------------------------------
//DEFINE AS LINHAS/COLUNAS/MINAS DE ACORDO COM A DIFICULDADE
//--------------------------------------------------------------------
void switch_dif(char dif, int &row, int &col, int &minas){
  switch(dif){
    case 'b':
      row = 10;
      col = 10;
      minas = 10;
      break;
    case 'i':
      row = 15;
      col = 15;
      minas = 40;
      break;
    case 'a':
      row = 15;
      col = 30;
      minas = 100;
      break;
    default:
      row = 10;
      col = 10;
      minas = 10;
  }
}


//--------------------------------------------------------------------
//IMPRIME NA TELA O TABULEIRO AUXILIAR
//--------------------------------------------------------------------
void PrintAuxBoard(int row, int col, int **tabuleiro, int **tabuleiro_aux){
  const int ASCII = 65;
  std::cout << "     ";
  for(int i=0;i<col;i++){
    if(ASCII+i<=90){
     std::cout << static_cast<char>(ASCII+i) << " "; 
    } else {
     std::cout << static_cast<char>(ASCII+i-42) << " "; 
    }
  }
  std::cout << std::endl << "   ┏━";
  for(int i=0;i<col;i++){
   std::cout << "━━"; 
  }
  std::cout<<"┓" << std::endl;
  
  for(int i=0; i<row;i++){
    for(int j=0; j<col;j++){
      if(j==0){
        if(i+1<10){
          std::cout << " " << i+1 <<" ┃ ";
        }else {
          std::cout << i+1 <<" ┃ ";
        }
      }
      if(tabuleiro_aux[i][j]==0){
        std::cout << "  ";
      } else if(tabuleiro_aux[i][j]==-1){
        std::cout << "⨂ ";
      } else {
        std::cout << tabuleiro_aux[i][j] << " ";
      }

      if(j==col-1){
        std::cout << "┃" << std::endl;
      }
    }
  }

  std::cout << "   ┗━";
  for(int i=0;i<col;i++){
   std::cout << "━━"; 
  }
  std::cout<<"┛" << std::endl;
  std::cout<< std::endl;

}


//--------------------------------------------------------------------
//IMPRIME NA TELA O TABULEIRO PRINCIPAL
//--------------------------------------------------------------------
void PrintBoard(int row, int col, int **tabuleiro, int **tabuleiro_aux){
  const int ASCII = 65;
  std::cout << std::endl << "     ";
  for(int i=0;i<col;i++){
    if(ASCII+i<=90){
     std::cout << static_cast<char>(ASCII+i) << " "; 
    } else {
     std::cout << static_cast<char>(ASCII+i-42) << " "; 
    }
  }
  std::cout << std::endl << "   ┏━";
  for(int i=0;i<col;i++){
   std::cout << "━━"; 
  }
  std::cout<<"┓" << std::endl;
  for(int i=0; i<row;i++){
    for(int j=0; j<col;j++){
      if(j==0){
        if(i+1<10){
          std::cout << " " << i+1 <<" ┃ ";
        }else {
          std::cout << i+1 <<" ┃ ";
        }
      }
      if(tabuleiro[i][j]==0){
        std::cout << "■ ";
      }else if(tabuleiro[i][j]==-2){
        std::cout << "✜ ";
      } else {
        if(tabuleiro_aux[i][j]==0){
          std::cout << "  ";
        } else if(tabuleiro_aux[i][j]==-1){
          std::cout << "⨂ ";
        } else {
          std::cout << tabuleiro_aux[i][j] << " ";
        }
      }

      if(j==col-1){
        std::cout << "┃" << std::endl;
      }  
    }
  }

  std::cout << "   ┗━";
  for(int i=0;i<col;i++){
   std::cout << "━━"; 
  }
  std::cout<<"┛" << std::endl;
  std::cout<< std::endl;
}



//--------------------------------------------------------------------
//INSERE OS VALORES NO TABULEIRO
//--------------------------------------------------------------------
void CreateBoard(int row, int col, int minas, int **tabuleiro, int **tabuleiro_aux){
  
  // GERAR TABULEIRO
  for(int i=0; i<row;i++){
      for(int j=0; j<col;j++){
        tabuleiro[i][j] = 0;
        tabuleiro_aux[i][j] = 0;
      }
  }

  // GERAR MINAS
  for(int i=0;i<minas;i++){
    int xMina;
    int yMina;
    srand (time(NULL));
    do {
      xMina = rand()%row;
      yMina = rand()%col;
    } while(tabuleiro_aux[xMina][yMina] != 0);
    tabuleiro_aux[xMina][yMina] = -1;
  }

  // GERAR NÚMEROS
  int quantMinas;
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      if(tabuleiro_aux[i][j] == 0){
        
        quantMinas=0;
        for(int mRow=i-1;mRow<=i+1;mRow++){
          for(int mCol=j-1;mCol<=j+1;mCol++){
            
            if((mRow >= 0 && mRow <= row-1) && (mCol >= 0 && mCol <= col-1)){
              if(tabuleiro_aux[mRow][mCol] == -1){
                quantMinas++;
              }
            }
            
          }
        }
        tabuleiro_aux[i][j] = quantMinas;    
      }
    }
  }
  
}

void ordenarTabela(Record *record){
  std::string aux_nome;
  int aux_tempo;
  for(int i=1;i<10;i++){
    for(int j=0;j<9;j++){
      if(record[j].tempo > record[j+1].tempo || record[j].tempo == 0){

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

//--------------------------------------------------------------------
//FUNÇÃO PRINCIPAL
//--------------------------------------------------------------------
void startGame(int dif){
  int row,col;
  int minas;
  
  switch_dif(dif, row, col, minas);

  //tabuleiro principal
  int **tabuleiro = (int **) malloc(row*sizeof(int*));
  for(int i=0;i<row;i++){
    tabuleiro[i] = (int *) malloc(col*sizeof(int));
  }

  //tabuleiro auxiliar
  int **tabuleiro_aux = (int **) malloc(row*sizeof(int*));
  for(int i=0;i<row;i++){
    tabuleiro_aux[i] = (int *) malloc(col*sizeof(int));
  }

  //Insere os valores no tabuleiro
  CreateBoard(row, col, minas, tabuleiro, tabuleiro_aux);

  //variáveis para marcar o tempo de partida
  bool vitoria=false;
  time_t tempo_inicial, tempo_final;

  //marca o tempo inicial
  time(&tempo_inicial);
  tm *tempo_inicial_info=localtime(&tempo_inicial);
  tempo_inicial=mktime(tempo_inicial_info);

  //Loop do jogo
  while(game_control==true){
    //
    system("clear");
    //PrintAuxBoard(row, col, tabuleiro, tabuleiro_aux);
    
    PrintBoard(row, col, tabuleiro, tabuleiro_aux);
    
    gameAction(row, col, tabuleiro, tabuleiro_aux, tempo_inicial);

    vitoria = endGame(row, col, minas, tabuleiro, tabuleiro_aux);
    
    if(vitoria == true){
      game_control=false;
    }
  }
  
  //marca o tempo final
  time(&tempo_final);
  tm *tempo_final_info=localtime(&tempo_final);
  tempo_final=mktime(tempo_final_info);

  //variável com o tempo de partida
  double tempo_de_jogo=difftime(tempo_final, tempo_inicial);

  system("clear");

  //Verifica se o jogador venceu
  if(vitoria == true){
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "┃      VOCÊ GANHOU       ┃" << std::endl;
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl << std::endl;
    PrintBoard(row, col, tabuleiro, tabuleiro_aux);

    std::cout << "\nTempo: " << timeToString(tempo_de_jogo) << std::endl;
    std::fstream file;
    std::string file_string;
    std::string diretorio;
    
    switch(dif){
      case 'b':
        diretorio = "records/b.txt";
        break;
      case 'i':
        diretorio = "records/i.txt";
        break;
      case 'a':
        diretorio = "records/a.txt";
        break;
    }
    file.open(diretorio, std::ios::in);
    
    int r_indice=0;
    int r_quant=0;
    Record record[10];
    
    if(file.is_open()){

      for(int i=0;i<10;i++){
        record[i].nome = "-";
        record[i].tempo = 0;
      }
      
      while(getline(file,file_string)){

          if(r_indice==0){
            record[r_quant].nome = file_string;
            r_indice++;
          } else {
            record[r_quant].tempo = std::stoi(file_string);
            r_indice=0;
            r_quant++;
          }
      }
    }
    file.close();
    
    //ORDENAR RECORDS
    ordenarTabela(record);
    
    if(r_quant<=10 && (tempo_de_jogo < record[9].tempo || record[9].tempo == 0)){
      std::string nome;
      std::cout << std::endl << "Você está entre os 10 jogadores com o melhor tempo.\n\n Digite o seu nome para entrar nos records: " << std::endl;
      std::cin >> nome;

      record[9].nome = nome;
      record[9].tempo = tempo_de_jogo;
      
      //ORDENAR RECORDS
      ordenarTabela(record);
    }

    remove("records/");
    file.open(diretorio, std::ios::out);
    for(int i=0;i<10;i++){
      file << record[i].nome << "\n";
      file << record[i].tempo << "\n";
    }
    
    file.close();
    
  } else {
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
    std::cout << "┃      FIM DE JOGO       ┃" << std::endl;
    std::cout << "┃      VOCÊ PERDEU       ┃" << std::endl;
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl << std::endl;
    PrintAuxBoard(row, col, tabuleiro, tabuleiro_aux);
    std::cout << "\nTempo: " << timeToString(tempo_de_jogo) << std::endl;
  }

  
  //desalocar a memória do tabuleiro
  for(int i=0;i<row;i++){
    free(tabuleiro[i]);
    free(tabuleiro_aux[i]);
  }
  free(tabuleiro);
  free(tabuleiro_aux);
  
}
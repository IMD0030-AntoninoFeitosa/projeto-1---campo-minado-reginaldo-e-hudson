#include "jogo.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

void mostrar_records() {
  std::fstream arquivo;
  char d;
  std::string diretorio;
  arquivo.open("config/dificuldade.txt", std::ios::in);
  
  if(arquivo.is_open()){      
    arquivo.get(d);
  }

  switch(d){
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
  arquivo.close();

  arquivo.open(diretorio, std::ios::in);
  int r_indice=0;
  int r_quant=0;
  Record record[10];
  std::string file_string;
  
  if(arquivo.is_open()){

    for(int i=0;i<10;i++){
      record[i].nome = "-";
      record[i].tempo = 0;
    }
    
    while(getline(arquivo,file_string)){

        if(r_indice==0){ //armazena o nome do jogador
          record[r_quant].nome = file_string;
          r_indice++;
        } else { //armazena o tempo do jogador
          record[r_quant].tempo = std::stoi(file_string);
          r_indice=0;
          r_quant++;
        }
    }
  }
  arquivo.close();

   std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
   std::cout << "┃         RANKING         ┃\n";
   std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n";
  int posicao=1;
  for(int i=0;i<10;i++){
    if(record[i].tempo != 0){
    std::cout << posicao << "º: " << record[i].nome << " - " << record[i].tempo << std::endl;
      posicao++;
    }
  }
  
}

void mostrar_regras(void) {
  std::cout << std::endl << std::endl;
  std::cout << "Option:" << std::endl;
  std::cout << " -h or --help                  Mostra todos os comandos."
            << std::endl;
  std::cout << " -r or --records               Mostra uma lista com os records."
            << std::endl;
  std::cout << " -d or --difficulty <option>   Modifica a dificuldade do jogo "
               "para <option>"
            << std::endl;
  std::cout << "                               -b or --beginner" << std::endl;
  std::cout << "                               -i or --intermediary"
            << std::endl;
  std::cout << "                               -a or --advanced" << std::endl;
}

int main(int argc, char *argv[]) {

  std::fstream arquivo;

  // Se o programa tive mais de um argumento
  if (argc > 1) {

    std::string arg = argv[1];

    // mostra o quadro com os comandos
    if (arg == "-h" || arg == "--help") {
      mostrar_regras();

      // Mostra os records
    } else if (arg == "-r" || arg == "--records") {
      mostrar_records();

      // Leitura da dificuldade do jogo
    } else if (arg == "-d" || arg == "--difficulty") {

      // abre o arquivo para escrita
      arquivo.open("config/dificuldade.txt", std::ios::out);

      if (argc > 2) {

        std::string newlevel = argv[2];

        if (newlevel == "-b" || newlevel == "--beginner") {
          arquivo << 'b';
          std::cout << "Dificuldade modificada para iniciante!\n";

        } else if (newlevel == "-i" || newlevel == "--intermediary") {
          arquivo << 'i';
          std::cout << "Dificuldade modificada para intermediário!\n";

        } else if (newlevel == "-a" || newlevel == "--advanced") {
          arquivo << 'a';
          std::cout << "Dificuldade modificada para avançado!\n";

        } else {
          std::cout << "Dificuldade desconhecida" << newlevel << std::endl;
          mostrar_records();
        }
      }

      arquivo.close();

    } else {
      std::cout << "Unknown argument: " << argv[1] << std::endl;
      mostrar_regras();
    }

  } else {
    // abre o arquivo para leitura
    arquivo.open("config/difficulty.txt", std::ios::in);

    // dificuldade padrão = "beginner"
    char dif = 'b';

    // Armazena a dificuldade na variável dif
    if (arquivo.is_open()) {
      arquivo.get(dif);
    } else {
      std::cout << "NAO FOI POSSÍVEL ABRIR O PROGRAMA" << std::endl;
    }

    arquivo.close();

    mudarDificuldade(dif);
    inicializarJogo();
    std::cout << "CAMPO MINADO" << std::endl;
    std::cout << std::endl;
    jogoPrincipal();
  }

  return 0;
}
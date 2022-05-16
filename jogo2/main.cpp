#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "game_engine.h"

void show_usage(void){
  std::cout << "Usage: game [option]" << std::endl;
  std::cout << "Option:" << std::endl;
  std::cout << " -h or --help                  Mostra todos os comandos." << std::endl;
  std::cout << " -r or --records               Mostra uma lista com os records." << std::endl;
  std::cout << " -d or --difficulty <option>   Modifica a dificuldade do jogo para <option>" << std::endl;
  std::cout << "                               -b or --beginner" << std::endl;
  std::cout << "                               -i or --intermediary" << std::endl;
  std::cout << "                               -a or --advanced" << std::endl;
}

void showRecords(){
  std::fstream d_file;
  char d;
  std::string diretorio;
  d_file.open("config/difficulty.txt", std::ios::in);
  
  if(d_file.is_open()){      
    d_file.get(d);
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
  d_file.close();

  d_file.open(diretorio, std::ios::in);
  int r_indice=0;
  int r_quant=0;
  Record record[10];
  std::string file_string;
  
  if(d_file.is_open()){

    for(int i=0;i<10;i++){
      record[i].nome = "-";
      record[i].tempo = 0;
    }
    
    while(getline(d_file,file_string)){

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
  d_file.close();

  std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
  std::cout << "┃         RANKING         ┃" << std::endl;
  std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl << std::endl;
  for(int i=0;i<10;i++){
    std::cout << i+1 << "º: " << record[i].nome << " - " << timeToString(record[i].tempo) << std::endl;
  }
  
}

int main(int argc, char ** argv){
  setlocale(LC_ALL,"portuguese");
  system("clear");

  std::fstream d_file;
  if(argc > 1){
    std::string arg = argv[1];
    if(arg == "-h" || arg == "--help"){
      show_usage();
    }else if(arg == "-r" || arg == "--records"){
      showRecords();
    }else if(arg == "-d" || arg == "--difficulty"){
      
      d_file.open("config/difficulty.txt", std::ios::out);
      
      if(argc > 2){
        std::string newlevel = argv[2];
        if(newlevel == "-b" || newlevel == "--beginner"){
          d_file << 'b';
          std::cout << "Dificuldade modificada para iniciante!\n";
        } else if(newlevel == "-i" || newlevel == "--intermediary"){
          d_file << 'i';
          std::cout << "Dificuldade modificada para intermediário!\n";
          //store_difficulty(CONFIG_FILE, Difficulty::intermediary);
        } else if(newlevel == "-a" || newlevel == "--advanced"){
          d_file << 'a';
          std::cout << "Dificuldade modificada para avançado!\n";
        } else {
          std::cout << "Dificuldade desconhecida" << newlevel << std::endl;
          show_usage();
        }
      }
      
      d_file.close();
      
    } else {
      std::cout << "Unknown argument: " << argv[1] << std::endl;
      show_usage();
    }
  } else {
    d_file.open("config/difficulty.txt", std::ios::in);
    char dif='b';
    if(d_file.is_open()){
      d_file.get(dif);
    }else {
      std::cout << "NAO FOI POSSÍVEL ABRIR O PROGRAMA" << std::endl;
    }
    d_file.close();    
    startGame(dif);
  }
  
  return 0;
}
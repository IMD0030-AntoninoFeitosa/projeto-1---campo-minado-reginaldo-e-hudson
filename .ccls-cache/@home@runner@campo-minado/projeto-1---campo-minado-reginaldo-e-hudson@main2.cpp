#include <iostream>

using namespace std;

void gerar_numeros(int L, int C, char *tabuleiro_aux)
{
    int qtd_bombas = 0;
    for(int i = 0; i < L + 2; i++)
    {
        for(int j = 0; j < C + 2; j++)
        {
          if(*tabuleiro_aux == '*')
          {
              
          
          
          
            }
                
        }
    }

}

void campo_bombas(int L, int C, int B)
{
    int contB = 0, i, j, linha = L, coluna = C;
    char tabuleiro[L][C];
    char tabuleiro_aux[L+2][C+2];
  //Gerando o tabuleiro principal
    for(int i = 0; i < L; i++)
    {
        for(int j = 0; j < C; j++)
        {
            tabuleiro[i][j] = 'X';
        }
    }
  //Gerando o tabuleiro auxiliar com 1 linha e 1 coluna a mais para facilitar a leitura das bombas e geração dos números
     for(int i = 0; i < L + 2; i++)
    {
        for(int j = 0; j < C + 2; j++)
        {
            tabuleiro_aux[i][j] = '0';
        }
    }

    for(contB = 0; contB < B; contB++)
    {
        do
        {
            i = rand()%L;
            j = rand()%C;
              if(i == 0){
                i = i + 1;
              }  
              if(j == 0){
                j = j + 1;
              }    
          }while(tabuleiro_aux[i][j] == '*');
        tabuleiro_aux[i][j] = '*';
    }
  //Imprimindo tabuleiro principal
       for(int i = 0; i < L; i++)
    {
        cout << endl;
        for(int j = 0; j < C; j++)
        {
            cout << tabuleiro[i][j] << ' ';
        }
    }
  //Imprimindo tabuleiro auxiliar
     for(int i = 0; i < L + 2; i++)
    {
        cout << endl;
        for(int j = 0; j < C + 2; j++)
        {
            cout << tabuleiro_aux[i][j] << ' ';
        }
    }
    gerar_numeros(linha, coluna, *tabuleiro_aux);
}

int main()
{
    char nome[50];
    int dif;
    int L, C, B;

    srand(time(NULL)); //continuar rodando a tela

    cout << "Nome do Jogador: ";
    cin >> nome;
    cout << "Nível de jogo - (1) Fácil - (2) Intermediário - (3) Difícil ";
    cin >> dif;

    switch(dif)
    {
    case 1:
        L = 10;
        C = 10;
        B = 10;
        campo_bombas(L, C, B);
        break;
     case 2:
        L = 15;
        C = 15;
        B = 40;
        campo_bombas(L, C, B);
        break;
    case 3:
        L = 15;
        C = 30;
        B = 100;
        campo_bombas(L, C, B);
        break;
    }
  return 0;
}

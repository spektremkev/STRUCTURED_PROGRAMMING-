/*Faça um programa, utilizando o Dev-C++, para armazenar os dados de um aluno(a), contendo os seguintes dados:
		matricula: inteiro
		nome: caractere
		sexo: caractere
		idade: inteiro
		av1, av2, av3 e media: real	(UTILIZE UMA MATRIZ PARA ARMAZENAR AS NOTAS)

O usuário poderá armazenar no máximo 50 alunosO usuário poderá armazenar no máximo 50 alunos. O programa terá a opção de adicionar, exibir ou salvar/carregar os dados. O programa deverá ter as seguintes condições. O programa terá a opção de adicionar, exibir ou salvar/carregar os dados. O programa deverá ter as seguintes condições:
    • Adicionar:
        ◦ Efetuar uma pesquisa para saber se o aluno(a) existe ou não no vetor através da matrícula do mesmo
            ▪ Se existir, informar que o aluno(a) já se encontra presente e não adicione
            ▪ Caso não exista, verifique se o sistema está ou não lotado antes de inserir
        ◦ Ao armazenar as notas utilize o mesmo critério de avaliação da UniCarioca para calcular a média, está não deve ser informada pelo aluno (Soma das 2 maiores notas divididos pela quantidade)
    • Exibir: 
        ◦ O usuário poderá exibir os alunos(as) com os seguintes critérios de média:
            ▪ Alunos reprovados com média inferior a 5
            ▪ Alunos reprovados com média inferior a 7
            ▪ Alunos reprovados
            ▪ Alunos aprovados com média superior ou igual a 7
            ▪ Alunos aprovados com média superior ou igual a 9
            ▪ Alunos aprovados
            ▪ Todos os alunos
    • Salvar/Carregar:
        ◦ O usuário irá escolher entre salvar ou carregar um arquivo externo
            ▪ Colocar um campo para o usuário informar o nome do arquivo externo, tanto na opção de salvar quanto carregar
            ▪ Ao selecionar a opção de carregar dados, o sistema deve ler todas as informações do arquivo externo e adicionar no programa#include <stdio.h>
*/

#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include<iostream>

using namespace std;

#define max 50
#define sex 10
#define Aux 2

typedef struct Pessoa
{
    char nome[max];
    int idade;
    char matricula[10];
	char sexo;
	float notas[2][2];

}Pessoa;

// Varivaies globais

FILE *arq, *arq2, *arquivoExiste;
Pessoa aluno;
char file[20]="bancoinicial.bin";

// prototipos das funcoes

int verificar_cheio();
int verifica_matricula(char matricula[]);
void menu_aprovados();
void menu_reprovados();

char menu()
{
	arq = fopen(file,"a+b");
	fclose(arq);
    system("cls");
    cout << "BANCO DE ALUNO..:"<< endl;
    cout << endl;
    cout << "[1] - Adicionar..............:"<< endl;
    cout << "[2] - Pesquisar..............:"<< endl;
    cout << "[3] - Exibir.................:"<< endl;
    cout << "[4] - Salvar/Carregar........:"<< endl;
    cout << "[0] - Sair...................:"<< endl;
    cout << endl;
    cout << "Opcao........................: "<< endl << endl;
    return (toupper(getche()));
}

// Adicionar aluno

void adicionar_aluno()
{
	if( verificar_cheio() >= 50)
	{
		cout << "NÃO PODE MAIS CADASTRAR"<< endl;
		return;
	}
	else
	{
		
	float arrayAux[Aux], media;
    char nome[max], matricula[10];
    
    arq = fopen(file,"a+b");
        if (arq == NULL)
        {
            cout << "ERRO NO ARQUIVO"<< endl;
            return;
        }
 	system("cls");
    cout << "******************************"<< endl;
 	cout << "*******BANCO DE DADOS*********" << endl;
    cout << "*****ADICIONAR USUARIO********"<< endl;
    cout << "**Digite a matricula do aluno:*"<< endl << endl;
    cout << "*******************************"<< endl;

	fflush(stdin);
    gets(matricula);
    
    if (verifica_matricula(matricula) == 1)
    {
        cout << "*******************************"<< endl;
        cout << "******Matricula ja existe******"<< endl;
        cout << "*******************************"<< endl;

    }
	else
    {
    	strcpy(aluno.matricula,matricula);
		cout << "Digite o nome: " << endl;
        scanf("%s", &aluno.nome);
      
        cout << "Digite a idade do aluno: "<< endl;
        scanf("%d", &aluno.idade);
        
        cout << "Digite o sexo do aluno: "<< endl;
        scanf(" %c", &aluno.sexo);
        
        cout << "Digite a nota da av1: "<< endl;
        scanf("%f", &arrayAux[0]);
        
        cout << "Digite a nota da av2: " << endl;
        scanf("%f", &arrayAux[1]);
        
        cout << "Digite a nota da av3: " << endl;
        scanf("%f", &arrayAux[2]);
        
        
        	if (arrayAux[0]>arrayAux[1])
			{
			if (arrayAux[1]>arrayAux[2])
			{
				media = (arrayAux[0]+arrayAux[1]) /3;
			}
			else
			{
				media = (arrayAux[0]+arrayAux[2]) /3;
			}
			
		}
	   	else if (arrayAux[1]>arrayAux[2])
		   {
                if (arrayAux[2]>arrayAux[0])
                {
                    media = (arrayAux[1]+arrayAux[2])/3;
                }
                else
                {
                    media = (arrayAux[1]+arrayAux[0])/3;
                }
	        }
    
			else 
			{
				if (arrayAux[0]>arrayAux[1])
				{
					media = (arrayAux[2]+arrayAux[0])/2;
				}
                else
                {
                    media = (arrayAux[2]+arrayAux[1])/2;
                }
	        }
   		
			    aluno.notas[0][0] = arrayAux[0];
			    aluno.notas[0][1] = arrayAux[1];
			    aluno.notas[1][0] = arrayAux[2];
			    aluno.notas[1][1] = media;

       
        fwrite(&aluno,sizeof(aluno),1,arq);
    }
	}
    fclose(arq);

}

//verificar se esta cheio

int verificar_cheio()
{
    int cont = 0;
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;
        return 0;
    }
    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
        cont++;     
        fread(&aluno,sizeof(Pessoa),1,arq);
    }   
    fclose(arq);
    return cont;
    
}

// verificar matricula
int verifica_matricula(char matricula[])
{
	
    fread(&aluno,sizeof(Pessoa),1,arq);
        while(!feof(arq))
        {
            if  (strcmp(aluno.matricula,matricula) == 0)
            {
                fseek(arq,-sizeof(Pessoa),SEEK_CUR);
                return 1;
            }
            fread(&aluno,sizeof(Pessoa),1,arq);
        }
    return 0;
    
}


// Pesquisar Aluno
void pesquisar_aluno()
{
    char matricula[10];

    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;

        return;
    }
	system("cls");
    cout << "**************************"<< endl;
    cout << "*****BANCO DE DADOS*******"<< endl;
    cout << "***PESQUISAR USUARIO******"<< endl;
    cout << "*Matricula para pesquisa:*"<< endl;
    cout << "**************************"<< endl;
    scanf("%s", &matricula);

    if (verifica_matricula(matricula) == 1)
    {
        fread(&aluno,sizeof(Pessoa),1,arq);
        cout << endl;
        cout << "-"<< endl;
        cout << " Nome...............:" << endl;
        cout << aluno.nome << endl;
        cout << endl<< endl;
        
        cout << "Matricula...........:"<< endl;
        cout << aluno.matricula << endl;
        cout <<  endl<< endl;
        
        cout << "Sexo................:"<< endl;
        cout << aluno.sexo << endl;
        cout <<  endl << endl;
        
        cout << "Idade...............:" << endl;
        cout <<  aluno.idade << endl;
        cout << endl << endl;
        
        cout << "Av1.................:" << endl;
        cout <<  aluno.notas[0][0] << endl;
        cout << endl << endl;
        
        cout << "Av2................:"<< endl;
        cout <<  aluno.notas[0][1] << endl;
        cout << endl << endl;
        
        cout << "Av3................:" << endl;
        cout <<  aluno.notas[1][0] << endl;
        cout << endl<< endl;
        
        cout << "Media Final.........:"<< endl;
        cout <<  aluno.notas[1][1] << endl;
        cout << endl << endl;
    }

    else
    {
        
        cout << "**************************"<< endl;
        cout << "****Aluno nao existe******"<< endl;
        cout << "**************************"<< endl;
    }

    fclose(arq);
}

void mostrar_todos()
{
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;

        return;
    }

    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
        cout << "NOME.....:" << aluno.nome << "NOTA.....:" << aluno.notas[1][1] << "MATRICOLA.....:" << aluno.matricula << endl;
        fread(&aluno,sizeof(Pessoa),1,arq);
    }
 

    fclose(arq);
}

void aprovadosMaiorIgual7()
{
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;
        return;
    }

    system("cls");
 	cout << "BANCO DE DADOS"<< endl;
    cout << "Aprovados com media maior ou igual a 7 "<< endl;
   
    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
    	if(aluno.notas[1][1]>=7)
		{
           
            cout << "**************************"<< endl;
    		cout << "NOME........:"<< aluno.nome<<"*"<< endl;
            cout <<"MEDIA FINAL:....."<< aluno.notas[1][1]<<"*"<< endl;
            cout << "**************************"<< endl;
		} 
		fread(&aluno,sizeof(Pessoa),1,arq);
    }
   

    fclose(arq);
}

void aprovadosMaiorIgual9()
{
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;
        return;
    }

    system("cls");
    
    cout << "*****************************************"<< endl;
 	cout << "************BANCO DE DADOS***************"<< endl;
    cout << "**Aprovados com media maior ou igual a 9**"<< endl;
    cout << "******************************************"<< endl;
    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
    	if(aluno.notas[1][1]>=9)
		{
    		cout << "**************************"<< endl;
    		cout << "NOME........:"<< aluno.nome<<"*"<< endl;
            cout <<"MEDIA FINAL:....."<< aluno.notas[1][1]<<"*"<< endl;
            cout << "**************************"<< endl;
		} 
		fread(&aluno,sizeof(Pessoa),1,arq);
    }
    

    fclose(arq);
}

void reprovadosAbaixo7()
{
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;
        return;
    }

    system("cls");
 	cout << "BANCO DE DADOS"<< endl;
    cout << "Reprovados com media abaixo de 7 "<< endl;
    

    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
    	if( aluno.notas[1][1] <7 )
		{
    		cout << "**************************"<< endl;
    		cout << "NOME........:"<< aluno.nome<<"*"<< endl;
            cout << "MEDIA FINAL:....."<< aluno.notas[1][1]<<"*"<< endl;
            cout << "**************************"<< endl;
		} 
		fread(&aluno,sizeof(Pessoa),1,arq);
    }
    

    fclose(arq);
}

void reprovadosAbaixo5()
{
    arq = fopen(file,"r+b");
    if (arq == NULL)
    {
        cout << "**************************"<< endl;
        cout << "******Erro no arquivo*****"<< endl;
        cout << "**************************"<< endl;   
        return;
    }

    system("cls");
    cout << "***********************************"<< endl;
 	cout << "**********BANCO DE DADOS***********"<< endl;
    cout << "**Reprovados com media abaixo de 5**"<< endl;
    cout << "************************************"<< endl;
   
    fread(&aluno,sizeof(Pessoa),1,arq);
    while (!feof(arq))
    {
    	if(aluno.notas[1][1]<5)
        {
    		cout << "**************************"<< endl;
    		cout << "NOME........:"<< aluno.nome<<"*"<< endl;
            cout <<"MEDIA FINAL:....."<< aluno.notas[1][1]<<"*"<< endl;
            cout << "**************************"<< endl;
		} 
		fread(&aluno,sizeof(Pessoa),1,arq);
    }
    

    fclose(arq);
}


char menu_exibir()
{
	char opcao;
	system("cls");
	cout << "BANCO DE DADOS"<< endl;
	cout << "EXIBIR USUARIOS............:"<< endl;
    cout << endl;
	cout << "[1] - Aprovados............:"<< endl;
    cout << "[2] - Reprovados...........:"<< endl;
    cout << "[3] - Todos................:"<< endl;
    cout << "[0] - Voltar...............:"<< endl;
    cout << "Opcao......................:"<< endl;
    scanf("%c", &opcao);
     
    switch(opcao) 
    {
    case '1':
        menu_aprovados();
        break;

    case '2' :
        menu_reprovados();
        break;

    case '3' :
        mostrar_todos();
        break;

     case '0' :
        menu();
        break;

    default:
    	cout << "Opcao invalida" << endl;
    	menu_exibir();
    }

};

// menu aprovados
void menu_aprovados()
{
	char opcao;
	system("cls");
	cout << "BANCO DE ALUNOS...............:" << endl;
	cout << "EXIBIR APROVADOS..............:" << endl;
    cout << endl;
	cout << "[1] - Media >=7...............:" << endl;
    cout << "[2] - Media >=9...............:" << endl;
    cout << "[0] - Voltar..................:" << endl;
    cout << "Opcao.........................:" << endl;
    scanf("%c", &opcao);
    
    switch(opcao) 
    {
    case '1':
        aprovadosMaiorIgual7();
        break;
    case '2' :
        aprovadosMaiorIgual9();
        break;
    case '0' :
        menu_exibir();
        break;  
    default:
    	cout << "Opcao invalida...........:"<< endl;
    	menu_aprovados();
    }
    
};

// menu reprovados
void menu_reprovados()
{
	char opcao;
	system("cls");
	cout << "BANCO DE DADOS..:"<< endl;
	cout << "EXIBIR REPROVADOS............:"<< endl;
    cout << endl;
	cout << "[1] - Media menor 7..........:"<< endl;
    cout << "[2] - Media menor 5..........:"<< endl;
    cout << "[0] - Voltar.................:"<< endl;
    cout << "Opcao........................:"<< endl;
    scanf("%c", &opcao);
    
     switch(opcao) 
	{
    case '1':
        reprovadosAbaixo7();
        break;

    case '2' :
        reprovadosAbaixo5();
        break;

    case '0' :
        menu_exibir();
        break;  

    default:
    cout << "Opcao invalida...............:"<< endl;
    	menu_reprovados();
	}
}

void menu_salvar_carregar()
{
	char opcao;
	system("cls");
	cout << "Banco atual..................: "<< "[" <<file <<"]" << endl;
	cout << "BANCO DE DADOS..:"<< endl;
	cout << "SALVAR/CARREGAR ARQUIVO......:"<< endl;
    cout << endl;
	cout << "[1] - Salvar.................:"<< endl;
    cout << "[2] - Carregar...............:"<< endl;
    cout << "[0] - Voltar.................:"<< endl;
    cout << "Opcao........................:"<< endl;
    scanf("%c", &opcao);
    
    switch(opcao) 
	{
    case '1':
    	system("cls");
		cout << "GOSTARIA DE SALVAR BANCO"<< endl;     
        char novobanco[100], c; 

    // Arbir arquivo de leitura
    arq = fopen(file, "r"); 
    if (arq == NULL) 
    { 
        cout << "Arquivo nao pode ser aberto"<< "[" << file << "]" << endl; 
        exit(0); 
    } 
  
  	cout << "Insira o nome do novo banco(Ex: novobanco): "<< endl; 
    scanf("%s", novobanco);   
    strcat(novobanco, ".bin");
 
    // Abrir outro arquivo para escrita
    arq2 = fopen(novobanco, "w"); 
    if (arq2 == NULL) 
    { 
        cout << "Arquivo nao pode ser aberto" << "["<<arq2 <<"]" << endl; 
        exit(0); 
    } 
  
    // Ler conteudo do arquivo
    c = fgetc(arq); 
    while (c != EOF) 
    { 
        fputc(c, arq2); 
        c = fgetc(arq); 
    } 
  
    cout << "Banco exportado com sucesso para" << "["<< novobanco << "]" << endl; 
    fclose(arq); 
    fclose(arq2);  	
    
        break;

    case '2' :
    	system("cls");
		cout << "CARREGAR ARQUIVO" << endl;

    	char nomeCarregar[20];
        cout << "Digite o nome do banco para carregar (incluir .bin no final do nome):" << endl;
        scanf("%s", &nomeCarregar);
        
		    arquivoExiste = fopen(nomeCarregar, "r"); 
		    if (arquivoExiste == NULL) 
		    { 
		        cout << "O arquivo" << "[" << nomeCarregar << "]" <<"nao existe!" << endl; 
		        return ;
		        menu_salvar_carregar();
		    }
			else
			{
		    	strcpy(file, nomeCarregar);
		    	cout << "Banco carregado " << endl;
		    	cout << "Banco Atual:" << file << endl;
		    	
			}
		fclose(arquivoExiste);
        break;

    case '0' :
        menu_exibir();
        break;  

    default:
    	cout << "Opcao invalida" << endl;
    	menu_salvar_carregar();
	}
}


int main()
{
    char op;

    do
    { 
        op = menu();

        switch(op)
        {
            case '1': adicionar_aluno(); break;
            case '2': pesquisar_aluno(); break;
            case '3': menu_exibir(); break;
            case '4': menu_salvar_carregar(); break;
        }

        cout << endl;
        system("PAUSE");

    }while (op != '0');

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define MAX 10
#define MOTA 50
#define PASSAGEIROS 100
#define MERCADORIAS 20
#define NOME 50
#define TELF 15
#define FILES 20
#define VEICULOS "veiculos.dat"
#define FIDELIZADOS "fidelizados.dat"

//Estrutura para guardar veiculos no parque
typedef struct veiculo{
	char matricula[MAX];
	int classe;
	time_t entrada;
}VEICULO;

//Estrutura para guardar veiculos fidelizados
typedef struct fidelizado{
    char nomeCliente[NOME];
    char telefone[TELF];      
    char matricula[MAX];
    int classe;
    time_t fimFidelizacao;
}FIDELIZADO;

//Estrutura para guardar os lugares livres no inicio do programa
typedef struct lugares{
    int mota;
    int passageiros;
    int mercadorias;
}LUGARES;


char menuP(void);
char menuB(void);
char menuD(void);
char escolherClasse(void);
int entradaVeiculo(char nomeF[], char nomeFidelizados[], int mota, int passageiros, int mercadorias);
int saidaVeiculo(char nomeF[], char nomeFidelizados[], int mota, int passageiros, int mercadorias);
void pesquisaVeiculo(char nomeF[]);
int validarMatricula(char matricula[]);
int validaRegisto(char matricula[], char nomeF[]);
void guardaFidelizado(char nomeFidelizados[], char nomeF[]);
void apagaFidelizacao(char nomeFidelizados[]);
void pesquisaFidelizacao(char nomeFidelizados[]);
float calcularValor(VEICULO veiculo, time_t saida);
void lugaresDisponiveis(int mota, int passageiros, int mercadorias);
void apagaFicheiro(char nomeF[]);
LUGARES contaVeiculos(char nomeF[]);
void verificaFidelizacao(char nomeFidelizados[]);
char* converterParaTempoLocal(time_t tempo);

int main(int argc, char *argv[]){
	
	char nomeF[FILES] = VEICULOS;
    char nomeFidelizados[FILES] = FIDELIZADOS;
	char mP, mB, mD, mClasse;
    int classe, mota, passageiros, mercadorias;
    LUGARES lugares;

    verificaFidelizacao(nomeFidelizados);
    lugares = contaVeiculos(nomeF);

    mota = lugares.mota;
    passageiros = lugares.passageiros;
    mercadorias = lugares.mercadorias;

	do{
        lugaresDisponiveis(mota, passageiros, mercadorias);
        //Menu principal
		mP = menuP();
		switch(mP){
			case 'A': //Entrada de veiculo
				system("cls");
				fflush(stdin);
				classe = entradaVeiculo(nomeF, nomeFidelizados, mota, passageiros, mercadorias);
                if(classe == 1){
                    mota--;
                }else if(classe == 2){
                    passageiros--;
                }else if(classe == 3){
                    mercadorias--;
                }
				system("cls");
			break;
			case 'B': //Saida de veiculo
				system("cls");
				fflush(stdin);
				classe = saidaVeiculo(nomeF, nomeFidelizados, mota, passageiros, mercadorias);
                if(classe == 1){
                    mota++;
                }else if(classe == 2){
                    passageiros++;
                }else if(classe == 3){
                    mercadorias++;
                }
				system("cls");
			break;
			case 'C': //Pesquisar um veiculo estacionado
				system("cls");
				fflush(stdin);
				pesquisaVeiculo(nomeF);
				system("cls");
			break;
			case 'D': //Menu de fidelizacao
				system("cls");
				fflush(stdin);
                do{
                    mD = menuD();
                    switch(mD){
                        case 'F': //Fidelizar um veiculo
                            system("cls");
                            fflush(stdin);
                            guardaFidelizado(nomeFidelizados, nomeF);
                            system("cls");
                        break;
                        case 'R': //Apaga um veiculo fidelizado
                            system("cls");
                            fflush(stdin);
                            apagaFidelizacao(nomeFidelizados);
                            system("cls");                          
                        break;
                        case 'C': //Consulta veiculos fidelizados
                            system("cls");
                            fflush(stdin);
                            pesquisaFidelizacao(nomeFidelizados);
                            system("cls");
                        break;
                        default: //Se diferente, voltar a pedir input
                            if(mD != 'S'){
                                system("cls");
                            }
                        break;
                    }
                //Sair para o menu principal
                }while(mD != 'S');
                system("cls");
			break;
			case 'E': //Menu para apagar base de dados
				system("cls");
                fflush(stdin);
                do{
                    mB = menuB();
                    switch(mB){
                        case 'V': //Eliminar base de dados de veiculos estacionados
                            apagaFicheiro(nomeF);
                            mota = MOTA;
                            passageiros = PASSAGEIROS;
                            mercadorias = MERCADORIAS;
                            system("cls");
                        break;
                        case 'F': //Eliminar base de dados de veiculos fidelizados
                            apagaFicheiro(nomeFidelizados);
                            system("cls");
                        break;
                        default: //Se diferente, voltar a pedir input
                            if(mB != 'S'){
                                system("cls");
                            }
                        break;
                    }
                //Sair para o menu principal
                }while(mB != 'S');
                system("cls");
			break;
            default: //Se diferente, voltar a pedir input
				if(mP != 'S'){
					system("cls");
				}
			break;
		}
    //Terminar programa
	}while(mP != 'S');
	return 0;
}

//Menu principal
char menuP(void){

	char opcaoP;
	printf("\n\n************ MENU ************\n\n");
	printf("A - Entrada de Veiculo\n");
	printf("B - Saida de Veiculo\n");
	printf("C - Pesquisa de Veiculo\n");
	printf("D - Clientes Fidelizados\n");
	printf("E - Limpar Base de Dados\n");
	printf("S - Sair\n\n");
    printf("Escolha uma opcao: ");
	opcaoP = toupper(getch());
	
	return(opcaoP);
}

//Menu para apagar base de dados
char menuB(void){

    char opcaoB;
    printf("\n\n*** ELIMINAR BASE DE DADOS ***\n\n");
    printf("Indique a base de dados que pretende elimiar:\n\n");
    printf("V - Veiculos Estacionados\n");
    printf("F - Veiculos Fidelizados\n");
    printf("S - Sair para o menu anterior\n\n");
    printf("Escolha uma opcao: ");
    opcaoB = toupper(getch());

    return(opcaoB);
}

//Menu Fidelizar
char menuD(void){

    char opcaoD;
    printf("\n\n****** MENU FIDELIZACAO ******\n\n");
    printf("F - Fidelizar Veiculo\n");
    printf("R - Remover Veiculo\n");
    printf("C - Pesquisar Veiculos Fidelizados\n");
    printf("S - Sair ao menu anterior\n\n");
    printf("Escolha uma opcao: ");
    opcaoD = toupper(getch());

    return(opcaoD);
}

char escolherClasse(void){

    char classe;
	printf("\nQual a classe do veiculo?\n\n");
	printf("1 - Mota\n");
	printf("2 - Ligeiro Passageiros\n");
	printf("3 - Ligeiro Mercadorias\n\n");
    printf("Introduza uma opcao: ");
    classe = getch();
    printf("%c", classe);

    return(classe);
}

//Entrada de Veiculo
int entradaVeiculo(char nomeF[], char nomeFidelizados[], int mota, int passageiros, int mercadorias) {
    
    FILE *f, *t;
    VEICULO veiculo;
    FIDELIZADO fidelizado;
    int classe = 0;
    char mClasse, matricula[MAX];

    f = fopen(nomeF, "ab");
    if (f == NULL) {
        printf("Erro na abertura do ficheiro!\n");
        getch();
        exit(1);
    }

    //Pedir matricula
    do {
        system("cls");
        printf("\n\n***** ENTRADA DE VEICULO *****\n\n");
        printf("Introduza a matricula do veiculo: ");
        scanf("%s", matricula);

        //Colocar input em maiusculas
        for(int i = 0; matricula[i] != '\0'; i++){
            matricula[i] = toupper(matricula[i]);
        }

        if(validarMatricula(matricula) == 0){
            //Verifica se a matricula fornecida esta dentro dos formatos aceites
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }else if(validaRegisto(matricula, nomeF)){//
            //Se matricula for de formato aceite, verifica se já esta registada no parque
            printf("\nEsta matricula ja esta registada!\n");
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
            fclose(f);
            getch();
            return 0;
        }
    }while(validarMatricula(matricula) == 0);

    strcpy(veiculo.matricula, matricula);
    veiculo.classe = 0;

    t = fopen(nomeFidelizados, "rb");
    if(t != NULL){
        while(fread(&fidelizado, sizeof(FIDELIZADO), 1, t) == 1){
            if(strcmp(veiculo.matricula, fidelizado.matricula) == 0){
                veiculo.classe = fidelizado.classe;
                printf("\nCliente fidelizado!\n\n");
                printf("Nome do Cliente: %s\n", fidelizado.nomeCliente);
                printf("Classe: %d", veiculo.classe);
                break;
            }
        }
        fclose(t);
    }
    
    if(veiculo.classe == 0){
        do{
            system("cls");
            printf("\n\n***** ENTRADA DE VEICULO *****\n\n");
            printf("Introduza a matricula do veiculo: %s\n\n", matricula);
            printf("Matricula valida!\n");

            mClasse = escolherClasse();
            switch(mClasse){
                case '1':
                    veiculo.classe = 1;
                    if(mota == 0){
                        printf("\nNao existem lugares disponiveis!\n");
                        printf("Pressione qualquer tecla para voltar ao menu anterior...");
                        fclose(f);
                        getch();
                        return 0;
                    }
                break;
                case '2':
                    veiculo.classe = 2;
                    if(passageiros == 0){
                        printf("\nNao existem lugares disponiveis!\n");
                        printf("Pressione qualquer tecla para voltar ao menu anterior...");
                        fclose(f);
                        getch();
                        return 0;
                    }
                break;
                case '3':
                    veiculo.classe = 3;
                    if(mercadorias == 0){
                        printf("\nNao existem lugares disponiveis!\n");
                        printf("Pressione qualquer tecla para voltar ao menu anterior...");
                        fclose(f);
                        getch();
                        return 0;
                    }
                break;
                default:
                    printf("\n\nEntrada invalida!\n");
                    printf("Pressione qualquer tecla para voltar a introduzir classe!");
                    getch();
                break;
            }
        }while(mClasse != '1' && mClasse != '2' && mClasse != '3');
    }

    veiculo.entrada = time(NULL);
    classe = veiculo.classe;

    fwrite(&veiculo, sizeof(VEICULO), 1, f);
    fclose(f);

    printf("\n\nEntrada Registada!\n");
    printf("Pressione qualquer tecla para voltar ao menu anterior...");
    getch();
    return classe;
}

//Saida de veiculo
int saidaVeiculo(char nomeF[], char nomeFidelizados[], int mota, int passageiros, int mercadorias){
    
	FILE *f, *t;
    VEICULO veiculo;
    time_t saida;
    char matricula[MAX], temp[FILES] = "temp.dat";
    int i, classe, encontrado = 0;
    float valor;

    printf("\n\n****** SAIDA DE VEICULO ******\n\n");

    f = fopen(nomeF, "rb");
    //Cria um ficheiro temporario para guardar os registos exceto o que se pretende eliminar
    t = fopen(temp, "wb");

    if(f == NULL || t == NULL){
        printf("Erro na abertura do ficheiro!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        fclose(t);
        getch();
        remove(temp);
        return 0;
    }

    do{
        system("cls");
        printf("\n\n****** SAIDA DE VEICULO ******\n\n");
        printf("Introduza a matricula do veiculo: ");
        scanf("%s", matricula);

        for(i = 0; matricula[i] != '\0'; i++){
            matricula[i] = toupper(matricula[i]);
        }

        if(validarMatricula(matricula) == 0){
            //Verifica se a matricula fornecida esta dentro dos formatos aceites
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }
    }while(validarMatricula(matricula) == 0);
    

    while(fread(&veiculo, sizeof(VEICULO), 1, f) == 1){
        if(strcmp(veiculo.matricula, matricula) == 0){
            classe = veiculo.classe;
            encontrado = 1;
            saida = time(NULL);
            valor = calcularValor(veiculo, saida); // Calculate and display parking fee
            printf("\nTempo estacionado: %ld minutos\n\n", (saida - veiculo.entrada) / 60); // Calculate and display parking duration in minutes
			fflush(stdin);
            if(validaRegisto(matricula, nomeFidelizados) == 1){
                valor = valor * 0.80;
                printf("Cliente fidelizado!\n");
                printf("Valor a pagar: %.2f euros\n", valor);
            }else{
                printf("Cliente nao fidelizado!\n");
                printf("Valor a pagar: %.2f euros\n", valor);
            }
            printf("\nRegisto removido com sucesso!\n");
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
            getch();
        }else{
            fwrite(&veiculo, sizeof(VEICULO), 1, t); //Guarda os registos exceto o que se pretende eliminar
        }
    }

    fclose(f);
    fclose(t);
    
    if(encontrado == 0){
        printf("\nVeiculo nao encontrado!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        remove(temp); //Apaga o ficheiro temporario
		fflush(stdin);
		getch();
        return 0;
    }
    
    remove(nomeF); //Apaga o ficheiro veiculos original
    rename(temp, nomeF); //Renomeia o ficheiro temporario para veiculos
    return classe;
}

//Consulta de uma matricula a indicar pelo utilizador
void pesquisaVeiculo(char nomeF[]){
    
    FILE *f;
    VEICULO veiculo;
    char matricula[MAX], *entrada;
	int i, encontrado = 0;

    printf("\n\n****** PESQUISAR VEICULO ******\n\n");

    f = fopen(nomeF, "rb");
    if(f == NULL){
        printf("Erro na abertura do ficheiro!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        getch();
        return;
    }

    do{
        system("cls");
        printf("\n\n****** PESQUISAR VEICULO ******\n\n");
	    printf("Introduza a matricula do veiculo a pesquisar: ");
	    scanf("%s", matricula);

	    for(i = 0; matricula[i] != '\0'; i++){
            matricula[i] = toupper(matricula[i]);
	    }

        if(validarMatricula(matricula) == 0){
            //Verifica se a matricula fornecida esta dentro dos formatos aceites
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }
    }while(validarMatricula(matricula) == 0);
    

    //Le todas as entradas do arquivo
    while(fread(&veiculo, sizeof(VEICULO), 1, f) == 1){
        //Se encontrar a matricula pesquisada
        if(strcmp(veiculo.matricula, matricula) == 0){
            encontrado = 1;
            entrada = converterParaTempoLocal(veiculo.entrada);
            printf("\nInformacoes sobre o veiculo:\n\n");
            printf("Matricula: %s\n", veiculo.matricula);
            printf("Classe: %d\n", veiculo.classe);
            printf("Hora de entrada: %s\n\n", entrada);
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
			getch();
            break;
        }
    }

    //Se a matricula nao for encontrada
    if(encontrado == 0){
        printf("\nVeiculo nao encontrado!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
		fflush(stdin);
		getch();
    }

    fclose(f);
}

//Insere um cliente para fidelizar
void guardaFidelizado(char nomeFidelizados[], char nomeF[]){

    FILE *f, *g;
    VEICULO veiculo;
    FIDELIZADO fidelizado;
    int i, duracao;
    char mClasse, data[20], matricula[MAX];
    time_t fimFidelizacao;
    
    f = fopen(nomeFidelizados, "ab");
	if(f == NULL){
		printf("Erro na abertura do ficheiro!\n");
		getch();
		exit(1);
	}

    printf("\n\n**** REGISTAR FIDELIZACAO ****\n\n");
    printf("Nome do Cliente: ");
    scanf("%s", fidelizado.nomeCliente);
    printf("Numero de telefone: ");
    scanf("%s", fidelizado.telefone);

    do{
        system("cls");
        printf("\n\n**** REGISTAR FIDELIZACAO ****\n\n");
        printf("Introduza a matricula a fidelizar: ");
        scanf("%s", matricula);

        for(i = 0; matricula[i] != '\0'; i++){
           matricula[i] = toupper(matricula[i]); 
        }

        if(validarMatricula(matricula) == 0){
            //Caso a matricula nao seja valida
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }else if(validaRegisto(matricula, nomeFidelizados)){
            //Verifica se ja existe uma matricula igual no ficheiro
            printf("\nEsta matricula ja esta registada!\n");
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
            fclose(f);
            getch();
            return;
        }
    }while(validarMatricula(matricula) == 0);
    
    strcpy(fidelizado.matricula, matricula);
    fidelizado.classe = 0;

    g = fopen(nomeF, "rb");
    if(g != NULL){
        while(fread(&veiculo, sizeof(VEICULO), 1, g) == 1){
            if(strcmp(veiculo.matricula, fidelizado.matricula) == 0){
                fidelizado.classe = veiculo.classe;
                printf("\nVeiculo presente no parque!\n\n");
                printf("Classe: %d", veiculo.classe);
                break;
            }
        }
        fclose(g);
    }
    
    if(fidelizado.classe == 0){
        do{
            system("cls");
            printf("\n\n**** REGISTAR FIDELIZACAO ****\n\n");
            printf("Introduza a matricula a fidelizar: %s\n", fidelizado.matricula);
            printf("Matricula valida!\n");
            
            mClasse = escolherClasse();
            switch(mClasse){
                case '1':
                    fidelizado.classe = 1;
                break;
                case '2':
                    fidelizado.classe = 2;
                break;
                case '3':
                    fidelizado.classe = 3;
                break;
                default:
                    printf("\n\nEntrada invalida!\n");
                    printf("Pressione qualquer tecla para voltar a introduzir classe!");
                    getch();
                break;
            }
        }while(mClasse != '1' && mClasse != '2' && mClasse != '3');
    }
        
    printf("\n\nIndique por quantos meses pretende fidelizar: ");
    scanf("%s", data);

    //Verifica se todos os caracteres da string sao algarismos
    for(i = 0; data[i] != '\0'; i++){
        if(!isdigit(data[i])){
            printf("\nEntrada invalida! Por favor, insira um numero valido.\n");
            getch();
            system("cls");
            break;
        }
    }

    //Se string for composta por digitos apenas, converte para inteiro
    duracao = atoi(data); // Converte string para inteiro
    time(&fimFidelizacao);
    fidelizado.fimFidelizacao = fimFidelizacao + duracao * 24 * 60 * 60 * 30;

    fwrite(&fidelizado, sizeof(FIDELIZADO), 1, f);
    fclose(f);
    printf("\nO Cliente foi fidelizado!\n");
    printf("Pressione qualquer tecla para voltar ao menu anterior...");
    getch();
}

//Funcao que apaga uma matricula fidelizada da base de dados
void apagaFidelizacao(char nomeFidelizados[]){
    
	FILE *f, *t;
    FIDELIZADO fidelizado;
    char matricula[MAX], tempf[FILES] = "tempf.dat";
    int i, encontrado = 0;

    printf("\n\n***** APAGAR FIDELIZACAO *****\n\n");

    f = fopen(nomeFidelizados, "rb");
    //Cria um ficheiro temporario
    t = fopen(tempf, "wb");

    if(f == NULL || t == NULL){
        printf("Erro na abertura do ficheiro!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        fclose(t);
        getch();
        remove(tempf);
        return;
    }

    do{
        system("cls");
        printf("\n\n***** APAGAR FIDELIZACAO *****\n\n");
	    printf("Introduza a matricula do veiculo a pesquisar: ");
	    scanf("%s", matricula);

	    for(i = 0; matricula[i] != '\0'; i++){
        matricula[i] = toupper(matricula[i]);
	    }

        if(validarMatricula(matricula) == 0){
            //Verifica se a matricula fornecida esta dentro dos formatos aceites
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }
    }while(validarMatricula(matricula) == 0);

    //Le todos os registos
    while(fread(&fidelizado, sizeof(FIDELIZADO), 1, f) == 1){
        //Se um registo corresponder a matricula fornecida
        if(strcmp(fidelizado.matricula, matricula) == 0){
            encontrado = 1;
            printf("\nA matricula fidelizada foi removida!\n");
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
            fflush(stdin);
            getch();
        }else{
            //Escreve no ficheiro temporario todos os registos exceto o que se pretende apagar
            fwrite(&fidelizado, sizeof(FIDELIZADO), 1, t);
        }
    }

    fclose(f);
    fclose(t);
    
    if(encontrado == 0){
        //Se a matricula nao for encontrada
        printf("\nCliente nao encontrado!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        remove(tempf);
		fflush(stdin);
		getch();
        return;
    }
    
    remove(nomeFidelizados); //Apaga ficheiro fidelizados original
    rename(tempf, nomeFidelizados); //Altera o nome do ficheiro temporario para fidelizados
    printf("Registo removido com sucesso\n");
}

//Funcao para consultar se uma matricula ja esta fidelizada
void pesquisaFidelizacao(char nomeFidelizados[]){
    
    FILE *f;
    FIDELIZADO fidelizado;
    char matricula[MAX], *fimFidelizacao;
	int i, encontrado = 0;

    printf("\n\n**** PESQUISAR FIDELIZACAO ****\n\n");
    
    f = fopen(nomeFidelizados, "rb");
    if(f == NULL){
        printf("Erro na abertura do ficheiro!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
        getch();
        return;
    }
    
    do{
        system("cls");
        printf("\n\n**** PESQUISAR FIDELIZACAO ****\n\n");
	    printf("Introduza a matricula do veiculo a pesquisar: ");
	    scanf("%s", matricula);

	    for(i = 0; matricula[i] != '\0'; i++){
        matricula[i] = toupper(matricula[i]);
	    }

        if(validarMatricula(matricula) == 0){
            //Verifica se a matricula fornecida esta dentro dos formatos aceites
            printf("\nMatricula invalida.\n");
            printf("Pressione qualquer tecla para voltar a introduzir matricula!");
            getch();
        }
    }while(validarMatricula(matricula) == 0);

    //Le todos os registos
    while(fread(&fidelizado, sizeof(FIDELIZADO), 1, f) == 1){   
        //Se a matricula fornecida corresponder a um registo
        if(strcmp(fidelizado.matricula, matricula) == 0){
            //Mostra informacao
            encontrado = 1;
            fimFidelizacao = converterParaTempoLocal(fidelizado.fimFidelizacao);
            printf("\nInformacoes sobre o veiculo:\n\n");
            printf("Nome do Cliente: %s\n", fidelizado.nomeCliente);
            printf("Numero de telefone: %s\n", fidelizado.telefone);
            printf("Matricula: %s\n", fidelizado.matricula);
            printf("Classe: %d\n", fidelizado.classe);
            printf("Fim da fidelizacao: %s\n\n", fimFidelizacao);
            printf("Pressione qualquer tecla para voltar ao menu anterior...");
            encontrado = 1;
			getch();
            break;
        }
    }

    if(encontrado == 0){
        //Se a matricula fornecida nao corresponder a nenhum registo
        printf("\nVeiculo nao encontrado!\n");
        printf("Pressione qualquer tecla para voltar ao menu anterior...");
		fflush(stdin);
		getch();
    }

    fclose(f);
}

//Valida o tipo de matricula e retorna 0 se invalido ou 1 se valido
int validarMatricula(char matricula[]){

    int valido = 0;

    if(strlen(matricula) == 8 &&
        isalpha(matricula[0]) && isalpha(matricula[1]) &&
        isdigit(matricula[3]) && isdigit(matricula[4]) &&
        isdigit(matricula[6]) && isdigit(matricula[7]) &&
        matricula[2] == '-' && matricula[5] == '-'){
            valido = 1;
            return valido;
    }else if(strlen(matricula) == 8 &&
        isdigit(matricula[0]) && isdigit(matricula[1]) &&
        isdigit(matricula[3]) && isdigit(matricula[4]) &&
        isalpha(matricula[6]) && isalpha(matricula[7]) &&
        matricula[2] == '-' && matricula[5] == '-'){
            valido = 1;
            return valido;
    }else if(strlen(matricula) == 8 &&
        isdigit(matricula[0]) && isdigit(matricula[1]) &&
        isalpha(matricula[3]) && isalpha(matricula[4]) &&
        isdigit(matricula[6]) && isdigit(matricula[7]) &&
        matricula[2] == '-' && matricula[5] == '-'){
            valido = 1;
            return valido;
    }else if(strlen(matricula) == 8 &&
        isalpha(matricula[0]) && isalpha(matricula[1]) &&
        isdigit(matricula[3]) && isdigit(matricula[4]) &&
        isalpha(matricula[6]) && isalpha(matricula[7]) &&
        matricula[2] == '-' && matricula[5] == '-'){
            valido = 1;
            return valido;
    }else if(strlen(matricula) <= 10){
        for(int i = 0; i < strlen(matricula); i++){
            if(isalnum(matricula[i]) == 0){
                return valido;
            }
        }
        valido = 1;
        return valido;
    }else{
        return valido;
    }
}

//Funcao que verifica se o veiculo a entrar ja existe no ficheiro
int validaRegisto(char matricula[], char nomeF[]){

    FILE *f;
    VEICULO veiculo;
    FIDELIZADO fidelizado;
    int valido = 0;

    f = fopen(nomeF, "rb");
    if (nomeF == NULL){
        printf("Erro na abertura do ficheiro %s!\n", nomeF);
        getch();
        exit(1);
    }

    if(strcmp(nomeF, VEICULOS) == 0){
        //Le todos os registos no ficheiro
        while(fread(&veiculo, sizeof(VEICULO), 1, f) == 1){
            //Compara a matrícula atual com a matrícula fornecida
            if(strcmp(veiculo.matricula, matricula) == 0){
                //Matrícula já existe no sistema
                fclose(f);
                valido = 1;
                return valido;
            }
        }
    }else if(strcmp(nomeF, FIDELIZADOS) == 0){
        //Le todos os registos no ficheiro
        while(fread(&fidelizado, sizeof(FIDELIZADO), 1, f) == 1){
            //Compara a matricula atual com a matrícula fornecida
            if(strcmp(fidelizado.matricula, matricula) == 0){
                //Matrícula ja existe no sistema
                fclose(f);
                valido = 1;
                return valido;
            }
        }
    }
    
    fclose(f);
    
    //Se chegamos aqui, a matricula nao foi encontrada no sistema
    return valido;
}

float calcularValor(VEICULO veiculo, time_t saida){
    
	double total = 0.0, valor = 0.0;
    int horas = 1 + difftime(saida, veiculo.entrada) / 3600; //Converte segundos em horas

    switch(veiculo.classe){
        case 1: //Mota
            if(horas <= 1){
                valor = 0.2;
                total = 1 * valor;
            }else if(horas <= 4){
                valor = 0.5;
                total = 0.2 + (horas - 1) * valor;
            }else if(horas <= 8){
                valor = 1.0;
                total = 0.2 + (0.5 * 3) + (horas - 4) * valor;
            }else{
                valor = 4.0;
                total = 0.2 + (0.5 * 3) + (1.0 * 4) + (horas - 8) * valor;
            }
        break;
        case 2: //Passageiros
            if(horas <= 1){
                valor = 0.5;
                total = 1 * valor;
            }else if(horas <= 4){
                valor = 1.0;
                total = 0.5 + (horas - 1) * valor;
            }else if(horas <= 8){
                valor = 1.5;
                total = 0.5 + (1.0 * 3) + (horas - 4) * valor;
            }else{
                valor = 10.0;
                total = 0.5 + (1.0 * 3) + (1.5 * 4) + (horas - 8) * valor;
            }
        break;
        case 3: //Mercadorias
            if(horas <= 1){
                valor = 2.0;
                total = 1 * valor;
            }else if(horas <= 4){
                valor = 4.0;
                total = 2.0 + (horas - 1) * valor;
            }else if(horas <= 8){
                valor = 8.0;
                total = 2.0 + (4.0 * 3) + (horas - 4) * valor;
            }else{
                valor = 20.0;
                total = 2.0 + (4.0 * 3) + (8.0 * 4) + (horas - 8) * valor;
            }
        break;
        default:
            printf("Classe de veiculo invalida.\n");
            getch();
            exit(1);
        break;
    }
    
    //Retorna o valor a pagar sem desconto de fidelizacao 
    return total;
}

//Funcao que imprime no ecra os lugares disponiveis para cada classe
void lugaresDisponiveis(int mota, int passageiros, int mercadorias){

    printf("\n\n******* LUGARES LIVRES *******\n\n");
    printf("Mota: %d\n", mota);
    printf("Passageiros: %d\n", passageiros);
    printf("Mercadorias: %d", mercadorias);
    //printf("\nPressione qualquer tecla para voltar ao menu anterior...");
}

//Funcao para apagar bases de dados
void apagaFicheiro(char nomeF[]){

    //Apaga a base de dados indicada ao chamar a funcao
    remove(nomeF);
    printf("\n\nBase de dados eliminada!\n");
    printf("Pressione qualquer tecla para continuar");
    getch();
    return;
}

//Funcao que abre o ficheiro dos veiculos estacionados se existir e conta os lugares livres
LUGARES contaVeiculos(char nomeF[]){

    FILE *f;
    VEICULO veiculo;
    LUGARES lugares;

    //Escrever na estrutura a lotacao do parque para cada classe
    lugares.mota = MOTA;
    lugares.passageiros = PASSAGEIROS;
    lugares.mercadorias = MERCADORIAS;

    f = fopen(nomeF, "rb");
    if(f == NULL){
        //Se o ficheiro nao existir, devolve os valores definidos no inicio do codigo
        return lugares;
    }

    //Le todos os registos do ficheiro
    while(fread(&veiculo, sizeof(VEICULO), 1, f) == 1){
        if(veiculo.classe == 1){
            //Se encontrar motas, decrementa o contador
            lugares.mota--;
        }else if(veiculo.classe == 2){
            //Se encontrar ligeiros de passageiros, decrementa o contador
            lugares.passageiros--;
        }else if(veiculo.classe == 3){
            //Se encontrar ligeiros de mercadorias, decrementa o contador
            lugares.passageiros--;
        }
    }

    fclose(f);
    return lugares;
}

//Funcao que verifica a data de fidelizacao dos veiculos e remove os que estiverem ultrapassados
void verificaFidelizacao(char nomeFidelizados[]){
    
	FILE *f, *t;
    FIDELIZADO fidelizado;
    char matricula[MAX], tempf[FILES] = "tempf.dat";

    f = fopen(nomeFidelizados, "rb");
    //Cria um ficheiro temporario para escever os registos exceto os que se pretendem apagar
    t = fopen(tempf, "wb");
    //Caso nao exista ficheiro, a funcao da return sem efetuar alteracoes
    if(f == NULL){
        fclose(t);
        remove(tempf);
        return;
    }

    //Le todos os registos
    while(fread(&fidelizado, sizeof(FIDELIZADO), 1, f) == 1){
        //Compara com a data do sistema e se tiver data de fidelizacao ultrapassada remove
        if(fidelizado.fimFidelizacao > time(NULL)){
            fwrite(&fidelizado, sizeof(FIDELIZADO), 1, t);
        }
    }
    fclose(f);
    fclose(t);
    remove(nomeFidelizados); //Apaga ficheiro fidelizados
    rename(tempf, nomeFidelizados); //Altera o nome do ficheiro temporario para fidelizados
}

//Funcao que converte o tempo do sistema para tempo local
char* converterParaTempoLocal(time_t tempo){
    // Converter o tempo para a estrutura tm
    struct tm *local = localtime(&tempo);

    // Criar um buffer para armazenar a representação formatada da data/hora
    char *buffer = (char*)malloc(80 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        getch();
        exit(1);
    }

    // Formatar a data/hora no formato desejado
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", local);

    // Retornar a string formatada
    return buffer;
}
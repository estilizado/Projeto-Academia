#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

typedef struct despesas{				//Despesas da academia
	float janeiro;
	float fevereiro;
	float marco;
	float abri;
	float maio;
	float jun;
	float jul;
	float ago;
	float set;
	float out;
	float nov;
	float dez;
	struct despesa_* prox;
}Despesas;

typedef struct pagamentos{						//Pagamentos dos alunos
	float janeiro;
	float fevereiro;
	float marco;
	float abri;
	float maio;
	float jun;
	float jul;
	float ago;
	float set;
	float out;
	float nov;
	float dez;
}Pagamentos;

typedef struct medidas{							//Medidas dos alunos
	char biceps[4];
	char peito[4];
	char coxa[4];
	char kg[4];
	char alt[4];
	struct medidas* prox;
}Medidas;

typedef struct lista{							//Dados pessoais
	char nome[80];
	char sexo[2];
	char cpf[12];
	char idade[3];
	char celular[20];
	char cidade [80];
	char email[30];
	char data[11];
	int ativo;
	Medidas medidas;
	Pagamentos pago;
	struct lista* prox;
}Lista;

// ASSINATURAS DAS FUN��ES

int menuPrincipal(void);
Lista* Dadospessoais(Lista* Aluno);
void cadastroSerie(void);
int financeiro(void);
int menuAluno(void);
Lista* criarLista();
Lista* inserir_dados(Lista *aluno,char *nome,char *sexo,char *cpf,char *idade,char *celular,char *cidade,char *email,char *data);
Lista* remover_cpf(Lista* Aluno, char* cpf);
void Atualizar_dados(Lista* Aluno, char *cpf);
void imprimir_dados(Lista *Aluno);
Lista* inserir_Medidas(Lista* Aluno);
void Saude_Aluno(Lista* Aluno);
int validaTelefone(char *telefone);
int validaNome(char *cidade);
int validaSexo(char *sexo);
int validaIdade(char *idade);
int validaData(char *nasc);
int validaMedidas(char *medida);
int validaCPF(char *cpf);
int meses(void);
void pagar(Lista* Aluno);
void desenvolvimentoAluno(Lista* Aluno);
void despesas(Despesas);
void desativar(Lista* aluno);
void mostrar_aluno(Lista* aluno);
void relatorios (Lista* aluno);
void alunos_atrasos(Lista* aluno);
int validaNumero(char desp[5]);
Lista* ler_arquivos(Lista* Aluno);
void salvar(Lista* l);
void total_despesas(Despesas d);
void salvartudo(Lista* Aluno);
Lista* carregar(Lista* Aluno);

// ESSA FUN��O IR� CHAMAR A OUTRAS FUN��ES APENAS

int main(void){
	setlocale(LC_ALL, "portuguese");

    Lista* Aluno=criarLista();


    Despesas DESPESAS;

    int opc;
    int opc2;
    char cpf[12];
    int acesso;
    inicio:
    opc=menuPrincipal();

    switch (opc){
    case 1:
        system("cls");
        acesso=menuAluno();

        switch (acesso){
        case 1:
            system("cls");
            Aluno=Dadospessoais(Aluno);
            break;
        case 2:
            system("cls");
            Aluno=inserir_Medidas(Aluno);
            break;
        case 3:
            system("cls");
            printf("Informe o CPF para Pesquisar: ");
            scanf(" %11[^\n]", cpf);
			int a = validaCPF(cpf);
			while(a == 1){
				printf("\n CPF INVALIDO ! \n");
				printf("Digite novamente : ");
				scanf(" %11[^\n]", cpf);
				a = validaCPF(cpf);
				}
			Atualizar_dados(Aluno,cpf);
            break;
        case 4:
            system("cls");
            printf("Informe o CPF do aluno para excluir cadastro: ");
			scanf(" %11[^\n]", cpf);
			int b = validaCPF(cpf);
			while(b == 1){
				printf("\n CPF INVALIDO ! \n");
				printf("Digite novamente : ");
				scanf(" %11[^\n]", cpf);
				b = validaCPF(cpf);
				}
            Aluno=remover_cpf(Aluno,cpf);
        }

        break;
    case 2:
        system("cls");
        Saude_Aluno(Aluno);
        break;
    case 3:
        system("cls");
        desenvolvimentoAluno(Aluno);
        break;
    case 4:
        system("cls");
        opc2=financeiro();

        if (opc2==1){
            system("cls");
            pagar(Aluno);
            break;
        }
        else if (opc2==2){
            system("cls");
            despesas(DESPESAS);
            break;
        }
        else if (opc2==3){
            system("cls");
            mostrar_aluno(Aluno);
            break;
        }
        else if (opc2==4){
            system("cls");
            relatorios(Aluno);
            break;
        }
        else if (opc2==5){
            system("cls");
            alunos_atrasos(Aluno);
            break;
        }
        else if (opc2==6){
            system("cls");
            desativar(Aluno);
            break;
            }


    case 5:
        imprimir_dados(Aluno);
        break;
    case 6:
        Aluno = carregar(Aluno);
        break;
    case 0:
        salvartudo(Aluno);
        exit(0);
    default:
        printf("\nValor inv�lido.");
        break;
    }


goto inicio;
	return 0;
}

// FUN��ES

int menuPrincipal(void){
	int escolha;

	{
	printf("                -----------------------------------\n");
	printf("                #   1 - CADASTRO DE ALUNO         #\n");
	printf("                #   2 - BUSCAR SA�DE DO ALUNO     #\n");
	printf("                #   3 - DESENVOLVIMENTO DE ALUNO  #\n");
	printf("                #   4 - FINANCEIRO                #\n");
	printf("                #   5 - IMPRIMIR                  #\n");
	printf("                #   6 - CARREGAR DADOS            #\n");
	printf("                #                                 #\n");
	printf("                #   0 - SAIR E SALVAR             #\n");
	printf("                -----------------------------------\n");
	printf("\n");
	printf(">>> Escolha sua op��o: ");
	scanf("%d", &escolha);

	return escolha;
	}
}
int menuAluno(void){
	int escolha;{
	printf("               -----------------------------------\n");
	printf("               #   1 - CADASTRAR DADOS PESSOAIS  #\n");
	printf("               #   2 - CADASTRAR MEDI��O         #\n");
	printf("               #   3 - ATUALIZAR DADOS           #\n");
	printf("               #   4 - EXCLUIR CADASTRO          #\n");
	printf("               #                                 #\n");
	printf("               #   0 - SAIR                      #\n");
	printf("               -----------------------------------\n");
	printf("\n");
	printf(">>> Escolha sua op��o: ");
	scanf("%d", &escolha);
	printf("\n");

	return escolha;
	}
}

Lista* Dadospessoais(Lista* Aluno){
	printf("CADASTRO DE ALUNO!\n");

	Lista *novo=malloc(sizeof(Lista));

	printf("\nNome do Usuario: ");
	scanf(" %80[^\n]",novo->nome);
	fflush(stdin);
	int val = validaNome(novo->nome);
	while(val == 1){
		printf("\nDigite o nome novamente: ");
		scanf(" %80[^\n]", novo->nome);
		fflush(stdin);
		val = validaNome(novo->nome);
		}

	printf("\nInforme o sexo (M) ou (F): ");
	scanf(" %1[^\n]", novo->sexo);
	fflush(stdin);
	int val2 = validaSexo(novo->sexo);
	while(val2 == 1){
		printf("\nInforme o sexo (M) ou (F): ");
		scanf(" %1[^\n]", novo->sexo);
		fflush(stdin);
		val2 = validaSexo(novo->sexo);
		}

	printf("\nInforme seu CPF: ");
	scanf(" %11[^\n]", novo->cpf);
	fflush(stdin);
	int val3 = validaCPF(novo->cpf);
	while(val3 == 1){
		printf("\n CPF INVALIDO ! \n");
        printf("Digite novamente : ");
		scanf(" %11[^\n]", novo->cpf);
		val3 = validaCPF(novo->cpf);
		}

	printf("\nInforme a idade: ");
	scanf(" %2[^\n]",novo->idade);
	fflush(stdin);
	int val4 = validaIdade(novo->idade);
	while(val4 == 1){
		printf("\nInforme a idade novamente: ");
		scanf(" %2[^\n]", novo->idade);
		fflush(stdin);
		val4 = validaIdade(novo->idade);
		}

	printf("\nInforme o celular: ");
	scanf(" %11[^\n]", novo->celular);
	fflush(stdin);
	int val5 = validaTelefone(novo->celular);
	while(val5 == 1){
		printf("\nInforme o celular novamente: ");
		scanf(" %11[^\n]", novo->celular);
		fflush(stdin);
		val5 = validaTelefone(novo->celular);
		}

	printf("\nInforme a cidade: ");
	scanf(" %80[^\n]",novo->cidade);
	fflush(stdin);
	int val6 = validaNome(novo->cidade);
	while(val6 == 1){
		printf("\nInforme a cidade novamente: ");
		scanf(" %80[^\n]", novo->cidade);
		fflush(stdin);
		val6 = validaNome(novo->cidade);
		}

	printf("\nInforme o E-MAIL : ");
	scanf(" %29[^\n]",novo->email);
	fflush(stdin);

	printf("\nInforme a data de Nascimento Ex: 01/01/2001: ");
	scanf(" %10[^\n]", novo->data);
	fflush(stdin);
	int val8 = validaData(novo->data);
	while(val8 == 1){
		printf("\nInforme a data novamente: ");
		scanf(" %10[^\n]", novo->data);
		fflush(stdin);
		val8 = validaData(novo->data);
		}

	printf("\n\nCADASTRO CONCLU�DO! \n\n");
	Aluno=inserir_dados(Aluno,novo->nome,novo->sexo,novo->cpf,novo->idade,novo->celular,novo->cidade,novo->email,novo->data);

	return Aluno;
	}

Lista* inserir_Medidas(Lista* Aluno){

	Lista* x=Aluno;

    char cpf1[12];
    if(Aluno==NULL){
            printf("\n\nN�O EXISTE ALUNO CADASTRADO. \n\n");
            system("pause");
    }
    else{
    printf("\n\n~~ MEDIDAS~~\n\n");
    printf("DIGITE O CPF PARA INSERIR AS MEDIDAS: ");
    scanf(" %11[^\n]", cpf1);
    int val0 = validaCPF(cpf1);
	while(val0 == 1){
		printf("\nDigite o CPF sem pontos e tracos: ");
		scanf(" %11[^\n]", cpf1);
		val0 = validaCPF(cpf1);
		}



		for (x=Aluno;x!=NULL;x=x->prox){
			if(strcmp(x->cpf, cpf1) == 0){
				printf("\nInforme o Peso do Aluno: ");
				scanf(" %3[^\n]", x->medidas.kg);
				int val1 = validaMedidas(x->medidas.kg);
				while(val1 == 1){
					printf("\nInforme o Peso do Aluno: ");
					scanf(" %3[^\n]", x->medidas.kg);
					fflush(stdin);
					val1 = validaMedidas(x->medidas.kg);
					}

				printf("\nInforme o Biceps: ");
				scanf(" %3[^\n]", x->medidas.biceps);
				int val2 = validaMedidas(x->medidas.biceps);
				while(val2 == 1){
					printf("\nInforme o Biceps: ");
					scanf(" %3[^\n]", x->medidas.biceps);
					fflush(stdin);
					val2 = validaMedidas(x->medidas.biceps);
					}

				printf("\nInforme o peitoral: ");
				scanf(" %3[^\n]", x->medidas.peito);
				int val4 = validaMedidas(x->medidas.peito);
				while(val4 == 1){
					printf("\nInforme o peitoral: ");
					scanf(" %3[^\n]", x->medidas.peito);
					fflush(stdin);
					val4 = validaMedidas(x->medidas.peito);
					}

				printf("\nInforme a medida das pernas: ");
				scanf(" %3[^\n]", x->medidas.coxa);
				int val5 = validaMedidas(x->medidas.coxa);
				while(val5 == 1){
					printf("\nInforme a medida das pernas: ");
					scanf(" %3[^\n]", x->medidas.coxa);
					fflush(stdin);
					val5 = validaMedidas(x->medidas.coxa);
					}
				printf("\n Informe a altura : ");
				scanf(" %3[^\n]", x->medidas.alt);
				int val6 = validaMedidas(x->medidas.alt);
				while (val6==1){
					printf("\n Informe novamente a altura : ");
					scanf(" %3[^\n]", x->medidas.alt);
					fflush(stdin);
					val6=validaMedidas(x->medidas.alt);
				}

				printf("\n\n MEDIDAS REGISTRADAS COM SUCESSO !!\n\n");
				}
		}
	}
	return Aluno;
}

void Atualizar_dados(Lista* Aluno, char *cpf){

	Lista* p=Aluno;
	if (p==NULL){
            printf("\n\nN�O EXISTE ALUNO CADASTRADO !\n\n");
        system("pause");
	}
	else{
	for (p=Aluno;p!=NULL;p=p->prox){
		if(strcmp(p->cpf, cpf) == 0){
			printf("\n\n ~~ATUALIZAR CADASTRO~~\n\n");
			printf("\nNome do Usuario: ");
			scanf(" %80[^\n]",p->nome);
			fflush(stdin);
			int val = validaNome(p->nome);
			while(val == 1){
				printf("\nDigite o nome novamente: ");
				scanf(" %80[^\n]", p->nome);
				fflush(stdin);
				val = validaNome(p->nome);
				}

			printf("\nInforme o sexo (M) ou (F): ");
			scanf(" %1[^\n]", p->sexo);
			fflush(stdin);
			int val2 = validaSexo(p->sexo);
			while(val2 == 1){
				printf("\nInforme o sexo (M) ou (F) novamente: ");
				scanf(" %1[^\n]", p->sexo);
				fflush(stdin);
				val2 = validaSexo(p->sexo);
				}


			printf("\nInforme a idade: ");
			scanf(" %2[^\n]",p->idade);
			fflush(stdin);
			int val4 = validaIdade(p->idade);
			while(val4 == 1){
				printf("\nInforme a idade novamente: ");
				scanf(" %2[^\n]", p->idade);
				fflush(stdin);
				val4 = validaIdade(p->idade);
				}


			printf("\nInforme o celular [sem pontos e tra�os]: ");
			scanf(" %11[^\n]",p->celular);
			fflush(stdin);
			int val5 = validaTelefone(p->celular);
			while(val5 == 1){
				printf("\nInforme o celular [sem pontos e tra�os] novamente: ");
				scanf(" %11[^\n]", p->celular);
				fflush(stdin);
				val5 = validaTelefone(p->celular);
				}

			printf("\nInforme a cidade: ");
			scanf(" %80[^\n]",p->cidade);
			fflush(stdin);
			int val6 = validaNome(p->cidade);
			while(val6 == 1){
				printf("\nInforme a cidade novamente: ");
				scanf(" %80[^\n]", p->cidade);
				fflush(stdin);
				val6 = validaNome(p->cidade);
				}

			printf("\nInforme o E-MAIL: ");
			scanf(" %29[^\n]",p->email);
			fflush(stdin);


			printf("\nInforme a data de Nascimento Ex: 01/01/2001: ");
			scanf(" %10[^\n]",p->data);
			fflush(stdin);
			int val8 = validaData(p->data);
			while(val8 == 1){
				printf("\nInforme a data novamente: ");
				scanf(" %10[^\n]", p->data);
				fflush(stdin);
				val8 = validaData(p->data);
				}
				printf("\n\n ATUALIZADO COM SUCESSO\n\n");
            }
        }
	}
}
void imprimir_dados(Lista *Aluno){
	Lista* p=Aluno;
	if (p==NULL){
			printf("\n\nN�o h� alunos cadastrados!\n\n");
			system("pause");
			}
    else {
		for (p=Aluno;p!=NULL;p=p->prox){
			printf("\nNome do Usuario: %s", p->nome);
			printf("\nSexo: %s", p->sexo);
			printf("\nCPF: %s", p->cpf);
			printf("\nIdade: %s", p->idade);
			printf("\nCelular: %s", p->celular);
			printf("\nCidade: %s", p->cidade);
			printf("\nE-MAIL: %s", p->email);
			printf("\nData de Nascimento: %s", p->data);
			printf("\nCoxa: %s", p->medidas.biceps);
			printf("\nAltura: %s", p->medidas.peito);
			printf("\nPeito: %s", p->medidas.coxa);
			printf("\nKilos: %s", p->medidas.kg);
			printf("\nBiceps: %s", p->medidas.alt);
			printf("\n");

		}
	}
}

void Saude_Aluno(Lista* Aluno){
    char cpf2[12];
    Lista* p;
    if(Aluno==NULL){
        printf("\nN�O EXISTE ALUNO CADASTRADO\n");
        system("pause");
    }
    else{
		float imc=0;
		printf("\n\nSA�DE DO ALUNO\n\n");
		printf("\nInforme o CPF do Aluno: ");
		scanf(" %11[^\n]", cpf2);
		int val01 = validaCPF(cpf2);
		while(val01 == 1){
			printf("\nDigite o CPF sem pontos e tracos: ");
			scanf(" %11[^\n]", cpf2);
			val01 = validaCPF(cpf2);
			}

		for (p=Aluno;p!=NULL;p=p->prox){
			if(strcmp(p->cpf, cpf2)==0){
				float altura=atof(p->medidas.alt);
				float pesoc=atof(p->medidas.kg);
				imc=pesoc/(altura*altura);
				if (imc<17.0){
					printf("\n%s, voc� esta muito abaixo do peso ideal, com um IMC de %.2f.\n",p->nome,imc);
				}
				else if (imc>17.0 &&imc<18.4){
					printf("\n%s, voc� est� abaixo do peso ideal, com um IMC de %.2f.\n ",p->nome,imc);
				}
				else if (imc>=18.5 && imc <=24.9){
					printf("\n%s, voc� esta com o peso ideal, IMC de %.2f.\n ",p->nome,imc);
				}
				else if (imc>=25.0 && imc<=29.99){
					printf("\n%s, voc� esta acima do peso, com IMC de %.2f. \n",p->nome,imc);
				}
				else if (imc>=30.0 && imc<34.99){
					printf("\n%s, voc� est� OBESO, com um IMC de %.2f.\n",p->nome,imc);
				}
				else if(imc>=35.0 && imc <=39.99){
					printf("\n%s, voc� est� com uma obesidade SEVERA, com um IMC de %.2f. \n",p->nome,imc);
				}
				else if(imc>40.0){
					printf("\n%s, voc� est� com uma obesidade M�RBIDA, com um IMC de %.2f.\n",p->nome,imc);
				}
				break;
			}


		}
	}
}

void desenvolvimentoAluno(Lista* Aluno){
	printf("DESENVOLVIMENTO DE ALUNO!\n");
	float nova_altura,novo_peito,nova_coxa,novo_biceps,resAlt,resPeso,resPeito,resBraco,resCoxs; //novo_peso,
	Lista* p=Aluno;
    if (p==NULL){
        printf("\n\nN�O EXISTE ALUNO CADASTRADO !!\n\n");
        system("pause");
    }
    else{
    char cpf3[12];
    printf("DIGITE O CPF DO ALUNO : ");
    scanf(" %11[^\n]", cpf3);
    int b1 = validaCPF(cpf3);
	while(b1 == 1){
		printf("\nDigite o CPF sem pontos e tracos: ");
		scanf(" %11[^\n]", cpf3);
		b1 = validaCPF(cpf3);
		}
    float altura=atof(p->medidas.alt);
    float biceps=atof(p->medidas.biceps);
    float coxa=atof(p->medidas.coxa);
    float peito=atof(p->medidas.peito);
    char temp2[5];
	for (p=Aluno;p!=NULL;p=p->prox){
		if(strcmp(p->cpf, cpf3) == 0){
		    printf("\nAVISO !!\n");
            printf("\nESSE PROCEDIMENTO DEVE SER FEITO AP�S 3 MESES DE TREINO !! \n");

            printf("\n\nInforme sua atual altura : \n\n");
            scanf(" %4[^\n]", temp2);
			sscanf(temp2, "%f", &nova_altura);
			int a = validaNumero(temp2);
			while(a == 1){
				printf("Informe sua atual altura ? \n");
				scanf(" %4[^\n]", temp2);
				sscanf(temp2, "%f", &nova_altura);
				a = validaNumero(temp2);
				}

            if(nova_altura>altura){
                resAlt=nova_altura-altura;
                printf("Voce aumentou %.2f cm.\n",resAlt);
            }
            else if(nova_altura<altura){
                resPeso=nova_altura-altura;
                printf("Voce diminuiu %.2f cm.\n",resPeso);
            }
            else if (nova_altura==altura){
                printf("N�o obteve resultados ! ");
            }

            printf("\n\nInforme o peitoral : \n\n");
            scanf(" %4[^\n]", temp2);
			sscanf(temp2, "%f", &novo_peito);
			int b = validaNumero(temp2);
			while(b == 1){
				printf("\n\nInforme o peitoral : \n\n");
				scanf(" %4[^\n]", temp2);
				sscanf(temp2, "%f", &novo_peito);
				b = validaNumero(temp2);
				}

            if (novo_peito>peito){
                resPeito=novo_peito-peito;
                printf(" Voce aumentou %.2f cm.",resPeito);
            }
            else if (novo_peito<peito){
                resPeito=novo_peito-peito;
                printf("Voce diminuiu %.2f cm.",resPeito);
            }
            else if (novo_peito==peito){
                printf("N�o obteve resultados ! ");

            }

            printf("\n\nInforme o biceps : \n\n");
            scanf(" %4[^\n]", temp2);
			sscanf(temp2, "%f", &novo_biceps);
			int c = validaNumero(temp2);
			while(c == 1){
				printf("Informe o biceps ? \n");
				scanf(" %4[^\n]", temp2);
				sscanf(temp2, "%f", &novo_biceps);
				c = validaNumero(temp2);
				}

            if (novo_biceps>biceps){
                resBraco=novo_biceps-biceps;
                printf("Voc� aumentou %.2f cm.",resBraco);
            }
            else if (novo_biceps<biceps){
                resBraco=novo_biceps-biceps;
                printf(" voce diminuiu %.2f cm",resBraco);
            }
            else if (novo_biceps==biceps){
                printf(" N�o obteve resultados ! ");

            }

            printf("\n\nInforme as medidas da perna : \n\n");
			scanf(" %4[^\n]", temp2);
			sscanf(temp2, "%f", &nova_coxa);
			int c1 = validaNumero(temp2);
			while(c1 == 1){
				printf("\n\nInforme as medidas da perna : \n\n");
				scanf(" %4[^\n]", temp2);
				sscanf(temp2, "%f", &nova_coxa);
				c1 = validaNumero(temp2);
				}

            if (nova_coxa>coxa){
                resCoxs=nova_coxa-coxa;
                printf("Voc� aumentou %.2f cm.",resCoxs);
            }
            else if (nova_coxa<coxa){
                resCoxs=nova_coxa-coxa;
                printf("Voc� diminuiu %.2f cm.",resCoxs);
            }
            else if (nova_coxa==coxa){
                     printf(" N�o obteve resultados ! ");
            }
        }

		}
	}
}

int financeiro(void){
    int escolha;
    do{
	printf("FINANCEIRO!\n");
	printf("                -----------------------------------\n");
	printf("                #   1 - PAGAR M�S                 #\n");
	printf("                #   2 - DESPESAS DA ACADEMIA      #\n");
	printf("                #   3 - ALUNOS ATIVOS             #\n");
	printf("                #   4 - RELATORIOS                #\n");
	printf("                #   5 - ALUNOS EM ATRASO          #\n");
	printf("                #   6 - DESATIVAR ALUNO           #\n");
	printf("                #   0 - SAIR                      #\n");
	printf("                -----------------------------------\n");
	printf("\n");
	printf(">>> Escolha sua op��o: ");
	scanf("%d", &escolha);
    }while(escolha>7);
    return escolha;
}

Lista* criarLista(){
	return NULL;
	}

Lista* inserir_dados(Lista *aluno,char *nome,char *sexo,char *cpf,char *idade,char *celular,char *cidade,char *email, char *data){
	Lista* p=aluno;  // RECEBE A LISTA ALUNO
	Lista* ant=NULL; // GUARDA A POSI��O ANTERIOR
	Lista* novo=(Lista*)malloc(sizeof(Lista)); // adiciona nome

	strcpy(novo->nome, nome);
	strcpy(novo->sexo, sexo);
	strcpy(novo->cpf, cpf);
	strcpy(novo->idade, idade);
	strcpy(novo->celular, celular);
	strcpy(novo->cidade, cidade);
	strcpy(novo->email,email);
	strcpy(novo->data, data);
	novo->ativo=1;
	novo->prox=NULL;

	// Lista vazia ?

	if (p==NULL){
        // guarda o novo
		return novo;
	}
	while ((p!=NULL) && strcmp(novo->nome,p->nome)>0) {
		// guarda as posi��es anteriores
		ant=p;
		// ir para o proximo
		p=p->prox;
		}
		// nao entendi
	if (ant==NULL){
	   novo->prox=p;
	   return novo;
		}
	// novo prox aponta para ant que aponta para o proximo
	// entao o anterior agora aponta para novo
	novo->prox=ant->prox;
	ant->prox=novo;
	return aluno;
}

Lista* remover_cpf(Lista* Aluno, char* cpf){
	Lista* ant=NULL;
	Lista* p=Aluno;                  					// p � aux pra percorrer
	while((p != NULL) && strcmp(p->cpf,cpf) != 0){
		ant=p;
		p=p->prox;
		}
														// caso ELE NAO ACHAR----
		if (p==NULL){
			printf("ALUNO N�O ENCONTRADO\n");
			return Aluno;
		}
														// ant � null so se for o primeiro elemento
		if(ant==NULL){
			Aluno=p->prox;
		}
		else{
			ant->prox=p->prox;
		}
	free(p);
	printf("CADASTRO REMOVIDO COM SUCESSO !");
	return Aluno;
}


int validaNome(char* cidade){
	int a;
	for(a = 0; cidade[a] != '\0'; a++){
		if((cidade[a] >= 'a' && cidade[a] <= 'z' ) || (cidade[a] >= 'A' && cidade[a] <= 'Z' ))
			return 0;
		else
			return 1;
		}
	return 0;
	}

int validaTelefone(char *telefone){
	int a;
	int j = strlen(telefone);
	for(a = 0; telefone[a] != '\0'; a++){
		if((telefone[a] >= 65 && telefone[a] <= 90) || (telefone[a] >=97 && telefone[a] <= 122) || (j < 8))
			return 1;
		else
			return 0;
		}
	return 0;
	}

int validaSexo(char *sexo){
	int a;
	for(a = 0; sexo[a] != '\0'; a++){
		if((sexo[a] == 'M' || sexo[a] == 'm') || (sexo[a] == 'F' || sexo[a] == 'f'))
			return 0;
		else
			return 1;
		}
	return 0;
	}

int validaIdade(char *idade){
	int a;
	for(a = 0; idade[a] != '\0'; a++){
		if(idade[a] >= 48 && idade[a] <= 57)
			return 0;
		else
			return 1;
		}
	return 0;
	}

int validaData(char *nasc){
		if(nasc[2] == 47 && nasc[5] == 47)
			return 0;
		else
			return 1;
	return 0;
	}

int validaMedidas(char *medida){
	int a;
	for(a = 0; medida[a] != '\0'; a++){
		if(medida[a] >= 48 && medida[a] <= 57)
			return 0;
		else
			return 1;
		}

	return 0;
	}

int validaCPF(char *cpf){
	int contador, soma, resultado, resultado2, valor;
	int digito10, digito11, tam;
	soma = 0;
	tam = strlen(cpf);
	if(tam < 11|| tam>11){
		printf("\nDigite o CPF com 11 campos.\n");
		return 1;
		}
	else{
		for(contador = 0; contador < 11; contador++){
			cpf[contador] -= 48;
		}

		for(contador = 0; contador < 9; contador++){ //Verifica��o para primeiro digito
			soma += cpf[contador] * (10 - contador);
			}

		resultado = soma % 11;

		if(resultado == 0 || resultado == 1)
			digito10 = 0;
		else
			digito10 = 11 - resultado;

		soma = 0;

		for(contador = 0; contador < 10; contador++){ //Verifica��o para segundo digito
			soma += cpf[contador] * (11 - contador);
			}
		valor = (soma / 11) * 11;
		resultado2 = soma - valor;
		if(resultado2 == 0 || resultado2 == 1)
			digito11 = 0;
		else
			digito11 = 11 - resultado2;

		for(contador = 0; contador < 11; contador++){
				cpf[contador] += 48;
			}
		if((digito10 == cpf[9]) && (digito11 == cpf[10]))
			return 1;
		else
			return 0;
	}


	return 0;
}

int validaNumero(char desp[5]){
	int a;
	for(a = 0; desp[a] != '\0'; a++){
	if(desp[a] >= 48 && desp[a] <= 57){
		 return 0;
		}
	else{
		return 1;
		}
	}
	return 0;
	}

int meses(void){
    int escolha;
    do{
	printf("\nInforme o m�s referente ao pagamento !!\n");
	printf("| 1 - JANEIRO       |\n");
	printf("| 2 - FEVEREIRO     |\n");
	printf("| 3 - MAR�O         |\n");
	printf("| 4 - ABRIL         |\n");
	printf("| 5 - MAIO          |\n");
	printf("| 6 - JUNHO         |\n");
	printf("| 7 - JULHO         |\n");
	printf("| 8 - AGOSTO        |\n");
	printf("| 9 - SETEMBRO      |\n");
	printf("| 10 - OUTUBRO      |\n");
	printf("| 11 - NOVEMBRO     |\n");
	printf("| 12 - DEZEMBRO     |\n");
	scanf("%d",&escolha);
	}while(escolha>12&&escolha<1);

	return escolha;
}

void pagar(Lista* Aluno){
    Lista* p=Aluno;
    if (p==NULL){
        printf("\n\nN�o existe aluno cadastrado !!\n\n");
        system("pause");
    }
    else{
    char cpf3[12];
    printf("DIGITE O CPF DO ALUNO : ");
    scanf(" %11[^\n]", cpf3);
    int x = validaCPF(cpf3);
	while(x == 1){
		printf("\nDigite o CPF sem pontos e tracos: ");
		scanf(" %11[^\n]", cpf3);
		x = validaCPF(cpf3);
		}
	for (p=Aluno;p!=NULL;p=p->prox){
		if(strcmp(p->cpf, cpf3) == 0){
			int mes_pag=meses();
			if(mes_pag==1){
                p->pago.janeiro=35.00;
                printf(" M�S DE JANEIRO PAGO !! \n");
			}
			else if (mes_pag==2){
                p->pago.fevereiro=35.00;
                printf(" M�S DE FEVEREIRO PAGO !! \n");
			}
			else if (mes_pag==3){
                p->pago.marco=35.00;
                printf(" M�S DE MAR�O PAGO !! \n");
			}
			else if (mes_pag==4){
                p->pago.abri=35.00;
                printf(" M�S DE ABRIL PAGO !! \n");
            }
            else if (mes_pag==5){
                p->pago.maio=35.00;
                printf(" M�S DE MAIO PAGO !! \n");
            }
            else if (mes_pag==6){
                p->pago.jun=35.00;
                printf(" M�S DE JUNHO PAGO !! \n");
            }
            else if (mes_pag==7){
                p->pago.jul=35.00;
                printf(" M�S DE JULHO PAGO !! \n");
            }
            else if (mes_pag==8){
                p->pago.ago=35.00;
                printf(" M�S DE AGOSTO PAGO !! \n");
            }
            else if (mes_pag==9){
                p->pago.set=35.00;
                printf(" M�S DE SETEMBRO PAGO !! \n");
            }
            else if (mes_pag==10){
                p->pago.out=35.00;
                printf(" M�S DE OUTUBRO PAGO !! \n");
            }
            else if (mes_pag==11){
                p->pago.nov=35.00;
                printf(" M�S DE NOVEMBRO PAGO !! \n");
            }
            else if (mes_pag==12){
                p->pago.dez=35.00;
                printf(" M�S DE DEZEMBRO PAGO !! \n");
            }
		}
		}
	}
}

void despesas(Despesas d){

	//FILE* despesa;
	//despesa = fopen("fileDespesaAcademia.txt", "w+");

    float luz;
    float agua;
    float funcionarios;
    float manutencao;
    float total;
    char temp[5];
	printf("\n\nINFORME AS DESPESAS DA ACADEMIA \n\n");


	printf("Quanto gastou com luz ? \n");
	scanf(" %4[^\n]", temp);
	sscanf(temp, "%f", &luz);
	int a = validaNumero(temp);
    while(a == 1){
        printf("\nDigite novamente: ");
        scanf(" %4[^\n]", temp);
        sscanf(temp, "%f", &luz);
        a = validaNumero(temp);
    }


	printf("Quanto gastou com agua ? \n");
	scanf(" %4[^\n]", temp);
	sscanf(temp, "%f", &agua);
	int b = validaNumero(temp);
    while(b == 1){
        printf("\nDigite novamente: ");
        scanf(" %4[^\n]", temp);
        sscanf(temp, "%f", &agua);
        b = validaNumero(temp);
    }


	printf("Quanto gastou com funcionarios ? \n");
	scanf(" %4[^\n]", temp);
	sscanf(temp, "%f", &funcionarios);
	int c = validaNumero(temp);
    while(c == 1){
        printf("\nDigite novamente: ");
        scanf(" %4[^\n]", temp);
        sscanf(temp, "%f", &funcionarios);
        c = validaNumero(temp);
    }

	printf("Quanto gastou com Manuten��o ? \n");
    scanf(" %4[^\n]", temp);
	sscanf(temp, "%f", &manutencao);
	int cc = validaNumero(temp);
    while(cc == 1){
        printf("\nDigite novamente: ");
        scanf(" %4[^\n]", temp);
        sscanf(temp, "%f", &manutencao);
        cc = validaNumero(temp);
    }

	total=luz+agua+funcionarios+manutencao;
	//int mes;
	printf(" QUAL O MES DESEJA CONTABILIZAR AS DESPESAS ?");
	int mes_pag=meses();

	if(mes_pag==1){
        d.janeiro=total;

        printf(">>> M�S DE JANEIRO CONTABILIZADO\n");
        //mes = 1;
		}
	else if (mes_pag==2){
		d.fevereiro=total;
		printf(">>>  M�S DE FEVEREIRO CONTABILIZADO!! \n");
		//mes = 2;
		}
	else if (mes_pag==3){
		d.marco=total;
		printf(">>>  M�S DE MAR�O CONTABILIZADO !! \n");
		//mes = 3;
		}
	else if (mes_pag==4){
		d.abri=total;
		printf(">>>  M�S DE ABRIL CONTABILIZADO !! \n");
		//mes = 4;
		}
	else if (mes_pag==5){
		d.maio=total;
		printf(">>>  M�S DE MAIO CONTABILIZADO !! \n");
		//mes = 5;
		}
	else if (mes_pag==6){
		d.jun=total;
		printf(">>>  M�S DE JUNHO CONTABILIZADO !! \n");
		//mes = 6;
		}
	else if (mes_pag==7){
		d.jul=total;
		printf(">>>  M�S DE JULHO CONTABILIZADO !! \n");
		//mes = 7;
		}
	else if (mes_pag==8){
		d.ago=total;
		printf(">>>  M�S DE AGOSTO CONTABILIZADO !! \n");
		//mes = 8;
		}
	else if (mes_pag==9){
		d.set=total;
		printf(">>>  M�S DE SETEMBRO CONTABILIZADO !! \n");
		//mes = 9;
		}
	else if (mes_pag==10){
		d.out=total;
		printf(">>>  M�S DE OUTUBRO CONTABILIZADO !! \n");
		//mes = 10;
		}
	else if (mes_pag==11){
		d.nov=total;
		printf(">>>  M�S DE NOVEMBRO CONTABILIZADO !! \n");
		//mes = 11;
		}
	else if (mes_pag==12){
		d.dez=total;
		printf(">>>  M�S DE DEZEMBRO CONTABILIZADO !! \n");
		//mes = 12;
	}

}

void desativar(Lista* aluno){
	Lista* p=aluno;
		if (p==NULL){
			printf("\nN�o existe aluno cadastrado.\n");
			system("pause");
		}
		else{
		char cpf3[12];
		printf("DIGITE O CPF DO ALUNO : ");
		scanf(" %11[^\n]", cpf3);
		int x = validaCPF(cpf3);
		while(x == 1){
			printf("\nDigite o CPF sem pontos e tracos: ");
			scanf(" %11[^\n]", cpf3);
			x = validaCPF(cpf3);
		}
		for (p=aluno;p!=NULL;p=p->prox){
			if(strcmp(p->cpf, cpf3) == 0){
				p->ativo=0;
				printf("O aluno %s, desativado do sistema com sucesso.", p->nome);
			}
        }
    }
}

void mostrar_aluno(Lista* aluno){
	Lista* p=aluno;
		if (p==NULL){
			printf("\n\nN�o existe aluno cadastrado !!\n\n");
			system("pause");
		}
		else{
		for (p=aluno;p!=NULL;p=p->prox){
			if(p->ativo==1){
				printf("ALUNOS ATIVOS ! ");
				printf("%s\n", p->nome);
			}
		}
	}
}

void relatorios (Lista* aluno){
	Lista* p=aluno;
    if (p==NULL){
        printf("\n\nN�o existe aluno cadastrado!!\n\n");
        system("pause");
    }
    else{
		float recebeu;

			printf("Informe um mes que deseja consultar receita: ");
			int mes_pag=meses();
			if(mes_pag==1){
				recebeu=p->pago.janeiro;
					printf("\nSaldo no mes de janeiro %.2f\n",recebeu);
				}
				else if (mes_pag==2){
					recebeu=p->pago.fevereiro;
					printf("\nSaldo do mes de fevereiro %.2f\n",recebeu);
				}
				else if (mes_pag==3){
					recebeu=p->pago.marco;
					printf("\nSaldo no mes de mar�o %.2f\n",recebeu);
				}
				else if (mes_pag==4){
					recebeu=p->pago.abri;
					printf("\nSaldo no mes de abril %.2f\n",recebeu);
				}
				else if (mes_pag==5){
					recebeu=p->pago.maio;
					printf("\nSaldo no mes de maio %.2f\n",recebeu);
				}
				else if (mes_pag==6){
					recebeu=p->pago.jul;
					printf("\nSaldo no mes de junho %.2f\n",recebeu);
				}
				else if (mes_pag==7){
				   recebeu=p->pago.jul;
					printf("\nSaldo no mes de julho %.2f\n",recebeu);
				}
				else if (mes_pag==8){
					recebeu=p->pago.ago;
					printf("\nSaldo no mes de Agosto %.2f\n",recebeu);
				}
				else if (mes_pag==9){
					recebeu=p->pago.set;
					printf("\nSaldo no mes de setembro %.2f\n",recebeu);
				}
				else if (mes_pag==10){
					recebeu=p->pago.out;
					printf("\nSaldo no mes de outubro %.2f\n",recebeu);
				}
				else if (mes_pag==11){
					recebeu=p->pago.nov;
					printf("\nSaldo no mes de Novembro %.2f\n",recebeu);
				}
				else if (mes_pag==12){
					recebeu=p->pago.dez;
					printf("\nSaldo no mes de dezembro %.2f\n",recebeu);
			}
		}
    }

void alunos_atrasos(Lista* aluno){
Lista* p=aluno;
if (p==NULL){
        printf("\nN�o existe aluno cadastrado.\n");
        system("pause");
    }
    else{

	for (p=aluno;p!=NULL;p=p->prox){
	    printf("\n%s est� devendo ", p->nome);
            if(p->pago.janeiro==0){
                printf(">>> Janeiro \n");
				}
			if (p->pago.fevereiro==0){
                printf(">>> Fevereiro \n");
				}
			 if (p->pago.marco==0){
                printf(">>> Mar�o \n");
				}
			 if (p->pago.abri==0){
                printf(">>> Abril \n");
				}
             if (p->pago.maio==0){
                printf(">>> Maio \n");
				}
             if (p->pago.jun==0){
                printf(">>> Junho \n");
				}
             if (p->pago.jul==0){
               printf(">>> Julho \n");
				}
             if (p->pago.ago==0){
                printf(">>> Agosto \n");
				}
             if (p->pago.set==0){
                printf(">>> Setembro \n");
				}
             if (p->pago.out==0){
                printf(">>> Outubro \n");
				}
             if (p->pago.nov==0){

                printf(">>> Novembro \n");
				}
             if (p->pago.dez==0){
                printf(">>> Dezembro \n");
				}
		}
	}
}
Lista* ler_arquivos(Lista* Aluno){
	char nome[81];
	char sexo[2];
	char cpf[12];
	char idade[3];
	char celular[20];
	char cidade[81];
	char email[30];
	char data[12];
	char alt[3];
	char biceps[3];
	char coxa[3];
	char kg[3];
	char peito[3];
	FILE* ler_;
	ler_ = fopen("teste.txt","rt");
	if(ler_ == NULL){
        printf("H� um erro ao abrir este arquivo!\n");
    	  exit(1);
	}
	Lista* p=Aluno;


	while(fscanf(ler_, "%s %s %s %s %s %s %s %s\n",  nome, sexo, cpf, idade, celular, cidade, email, data) == 8){
    p=inserir_dados(p,nome,sexo,cpf,idade,celular,cidade,email,data);

printf(" Dados carregados");
return p;

fclose(ler_);
}
}

void salvar(Lista* l){
	FILE *s;
	s = fopen ("teste.txt", "wt");
	Lista* salva;
	for(salva=l; salva!=NULL; salva=salva->prox){
		fprintf(s, "%s\n", salva->nome);
		fprintf(s, "%s\n", salva->sexo);
		fprintf(s, "%s\n", salva->cpf);
		fprintf(s, "%s\n", salva->idade);
		fprintf(s, "%s\n", salva->celular);
		fprintf(s, "%s\n", salva->cidade);
		fprintf(s, "%s\n", salva->email);
		fprintf(s, "%s\n", salva->data);
		fprintf(s, "%s\n", salva->medidas.alt);
		fprintf(s, "%s\n", salva->medidas.biceps);
		fprintf(s, "%s\n", salva->medidas.coxa);
		fprintf(s, "%s\n", salva->medidas.kg);
		fprintf(s, "%s\n", salva->medidas.peito);
		fprintf(s, "%d\n", salva->ativo);
}
}
void total_despesas(Despesas d){

		float recebeu;

			printf("Informe um mes que deseja consultar as despesas : ");
			int mes_pag=meses();

			if(mes_pag==1){
				recebeu=d.janeiro;
					printf("\nDespesas em janeiro %.2f\n",recebeu);
				}
				else if (mes_pag==2){
					recebeu=d.fevereiro;
					printf("\nDespesas em fevereiro %.2f\n",recebeu);
				}
				else if (mes_pag==3){
					recebeu=d.marco;
					printf("\nDespesas em mar�o %.2f\n",recebeu);
				}
				else if (mes_pag==4){
					recebeu=d.abri;
					printf("\nDespesas em abril %.2f\n",recebeu);
				}
				else if (mes_pag==5){
					recebeu=d.maio;
					printf("\nDespesas em maio %.2f\n",recebeu);
				}
				else if (mes_pag==6){
					recebeu=d.jun;
					printf("\nDespesas em junho %.2f\n",recebeu);
				}
				else if (mes_pag==7){
				   recebeu=d.jul;
					printf("\nDespesas em julho %.2f\n",recebeu);
				}
				else if (mes_pag==8){
					recebeu=d.ago;
					printf("\nDespesas em Agosto %.2f\n",recebeu);
				}
				else if (mes_pag==9){
					recebeu=d.set;
					printf("\nDespesas em setembro %.2f\n",recebeu);
				}
				else if (mes_pag==10){
					recebeu=d.out;
					printf("\nDespesas em outubro %.2f\n",recebeu);
				}
				else if (mes_pag==11){
					recebeu=d.nov;
					printf("\nDespesas em Novembro %.2f\n",recebeu);
				}
				else if (mes_pag==12){
					recebeu=d.dez;
					printf("\nDespesas em dezembro %.2f\n",recebeu);
			}
		}

Lista* carregar(Lista* Aluno) {
    FILE *file = fopen("teste.txt", "r");

    char nome[81];
	char sexo[2];
	char cpf[12];
	char idade[3];
	char celular[20];
	char cidade[81];
	char email[30];
	char data[12];
	char alt[4];
	char biceps[4];
	char coxa[4];
	char kg[4];
	char peito[4];
	file = fopen("teste.txt", "r");
    if (file == NULL) {
        printf("Erro, n�o foi possivel abrir o arquivo\n");
    } else {
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", nome,sexo,cpf,idade,celular,cidade,email,data,alt,biceps,coxa,kg,peito) != EOF) {
            Lista* nova = (Lista*) malloc(sizeof(Lista));
   //         if (nome[0] >= 33) {
                strcpy(nova->nome, nome);
                strcpy(nova->sexo, sexo);
                strcpy(nova->cpf,cpf);
                strcpy(nova->idade,idade);
                strcpy(nova->celular,celular);
                strcpy(nova->cidade,cidade);
                strcpy(nova->email,email);
                strcpy(nova->data,data);
                strcpy(nova->medidas.alt,alt);
                strcpy(nova->medidas.biceps,biceps);
                strcpy(nova->medidas.coxa,coxa);
                strcpy(nova->medidas.kg,kg);
                strcpy(nova->medidas.peito,peito);
                nova->prox = Aluno;
                Aluno = nova;
            //}
        }
    }
    fclose(file);
    return Aluno;
}

void salvartudo(Lista* Aluno) {
    FILE *file = fopen("teste.txt", "w");
    if (file == NULL) {
        printf("Houve um erro ao abrir o arquivo.\n");
        exit(1);
    } else {
        Lista* aux;
        for (aux = Aluno; aux != NULL; aux = aux->prox) {
            fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n", aux->nome, aux->sexo,aux->cpf, aux->idade,aux->celular,aux->cidade,aux->email, aux->data, aux->medidas.alt, aux->medidas.biceps, aux->medidas.coxa, aux->medidas.kg, aux->medidas.peito);
        }
        fclose(file);
    }
}



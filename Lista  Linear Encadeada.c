#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64

//Espera 3 segundos
#define ESPERA sleep(3)

#define LIMPA_TELA system("cls")
//Estrutura da lista que será criada
typedef struct lista {
    char *nome;
    int matricula;
    struct lista *proximo;
} Dados;

//Funções para manusear os dados (irão retornar dados)
Dados *inicia_dados  (char *nome, int idade);
Dados *insere_dados  (Dados *dados, char *nome, int idade);
Dados *delbusca_dados(Dados *dados, char *chave);
Dados *deleta_dados  (Dados *dados, int nTipo);
int   checa_vazio    (Dados *dados);

//Funções para mostrar dados
void  exibe_dados    (Dados *dados);
void  exibe_tamanho  (Dados *nova);
void  busca_dados    (Dados *dados, int chave);

Dados *principal = NULL;

void criavazia(void){
    char *nome;
    int matricula;
    //Alocando dados para uma String
    nome = (char *)malloc(BUFFER);
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    fprintf(stdout, "\n");
    fprintf(stdout, "Digite a matricula: \n----> ");
    scanf("%d", &matricula);
    fprintf(stdout, "\n");
    //Lançando os dados lidos na lista Principal

    principal = inicia_dados(nome, matricula);
}

//Iniciando os dados da lista vazia
Dados *inicia_dados(char *nome, int matricula) {
    Dados *novo;
    //Alocando memória para a posição atual da lista
    novo = (Dados *)malloc(sizeof(Dados));
    //Lançando os dados lidos
    novo->nome = (char *)malloc(strlen(nome)+1);
    strncpy(novo->nome, nome, strlen(nome)+1);
    novo->matricula = matricula;
    //Apontando para a próxima posição da lista
    novo->proximo = NULL;
    return novo;
}

void insereinicio(void){
    char *nome;
    int matricula;
    //Reservando espaço para String
    nome = (char *)malloc(BUFFER);
    //Armazenando String Nome
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    fprintf(stdout, "\n");
    fprintf(stdout, "Digite a matricula: \n----> ");
    scanf("%d", &matricula);
    fprintf(stdout, "\n");
    //Lançando dados no ínicio da lista
    principal = insere_dados(principal, nome, matricula);
}

//Inserindo dados recebidos
Dados *insere_dados(Dados *dados, char *nome, int matricula) {
    Dados *inicio;
    inicio = (Dados *)malloc(sizeof(Dados));
    inicio->nome = (char *)malloc(strlen(nome)+1);
    strncpy(inicio->nome, nome, strlen(nome)+1);
    inicio->matricula = matricula;
    inicio->proximo = dados;
    return inicio;
}


void inserefim(void) {
    char *nome;
    int matricula;
    //Alocação de espaço para String Nome
    nome = (char *)malloc(BUFFER);
    //Armazenando String Nome
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    fprintf(stdout, "\n");
    fprintf(stdout, "Digite a matricula: \n----> ");
    scanf("%d", &matricula);
    fprintf(stdout, "\n");
    //Criando listas auxiliares
    Dados *final,*aux;
    //Alocando dados para a posição final da lista
    final = (Dados *)malloc(sizeof(Dados));
    final->nome = (char *)malloc(strlen(nome)+1);
    strncpy(final->nome, nome, strlen(nome)+1);
    final->matricula = matricula;
    final->proximo=NULL;
    aux=principal;
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=NULL;
    aux->proximo=final;
}

void listavazia(void){
    if (principal == NULL)
        fprintf(stdout, "\n\nLista esta Vazia!\n\n ");
    else
        fprintf(stdout, "\n\nLista nao esta Vazia!\n\n ");
    getchar();
}

void exibe(void) {
    if (!checa_vazio(principal))
        exibe_dados(principal);
}

//Exibindo todos os dados do menu
void exibe_dados(Dados *dados) {
    fprintf(stdout, "Cadastro:\n\n");
    fprintf(stdout, "------------------------\n");
    //Exibindo todos os valores da lista
    for (; dados != NULL; dados = dados->proximo) {
        fprintf(stdout, "Nome: %s\n", dados->nome);
        fprintf(stdout, "Matricula: %d\n", dados->matricula);
        fprintf(stdout, "------------------------\n");
    }
    getchar();
}

void delbusca(void) {
    char *chave;
    if (!checa_vazio(principal)) {
        chave = (char *)malloc(BUFFER);
        //Armazenando o valor digitado
        fprintf(stdout, "Digite o nome para buscar: \n --> ");
        scanf("%s", chave);
        //Deletando a chave buscada
        principal = delbusca_dados(principal, chave);
    }
}

Dados *delbusca_dados(Dados *dados, char *chave) {
    int achou=0,cont=0;
    Dados *juntou, *aux, *nova=dados;
    for (; nova != NULL; nova = nova->proximo) {
        if (strcmp(chave, nova->nome) == 0) {
            achou=1;
            cont++;
        }
    }
    if(achou==1){
        int ind=0;
        for(ind=0;ind<cont;ind++){
            if(strcmp(chave,dados->nome)==0){
                aux=dados;
                dados=dados->proximo;
                free(aux);
            }
            else{
                aux=dados;
                while(strcmp(chave,aux->nome)!=0){
                    aux=aux->proximo;
                }

                juntou=dados;
                while(juntou->proximo!=aux){
                    juntou=juntou->proximo;
                }
                //Aponta para o próximo valor válido
                juntou->proximo=aux->proximo;

                free(aux);
            }
        }
        fprintf(stdout, "Excluido.\n");
    }
    else
        fprintf(stdout, "Nenhum resultado encontrado.\n");

    getchar();
    return dados;
}

void busca_dados(Dados *dados, int chave) {
    int achou = 0;

    for (; dados != NULL; dados = dados->proximo) {
        if ((chave == dados->matricula)) {
            fprintf(stdout, "------------------------\n");
            fprintf(stdout, "Nome: %s\n", dados->nome);
            fprintf(stdout, "Matricula: %d\n", dados->matricula);
            fprintf(stdout, "------------------------\n");
            achou++;
        }
    }

    if (achou == 0)
        fprintf(stdout, "Nenhum resultado encontrado.\n");
    else
        fprintf(stdout, "Foram encontrado(s) %d registro(s).\n", achou);

    getchar();
}

void limpa_lista() {
    Dados *dados = principal, *aux;
    while (dados != NULL)
    {
        aux = dados;
        dados = dados->proximo;
        free (aux);
    }
    principal = NULL;

}

int checa_vazio(Dados *dados) {
    //Se a lista estiver vazia
    if (dados == NULL) {
            fprintf(stdout, "Lista vazia!\n");
            getchar();
            return 1;
    } else
            return 0;
}

int main(void) {
    char escolha;
    int chave=0;
    do {

        LIMPA_TELA;
        fprintf(stdout, "\n\t\tCadastro de Clientes\n\n");
        fprintf(stdout, "Escolha uma opcao: \n");
        fprintf(stdout, "1 - Criar lista vazia\n");
        fprintf(stdout, "2 - Inserir no Inicio de uma lista\n");
        fprintf(stdout, "3 - Inserir no Fim de uma lista\n");
        fprintf(stdout, "4 - Verifica se a lista  esta vazia...\n");
        fprintf(stdout, "5 - Exibir todos os valores da Lista\n");
        fprintf(stdout, "6 - Eliminar nodo buscado\n");
        fprintf(stdout, "7 - Busca Dados\n");
        fprintf(stdout, "8 - Limpar a lista\n");
        fprintf(stdout, "s - Para Sair\n\n");

        fprintf(stdout, "Resposta: ");
        scanf("%c", &escolha);

        switch(escolha) {
            case '1':
                chave=1;
                criavazia();
                break;
            case '2':
                insereinicio();
                break;
            case '3':
                if(principal!=NULL){
                    inserefim();
                }
                else{
                    insereinicio();
                }
                break;
            case '4':
                listavazia();
                break;
            case '5':
                exibe();
                break;

             case '6':
                delbusca();
                break;

            case '7':
                fprintf(stdout, "Digite uma matricula para buscar: \n--> ");
                    scanf("%d", &chave);
                    busca_dados(principal, chave);

                break;

            case '8':
                limpa_lista();

            break;

            case 's':
                fprintf(stderr,"finalizado!\n");
                exit(0);
                break;
            case 'S':
                fprintf(stderr,"finalizado!\n");
                exit(0);
                break;

            default:
                fprintf(stderr,"Digite uma opcao valida (pressione -Enter- p/ continuar)!\n");
                getchar();
                break;
        }

        getchar();
    }
    while (escolha > 0);
    return 0;
}

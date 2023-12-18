#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sPasta{
    char nome[31];
    int arquivos;
}Pasta;

typedef struct sNo{
    Pasta info;
    int fb;
    struct sNo *esq;
    struct sNo *dir;
}NO;

void inicializar(NO **raiz){
    *raiz=NULL;
}

NO *alocarNO(){
    return(NO*)malloc(sizeof(NO));
}

NO *desalocarNO(NO*q){
    free(q);
}

void avl_RotDir(NO **raiz){
   NO *aux;
   aux = (*raiz)->esq;
   (*raiz)->esq = aux->dir;
   aux->dir = *raiz;
   (*raiz)->fb = 0;
   *raiz = aux;
}

void avl_RotEsqDir(NO **raiz){
   NO *fE;
   NO *ffD;
   fE = (*raiz)->esq;
   ffD = fE->dir;

  fE->dir = ffD->esq;
  ffD->esq = fE;

  (*raiz)->esq = ffD->dir;
  ffD->dir = *raiz;

  if(ffD->fb == +1)
    (*raiz)->fb = -1;
  else
    (*raiz)->fb = 0;

  if(ffD->fb == -1)
     fE->fb = +1;
  else
     fE->fb = 0;

  *raiz = ffD;
}

void avl_Aux1(NO **raiz){
   NO* fE;
   fE = (*raiz)->esq;

   if(fE->fb == +1){
     /* Sinais iguais e positivo*/
     avl_RotDir(&(*raiz));
   }else
     /* Sinais diferentes*/
     avl_RotEsqDir(&(*raiz));
   (*raiz)-> fb = 0;
}

void avl_RotEsq(NO **raiz){
  NO *aux;
   aux = (*raiz)->dir;
   (*raiz)->dir = aux->esq;
   aux->esq = *raiz;
   (*raiz)->fb = 0;
   *raiz = aux;
}

void avl_RotDirEsq(NO **raiz){
    NO *fE;
    NO *ffD;
    fE = (*raiz)->esq;
    ffD = fE->dir;

    (*raiz)->esq = ffD->dir;
    ffD->dir = *raiz;
    fE->dir = ffD->esq;
    ffD->esq = fE;

    if(ffD->fb == +1){
    (*raiz)->fb = -1;
  }else
    (*raiz)->fb = 0;

    if(fE->fb == -1){
     ffD->fb = +1;
  }else
     ffD->fb = 0;

    *raiz = fE;
}

void avl_Aux2(NO **raiz){
    NO* fD;
    fD=(*raiz)->dir;
    if(fD->fb==+1){
        avl_RotEsq(&(*raiz));
    }else
        avl_RotDir(&(*raiz));
            (*raiz)->fb=0;
}


int avl_inserir(NO **raiz, Pasta elem){
    int ok;

    if(*raiz==NULL){
        *raiz=alocarNO();
        if(*raiz==NULL){
            printf("Problema na alocacao\n");
            return 0;
        }
        (*raiz)->esq=NULL;
        (*raiz)->dir=NULL;
        (*raiz)->info=elem;
        (*raiz)->fb=0;
        return 1;
    }
    if(elem.arquivos<(*raiz)->info.arquivos){
        ok=avl_inserir(&(*raiz)->esq, elem);
        if(ok){
            switch((*raiz)->fb){
            case -1:
                (*raiz)->fb=0;
                ok=0;
                break;
            case 0:
                (*raiz)->fb=+1;
                break;
            case +1:
                avl_Aux1(&(*raiz));
                ok=0;
                break;

            }
        }
    }
else if(elem.arquivos>(*raiz)->info.arquivos){
    ok=avl_inserir(&(*raiz)->dir,elem);
    if(ok){
        switch((*raiz)->fb){
        case+1:
            (*raiz)->fb=0;
            ok=0;
            break;
        case 0:
            (*raiz)->fb=-1;
            break;
        case -1:
            avl_Aux2(&(*raiz));
            ok=0;
            break;

        }
    }

else
    ok=0;
    return ok;
    }
}

void em_ordem(NO *raiz){
    if (raiz != NULL)
   {
        em_ordem(raiz->esq);
        printf("Nome: %s\n", raiz->info.nome);
        printf("Numero de arquivos: %d \n", raiz->info.arquivos);
        em_ordem(raiz->dir);
   }
}

void pos_ordem(NO *raiz){
    if (raiz != NULL)
    {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("Nome: %s\n", raiz->info.nome);
        printf("Numero de arquivos: %d \n", raiz->info.arquivos);
    }
}

int main (){
    NO *ptRaiz;
    int opcao;
    Pasta x;
    inicializar(&ptRaiz);

    do{
            printf("Selecione uma das opcoes abaixo:  \n");
            printf("1 - Inserir um elemento na arvore AVL \n");
            printf("2 - Exibir em_ordem na arvore AVL \n");
            printf("3 - Exibir em pos_ordem na arvore AVL \n");
            printf("4 - Sair \n");
            printf("--> ");

            scanf("%d", &opcao);

         switch(opcao){
            case 1:
                    fflush(stdin);
                    printf("\nDigite o nome da pasta: \n");
                    printf("--> ");
                    scanf("%s", &x.nome);
                    fflush(stdin);
                    printf("Digite o numero de arquivos da pasta: \n");
                    printf("--> ");
                    scanf("%d", &x.arquivos);

                    avl_inserir(&ptRaiz, x);
                    printf("\n** Pasta inserido com sucesso**\n\n");
                break;
            case 2:
                    printf("Impressao: \n");
                    em_ordem(ptRaiz);
                    printf("\n");
                break;
            case 3:
                    printf("Impressao: \n");
                    pos_ordem(ptRaiz);
                    printf("\n");
                break;
            default:
                printf("Encerrando o programa\n");
                break;
            }

    }while(opcao!=4);

return 0;

}
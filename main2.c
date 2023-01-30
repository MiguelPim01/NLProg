#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/indices.h"
#include "headers/palavra.h"
#include "headers/indicePalavras.h"
#include "headers/arrayBusca.h"
#include "headers/documento.h"

#define FLAG_CLASSIFICADOR 1

int main(int argc, char *argv[])
{
    FILE *fileBin;
    Indices *indices = NULL;
    IndicePalavras *palavrasBuscadas = NULL;
    ArrayBusca *arrayB = NULL;

    char caminho[100], texto[100], *token;
    caminho[0]='\0'; texto[0]='\0';

    if (argc <= 2)
    {
        printf("ERRO: Quantidade insuficiente de argumentos dados\n");
        printf("Para rodar corretamente: ./prog2 <arquivo_indices.bin> <numero_K>\n");
        return 1;
    }

    sprintf(caminho, "%s", argv[1]);
    fileBin = fopen(caminho, "rb");

    if (fileBin == NULL)
    {
        printf("ERRO: Não foi possivel abrir o arquivo %s\n", caminho);
        return 1;
    }

    // LENDO E ARMAZENANDO OS INDICES DE DOCS E PALAVRAS:
    indices = CarregaIndicesBin(indices, fileBin);

    
    // FUNCIONAMENTO DO PROGAMA:

    char opcao;

    printf("1 - Buscar Noticia\n");
    printf("2 - Classificar Noticia\n");
    printf("3 - Relatorio da Palavra\n");
    printf("4 - Relatorio do Documento\n");
    printf("Escolha uma opcao: ");
    scanf("%c", &opcao);
    scanf("%*[^\n]");
    scanf("%*c");

    switch (opcao)
    {
        case '1': // BUSCAR NOTICIA (20% nota)
            palavrasBuscadas = InicializaIndicePalavras(palavrasBuscadas);
        
            printf("\nBusque algo: ");

            scanf("%[^\n]", texto);
            token = strtok(texto, " ");

            printf("\n");

            while (token)
            {
                AdicionaPalavraBuscada(palavrasBuscadas, RetornaArrayPalavras(indices), token);

                token = strtok(NULL, " ");
            } // Constroi array de de ponteiros para as palavras digitadas

            arrayB = InicializaArrayBusca();

            CriaArrayDeBusca_IndxPalavras(palavrasBuscadas, arrayB, RetornaIndiceDocs(indices));

            OrdenaArrayBusca(arrayB);

            PrintaResultadoDaBusca(arrayB);

            LiberaIndicePalavrasBuscadas(palavrasBuscadas);
            LiberaArrayBusca(arrayB);
            break;
        case '2': // CLASSIFICAR NOTICIA (30% nota)
            Documento *noticiaDigitada = InicializaDocumento_classificador(); 
            palavrasBuscadas = InicializaIndicePalavras(palavrasBuscadas);
            double *cossenos;

            printf("\nDigite uma Noticia: ");

            scanf("%[^\n]", texto);
            token = strtok(texto, " ");

            printf("\n");

            while (token)
            {
                CriaIndicePalavras_classificador(palavrasBuscadas, RetornaArrayPalavras(indices), token, RetornaIndiceDocs(indices));

                token = strtok(NULL, " ");
            } // Realiza a criacao do documento para a classificador de classe

            AtribuiTf_idfIdxPalavras(RetornaArrayPalavras(indices), RetornaIndiceDocs(indices), FLAG_CLASSIFICADOR);

            CriaDoc_classificador_indPalavras(palavrasBuscadas, noticiaDigitada, RetornaArrayPalavras(indices));

            cossenos = CriaArrayCossenos(RetornaIndiceDocs(indices), noticiaDigitada);

            

            free(cossenos);
            LiberaDoc(noticiaDigitada);
            LiberaIndicePalavrasBuscadas(palavrasBuscadas);
            break;
        case '3': // RELATORIO DA PALAVRA (5% nota)
            break;
        case '4': // RELATORIO DO DOCUMENTO (5% nota)
            break;
        default:
            printf("ERRO: Opcao Invalida!\n");
            break;
    }

    // LIBERANDO MEMORIA:
    LiberaIndices(indices);

    // FECHANDO ARQUIVO:
    fclose(fileBin);


    return 0;
}
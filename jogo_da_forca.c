#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char chutes[TAMANHO_ALFABETO];
int qtdpalavra[TAMANHO_ALFABETO];
char palavrasegreda[TAMANHO_PALAVRA];
int indiceqtdpalavra = 0;
int chutesdados = 0;
int ganhou = 1;
int erros = 0;

void abertura()
{
    printf("\n\n                                 *****************\n");
    printf("                                 * JOGO DA FORCA *\n");
    printf("                                 *****************\n\n");

    printf("                                   DICA:FRUTAS    \n\n");
}
void teladevitoria() 
{
    printf("\nParabéns, você ganhou!\n\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}
void teladederrota() 
{
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasegreda);
    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
}
void chuta()
{
    char chute;
    scanf(" %c", &chute);
    chutes[chutesdados] = chute;
    chutesdados++;
}
void adicionapalavra()
{
    char quer;
    printf("Deseja adicionar uma nova palavra no arquivo? (s/n):");
    scanf(" %c", &quer);

    if (quer == 's')
    {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Digite a nova palavra que deseja adicionar :");
        scanf("%s",novapalavra);

        FILE* arquivo;
        arquivo = fopen("palavras_da_forca.txt","r+");
        if (arquivo == 0)
        {
            printf("Ocorreu erro ao consutar o banco de dados.");
        }

        int quantidadelinha;
        fscanf(arquivo,"%d",&quantidadelinha);
        quantidadelinha++;
        fseek(arquivo,0,SEEK_SET);
        fprintf(arquivo,"%d",quantidadelinha);

        fseek(arquivo,0,SEEK_END);
        fprintf(arquivo,"\n%s",novapalavra);

        fclose(arquivo);
    }
}
int avaliachute(char letra)
{
    int achou = 0;
    for (int j = 0; j < chutesdados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }
    return achou;
}
void personagem() {
    printf("   _____________________            \n");
    printf("  |     /               |           \n");
    printf("  |    /                |           \n");
    printf("  |   /                %c%c%c       \n",(erros >= 1 ? '(':' '),(erros >=1? '_': ' '),(erros >=1 ?')': ' '));
    printf("  |  /               %c  %c  %c     \n",(erros >= 3 ? '\\':' '),(erros >= 2 ? '|':' '),(erros >=4 ? '/':' '));
    printf("  | /                 %c%c%c%c%c    \n",(erros >= 3 ? '\\':' '),(erros >= 3 ? '_': ' '),(erros >= 2 ? '|' : ' '),
    (erros >= 4 ? '_' : ' '),(erros >= 4 ? '/' : ' '));
    printf("  |/                    %c          \n",(erros >= 2 ? '|' : ' '));
    printf("  |                     %c          \n",(erros >= 2 ? '|':' '));
    printf("  |                    %c %c        \n",(erros >= 5 ? '/': ' '),(erros >= 6 ? '\\':' '));
    printf("  |                   %c   %c       \n",(erros >= 5 ? '/': ' '),(erros >= 6 ? '\\':' '));
    printf("  |                  %c     %c      \n",(erros >= 5 ? '/': ' '),(erros >= 6 ? '\\':' '));
    printf("  |                                 \n");
    printf("  |                                 \n");
    printf("  |                                 \n");
    printf("\n\n");

}
int desenhaforca()
{

    int qtd = 0;
    int achou = 0;
    int ganhou = 1;
    printf("                            ");
    for (int i = 0; i < strlen(palavrasegreda); i++)
    {
        achou = avaliachute(palavrasegreda[i]);
        if (achou)
        {
            printf("%c", palavrasegreda[i]);
        }
        else
        {
            printf("_ ");
            ganhou = 0;
            qtd++;
        }
    }
    adicionaerros(qtd);
    printf("\n\n");
    personagem();
    return ganhou;
}

void escolhepalavra()
{

    FILE* arquivo = fopen("palavras_da_forca.txt", "r");
    if (arquivo == 0)
    {
        printf("Desculpe, tivemos problemas ao acessar o banco de dados.\n\n");
        exit(1);
    }

    srand(time(0));

    int qtddepalavras;
    fscanf(arquivo, "%d", &qtddepalavras);
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(arquivo, "%s", palavrasegreda);
    }
    qtdpalavra[indiceqtdpalavra] = strlen(palavrasegreda);
    fclose(arquivo);
}
int adicionaerros(int qtd) 
{
    if (indiceqtdpalavra >= 0)
    {
    qtdpalavra[indiceqtdpalavra] = qtd;
    int comparaletra = qtdpalavra[indiceqtdpalavra-1] == qtdpalavra[indiceqtdpalavra];
        if (comparaletra)
        {
            erros++;
        }
    }
    indiceqtdpalavra++;
}
int enforcou()
{
    if (erros > 5) return 1;
    return 0;
}

int main()
{

    abertura();
    escolhepalavra();

    do
    {
        ganhou = desenhaforca();
        if (ganhou == 0 )
        {
            chuta();
        }
    } while (!ganhou && !enforcou());
    if (ganhou)
    {
        teladevitoria();
    }else{
        teladederrota();
    }
    adicionapalavra();
}

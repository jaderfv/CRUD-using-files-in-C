#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct cadastro{
      
       int codFornecedor;
       char nomeFornecedor[20] ;
       int totalCompras ;
       int excluido;
       };
       
struct produto{
       int numFornecedor;
       int codProduto;      
       char nomeProduto[20];
       int preco;
       int quantidade;
       int excluido;
       int quantTotal;
       };
//arquivo cadastro       
void inserirFornecedor(FILE *cad); 
void alterarFornecedor(FILE *cad);
int consultaFornecedor(FILE *cad);
//arquivo produto
void inserirProduto(FILE *cad, FILE *prod);
void consultaProduto(FILE *cad, FILE *prod);
void alterarProduto(FILE *cad, FILE *prod);
void excluirProduto(FILE *cad, FILE *prod);
      
main()
{
//decalaracao das funcoes


int forn,pro;
FILE *cad, *prod;
    char nomeArquivo[25];
    int codigo,opcao;
     
    
 
     
  
          cad = fopen("c:\\temp\\cadastroFornecedor.dat", "rb+");     //abre para leitura ou gravacao
          prod = fopen("c:\\temp\\cadastroProduto.dat", "rb+"); 
     
          if( cad==NULL)
          {
              cad=fopen("c:\\temp\\cadastroFornecedor.dat", "wb+"); //cria para leitura ou gravacao
          }
          if (prod ==NULL)
          {
              prod = fopen("c:\\temp\\cadastroProduto.dat", "wb+");       
          }        
          if(cad==NULL)
	      {
            printf("\n O arquivo Fornecedor nao pode ser aberto! ");
           }
          if (prod==NULL)
          {
            printf("\n O arquivo Produto nao pode ser aberto! ");
           }

        
        
           printf("_______________BOLACHAS MARIA LTDA._______________\n");
           printf("1- Cadastro de Fornecedor:\n2- Cadastro de compras\n0- Sair\n:");
           scanf("%d",&opcao);
           
       
   while(opcao != 0)  
   {        
     switch(opcao)
     {
           case 1:
           {     
           printf ("\n_____FORNECEDOR_____\n\n");  
           printf("1-Inserir\n2-Consultar\n3-Alterar\n4-Excluir\n: ");
           scanf("%d", &forn);
           
           
              switch(forn)
              {//abre switch forn
                
                   case 1:
                    {
                        inserirFornecedor(cad);
                        break;
                    }
                   case 2:
                    {
                         consultaFornecedor(cad);
                         break;
                    }
                   case 3:
                    {
                         alterarFornecedor(cad);
                         break;
                    } 
                   case 4:
                    {
                         printf("PROIBIDO EXCLUIR FORNECEDOR!"); 
                         break;    
                    }
                    
              }// fecha switch forn
              break;
           }
           
          case 2:
               {
                printf ("\n_____PRODUTO_____\n\n");  
                printf("1-Inserir\n2-Consultar\n3-Alterar\n4-Excluir\n: "); 
                scanf("%i", &pro);
                             switch(pro)
                              {//abre switch pro
                                case 1:
                                 {
                                   inserirProduto(cad,prod);  
                                   break;  
                                 }
                                case 2:
                                 {
                                   consultaProduto(cad,prod);
                                   break;
                                 }
                                 case 3:
                                 {
                                   alterarProduto(cad, prod);   
                                   break;
                                 } 
                                 case 4:
                                 {
                                      excluirProduto(cad,prod);
                                   break;
                                 }                    
                              }
               }//fecha case 2 switch opcao
                  
     }//fecha switch opcao  
    printf("\n1- Cadastro de Fornecedor:\n2- Cadastro de compras\n0- Sair\n:");
    scanf("%d",&opcao);      
          
   }//fecha while
            
 fclose(cad);
 fclose(prod);       
 
 getch();
   
}
void inserirFornecedor(FILE *cad) //funcao INSERIR FORNECEDOR
{
  struct cadastro c;
  
  printf("Digite o codigo do fornecedor:");
  fflush(stdin);
  scanf("%i", &c.codFornecedor);
  printf("Digite o nome do fornecedor:"); 
  fflush(stdin);
  gets(c.nomeFornecedor); 
  c.totalCompras = 0;
  
  
  rewind( cad ); // recoloca o indicador de posicao no inicio do arquivo
  fseek( cad, c.codFornecedor * sizeof( struct cadastro ), SEEK_CUR ); // posiciona o arquivo na posicao que ficara o registro, conforme codigo
  fwrite( &c, sizeof(struct cadastro), 1, cad ); // grava o registro no final do arquivo, uma gravacao de arquivo
  printf("\n CADASTRO EFETUADO COM SUCESSO! \n");

     
}
int consultaFornecedor(FILE *cad)
{
struct cadastro c;
    int cod; // codigo= a ser consultado no arquivo
    int pos;    // posição do ponteiro no arquivo
    
    
    printf("Informe o codigo:");// dados que sera procurado no arquivo
    fflush(stdin);          // limpa buffer de entrada
    scanf( "%i", &cod );
    
    rewind( cad );     // recoloca o indicador de posicao no inicio do arquivo
    fseek( cad, cod * sizeof( struct cadastro ), SEEK_CUR ); // posiciona no registro com codigo procurado
    pos= ftell( cad ); // para ver a posicao do ponteiro no arquivo

    fread( &c, sizeof( struct cadastro  ), 1, cad );          // le o registro
    if( c.codFornecedor == cod  )   // verifica se registro foi excluido logicamente
    {
        printf( "\n Codigo: %i", c.codFornecedor);
        printf( "\n Nome do Fornecedor: %s", c.nomeFornecedor );
        printf( "\n Total de compras: %i\n\n", c.totalCompras);
    }
    else
        printf("\n Registro nao encontrado!\n ");
        
    return cod;
}
void alterarFornecedor(FILE *cad)
{
     struct cadastro c;
     int codigo;    // codigo a ser alterado no arquivo
     
     printf("|Alteracao de cadastro|");
     codigo= consultaFornecedor(cad); // procura pelo registro que sera alterado

     rewind( cad ); // recoloca o indicador de posicao no inicio do arquivo
     fseek( cad, codigo * sizeof( struct cadastro ), SEEK_SET); // posiciona no registro que sera alterado
     fread( &c, sizeof( struct cadastro ), 1, cad );          // le registro que sera alterado
    
     if( c.codFornecedor == codigo && codigo != 0 )
     {
         printf( "\n\n Novo Nome: " );
         fflush( stdin );
         gets(c.nomeFornecedor );
     } // verifica se registro foi excluido logicamente
     
     
     rewind( cad ); // recoloca o indicador de posicao no inicio do arquivo
     fseek( cad, codigo * sizeof( struct cadastro ), SEEK_SET); // posiciona no registro que sera alterado
     fwrite( &c, sizeof( struct cadastro ), 1, cad);          // grava alteracao
     printf( "\n Registro alterado! \n" ); 
}
void inserirProduto(FILE *cad, FILE *prod)
{    
    int cod; // codigo = a ser consultado no arquivo
    int pos;    // posição do ponteiro no arquivo
    struct produto p;
    struct cadastro c;
    
    
    printf("Informe o codigo do fornecedor:");// dados que sera procurado no arquivo
    fflush(stdin);          // limpa buffer de entrada
    scanf( "%i", &cod );
    
    rewind( cad );     // recoloca o indicador de posicao no inicio do arquivo
    fseek( cad, cod * sizeof( struct cadastro ), SEEK_CUR ); // posiciona no registro com codigo procurado
    pos= ftell( cad ); // para ver a posicao do ponteiro no arquivo
    fread( &c, sizeof( struct cadastro  ), 1, cad );
    
     if ( c.codFornecedor == cod)
     {
     p.numFornecedor = c.codFornecedor;//associa produto ao fornecedor para consulta
     printf("Fornecedor: %s", c.nomeFornecedor);
     printf("\nDigite o codigo do produto:");
     fflush(stdin);
     scanf("%i", &p.codProduto );
     printf("\nDigite o nome do produto:"); 
     fflush(stdin);
     gets(p.nomeProduto);
     printf("\nPreco:");
     fflush(stdin);
     scanf("%i", &p.preco);
     printf("\nQuantidade comprada:");
     fflush(stdin);
     scanf("%i", &p.quantidade);
     p.excluido = 0;
     

     
     rewind( prod ); // recoloca o indicador de posicao no inicio do arquivo
     fseek( prod, p.codProduto * sizeof( struct produto ), SEEK_CUR ); // posiciona o arquivo na posicao que ficara o registro, conforme codigo
     fwrite( &p, sizeof(struct produto), 1, prod); // grava o registro no final do arquivo, uma gravacao de arquivo
     printf("\n CADASTRO EFETUADO COM SUCESSO! \n");
     
     c.totalCompras = c.totalCompras+(p.quantidade*p.preco); //atualiza total de compras na consulta fornecedor
    
     rewind( cad ); // recoloca o indicador de posicao no inicio do arquivo
     fseek( cad, c.codFornecedor * sizeof( struct cadastro ), SEEK_CUR ); // posiciona o arquivo na posicao que ficara o registro, conforme codigo
     fwrite( &c, sizeof(struct cadastro), 1, cad); // grava o registro no final do arquivo, uma gravacao de arquivo
     }
     else 
     {
          printf("\n FORNECEDOR NAO ENCONTRADO!");
     }    
  
}
void consultaProduto(FILE *cad,FILE *prod)   
{
  int codigo; // codigo= a ser consultado no arquivo
  int pos;    // posição do ponteiro no arquivo
  struct produto p; 
    
    printf("Informe o codigo do produto:");// dados que sera procurado no arquivo
    fflush(stdin);          // limpa buffer de entrada
    scanf( "%i", &codigo );
    
    rewind( prod );     // recoloca o indicador de posicao no inicio do arquivo
    fseek( prod, codigo * sizeof( struct produto ), SEEK_CUR ); // posiciona no registro com codigo procurado
    pos= ftell( prod ); // para ver a posicao do ponteiro no arquivo
    fread( &p, sizeof( struct produto  ), 1, prod );          // le o registro  
    
    if( p.codProduto == codigo && p.excluido == 0 )   
    {
        printf("\n Fornecedor: %i",p.numFornecedor);
        printf("\n Nome do produto: %s", p.nomeProduto);
        printf("\n Preco: %i", p.preco);
        printf("\n Última quantidade comprada: %i\n\n", p.quantidade);
        
    }
    else if(p.excluido != 0)
    {
         printf("PRODUTO EXCLUIDO!");
    }    
    else
    {
        printf("\n PRODUTO NAO ENCONTRADO!\n "); 
    }
     
} 
void alterarProduto(FILE *cad, FILE *prod)      
{    
    int cod, pos,opcao;
    struct produto p;
     
    printf("|ALTERACAO DE PRODUTO|\n\n"); 
    printf("Informe o codigo do produto:");// dados que sera procurado no arquivo
    fflush(stdin);          // limpa buffer de entrada
    scanf( "%i", &cod );
    
    rewind( prod );     // recoloca o indicador de posicao no inicio do arquivo
    fseek( prod, cod * sizeof( struct produto ), SEEK_CUR ); // posiciona no registro com codigo procurado
    pos= ftell( prod ); // para ver a posicao do ponteiro no arquivo
    fread( &p, sizeof( struct produto  ), 1, prod );          // le o registro
    
            if (p.codProduto == cod && p.excluido == 0)
             {
               printf("1-Alterar nome do produto\n2-Alterar preco\n3-Alterar quantidade do produto\n:");
               scanf("%i",&opcao);
                        switch (opcao)
                        {
                               case 1:
                               {
                                    printf("Digite o nome do produto:");
                                    fflush(stdin);
                                    gets(p.nomeProduto);
                                    break;
                                }
                               case 2:
                               {
                                    printf("Digite o preco do produto:");
                                    scanf("%i", &p.preco);
                                    break;
                               }
                               case 3:
                               {
                                    printf("Digite a quantidade do produto:");
                                    scanf("%i", &p.quantidade);
                                    break;
                               }
                        }                         
               rewind( prod ); // recoloca o indicador de posicao no inicio do arquivo
               fseek( prod, cod * sizeof( struct produto), SEEK_SET); // posiciona no registro que sera alterado
               fwrite( &p, sizeof( struct produto ), 1, prod);          // grava alteracao
               printf( "\n Registro alterado! \n" ); 
             }
             else
             {
                 printf("PRODUTO NAO ENCONTRADO!");
             }                                       
}
void excluirProduto(FILE *cad, FILE *prod)    
{
    struct produto p;
    int cod,pos;
     
    printf("|EXCLUSAO DE PRODUTO|\n\n"); 
    printf("Informe o codigo do produto:");// dados que sera procurado no arquivo
    fflush(stdin);          // limpa buffer de entrada
    scanf( "%i", &cod );
    
    rewind( prod );     // recoloca o indicador de posicao no inicio do arquivo
    fseek( prod, cod * sizeof( struct produto ), SEEK_CUR ); // posiciona no registro com codigo procurado
    pos= ftell( prod ); // para ver a posicao do ponteiro no arquivo
    fread( &p, sizeof( struct produto  ), 1, prod );          // le o registro 
    
    if (p.codProduto == cod)
    {
       p.excluido = 1 ;             
       printf("\nPRODUTO EXCLUIDO COM SUCESSO!");
       
       rewind( prod ); // recoloca o indicador de posicao no inicio do arquivo
       fseek( prod, cod * sizeof( struct produto), SEEK_SET); // posiciona no registro que sera alterado
       fwrite( &p, sizeof( struct produto ), 1, prod);          // grava alteracao
    }
    else
    {
        printf("\nPRODUTO NAO ENCONTRADO!");
    }                   
}     

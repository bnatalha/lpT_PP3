/**
* @file
* @brief Onde fica a função principal que realiza a tarefa do item (3).
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 26/06/2017
* @date --
* @sa --
*/

#include "header.h"
#include "Produto.h"
#include "Produto_tipos.h"
#include "Cesta.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

// objetivo :
//./exportar -t <tipo>(opcional) -f <fornecedor>(opcional) --full(opcional) <arquivo_saida>(obrigatorio)


void mostrar_ajuda(char *s);

bool nao_eh_flag(char operacao, char* meu_argumento);
bool valid_arg(char operacao, char* meu_argumento);

void export_cesta();

static int full_flag = 0;	//
static int fornecerdor_flag = 0;	//
static int tipo_flag = 0;	//
//static int arquivo_flag = 0;	//
static string meutipo, meufornecedor, meuarquivo; //

/*
//const struct long_options[] = {
struct option long_options[] {
	{"tipo", required_argument, &tipo_flag, 't'},
	{"fornecedor", required_argument, &fornecerdor_flag, 'f'},
	{"full", no_argument, &full_flag, 'u'},
	{0, 0, 0, 0},
} ;
*/

/**
* @brief Função principal de exportação
*/
int main (int argc,char *argv[])
{
	char opt;

	if(argc == 1)
	{
		cout << "Nenhum argumento passado." << endl;
		mostrar_ajuda(argv[0]);
		exit(1);
	}
/*
	const struct option long_options[] {
		{"tipo", required_argument, &tipo_flag, 't'},
		{"fornecedor", required_argument, &fornecerdor_flag, 'f'},
		{"full", no_argument, &full_flag, 'u'},
		{0, 0, 0, 0},
	} ;
*/
		const struct option long_options[] {
		{"tipo", required_argument, &tipo_flag, 't'},
		{"fornecedor", required_argument, &fornecerdor_flag, 'f'},
		{"full", no_argument, &full_flag, 'u'},
		{0, 0, 0, 0},
	} ;

    
    while ( (opt=getopt_long(argc, argv, "t:f:", long_options, NULL)) > 0 ) {
        switch ( opt ) {
            case 't':	//tipo
            	if(valid_arg(opt,optarg))
                {
                	meutipo = optarg;
                	tipo_flag = 1 ;
                }
                break ;
            case 'f':
                if(valid_arg(opt,optarg))
                {
                	meufornecedor = optarg;
                	fornecerdor_flag = 1 ;
                }else{
                	cout << opt << ": [argumento inválido]. \""<< optarg << "\" é o nome de uma flag." << endl;
                	exit(1);
                }
                break ;
            case 'u':
                full_flag = 1 ;
                break ;
            default:
				mostrar_ajuda(argv[0]);
				break;
        }
    }

    cout << "tipo(" << tipo_flag << "):" << meutipo << endl;
    cout << "fornecedor(" << fornecerdor_flag<< "):" << meufornecedor << endl;
    cout << "full(" << full_flag << "): type on?" << tipo_flag << endl;

    // [Throw] invalid argument
    if(full_flag and !tipo_flag){
    	cout << "--full: deve ser utilizado com -t. Veja a ajuda:" << endl;
    	mostrar_ajuda(argv[0]);
    }
    // [Throw] invalid argument
	if(optind == argc)
		cout << "Arquivo de saída não foi passado." << endl;
	// [Throw] invalid argument
	else if (optind+1 < argc)
		cout << "Muitos argumentos passados. Tente novamente." << endl;	
	// [Throw] invalid argument
	else if (optind+1 == argc){
		meuarquivo = argv[optind];
		cout << "Salvando em \"" << meuarquivo << "\"" << endl;
	}

	// Programa de exportação será executado.
	export_cesta();

	cout << ">>>Saindo do programa..." << endl;
	return 0;


}

/*funcion that show the help information*/
void mostrar_ajuda(char *s)
{
	cout<<"Como usar:       "<<s<<"./exportar -t <tipo> -f <fornecedor> --full <arquivo_saida>"<<endl;
	cout<<"arg:             "<< endl;
	cout<<"-t               "<<"(opcional)  <tipo> de produto a ser exportado (CD ou Salgado)"<<endl;
	cout<<"-f               "<<"(opcional)  apenas produtos forencidos por este <fornecedor>"<<endl;
	cout<<"--full           "<<"(opcional)  (deve ser utilizado com -t) para cada produto exportado, também seram exportados os dados especificos do seu tipo"<<endl;
	cout<<"<arquivo_saida>: "<<"OBRIGATÓRIO  nome do arquivo de saída"<<endl;
	cout<<"exemplo:         "<<s<<" -tCD --full data/out.csv"<<endl;
}

/**
* @brief Verifica se 'optarg' não é uma flag
* @param my_arg optarg a ser verificado
* @return false caso 'optarg' seja igual a "--full", "-t" ou "-f"
* e true caso contrário
*/
bool nao_eh_flag(char operacao, char* meu_argumento)
{
	//[THROW] invalid argument
	if(strcmp(meu_argumento,"--full") == 0 or
		strcmp(meu_argumento,"-t") == 0 or
		strcmp(meu_argumento,"-f") == 0)	// se o argumento for igual a uma das flags
	{
		cout << '-' << operacao << ": [argumento inválido]. \""<< meu_argumento << "\" é o nome de uma flag." << endl;
		//return false;
		exit(1);
	}
	
	return true;
}

/**
* @brief Verifica se 'optarg' é um argumento valido
* @param my_arg optarg a ser verificado
* @return false caso 'optarg' seja igual a "--full", "-t" ou "-f"
* e true caso contrário
*/
bool valid_arg(char operacao, char* meu_argumento)
{
	if(nao_eh_flag(operacao,meu_argumento))
	{
		if(operacao == 't')	// se for -t
		{
			//[THROW] invalid argument
			if(strcmp(meu_argumento, "CD") != 0 and
				strcmp(meu_argumento, "Salgado") != 0)
			{
				cout << '-' << operacao << ": [argumento inválido]. \""<< meu_argumento << "\" não é um nome de um tipo válido."<< endl;
				exit(1);
			}
			else return true;
		}

		if(operacao == 'f')	// se for -f
		{
			//recupera lista com nome de fornecedores: usa de condição
			//[THROW] invalid argument
			if(strcmp(meu_argumento, "Maria") != 0 and
				strcmp(meu_argumento, "Sony") != 0)
			{
				cout << '-' << operacao << ": [argumento inválido]. \""<< meu_argumento << "\" não existe na lista de fornecedores." << endl;
				exit(1);
			}
			else return true;
		}
	}
	return false;
}

// ======================================================================================================
// ============================================== Exportação ============================================
// ======================================================================================================

void export_cesta()
{
	Cesta estoque;	
	Cesta to_export;

	estoque.load();

	if(fornecerdor_flag and tipo_flag )
		to_export.fetch_type_and_provider_from(estoque,meutipo,meufornecedor);
	if(fornecerdor_flag and !tipo_flag )
		to_export.fetch_from(estoque,meufornecedor);
	if(!fornecerdor_flag and tipo_flag )
		to_export.fetch_from(estoque,meutipo);
	if(!fornecerdor_flag and !tipo_flag )
		to_export.load();

	to_export.export_csv(meuarquivo.c_str(), full_flag);
}

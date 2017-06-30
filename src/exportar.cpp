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
#include "Salgado.h"
#include "CD.h"
#include "Cesta.h"

//#include <unistd.h>
//#include <cstring>	//para strcmp()
//#include <cstring.h>
//#include <cstdlib.h>
#include <getopt.h>

// objetivo :
//./exportar -t <tipo>(opcional) -f <fornecedor>(opcional) --full(opcional) <arquivo_saida>(obrigatorio)


void mostrar_ajuda(char *s);

bool nao_eh_flag(char operacao, char* meu_argumento);
bool valid_arg(char operacao, char* meu_argumento);

void export_cesta();

static int full_flag = 0;	/**< Indica se a flag "--full" foi passada como argumento */
static int fornecerdor_flag = 0;	/**< Indica se a flag "-f" foi passada como argumento */
static int tipo_flag = 0;	/**< Indica se a flag "-t" foi passada como argumento */
static string meutipo;	/**< Guarda o nome do tipo passado pelo usuário como argumento da flag -t */
static string meufornecedor;	/**< Guarda o nome do fornecedor passado pelo usuário como argumento da flag -f */
static string meuarquivo;	/**< Guarda o nome do arquivo (sem extensão e sem nome de diretório) passado pelo usuário como argumento */

qlt::Cesta estoque; /**< Cesta que carregara o estoque */

/**
* @brief Função principal de exportação
*/
int main (int argc,char *argv[])
{
	char opt;	/**< recebe os argumentos marcados como flags pela operação optget_long()*/
	
	try
	{	// Exceção caso não seja passado nenhum argumento
		if(argc == 1)
			throw std::invalid_argument("Nenhum argumento passado.");
		
		// Opções longas
		const struct option long_options[] {
			{"tipo", required_argument, &tipo_flag, 't'},
			{"fornecedor", required_argument, &fornecerdor_flag, 'f'},
			{"full", no_argument, &full_flag, 'u'},
			{0, 0, 0, 0},
		} ;
	
	    // Analisando os argumentos passados
	    while ( (opt=getopt_long(argc, argv, "t:f:", long_options, NULL)) > 0 ) {
	        switch ( opt ) {
	            case 't':	//caso tenha detectado a flag seja '-t'
	            	valid_arg(opt,optarg);	// Se optarg for um argumento válido 
	               
	                meutipo = optarg;	// atribui a 'meutipo' o argumento de optarg
	                tipo_flag = 1 ;	// "sobe" a flag que avisa que -t foi detectado
	                break ;
	            case 'f': //caso opt tenha detectado a flag '-f'
	                valid_arg(opt,optarg); // Verifica se optarg for um argumento válido
	                
	                meufornecedor = optarg; // atribui a 'meufornecedor' o argumento de optarg
	                fornecerdor_flag = 1 ; // "sobe" a flag que avisa que -f foi detectado
	                
	                break ;
	            case 'u': //caso opt tenha detectado a flag --full
	                full_flag = 1 ;
	                break ;
	            default:	// Se não for nenhum dos caso
					//mostrar_ajuda(argv[0]);	// mostra ajuda de como executar o programa
	            	throw std::invalid_argument("Argumento inválido.");
					break;
	        }
	    }

	    
	    if(full_flag and !tipo_flag){
	    	cout << "--full: deve ser utilizado com -t. Veja a ajuda:" << endl;
	    	throw std::invalid_argument("");
	    }
	    if(optind == argc)	// não sobrou argumentos pra serem o nome do arquivo de saída
			throw std::invalid_argument("Arquivo de saída não foi passado.");
		else if (optind+1 < argc) // mesmo contando com o suposto que argumento que seria do nome do arquivo de saída, ainda sobra argumentos
			throw std::invalid_argument("Muitos argumentos passados. Tente novamente.");
		else if (optind+1 == argc){	// Se for o número correto de argumentos
			meuarquivo = argv[optind];	//atribui a meu arquivo
			export_cesta();	// performa a exportação com os critérios informados
			cout << endl;
		}
	} catch(std::exception &e)
	{
		cout << e.what() << endl;

		mostrar_ajuda(argv[0]);
	}

	cout << ">>> Saindo do programa..." << endl;
	return 0;
}

/**
* @brief Imprime no terminal um mini manual de como executar o programa de exportação
* @param s nome do executável
*/
void mostrar_ajuda(char *s)
{
	cout<<"Como usar:       "<<s<<"./exportar -t <tipo> -f <fornecedor> --full <arquivo_saida>"<<endl;
	cout<<"arg:             "<< endl;
	cout<<"-t               "<<"(opcional)  <tipo> de produto a ser exportado (CD ou Salgado)"<<endl;
	cout<<"-f               "<<"(opcional)  apenas produtos forencidos por este <fornecedor>"<<endl;
	cout<<"--full           "<<"(opcional)  (deve ser utilizado com -t) para cada produto exportado, também seram exportados os dados especificos do seu tipo"<<endl;
	cout<<"<arquivo_saida>: "<<"OBRIGATÓRIO  nome do arquivo de saída (sem extensão)"<<endl;
	cout<<"exemplo:         "<<s<<" -tCD --full data/out.csv"<<endl;
}

/**
* @brief Verifica se 'optarg' não é uma flag
* @param operacao flag detectado pelo opt_long
* @param meu_argumento optarg a ser verificado
* @return false caso 'optarg' seja igual a "--full", "-t" ou "-f"
* e true caso contrário
*/
bool nao_eh_flag(char operacao, char* meu_argumento)
{
	if(strcmp(meu_argumento,"--full") == 0 or
		strcmp(meu_argumento,"-t") == 0 or
		strcmp(meu_argumento,"-f") == 0)	// se o argumento for igual a uma das flags
	{
		cout << '-' << operacao << ": [argumento inválido]. \""<< meu_argumento << "\"";
		throw std::invalid_argument(" é o nome de uma flag.");
	}
	
	return true;
}

/**
* @brief Verifica se 'optarg' é um argumento valido
* @param operacao flag detectado pelo opt_long
* @param meu_argumento optarg a ser verificado
* @return false caso 'optarg' seja igual a "--full", "-t" ou "-f"
* e true caso contrário
*/
bool valid_arg(char operacao, char* meu_argumento)
{
	if(nao_eh_flag(operacao,meu_argumento))	// Se o argumento não for flag
	{
		if(operacao == 't')	// se for -t
		{
			if(strcmp(meu_argumento, "CD") != 0 and
				strcmp(meu_argumento, "Salgado") != 0)
			{
				cout << '-' << operacao << ": [argumento inválido]. \""<< meu_argumento << "\" não é um nome de um tipo válido."<< endl;
				throw std::invalid_argument(" não é um nome de um tipo válido.");
			}
			else return true;
		}
	}
	return false;
}

// ======================================================================================================
// ============================================== Exportação ============================================
// ======================================================================================================


/**
* @brief função que performa a exportação
*/
void export_cesta()
{
	qlt::Cesta to_export;	/**< Cesta que será exportada */

	estoque.load(); // Se conseguir Carregar o estoque

	if(estoque.size() > 0)
	{
		if(fornecerdor_flag and tipo_flag )	// Se tiver as flags -f e -t
			to_export.fetch_type_and_provider_from(estoque,meutipo,meufornecedor);
		if(fornecerdor_flag and !tipo_flag ) // Se entre -f e -t só tiver detectado -f
			to_export.fetch_from(estoque,meufornecedor);
		if(!fornecerdor_flag and tipo_flag ) // Se entre -f e -t só tiver detectado -t
			to_export.fetch_from(estoque,meutipo);
		if(!fornecerdor_flag and !tipo_flag )	// Se não tiver detectado nem -f ou -t
			to_export.load();

		to_export.export_csv(meuarquivo.c_str(), full_flag);
	}
	else
		cout << " Arquivo \"data\\my_store.csv\" está vazio." << endl;
}

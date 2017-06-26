/**
* @file
* @brief Onde fica a função principal.
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 02/06/2017
* @date --
* @sa --
*/

#include "header.h"
#include "Produto.h"
#include "Produto_tipos.h"
#include "Cesta.h"
//#include "test.h"


/**
* @brief Função principal
*/
int main(int argc, char const *argv[])
{
	Cesta loja;	/**< Produtos da loja */
	Cesta cliente;	/**< Produtos que o cliente deseja comprar da loja */

	cout << "Bem vindo ao sistema de admnistração de produtos da QLeveTudo." << endl
		<< 	"Carregando Cesta da loja...";

	loja.load();	// Carregando produtos da loja do arquivo "data/my_store.csv"
	//cout << loja.size() << endl;

	//loja.print(cout);


	cout << "Pronto. Total de Produtos cadastrados: " << loja.size() << endl
		<< " Total de unidades disponíveis: " << loja.unities() << endl
		<< "====================================================" << endl;

	menu_principal(loja, cliente);	// Interação com o usuário

	// Finalizando o programa

	cout << "Salvando informações do estoque da loja...";

	loja.save();	// Salva os produtos do Cesta da loja em "data/my_store.csv" (sobrescreve)

	cout << "Pronto." << endl;

	cout << "Saindo. . ." << endl;

	return 0;
}
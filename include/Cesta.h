#ifndef Cesta_H
#define Cesta_H

/**
* @file
* @brief Definição e implementação da classe Produto
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 05/06/2017
* @date 06/06/2017
* @sa --
*/

#include "header.h"
#include "Produto.h"
#include "myLista.h"


/**
* @enum direction
* @brief indica Domínio e contradomínio da função
*/
enum direction {loja_loja = 0, loja_venda = 1, venda_loja, venda_venda };

/**
* @class Cesta
* @brief Classe que armazenará uma lista de ponteiro para Produto de produto, 
* @tparam Um tipo de produto (CD, DVD, Fruta, etc.)
*/
class Cesta
{
	private:
		myLista<Produto*> produtos;	/**< Lista de ponteiros para Produto */

	public:

		/**
		* @brief Constrói um objeto Cesta vazio
		*/
		Cesta(){}

		/**
		* @brief Cesta criada a partir de outra Cesta (cópia)
		* @param original Cesta a ser copiado
		*/
		Cesta( Cesta &origem)	{*this = origem;}

		/**
		* @brief Destrói todos os elementos alocados na Cesta
		*/
		~Cesta()
		{
			for (auto &e : produtos) if(e != NULL) delete e;	// Deleta todos os Produtos alocados na lista interna da Cesta
		}

		// Métodos
		// Getters
		int size();	/**< Retorna a quantidade total de produtos (contando com as unidade) neste grupo */
		float price();	/**< Retorna a soma dos preços de todos os produtos (contando com as unidade) neste grupo */
		typename myLista<Produto*>::iterator search( const string& m_barcode ); /**< Procura Por um produto cadastrado que tenha seu código de barras igual a 'm_barcode' */
		//int get_max_qnt( typename myLista<Produto*>::iterator& it );	
		// procurar por fornecedor (string)
		
		// Setters
		void reg( Produto* prod );	/**< Cadastra um produto na lista (se ele ja estiver cadastrado, aumenta a sua quantidade em um) */
		void unreg( typename myLista<Produto*>::iterator& it ); /**< Descadastra um produto */
		void change_qnt( typename myLista<Produto*>::iterator& it, const int x ); /**< Remove ou acrescenta uma quantidade de unidades de um certo produto cadastrado*/
		void modify( Produto* prod );
		void absorb_qnt(typename myLista<Produto*>::iterator it, const int x); /**<  Move um número de unidades do produto apontado por 'it' a Cesta que chamou está função. */
		
		// Printers
		void print( std::ostream& out );	/**< Imprime uma lista com todos os produtos do grupo */ 
		void print_type( std::ostream& out, const string& my_type );	/**< Imprime produtos de um tipo */
		void print_notafiscal(std::ostream& out); /**<  Imprime os Produtos no formato de um cupom fiscal da loja */ 
		
		// Manipulação de arquivos
		void save();	/**<  Salva os Produtos e listas desta Cesta em um arquivo .csv */ 
		void load();	/**<  Carrega os Produtos e listas desta Cesta de um arquivo .csv */

		// Sobrecarga de operadores
		bool operator== ( Cesta& direita);	/**< Compara um grupo com outro pra ver se são iguais (possuem a mesma lista de produtos)*/
		Cesta& operator= (Cesta& direita);	/**< Atribui a lista de um grupo para este */
		//friend &istream operator>> (istream &in, const Produto x);	/**< Sobrecarga do >> */


		typedef typename myLista<Produto*>::iterator it_P;

		// Friends
		friend void menu_principal (Cesta& m_loja, Cesta& m_cliente);
		friend void sub_encontrou_produto( typename myLista<Produto*>::iterator& it, Cesta& m_loja, Cesta& m_cliente, direction my_case );
		friend void sub_consulta (Cesta& m_loja, Cesta& m_cliente, direction my_case );
		friend void sub_cadastro_loja(Cesta& target);
		friend void sub_venda(Cesta &m_loja, Cesta& m_cliente);
};

// =================================================================================
// ================================= IMPLEMENTAÇÃO ================================= 


// -------------------------------------------------
// ----------------------------------------- Getters 

int Cesta::size()
{
	int sum = 0;	// Vai armazenar a soma total de unidades de todos os produtos do grupo

	for( auto &e: produtos )
		sum += e->get_quantity() ;	// Soma as quantidades

	return sum;
}


float Cesta::price()
{
	float sum = 0;	// Vai armazenar a soma total de preços de todos os produtos do grupo

	for( auto &e: produtos )
		sum = sum + *e ;	// Soma os preços

	return sum;
}

/**
* @param m_barcode código de barras do Produto procurado
* @return Interator pra localização do Produto procurado na lista. Se o iterator for igual ao fim da lista, o produto buscado não foi achado.
*/
typename myLista<Produto*>::iterator Cesta::search( const string& m_barcode )
{
	typename myLista<Produto*>::iterator it = produtos.begin();	// Cria um iterator pro inícia da 'produtos'
	
	for( ; it != produtos.end() ; it++ )
		if( (*it)->get_barcode() == m_barcode ) break;	// encontrou*

	return it;	// *se it == produtos.end(), não encontrou.
}

/**
* @param it Iterator para o produto
* @param x quantidade a ser acrescentada ou removida ( se for negativo)
*/


// -------------------------------------------------
// ----------------------------------------- Setters 


/*
* @param prod Produto utilizado na função
*/
void Cesta::reg( Produto* prod )
{
	typename myLista<Produto*>::iterator it = search(prod->get_barcode());	// Iterator para o produto

	if (it != produtos.end())	// Se o produto ja foi registrado
		cout << " Produto ja tinha sido registrado." << endl;
	else	// Se o produto ainda não foi registrado
	{
		produtos.push_back(prod);	// Regista o produto.
		cout << " Produto foi registrado.";
	}
}

/**
* @param it Iterator para o produto
*/
void Cesta::unreg( typename myLista<Produto*>::iterator& it )
{
	delete (*it);

	produtos.remove( (*it) );
}

void Cesta::change_qnt( typename myLista<Produto*>::iterator& it, const int x )
{
	(*it)->set_quantity( x );

//	cout << "Nova quantidade: " << (*it).get_quantity() << endl;
}

void Cesta::modify( Produto* prod )
{
	prod->change();
}

void Cesta::absorb_qnt(typename myLista<Produto*>::iterator it, const int x)
{
	bool found = false;	// Indica se a o produto apontado por 'it' foi encontrado na Cesta que chamou esta função

	for(auto &e: produtos)	// Percorre a cesta que chamou a função
	{
		if (*e == *(*it))	// Se achar o produto que é igual ao apontado por 'it'
		{
			found = true;	// Achou produto na Cesta que chamou esta função

			e->set_quantity( e->get_quantity() + x );	// Soma a quantidade disponivel na cesta com 'x'
			(*it)->set_quantity( (*it)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'
			
			break;	// Sai do loop
		}
	}

	if( found == false )	// Se produto não era cadastrado na Cesta que chamou esta função
	{
		reg( (*it) );	// Registra o produto na cesta que chamou a função
		
		for(auto &e: produtos)	// Percorre a cesta que chamou a função
		{
			if (*e == *(*it))	// Se achar o produto que é igual ao apontado por 'it'
			{
				e->set_quantity( e->get_quantity() + x );	// Soma a quantidade disponivel na cesta com 'x'
				(*it)->set_quantity( (*it)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'
				
				break;	// Sai do loop
			}
		}
	}
}


// -------------------------------------------------
// ---------------------------------------- Printers


/**
* @param out ostream onde vai ser impressa a função
*/
void Cesta::print( std::ostream& out )
{
	int i = 0;	// índice

	//out << "LISTANDO PRODUTOS: {" << endl;
	for (auto &e: produtos)
	{
		cout << "(" << i++ << "):";
		e->print_it(out);
		cout << endl;
	}
	//out << "}" << endl;
}

/**
* @param out ostream onde vai ser impressa a função
* @param my_type Tipo de Produto a ser impresso
*/
void Cesta::print_type( std::ostream& out, const string& my_type )
{
	int i = 0;	// índice

	//out << "LISTANDO '"<< my_type <<"': {" << endl;
	for (auto &e: produtos)
	{
		if( e->get_type() == my_type)	// Se for o tipo que procuro
		{
			cout << "(" << i++ << "):";
			e->print_it(out);
			cout << endl;
		}
	}
	//out << "}" << endl;
}

void Cesta::print_notafiscal(std::ostream& out)
{
	out << "________________________________________________________________" << endl;
	out << "------------------------- CUPOM FISCAL -------------------------" << endl;
	out << "________________________________________________________________" << endl;
	out << "====================== MERCADO QLEVE TUDO ======================" << endl;
	out << "=============== Rua Inferno no Céu, n450, Alecrim  =============" << endl;
	out << "________________________________________________________________" << endl;
	out << "----------------------------------------------------------------" << endl;
	if(produtos.empty() == false )
	{
		//out << "CD's:" << endl;
		print_type(out,"CD");
		out << "________________________________________________________________" << endl;
		//out << "Salgados:" << endl;
		print_type(out,"Salgado");
		out << "________________________________________________________________" << endl;
	}
	out << "----------------------------------------------------------------" << endl;
	out << "TOTAL: $" << price() << endl;
	out << "----------------------------------------------------------------" << endl;
	out << "Volte sempre!" << endl;
}


// -------------------------------------------------
// ------------------------- Manipulação de Arquivos 


void Cesta::load()
{
	string filename("data/my_store.csv");    // Local do arquivo a ser salvo com os dados da cesta
	string dummy_type;	// Armazena o tipo do produto

	// Criando ponteiros para novos tipos
	CD      *new_cd; 
	Salgado *new_sa;

	// Abrindo stream de saída
	std::ifstream inData(filename.c_str());

	// Leitura
	if(inData.is_open())
	{
		inData.seekg (0, inData.end);
		int length = inData.tellg();	// Armazena a quantidade de caracteres no arquivo
		inData.seekg (0, inData.beg);

		if(length >= 0)	// Se o arquivo não for vazio
		{
			while( inData.tellg() != -1)	// enquanto não chegar ao fim do arquivo
			{
				inData.ignore(1);	// ignora o primeiro '\"'
				//cout << char(inData.peek()) << endl;
				getline(inData, dummy_type, '\"');	// ex.: dummy_type = "CD"
				inData.ignore(1);	// ignora o ';'

				if (dummy_type == "CD")
				{
					new_cd = new CD;
					new_cd->load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
					produtos.push_back(new_cd);	// Armazena o produto na lista de produtos diretamente
				}

				if (dummy_type == "Salgado")
				{
					new_sa = new Salgado;
					new_sa->load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
					produtos.push_back(new_sa);	// Armazena o produto na lista de produtos diretamente
				}

				dummy_type = "";	 //esvazia o dummy
				// doce etc
			}
			
		}
		else 
			cout << "\"" << filename << "\" está vazio." << endl;

		inData.close();	// Fecha stream de leitura
	}
	else // O arquivo não foi iniciado corretamente
	{
		cerr << "Erro ao tentar inicializar stream de entrada para " << filename << "." << endl;
		exit(1);
	}
}

/**
* @details Cada linha vai conter as seguintes informações sobre os produtos:
* "TIPO";"FORNECEDOR";PREÇO;"CODIGO_DE_BARRAS";QUANTIDADE;<informações específicas de cada produto>
*/
void Cesta::save()
{
	string filename("data/my_store.csv");    /**< string com o nome do local do arquivo a ser salvo com os dados do baú */

	std::ofstream outData(filename.c_str()); /**< stream de saída para 'filename' */

	// Verifica se 'outData' abriu corretamente
	if(outData.is_open())
	{
		// Imprime os produtos de cada secção
		for(auto &e: produtos)
			e->save_csv_it(outData);

		// Fecha stream.
		outData.close();
	}
	else
	{
		cerr << "Erro ao tentar inicializar stream de saída para "<< filename <<"." << endl;
		exit(1);
	}
}


// -------------------------------------------------
// ------------------------ Sobrecarga de operadores 

/**
* @param direita grupo a ser comparado
*/
bool Cesta::operator== ( Cesta &direita)
{
	if(produtos.size() != direita.produtos.size() )	return false;	// Se os tamanhos das listas comparadas forem diferentes, retorna falso.

	myLista<Produto*>::iterator esq;	// declara iterator que vai percorrer a Cesta que chamou esta função

	// Se os tamanhos das listas comparadas forem iguais
	for(myLista<Produto*>::iterator dir = direita.produtos.begin(); dir != direita.produtos.end(); dir++)
	{
		for(esq = produtos.begin(); esq != produtos.end(); esq++)
		{
			//if( (*esq)->get_barcode() == (*dir)->get_barcode() ) break;	// Se algum item delas diferirem um do outro (até na ordem), retorna falso.
			if( *(*esq) == *(*dir) ) break;	// Se forem iguais
		}
		if( esq == produtos.end())	// Se não encontrou um Produto de direita
			return false;
	}
	
	return true;
}

/**
* @param direita grupo a ser copiado
*/
Cesta& Cesta::operator= (Cesta &direita)
{
	if ( (*this == direita) == false)	// Se as Cestas não forem iguais
	{
		if( not(produtos.empty()) )	// Se a que chamou esta função não estiver vazia
			for(auto &e : produtos) delete e;	// deletar seu conteudo

		if( not(direita.produtos.empty()) )	// Se a lista da direita não estiver vazia
		{
			for(myLista<Produto*>::iterator dir = direita.produtos.begin();
				dir != direita.produtos.end(); dir++)
			{
				if( (*dir)->get_type() == "CD" )	// Se o item apontado na Cesta da direita for um CD
					produtos.push_back( new CD((*dir)));
				else if( (*dir)->get_type() == "Salgado" )	// Se o item apontado na Cesta da direita for um CD
					produtos.push_back( new Salgado((*dir)));

				// Doce etc

			}
		}
	}

	return *this;
}

#include "Menu.h"

#endif
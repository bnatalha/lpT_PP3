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

/**
* @enum direction
* @brief indica Domínio e contradomínio da função
*/
enum direction {loja_loja = 0, loja_venda = 1, venda_loja, venda_venda };

/**
* @brief Imprime uma 'direction' (facilita a visualização)
* @param out Referência para uma stream de saída
*/
void print_direction(direction& x , std::ostream& out)
{
	if(x == direction::loja_loja) out << "O : loja -> loja";
	if(x == direction::loja_venda) out << "O : loja -> venda";
	if(x == direction::venda_loja) out << "O : venda -> loja";
	if(x == direction::venda_venda) out << "O : venda -> venda";
}

/**
* @class Cesta
* @brief Classe que armazenará uma lista de ponteiro para Produto de produto, 
* @tparam Um tipo de produto (CD, DVD, Fruta, etc.)
*/
class Cesta
{
	private:
		map<string,Produto* > produtos;	/**< Onde são armazenados os produtos da loja */

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
			for (map<string,Produto* >::iterator it = produtos.begin() ; it != produtos.end(); it++)
				if(it->second != NULL) delete it->second;	// Deleta todos os Produtos alocados no mapa interno da Cesta
		}

		// Métodos
		// Getters
		int unities();	/**< Retorna a quantidade total de produtos (contando com as unidade) */
		int size();	/**< Retorna a quantidade total de produtos cadastrados */
		float price();	/**< Retorna a soma dos preços de todos os produtos (contando com as unidade) neste grupo */
		typename map<string, Produto*>::iterator search( const string& m_barcode ); /**< Procura Por um produto cadastrado que tenha seu código de barras igual a 'm_barcode' */				

		// Setters
		void reg( Produto* prod );	/**< Cadastra um produto na lista (se ele ja estiver cadastrado, aumenta a sua quantidade em um) */
		void unreg( typename map<string, Produto*>::iterator& it ); /**< Descadastra um produto */
		void absorb_qnt(typename map<string, Produto*>::iterator it, const int x); /**<  Move um número de unidades do produto apontado por 'it' a Cesta que chamou está função. */
		void clear();	/**< Limpa o mapa interno, desalocando tudo e removendo os pares existentes */
		void fetch_from( Cesta& orig, bool s_type, bool s_prov, const string& m_type, const string& m_provider);
		
		// Printers
		void print( std::ostream& out );	/**< Imprime uma lista com todos os produtos do grupo */ 
		void print_type( std::ostream& out, const string& my_type );	/**< Imprime produtos de um tipo */
		void print_provider( std::ostream& out, const string& my_provider );	/**< Imprime produtos de um provedor */
		void print_notafiscal(std::ostream& out); /**<  Imprime os Produtos no formato de um cupom fiscal da loja */ 
		
		// Manipulação de arquivos
		void save();	/**<  Salva os Produtos e listas desta Cesta em um arquivo .csv */ 
		void load();	/**<  Carrega os Produtos e listas desta Cesta de um arquivo .csv */

		// Sobrecarga de operadores
		bool operator== ( Cesta& direita);	/**< Compara um grupo com outro pra ver se são iguais (possuem a mesma lista de produtos)*/
		Cesta& operator= (Cesta& direita);	/**< Atribui a lista de um grupo para este */
		//friend &istream operator>> (istream &in, const Produto x);	/**< Sobrecarga do >> */

		// Friends
		friend void menu_principal (Cesta& m_loja, Cesta& m_cliente);
		friend void sub_encontrou_produto( typename map<string, Produto*>::iterator& it, Cesta& m_loja, Cesta& m_cliente, direction my_case );
		friend void sub_consulta (Cesta& m_loja, Cesta& m_cliente, direction my_case );
		friend void sub_cadastro_loja(Cesta& target);
		friend void sub_venda(Cesta &m_loja, Cesta& m_cliente);
};

// =================================================================================
// ================================= IMPLEMENTAÇÃO ================================= 


// -------------------------------------------------
// ----------------------------------------- Getters 

int Cesta::unities()
{
	int sum = 0;	// Vai armazenar a soma total de unidades de todos os produtos do grupo

	for( auto &e: produtos )
		sum += e.second->get_quantity() ;	// Soma as quantidades

	return sum;
}

int Cesta::size()
{
	return produtos.size();
}


float Cesta::price()
{
	float sum = 0;	// Vai armazenar a soma total de preços de todos os produtos do grupo

	for( auto &e: produtos )
		sum = sum + *(e.second) ;	// Soma os preços

	return sum;
}

/**
* @param m_barcode código de barras do Produto procurado
* @return Interator pra localização do Produto procurado na lista. Se o iterator for igual ao fim da lista, o produto buscado não foi achado.
*/
typename map<string, Produto*>::iterator Cesta::search( const string& m_barcode )
{
	typename map<string, Produto*>::iterator it = produtos.find(m_barcode);	// procura pelo codigo de barras em 'produtos'

	return it;	// *se it == produtos.end(), não encontrou.
}

/**
* @param m_provider nome do fornecedor procurado
* @param orig Cesta onde os produtos do fornecedor 'm_provider' seram procurados
*/
/*
void Cesta::fetch_provider_from( const string& m_provider, Cesta& orig  )
{
	for( map<string, Produto*>::iterator it = orig.produtos.begin();
		it != orig.produtos.end(); it++)	//utilizando um iterator para a Cesta que está sendo vasculhada
	{
		if( it->second->get_provider() == m_provider )	// Se encontrou um produto do fornecedor requisitado
		{			
			if(produtos.count( it->second->get_barcode() ) == 0 ) // Caso ele não exista nesta Cesta
			{	
				if(it->second->get_type() == "CD")
				{
					CD *new_cd = new CD(it->second);
					produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_cd));	// O registra como CD.
				}
				if(it->second->get_type() == "Salgado")
				{
					Salgado *new_sal = new Salgado(it->second);
					produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_sal));	// O registra como Salgado.
				}
			}
		}
	}
}
*/



// -------------------------------------------------
// ----------------------------------------- Setters 


/*
* @param prod Produto utilizado na função
*/
void Cesta::reg( Produto* prod )
{
	typename map<string, Produto*>::iterator it = search(prod->get_barcode());	// Iterator para o produto

	if (it != produtos.end())	// Se o produto ja foi registrado
		cout << " Produto ja tinha sido registrado." << endl;
	else	// Se o produto ainda não foi registrado
	{
		produtos.insert(std::pair<string, Produto*>(prod->get_barcode(),prod));	// Regista o produto.
		cout << " Produto foi registrado.";
	}
}

/**
* @param it Iterator para o produto
*/
void Cesta::unreg( typename map<string, Produto*>::iterator& it )
{
	delete (*it).second;	// deleta o conteudo apontado pelo ponteiro para produto
	produtos.erase(it);	// deleta o par do mapa;
}

/**
* @param it Iterator para o produto a ser alterado de uma outra Cesta
* @param x inteiro constante com a quantidade de unidades do produto apontado por 'it' que será registrado nessa Cesta
*/
void Cesta::absorb_qnt(typename map<string, Produto*>::iterator it, const int x)
{
	bool found = false;	// Indica se a o produto apontado por 'it' foi encontrado na Cesta que chamou esta função

	for(map<string, Produto*>::iterator aqui = produtos.begin();
		aqui != produtos.end(); aqui++)	// Percorre a cesta que chamou a função
	{
		if (aqui->second->get_barcode() == it->second->get_barcode() )	// Se achar o produto que é igual ao apontado por 'it'
		{
			found = true;	// Achou produto na Cesta que chamou esta função

			aqui->second->set_quantity( aqui->second->get_quantity() + x );	// Soma a quantidade disponivel na cesta com 'x'
			(it->second)->set_quantity( (it->second)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'
			
			cout << "Tit->second = " << it->second << " e aqui->second = " << aqui->second << endl;
			break;	// Sai do loop
		}
	}

	if( found == false )	// Se produto não era cadastrado na Cesta que chamou esta função
	{
		if(it->second->get_type() == "CD") reg( new CD(it->second) );	// Registra o produto na cesta que chamou a função
		else if(it->second->get_type() == "Salgado") reg( new Salgado(it->second) );	// Registra o produto na cesta que chamou a função
				
		for(map<string, Produto*>::iterator aqui = produtos.begin();
			aqui != produtos.end(); aqui++)	// Percorre a cesta que chamou a função
		{
			if (aqui->second->get_barcode() == it->second->get_barcode())	// Se achar o produto que é igual ao apontado por 'it'
			{
				aqui->second->set_quantity( x );	// Fixa a quantidade disponivel na cesta com 'x'
				(it->second)->set_quantity( (it->second)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'

				cout << "Fit->second = " << it->second << " e aqui->second = " << aqui->second << endl;
				
				break;	// Sai do loop
			}
		}
	}
}

void Cesta::clear()
{
	for (map<string,Produto* >::iterator it = produtos.begin() ; it != produtos.end(); it++)
		if(it->second != NULL) delete it->second;	// Deleta todos os Produtos alocados no mapa interno da Cesta

	produtos.clear();	// Remove todos os pares do mapa.
}

/**
* @param orig Cesta onde os produtos do tipo 'm_type' seram procurados
* @param s_type diz se a busca levará em conta o tipo do produto
* @param s_prov diz se a busca levará em conta o fornecedor do produto
* @param m_type tipo do produto procurado
* @param m_provider fornecedor procurado
*/
void Cesta::fetch_from( Cesta& orig, bool s_type, bool s_prov, const string& m_type, const string& m_provider )
{
	for( map<string, Produto*>::iterator it = orig.produtos.begin();
		it != orig.produtos.end(); it++)	//utilizando um iterator para a Cesta que está sendo vasculhada
	{
		bool found_type = it->second->get_type() == m_type;
		bool found_provider = it->second->get_provider() == m_provider;

		//if( (s_type and (it->second->get_type() == m_type) ) or 
		//    (s_prov and (it->second->get_provider() == m_provider) ) )	// Se encontrou o produto

		if( (s_type and found_type) or (s_prov and found_provider ) )	// Se encontrou o produto
		{
			if(produtos.count( it->second->get_barcode() ) == 0 ) // Caso ele não exista nesta Cesta
			{	
				if(it->second->get_type() == "CD")
				{
					CD *new_cd = new CD(it->second);
					produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_cd));	// O registra como CD.
				}
				if(it->second->get_type() == "Salgado")
				{
					Salgado *new_sal = new Salgado(it->second);
					produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_sal));	// O registra como Salgado.
				}
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
		e.second->print_it(out);
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
		if( e.second->get_type() == my_type)	// Se for o tipo que procuro
		{
			cout << "(" << i++ << "):";
			e.second->print_it(out);
			cout << endl;
		}
	}
	//out << "}" << endl;
}

void Cesta::print_provider( std::ostream& out, const string& my_provider )
{
	int i = 0;	// índice

	//out << "LISTANDO '"<< my_type <<"': {" << endl;
	for (auto &e: produtos)
	{
		if( e.second->get_provider() == my_provider)	// Se for o tipo que procuro
		{
			cout << "(" << i++ << "):";
			e.second->print_it(out);
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
		inData.seekg (0, inData.beg);	// volta o ponteiro do buffer pro início


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

					try{
						new_cd = new CD;
					} catch (std::exception &e)	{
						cerr << "[CAUGHT] Cesta::load(): " << e.what() << endl;
					}

					new_cd->load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
					produtos.insert(std::pair<string, Produto*>(new_cd->get_barcode(),new_cd));	// Armazena o produto no mapa de produtos diretamente
				}

				if (dummy_type == "Salgado")
				{
					new_sa = new Salgado;
					new_sa->load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
					produtos.insert(std::pair<string, Produto*>(new_sa->get_barcode(),new_sa));	// Armazena o produto no mapa de produtos diretamente
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
		//cerr << "Erro ao tentar inicializar stream de entrada para " << filename << "." << endl;
		cout << "Erro ao tentar inicializar stream de entrada para " << filename << "." << endl
			<< "Iniciando loja sem produtos cadastrados." << endl;
		//exit(1);
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
			e.second->save_csv_it(outData);

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
* @param direita cesta a ser comparada
*/
bool Cesta::operator== ( Cesta &direita)
{
	if(produtos.size() != direita.produtos.size() )	return false;	// Se os tamanhos das listas comparadas forem diferentes, retorna falso.

	//map<string, Produto*>::iterator esq;	// declara iterator que vai percorrer a Cesta que chamou esta função

	// Se os tamanhos dos mapas comparados forem iguais
	/*for(map<string, Produto*>::iterator dir = direita.produtos.begin();
		dir != direita.produtos.end(); dir++)
	{
		for(esq = produtos.begin(); esq != produtos.end(); esq++)
		{
			//if( (*esq)->get_barcode() == (*dir)->get_barcode() ) break;	// Se algum item delas diferirem um do outro (até na ordem), retorna falso.
			if( *(*esq) == *(*dir) ) break;	// Se forem iguais
		}
		if( esq == produtos.end())	// Se não encontrou um Produto de direita
			return false;
	}*/
	for(auto& e : produtos)
		if (direita.search(e.second->get_barcode()) == direita.produtos.end() )	return false;	// se não achar o produto, retorna falso

	return true;
	
	//return (produtos == direita.produtos);
}

/**
* @param direita grupo a ser copiado
*/
Cesta& Cesta::operator= (Cesta &direita)
{
	if ( (*this == direita) == false)	// Se as Cestas não forem iguais
	{
		if( not(produtos.empty()) )	// Se a que chamou esta função não estiver vazia
			for(map<string, Produto*>::iterator esq = produtos.begin();
				esq != produtos.end(); esq++) unreg(esq);	// destroi todos serus produtos

		if( not(direita.produtos.empty()) )	// Se a lista da direita não estiver vazia
		{
			for(map<string, Produto*>::iterator dir = direita.produtos.begin();
				dir != direita.produtos.end(); dir++)
			{
				if( (dir->second)->get_type() == "CD" )	// Se o item apontado na Cesta da direita for um CD
					produtos.insert( std::pair<string,Produto*> ( dir->second->get_barcode(), (new CD((dir->second))) ) );
				else if( dir->second->get_type() == "Salgado" )	// Se o item apontado na Cesta da direita for um CD
					produtos.insert( std::pair<string,Produto*> ( dir->second->get_barcode(), (new Salgado((dir->second))) ) );

				// Doce etc

			}
		}
	}
	
	//*this

	return *this;
}

#include "Menu.h"

#endif
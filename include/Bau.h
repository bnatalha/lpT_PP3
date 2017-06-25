#ifndef BAU_H
#define BAU_H

/**
* @file
* @brief Implementação de um Salgado (derivados da classe Produto)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "header.h"
#include "Produto.h"
#include "Seccao.h"

/**
* @class Bau
* @brief Um Baú de items. Contém um Seccao para cada tipo de produto e os modifica.
*/
class Bau
{
	private:
		Seccao<CD> s_cds; /**< Seccao do tipo CD  */
		Seccao<Salgado> s_sal;	/**< Seccao do tipo CD */
		//Seccao<Salgado> s_doc;	

		// doce etc

	public:

		/**
		* @brief Constrói um objeto Bau sem especificar seus dados
		*/
		Bau(){}

		/**
		* @brief Constrói um objeto Bau como uma cópia de outro Bau já existente
		*/
		Bau( const Bau& orig) 
			: s_cds(orig.s_cds), s_sal(orig.s_sal)
		{}

		/**
		* @brief Destrutor de Bau
		*/
		~Bau(){}

		// Métodos

		// Getters
		//void search_provider(string& prov);	/**< Busca e imprime todos os produtos de um fornecedor */
		bool is_empty( );	/**<  Checa se o Bau está vazio */
		typename myLista<CD>::iterator search_CD( const string& m_barcode); /**< Procura por um codigo de barras na Secção de CD do Bau */
		typename myLista<Salgado>::iterator search_Salgado( const string& m_barcode); /**< Procura por um um codigo de barras na Secção de Salgado do Bau */
		
		// Setters
		void absorb_B( Bau& orig);	/**<  Move todos os itens de 'orig' para o Bau que chamou está função */
		void clear_B( );	/**<  Remove todos os items deste Bau */
		void register_CD( CD& p);	/**<  Cadastra um CD no Bau */
		void register_Salgado( Salgado& p);	/**<  Cadastra um Salgado no Bau */
		void unregister_CD( typename myLista<CD>::iterator& p);	/**<  Descadastra um CD no Bau */
		void unregister_Salgado( typename myLista<CD>::iterator& p);	/**<  Descadastra um Salgado no Bau */
		//void register_Doce( Doce& p);	/**<  Registra um Salgado no Bau */

		void save();	/**<  Salva os Produtos e listas deste Bau em um arquivo .csv */ 
		void load();	/**<  Carrega os Produtos e listas deste Bau de um arquivo .csv */ 
		
		// Sobrecarga de operadores
		Bau& operator=(const Bau& orig);
		void print(std::ostream& out);
};

// ==============
// Implementações
// ==============


// ============== Getters
// ======================

/**
* @param orig Bau a ser absorvido
*/
void Bau::absorb_B( Bau& orig)
{
	*this = orig;	// Copia os items de 'orig' para este Bau
	orig.clear_B();	// Limpa 'orig'
}

bool Bau::is_empty()
{
	return ( s_cds.l_produtos.empty() and
			 s_sal.l_produtos.empty()  );
}

/**
* @param CD procurado
*/
typename myLista<CD>::iterator Bau::search_CD( const string& m_barcode)
{
	typename myLista<CD>::iterator it = s_cds.search_P(m_barcode);	// Cria um iterator para receber o resultado da busca pelo produto na lista

	return it;	
}

/**
* @param Salgado procurado
*/
typename myLista<Salgado>::iterator Bau::search_Salgado( const string& m_barcode)
{
	typename myLista<Salgado>::iterator it = s_sal.search_P(m_barcode);	// Cria um iterator para receber o resultado da busca pelo produto na lista

	return it;	
}

// ============== Setters
// ======================

/**
* @param CD a ser registrado
*/
void Bau::register_CD( CD& p)
{
	s_cds.register_P(p);
}

/**
* @param Salgado a ser registrado
*/
void Bau::register_Salgado( Salgado& p)
{
	s_sal.register_P(p);
}

void Bau::clear_B( )
{
	s_cds.l_produtos.clear();	// Limpa a lista da Seccao de CD
	s_sal.l_produtos.clear();	// Limpa a lista da Seccao de Salgado
	//s_doc.l_produtos.clear();	// Limpa a lista da Seccao de Salgado
}

void unregister_CD( typename myLista<CD>::iterator& p)
{
	s_cds.unregister_P(p);
}

void unregister_Salgado( typename myLista<Salgado>::iterator& p)
{
	s_sal.unregister_P(p);
}

/**
* @details Cada linha vai conter as seguintes informações sobre os produtos:
* "TIPO";"FORNECEDOR";PREÇO;"CODIGO_DE_BARRAS";QUANTIDADE;<informações específicas de cada produto>
*/
void Bau::save( )
{
	string filename("data/my_store.csv");    /**< string com o nome do local do arquivo a ser salvo com os dados do baú */

	std::ofstream outData(filename.c_str()); /**< stream de saída para 'filename' */

	// Verifica se 'outData' abriu corretamente
	if(outData.is_open())
	{
		// Imprime os produtos de cada secção
		s_cds.save_csv_P(outData);
		s_sal.save_csv_P(outData);
		//s_doc.save_csv_P(outData);

		// Fecha stream.
		outData.close();
	}
	else
	{
		cerr << "Erro ao tentar inicializar stream de saída para "<< filename <<"." << endl;
		exit(1);
	}
}

void Bau::load( )
{
	
	string filename("data/my_store.csv");    /**< string com o nome do local do arquivo a ser salvo com os dados do baú */
	string dummy_type;	// Armazena o tipo do produto

	CD new_cd; // Cria um novo CD
	Salgado new_sa;	// Cria um novo Salgado

	std::ifstream inData(filename.c_str()); /**< stream de entrada para 'filename' */

	// Leitura
	if(inData.is_open())
	{
		while( inData.tellg() != -1)	// enquanto não chegar ao fim do arquivo
		{
			inData.ignore(1);	// ignora o primeiro '\"'
			//cout << char(inData.peek()) << endl;
			getline(inData, dummy_type, '\"');	// ex.: dummy_type = "CD"
			inData.ignore(1);	// ignora o ';'

			if (dummy_type == "CD")
			{
				new_cd.load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
				s_cds.l_produtos.push_sorted(new_cd);	// Armazena o produto na lista de produtos diretamente
			}

			if (dummy_type == "Salgado")
			{
				new_sa.load_csv_it(inData);	// Carrega o new_ com o conteudo de uma linha de inData
				s_sal.l_produtos.push_sorted(new_sa);	// Armazena o produto na lista de produtos diretamente
			}

			dummy_type = "";
			// doce etc
		}

		inData.close();
	}
	else
	{
		cerr << "Erro ao tentar inicializar stream de entrada para " << filename << "." << endl;
		exit(1);
	}

}

// =======================================
// ============== Sobrecarga de operadores
// =======================================

Bau& Bau::operator=( const Bau& orig)
{
	s_cds = orig.s_cds;
	s_sal = orig.s_sal;

	return *this;
}

void Bau::print(std::ostream& out)
{
	out << "________________________________________________________________" << endl;
	out << "------------------------- CUPOM FISCAL -------------------------" << endl;
	out << "________________________________________________________________" << endl;
	out << "====================== MERCADO QLEVE TUDO ======================" << endl;
	out << "=============== Rua Inferno no Céu, n450, Alecrim  =============" << endl;
	out << "________________________________________________________________" << endl;
	out << "----------------------------------------------------------------" << endl;
	if( s_cds.l_produtos.empty() == false )
	{
		out << "CD's:" << endl;
		s_cds.print_P(out);
		out << "subtotal: $" << s_cds.price_P() << endl;
		out << "________________________________________________________________" << endl;
	}
	if( s_sal.l_produtos.empty() == false )
	{
		out << "Salgados:" << endl;
		s_sal.print_P(out);
		out << "subtotal: $" << s_sal.price_P() << endl;
		out << "________________________________________________________________" << endl;
	}
	out << "----------------------------------------------------------------" << endl;
	out << "TOTAL: $" << (s_sal.price_P() + s_cds.price_P()) << endl;
	out << "----------------------------------------------------------------" << endl;
	out << "Volte sempre!" << endl;
}

#endif
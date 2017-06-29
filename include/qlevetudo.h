#ifndef QLEVETUDO_H
#define QLEVETUDO_H

#include "header.h"

/**
* @namespace qlt
* @brief Contem definições feitas pelo usuário para o sistema QLeveTudo
*/
namespace qlt
{

	/**
	* @enum direction
	* @brief indica qual Cesta receberá informações e em qual Cesta será realizada a busca por Produtos/informações
	*/
	enum direction {loja_loja = 0, loja_venda = 1, venda_loja, venda_venda };

	/**
	* @brief Imprime se uma venda foi iniciada e qual Cesta está sendo operada 
	* @param out Referência para uma stream de saída
	*/
	void print_direction(direction& x , std::ostream& out)
	{
		if(x == direction::loja_loja) out << "Não iniciou venda. Operando: estoque";
		if(x == direction::loja_venda) out << "Não iniciou venda. Operando: cesta do cliente";
		if(x == direction::venda_loja) out << "Iniciou venda. Operando: estoque";
		if(x == direction::venda_venda) out << "Iniciou venda. Operando: cesta do cliente";
	}

	/**
	* @class Produto
	* @brief Classe abstrata contendo as principais características comuns aos produtos da loja.
	*/
	class Produto
	{

		protected:
			string product_type;	/**< Tipo de produto (bebida, cd,etc) */
			string provider;	/**< Nome do fornecedor deste produto */
			float price;	/**< Preço do produto por unidade em R$*/
			string barcode;	/**< Código de barras (13 números símbolo EAN-13)*/
			int quantity;	/**< Quantidade deste produto em estoque */
			
		public:

			/**
			* @brief Constrói um objeto Produto sem especificar seus dados
			*/
			Produto()
				: product_type(""), provider(""), price(0), barcode("0000000000000"), quantity(0) 
			{}
			
			/**
			* @brief Constrói um Produto especificando seus atributos a partir de passagem de parâmetros (quantidade sempre inicia em 0)
			*/
			Produto(string produto, string fornecedor , float valor, string codigo)
				: product_type(produto), provider(fornecedor), price(valor), barcode(codigo), quantity(0)
			{}

			/**
			* @brief Produto criado a partir de outro produto (cópia)
			* @param original produto a ser copiado
			*/
			Produto( const Produto &origem)
				: product_type(origem.product_type), provider(origem.provider), price(origem.price), barcode(origem.barcode), quantity(origem.quantity)
			{}

			virtual ~Produto(){}

			// Métodos

			// Getter // Checar documentaçao
			string get_type() const { return product_type; }	/**< Retorna o tipo do produto (string) */
			string get_provider() const { return provider; }	/**< Retorna o nome do fornecedor do produto (string) */
			float get_price() const { return price; }	/**< Retorna preço do produto (float) */
			string get_barcode() const { return barcode; }	/**< Retorna o código de barras do produto (string) */
			float get_quantity() const { return quantity; }	/**< Retorna a quantidade de produtos (unidade) existentes */

			// Setters	// Checar se funciona pra rvalue
			void set_type( const string& x ) { product_type = x; }	/**< Modifica o tipo do produto (string) */
			void set_provider( const string& x ) { provider = x; }	/**< Modifica o nome do fornecedor do produto (string) */
			void set_price( const float& x ) { price = x; }	/**< Modifica preço do produto (float) */
			void set_barcode( const string& x ) { barcode = x; } 	/**< Modifica o código de barras do produto (string) */
			void set_quantity( const int& x ) { quantity = x; }	/**< Modifica a quantidade de produtos (unidade) existentes */
			bool change_product_specs();	/**< Modifica uma por uma as características do produto */

			// Sobrecarga de operadores
			float operator+ (const Produto &x);	/**< Retorna o resultado da adição do preço de dois produtos */
			friend float operator+ (float y, const Produto &x);	/**< Retorna o resultado da adição de um float com o preço do produto */
			float operator- (const Produto &x);	/**< Retorna o resultado da subtração do preço de dois produtos */
			friend float operator- (float y, const Produto &x);	/**< Retorna o resultado da subtração de um float com o preço do produto */
			//virtual bool operator= (const Produto &x);	/**< Cria uma copia de 'x' dinamicamente e atribui essa valor a o produto que invocou esta função */
			virtual bool operator== (const Produto &x);	/**< Verifica se dois produtos tem codigós de barra iguais */
			virtual bool operator!= (const Produto &x);	/**< Verifica se dois produtos tem codigós de barra diferentes */
			virtual bool operator> (const Produto &x); /**< Verifica se este produto tem o seu valor do código de barras maior do que o outro */
			virtual bool operator< (const Produto &x); /**< Verifica se este produto tem o seu valor do código de barras menor do que o outro */
			virtual bool operator>= (const Produto &x); /**< Verifica se este produto tem o seu valor do código de barras maior ou igual do que o outro */
			virtual bool operator<= (const Produto &x); /**< Verifica se este produto tem o seu valor do código de barras menor ou igual do que o outro */

			// ========================= Getters e Setters Virtuais =========================
			//  = Getters =
			virtual string get_expiration() { return ""; }	/**< Retorna o vencimento do produto (string) */
			virtual float get_sodium() {return 0;}	/**< Retorna a taxa de sódio (em mg) do produto */
			virtual bool get_gluten() {return true;}	/**< Retorna se o produto contém glúten ou não */
			virtual bool get_lactose() {return true;}	/**< Retorna se o produto contém lactose ou não */
			virtual string get_date() {return "";}	/**< Retorna a data de produção do lote do produto (string) */
			
			virtual string get_name() {return "";}	/**< Retorna título do CD (string) */
			virtual string get_title() {return "";}	/**< Retorna o título do livro (string) */
			virtual string get_artist() {return "";}	/**< Retorna artista do CD (string) */
			virtual string get_style() {return "";}	/**< Retorna o estilo do CD (string) */
			virtual string get_genre() {return "";}	/**< Retorna o gênero do produto */
			
			//Setters
			virtual void set_expiration(const string &x) {}	/**< Altera o vencimento do produto (string) */
			virtual void set_sodium(const float &x) {}	/**< Altera a taxa de açucar (em mg) do produto */
			virtual void set_gluten(const bool &x) {}	/**< Altera o atributo que diz se o produto contém glúten ou não */
			virtual void set_lactose(const bool &x) {}	/**< Altera o atributo que diz se o produto contém lactose ou não */
			
			virtual void set_name(const string &x) {}	/**< Altera título do CD (string) */
			virtual void set_title(const string &x) {}	/**< Altera o título do livro */
			virtual void set_artist(const string &x) {}	/**< Altera artista do CD (string) */
			virtual void set_style(const string &x) {}	/**< Altera o estilo do CD (string) */
			virtual void set_genre(const string &x) {}	/**< Altera o gênero do DVD */
			
			virtual bool change() =0;
			
			// auxiliar da sobrecarga de extração
			virtual void print_it (std::ostream& out) const =0;	/**< Função virtual pura que define como vai ser a impressão das informações do produto */
			virtual void save_csv_it (std::ofstream& out) =0;	/**< Função virtual pura que define como vai ser salva as informações dos produtos em um arquivo .csv */
			virtual void load_csv_it (std::ifstream& in) =0;	/**< Função virtual pura que define como seram lidas as informações dos produtos de um arquivo .csv */
			void save_csv_P (std::ofstream& out);	/**< Salva apenas os dados comuns a todos objetos de uma subclasse da classe Produto ('product_type', 'provider', 'barcode', 'quantity' e 'price')  */
			void load_csv_P (std::ifstream& in);	/**< Lê apenas os dados comuns a todos objetos de uma subclasse da classe Produto ('product_type', 'provider', 'barcode', 'quantity' e 'price')  */		
	};

	/**
	* @class CD
	* @brief Herdeira da classe Produto, usada para produtos do tipo cd
	*/
	class CD : public Produto
	{

		private:
			string name;	/**< Nome do CD */
			string artist;	/**< Artista do CD */
			string style; /**< Estilo do CD */

		public:

			/**
			* @brief Constrói um objeto CD sem especificar seus dados
			*/
			CD() 
				: Produto("CD","", 0, "00000000"), name(""), artist(""), style("")
			{}

			/**
			* @brief Constrói um objeto CD especificando seus atributos a partir de passagem de parâmetros
			*/
			CD(string nome, string artista, string estilo) 
				: Produto("CD","", 0, "00000000"), name(nome), artist(artista), style(estilo)
			{}

			/**
			* @brief Constrói um objeto CD copiando de um outro obejto CD
			*/
			CD(const CD& orig) 
				: Produto( orig.get_type(), orig.get_provider(), orig.get_price(), orig.get_barcode()),
				name(orig.name), artist(orig.artist), style(orig.style)
			{ set_quantity(orig.get_quantity()); }

			/**
			* @brief Constrói um objeto CD a partir de um ponteiro para um Porduto
			*/
			CD(Produto* orig) 
				: Produto( orig->get_type(), orig->get_provider(), orig->get_price(), orig->get_barcode() ),
				name(orig->get_name()), artist(orig->get_artist()), style(orig->get_style())
			{ set_quantity(orig->get_quantity()); }

			/**
			* @brief Destrutor virtual de CD
			*/
			virtual ~CD(){}

			// Métodos

			// Gets
			string get_name() { return name; }	/**< Retorna título do CD (string) */
			string get_artist() { return artist; }	/**< Retorna artista do CD (string) */
			string get_style() { return style; }	/**< Retorna o estilo do CD (string) */

			// Sets
			void set_name(const string &x) { name = x; }	/**< Altera título do CD (string) */
			void set_artist(const string &x) { artist = x; }	/**< Altera artista do CD (string) */
			void set_style(const string &x) { style = x; }	/**< Altera o estilo do CD (string) */
			bool change(); /**< Altera tudo do CD */

			// auxiliar da sobrecarga de extração
			void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
			void save_csv_it (std::ofstream& out);	/**< Função que define como vai ser salva as informações dos produtos em um arquivo .csv */
			void load_csv_it (std::ifstream& in);	/**< Função que define como seram lidas as informações dos produtos de um arquivo .csv */
	};

	/**
	* @class Salgado
	* @brief Herdeira da classe Produto, usada para produtos do tipo salgado
	*/
	class Salgado : public Produto
	{
		
		private:
			string expiration; /**< Vencimento do Salgado */
			float sodium;	/**< Taxa de sodio (em mg) */
			bool gluten;    /**< Bala contem glúten ou nao */
			bool lactose;   /**< Bala contem lactose ou nao */

		public:

			/**
			* @brief Constrói um objeto Salgado sem especificar seus dados
			*/
			Salgado() 
				: Produto("Salgado","", 0, "00000000"), expiration(""), sodium(0), gluten(false), lactose(false)
			{}

			/**
			* @brief Constrói um objeto Salgado especificano seus dados através da passagem de seus atributos como parâmetro
			*/
			Salgado(string vencimento, float sodio, bool glut, bool lacto) 
				: Produto("Salgado","", 0, "00000000"), expiration(vencimento), sodium(sodio), gluten(glut), lactose(lacto)
			{}

			/**
			* @brief Constrói um objeto Salgado copiando de um outro obejto Salgado
			*/
			Salgado(const Salgado& orig) 
				: Produto( orig.get_type(), orig.get_provider(), orig.get_price(), orig.get_barcode()),
				expiration(orig.expiration), sodium(orig.sodium), gluten(orig.gluten), lactose(orig.lactose)
			{ set_quantity(orig.get_quantity()); }

			/**
			* @brief Constrói um objeto Salgado a partir de um ponteiro para um Porduto
			*/
			Salgado(Produto* orig) 
				: Produto( orig->get_type(), orig->get_provider(), orig->get_price(), orig->get_barcode()),
				expiration(orig->get_expiration()), sodium(orig->get_sodium()), gluten(orig->get_gluten()), lactose(orig->get_lactose())
			{ set_quantity(orig->get_quantity()); }

			/**
			* @brief Destrutor virtual de Salgado
			*/
			virtual ~Salgado(){}

			// Métodos

			// Gets
			string get_expiration() { return expiration; }
			float get_sodium() { return sodium; }	/**< Retorna a taxa de sódio (em mg) do produto */
			bool get_gluten() { return gluten; }	/**< Retorna se o produto contém glúten ou não */
			bool get_lactose() { return lactose; }	/**< Retorna se o produto contém lactose ou não */

			// Sets
			void set_expiration(const string &x) { expiration = x; }
			void set_sodium(const float &x) { sodium = x; }	/**< Altera a taxa de açucar (em mg) do produto */
			void set_gluten(const bool &x) { gluten = x; }	/**< Altera o atributo que diz se o produto contém glúten ou não */
			void set_lactose(const bool &x) { lactose = x; }	/**< Altera o atributo que diz se o produto contém lactose ou não */
			bool change(); /**< Altera tudo do Salgado */

			// auxiliar da sobrecarga de extração
			void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
			void save_csv_it (std::ofstream& out);	/**< Função que define como vai ser salva as informações dos produtos em um arquivo .csv */
			void load_csv_it (std::ifstream& in);	/**< Função que define como seram lidas as informações dos produtos de um arquivo .csv */
	};


	/**
	* @class Cesta
	* @brief Classe que armazenará uma lista de ponteiro para Produto de produto, 
	* @tparam Um tipo de produto (CD, DVD, Fruta, etc.)
	*/
	class Cesta
	{
		private:
			map<string,Produto* > produtos;	/**< Onde são armazenados os produtos da Cesta */
			//map<string,int> fornecedores;	/**< Onde são armazenados os fornecedores da Cesta */

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
			int units();	/**< Retorna a quantidade total de produtos (contando com as unidade) */
			int size();	/**< Retorna a quantidade total de produtos cadastrados */
			float price();	/**< Retorna a soma dos preços de todos os produtos (contando com as unidade) neste grupo */
			typename map<string, Produto*>::iterator search( const string& m_barcode ); /**< Procura Por um produto cadastrado que tenha seu código de barras igual a 'm_barcode' */				
			bool is_valid_type( const string& str); /*!*/
			//string* get_provider_list();	/*!*/

			// Setters
			void reg( Produto* prod );	/**< Cadastra um produto na lista (se ele ja estiver cadastrado, aumenta a sua quantidade em um) */
			void unreg( typename map<string, Produto*>::iterator& it ); /**< Descadastra um produto */
			void absorb_qnt(typename map<string, Produto*>::iterator it, const int x); /**<  Move um número de unidades do produto apontado por 'it' a Cesta que chamou está função. */
			void clear();	/**< Limpa o mapa interno, desalocando tudo e removendo os pares existentes */
			void fetch_from( Cesta& orig, const string& m_search);
			void fetch_type_and_provider_from( Cesta& orig, const string& m_type, const string& m_provider );
			
			// Printers
			void print( std::ostream& out );	/**< Imprime uma lista com todos os produtos do grupo */ 
			void print_type( std::ostream& out, const string& my_type );	/**< Imprime produtos de um tipo */
			void print_provider( std::ostream& out, const string& my_provider );	/**< Imprime produtos de um provedor */
			void print_notafiscal(std::ostream& out); /**<  Imprime os Produtos no formato de um cupom fiscal da loja */ 
			
			// Manipulação de arquivos
			bool save();	/**<  Salva os Produtos e listas desta Cesta em um arquivo .csv */ 
			bool load();	/**<  Carrega os Produtos e listas desta Cesta de um arquivo .csv */
			bool export_csv(const char* filename, int& print_full);

			// Sobrecarga de operadores
			bool operator== ( Cesta& direita);	/**< Compara um grupo com outro pra ver se são iguais (possuem a mesma lista de produtos)*/
			Cesta& operator= (Cesta& direita);	/**< Atribui a lista de um grupo para este */
			//friend &istream operator>> (istream &in, const Produto x);	/**< Sobrecarga do >> */

			// Friends
			friend void menu_principal (Cesta& m_loja, Cesta& m_cliente);
			friend bool sub_modificar(typename map<string, Produto*>::iterator& it, Cesta& target );
			friend void sub_encontrou_produto( typename map<string, Produto*>::iterator& it, Cesta& m_loja, Cesta& m_cliente, direction my_case );
			friend void sub_consulta (Cesta& m_loja, Cesta& m_cliente, direction my_case );
			friend void sub_cadastro_loja(Cesta& target);
			friend void sub_venda(Cesta &m_loja, Cesta& m_cliente);
	};
}


#include "Produto.h"
#include "CD.h"
#include "Salgado.h"
#include "Cesta.h"


#endif
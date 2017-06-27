#ifndef PRODUTOS_H
#define PRODUTOS_H

/**
* @file
* @brief Definição e implementação da classe Produto
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "header.h"

/**
* @class Produto
* @brief Classe abstrata contendo as principais características comuns aos produtos da loja.
*/
class Produto
{
	//friend class Bau;

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

		void change_product_specs();	/**< Modifica uma por uma as características do produto */

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
		virtual float get_alchool() {return 0;}	/**< Retorna o teor alcoólico (em %) do produto (float) */
		virtual float get_sugar() {return 0;}	/**< Retorna a taxa de açucar (em mg) do produto (float) */
		virtual float get_sodium() {return 0;}	/**< Retorna a taxa de sódio (em mg) do produto */
		virtual bool get_gluten() {return true;}	/**< Retorna se o produto contém glúten ou não */
		virtual bool get_lactose() {return true;}	/**< Retorna se o produto contém lactose ou não */
		virtual int get_number() {return 0;}	/**< Retorna o número do lote do produto (int) */
		virtual string get_date() {return "";}	/**< Retorna a data de produção do lote do produto (string) */
		
		virtual string get_name() {return "";}	/**< Retorna título do CD (string) */
		virtual string get_title() {return "";}	/**< Retorna o título do livro (string) */
		virtual string get_artist() {return "";}	/**< Retorna artista do CD (string) */
		virtual string get_author() {return "";}	/**< Retorna o autor do livro (string) */
		virtual string get_style() {return "";}	/**< Retorna o estilo do CD (string) */
		virtual string get_genre() {return "";}	/**< Retorna o gênero do produto */
		virtual string get_publisher() {return "";}	/**< Retorna a editora do livro (string) */
		virtual int get_duration() {return 0;}	/**< Retorna a duração (em minutos) do DVD (int) */
		virtual int get_year() {return 0;}	/**< Retorna ano de publicação do livro (int) */

		//Setters
		virtual void set_expiration(const string &x) {}	/**< Altera o vencimento do produto (string) */
		virtual void set_alchool(const float &x) {}	/**< Altera o teor alcoólico (em %) do produto (float) */
		virtual void set_sugar(const float &x) {}	/**< Altera a taxa de açucar (em mg) do produto (float) */
		virtual void set_sodium(const float &x) {}	/**< Altera a taxa de açucar (em mg) do produto */
		virtual void set_gluten(const bool &x) {}	/**< Altera o atributo que diz se o produto contém glúten ou não */
		virtual void set_lactose(const bool &x) {}	/**< Altera o atributo que diz se o produto contém lactose ou não */
		virtual void set_number(const int &x) {}	/**< Altera o número do lote do produto (int) */
		virtual void set_date(const string &x) {}	/**< Altera data de produção do lote do produto (string) */
		
		virtual void set_name(const string &x) {}	/**< Altera título do CD (string) */
		virtual void set_title(const string &x) {}	/**< Altera o título do livro */
		virtual void set_artist(const string &x) {}	/**< Altera artista do CD (string) */
		virtual void set_author(const string &x) {}	/**< Altera o autor do livro (string) */
		virtual void set_style(const string &x) {}	/**< Altera o estilo do CD (string) */
		virtual void set_genre(const string &x) {}	/**< Altera o gênero do DVD */
		virtual void set_duration(const int &x) {}	/**< Altera a duração (em minutos) do DVD (int) */
		virtual void set_publisher(const string &x) {}	/**< Altera a editora do livro (string) */
		virtual void set_year(const int &x) {} /**< Altera o ano de publicação do livro (int) */

		virtual void change() =0;
		
		// auxiliar da sobrecarga de extração
		virtual void print_it (std::ostream& out) const =0;	/**< Função virtual pura que define como vai ser a impressão das informações do produto */
		virtual void save_csv_it (std::ofstream& out) =0;	/**< Função virtual pura que define como vai ser salva as informações dos produtos em um arquivo .csv */
		virtual void load_csv_it (std::ifstream& in) =0;	/**< Função virtual pura que define como seram lidas as informações dos produtos de um arquivo .csv */
		void save_csv_P (std::ofstream& out);
		
};

// ============ Implementação ============

//  == Sobrecarga de operadores ==

/**
* @param x Referência para o Produto a ter seu preço usado como segunda parcela de uma soma
* @return Um float com o valor do preço do produto atual + o preço do produto 'x'
*/
float Produto::operator+(const Produto &x)
{
	return( (this->price * this->quantity ) + ( x.price * x.quantity ) ) ;
}

/**
* @param y Float usado como primeira parcela de uma soma
* @param x Referência para o Produto a ter seu preço usado como segunda parcela de uma soma
* @return Um float com o valor do preço do produto atual + o preço do produto 'x'
*/
float operator+ (float y, const Produto &x)
{
	return( y + ( x.price * x.quantity ) );
}

/**
* @param x Referência para o Produto a ter seu preço usado como segunda parcela da subtração
* @return Um float com o valor do preço do produto atual - o preço do produto 'x'
*/
float Produto::operator-(const Produto &x)
{
	return( (this->price * this->quantity ) - ( x.price * x.quantity ) );
}

/**
* @param y Float usado como primeira parcela de uma subtração
* @param x Referência para o Produto a ter seu preço usado como segunda parcela de uma subtração
* @return Um float com o valor do preço do produto atual - o preço do produto 'x'
*/
float operator-(float y, const Produto &x)
{
	return( y - ( x.price * x.quantity ) );
}

// Comparação

/**
* @param x Referência para o Produto a ser comparado
* @returns Se os produtos comparados tem códigos de barras iguais
*/
bool Produto::operator== (const Produto &x)
{
	return (stoull(barcode) == stoull(x.barcode));
}

/**
* @param x Referência para o Produto a ser comparado
* @returns Se os produtos comparados tem códigos de barras diferentes
*/
bool Produto::operator!= (const Produto &x)
{
	return (*this != x);
}

/**
* @param x Referência para o Produto a ter seu código de barras comparado
*/
bool Produto::operator>( const Produto &x){
	return (stoull(barcode) > stoull(x.barcode));
}

/**
* @param x Referência para o Produto a ter seu código de barras comparado
*/
bool Produto::operator<( const Produto &x){
	return (stoull(barcode) < stoull(x.barcode));
}

/**
* @param x Referência para o Produto a ter seu código de barras comparado
*/
bool Produto::operator>= ( const Produto &x){
	//return (*this > x) or (barcode == x.barcode));
	return ((*this > x) or (*this == x));
}

/**
* @param x Referência para o Produto a ter seu código de barras comparado
*/
bool Produto::operator<= ( const Produto &x){
	//return ((barcode < x.barcode) or (barcode == x.barcode));
	return ((*this < x) or (*this == x));
}

// Auxiliares de alteração


bool my_question(const char* question){
	
	char answer;
	int counter = 0;
	do
	{
		cout << question << " ('y' para sim e 'n' para não) >>";
		cin >> answer;
		cin.ignore();
		if(counter++ > 0)cout << "Input inválido. Tente de novo. >>";
	}
	while( answer != 'y' and answer != 'n');
	return ( answer == 'y');	// retorna true se a resposta for positiva;
}

void Produto::change_product_specs()
{
	string new_s;

	cout << "Fornecedor atual: \""<< get_provider()<< "\".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo fornecedor. >>" ;
		getline(cin, new_s,'\n');
		//cin.ignore();
		set_provider(new_s);
		cout << endl;
	}

	cout << "Preço atual: $"<< get_price()<< ".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo preço. >>" ;
		getline(cin, new_s, '\n');	
		//cin.ignore();
		set_price( std::stof(new_s) );
	}

	cout << "Código de barras atual: "<< get_barcode()<< ".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo codigo de barras. >>" ;
		getline(cin, new_s, '\n');	
		//cin.ignore();
		set_barcode(new_s);
	}

	cout << "Quantidade atual: "<< get_quantity()<< ".";
	if (my_question(" Deseja alterar?") ){
	cout << "Insira nova quantidade. >>" ;
		getline(cin, new_s, '\n');	
		//cin.ignore();
		set_quantity( std::stoi(new_s) );
	}
}

void Produto::save_csv_P(std::ofstream& out)
{
	out << '\"' << product_type << "\";"	//"tipo";
		<< '\"' << provider << "\";"	//"fornecedor";
		<< price << ";"	//preço;
		<< '\"' << barcode << "\";"	//"codigo_de_baras";
		<< quantity	//quantidade;
		<< endl;

	// Exemplo de impressão:
	//"Salgado";"Salgarilhos";2;"000000133";5
	//
}

#include "Produto_tipos.h"

#endif
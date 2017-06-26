#ifndef CD_H
#define CD_H

/**
* @file
* @brief Implementação de um CD (derivado da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"
#include "header.h"

/**
* @class CD
* @brief Herdeira da classe Produto, usada para produtos do tipo cd
*/
class CD : public Produto
{
	//friend class Cesta;

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
		void change(); /**< Altera tudo do CD */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
		void save_csv_it (std::ofstream& out);	/**< Função que define como vai ser salva as informações dos produtos em um arquivo .csv */
		void load_csv_it (std::ifstream& in);	/**< Função que define como seram lidas as informações dos produtos de um arquivo .csv */
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void CD::print_it(std::ostream& out) const
{
	out << "Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço (unidade): $" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< ", Quantidade: " << quantity
		<< ", Preço Total: $" << 0.0+(*this)
		<< "\n+\tTítulo: \"" << name << "\""
		<< " , Artista: " << artist
		<< " , Estilo: " << style;
}

/**
* @param out Referência para um stream de saída para um arquivo
*/
void CD::save_csv_it(std::ofstream& out)
{
	//cout << "here";
	out << '\"' << product_type << "\";"	//"tipo";
		<< '\"' << provider << "\";"	//"fornecedor";
		<< price << ";"	//preço;
		<< '\"' << barcode << "\";"	//"codigo_de_baras";
		<< quantity << ";"	//quantidade;
		//
		<< '\"' << name << "\";"	//"nome";
		<< '\"' << artist << "\";"	//"artista";
		<< '\"' << style << "\""	//"estilo";
		<< endl;

	// Exemplo de impressão:
	//"CD";"Sony Music";9.4;"000000123";2;"Album A";"Artistino";"Forró"
}


void CD::change()
{
	string new_s;

	change_product_specs();

	// PROPRIOS DO PRODUTO

	// Nome
	cout << "Título atual: \""<< get_name()<< "\".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo título. >>" ;
		getline(cin, new_s, '\n');	
		//cin.ignore();
		set_name(new_s);
	}
	// Artista
	cout << "Artista atual: \""<< get_artist()<< "\".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo artista. >>" ;
		getline(cin, new_s,'\n');	
		//cin.ignore();
		set_artist(new_s);
	}
	// Estilo
	cout << "Estilo atual: \""<< get_style()<< "\".";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo estilo. >>" ;
		getline(cin, new_s,'\n');	
		//cin.ignore();
		set_style(new_s);
	}
}

/**
* @param in Referência para um stream de entrada para um arquivo
*/
void CD::load_csv_it (std::ifstream& in)
{
	string dummy;

	// Fornecedor
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "Sony Music"
	set_provider(dummy);	// modifica Fornecedor
	in.ignore(1);	// ignora o ';''
	
	// Preço
	getline(in, dummy, ';');	// ex.: dummy = "9.4"
	set_price( stof(dummy) );	// modifica Fornecedor

	// Código de Barras
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "000000123"
	set_barcode(dummy);	// modifica Código de Barras
	in.ignore(1);	// ignora o ';'
		
	// Quantidade
	getline(in, dummy, ';');	// ex.: dummy = "2"
	set_quantity( stoi(dummy) );	// modifica Quantidade

	// 

	// nome
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "Album A"
	set_name(dummy);	// modifica nome
	in.ignore(1);	// ignora o ';'

	// artista
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "Artistino"
	set_artist(dummy);	// modifica artista
	in.ignore(1);	// ignora o ';'

	// estilo
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "Forró"
	set_style(dummy);	// modifica estilo
	in.ignore(1);	// ignora o primeiro '\n'
	
	// fim da linha
}


#endif

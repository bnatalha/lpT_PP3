#ifndef LIVRO_H
#define LIVRO_H

/**
* @file
* @brief Implementação de um Livro (derivado da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"

/**
* @class Livro
* @brief Herdeira da classe Produto, usada para produtos do tipo livro
*/
class Livro : public Produto
{
	private:
		string title; 	/**< titulo do Livro */
		string author;	/**< autor do Livro */
		string publisher; /**< editora do Livro */
		int year;	/**< ano em que o livro foi publicado */

	public:

		/**
		* @brief Constrói um objeto Livro sem especificar seus dados
		* @sa Chamando construtor da classe Mãe na classe filha no construtoe(http://www.studytonight.com/cpp/order-of-constructor-call.php)
		*/
		Livro() 
			: Produto("Livro","", 0, "00000000"), title(""), author(""), publisher(""), year(0)
		{}

		/**
		* @brief Constrói um objeto Livro especificando seus atributos a partir de passagem de parâmetros
		*/
		Livro(string titulo, string autor, string edit, int ano) 
			: Produto("Livro","", 0, "00000000"), title(titulo), author(autor), publisher(edit), year(0)
		{}

		// Métodos

		// Gets
		string get_title() { return title; }	/**< Retorna o título do livro (string) */
		string get_author() { return author; }	/**< Retorna o autor do livro (string) */
		string get_publisher() { return publisher; }	/**< Retorna a editora do livro (string) */
		int get_year() { return year; }	/**< Retorna ano de publicação do livro (int) */

		// Sets
		void set_title(const string &x) { title = x; }	/**< Altera o título do livro (string) */
		void set_author(const string &x) { author = x; }	/**< Altera o autor do livro (string) */
		void set_publisher(const string &x) { publisher = x; }	/**< Altera a editora do livro (string) */
		void set_year(const int &x) { year = x; } /**< Altera o ano de publicação do livro (int) */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void Livro::print_it(std::ostream& out) const
{
	out << "[Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: R$" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< "\n/\\\tTítulo: \"" << title << "\""
		<< " , Autor: " << author
		<< " , Editora: " << publisher
		<< " , Ano de publicação: " << year
		<< "]";
}

#endif

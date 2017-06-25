#ifndef DVD_H
#define DVD_H

/**
* @file
* @brief Implementação de um DVD (derivado da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"

/**
* @class DVD
* @brief Herdeira da classe Produto, usada para produtos do tipo DVD
*/
class DVD : public Produto
{
	private:
		string title; 	/**< titulo do DVD */
		string genre;	/**< genero do DVD */
		int duration;	/**< duracao do DVD, em minutos */

	public:

		/**
		* @brief Constrói um objeto DVD especificando seus atributos a partir de passagem de parâmetros
		*/
		DVD() 
			: Produto("DVD","", 0, "00000000"), title(""), genre(""), duration(0)
		{}

		/**
		* @brief Constrói um objeto DVD sem especificar seus dados
		*/
		DVD(string titulo, string genero, int duracao) 
			: Produto("DVD","", 0, "00000000"), title(titulo), genre(genero), duration(duracao)
		{}

		// Métodos

		// Gets
		string get_title() { return title; }	/**< Retorna o título do produto*/
		string get_genre() { return genre; }	/**< Retorna o gênero do produto */
		int get_duration() { return duration; }	/**< Retorna a duração (em minutos) do DVD (int) */

		// Sets
		void set_title(const string &x) { title = x; }	/**< Altera o título do DVD */
		void set_genre(const string &x) { genre = x; }	/**< Altera o gênero do DVD */
		void set_duration(const int &x) { duration = x; }	/**< Altera a duração (em minutos) do DVD (int) */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */

		friend class Produto;
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void DVD::print_it(std::ostream& out) const
{
	out << "[Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: R$" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< "\n/\\\t Título: \"" << title << "\""	
		<< " , Gênero: " << genre
		<< " , Duração: " << duration << "min"
		<< "]";
}

#endif

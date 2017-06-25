#ifndef FRUTA_H
#define FRUTA_H

/**
* @file
* @brief Implementação de um Fruta (derivados da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"

/**
* @class Fruta
* @brief Herdeira da classe Produto, usada para produtos do tipo fruta
*/
class Fruta : public Produto
{
	private:
		string expiration; /**< Vencimento da fruta */
		int number;	/**< Número do lote */
		string date;	/**< Data de producao do lote */

	public:

		/**
		* @brief Constrói um objeto Fruta sem especificar seus dados
		*/
		Fruta() 
			: Produto("Fruta","", 0, "00000000"), expiration(""), number(0), date("")
		{}

		/**
		* @brief Constrói um objeto Fruta especificando seus atributos a partir de passagem de parâmetros
		*/
		Fruta(string vencimento, int numero, string data) 
			: Produto("Fruta","", 0, "00000000"), expiration(vencimento), number(numero), date(data)
		{}

		// Métodos

		// Gets
		string get_expiration() { return expiration; }	/**< Retorna o vencimento do produto (string) */
		int get_number() { return number; }	/**< Retorna o número do lote do produto (int) */
		string get_date() { return date; }	/**< Retorna a data de produção do lote do produto (string) */

		// Sets
		void set_expiration(const string &x) { expiration = x; }	/**< Altera o vencimento do produto (string) */
		void set_number(const int &x) { number = x; }	/**< Altera o número do lote do produto (int) */
		void set_date(const string &x) { date = x; }	/**< Altera data de produção do lote do produto (string) */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void Fruta::print_it(std::ostream& out) const
{
	out << "[Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: R$" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< "\n/\\\tVencimento: " << expiration
		<< " , Lote: " << number
		<< " , Data de produção do lote: " << date
		<< "]";
}

#endif
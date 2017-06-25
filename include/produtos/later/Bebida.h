#ifndef BEBIDA_H
#define BEBIDA_H

/**
* @file
* @brief Implementação dos tipos de produtos (derivados da classe Produto)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"

/**
* @class Bebida
* @brief Herdeira da classe Produto, usada para produtos do tipo bebida
*/
class Bebida : public Produto
{
	private:
		string expiration; /**< Vencimento da bebida */
		float alchool;	/**< Teor alcoólico (em %) */
		float sugar;	/**< Taxa de açucar (em mg) */

	public:

		/**
		* @brief Constrói um objeto Bebida sem especificar seus dados
		*/
		Bebida() 
			: Produto("Bebida","", 0, "00000000"), expiration(""), alchool(0), sugar(0)
		{}

		/**
		* @brief Constrói um objeto Bebida especificando seus atributos a partir de passagem de parâmetros
		*/
		Bebida(string vencimento, float teor_alcool, float acucar_mg) 
			: Produto("Bebida","", 0, "00000000"), expiration(vencimento), alchool(teor_alcool), sugar(acucar_mg)
		{}

		~Bebida(){}

		// Métodos

		// Gets
		string get_expiration() { return expiration; }	/**< Retorna o vencimento do produto (string) */
		float get_alchool() { return alchool; }	/**< Retorna o teor alcoólico (em %) do produto (float) */
		float get_sugar() { return sugar; }	/**< Retorna a taxa de açucar (em mg) do produto (float) */

		// Sets
		void set_expiration(const string &x) { expiration = x; }	/**< Altera o vencimento do produto (string) */
		void set_alchool(const float &x) { alchool = x; }	/**< Altera o teor alcoólico (em %) do produto (float) */
		void set_sugar(const float &x) { sugar = x; }	/**< Altera a taxa de açucar (em mg) do produto (float) */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void Bebida::print_it(std::ostream& out) const
{
	out << "[Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: R$" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< "\n/\\\tVencimento: " << expiration
		<< " , Teor alcoólico: " << alchool << "%"
		<< " , Taxa de açucar: " << sugar << "mg"
		<< "]";
}

#endif

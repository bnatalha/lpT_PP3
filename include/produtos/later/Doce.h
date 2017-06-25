#ifndef DOCE_H
#define DOCE_H

/**
* @file
* @brief Implementação de um doce (derivados da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"

/**
* @class Doce
* @brief Herdeira da classe Produto, usada para produtos do tipo doce
*/
class Doce : public Produto
{
	private:
		string expiration; /**< Vencimento do doce */
		float sugar;	/**< Taxa de açucar (em mg) */
		bool gluten;    /**< Se contem glúten ou nao */
		bool lactose;   /**< Se contem lactose ou nao */

	public:

		/**
		* @brief Constrói um objeto Doce sem especificar seus dados
		* @sa Chamando construtor da classe Mãe na classe filha no construtoe(http://www.studytonight.com/cpp/order-of-constructor-call.php)
		*/
		Doce() 
			: Produto("Doce","", 0, "00000000"), expiration(""), sugar(0), gluten(false), lactose(false)
		{}

		/**
		* @brief Constrói um objeto Doce especificando seus atributos a partir de passagem de parâmetros
		*/
		Doce(string vencimento, float acucar, bool glut, bool lacto) 
			: Produto("Doce","", 0, "00000000"), expiration(vencimento), sugar(acucar), gluten(glut), lactose(lacto)
		{}

		// Métodos

		// Gets
		string get_expiration() { return expiration; }	
		float get_sugar() { return sugar; }	/**< Retorna a taxa de açucar (em mg) do produto */
		bool get_gluten() { return gluten; }	/**< Retorna se o produto contém glúten ou não */
		bool get_lactose() { return lactose; }	/**< Retorna se o produto contém lactose ou não */

		// Sets
		void set_expiration(const string &x) { expiration = x; }
		void set_sugar(const float &x) { sugar = x; }	/**< Altera a taxa de açucar (em mg) do produto */
		void set_gluten(const bool &x) { gluten = x; }	/**< Altera o atributo que diz se o produto contém glúten ou não */
		void set_lactose(const bool &x) { lactose = x; }	/**< Altera o atributo que diz se o produto contém lactose ou não */

		// auxiliar da sobrecarga de extração
		void print_it (std::ostream& out) const;	/**< Função que define como vai ser a impressão do produto */
};

// Implementações

/**
* @param out Referência para um stream de saída
* @sa sobrecarga de operadores em subclasses (https://stackoverflow.com/questions/19376943/)
*/
void Doce::print_it(std::ostream& out) const
{
	out << "[Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: R$" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< "\n/\\\tVencimento: " << expiration
		<< " , Taxa de açucar: " << sugar << "mg"			
		<< " , Contem glúten: " << (gluten? "Sim":"Não")
		<< " , Contem lactose: " << (lactose? "Sim":"Não")
		<< "]" << endl;
}

#endif

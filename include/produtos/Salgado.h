#ifndef SALGADO_H
#define SALGADO_H

/**
* @file
* @brief Implementação de um Salgado (derivados da classe Produto)
* @author Michel Jean Katsilis (https://github.com/MJK2)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

#include "Produto.h"
#include "header.h"

/**
* @class Salgado
* @brief Herdeira da classe Produto, usada para produtos do tipo salgado
*/
class Salgado : public Produto
{
	//friend class Cesta;
	
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
		void change(); /**< Altera tudo do Salgado */

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
void Salgado::print_it(std::ostream& out) const
{
	out << "Produto: " <<  product_type
		<< ", Fornecedor: " << provider
		<< ", Preço: $" << price	// Trocar '.' por ',' na impressão
		<< ", Código de Barras: " << barcode
		<< ", Quantidade: " << quantity
		<< ", Preço Total: $" << 0.0+(*this)
		<< "\n+\tVencimento: " << expiration
		<< " , Taxa de sódio: " << sodium << "mg"
		<< " , Contem glúten: " << (gluten? "Sim":"Não")
		<< " , Contem lactose: " << (lactose? "Sim":"Não");
}

/**
* @param out Referência para um stream de saída para um arquivo
*/
void Salgado::save_csv_it(std::ofstream& out)
{
	out << '\"' << product_type << "\";"	//"tipo";
		<< '\"' << provider << "\";"	//"fornecedor";
		<< price << ";"	//preço;
		<< '\"' << barcode << "\";"	//"codigo_de_baras";
		<< quantity << ";"	//quantidade;
		//
		<< '\"' << expiration << "\";"	//"vencimento";
		<< sodium << ";"	//"taxa de sódio (em mg)";
		<< (gluten?'y':'n') << ";"	//'contem glutem';
		<< (lactose?'y':'n')	//'contem lactose'
		<< endl;

	// Exemplo de impressão:
	//"Salgado";"Salgarilhos";2;"000000133";5;"14/06/17";34;y;n
	
}

void Salgado::change()
{

	float new_f;

	// MUDANÇAS COMUNS DE PRODUTOS
	change_product_specs();

	// PROPRIOS DO PRODUTO

	// SODIO
	cout << "Taxa de sódio atual: "<< get_sodium()<< "mg.";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo sódio. >>" ;
		cin >> new_f;	// Armazena o novo sódio em 'new_'
		cin.ignore();
		set_sodium(new_f);	// Modifica o sódio para o conteudo de 'new_'
	//	cout << "sódio: \"" << get_sodium() << "\"" << endl;
	}

	// GLUTEN
	cout << "Glutem atual: " << (get_gluten()?"":"NÃO ") << "contém\".";
	if ( my_question(" Deseja alterar?") ) set_gluten( !get_gluten() );

	//LACTOSE
	cout << "Lactose atual:  \"" << (get_lactose()?"":"NÃO ") << "contém\".";
	if ( my_question(" Deseja alterar?") ) set_lactose( !get_lactose() );
}

/**
* @param in Referência para um stream de entrada para um arquivo
*/
void Salgado::load_csv_it (std::ifstream& in)
{
	string dummy;

	// Fornecedor
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "Sony Music"
	set_provider(dummy);	// modifica Fornecedor
	in.ignore(1);	// ignora o ';''

	// Preço
	getline(in, dummy, ';');	// ex.: dummy = "9.4"
	set_price( std::stof(dummy) );	// modifica Fornecedor

	// Código de Barras
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "000000123"
	set_barcode(dummy);	// modifica Código de Barras
	in.ignore(1);	// ignora o ';'
		
	// Quantidade
	getline(in, dummy, ';');	// ex.: dummy = "2"
	set_quantity( std::stoi(dummy) );	// modifica Quantidade

	// 

	// validade
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "13/04/18"
	set_expiration(dummy);	// modifica a validade
	in.ignore(1);	// ignora o ';'

	// sódio
	getline(in, dummy, ';');	// ex.: dummy = "24"
	set_sodium( std::stof(dummy) );	// modifica sódio

	// glutem
	getline(in, dummy, ';');	// ex.: dummy = true
	set_gluten( (dummy == "y" ?true:false) );	// modifica glutem

	// lactose
	getline(in, dummy);	// ex.: dummy = false
	set_lactose( (dummy == "y" ?true:false) );	// modifica lactose
	//in.ignore(1);	// ignora o primeiro '\n'
	
	// fim da linha
}

#endif
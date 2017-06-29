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

#include "qlevetudo.h"

namespace qlt
{
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

bool Salgado::change()
{
	string new_s;

	// MUDANÇAS COMUNS DE PRODUTOS
	bool barcode_changed = change_product_specs();

	// PROPRIAS DESTE TIPO

	// SODIO
	cout << "Taxa de sódio atual: "<< get_sodium()<< "mg.";	
	if (my_question(" Deseja alterar?") ){
		cout << "Insira novo valor. >>" ;
		getline(cin, new_s,'\n');
		try{set_sodium( std::stof(new_s) );	// Tenta mudar o valor do sódio
		}catch (std::exception &e){
			cout << "Valor inválido inválido. Setando para 5mg.";
			set_sodium(5);
		}
	}

	// GLUTEN
	cout << "Glutem atual: " << (get_gluten()?"":"NÃO ") << "contém\".";
	if ( my_question(" Deseja alterar?") ) set_gluten( !get_gluten() );

	//LACTOSE
	cout << "Lactose atual:  \"" << (get_lactose()?"":"NÃO ") << "contém\".";
	if ( my_question(" Deseja alterar?") ) set_lactose( !get_lactose() );

	return barcode_changed;
}

/**
* @param in Referência para um stream de entrada para um arquivo
*/
void Salgado::load_csv_it (std::ifstream& in)
{
	string dummy;

	// Validade

	// exceção:
	if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Validade.");
	in.ignore(1);	// ignora o primeiro '\"'
	getline(in, dummy, '\"');	// ex.: dummy = "13/04/18"
	// exceção:
	try{
		if(dummy.size() != 8) throw std::runtime_error("Quantidade de caractéres inválida.");
		if( (isdigit(dummy.at(0)) == false) or (isdigit(dummy.at(1)) == false) or
			(dummy.at(2) != '/') or
			(isdigit(dummy.at(3)) == false) or (isdigit(dummy.at(4)) == false) or
			(dummy.at(5) != '/') or
			(isdigit(dummy.at(6)) == false) or (isdigit(dummy.at(7)) == false))	// se conter algum caractere inválido
		throw std::runtime_error("Formato inválido.");
	}catch(std::exception &e){
		string error = "Em validade: ";
		error += e.what();
		throw std::runtime_error(error+"\nFormato correto: \"13/04/18\")");
	}
	set_expiration(dummy);	// modifica a validade
	// exceção:
	if( char(in.peek()) != ';' ) throw std::runtime_error("Faltando ';' entre Validade e Sódio.");
	in.ignore(1);	// ignora o ';'

	// Sódio

	// exceção:
	getline(in, dummy, ';');	// ex.: dummy = "24"
	// exceção:
	try{set_sodium( std::stof(dummy) );}	// modifica sódio
	catch(std::exception& e){
		throw std::runtime_error("Valor do sódio inválido");
	}

	// Glutem

	// exceção:
	if( char(in.peek()) != 'y' and char(in.peek()) != 'n'  ) throw std::runtime_error("Valor do glutem inválido.");
	getline(in, dummy, ';');	// ex.: dummy = "n"
	// exceção:
	set_gluten( (dummy == "y" ?true:false) );	// modifica glutem

	// lactose
	if( char(in.peek()) != 'y' and char(in.peek()) != 'n'  ) throw std::runtime_error("Valor de lactose inválido.");
	getline(in, dummy);	// ex.: dummy = "y"
	set_lactose( (dummy == "y" ?true:false) );	// modifica lactose
	
	// fim da linha
}
}
#endif
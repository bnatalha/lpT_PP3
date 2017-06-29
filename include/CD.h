#ifndef CD_H
#define CD_H

/**
* @file
* @brief Implementação de um CD (derivado da classe Produto)
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 04/06/2017
* @date --
* @sa --
*/

//#include "Produto.h"
#include "qlevetudo.h"

namespace qlt{

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

	/**
	* @return true se tiver alterado o codigo de barras. false caso contrário.
	*/
	bool CD::change()
	{
		string new_s;

		// MUDANÇAS COMUNS DE PRODUTOS
		bool barcode_changed = change_product_specs();

		// PROPRIOS DESTE TIPO DE PRODUTO

		// Nome
		cout << "Título atual: \""<< get_name()<< "\".";	
		if (my_question(" Deseja alterar?") ){
			cout << "Insira novo título. >>" ;
			getline(cin, new_s, '\n');	
			set_name(new_s);
		}
		// Artista
		cout << "Artista atual: \""<< get_artist()<< "\".";	
		if (my_question(" Deseja alterar?") ){
			cout << "Insira novo artista. >>" ;
			getline(cin, new_s,'\n');
			set_artist(new_s);
		}
		// Estilo
		cout << "Estilo atual: \""<< get_style()<< "\".";	
		if (my_question(" Deseja alterar?") ){
			cout << "Insira novo estilo. >>" ;
			getline(cin, new_s,'\n');
			set_style(new_s);
		}

		return barcode_changed;
	}

	/**
	* @param in Referência para um stream de entrada para um arquivo
	*/
	void CD::load_csv_it (std::ifstream& in)
	{
		string dummy;

		// Nome

		// exceção:
		if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Nome.");
		in.ignore(1);	// ignora o primeiro '\"'
		getline(in, dummy, '\"');	// ex.: dummy = "Album A"
		set_name(dummy);	// modifica nome
		// exceção:
		if( char(in.peek()) != ';' ) throw std::runtime_error("Faltando ';' entre Nome e Artista.");
		in.ignore(1);	// ignora o ';'

		// Artista

		// exceção:
		if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Artista.");
		in.ignore(1);	// ignora o primeiro '\"'
		getline(in, dummy, '\"');	// ex.: dummy = "Artistino"
		set_artist(dummy);	// modifica artista
		// exceção:
		if( char(in.peek()) != ';' ) throw std::runtime_error("Faltando ';' entre Artista e Estilo.");
		in.ignore(1);	// ignora o ';'

		// Estilo

		// exceção:
		if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Estilo.");
		in.ignore(1);	// ignora o primeiro '\"'
		getline(in, dummy, '\"');	// ex.: dummy = "Forró"
		set_style(dummy);	// modifica estilo
		// exceção:
		if( char(in.peek()) != '\n' ) throw std::runtime_error("Faltando nova linha após Estilo.");
		in.ignore(1);	// ignora o primeiro '\n'
		
		// fim da linha
	}
}

#endif

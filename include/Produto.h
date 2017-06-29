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

#include "qlevetudo.h"

namespace qlt{

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

	/**
	* @brief pergunta ao usuário uma questão simples que requer como resposta "sim" ou "não". Não deixa
	* o usuário prosseguir até receber uma resposta válida.
	* @param question armazena a pergunta que será feita ao usuario
	* @retval true O usuário respondeu "sim" ('y')
	* @retval false O usuário respondeu "não" ('n')
	*/
	bool my_question(const char* question){
		string my_prompt(" ('y' para sim e 'n' para não) >>");	// orientação ao usuário
		char answer[30];	// armazena a resposta do usuário
			
		cout << question << my_prompt;	// mostra a orientação ao usuário;
		
		do //enquanto o usuário não responde com 'n' ou 'y'
		{
			cin.getline(answer,30);	//pega a resposta
			
			// se pegar falhar a entrada, ou cin.getline tiver extraido mais que dois caracteres ou não for y ou n
			try{if(cin.fail() or cin.gcount()>2 or (strcmp(answer,"y")!=0 and strcmp(answer,"n")!=0) )
				throw std::invalid_argument("Input inválido.");	//Joga uma exceção de entrada inválida
			}catch(std::exception &e){
				cout << e.what() << my_prompt;
			}
		}
		while( (strcmp(answer,"y") !=0 and strcmp(answer,"n")!=0 ) );
		return ( strcmp(answer,"y") == 0 );	// retorna true se a resposta for "sim"
	}

	/**
	* @return true se alterou o código de barras do produto
	*/
	bool Produto::change_product_specs()
	{
		bool barcode_changed = false;

		string new_s;	//string que armazena o dado que o usuário irá passar

		cout << "Fornecedor atual: \""<< get_provider()<< "\".";	// Mostra o fornecedor atual do produto
		if (my_question(" Deseja alterar?") ){	// Pergunta ao usuário se ele deseja trocar o fornecedor do produto
			cout << "Insira novo fornecedor. >>" ;
			getline(cin, new_s,'\n');
			set_provider(new_s);
			cout << endl;
		}

		cout << "Preço atual: $"<< get_price()<< ".";	
		if (my_question(" Deseja alterar?") ){ // Pergunta ao usuário se ele deseja trocar o preço do produto
			cout << "Insira novo preço. >>" ;
			getline(cin, new_s,'\n');
			try{set_price( std::stof(new_s) );
			}catch (std::exception &e){
				cout << "Preço inválido. Setando em $1.99 ."<< endl;
				set_price(1.99);
			}
		}

		cout << "Código de barras atual: "<< get_barcode()<< ".";	
		if (my_question(" Deseja alterar?") ){ // Pergunta ao usuário se ele deseja trocar o código de barras do produto
			cout << "Insira novo codigo de barras. >>" ;
			getline(cin, new_s, '\n');
			if(new_s != get_barcode())	
			set_barcode(new_s);
		}

		cout << "Quantidade atual: "<< get_quantity()<< ".";
		if (my_question(" Deseja alterar?") ){ // Pergunta ao usuário se ele deseja trocar a quantidade do produto
			cout << "Insira nova quantidade. >>" ;
			getline(cin, new_s,'\n');
			try{set_quantity( std::stoi(new_s) );
			}catch (std::exception &e){
				cout << "Quantidade inválida. Setando em 1 ."<< endl;
				set_quantity(1);
			}
		}

		return barcode_changed;
	}

	/**
	* @param out Referência para um stream de saída para um arquivo
	*/
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

	/**
	* @param in Referência para um stream de entrada para um arquivo
	*/
	void Produto::load_csv_P (std::ifstream& in)
	{
		string dummy;

		// Fornecedor
		
		// exceção:
		if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Fornecedor.");
		in.ignore(1);	// ignora o primeiro '\"'
		getline(in, dummy, '\"');	// ex.: dummy = "Sony Music"
		set_provider(dummy);	// modifica Fornecedor
		// exceção: 
		if( char(in.peek()) != ';' ) throw std::runtime_error("Faltando ';' entre Fornecedor e Preço.");	
		in.ignore(1);	// ignora o ';'

		// Preço
		getline(in, dummy, ';');	// ex.: dummy = "9.4"
		//exceção
		try{set_price( std::stof(dummy) );}	// modifica Fornecedor
		catch(std::exception& e){
			throw std::runtime_error("Preço inválido");
		}

		// Código de Barras
		// exceção:
		if( char(in.peek()) != '\"' ) throw std::runtime_error("Faltando aspas em Código de barras.");
		in.ignore(1);	// ignora o primeiro '\"'
		getline(in, dummy, '\"');	// ex.: dummy = "000000123"
		set_barcode(dummy);	// modifica Código de Barras
		// exceção: 
		if( char(in.peek()) != ';' ) throw std::runtime_error("Faltando ';' entre Código de barras e Quantidade.");
		in.ignore(1);	// ignora o ';'
			
		// Quantidade
		getline(in, dummy, ';');	// ex.: dummy = "2"
		// exceção: 
		try{set_quantity( std::stoi(dummy) );}	// modifica Quantidade
		catch(std::exception& e){
			throw std::runtime_error("Quantidade inválida");
		}
	}

}

#endif
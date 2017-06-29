#ifndef Cesta_H
#define Cesta_H

/**
* @file
* @brief Definição e implementação da classe Produto
* @author Natália Azevedo de Brito (https://github.com/bnatalha)
* @since 05/06/2017
* @date 29/06/2017
* @sa --
*/

#include "qlevetudo.h"

namespace qlt{



// =================================================================================
// ================================= IMPLEMENTAÇÃO ================================= 


// -------------------------------------------------
// ----------------------------------------- Getters 

int Cesta::units()
{
	int sum = 0;	// Vai armazenar a soma total de unidades de todos os produtos do grupo

	for( auto &e: produtos )
		sum += e.second->get_quantity() ;	// Soma as quantidades

	return sum;
}

int Cesta::size()
{
	return produtos.size();
}


float Cesta::price()
{
	float sum = 0;	// Vai armazenar a soma total de preços de todos os produtos do grupo

	for( auto &e: produtos )
		sum = sum + *(e.second) ;	// Soma os preços

	return sum;
}

/**
* @param m_barcode código de barras do Produto procurado
* @return Interator pra localização do Produto procurado na lista. Se o iterator for igual ao fim da lista, o produto buscado não foi achado.
*/
typename map<string, Produto*>::iterator Cesta::search( const string& m_barcode )
{
	typename map<string, Produto*>::iterator it = produtos.find(m_barcode);	// procura pelo codigo de barras em 'produtos'

	return it;	// *se it == produtos.end(), não encontrou.
}

// -------------------------------------------------
// ----------------------------------------- Setters 


/*
* @param prod Produto utilizado na função
*/
void Cesta::reg( Produto* prod )
{
	typename map<string, Produto*>::iterator it = search(prod->get_barcode());	// Iterator para o produto

	if (it != produtos.end())	// Se o produto ja foi registrado
		cout << " Produto ja tinha sido registrado." << endl;
	else	// Se o produto ainda não foi registrado
	{
		produtos.insert(std::pair<string, Produto*>(prod->get_barcode(),prod));	// Regista o produto.
		cout << " Produto foi registrado.";
	}

	// Atualiza a lista de fornecedores
/*
	int count = 0;	// guarda o número de vezes que encontrou um produto da cesta que era do mesmo fornecedor que 'prod'
	
	for (map<string,Produto*>::iterator it = produtos.begin(); it!=mymap.end() and count<2; it++)
	{ 
		if(it->second->get_provider() == prod->get_provider()) count++;
	}

	if(count > 2) prod->get_provider() */
}

/**
* @param it Iterator para o produto
*/
void Cesta::unreg( typename map<string, Produto*>::iterator& it )
{
	if(it->second != NULL)	delete (*it).second;	// deleta o conteudo apontado pelo ponteiro para produto (se este não estiver apontando para NULL)
	if(produtos.find(it->first) != produtos.end()) produtos.erase(it);	// deleta o par do mapa, se encontrá-lo.
}

/**
* @param it Iterator para o produto a ser alterado de uma outra Cesta
* @param x inteiro constante com a quantidade de unidades do produto apontado por 'it' que será registrado nessa Cesta
*/
void Cesta::absorb_qnt(typename map<string, Produto*>::iterator it, const int x)
{
	bool found = false;	// Indica se o produto apontado por 'it' foi encontrado na Cesta que chamou esta função

	for(map<string, Produto*>::iterator aqui = produtos.begin();
		aqui != produtos.end(); aqui++)	// Percorre a cesta que chamou a função
	{
		if (aqui->second->get_barcode() == it->second->get_barcode() )	// Se achar o produto que é igual ao apontado por 'it'
		{
			found = true;	// Achou produto na Cesta que chamou esta função

			aqui->second->set_quantity( aqui->second->get_quantity() + x );	// Soma a quantidade disponivel na cesta com 'x'
			(it->second)->set_quantity( (it->second)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'
			
			//cout << "Tit->second = " << it->second << " e aqui->second = " << aqui->second << endl;
			break;	// Sai do loop
		}
	}

	if( found == false )	// Se produto não era cadastrado na Cesta que chamou esta função
	{
		try
		{
			if(it->second->get_type() == "CD") reg( new CD(it->second) );	// Registra o produto na cesta que chamou a função
			else if(it->second->get_type() == "Salgado") reg( new Salgado(it->second) );	// Registra o produto na cesta que chamou a função
		}catch(std::exception &e){cout << "[CAUGHT] absorb_qnt(): " << e.what() << endl; }
				
		for(map<string, Produto*>::iterator aqui = produtos.begin();
			aqui != produtos.end(); aqui++)	// Percorre a cesta que chamou a função
		{
			if (aqui->second->get_barcode() == it->second->get_barcode())	// Quando achar o produto recém registrado
			{
				aqui->second->set_quantity( x );	// Fixa a quantidade disponivel na cesta com 'x'
				(it->second)->set_quantity( (it->second)->get_quantity() - x );	// Subtrai unidades disponíveis de 'it' por 'x'

				//cout << "Fit->second = " << it->second << " e aqui->second = " << aqui->second << endl;
				
				break;	// Sai do loop
			}
		}
	}
}

void Cesta::clear()
{
	for (map<string,Produto* >::iterator it = produtos.begin() ; it != produtos.end(); it++)
		if(it->second != NULL) delete it->second;	// Deleta todos os Produtos alocados no mapa interno da Cesta

	produtos.clear();	// Remove todos os pares do mapa.
}

/**
* @param orig Cesta onde os produtos do tipo 'm_type' seram procurados
* @param m_search O que é procurado (fornecedor ou tipo).
*/
void Cesta::fetch_from( Cesta& orig, const string& m_search )
{
	try
	{
		for( map<string, Produto*>::iterator it = orig.produtos.begin();
			it != orig.produtos.end(); it++)	//utilizando um iterator para a Cesta que está sendo vasculhada
		{
			bool searching_type = is_valid_type(m_search);

			if( (searching_type and (it->second->get_type() == m_search) ) or 
			    (!searching_type and (it->second->get_provider() == m_search) ) )	// Se encontrou o produto
			{
				if(produtos.count( it->second->get_barcode() ) == 0 ) // Caso ele não exista nesta Cesta
				{	
					if(it->second->get_type() == "CD")
					{
						CD *new_cd = new CD(it->second);
						produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_cd));	// O registra como CD.
					}
					if(it->second->get_type() == "Salgado")
					{
						Salgado *new_sal = new Salgado(it->second);
						produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_sal));	// O registra como Salgado.
					}
				}
			}
		}
	}catch(std::exception &e){cout << "[CAUGHT] fetch_from(): " << e.what() << endl; }
}

/**
* @param orig Cesta onde os produtos do tipo 'm_type' seram procurados
* @param m_provider fornecedor procurado
* @param m_type tipo procurado
*/
void Cesta::fetch_type_and_provider_from( Cesta& orig, const string& m_type, const string& m_provider )
{
	try
	{
		for( map<string, Produto*>::iterator it = orig.produtos.begin();
			it != orig.produtos.end(); it++)	//utilizando um iterator para a Cesta que está sendo vasculhada
		{
			if( ( it->second->get_type() == m_type) and 
			    (it->second->get_provider() == m_provider)  )	// Se encontrou o produto
			{
				if(produtos.count( it->second->get_barcode() ) == 0 ) // Caso ele não exista nesta Cesta
				{	
					if(it->second->get_type() == "CD")
					{
						CD *new_cd = new CD(it->second);
						produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_cd));	// O registra como CD.
					}
					if(it->second->get_type() == "Salgado")
					{
						Salgado *new_sal = new Salgado(it->second);
						produtos.insert(std::pair<string, Produto*>(it->second->get_barcode(),new_sal));	// O registra como Salgado.
					}
				}
			}
		}
	}catch(std::exception &e){cout << "[CAUGHT] fetch_type_and_provider_from(): " << e.what() << endl; }
}


// -------------------------------------------------
// ---------------------------------------- Printers


/**
* @param out ostream onde vai ser impressa a função
*/
void Cesta::print( std::ostream& out )
{
	int i = 0;	// índice

	//out << "LISTANDO PRODUTOS: {" << endl;
	for (auto &e: produtos)
	{
		cout << "(" << i++ << "):";
		e.second->print_it(out);
		cout << endl;
	}
	//out << "}" << endl;
}

/**
* @param out ostream onde vai ser impressa a função
* @param my_type Tipo de Produto a ser impresso
*/
void Cesta::print_type( std::ostream& out, const string& my_type )
{
	int i = 0;	// índice

	for (auto &e: produtos)
	{
		if( e.second->get_type() == my_type)	// Se for o tipo que procuro
		{
			cout << "(" << i++ << "):";
			e.second->print_it(out);
			cout << endl;
		}
	}
}

/**
* @param out ostream onde vai ser impressa a função
* @param my_provider Fornecedor dos Produtos a serem impressos em 'out'
*/
void Cesta::print_provider( std::ostream& out, const string& my_provider )
{
	int i = 0;	// índice

	for (auto &e: produtos)
	{
		if( e.second->get_provider() == my_provider)	// Se for o fornecedor que procuro
		{
			cout << "(" << i++ << "):";
			e.second->print_it(out);
			cout << endl;
		}
	}
}

void Cesta::print_notafiscal(std::ostream& out)
{
	out << "________________________________________________________________" << endl;
	out << "------------------------- CUPOM FISCAL -------------------------" << endl;
	out << "________________________________________________________________" << endl;
	out << "====================== MERCADO QLEVE TUDO ======================" << endl;
	out << "=============== Rua Inferno no Céu, n450, Alecrim  =============" << endl;
	out << "________________________________________________________________" << endl;
	out << "----------------------------------------------------------------" << endl;
	if(produtos.empty() == false )
	{
		print_type(out,"CD");
		out << "________________________________________________________________" << endl;
		print_type(out,"Salgado");
		out << "________________________________________________________________" << endl;
	}
	out << "----------------------------------------------------------------" << endl;
	out << "TOTAL: $" << price() << endl;
	out << "----------------------------------------------------------------" << endl;
	out << "Volte sempre!" << endl;
}


// -------------------------------------------------
// ------------------------- Manipulação de Arquivos 

/**
* @return true se conseguiu carregar o a Cesta com sucesso
*/
bool Cesta::load()
{
	string filename("data/my_store.csv");    // Local do arquivo a ser salvo com os dados da cesta
	string dummy_type;	// Armazena o tipo do produto
	int lines = 0;	// marca por quantas novas linhas ja passaram

	// Criando ponteiros para novos tipos
	CD      *new_cd = NULL; 
	Salgado *new_sa = NULL;

	// Abrindo stream de saída
	std::ifstream inData(filename.c_str());

	// Leitura
	if(inData.is_open())
	{
		inData.seekg (0, inData.end);
		int length = inData.tellg();	// Armazena a quantidade de caracteres no arquivo
		inData.seekg (0, inData.beg);	// volta o ponteiro do buffer pro início

		int new_lines = std::count(std::istreambuf_iterator<char>(inData),
  			   std::istreambuf_iterator<char>(), '\n');	// conta quantos '\n' existem no arquivo

		inData.seekg (0, inData.beg);	// volta o ponteiro do buffer pro início

		if(length >= 0)	// Se o arquivo não for vazio
		{
			try
			{
				while( lines <= new_lines and inData.peek() != -1)	// enquanto não chegar ao fim do arquivo
				{
					// primeira exceção: falta aspás no início da definição de tipo (e não estamos na última linha do arquivo)
					if( char(inData.peek()) != '\"') throw std::runtime_error("Faltando aspas em Tipo.");
					inData.ignore(1);	// ignora o primeiro '\"'
					getline(inData, dummy_type, '\"');	// ex.: dummy_type = "CD"
					// segunda exceção: tipo extraído não é válido
					if( dummy_type != "CD" and dummy_type != "Salgado" ) throw std::runtime_error(dummy_type+" é Tipo inválido/falta aspas no final final");
					// terceira exceção: falta ';' separando Tipo do próximo campo
					if( char(inData.peek()) != ';' ) throw std::runtime_error("Falta ';' depois de Tipo");
					inData.ignore(1);	// ignora o ';'

					if (dummy_type == "CD")
					{
						try{	// tenta alocar um novo CD
							new_cd = new CD;
						} catch (std::exception &e)	{
							cerr << "[CAUGHT] Cesta::load(): " << e.what() << endl;
						}

						new_cd->load_csv_P(inData);	// Carrega os dados comuns a todos Produtos em new_
						new_cd->load_csv_it(inData);	// Carrega o new_ com os dados comuns ao tipo dele (CD)
						produtos.insert(std::pair<string, Produto*>(new_cd->get_barcode(),new_cd));	// Armazena o produto no mapa de produtos diretamente
						new_cd = NULL;
					}

					if (dummy_type == "Salgado")
					{try{	// tenta alocar um novo CD
							new_sa = new Salgado;
						} catch (std::exception &e)	{
							cerr << "[CAUGHT] Cesta::load(): " << e.what() << endl;
						}

						new_sa->load_csv_P(inData);	// Carrega os dados comuns a todos Produtos em new_
						new_sa->load_csv_it(inData);	// Carrega o new_ com os dados comuns ao tipo dele (CD)
						produtos.insert(std::pair<string, Produto*>(new_sa->get_barcode(),new_sa));	// Armazena o produto no mapa de produtos diretamente
						new_sa = NULL;
					}

					dummy_type = "";	 //esvazia o dummy
					lines++;	//aumenta o número de linhas;
				}

			}catch(std::exception& e ){
				cout<<"Na linha "<<lines+1<<" de "<<filename<<": " << e.what(); // se tiver lido pelo menos um produto, mostra o erro final.
				//[DEBUG]cout << endl << "peek = " << inData.peek()<< " and tellg = " << inData.tellg() << endl;
				if(new_cd != NULL) delete new_cd;
				if(new_sa != NULL) delete new_sa;
					
				inData.close();	// Fecha stream de leitura
				return false;
			}
			return true;	// Leu o arquivo .csv sem chegar a nenhuma exceção
		}
		else cout << "\"" << filename << "\" está vazio." << endl;

		inData.close();	// Fecha stream de leitura
		return false;
	}
	else // O arquivo não foi iniciado corretamente
	{
		cout << "Erro ao tentar inicializar stream de entrada para " << filename << "." << endl
			<< "Iniciando loja sem produtos cadastrados." << endl;
		return false;
	}
}

/**
* @details Cada linha vai conter as seguintes informações sobre os produtos:
* "TIPO";"FORNECEDOR";PREÇO;"CODIGO_DE_BARRAS";QUANTIDADE;informações específicas de cada produto
* @return true se conseguiu salvar, false caso contrário
*/
bool Cesta::save()
{
	string filename("data/my_store.csv");    /**< string com o nome do local do arquivo a ser salvo com os dados do baú */

	std::ofstream outData(filename.c_str()); /**< stream de saída para 'filename' */

	// Verifica se 'outData' abriu corretamente
	if(outData.is_open())
	{
		// Imprime os produtos de cada secção
		for(auto &e: produtos)
			e.second->save_csv_it(outData);

		// Fecha stream.
		outData.close();

		return true;	// Conseguiu salvar com sucesso
	}
	else
	{
		cerr << "Erro ao tentar inicializar stream de saída para "<< filename <<"." << endl
			<< "Estoque não será salvo." << endl;
		return false;	// Não conseguiu salvar
	}
}

/**
* @details Cada linha vai conter as seguintes informações sobre os produtos:
* "TIPO";"FORNECEDOR";PREÇO;"CODIGO_DE_BARRAS";QUANTIDADE;informações específicas de cada produto
* @return true se conseguiu salvar, false caso contrário
*/
bool Cesta::export_csv(const char* filename, int& print_full)
{
	string outfile("data/"); /**< string com o nome do local do arquivo a ser salvo com os dados do baú */
	outfile += filename;
	outfile += ".csv";    

	std::ofstream outData(outfile.c_str()); /**< stream de saída para 'filename' */

	// Verifica se 'outData' abriu corretamente
	if(outData.is_open())
	{
		// Imprime os produtos de cada secção
		for(auto &e: produtos)
		{
			if(print_full) e.second->save_csv_it(outData);	// se flag --full for estiver habilitada, imprime todos os dados do produto
			else e.second->save_csv_P(outData);	// caso contrário imprime só os atributos de Produto*
		}

		// Fecha stream.
		outData.close();

		cout << "!Exportado para \"" << outfile << "\".";
		
		return true; // Conseguiu ler com sucesso
	}
	else
	{
		//[THROW]
		cerr << "Erro ao tentar inicializar stream de saída para "<< outfile <<"." << endl;
		//exit(1);
		return false; // Não conseguiu ler
	}
}


// -------------------------------------------------
// ------------------------ Sobrecarga de operadores 

/**
* @param direita cesta a ser comparada
*/
bool Cesta::operator== ( Cesta &direita)
{
	if(produtos.size() != direita.produtos.size() )	return false;	// Se os tamanhos das listas comparadas forem diferentes, retorna falso.

	for(auto& e : produtos)
		if (direita.search(e.second->get_barcode()) == direita.produtos.end() )	return false;	// se não achar o produto, retorna falso

	return true;
}

/**
* @param direita grupo a ser copiado
*/
Cesta& Cesta::operator= (Cesta &direita)
{
	if ( (*this == direita) == false)	// Se as Cestas não forem iguais
	{
		if( not(produtos.empty()) )	// Se a que chamou esta função não estiver vazia
			for(map<string, Produto*>::iterator esq = produtos.begin();
				esq != produtos.end(); esq++) unreg(esq);	// destroi todos serus produtos

		if( not(direita.produtos.empty()) )	// Se a lista da direita não estiver vazia
		{
			try
			{
				for(map<string, Produto*>::iterator dir = direita.produtos.begin();
					dir != direita.produtos.end(); dir++)
				{
					if( (dir->second)->get_type() == "CD" )	// Se o item apontado na Cesta da direita for um CD
						produtos.insert( std::pair<string,Produto*> ( dir->second->get_barcode(), (new CD((dir->second))) ) );
					else if( dir->second->get_type() == "Salgado" )	// Se o item apontado na Cesta da direita for um CD
						produtos.insert( std::pair<string,Produto*> ( dir->second->get_barcode(), (new Salgado((dir->second))) ) );
				}
			}catch (std::exception &e) {cerr << "[CAUGHT] operator=: " << e.what() << endl;}
		}
	}

	return *this;
}

// =====================================================================================================
// =========================================== Função auxiliar =========================================
// =====================================================================================================

/**
* @brief Verifica se uma string corresponde a o nome de um tipo de produto válido.
* @param str Referência para string a ser verificada
*/
bool Cesta::is_valid_type( const string& str)
{
	if( str == "CD" or 
		str == "Salgado") return true;
	return false;
}

}

//#include "Menu.h"

#endif
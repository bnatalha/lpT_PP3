#ifndef MENU_H
#define MENU_H

#include "header.h"
#include "Produto.h"
#include "Cesta.h"

// Funções que auxiliam o menu

//int set_number(int beginning, int end);

// =================================================================================
// ================================= IMPLEMENTAÇÃO ================================= 

/**
* @brief Permite o usuário prosseguir apenas caso tenha digitado um interio que pertença a ['smallest';'greatest']
* @param smallest menor número permitido
* @param greatest maior número permitido
* @return operação válida (dentro do intervalo [fechado) passado)
*/
int set_number(int smallest, int greatest)
{
	int number;

	cin >> number;
	cin.ignore();

	while (number < smallest or greatest < number )
	{
		cout << "Digite um número válido. >>";
		cin >> number;
		cin.ignore();
	}
	return number;
}

/**
* @brief Menu de opções principal
* @param m_loja Referência para Cesta da loja
* @param m_loja Referência para Cesta de venda
*/
void menu_principal (Cesta& m_loja, Cesta& m_cliente)
{
	int op;	//guarda a operação.

	do{
		cout << "=============================" << endl
			<< "Operações principais:" << endl
			<< "=============================" << endl
			<< "1) Consultar items na loja;" << endl
			<< "2) Cadastrar items na loja;" << endl
			<< "3) Iniciar Compra;" << endl
			<< "0) Finalizar o programa;" << endl
			<< "Digite o número da operação a ser realizada. >>";
		
		op = set_number(0,3);	// Solicita do usuário a operação
		cout << endl;

		if( op == 1) //1) Consultar items na loja;
			sub_consulta(m_loja, m_cliente, direction::loja_loja );
		else if( op == 2 )	//2) Cadastrar items na loja;
			sub_cadastro_loja(m_loja);
		else if( op == 3 )	//3) Iniciar Compra;
			sub_venda(m_loja, m_cliente);

	}while( op != 0 );
}

/**
* @brief Menu de opções de Modificação de item de item
* @param target Cesta que será consultado
* @param aux Cesta que será consultado para movimentação de Produtos se necessário
* @param my_case 'consulta' para consulta do Cesta da loja e 'venda' consulta do Cesta do cliente
*/
void sub_encontrou_produto( typename map<string, Produto*>::iterator& it, Cesta& m_loja, Cesta& m_cliente, direction my_case )
{
	int op;	// Número da operação
	string a_barcode;	// armazena código de barras

	do
	{
		print_direction(my_case,cout);
		cout << endl
			<< "O que você deseja fazer com este "<< (it->second)->get_type() <<":" << endl
			<< "1) modificar;" << endl
			<< "2) descadastrar;" << endl
			<< "3) cadastrar;" << endl
			<< "0) nada;" << endl
			<< "Digite o número da operação a ser realizada. >>";
		
		op = set_number(0,3);
		cout << endl;

		// operações

		if(op == 1)	// 1) Modificar
		{
			if (my_case == direction::venda_venda or my_case == direction::loja_loja)
				(it->second)->change();
			else
				cout << "Não pode descastrar esse produto por aqui." << endl;
		}
		else if(op == 2)	//2) Remover
		{
			if(my_case == direction::loja_loja)
			{
				m_loja.unreg(it);
				cout << "Produto descadastrado." << endl;
				op = 0;
			}
			else if(my_case == direction::loja_venda)
			{
				cout << "Não pode descadastrar produtos da loja tendo iniciado uma venda." << endl;
			}
			else if(my_case == direction::venda_venda)
			{
				m_cliente.unreg(it);
				cout << "Produto descadastrado." << endl;
				op = 0;
			}
			else if(my_case == direction::venda_loja)
			{
				cout << "Não pode descadastrar produtos de uma venda que nem existe" << endl;
			}
		}
		else if(op == 3)	// Cadastrar produto
		{
			if(my_case == direction::loja_loja)
			{
				cout << "Não pode cadastrar produtos da loja por aqui." << endl;
			}
			else if(my_case == direction::loja_venda)
			{
				int qtd;

				cout << "Unidades disponiveis: " << (it->second)->get_quantity() << ". Quantas serao cadastradas? >>";
				qtd = set_number(0,(it->second)->get_quantity());	// Pega a quantidade a ser movida

				cout << "[DEBUG] &m_loja=" << &m_loja << " e &m_cliente=" <<&m_cliente << endl;
				m_cliente.absorb_qnt(it, qtd);	// Cadastra o item.
			}
			else if(my_case == direction::venda_venda)
			{
				cout << "Não faz sentido. [1]" << endl;
			}
			else if(my_case == direction::venda_loja)
			{
				cout << "Não faz sentido. [2]" << endl;
			}		
		}
	}while(op != 0);
}

/**
* @brief Menu de opções de Consulta de item
* @param target Cesta que será consultado
* @param aux Cesta que será consultado para movimentação de Produtos se necessário
* @param my_case Caso da consulta ('consulta' para consulta do Cesta da loja e 'venda' consulta do Cesta do cliente)
*/
void sub_consulta (Cesta& m_loja, Cesta& m_cliente, direction my_case )
{
	int op;	// Armazena operação interna
	int op_2;	// Armazena operação interna da consulta (2)
	string a_barcode;	// Armazena codigo de barras

	do
	{
		print_direction(my_case,cout);
		cout << endl
			<< "Opções de consulta:" << endl
			<< "1) Consultar/alterar produto por código de barras;" << endl
			<< "2) Listar produtos por tipo;" << endl
			<< "0) voltar;" << endl
			<< "Digite o número da operação a ser realizada. >>";
	
		op = set_number(0,2);	// Pega número válido
		cout << endl;

		// operações

		if(op == 1)	//1) por código de barras;
		{
			cout << "Insira o código de barras. >>";
			cin >> a_barcode;
			cin.ignore();

			cout << "Procurando por '" << a_barcode << "'...";

			// Criando iterators para pesquisar por produto.
			map<string, Produto*>::iterator it;
			map<string, Produto*>::iterator it_end;

			// Procurando codigo de barras
			if(my_case == direction::venda_venda)
			{
				it = m_cliente.search(a_barcode);
				it_end = m_cliente.produtos.end();
			}

			if(my_case == direction::loja_venda or my_case == direction::loja_loja)
			{
				it = m_loja.search(a_barcode);
				it_end = m_loja.produtos.end();
			}

			// Resultado da pesquisa
			if(it != it_end )	// Se encontrou
			{
				cout << "Encontrado." << endl;
				(it->second)->print_it(cout);
				cout << endl;

				cout << "[DEBUG] &m_loja=" << &m_loja << " e &m_cliente=" <<&m_cliente << endl;
				sub_encontrou_produto(it, m_loja, m_cliente, my_case);
			}			
			else
				cout << "Produto não existe." << endl;
		}

		if(op == 2)	//2) Listar produtos por tipo;
		{
			cout << "Insira '1' para CD e '2' para Salgado. >>";
			op_2 = set_number(1,2);	// Pega número válido

			if(op_2 == 1)	// CD
			{
				cout << "Imprimindo CDs:" << endl;
				if(my_case == direction::loja_venda or my_case == direction::loja_loja)
					m_loja.print_type(cout, "CD");
				else  m_cliente.print_type(cout, "CD");
				cout << endl << "--Fim--" << endl;
			}
			else if(op_2 == 2)	// Salgado
			{
				cout << "Imprimindo Salgado:" << endl;
				if(my_case == direction::loja_venda or my_case == direction::loja_loja)
					m_loja.print_type(cout, "Salgado");
				else  m_cliente.print_type(cout, "Salgado");
				cout << endl << "--Fim--" << endl;
			}
		}

	} while(op != 0);
}

/**
* @brief Menu de opções de Cadastro de Item na loja
* @param alvo Cesta onde o iterm será cadastrado
*/
void sub_cadastro_loja(Cesta& target)
{
	int new_item;

	cout << "Insira '1' para cadastrar CD e '2' para Salgado. >>";
	new_item = set_number(1,2);	// Pega número válido

	if(new_item == 1)	// Se for CD
	{
		CD *cd = new CD;	// Cria novo CD
		cd->change();	// modifica o CD
		map<string,Produto* >::iterator it = target.produtos.find(cd->get_barcode() );	// Busca se CD criado existe no mapa.
		if( it == target.produtos.end())	// se não existe
			target.reg(cd);	// registra o cd
		else	// caso contrário
		{
			cout << "Produto encontrado:" << endl; it->second->print_it(cout);
			cout << endl;
			if (my_question("O produto que você está tentando cadastrar já existe. Deseja subistituí-lo? ") )
			{	//se sim
				target.unreg(it);
				target.reg(cd);
			}
			else
			{
				delete cd;	// deleta CD que seria cadastrado
				cout << "Cadastramento cancelado." << endl;
			}
			
		}
	}
	else if(new_item == 2) //Se for Salgado
	{
		Salgado *sal = new Salgado;
		sal->change();
		target.reg(sal);
		map<string,Produto* >::iterator it = target.produtos.find(sal->get_barcode() );	// Busca se Salgado criado existe no mapa.
		if( it == target.produtos.end())	//se não existe
			target.reg(sal);	// registra o cd
		else
		{
			delete sal;	// deleta Salgado criado
			cout << "Salgado já exite. Cadastramento cancelado." << endl;
		}
	}
}


/**
* @brief Menu de Realização de m_cliente
* @return opção selecionada
*/
void sub_venda(Cesta &m_loja, Cesta& m_cliente)
{
	int op = 34;

	do
	{	cout << "[DEBUG] &m_loja=" << &m_loja << " e &m_cliente=" <<&m_cliente << endl;
		cout << "Venda:" << endl
			<< "1) Consultar items para adicionar a venda;" << endl
			<< "2) Consultar/alterar items da venda;" << endl
			<< "3) Ver Produtos cadastrados até agora na venda;" << endl
			<< "4) Finalizar venda" << endl
			<< "0) cancelar" << endl
			<< "Digite o número da operação a ser realizada. >>";
		op = set_number(0,4);	// Pega a operação
		cout << endl;

		// Operações

		if     (op == 1)	//1) Consultar items para adicionar a venda;
		{
			sub_consulta(m_loja,m_cliente,direction::loja_venda);
		}
		else if(op == 2)
		{
			sub_consulta(m_loja,m_cliente,direction::venda_venda);
		}
		else if(op == 3)	//3) Ver Produtos cadastrados até agora na venda;
		{
			m_cliente.print(cout);
		}
		else if(op == 4)	//5) Finalizar venda
		{
			cout << "[DEBUG] &m_loja=" << &m_loja << " e &m_cliente=" <<&m_cliente << endl;
			m_cliente.print_notafiscal(cout);	// Imprime nota fiscal
			m_cliente.clear();	//Limpa a Cesta cliente
			cout << "Venda finalizada." << endl;
		}
		else if(op == 0)
		{
			cout << "[DEBUG] &m_loja=" << &m_loja << " e &m_cliente=" <<&m_cliente << endl;
			for(map<string, Produto*>::iterator it = m_cliente.produtos.begin(); it != m_cliente.produtos.end(); it++)
				m_loja.absorb_qnt(it, (it->second)->get_quantity());	// Absorve todos as unidades apontados por 'it' para loja.
			
			m_cliente.clear();	//Limpa a Cesta cliente

			cout << "!! Venda cancelada !!" << endl << endl;
		}

	}while(op != 4 and op != 0);
}


#endif

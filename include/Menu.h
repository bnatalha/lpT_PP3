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
	int op;

	do{
		cout << "Operações principais:" << endl
			<< "1) Consultar items na loja;" << endl
			<< "2) Cadastrar items na loja;" << endl
			<< "3) Iniciar Compra;" << endl
			<< "0) Finalizar o programa;" << endl
			<< "Digite o número da operação a ser realizada. >>" << endl;
		
		op = set_number(0,3);	// Solicita do usuário a operação

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
void sub_encontrou_produto( typename myLista<Produto*>::iterator& it, Cesta& m_loja, Cesta& m_cliente, direction my_case )
{
	int op;	// Número da operação
	string a_barcode;	// armazena código de barras

	do
	{
		cout << "O que você deseja fazer com este "<< (*it)->get_type() <<":" << endl
			<< "1) modificar;" << endl
			<< "2) descadastrar;" << endl
			<< "3) cadastrar;" << endl
			<< "0) nada;" << endl
			<< "Digite o número da operação a ser realizada. >>" << endl;
		
		op = set_number(0,3);

		// operações

		if(op == 1)	// 1) Modificar
		{
			(*it)->change();
		}
		else if(op == 2)	//2) Remover
		{
			if(my_case == direction::loja_loja)
			{
				m_loja.unreg(it);
			}
			else if(my_case == direction::loja_venda)
			{
				cout << "Não pode descadastrar produtos da loja tendo iniciado uma venda." << endl;
			}
			else if(my_case == direction::venda_venda)
			{
				m_cliente.unreg(it);	
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

				cout << "Unidades disponiveis: " << (*it)->get_quantity() << ". Quantas serao cadastradas? >>";
				qtd = set_number(0,(*it)->get_quantity());	// Pega a quantidade a ser movida

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
	string a_barcode;	// Armazena codigo de barras

	do
	{
		cout << "Opções de consulta:" << endl
			<< "1) Consultar/alterar produto por código de barras;" << endl
			<< "2) Listar produtos por tipo;" << endl
			<< "0) voltar;" << endl
			<< "Digite o número da operação a ser realizada. >>" << endl;
	
		op = set_number(0,2);	// Pega número válido

		// operações

		if(op == 1)	//1) por código de barras;
		{
			cout << "Insira o código de barras. >>";
			cin >> a_barcode;
			cin.ignore();

			cout << "Procurando por '" << a_barcode << "'...";

			// Criando iterators para pesquisar por produto.
			myLista<Produto*>::iterator it;
			myLista<Produto*>::iterator it_end;

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
				(*it)->print_it(cout);
				cout << endl;

				sub_encontrou_produto(it, m_loja, m_cliente, my_case);
			}			
			else
				cout << "Produto não existe." << endl;
		}

		if(op == 2)	//2) Listar produtos por tipo;
		{
			cout << "Insira o Tipo (disponíveis \"CD\" e \"Salgado\"). >>";
			cin >> a_barcode;
			cin.ignore();

			if(a_barcode == "CD")
			{
				cout << "Imprimindo CDs:" << endl;
				if(my_case == direction::loja_venda or my_case == direction::loja_loja) m_loja.print_type(cout, a_barcode);
				else  m_cliente.print_type(cout, a_barcode);
				cout << endl << "--Fim--" << endl;
			}
			else if(a_barcode == "Salgado")
			{
				cout << "Imprimindo Salgado:" << endl;
				if(my_case == direction::loja_venda or my_case == direction::loja_loja) m_loja.print_type(cout, a_barcode);
				else  m_cliente.print_type(cout, a_barcode);
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
	string new_item;

	cout << "Insira o tipo de produto a ser cadastrado (Salgado ou CD). >>";
		
	cin >> new_item;
	cin.ignore();	

	if(new_item == "CD")
	{
		CD *cd = new CD;
		cd->change();
		target.reg(cd);
	}
	else if(new_item == "Salgado")
	{
		Salgado *sal = new Salgado;
		sal->change();
		target.reg(sal);
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
	{
		cout << "Venda:" << endl
			<< "1) Consultar items para adicionar a venda;" << endl
			<< "2) Consultar/alterar items da venda;" << endl
			<< "3) Ver Produtos cadastrados até agora na venda;" << endl
			<< "4) Finalizar venda" << endl
			<< "0) cancelar" << endl
			<< "Digite o número da operação a ser realizada. >>" << endl;
		op = set_number(0,4);	// Pega a operação

		// Operações

		if     (op == 1)	//1) Consultar items para adicionar a venda;
		{
			sub_consulta(m_loja,m_cliente,direction::loja_venda);
		}
		else if(op == 2)
		{
			sub_consulta(m_loja,m_cliente,direction::venda_venda);
		}
		else if(op == 3)	//4) Ver Produtos cadastrados até agora na venda;
		{
			m_cliente.print(cout);
		}
		else if(op == 5)	//5) Finalizar venda
		{
			m_cliente.print_notafiscal(cout);	// Imprime nota fiscal
			m_cliente.~Cesta();	// Destro todos os items cadastrados na venda
			cout << "Venda finalizada." << endl;
		}
		else if(op == 0)
		{
			for(myLista<Produto*>::iterator it = m_cliente.produtos.begin(); it != m_cliente.produtos.end(); it++)
				m_loja.absorb_qnt(it, (*it)->get_quantity());	// Absorve todos as unidades apontados por 'it' para loja.
			
			m_cliente.~Cesta();	// Destroi todos os items da Cesta do cliente.

			cout << "Venda cancelada." << endl;
		}

	}while(op != 5 or op != 0);
}


#endif

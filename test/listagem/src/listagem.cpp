#include <iostream>
#include "listagem.h"
#include <list>
//#include <memory>
#include <string>

#include <deque>


#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
//#include <stdexcept>
#include <vector>

#define TOTAL 10

// testar list

void alocar( list<Base*> &lista)
{
	//TipoA *a = new TipoA(2,"a"); // Instancia UM objeto da classe TipoA	
	//TipoB *b = new TipoB(2,"b"); // Instancia UM objeto da classe TipoA
	//TipoA *aa  = a;

	lista.push_front(new TipoA(2,"a"));
	//lista.push_back(b);

	//delete a;
	//delete aa;
	//delete b;
}

int func3()
{
	//TipoA a1(1,"a"); // Instancia UM objeto da classe TipoA
	//TipoB b1(2,"b"); // Instancia UM objeto da classe TipoB
	//a1.imprime(); 
	//b1.imprime();

	list<Base*> lista; // Cria UMA lista (usando STL) genérica usando a classe Base
	list<Base*> lista2; // Cria UMA lista (usando STL) genérica usando a classe Base
	//list<int*> lista;
/*	
	// Preenche a lista com elementos do TipoA (quando i for par) ou TipoB (quando i for impar)
	for(int i=0; i<1; i++)
	{
		// O metodo push_back() insere um elemento no final da lista (STL)
		lista.push_front(&a1);
		lista.push_back(&b1);
	}

	// Imprime os elementos da lista usando um iterador (STL)
	for (list<Base*>::iterator it = lista.begin(); it != lista.end(); ++it)
	{
		// Como cada elemento da lista é um objeto TipoA ou TipoB e ambos respondem ao 
		// metodo imprime()...
		(*it)->imprime();
	}

	cout << "NEXT" << endl;

	lista.front()->foo();
	lista.back()->bar();
	cout << ( lista.front()->onto()? "true":"false") << endl;
*/
	alocar(lista);

	for (auto &e : lista) e->imprime();

	// Testando push copiando de iterator

	list<Base*>::iterator it = lista.begin();	// Iterator criado

	//TipoA *novo = new TipoA((*it)->get_cod(), (*it)->get_pref());	// Cria novo tipoA com base o iterator
	TipoA *novo = new TipoA;	// Cria novo tipoA com base o iterator

	lista2.push_back( novo );	// o assimila a lista 2


	cout << "lista:" << endl;
	for (auto &e : lista) e->imprime();
	cout << "lista2:" << endl;
	for (auto &e : lista2) e->imprime();

	


	// Deletando informações
	for (auto &e : lista)	delete e;
	for (auto &e : lista2)	delete e;

	return 0;
}

void ecpt_test()
{
	std::vector<int> myvector(10);

	//int* a = new int[1];
	//a[0] = 4;

	//try {
		myvector.at(20)=100;      // vector::at throws an out-of-range
		//a[1] = 45;
	//}
	//catch (const std::out_of_range& oor) {
	//	std::cerr << "Out of Range error: " << oor.what() << '\n';
	//}

	cout << "fim." << endl;

	//delete[] a;

}



int op_deque ()
{
	std::deque<unsigned> mydeque (10);   // 10 zero-initialized unsigneds

	// assign some values:
	/*for (unsigned i=0; i<mydeque.size(); i++)
		mydeque[i]=i;
    
	mydeque.pop_front();
	mydeque.pop_front();mydeque.pop_front();mydeque.pop_back();

	std::cout << "mydeque contains:";
	for (unsigned i=0; i<mydeque.size(); i++)	
	*/
	for (unsigned i=2; i<4; i++)
		std::cout << ' ' << mydeque[0];

	std::cout << '\n';

	return 0;
}

int main () {

	op_deque();

  return 0;
}

/**
* @file
* @brief Implementação dos construtores de myPilha
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_1_H
#define MYLISTA_1_H

/**
* @brief Constrói uma lista vazia
*/
template < typename T>
myLista<T>::myLista()
	: sentinela_head(NULL), sentinela_tail(NULL), qtd_elementos(0)
{}

/**
* @brief Constrói uma lista a partir de uma lista já existente
* @param copy Lista a ser copiada
*/
template < typename T>
myLista<T>::myLista( const myLista & copy )
	: sentinela_head(NULL), sentinela_tail(NULL), qtd_elementos(0)
{
	myNode * _pointer = copy.sentinela_head;

	while (_pointer != NULL)
	{
		push_back(_pointer->elemento);
		_pointer = _pointer->proximo;
	}
}

/**
* @brief [INVALIDO]Constrói uma lista com 'n' elementos, todos elementos sendo 'val'
* (.: //Invalidado pela nova implementação dos metodos push (só entra algum elemento na lista caso ele ainda não exista nela)
* @param n Quantidade de elementos a ser criados
* @param val Valor que cada elemento criado a partir desta função receberá
*/
template < typename T>	// fill;
myLista<T>::myLista(const int& n, const T& val)
: sentinela_head(NULL), sentinela_tail(NULL), qtd_elementos(0)
{
	while (size() < n)	// Enquanto o tamanho da lista for menor que 'n'
		push_front(val);	// Adiciona a lista nós com elemento 'val'
}

#endif
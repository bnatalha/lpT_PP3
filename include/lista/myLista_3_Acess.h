/**
* @file
* @brief Implementação dos métodos front() e back() de myPilha
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_3_H
#define MYLISTA_3_H

/**
* @brief Acessa o elemento mais a frente na lista
* @return O elemento do nó apontado pela cabeça;
*/
template < typename T>
T& myLista<T>::front()
{
	// exceção caso lista esteja vazia (?)
	return (sentinela_head->elemento);
}

/**
* @brief Acessa o elemento no último nó da lista
* @return O elemento do nó apontado pela cauda;
*/
template < typename T>
T& myLista<T>::back()
{
	// exceção caso lista esteja vazia (?)
	return (sentinela_tail->elemento);
}
#endif
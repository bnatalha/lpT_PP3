/**
* @file
* @brief Implementação do destrutor de myPilha
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_2_H
#define MYLISTA_2_H

/**
* @brief Destroi a lista, destruindo seus elementos.
*/
template < typename T>
myLista<T>::~myLista()
{
	clear();
}

#endif
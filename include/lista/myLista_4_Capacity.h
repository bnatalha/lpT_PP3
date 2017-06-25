/**
* @file
* @brief Implementação dos metodos de size() e empty() de myPilha
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_4_H
#define MYLISTA_4_H

/**
* @brief Checa se a quantidade de nós da lista
* @return atributo qtd_elementos
*/
template < typename T>
int myLista<T>::size()
{
	return qtd_elementos;
}

/**
* @brief Checa se a lista está vazia
*/
template < typename T>
bool myLista<T>::empty()
{
	return ( size() == 0 );
}


#endif
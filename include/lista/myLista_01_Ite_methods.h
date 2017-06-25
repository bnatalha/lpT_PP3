/**
* @file
* @brief Implementação dos métodos de myLista que utilizam iteratores
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 04/06/2017
* @date 04/06/2017
* @sa std::list (http://www.cplusplus.com/reference/list/list/)
*/

#ifndef MYLISTA_01_H
#define MYLISTA_01_H

/**
* @brief Constrói um const_iterator que aponta para o início da lista (primeiro elemento)
*/
template < typename T>
typename myLista<T>::const_iterator myLista<T>::begin() const
{
	typename myLista<T>::const_iterator cit(sentinela_head);
	return cit;
}

/**
* @brief Constrói um iterator que aponta para o início da lista (primeiro elemento)
*/
template < typename T>
typename myLista<T>::iterator myLista<T>::begin()
{
	typename myLista<T>::iterator cit(sentinela_head);
	return cit;
}

/**
* @brief Constrói um const_iterator que aponta para o elemento após o último
*/
template < typename T>
typename myLista<T>::const_iterator myLista<T>::end() const
{
	typename myLista<T>::const_iterator cit(NULL);	// NULL = sentinela_tail->proximo
	return cit;
}

/**
* @brief Constrói um iterator que aponta para o elemento após o último
*/
template < typename T>
typename myLista<T>::iterator myLista<T>::end()
{
	typename myLista<T>::iterator cit(NULL);	// NULL = sentinela_tail->proximo
	return cit;
}

#endif
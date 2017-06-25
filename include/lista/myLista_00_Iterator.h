/**
* @file
* @brief Implementação do iterator de myLista
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 04/06/2017
* @date 04/06/2017
* @sa iterators (http://en.cppreference.com/w/cpp/language/operators)
* pos and prefix increment and decrement (http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/)
*/

#ifndef MYLISTA_00_H
#define MYLISTA_00_H

// ========================== CONST_ITERATOR ==========================

// Construtor 

/**
* @brief Constroi um iterador constante vazio
*/
template < typename T >
myLista<T>::const_iterator::const_iterator()
{
	atual = NULL;	// Aponta o ponteiro para nó interno do iterator para NULL
}

// Acesso

/**
* @brief Sobrecarga do operador '*' para iteradores constantes
* @return Retorna o nó apontado pelo iterator
*/
template < typename T >
const T& myLista<T>::const_iterator::operator*() const
{
	return *(atual)->data;
}


// Incremento e Decremento

/**
* @brief Sobrecarga do operador++ para iteradores constantes (pós-incrementação)
* @return Iterator temporário criado dentro da função
* @sa posfix Increment and decrement (http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/)
*/
template < typename T >
typename myLista<T>::const_iterator myLista<T>::const_iterator::operator++(int)
{
	const_iterator temp(atual); // Cria um const_iterator temporário com as informações do iterator usado antes da chamada desta função
	atual = atual->proximo; // Aumenta o valor do iterator usado
	return temp;
}

/**
* @brief Sobrecarga do operador++ para iteradores constantes (pré-incrementação)
* @return Iterator atualizado com a incrementação
* @sa prefix Increment and decrement (http://en.cppreference.com/w/cpp/language/operators)
*/
template < typename T >
typename myLista<T>::const_iterator& myLista<T>::const_iterator::operator++()
{
	atual = atual->proximo; // iterator usado aponta para o próximo nó da lista
	return *this;
}

/**
* @brief Sobrecarga do operador-- para iteradores constantes (pós-decrementação)
* @return Iterator temporário criado dentro da função
* @sa posfix Increment and decrement (http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/)
*/
template < typename T >
typename myLista<T>::const_iterator myLista<T>::const_iterator::operator--(int)
{
	const_iterator temp(atual); // Cria um const_iterator temporário com as informações do iterator usado antes de sofrer a decrementação
	atual = atual->anterior; // Manado o iterator para o nó anterior o valor do iterator usado
	return temp;
}

/**
* @brief Sobrecarga do operador++ para iteradores constantes (pré-decrementação)
* @return Iterator atualizado com a decrementação
* @sa prefix Increment and decrement (http://en.cppreference.com/w/cpp/language/operators)
*/
template < typename T >
typename myLista<T>::const_iterator& myLista<T>::const_iterator::operator--()
{
	atual = atual->anterior; // iterator usado passa a apontar para nó anterior na lista
	return *this;
}

// Comparação

/**
* @brief Sobrecarga do operador== para iteradores constantes
* @return Verifica se os iterators estam apontando para o mesmo nó
*/
template < typename T >
bool myLista<T>::const_iterator::operator== (const const_iterator& it_direita) const
{
	return (atual == it_direita.atual); 
}

/**
* @brief Sobrecarga do operador!= para iteradores constantes
* @return Verifica se os iterators estam apontando para nós doferentes
*/
template < typename T >
bool myLista<T>::const_iterator::operator!= (const const_iterator& it_direita) const
{
	return (atual != it_direita.atual); // Retorne true se os dois atuals são diferentes
}


// ========================== ITERATOR ==========================

// Acesso

/**
* @brief Sobrecarga do operador* para iteradores não constantes em listas constantes
* @return Valor/elemento armazenado no nó apontado pelo iterator
*/
template < typename T >
const T & myLista<T>::iterator::operator* () const
{
	return (this->atual)->elemento; 
}

/**
* @brief Sobrecarga do operador* para iteradores não constantes
* @return Valor/elemento armazenado no nó apontado pelo iterator
*/
template < typename T >
T & myLista<T>::iterator::operator* ()
{
	return (this->atual)->elemento;
}

// Incremento e Decremento

/**
* @brief Sobrecarga do operador++ para iteradores constantes (pós-incrementação)
* @return Iterator temporário criado dentro da função
* @sa posfix Increment and decrement (http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/)
*/
template < typename T >
typename myLista<T>::iterator myLista<T>::iterator::operator++(int)
{
	iterator temp(this->atual); // Cria um const_iterator temporário com as informações do iterator usado antes da chamada desta função
	this->atual = (this->atual)->proximo; // Aumenta o valor do iterator usado
	return temp;
}

/**
* @brief Sobrecarga do operador++ para iteradores constantes (pré-incrementação)
* @return Iterator atualizado com a incrementação
* @sa prefix Increment and decrement (http://en.cppreference.com/w/cpp/language/operators)
*/
template < typename T >
typename myLista<T>::iterator& myLista<T>::iterator::operator++()
{
    this->atual = (this->atual)->proximo; // iterator usado aponta para o próximo nó da lista
    return *this;
}

/**
* @brief Sobrecarga do operador-- para iteradores não constantes (pós-decrementação)
* @return Iterator temporário criado dentro da função
* @sa posfix Increment and decrement (http://www.learncpp.com/cpp-tutorial/97-overloading-the-increment-and-decrement-operators/)
*/
template < typename T >
typename myLista<T>::iterator myLista<T>::iterator::operator--(int)
{
	iterator temp(this->atual); // Cria um const_iterator temporário com as informações do iterator usado antes de sofrer a decrementação
	this->atual = (this->atual)->anterior; // iterator usado passa a apontar para nó anterior na lista
	return temp;
}

/**
* @brief Sobrecarga do operador++ para iteradores não constantes (pré-decrementação)
* @return Iterator atualizado com a decrementação
* @sa prefix Increment and decrement (http://en.cppreference.com/w/cpp/language/operators)
*/
template < typename T >
typename myLista<T>::iterator& myLista<T>::iterator::operator--()
{
	this->atual = (this->atual)->anterior; // iterator usado passa a apontar para nó anterior na lista
	return *this;
}

// ?
/**
* @brief Sobrecarga do operador= (atribuição)
* @return Valor/elemento armazenado no nó apontado pelo iterator
*/
template < typename T >
typename myLista<T>::iterator& myLista<T>::iterator::operator=( const iterator& it_direita )
{
	this->atual = it_direita.atual;
	return *this;
}

#endif
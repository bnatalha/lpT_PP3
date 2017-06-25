/**
* @file
* @brief Definição de myLista e implemnetação das sobrecargas de operadores dela
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_H
#define MYLISTA_H

#include "header_2.h"

/**
* @class myLista
* @brief Classe criada para simular a classe std::list da STL do C++, só que já ordenada 
* (neste exemplo, na ordem decrescente)
* @tparam T Tipo dos elementos da lista
*/
template < typename T >
class myLista
{
	private:

		/**
		* @struct myNode
		* @brief Estrutura que define um nó dá lista
		*/
		struct myNode
		{
			T elemento;	/**< Elemento que o nó guarda */
			myNode* anterior; /**< Ponteiro para o nó anterior (no sentido do início) da lista */
			myNode* proximo; /**< Ponteiro para o próximo nó (no sentido do fim) da lista */

			/**
			* @brief Construtor de myNode
			*/
			myNode(const T& data, myNode* prevNode = NULL, myNode* nextNode = NULL)
				:	elemento(data), anterior(prevNode), proximo(nextNode)
			{}

			/**
			* @brief Construtor de myNode
			*/
			myNode(T& data, myNode* prevNode = NULL, myNode* nextNode = NULL)
				:	elemento(data), anterior(prevNode), proximo(nextNode)
			{}
		};

		myNode *sentinela_head;	/**< Ponteiro para o nó do início (head) da lista */
		myNode *sentinela_tail;	/**< Ponteiro para o nó do fim (tail) da lista */
		int qtd_elementos;	/**< A quantidade de elementos armazenados na lista */

	public:

		/**
		* @class const_iterator
		* @brief iterator constante de myLista
		* @sa const no fim da assinatura (https://stackoverflow.com/questions/1549869/)
		*/
		class const_iterator
		{
			public:
				// Construtor
				const_iterator();

				// Acesso
				const T& operator*() const;

				// Movimentação
				const_iterator& operator++ ();	// pré-incrementação
				const_iterator operator++ (int);	// pós-incrementação
				const_iterator& operator-- ();	// pré-decrementação
				const_iterator operator-- (int);	// pós-decrementação

				// Comparação
				bool operator==( const const_iterator & it_direita ) const;
				bool operator!=( const const_iterator & it_direita ) const;

			protected:
				// Construtor
				const_iterator( myNode *ponteiro )
					: atual (ponteiro)
				{} 

				// Atributos
				myNode * atual;	/**< Ponteiro para um nó */

				// Permissão
				friend class myLista<T>;
		};

		/**
		* @class iterator
		* @brief iterator "modificável" de myLista
		* @sa const no fim da assinatura (https://stackoverflow.com/questions/1549869/)
		*/
		class iterator : public const_iterator
		{
			public:
				// Construtor
				iterator()
					: const_iterator()
				{}

				// Acesso ao conteudo do iterator
				const T& operator*() const;
				T& operator*();

				// Movimentação
				iterator& operator++ ();	// pré-incrementação
				iterator operator++ (int);	// pós-incrementação
				iterator& operator-- ();	// pré-decrementação
				iterator operator-- (int);	// pós-decrementação
					
				// Atribuição
				iterator & operator= ( const iterator& it_direita );

			protected:
				// Construtor
				iterator ( myNode *ponteiro)
					: const_iterator(ponteiro)
				{}

				// Permissão
				friend class myLista<T>;	
		};

		// Construtor
		myLista();
		myLista( const myLista & copy );
		// range
		myLista(const int& n, const T& val);	// Invalidado pela nova implementação dos metodos push (só entra algum elemento na lista caso ele ainda não exista nela)
		
		// Destrutor
		~myLista();

		// Iterator
		const_iterator begin() const;
		iterator begin();
		const_iterator end() const;
		iterator end();

		// Acesso a elementos
		T& front();
		T& back();
		
		// Capacidade
		int size();
		bool empty();

		// Modificadores
		//void push_sorted(const T& elem );
		void push_sorted( T elem );
		void push_back( const T& elem );	// bool se tiver como checar se pode ser alocado ou não
		bool pop_back();
		void push_front( const T& elem );
		bool pop_front();
		void clear();
		void erase( iterator &it );
		//insert()	iterator

		// Operações
		void remove(const T& val);
		void unique();
		// > Auxiliares dos modificadores
		bool exist(const T& elem);
		//sort();

		// Sobrecarga de operadores
		bool operator== ( myLista<T> l_direita);
		bool operator!= ( myLista<T> l_direita);
		myLista<T>& operator= (const myLista<T> copy);
		// PARA TESTE: sobrecarga operador <<
		template <typename foo>
		friend std::ostream& operator<< (std::ostream& out, const myLista<foo> copy);
};

// Implementação de Sobrecargas

/**
* @brief Sobrecarga do operador "==". Checa se duas listas são iguais.
* @param l_direita Lista a ser comparada
*/
template <typename T>
bool myLista<T>::operator== ( myLista<T> l_direita)
{
	if(size() != l_direita.size()) // Se as listas forem de tamanhos diferentes
		return false;	// São diferentes
	
	//else	

	myNode *esq = sentinela_head;	// Cria ponteiro para o início desta lista
	myNode *dir = l_direita.sentinela_head;	// Cria ponteiro para o início da lista a ser comparada
	
	while( esq != NULL )	// Enquanto não chegar ao fim da lista*
	{
		if (esq->elemento != dir->elemento) return false;	// Se o conteúdo dos ponteiros forem diferentes entre sí, não são listas iguais

		esq = esq->proximo;	// Movimento o ponteiro para frente
		dir = dir->proximo;	// Movimento o ponteiro para frente
	}

	return true;

	// *Os dois ponteiros andam na mesma velocidade em listas de tamanhos iguais
}

/**
* @brief Sobrecarga do operador "!=". Checa se duas listas são diferente.
* @param l_direita Lista a ser comparada
*/
template <typename T>
bool myLista<T>::operator!= ( myLista<T> l_direita)
{
	return ( not( *this == l_direita ) );
}

/**
* @brief Sobrecarga do operador "="
* @param copy Lista a ser copiada
*/
template <typename T>
myLista<T>& myLista<T>::operator= (const myLista<T> copy)
{
	if ( *this != copy )
	{
		clear();	// Destroi os elementos da lista que vai ser modificada
		
		myNode *_pointer = copy.sentinela_head;	// Cria um ponteiro não constante para o início da lista a ser copiada
		while( _pointer != NULL )	// Enquanto ponteiro não chegar no fim da lista a ser copiada (NULL)
		{
			push_back(_pointer->elemento);	// Acrescenta o elemento do nó da vez ao fim desta lista
			_pointer = _pointer->proximo;	// Ponteiro anda no sentido do fim da lista a ser copida
		}
	}

	return *this;
}

/**
* @brief Sobrecarga do operador "<<"
* @param out ostream a ser usada
* @param lista myLista a ser impressa
* @sa Explicação para uso do typename dentro da função em http://stackoverflow.com/questions/610245/
*/
template <typename foo>
std::ostream& operator<< (std::ostream& out, const myLista<foo> lista)
{
	typename myLista<foo>::myNode *_pointer = lista.sentinela_head;	// Ponteiro para o primeiro nó da lista

	out << "[ ";
	while( _pointer != NULL )
	{
		out << _pointer->elemento << (_pointer->proximo == NULL ? " ": ", ");
		_pointer = _pointer->proximo;
	}
	out << "]";

	return out;
}

#include "myLista_00_Iterator.h"
#include "myLista_01_Ite_methods.h"
#include "myLista_1_Construtor.h"
#include "myLista_2_Destrutor.h"
#include "myLista_3_Acess.h"
#include "myLista_4_Capacity.h"
#include "myLista_5_Modifiers.h"
#include "myLista_6_Operations.h"

#endif
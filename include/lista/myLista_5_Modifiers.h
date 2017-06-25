/**
* @file
* @brief Implementação dos métodos clear(), push_'s(), pop's() de myPilha
* @author Natália Azevedo de Brito (https://github.com/bnatalha/)
* @since 14/05/2017
* @date 21/05/2017
* @sa std::stack (http://www.cplusplus.com/reference/stack/stack/, http://en.cppreference.com/w/cpp/container/list)
*/

#ifndef MYLISTA_5_H
#define MYLISTA_5_H

/**
* @brief Remove todos os elementos da lista, a deixando com tamanho = 0.
*/
template < typename T>
void myLista<T>::clear()
{
	while ( sentinela_head != NULL )	// Se tiver mais de um elemento na lista,
	{
		pop_back();
	}
}

/**
* @brief Adiciona um elemento a lista respeitando a ordem DECRESCENTE (Tem comportamento inesperado se a lista não estiver nesta ordem)
* @param elem Elemento a ser adicionado ao início da lista
*/
template < typename T>
//void myLista<T>::push_sorted( const T& elem )
void myLista<T>::push_sorted( T elem )
{
		myNode *new_node = new myNode(elem);	// Cria um novo nó dinamicamente com o elemento a ser adicionado

		if ( empty() )	 // Se for o primeiro nó da lista (sentinelas não contam)
		{
			sentinela_tail = new_node;	// O nó criado agora é o ultimo da lista	
			sentinela_head = new_node;	// O nó criado agora também é o primeiro da lista	

			qtd_elementos++;	// Total de elementos da lista aumenta	
		}
		
		else // Se já existir algum elemento na lista
		{
			if(elem >= sentinela_head->elemento)	// Se o elemento a ser acrescentado for maior ou igual do que o que está na frente da lista
			{
				delete new_node;	// Não vai ser mais necessário o nó criado graças as função push_front()
				push_front(elem);	// Coloca o elemento na frente da Lista
			}
			else if(sentinela_tail->elemento >= elem)	// Se o elemento do fim da lista for maior ou igual do que o que vai ser acrescentado
			{
				delete new_node;	// Não vai ser mais necessário o nó criado graças as função push_back()
				push_back(elem);	// Coloca o elemento no final da lista
			}
			else if(sentinela_head->elemento > elem and sentinela_tail->elemento < elem )	// else
			{
				myNode *_pointer = NULL;	// Cria um ponteiro para nós

				_pointer = sentinela_head;	// Atribui a _pointer um ponteiro para o primeiro nó da lista

				while(elem <= _pointer->elemento)	// Até encontrar um nó com um elemento que seja menor do que o que será acrescentado a lista
					_pointer = _pointer->proximo;	// Avança o _pointer em direção a fim da lista 

				// Associa o new_node com os nós proximos a ele
				// Situação inicial: [elem]	[_p-1]-[_p]
				new_node->proximo = _pointer;	// [elem]->[_p] | [_p-1]-[_p]
				new_node->anterior = _pointer->anterior;	// [_p-1]<-[elem]->[_p] | [_p-1]-[_p]
				// Coloca new_node entre os elementos _pointer->anterior e _pointer
				_pointer->anterior->proximo = new_node;	// [_p-1]-[elem] | [_p-1]<-[_p]
				_pointer->anterior = new_node;	// [_p-1]-[elem]-[_p]

				qtd_elementos++;	// Total de elementos da lista aumenta	
			}
		}
}

/**
* @brief Adiciona um elemento ao fim da lista
* @param elem Elemento a ser adicionado ao fim da lista
*/
template < typename T>
void myLista<T>::push_back( const T& elem )
{
	myNode *new_node = new myNode(elem, sentinela_tail);	// Cria um novo nó dinamicamente com o elemento adicionado, com o anterior dele sendo o último atual (apontado pela cauda)

	if ( empty() ) // Se for o primeiro nó da lista (sentinelas não contam)
		sentinela_head = new_node;	// O nó criado agora é o primeiro da lista	
		
	else // Se já existir algum elemento na lista
		sentinela_tail->proximo = new_node;	// Faz com que o ultimo nó da lista aponte para o nó criado

	sentinela_tail = new_node;	// O nó criado agora é o ultimo da lista

	qtd_elementos++;	// Total de elementos da lista aumenta	
}

/**
* @brief Remove um elemento do fim da lista, se está não estiver vazia
* @retval true Se um elemento foi retirado
* @retval false Se a lista for vazia
*/
template < typename T>
bool myLista<T>::pop_back()
{
	if ( size() == 0 )
	{
		cout << "pop_back(): A Lista está vazia." << endl;	// ou cout?
		return false;
	}

	myNode *_destruir = sentinela_tail;	// Atribui o endereço apontado pela cauda a um ponteiro
	sentinela_tail = sentinela_tail->anterior;	// A cauda agora aponta para o *penúltimo* nó (ou null, se tamanho da lista for 1)
	
	if (size() == 1 )	// Se a lista possuir apenas um elemento
		sentinela_head = NULL;	// Aponta a cabeça para NULL
	
	if( sentinela_tail != NULL )	// Se o rabo não estiver apontando para NULL (se a lista possuir mais de um elemento)
		sentinela_tail->proximo = NULL;	// // O novo ultimo nó não tem mais ligação com o antigo ultimo nó


	delete _destruir;	// Deleta o elemento que era o último da lista

	qtd_elementos--;	// Total de elementos da lista diminui

	return true;	
}

/**
* @brief Adiciona um elemento ao início da lista
* @param elem Elemento a ser adicionado ao início da lista
*/
template < typename T>
void myLista<T>::push_front( const T& elem )
{
	myNode *new_node = new myNode(elem, NULL, sentinela_head);	// Cria um novo nó dinamicamente com o elemento adicionado, com o próximo dele sendo o primeiro atual (apontado pela cabeça)

	if ( empty() ) // Se for o primeiro nó da lista (sentinelas não contam)
		sentinela_tail = new_node;	// O nó criado agora é o primeiro da lista	
		
	else // Se já existir algum elemento na lista
		sentinela_head->anterior = new_node;	// O primeiro nó da lista agora tem um nó anterior: O nó criado

	sentinela_head = new_node;	// O nó criado é o novo primeiro nó da lista

	qtd_elementos++;	// Total de elementos da lista aumenta	
}

/**
* @brief Remove um elemento do início lista, se está não estiver vazia
* @retval true Se um elemento foi retirado
* @retval false Se a lista for vazia
*/
template < typename T>
bool myLista<T>::pop_front()
{
	if ( size() == 0 )
	{
		cout << "pop_front(): A Lista está vazia." << endl;	// ou cerr?
		return false;
	}
	myNode *_destruir = sentinela_head;	// Atribui o endereço apontado pela cabeça a um ponteiro
	sentinela_head = sentinela_head->proximo;	// A cabeça agora aponta para o *segundo* nó (ou null, se tamanho da lista for 1)

	if (size() == 1 )	// Se a lista possuir apenas um elemento
		sentinela_tail = NULL;	// Aponta a cauda para NULL

	if( sentinela_head != NULL )	// Se a cabeça não estiver apontando para NULL (se a lista possuir mais de um elemento)
		sentinela_head->anterior = NULL;	// O novo primeiro nó não tem mais ligação com o antigo primeiro nó
	
	delete _destruir;	// Deleta o elemento que era o primeiro da lista

	qtd_elementos--;	// Total de elementos da lista diminui

	return true;	
}

/**
* @brief Destroi o nó apontado por um iterator
* @param it iterator da lista que aponta qual nó será destruído
*/
template < typename T>
void myLista<T>::erase( myLista<T>::iterator &it )
{
	myNode *_pointer = (it.atual);	// _pointer aponta para o mesmo nó que o iterator it;
	myNode *_destruir;	// Ponteiro para o nó a ser destruído.
	
	it++;	// iterator avança;

	// Verificando posição do nó apontado pelo ponteiro na lista
	if(_pointer->anterior == NULL and _pointer->proximo == NULL)
	// H-> [val] <-T (Se só existe este nó na lista)
	{
		pop_front();
		_pointer = NULL;
	}
	else if(_pointer->anterior != NULL and _pointer->proximo == NULL)	// Já percorreu toda a lista
	// H-> [n_0]...[n_k-1][val] <-T (Se só existe nó anterior a este e não depois dele)
	{
		_pointer = _pointer->proximo;	// Avança o ponteiro para o fim da lista
		pop_back();
		//_pointer = NULL;
	}
	else if(_pointer->anterior == NULL and _pointer->proximo != NULL)
	// H-> [val][n_1]...[n_k] <-T Se só existe nó depois deste e não antes dele)
	{	
		//_pointer é igual a head
		_pointer = _pointer->proximo;	// Avança o ponteiro para o fim da lista
		pop_front();	// Destroi o elemento (supostamente no início da lista)

	}
	else if(_pointer->anterior != NULL and _pointer->proximo != NULL)
	// H-> [n_0]...[n_z][val][n_z+2]...[n_k] <-T (Se existe nó antes e depois deste)
	{
		// Inicialmente: [x]-[val]-[y],	onde "-" indica que estão conectados em ambos sentidos (anterior e proximo)
				
		_pointer->anterior->proximo = _pointer->proximo;	// Pega o nó anterior ao selecionado e o conecta com o próximo do atual
		// [x]->[z]  [x]<-[val]-[z]
				
		_pointer->proximo->anterior = _pointer->anterior;	// Pega o nó depois do selecionado e o conecta com o anterior do selecionado
		// [x]-[z] [x]<-[val]->[z]
				
		_destruir = _pointer;	// Atribui ao ponteiro destrutor qual o nó a ser destruído
		// _destruir -> [val]
				
		_pointer = _pointer->proximo; //	Avança o ponteiro em direção ao fim da lista
		// _pointer -> [val]
				
			delete _destruir; // Destrói o nó [val]

		qtd_elementos--; // Diminui o contador de elementos da lista
	}
}

#endif
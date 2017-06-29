#ifndef LISTAGEM_H
#define LISTAGEM_H


#include <iostream>
#include <string>

#include "qlt.h"

namespace qlt{
//using namespace std;



Base::Base(int vCodigo):
	m_codigo(vCodigo){}



TipoA::TipoA(int vCodigo, string vPrefixo):
	Base(vCodigo),m_prefixo(vPrefixo){}
TipoA::TipoA(TipoA& x):
	Base(x.get_cod()),m_prefixo(x.m_prefixo){}

void
TipoA::imprime()
{
	cout << m_prefixo << m_codigo << endl;
}



TipoB::TipoB(int vCodigo, string vSufixo):
	Base(vCodigo),m_sufixo(vSufixo){}

void
TipoB::imprime()
{
	cout << m_codigo << m_sufixo << endl;
}
}


#endif
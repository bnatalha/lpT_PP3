#ifndef QLTQLT
#define QLTQLT


#include "header.h"

namespace qlt {
int funcexp ();
int func_price();
int set_valid_number(int smallest, int greatest);
int my_read ();
bool my_question(const char* question);


class Base
{
protected:
	int m_codigo;
public:
	Base(int vCodigo);
	Base() : m_codigo(432){}
	virtual ~Base(){}

	int get_cod(){return m_codigo;}

	virtual void imprime()=0;
	virtual string get_pref(){return "";}
	virtual void foo(){}
	virtual void bar(){}
	virtual bool onto(){ return true; }
};

class TipoA: public Base
{
	//friend class Base;
private:
	string m_prefixo;
public:
	TipoA() : Base(), m_prefixo("doido"){}
	TipoA(int vCodigo, string vPrefixo);
	TipoA(TipoA& x);
	virtual ~TipoA(){}
	string get_pref(){return m_prefixo;}
	void imprime();
	void foo(){ cout << "foo" << m_prefixo << endl;}
	bool onto(){ return false;}
};

class TipoB: public Base
{
	//friend class Base;
private:
	string m_sufixo;

public:
	TipoB(int vCodigo, string vSufixo);
	virtual ~TipoB(){}
	void imprime();
	void bar(){ cout << "bar" << m_sufixo << endl;}
};


}

#include "listagem.h"

#endif
#include <iostream>
#include <string>


using namespace std;

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

Base::Base(int vCodigo):
	m_codigo(vCodigo){}

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

TipoA::TipoA(int vCodigo, string vPrefixo):
	Base(vCodigo),m_prefixo(vPrefixo){}
TipoA::TipoA(TipoA& x):
	Base(x.get_cod()),m_prefixo(x.m_prefixo){}

void
TipoA::imprime()
{
	cout << m_prefixo << m_codigo << endl;
}

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

TipoB::TipoB(int vCodigo, string vSufixo):
	Base(vCodigo),m_sufixo(vSufixo){}

void
TipoB::imprime()
{
	cout << m_codigo << m_sufixo << endl;
}
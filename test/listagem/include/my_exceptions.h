#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <stdexcept>

// ===============================================================================================
// ========================================== PRODUTO ============================================
// ===============================================================================================

/**
* @class mbad_type
* @brief Derivada de std::exception. Usada quando um tipo inválido for detectado.
*/
class mbad_type: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Tipo inválido.";
  }
} mbadtype;

/**
* @class mbad_price
* @brief Derivada de std::exception. Usada quando um Preço inválido for detectado.
*/
class mbad_price: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Preço inválido.";
  }
} mbadprice;

/**
* @class mbad_barcode
* @brief Derivada de std::exception. Usada quando um Código de barras inválido for detectado.
*/
class mbad_barcode: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Código de barras inválido";
  }
} mbadcode;

/**
* @class mbad_quantity
* @brief Derivada de std::exception. Usada quando uma Quantidade inválido for detectado.
*/
class mbad_quantity: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Quantidade inválida";
  }
} mbadqnt;

/**
* @class mbad_provider
* @brief Derivada de std::exception. Usada quando um Fornecedor inválido for detectado.
*/
class mbad_provider: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Fornecedor inválido";
  }
} mbadprov;

// ===============================================================================================
// ======================================== VIRTUAIS =============================================
// ===============================================================================================

/**
* @class mbad_name
* @brief Derivada de std::exception. Usada quando um nome inválido for detectado.
*/
class mbad_name: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Nome inválido";
  }
} mbadname;

// ===============================================================================================
// ======================================== PARSING ==============================================
// ===============================================================================================

/**
* @class mno_quotation_mark
* @brief Derivada de std::exception. Usada quando falta aspas no in[icio ou no fim da leitura de um campo
* que guarda informações para um  atributo do tipo string;
*/
class mno_quote: public std::runtime_error
{/*
  virtual const char* what() const throw()
  {
    return "Faltou aspas \"";
  }*/
  public:
    mno_quote() : runtime_error("no quotes"){}
} mnoquote;



#endif
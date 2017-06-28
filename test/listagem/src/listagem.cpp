#include <iostream>
#include <algorithm>
#include "listagem.h"
#include "my_exceptions.h"
#include <list>
//#include <memory>
#include <string>

#include <deque>
#include <string.h>


#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
//#include <stdexcept>
#include <vector>

#define TOTAL 10

bool my_question(const char* question){
	string my_prompt(" ('y' para sim e 'n' para não) >>");
	char answer[30];	// armazena a resposta do usuário
		
	cout << question << my_prompt;
	
	do //enquanto o usuário não responde com 'n' ou 'y'
	{
		cin.getline(answer,30);	//pega a resposta
		
		// se pegar falha em cin, ou cin.getline tiver extraido mais que dois caracteres ou não for y ou n
		try{if(cin.fail() or cin.gcount()>2 or (strcmp(answer,"y")!=0 and strcmp(answer,"n")!=0) )
			throw std::invalid_argument("Input inválido.");	//
		}catch(std::exception &e){
			cout << e.what() << my_prompt;
		}
	}
	while( (strcmp(answer,"y") !=0 and strcmp(answer,"n")!=0 ) );
	return ( strcmp(answer,"y") == 0 );	// retorna true se a resposta for "sim"
}



int funcexp () {

char num[2];
	while(true)
	{
    cin.getline(num,2);
    try{
       if(cin.fail() or cin.gcount()>2){
           throw mbadtype;
       }
       cout << "out.\n";
   }
   catch( std::exception &e ){
      cout<<e.what()<<endl;
          break;
   }
	}
	cout << endl<< "é\n";
  return 0;
}

int func_price()
{
	int price;
	string new_s;
	if (my_question(" Deseja alterar?") ){ // Pergunta ao usuário se ele deseja trocar o preço do produto
		cout << "Insira novo preço (será arredondad). >>" ;
		cin >> new_s;
		try{price = std::stoi(new_s);
		}catch (exception &e){
			cout << "Preço inválido. Setando em $1.99 ."<< endl;
			price = 1;
		}
	}

	cout << "is " << price << endl;
	return 9;
}

int set_valid_number(int smallest, int greatest)
{
	int number;
	string str;
	int counter = 0;

	while (number < smallest or greatest < number )
	{
		if(counter++ > 0)cout << "Digite um número válido. >>";
		getline(cin,str,'\n');
		try{
		number = stoi(str);
		}catch(std::exception& e){
			number = greatest+1;
		}
	}
	return number;
}

int my_read () {
  std::ifstream is ("text.txt", std::ifstream::binary);
  if (is) {

  	is.seekg (0, is.end);
	int length = is.tellg();	// Armazena a quantidade de caracteres no arquivo
	is.seekg (0, is.beg);	// volta o ponteiro do buffer pro início
  	
  	int new_lines = std::count(std::istreambuf_iterator<char>(is),
  			   std::istreambuf_iterator<char>(), '\n');

    //is.close();
  	//cout << 
    cout << "new lines = " << new_lines << " caracteres = " << length << endl;


    // print content:
    //std::cout.write (buffer,length);

    //delete[] buffer;
  }

  return 0;
}

int main()
{
	//try{	throw mbadtype; }catch(std::exception &e){cout << "caught: " << e.what() << endl;}
	//funcexp();
	//my_question("toma esse rock. ") ? (cout << "tomei"): (cout << "naotomei" ) ;
	//func_price();
	//cout << "Dê input q preste. >> ";
	//set_valid_number(0,2);
	//cout<< "sí\n";
	my_read();

	/*TipoA * a = new TipoA;
	/Base * basea = a;
	Base * baseb = basea;

	baseb->foo();
	basea->foo();*/

	return 0;
}

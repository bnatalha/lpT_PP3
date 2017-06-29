#include "qlt.h"

namespace qlt{

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
	int price = 5;
	string new_s;
	if (my_question(" Deseja alterar?") ){ // Pergunta ao usuário se ele deseja trocar o preço do produto
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
}

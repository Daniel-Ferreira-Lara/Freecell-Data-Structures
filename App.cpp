#include <bits/stdc++.h>
#include "freecell.cpp"
using namespace std;
void menu(int choice);
int main(){
	Freecell f;
	int choice,o,d;
	f.print();
		cout<< "____________________\n|Opcoes:\n|1-> Move Mesa-Temp\n|2-> Move Mesa-Naipe\n|3-> Move Mesa-Mesa";
		cout<< "\n|4-> Move Temp-Mesa\n|5-> Move Temp-Naipe\n|6-> Move Naipe-Mesa\n|7-> Move Naipe-Temp\n|8-> Jogadas\n|9->Sair\n|____________________\n"<<endl;
	cin>>choice;
	while(choice!=9){
		
		cout<< "____________________\n|Opcoes:\n|1-> Move Mesa-Temp\n|2-> Move Mesa-Naipe\n|3-> Move Mesa-Mesa";
		cout<< "\n|4-> Move Temp-Mesa\n|5-> Move Temp-Naipe\n|6-> Move Naipe-Mesa\n|7-> Move Naipe-Temp\n|8-> Jogadas\n|9->Sair\n|____________________\n"<<endl;
		if(choice<8&&choice>0){
			cout<<"Digite a Origem e O destino: ";
			cin>>o>>d;
		}
		switch(choice){
			case 1:
				f.mesa_tempo(o,d);
				break;
			case 2:
				f.mesa_naipe(o,d);
				break;
			case 3:
				f.mesa_mesa(o,d);
				break;
			case 4:
				f.tempo_mesa(o,d);
				break;
			case 5:
				f.tempo_naipe(o,d);
				break;
			case 6:
				f.naipe_mesa(o,d);
				break;
			case 7:
				f.naipe_tempo(o,d);
				break;
			case 8:
				f.plays();
				break;
			case 9:
				break;
		}
		f.print();
		cin>>choice;
		
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
class Freecell{
	private:
		#define RED "\e[0;31m\e[47m"
		#define GRN "\e[0;32m\e[47m"
		#define reset "\e[0m\e[0;30m\e[47m"
		#define mp(a,b) (make_pair(a,b))
		#define pb(x) push_back(x)
		enum naipes{copas = 3,ouros,paus,espadas};
		typedef pair<int,int> Card;
		vector<Card> mesa[8];
		vector<Card> tempo;
		vector<Card> naipe[4];
		int jogadas;
		void printCard(Card card);
		void create();
		void msg(int resp,string origin,int n);
		bool isRed(Card card){return(card.second<5);}
		bool isBlack(Card card){return(!isRed(card));}
		bool isSameColor(Card ant,Card next){return(isRed(ant)==isRed(next));}
		bool isSameNaipe(Card ant,Card next){return(ant.second==next.second);}
		bool isSucessor(Card ant,Card next){return(ant.first==next.first-1);}
		void erros(int retorno, string ini, string fim, string algofim);
	public:
		Freecell();
		~Freecell();
		void printV(vector<Card> v);
		void print();
		void mesa_naipe(int ori,int dest);
		void mesa_tempo(int ori,int dest);
		void mesa_mesa(int ori,int dest);

		void tempo_mesa(int ori,int dest);
		void tempo_naipe(int ori,int dest);

		void naipe_tempo(int ori,int dest);
		void naipe_mesa(int ori,int dest);

		void plays();
};
//Private
void Freecell::create(){
	srand(time(NULL));
	vector<Card> aux;
	for(int i=1;i<=13;i++)
		for(int j=3;j<7;j++)
			aux.pb(mp(i,j));
	//printV(aux);
	for(int i=0;i<=5;i++)
		random_shuffle(aux.begin(),aux.end());
	//printV(aux);
	int n=0;
	while(n<aux.size())
		mesa[n%8].pb(aux[n++]);
	// for(int i=0;i<8;i++)
	// 	printV(mesa[i]);
	for(int i=0;i<=4;i++)
		tempo.pb(mp(0,0));
	jogadas=0;
}
void Freecell::msg(int resp,string origin,int n){
	switch(resp){
		case 1:
			cout<<"carta movida para "<<origin<<" de numero "<<n<<endl;
			jogadas++;
			break;
		case -1:
			cout<<"Erro ao mover a carta\n";
			break;
		default:
			break;
	}
}
void Freecell::erros(int retorno, string ini, string fim, string algofim)
{
    switch (retorno)
    {
    case 1:
        puts( "\nCarta movida com sucesso :)\n" );
        break;
    case 0:
        puts("\nLocais inexistentes\n" );
        break;
    case -1:
        printf("\n%s esta sem nada\n" , ini);
        break;
    case -2:
        printf("\n%s esta %s\n" , fim, algofim);
        break;
    case -3:
        puts("\nNao eh possivel mover\n" );
        break;
    default:
        puts("\nMovimento invalido :/\n" );
        break;
    }
	jogadas++;
}


//Public
Freecell::Freecell(){
	create();
	cout<<"Jogo criado\n";
}
Freecell::~Freecell(){cout<<"Jogo destruido\n";}

void Freecell::printV(vector<Card> vet){
	for(Card c: vet)
		printCard(c);
	cout<<endl;
}
void Freecell::printCard(Card c){printf("[%2d|%c]",c.first,c.second);}//cout<<"["<<c.first<<"|"<<(char)c.second<<"]";}
void Freecell::print(){

	cout << "[TEMP] = ";
	for(int i=0;i<4;i++){
		cout<<i<<"-";
		if(tempo[i].first!=0)
			printCard(tempo[i]);
		else
			printf("[  | ]");
		cout<<" ";
	}
	int i=0;
	cout<<endl<<endl;
	
	for(vector<Card> vc:naipe){
		cout<<"[NAIPE "<<i++<<"] ==> ";
		printV(vc);
	}
	cout<<endl<<endl,i=0;

	for(vector<Card> vc:mesa){
		printf("[MESA %2d] ==> ",i++);//cout<<"[MESA "<<i++<<"] ==> ";
		printV(vc);
	}
}

void Freecell::mesa_naipe(int ori,int dest){
	if((!naipe[dest].size())||((naipe[dest].size())&&isSucessor(naipe[dest].back(),mesa[ori].back())&&isSameNaipe(naipe[dest].back(),mesa[ori].back())))
			naipe[dest].push_back(mesa[ori].back()),mesa[ori].pop_back(),erros(1,"Mesa","naipe","vazia");
	else
		msg(-1,"naipe",dest);
}
void Freecell::mesa_tempo(int ori,int dest){
	if(!tempo[dest].first)
			tempo[dest]=mesa[ori].back(),mesa[ori].pop_back(),msg(1,"temporario",dest);
	else
		msg(-1,"temporario",dest);
}
void Freecell::mesa_mesa(int ori,int dest){
	if(mesa[ori].size() && !isSameColor(mesa[ori].back(),mesa[dest].back()) && isSucessor(mesa[ori].back(),mesa[dest].back()))
		mesa[dest].push_back(mesa[ori].back()), mesa[ori].pop_back(), msg(1,"mesa",dest);
	else
		msg(-1,"mesa",dest);
}

void Freecell::tempo_mesa(int ori,int dest){
	if(mesa[ori].size() && !isSameColor(tempo[ori],mesa[dest].back()) && isSucessor(tempo[ori],mesa[dest].back()))
		mesa[dest].push_back(tempo[ori]), mesa[ori].pop_back(), msg(1,"mesa",dest);
	else
		msg(-1,"mesa",dest);
}
void Freecell::tempo_naipe(int ori,int dest){
	if((!naipe[dest].size())||((naipe[dest].size())&&isSucessor(naipe[dest].back(),tempo[ori])&&isSameNaipe(naipe[dest].back(),tempo[ori])))
			naipe[dest].push_back(tempo[ori]),mesa[ori].pop_back(),msg(1,"naipe",dest);
	else
		msg(-1,"naipe",dest);
}

void Freecell::naipe_mesa(int ori,int dest){
	if(naipe[ori].size() && !isSameColor(naipe[ori].back(),mesa[dest].back()) && isSucessor(naipe[ori].back(),mesa[dest].back()))
		mesa[dest].push_back(naipe[ori].back()), naipe[ori].pop_back(), msg(1,"mesa",dest);
	else
		msg(-1,"mesa",dest);
}
void Freecell::naipe_tempo(int ori,int dest){
	if(!tempo[dest].first)
			tempo[dest]=naipe[ori].back(),naipe[ori].pop_back(),msg(1,"temporario",dest);
	else
		msg(-1,"temporario",dest);
}

void Freecell::plays(){
	cout<<"\n\n Jogadas ate agora ==> "<<jogadas<<" plays\n";
}

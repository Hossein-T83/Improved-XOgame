#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
// tabe chap jadval
void jadval(string play[3][3]){
	cout<<"     *     *"<<endl;
	cout<<"  "<<play[0][0];
	cout<<" *  "<<play[0][1];
	cout<<" * "<<play[0][2]<<endl;
	
	cout<<"     *     *"<<endl<<"*****************"<<endl;
	
	cout<<"     *     *"<<endl;
	cout<<"  "<<play[1][0];
	cout<<" *  "<<play[1][1];
	cout<<" * "<<play[1][2]<<endl;
	cout<<"     *     *"<<endl<<"*****************"<<endl;
	cout<<"     *     *"<<endl;
	cout<<"  "<<play[2][0];
	cout<<" *  "<<play[2][1];
	cout<<" * "<<play[2][2]<<endl;
	cout<<"     *     *"<<endl;
}
//player 1 = red and player 2 = blue
bool error(int i2, int j2,string play[3][3] , int i , int j){
	if (play[i2][j2][1]<play[i][j][1] || play[i2][j2]==" ")
		return true;
	else
		return false;
}
bool errorBazi(int i, int j,string play[3][3],string sym){
	if (play[i][j][1]<sym[1] || play[i][j]==" ")
		return true;
	else
		return false;
}
bool available(string sym, string player[6]){
	bool check=false;
	for (int i=0 ; i<6; i++){
		if (player[i]==sym){
			check=false;
			return true;
		}
	}
	if (!check)
		return false;
}
int main(){
	string sym;
	int score1=0,score2=0;
	string player1Name,player2Name;
	cout<<"Please enter your usernames: "<<endl;
	cin>>player1Name>>player2Name;
	
	//loading file
	ifstream oldhistory;
	oldhistory.open("Oldhis.txt",ios_base::app);
	string line;
	ofstream newhistory;
    newhistory.open("newhis.txt",ios_base::app);
	
	//checking game history
	bool neww=true;
	int player1Score=0,player2Score=0;
	string temp;
	while(getline(oldhistory,line))
	{
		if(line.find(player1Name)!=string::npos && line.find(player2Name)!=string::npos)
        {
            cout <<line<<endl;
            neww=false;
       		for (int i=0; i<line.length();i++){
       			if (line[i]<58 && line[i]>47){
       				temp.push_back(line[i]);
				}
				if (line[i]==45){
					player1Score=stoi(temp);
					temp="";
				}
				if(i==line.length()-1)
					player2Score=stoi(temp);  
			}
			string tempName;
			for (int i=0; i<line.length();i++){
       			if (line[i]>96 && line[i]<123){
       			 	tempName.push_back(line[i]);
				}
				else{
					if (player1Name!=tempName){
						swap(player1Name,player2Name);
						break;
					}
				}
			}
			
        }
        else{
        	newhistory<<line<<endl;
		}
    }
    
    oldhistory.close();
    
    
    
	
	int i , j , i2,j2;
	// mohre ha
	string player1[6],player2[6];
	player1[0]="R1",player1[1]="R1",player1[2]="R2",player1[3]="R2",player1[4]="R3",player1[5]="R3",	player2[0]="B1",player2[1]="B1",player2[2]="B2",player2[3]="B2",player2[4]="B3",player2[5]="B3";
	
	string play[3][3],posht[3][3],posht2[3][3];
	for (int i=0 ; i<3; i++){
		for (int j=0 ; j<3 ;j++){
			play[i][j]="  ";
		}
	}
	
	string check;
	//bool player nobat ro moshakhas mikone, true = player1 and false = player2
	bool game=true,player=true;
	int num;
	int round=1;
	check="no";
	
	
	while (game){
		start:
		if (round>2){
			cout<<"Change?(yes/no)"<<endl;
			cin>>check;
		}
		round++;
		if (check=="no"){
			cout<<"Please choose your mohre: "<<endl;
			//chap mohre haye mojod
			if(player){
				cout<<"Player1("<<player1Name<<"): ";
				for (int i=0 ; i<6 ; i++){
					cout<<player1[i]<<" ";
				}
			}
			else{
				cout<<"Player2("<<player2Name<<"): ";
				for (int i=0 ; i<6 ; i++){
					cout<<player2[i]<<" ";
				}
			}
			cout<<endl;
			symbol:
			cin>>sym;
			//baresi mojod boodan
			if(player){
				if (!available(sym,player1))
				{
					cout<<"Mohre mojod nist lotfan dobare vared konid: ";
					goto symbol;
				}
			}
			else{
				if (!available(sym,player2))
				{
					cout<<"Mohre mojod nist lotfan dobare vared konid: ";
					goto symbol;
				}
			}
			cout<<"Please enter a coordinate: "<<endl;
			cin>>i>>j;
			if(player){
				if (!errorBazi(i,j,play,sym))
				{
					cout<<"Momken nist lotfan dobare vared konid: ";
					goto symbol;
				}
			}
			else{
				if (!errorBazi(i,j,play,sym))
				{
					cout<<"Momken nist lotfan dobare vared konid: ";
					goto symbol;
				}
			}
			posht2[i][j]=posht[i][j];
			posht[i][j]=play[i][j];
			play[i][j]=sym;
			// avaz kardan nobat va hazf mohre haye estefade shode
			if (play[i][j][0]=='R'){
				player=false;
				for (int n=0 ; n<6 ; n++){
					if (player1[n]==play[i][j]){
						player1[n]=" ";
						break;
					}
				}
			}
			else{
				player=true;
				for (int n=0 ; n<6 ; n++){
					if (player2[n]==play[i][j]){
						player2[n]=" ";
						break;
					}
				}
			}
			
			jadval(play);
		}
		else{
			// avaz kardan jaye mohre ha
			cout<<"mahal mohre mored nazar va mahal jadid ra vared konid: ";
			cin>>i>>j>>i2>>j2;
			if(player){
				if (!error(i2,j2,play,i,j)||play[i][j][0]!='R')
				{
					cout<<"Momken nist lotfan dobare vared konid: ";
					goto start;
				}
			}
			else{
				if (!error(i2,j2,play,i,j)||play[i][j][0]!='B')
				{
					cout<<"Momken nist lotfan dobare vared konid: ";
					goto start;
				}
			}
			play[i2][j2]=play[i][j];
			play[i][j]=posht[i][j];
			posht[i][j]=posht2[i][j];
			jadval(play);
			player=(player+1)%2;
		}
		
		
		
		// barressi bord
		for (int i=0 ; i<3; i++){
			if (play[i][0][0]==play[i][1][0] && play[i][0][0]==play[i][2][0] && play[i][0]!="  "){
				if (play[i][0][0]=='R'){
					cout<<"Player 1 wins!"<<endl;
					//sabt score to file
					if (neww){
						newhistory<<player1Name<<" 1 - 0 "<<player2Name<<endl;
					}
					else{
						player1Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
				else{
					cout<<"Player 2 wins!"<<endl;
					if (neww){
						newhistory<<player2Name<<" 1 - 0 "<<player1Name<<endl;
					}
					else{
						player2Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
			}
			if (play[0][i][0]==play[1][i][0] && play[0][i][0]==play[2][i][0] && play[0][i]!="  "){
				if (play[0][i][0]=='R'){
					cout<<"Player 1 wins!"<<endl;
					if (neww){
						newhistory<<player1Name<<" 1 - 0 "<<player2Name<<endl;
					}
					else{
						player1Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
				else{
					cout<<"Player 2 wins!"<<endl;
					if (neww){
						newhistory<<player2Name<<" 1 - 0 "<<player1Name<<endl;
					}
					else{
						player2Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
			}
		}
		if (play[0][0][0]==play[1][1][0] && play[0][0][0]==play[2][2][0] && play[0][0]!="  "){
			if (play[0][i][0]=='R'){
					cout<<"Player 1 wins!"<<endl;
					if (neww){
						newhistory<<player1Name<<" 1 - 0 "<<player2Name<<endl;
					}
					else{
						player1Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
				else{
					cout<<"Player 2 wins!"<<endl;
					if (neww){
						newhistory<<player2Name<<" 1 - 0 "<<player1Name<<endl;
					}
					else{
						player2Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
		}
		else if (play[0][2][0]==play[1][1][0] && play[0][0][0]==play[2][0][0] && play[0][2]!="  "){
			if (play[0][i][0]=='R'){
					cout<<"Player 1 wins!"<<endl;
					if (neww){
						newhistory<<player1Name<<" 1 - 0 "<<player2Name<<endl;
					}
					else{
						player1Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
				else{
					cout<<"Player 2 wins!"<<endl;
					if (neww){
						newhistory<<player2Name<<" 1 - 0 "<<player1Name<<endl;
					}
					else{
						player2Score++;
						newhistory<<player1Name<<" "<<player1Score<<" - "<<player2Score<<" "<<player2Name;
					}
					game=false;
				}
		}
		
	}
	newhistory.close();
	remove("Oldhis.txt");
    rename("newhis.txt", "Oldhis.txt");
}

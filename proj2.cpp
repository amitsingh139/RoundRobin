#include<bits/stdc++.h>
using namespace std;

class player{
	public:
		int id;
		char name[30];
		int wins=0;
		int points=0;
		float nrr=0.0;
		void enterData();
		void showData();
};
void player :: enterData(){
	cout<<"Enter name : ";
	cin>>name;
}
void player :: showData(){
	cout<<name<<"\t"<<wins<<"\t"<<nrr<<endl;
}
void display(player p[],int n){
	for(int i=0;i<n;i++)
		p[i].showData();
}


void random(int n,map<pair<int,int>,int> &mp,int arr[]){
        int val1=0;
	int val2=0;
        int f=1;
        srand(static_cast<unsigned int>(time(nullptr)));	
        while(f==1 || mp[{val1,val2}]){
                val1=(rand()%n);
		val2=(rand()%n);
                if(mp[{val1,val2}]){
                        f=0;
                        mp[{val1,val2}]=0;
			arr[0]=val1;
			arr[1]=val2;
                }
        }
}

bool comp(pair<pair<int,int>,int> &x,pair<pair<int,int>,int> &y){
        if(x.first.first>y.first.first)
	      return true;
        else if(x.first.first<y.first.first)
	      return false;
        else 
		return x.first.second>y.first.second;
}

void checkResult(player p[],int n,int res[]){
	int max=0;
	vector<pair<pair<int,int>,int>> vec;
	for(int i=0;i<n;i++)
		vec.push_back({{p[i].wins,p[i].nrr},i});

	sort(vec.begin(),vec.end(),comp);

	res[0]=vec[0].second;
	res[1]=vec[1].second;
}

void nrr(int x,int y,player p[],int i,int j){
	float d;
	if(x>y){
		d=(float)x/(float)y;
		p[i].nrr+=d;
		p[j].nrr-=d;
	}
	else{
		d=(float)y/(float)x;
		p[i].nrr-=d;
		p[j].nrr+=d;
	}
	cout<<"nrr : "<<d<<endl;
}

void round_robin(player p[],int n){
	int t=(n*(n-1))/2;   //total no of matches

        map<pair<int,int>,int> mp;	
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			mp.insert({{i,j},1});
		}
	}

	while(t){       
		        cout<<endl;
			int arr[2];
			random(n,mp,arr);
			int i=arr[0];
			int j=arr[1];
		        cout<<endl;	
		        cout<<"Match Between : "<<p[i].name<<" & "<<p[j].name<<endl;
			cout<<"Enter match result "<<endl;
			cout<<"Who wins player1 or player2  : ";

			int x;
			cin>>x;
			if(x==1)
				p[i].wins++;
			else
				p[j].wins++;
			int val1=0,val2=0;
			cout<<"Enter player 1 points : ";
			cin>>val1;
			p[i].points+=val1;

			cout<<"Enter player 2 points : ";
                        cin>>val2;
                        p[j].points+=val2;

			nrr(val1,val2,p,i,j);
			--t;
	}
	cout<<endl;
	
	cout<<"League Stage is completed "<<endl;

	cout<<"Name\t"<<"Wins\t"<<"NRR"<<endl;
	display(p,n);
	

	int res[2]={0,0};
	checkResult(p,n,res);
	cout<<"Final match is between "<<p[res[0]].name <<" & "<<p[res[1]].name<<endl;
	
}


int main(){
	int n;
	cout<<"Enter no of player : ";
	cin>>n;
	player p[n];
	for(int i=0;i<n;i++)
		p[i].enterData();
	round_robin(p,n);
}
#include<bits/stdc++.h>
using namespace std;

class player{
	public:
		int id;
		char name[30];
		int wins=0;
		float nrr=0.0;
		void enterData();
		void showData();
};
void player :: enterData(){
	//cout<<"Enter name : ";
	cin>>name;
}
void player :: showData(){
	cout<<name<<"\t"<<wins<<"\t";
	printf("%.2f",nrr);
	cout<<endl;
}
void display(player p[],int n){
	for(int i=0;i<n;i++)
		p[i].showData();
}

//randomly searching between the player id's
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
	vector<pair<pair<int,int>,int>> vec;
	for(int i=0;i<n;i++)
		vec.push_back({{p[i].wins,p[i].nrr},i});

	sort(vec.begin(),vec.end(),comp);

	res[0]=vec[0].second;
	res[1]=vec[1].second;
	res[2]=vec[2].second;
	res[3]=vec[3].second;
}

void nrr(int x,int y,player p[],int i,int j){
	float d;
        if((x == 7 && y==0) ||(x==0 && y==7)){
		d=2.0;
		if(x>y){
			p[i].nrr+=d;
		        p[j].nrr-=d;
	        }
	        else{
		        p[i].nrr-=d;
		        p[j].nrr+=d;
	        }
	}
        else{
		if(x>y){
		       d=((float)x/(float)y)/10.0;
		       p[i].nrr+=d;
		       p[j].nrr-=d;
	        }
	        else{
		       d=((float)y/(float)x)/10.0;
		       p[i].nrr-=d;
		       p[j].nrr+=d;
	        }
	}
	cout<<"nrr : "<<d<<endl;
}

void singleEliminator(player p[],int n){
	int res[3]={0,0,0};
        checkResult(p,n,res);

        int l;
        cout<<"\nEliminator Match is between "<<p[res[1]].name<<" & "<<p[res[2]].name<<endl;
        cout<<"Who wins : ";
        cin>>l;
        int f2;
        if(l==1)
                f2=res[1];
        else
                f2=res[2];

        cout<<"\nFinal match is between "<<p[res[0]].name <<" & "<<p[f2].name<<endl;
}

void doubleEliminator(player p[],int n){
        int res[4]={0,0,0,0};
        checkResult(p,n,res);

        int l;
        cout<<"\n First Eliminator Match is between "<<p[res[3]].name<<" & "<<p[res[2]].name<<endl;
        cout<<"Who wins : ";
        cin>>l;
        int f1;
        if(l==1)
                f1=res[3];
        else
                f1=res[2];

        cout<<"\nSecond Eliminator Match is between "<<p[res[1]].name <<" & "<<p[f1].name<<endl;
	cout<<"Who wins : ";
	int f2;
	cin>>l;
	if(l==1)
		f2=res[1];
	else
		f2=f1;

	cout<<"\nFinal match is between "<<p[res[0]].name <<" & "<<p[f2].name<<endl;

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

			cout<<"Enter player 2 points : ";
                        cin>>val2;

			nrr(val1,val2,p,i,j);
			--t;
	}
	cout<<endl;
	
	cout<<"League Stage is completed "<<endl;
        cout<<"Name\t"<<"Wins\t"<<"NRR"<<endl;
        display(p,n);


	int x;
        cout<<"Eleminator type : 1.Single Eliminator 2.Double Eliminator "<<endl;
        cin>>x;	
        	
	switch(x){
		case 1: singleEliminator(p,n);
			break;
		case 2: doubleEliminator(p,n);
			break;	
	}
		
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

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

ofstream Index,Seq,Con;
const int K = 0;
const int B = 1;
const int G = 2;
const int C = 3;
const int R = 4;
const int M = 5;
const int Y = 6;
const int W = 7;
const int k = 8;
const int b = 9;
const int g = 10;
const int c = 11;
const int r = 12;
const int m = 13;
const int y = 14;
const int w = 15;
const string Color = "KBGCRMYWkbgcrmyw";
const string Color2[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};
int Fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

class edge_permu{

  private:
    short Edge[12];
    short Rot[16][3] = {{2,1,0},{3,4,0},{6,5,1},{5,7,3},{8,9,2},{10,8,4},{9,11,6},{11,10,7},{0,1,2},{0,4,3},{1,5,6},{3,7,5},{2,9,8},{4,8,10},{6,11,9},{7,10,11}};
    void oneFaceTurn(int face){
      int t;
      t =Edge[Rot[face][0]];
      Edge[Rot[face][0]] = Edge[Rot[face][1]];
      Edge[Rot[face][1]] = Edge[Rot[face][2]];
      Edge[Rot[face][2]] = t;
    }
    int fact(int x){
      return Fact[x];
    }
    
  public:
    edge_permu(int index){
      int visit[12] = {};
      for(int i=0; i<12; i++){
        int q = index / fact(11-i);
        int count = 0;
        for(int j=0; j<12; j++){
          if(visit[j] == 0){
            if(q == count){
              Edge[i] = j;
              visit[j] = 1;
              break;
            }
            count += 1;
          }
        }
        index %= fact(11-i);
      }
    }
    void Turn(string s){
      for(int i=0; i<s.length(); i++){
        for(int j=0; j<16; j++){
          if(Color2[j][0] == s[i]){
            oneFaceTurn(j);
          }
        }
      }
    }
    void print(){
      for(int i=0; i<12; i++){
        printf("%d ",Edge[i]);
      }
      printf("\n");
    }

    int index(){
      int visit[12] = {};
      int sum = 0;
      for(int i=0; i<12; i++){
        int a = Edge[i];
        int count = 0;
        for(int j=0; j<a; j++){
          if(visit[j] == 0){
            count++;
          }
        }
        visit[a] = 1;
        sum += count * fact(11-i);
      }
      return sum;
    }
};




const int Max_index = 479001600;
edge_permu a(0);
vector<int> V;
vector<pair<int,string>> seqin;
vector<string> concen;
int num[479001600] = {};
int nei[8][3] = {{1,2,4},{0,3,5},{0,3,6},{1,2,7},{0,5,6},{1,4,7},{2,4,7},{3,5,6}};
bool isfind = false;
int Max_depth = 10;
int maxnum = 1;
string inverse(string s){
	
	string news;
	for(int i = s.size()-1; i>=0 ; i--){
		for(int j=0; j<16; j++){
			if(Color[j] == s[i]){
				news += Color2[(j+8)%16];
			}
		}
	}
	return news;
}
string reverse(string s){
    string news;
	for(int i = 0; i<s.size() ; i++){
		for(int j=0; j<16; j++){
			if(Color[j] == s[i]){
				news += Color2[(j+8)%16];
			}
		}
	}
	return news;
}
void dfs(string s,int face,int depth){
	
    if(depth == Max_depth){
    	if(isfind && num[a.index()] > 1){
	    	seqin.push_back({a.index(),s});
		}
		else{
			num[a.index()]++;
		}
        return ;
    }
    for(int i=0; i<3; i++){
    	for(int j=0; j<2; j++){
    		a.Turn(Color2[nei[face][i] + 8 * j]);
    		dfs(s + Color2[nei[face][i] + 8 * j],nei[face][i],depth+1);
    		a.Turn(Color2[nei[face][i] + 8 * (1-j)]);
		}
	}
}
void Init(){
	Index.open("Index.txt");
	Seq.open("Seq.txt");
	Con.open("Concen.txt");
}
void First(){
    for(int i=0; i<16; i++){
        a.Turn(Color2[i]);
        dfs(Color2[i],i%8,0);
        a.Turn(Color2[(i+8)%16]);
    }
    for(int i=0; i<Max_index; i++){
    	if(num[i] > 1){
    		//printf("%d %d\n",i,num[i]);
    		maxnum = max(maxnum,num[i]);
    		Index << i << "\n";
    		V.push_back(i);
		}
	}
	/*
	for(int i=0; i<V.size(); i++){
		printf("V[%d] : %d\n",i,V[i]);
	}
	*/
    printf("V.size() : %d\n",V.size()); // 149296
    printf("%d\n",a.index());
    printf("maxnum : %d\n",maxnum);
}
void Second(){
	
	for(int i=0; i<16; i++){
        a.Turn(Color2[i]);
        dfs(Color2[i],i%8,0);
        a.Turn(Color2[(i+8)%16]);
    }
    printf("seqin.size() : %d\n",seqin.size());
    sort(seqin.begin(),seqin.end());
    for(int i=0; i<seqin.size(); i++){
    	Seq << seqin[i].first << " " << seqin[i].second << "\n";
	}
}
void Third(){
	int baseindex = -1;
	string basestring;
	for(int i=0; i<seqin.size(); i++){
		int t = seqin[i].first;
		string s = seqin[i].second;
		if(i%1000000 == 0){
			cout << "i : " << i << endl;
		}
		if(baseindex == -1 || baseindex != t){
			if(baseindex != -1){
				Con << baseindex << "\n";
				if(baseindex == 0){
					for(int j=0; j<concen.size(); j++){
						Con << concen[j] << "\n";
					}
				}
				basestring = concen[0];
				for(int j=1; j<concen.size(); j++){
					Con << basestring + inverse(concen[j]) << "\n";
				}
				concen.clear();
				Con << "End" << "\n";
			}
			baseindex = t;
		}
		concen.push_back(s);
	}
	Con << baseindex << "\n";
	basestring = concen[0];
	for(int j=1; j<concen.size(); j++){
		Con << basestring + inverse(concen[j]) << "\n";
	}
	concen.clear();
	Con << "End" << "\n";
}
void Finish(){
	Index.close();
	Seq.close();
	Con.close();
}
int main(int argc, char* a0rgv[]) {
	Init();
	First();
	isfind = true;
	Second();
	Third();
	Finish();
	
}

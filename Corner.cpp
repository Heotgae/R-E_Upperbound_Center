#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

ifstream Corner[19];

using namespace std;
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
int Fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
int Pow4[7]={1, 4, 16, 64, 256, 1024, 4096};
int per_rot[16][3] = {{0,1,2},{0,2,3},{0,4,1},{0,3,4},{1,5,2},{2,5,3},{1,4,5},{3,5,4},{2,1,0},{3,2,0},{1,4,0},{4,3,0},{2,5,1},{3,5,2},{5,4,1},{4,5,3}};
int ori_rot[16][3] = {{0,0,0},{3,2,3},{2,3,3},{3,3,2},{2,3,3},{3,3,2},{3,3,2},{0,0,0},{0,0,0},{1,1,2},{2,1,1},{1,2,1},{2,1,1},{1,2,1},{1,2,1},{0,0,0}};
const string Color3[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};// {x,y,z} , {z,y,x} ÀÌ¸י {a,b,c} , {4-a,4-c,4-b}
const string num[6] = {"0","1","2","3","4","5"};
class corner_permu{
  int per_cor[6];
  int ori_cor[6];
  private:
    int fact(int x){
        return Fact[x];
    }
    int pow4(int x){
        return Pow4[x];
    }
    void oneFaceTurn(int face){
      int p0 = per_cor[per_rot[face][0]];
      int o0 = ori_cor[per_rot[face][0]];
      per_cor[per_rot[face][0]] = per_cor[per_rot[face][1]];
      ori_cor[per_rot[face][0]] = (ori_cor[per_rot[face][1]] + ori_rot[face][1])%4;
      per_cor[per_rot[face][1]] = per_cor[per_rot[face][2]];
      ori_cor[per_rot[face][1]] = (ori_cor[per_rot[face][2]] + ori_rot[face][2])%4;
      per_cor[per_rot[face][2]] = p0;
      ori_cor[per_rot[face][2]] = (o0 + ori_rot[face][0])%4;
    }
  public:
    corner_permu(int index){
      int per_index = index / pow4(6);
      int ori_index = index % pow4(6);
      bool visit[6] = {};
      for(int i=0; i<6; i++){
        int count = 0,q = per_index/fact(5-i);
        for(int j=0; j<6; j++){
          if(visit[j] == 0){
            if(q == count){
              per_cor[i] = j;
              visit[j] = 1;
              break;
            }
            count += 1;
          }
        }
        per_index %= fact(5-i);
      }
      for(int i=0; i<6; i++){
        ori_cor[i] = ori_index / pow4(5-i);
        ori_index %= pow4(5-i);
      }
    }
    void Turn(string s){
      for(int i=0; i<s.length(); i++){
        for(int j=0; j<16; j++){
          if(Color3[j][0] == s[i]){
            oneFaceTurn(j);
          }
        }
      }
    }
    string print(){
        string s;
        for(int i=0; i<6; i++){
            s += num[per_cor[i]]+ " ";
        }
        s += "\n";
        for(int i=0; i<6; i++){
            s += num[ori_cor[i]] + " ";
        }
        s += "\n";
        return s;
    }
    int index(){
      int sum = 0;
      bool visit[6] = {};
      for(int i=0; i<6; i++){
        int count = 0;
        for(int j=0; j<per_cor[i]; j++){
          if(!visit[j]){
            count++;
          }
        }
        sum += count * fact(5-i);
        visit[per_cor[i]] = 1;
      }
      sum *= pow4(6);
      for(int i=0; i<6; i++){
        sum += ori_cor[i] * pow4(5-i);
      }
      return sum;
    }
};

string Number[21] =  {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};
int D[11520] = {};
bool V[11520] = {};
vector<string> Seq;
int Numd = {};

void Init(){
	for(int i=12; i<19; i++){
		Corner[i].open("Corner_" + Number[i] + ".txt");
	}
	for(int i=0; i<11520; i++){
		D[i] = -1;
	}
}
void Sequencing(){
	for(int i=12; i<19; i++){
		string s;
		Corner[i] >> s;
		corner_permu a(0);
		a.Turn(s);
		if(!V[a.index()]){
			Seq.push_back(s);
			V[a.index()] = true;
		}
		printf("%d : %d\n",i,Seq.size());
	}
}

int main(){
	Init();
	
	Sequencing();
}

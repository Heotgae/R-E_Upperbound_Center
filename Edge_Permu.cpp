#define DEBUG
#ifdef DEBUG
#include <cassert>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) {}
#endif

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
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
const string Color2[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};
int Fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};


FILE* pfile[19];

class edge_permu{

  private:
    short Edge[12];
    short Rot[16][3] = {{0,1,2},{0,4,3},{1,5,6},{3,7,5},{2,9,8},{4,8,10},{6,11,9},{7,10,11},{2,1,0},{3,4,0},{6,5,1},{5,7,3},{8,9,2},{10,8,4},{9,11,6},{11,10,7}};
    void oneFaceTurn(int face){
      int t;
      t =Edge[Rot[face][0]];
      Edge[Rot[face][0]] = Edge[Rot[face][1]];
      Edge[Rot[face][1]] = Edge[Rot[face][2]];
      Edge[Rot[face][2]] = t;
    }
    int fact(int x){
      ASSERT(0<=x&&x<=12);
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
    void print(int count){
      for(int i=0; i<12; i++){
        fprintf(pfile[count],"%d ",Edge[i]);
      }
      fprintf(pfile[count],"\n");
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




#define DEBUG

#ifdef DEBUG
#include <cassert>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) {}
#endif

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;

short D[479001600];
//int sum = 239500800;
int Solved[12] = {0,43679976,80061199,353742458,278902018,143099954,187983136,384401903,212340383,474278733,299011189,416502789};
queue<int> to_Crawl,Next;

int main(int argc, char* argv[]) {
    for(int i=0; i<479001600; i++){
        D[i] = -1;
    }
    for(int i=0;i<19;++i){
  	    char s[50];
  	    sprintf(s,"edge_distance%d.txt",i);
  	    pfile[i] = fopen(s, "w");
    }
    for(int i=0; i<12; i++){
        int base = Solved[i];
        D[base] = 0;
        to_Crawl.push(base);
    }
    
    int count = -1;
    int sum = 239500800;
    while(!to_Crawl.empty() && count <= 18){
        count++; 
        printf("sum : %d count : %d\n",sum,count);
        while(!to_Crawl.empty()){
            int t = to_Crawl.front(); to_Crawl.pop();
            edge_permu a(t);
            sum--;
            for(int j=0; j<16; j++){
                a.Turn(Color2[j]); 
                if(D[a.index()] == -1 || D[a.index()] > count + 1){
                    Next.push(a.index());
                    D[a.index()] = count + 1;
                }
                a.Turn(Color2[(j+8)%16]);
            }
        }
        while(!Next.empty()){
            to_Crawl.push(Next.front()); Next.pop();
        }
        printf("sum : %d count : %d\n",sum,count);
    }
    for(int i=0; i<479001600; i++){
        if(D[i] != -1){
            edge_permu a(i);
            a.print(D[i]);
        }
    }
    for(int i=0;i<19;++i){
  	    fclose(pfile[i]);
    }
    return 0;
}

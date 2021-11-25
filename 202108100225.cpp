#include <cassert>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

ofstream facecorner_dis_txt[100],face_dis_txt[100];

const int K = 0;//
const int B = 1;
const int G = 2;
const int C = 3;//
const int R = 4;
const int M = 5;//
const int Y = 6;//
const int W = 7;
const string Color[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};
int legal[4] = {0,3,5,6};
int changingface[4] = {1,2,4,7};
// uppercase: counterclockwise; lowercase: clockwise
const int evcper[8][12] = {{0,1,2,0,1,2,3,7,12,4,6,13},{},{},{3,7,5,0,3,4,3,21,8,5,22,6},{},{4,8,10,2,5,3,4,14,21,5,12,23},{6,11,9,1,4,5,7,22,14,8,23,13},{}};
int Fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
/*Permutation of [i] of pieces in this info
    first 3 elements: permutation of edges
    second 3 elements: permutation of vertices
    last [3]x[3] elements: 3 3-cycles of center pieces*/
const bool vrot[8][3] = {{false,false,false},{},{},{false,true,true},{},{false,true,true},{false,true,true},{}};
//use octal
const short initedges [12] = {1,2,4,1,1,2,2,7,4,4,7,7};
const short initvertices [6] = {0,1,2,3,4,5};//starts from 0 or 7 originally. Rotates as cube rotates, 0 and 7 positions as first digit.
const short initcenters [24] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7};//Facets on <first digit> towards direction of <second digit>
int pow6[4] = {1,6,36,216};
int CC[13][13] = {1,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,0,0,0,0,0,
1,2,1,0,0,0,0,0,0,0,0,0,0,
1,3,3,1,0,0,0,0,0,0,0,0,0,
1,4,6,4,1,0,0,0,0,0,0,0,0,
1,5,10,10,5,1,0,0,0,0,0,0,0,
1,6,15,20,15,6,1,0,0,0,0,0,0,
1,7,21,35,35,21,7,1,0,0,0,0,0,
1,8,28,56,70,56,28,8,1,0,0,0,0,
1,9,36,84,126,126,84,36,9,1,0,0,0,
1,10,45,120,210,252,210,120,45,10,1,0,0,
1,11,55,165,330,462,462,330,165,55,11,1,0,
1,12,66,220,495,792,924,792,495,220,56,13,1}; // CC[a][b] aCb 리턴
short For7[220][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,1,9},{0,1,10},{0,1,11},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,2,9},{0,2,10},{0,2,11},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,3,9},{0,3,10},{0,3,11},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,4,9},{0,4,10},{0,4,11},{0,5,6},{0,5,7},{0,5,8},{0,5,9},{0,5,10},{0,5,11},{0,6,7},{0,6,8},{0,6,9},{0,6,10},{0,6,11},{0,7,8},{0,7,9},{0,7,10},{0,7,11},{0,8,9},{0,8,10},{0,8,11},{0,9,10},{0,9,11},{0,10,11},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,2,9},{1,2,10},{1,2,11},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,3,9},{1,3,10},{1,3,11},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,4,9},{1,4,10},{1,4,11},{1,5,6},{1,5,7},{1,5,8},{1,5,9},{1,5,10},{1,5,11},{1,6,7},{1,6,8},{1,6,9},{1,6,10},{1,6,11},{1,7,8},{1,7,9},{1,7,10},{1,7,11},{1,8,9},{1,8,10},{1,8,11},{1,9,10},{1,9,11},{1,10,11},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,3,9},{2,3,10},{2,3,11},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,4,9},{2,4,10},{2,4,11},{2,5,6},{2,5,7},{2,5,8},{2,5,9},{2,5,10},{2,5,11},{2,6,7},{2,6,8},{2,6,9},{2,6,10},{2,6,11},{2,7,8},{2,7,9},{2,7,10},{2,7,11},{2,8,9},{2,8,10},{2,8,11},{2,9,10},{2,9,11},{2,10,11},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,4,9},{3,4,10},{3,4,11},{3,5,6},{3,5,7},{3,5,8},{3,5,9},{3,5,10},{3,5,11},{3,6,7},{3,6,8},{3,6,9},{3,6,10},{3,6,11},{3,7,8},{3,7,9},{3,7,10},{3,7,11},{3,8,9},{3,8,10},{3,8,11},{3,9,10},{3,9,11},{3,10,11},{4,5,6},{4,5,7},{4,5,8},{4,5,9},{4,5,10},{4,5,11},{4,6,7},{4,6,8},{4,6,9},{4,6,10},{4,6,11},{4,7,8},{4,7,9},{4,7,10},{4,7,11},{4,8,9},{4,8,10},{4,8,11},{4,9,10},{4,9,11},{4,10,11},{5,6,7},{5,6,8},{5,6,9},{5,6,10},{5,6,11},{5,7,8},{5,7,9},{5,7,10},{5,7,11},{5,8,9},{5,8,10},{5,8,11},{5,9,10},{5,9,11},{5,10,11},{6,7,8},{6,7,9},{6,7,10},{6,7,11},{6,8,9},{6,8,10},{6,8,11},{6,9,10},{6,9,11},{6,10,11},{7,8,9},{7,8,10},{7,8,11},{7,9,10},{7,9,11},{7,10,11},{8,9,10},{8,9,11},{8,10,11},{9,10,11}};
short For4[84][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,5,6},{0,5,7},{0,5,8},{0,6,7},{0,6,8},{0,7,8},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,5,6},{1,5,7},{1,5,8},{1,6,7},{1,6,8},{1,7,8},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,5,6},{2,5,7},{2,5,8},{2,6,7},{2,6,8},{2,7,8},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,5,6},{3,5,7},{3,5,8},{3,6,7},{3,6,8},{3,7,8},{4,5,6},{4,5,7},{4,5,8},{4,6,7},{4,6,8},{4,7,8},{5,6,7},{5,6,8},{5,7,8},{6,7,8}};
short For2[20][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,2,3},{0,2,4},{0,2,5},{0,3,4},{0,3,5},{0,4,5},{1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},{2,3,4},{2,3,5},{2,4,5},{3,4,5}};
short For1[1][3] = {{0,1,2}};
const short symmetries[12][8] {{0,1,2,3,4,5,6,7},{0,2,4,6,1,3,5,7},{0,4,1,5,2,6,3,7},{5,1,4,0,7,3,6,2},{3,1,7,5,2,0,6,4},{3,7,2,6,1,5,0,4},{6,4,2,0,7,5,3,1},{5,7,1,3,4,6,0,2},{6,2,7,3,4,0,5,1},{3,2,1,0,7,6,5,4},{5,4,7,6,1,0,3,2},{6,7,4,5,2,3,0,1}};

class Octahedron {
  private:

    int octpow(int n){
      return 1 << (3*n);
    }

    short vertex_flip(short ver, bool t){
      if(t){
        return (ver+6)%12;
      }
      return ver;
    }
    //
    
    short edges [12];
    short vertices [6];//contains orientation info
    short centers [24]; //centers only have color info, not original orientation. ex) {0,0,0,1,1,1,...}
    
  public:
    //short facets[8][9];
    Octahedron(int64_t index){
      int index1 = index % 369600 , index2 = ((index/369600) >> 6), index3 = (index/369600) % (1 << 6);

      //index1 복원
      int for1 = 0,for2 = (index1 % (Fact[6]/pow6[2])) / (Fact[3]/pow6[1]),for4 = (index1 % (Fact[9]/pow6[3])) / (Fact[6] / pow6[2]),for7 = index1 / (Fact[9]/pow6[3]);
      int a[12] = {};
      int count = 0,se=0;
      for(int i=0; i<3; i++){
        a[For7[for7][i]] = 7;
      }
      count = se = 0;
      for(int i=0; i<12; i++){
        if(!a[i])
          count++;
        if(For4[for4][se] == count - 1){
          a[i] = 4;
          se++;
          if(se == 3){
            break;
          }
        }
      }
      count = se = 0;
      for(int i=0; i<12; i++){
        if(!a[i])
          count++;
        if(For2[for2][se] == count - 1){
          a[i] = 2;
          se++;
          if(se == 3){
            break;
          }
        }
      }
      count = se = 0;
      for(int i=0; i<12; i++){
        if(!a[i])
          count++;
        if(For1[for1][se] == count - 1){
          a[i] = 1;
          se++;
          if(se == 3){
            break;
          }
        }
      }
      for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
          centers[3*changingface[i]+j] = a[3*i+j];
        }
      }
      //index2,index3
      bool Visit[6] = {};
      for(int i=0; i<6; i++){
        int count = 0;
        for(int j=0; j<6; j++){
          if(!Visit[j]){
            count++;
          }
          if(index2 / Fact[5-i] + 1 == count){
            vertices[i] = j + 6 * ((index3 & (1 << (5-i))) >> (5-i));
            Visit[j] = true;
            break;
          }
        }
        index2 %= Fact[5-i];
      }
    }

    void oneFaceTurn(int facetoturn){
      if(facetoturn < 8){
        short a = edges[evcper[facetoturn][2]];
        edges[evcper[facetoturn][2]] = edges[evcper[facetoturn][1]];
        edges[evcper[facetoturn][1]] = edges[evcper[facetoturn][0]];
        edges[evcper[facetoturn][0]] = a;
        a = vertex_flip(vertices[evcper[facetoturn][5]],vrot[facetoturn][2]);
        vertices[evcper[facetoturn][5]] = vertex_flip(vertices[evcper[facetoturn][4]],vrot[facetoturn][1]);
        vertices[evcper[facetoturn][4]] = vertex_flip(vertices[evcper[facetoturn][3]],vrot[facetoturn][0]);
        vertices[evcper[facetoturn][3]] = a;
        for(int i = 2; i<4; i++){
          a = centers[evcper[facetoturn][i*3+2]];
          centers[evcper[facetoturn][i*3+2]] = centers[evcper[facetoturn][i*3+1]];
          centers[evcper[facetoturn][i*3+1]] = centers[evcper[facetoturn][i*3]];
          centers[evcper[facetoturn][i*3]] = a;
        }
      }
      else {
        facetoturn -= 8;
        short a = edges[evcper[facetoturn][0]];
        edges[evcper[facetoturn][0]] = edges[evcper[facetoturn][1]];
        edges[evcper[facetoturn][1]] = edges[evcper[facetoturn][2]];
        edges[evcper[facetoturn][2]] = a;
        a = vertex_flip(vertices[evcper[facetoturn][3]],4-vrot[facetoturn][2]);
        vertices[evcper[facetoturn][3]] = vertex_flip(vertices[evcper[facetoturn][4]],4-vrot[facetoturn][0]);
        vertices[evcper[facetoturn][4]] = vertex_flip(vertices[evcper[facetoturn][5]],4-vrot[facetoturn][1]);
        vertices[evcper[facetoturn][5]] = a;
        for(int i = 2; i<4; i++){
          a = centers[evcper[facetoturn][i*3]];
          centers[evcper[facetoturn][i*3]] = centers[evcper[facetoturn][i*3+1]];
          centers[evcper[facetoturn][i*3+1]] = centers[evcper[facetoturn][i*3+2]];
          centers[evcper[facetoturn][i*3+2]] = a;
        }
      }
    }
    bool isCornerOrdered(){
      for(int i=0; i<6; i++){
        if(vertices[i]!=i){
          return false;
        }
      }
      return true;
    }
    void print(int dis){
      //cout << dis << endl;
      //여기 아래에다 파일이름 facecorner_dis.txt에 //// 사이에 있는 것 넣기, dis에는 숫자 받아온것 대충 알아듣길
      
      ///////////////////////
      for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
          facecorner_dis_txt[dis] << centers[changingface[i]*3+j] << ", ";
        }
        
      }
      facecorner_dis_txt[dis] << "\n";
      for(int i=0; i<6; i++){
        facecorner_dis_txt[dis] << vertices[i] << ", ";
      }
      facecorner_dis_txt[dis] << "\n";
      //////////////////////

      if(isCornerOrdered()){
        // 파일 추가로 corner가 맞추어져 있는 경우는 따로 파일 파서, face_dis.txt에 center 내용만 아래 ///// 사이에 있는 것
        //참고로 print는 삭제, 이 안에 들어오는거라고 facecorner에 안넣는거는 아님.
        for(int i=0; i<4; i++){
	        for(int j=0; j<3; j++){
	          face_dis_txt[dis] << centers[changingface[i]*3+j] << ", ";
	        }
	    }
	    face_dis_txt[dis] << "\n";
      }
      ///////////////////////////
      //////////////////////////
    }

    bool isFaceSolved(){
      for(int i=0; i<24; i++){
        if(centers[i]!=initcenters[i]){
          return false;
        }
      }
      return true;
    }

    bool isCornerEdgeSolved(){
      for(int i=0; i<12; i++){
        if(edges[i]!=initedges[i]){
          return false;
        }
      }
      for(int i=0; i<6; i++){
        if(vertices[i]!=initvertices[i]){
          return false;
        }
      }
      return true;
    }
    int f(int a,int b,int c,int l){
      //cout << a << " " << b << " " << c << " " << endl;
      return (CC[l][3] - CC[l-a][3] + CC[l-a-1][2] - CC[l-b][2] + CC[l-b-1][1] - CC[l-c][1]);
    }
    int64_t index(){
      int index1 = 0,index2 = 0,index3 = 0;
      //index1 center 이용
      int relloc[4][4] = {};
      int numin[4] = {};
      for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
          int num = centers[3*changingface[i]+j]/2;
          relloc[num][numin[num]+1] += relloc[num][numin[num]];
          numin[num]++;
          for(int k=3; k>=num; k--){
            relloc[k][numin[k]]++;
          }
        }
      }
      for(int i=0; i<4; i++){
        index1 += f(relloc[i][0],relloc[i][1],relloc[i][2],3 * (i+1)) * (Fact[3*i] / pow6[i]);
      }
      //index2 , index3
      bool visit[6] = {};
      for(int i=0; i<6; i++){
        int count = 0;
        for(int j=0; j<vertices[i]%6; j++){
          if(!visit[j])
            count++;
        }
        index2 += count * Fact[5-i];
        visit[vertices[i]%6] = true;
        index3 += (vertices[i]/6) * (1 << (5-i));
      }
      // return sum
      int64_t sum = (int64_t((index2 << 6) + index3) * 369600) + index1;
      return (int64_t((index2 << 6) + index3) * 369600) + index1;
    }
};



















#include <cassert>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
//#include "face_4_permu.hpp"
//#include "corner_permu.hpp"
//#include "makeart.hpp"
//#include "edge_permu.hpp"
//#include "octahedron.hpp"
#include <string>
#include <queue>
#include <vector>
//#include <stdio.h>

using namespace std;

//void Create2();
//void f();
//bool Visit[479001600] = {};
//bool Visit_per[720] = {};
//bool Visit_ori[4096] = {};
//int sum = 11520;
//int per_sum = 360;
//int ori_sum = 32;
//
//int bozo2[8][3] = {{G,R,B},{K,M,C},{K,C,Y},{B,W,G},{K,Y,M},{B,R,W},{G,W,R},{C,M,Y}};
//queue<int> To_Visit_per,Next_per;
//queue<int> To_Visit_ori,Next_ori;



int trinaryshift(int i, int j);


const int64_t MAX_SIZE = 17031168000;
const int64_t statenum = 4257792000;
int64_t sum = statenum;
int base = 369599;
int count = -1;
int maxd = -1;
vector<bool> Visit(MAX_SIZE);
queue<int64_t> to_crawl[81],Next[81];
int64_t Numdis[100] = {};

int Nonzero3(int num){
  // num -> abcd
  //num = a *  27 + b * 9 + c * 3 + d
  return (num%3 != 0) + ((num/3)%3 != 0) + ((num/9)%3 !=0) + ((num/27)%3 !=0);
}
bool Empty(){
  for(int i=0; i<81; i++){
    if(!to_crawl[i].empty()){
      return false;
    }
  }
  return true;
}
int64_t to_sum(){
	int64_t sum = 0;
	for(int i=0; i<81; i++){
		sum += to_crawl[i].size();
	}
	return sum;
}
void Init(){
	to_crawl[0].push(base);
	  Visit[base] = true;
	  Octahedron s(base);
	  s.print(0);
	  Numdis[0]++;
}
void SOLUTION(){
  while(sum && count < 15){
    count++;
    cout << "sum : " << sum << " count : " << count << "\n";
    for(int i=0; i<81; i++){
      while(!to_crawl[i].empty()){
        int64_t t = to_crawl[i].front(); to_crawl[i].pop();
        Octahedron a(t);
        sum--;
        for(int j=0; j<4; j++){
          int k1 = trinaryshift(i,j);
          int k2 = trinaryshift(k1,j);
          a.oneFaceTurn(legal[j]);
          if(!Visit[a.index()]){
            Next[k1].push(a.index());
            Visit[a.index()] = true;
            a.print(count + 1 + Nonzero3(k1) * 8);
            Numdis[count + 1 + Nonzero3(k1) * 8]++;
            if(count + 1 + Nonzero3(k1) * 8 > maxd){
              maxd = count + 1 + Nonzero3(k1) * 8;
            }
          }

          a.oneFaceTurn(legal[j]);
          if(!Visit[a.index()]){
            Next[k2].push(a.index());
            Visit[a.index()] = true;
            a.print(count + 1 + Nonzero3(k2) * 8);
            Numdis[count + 1 + Nonzero3(k2) * 8]++;
            if(count + 1 + Nonzero3(k2) * 8 > maxd){
              maxd = count + 1 + Nonzero3(k2) * 8;
            }
          }
          a.oneFaceTurn(legal[j]);
        }
      }
    }
    for(int i=0; i<81; i++){
      while(!Next[i].empty()){
        to_crawl[i].push(Next[i].front()); Next[i].pop();
      }
    }
    cout << "sum : " << sum << " count : " << count << " to_sum : " << to_sum() << "\n";
  }
}
void Result(){
  cout << "finish" << endl;
  if(Empty()){
    cout << "다 탐색 함" << endl;
  }
  else{
    cout << "다 탐색 못함 병신, count를 늘려라" << endl;
  }
  cout << "최종 : sum : " << sum << " count : " << count << " maxd : " << maxd << "\n";
  for(int i=0; i<= maxd; i++){
    cout << "dis가 " << i << "인 개수 : " << Numdis[i] << "\n";
  }
}
void Checking(){
  bool V[369600] = {};
  int sumfind = 369600;
  queue<int64_t> to_find,next_find;

  to_find.push(base);
  V[base] = true;
  while(!to_find.empty()){
    count++;
    cout << "sumfind : " << sumfind << " count : " << count << "\n";
    while(!to_find.empty()){
      int64_t t = to_find.front(); to_find.pop();
      Octahedron a(t);
      sumfind--;
      for(int j=0; j<4; j++){
        int64_t index = a.index();

        a.oneFaceTurn(legal[j]);
        index = a.index();
        if(!V[index % 369600]){
          V[index % 369600] = true;
          next_find.push(a.index());
        }

        a.oneFaceTurn(legal[j]);
        index = a.index();
        if(!V[index % 369600]){
          V[index % 369600] = true;
          next_find.push(a.index());
        }

        a.oneFaceTurn(legal[j]);
      }
    }
    while(!next_find.empty()){
      to_find.push(next_find.front()); next_find.pop();
    }
    cout << "sumfind : " << sumfind << " count : " << count << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }
}
int main(int argc, char* a0rgv[]) {
	for(int i=0; i<100; i++){
		facecorner_dis_txt[i].open("facecorner_" + to_string(i) + ".txt");
  		face_dis_txt[i].open("face_" + to_string(i) + ".txt");	
	}
	/*Init();
	SOLUTION();
	Result();*/
	Checking();
	for(int i=0; i<100; i++){
		facecorner_dis_txt[i].close();
		face_dis_txt[i].close();	
	}
}

int pow3[5] = {1,3,9,27,81};

int trinaryshift(int i, int j){
  int k = (i/pow3[j])%3;
  int l = (k+1)%3;
  return i+(l-k)*pow3[j];
}


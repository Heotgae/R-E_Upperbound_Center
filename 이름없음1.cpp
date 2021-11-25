// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm
// Octahedron Solving Algorithm

#include <cassert>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

ifstream EdgeSolInv,VertexSolInv,CenterSolInv;




const int K = 0;
const int B = 1;
const int G = 2;
const int C = 3;
const int R = 4;
const int M = 5;
const int Y = 6;
const int W = 7;
const string Color[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};
const string Color2 = "KBGCRMYWkbgcrmyw";
// uppercase: counterclockwise; lowercase: clockwise
const int evcper[8][15] = {{0,1,2,0,1,2,0,2,1,3,7,12,4,6,13},{0,4,3,0,2,3,3,4,5,0,15,10,1,16,9},{1,5,6,0,4,1,6,8,7,0,11,18,2,9,19},{3,7,5,0,3,4,9,10,11,3,21,8,5,22,6},{2,9,8,1,5,2,12,13,14,1,18,17,2,20,15},{4,8,10,2,5,3,15,17,16,4,14,21,5,12,23},{6,11,9,1,4,5,18,19,20,7,22,14,8,23,13},{7,10,11,3,5,4,21,23,22,10,17,19,11,16,20}};
/*Permutation of [i] of pieces in this info
    first 3 elements: permutation of edges
    second 3 elements: permutation of vertices
    last [3]x[3] elements: 3 3-cycles of center pieces*/
const int vrot[8][3] = {{0,0,0},{2,1,1},{1,1,2},{1,2,1},{1,1,2},{1,2,1},{1,2,1},{0,0,0}};
int legal[4] = {0,3,5,6};
int changingface[4] = {1,2,4,7};
 
const int vertex_facet[6][4] = {{4,9+8,27+4,18+8},{8,18+4,54+8,36+4},{0,36,45,9},{63+4,27+8,9+4,45+8},{63,54,18,27},{63+8,45+4,36+8,54+4}};
const int edge_facet[12][2] = {{1,9+3},{6,18+6},{3,36+1},{27+6,9+6},{45+3,9+1},{27+1,18+3},{54+3,18+1},{27+3,63+1},{45+1,36+3},{54+6,36+6},{45+6,63+6},{54+1,63+3}};
const int center_facet[24] = {0*9+5,0*9+2,0*9+7,1*9+7,1*9+2,1*9+5,2*9+7,2*9+5,2*9+2,3*9+5,3*9+7,3*9+2,4*9+2,4*9+5,4*9+7,5*9+2,5*9+7,5*9+5,6*9+7,6*9+2,6*9+5,7*9+5,7*9+2,7*9+7};
//use octal
const short initedges [12] = {01,02,04,031,051,032,062,037,054,064,057,067};
const short initvertices [6] = {0132,0264,0451,07315,07623,07546};//starts from 0 or 7 originally. Rotates as cube rotates, 0 and 7 positions as first digit.
const short initcenters [24] = {03,05,06,012,014,017,021,024,027,030,035,036,041,042,047,050,053,056,060,063,065,071,072,074};//Facets on <first digit> towards direction of <second digit>
pair<int,int> a[72] = {{2,0},{0,0},{1,-1},{2,0},{0,0},{0,-1},{1,0},{2,-1},{1,0},{2,3},{4,1},{4,-1},{0,1},{3,2},{5,-1},{3,1},{3,-1},{0,1},{4,2},{6,1},{8,-1},{5,1},{1,1},{7,-1},{1,1},{6,-1},{0,3},{4,3},{5,0},{11,-1},{7,0},{0,2},{9,-1},{3,0},{10,-1},{3,1},{2,1},{2,1},{12,-1},{8,1},{1,3},{13,-1},{9,1},{14,-1},{5,2},{2,2},{8,0},{15,-1},{4,0},{5,1},{17,-1},{10,0},{16,-1},{3,3},{4,1},{11,0},{19,-1},{6,0},{5,3},{20,-1},{9,0},{18,-1},{1,2},{4,0},{7,1},{22,-1},{11,1},{3,0},{21,-1},{10,1},{23,-1},{5,0}};
const short symmetries[12][8] {{0,1,2,3,4,5,6,7},{0,2,4,6,1,3,5,7},{0,4,1,5,2,6,3,7},{5,7,1,3,4,6,0,2},{6,2,7,3,4,0,5,1},{3,1,7,5,2,0,6,4},{5,1,4,0,7,3,6,2},{6,4,2,0,7,5,3,1},{3,7,2,6,1,5,0,4},{3,2,1,0,7,6,5,4},{5,4,7,6,1,0,3,2},{6,7,4,5,2,3,0,1}};
const short Edgesymmetries[12][12] = {
{0,1,2,3,4,5,6,7,8,9,10,11},
{1,2,0,6,5,9,8,11,3,4,7,10},
{2,0,1,8,9,4,3,10,6,5,11,7},
{10,4,8,7,11,3,0,5,9,2,6,1},
{7,11,9,6,1,8,10,3,2,9,0,4},
{3,7,5,4,0,10,11,8,1,6,2,9},
{4,8,10,0,3,2,9,1,7,11,5,6},
{9,6,11,2,8,1,5,0,10,7,4,3},
{7,5,3,11,10,6,1,9,4,0,8,2},
{5,3,7,1,6,0,4,2,11,10,9,8},
{8,10,4,9,2,11,7,6,0,3,1,5},
{11,9,6,10,7,8,2,4,5,1,3,0}
};
const short VertexPersymmetries[12][6] = {
{0,1,2,3,4,5},
{1,2,0,4,5,3},
{2,0,1,5,3,4},
{3,2,5,4,0,1},
{4,5,1,0,3,2},
{3,4,0,2,5,1},
{2,5,3,0,1,4},
{1,4,5,2,0,3},
{4,0,3,5,1,2},
{0,3,4,1,2,5},
{5,3,2,1,4,0},
{5,1,2,3,4,0}
};
const short VertexOrisymmetries[12][6] = {
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{1,2,3,2,1,3},
{3,1,2,3,2,1},
{3,1,2,3,2,1},
{2,3,1,1,3,2},
{2,3,1,1,3,2},
{1,2,3,2,1,3},
{2,3,1,1,3,2},
{1,2,3,2,1,3},
{3,1,2,3,2,1}
};
const int syminv[12] = {0,2,1,4,3,6,5,8,7,9,10,11};
int pow6[8] = {1,6,36,216,1296,7776,46656,279936};
int Fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
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
1,12,66,220,495,792,924,792,495,220,56,13,1}; // CC[a][b] aCb
short For7[220][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,1,9},{0,1,10},{0,1,11},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,2,9},{0,2,10},{0,2,11},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,3,9},{0,3,10},{0,3,11},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,4,9},{0,4,10},{0,4,11},{0,5,6},{0,5,7},{0,5,8},{0,5,9},{0,5,10},{0,5,11},{0,6,7},{0,6,8},{0,6,9},{0,6,10},{0,6,11},{0,7,8},{0,7,9},{0,7,10},{0,7,11},{0,8,9},{0,8,10},{0,8,11},{0,9,10},{0,9,11},{0,10,11},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,2,9},{1,2,10},{1,2,11},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,3,9},{1,3,10},{1,3,11},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,4,9},{1,4,10},{1,4,11},{1,5,6},{1,5,7},{1,5,8},{1,5,9},{1,5,10},{1,5,11},{1,6,7},{1,6,8},{1,6,9},{1,6,10},{1,6,11},{1,7,8},{1,7,9},{1,7,10},{1,7,11},{1,8,9},{1,8,10},{1,8,11},{1,9,10},{1,9,11},{1,10,11},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,3,9},{2,3,10},{2,3,11},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,4,9},{2,4,10},{2,4,11},{2,5,6},{2,5,7},{2,5,8},{2,5,9},{2,5,10},{2,5,11},{2,6,7},{2,6,8},{2,6,9},{2,6,10},{2,6,11},{2,7,8},{2,7,9},{2,7,10},{2,7,11},{2,8,9},{2,8,10},{2,8,11},{2,9,10},{2,9,11},{2,10,11},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,4,9},{3,4,10},{3,4,11},{3,5,6},{3,5,7},{3,5,8},{3,5,9},{3,5,10},{3,5,11},{3,6,7},{3,6,8},{3,6,9},{3,6,10},{3,6,11},{3,7,8},{3,7,9},{3,7,10},{3,7,11},{3,8,9},{3,8,10},{3,8,11},{3,9,10},{3,9,11},{3,10,11},{4,5,6},{4,5,7},{4,5,8},{4,5,9},{4,5,10},{4,5,11},{4,6,7},{4,6,8},{4,6,9},{4,6,10},{4,6,11},{4,7,8},{4,7,9},{4,7,10},{4,7,11},{4,8,9},{4,8,10},{4,8,11},{4,9,10},{4,9,11},{4,10,11},{5,6,7},{5,6,8},{5,6,9},{5,6,10},{5,6,11},{5,7,8},{5,7,9},{5,7,10},{5,7,11},{5,8,9},{5,8,10},{5,8,11},{5,9,10},{5,9,11},{5,10,11},{6,7,8},{6,7,9},{6,7,10},{6,7,11},{6,8,9},{6,8,10},{6,8,11},{6,9,10},{6,9,11},{6,10,11},{7,8,9},{7,8,10},{7,8,11},{7,9,10},{7,9,11},{7,10,11},{8,9,10},{8,9,11},{8,10,11},{9,10,11}};
short For4[84][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,5,6},{0,5,7},{0,5,8},{0,6,7},{0,6,8},{0,7,8},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,5,6},{1,5,7},{1,5,8},{1,6,7},{1,6,8},{1,7,8},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,5,6},{2,5,7},{2,5,8},{2,6,7},{2,6,8},{2,7,8},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,5,6},{3,5,7},{3,5,8},{3,6,7},{3,6,8},{3,7,8},{4,5,6},{4,5,7},{4,5,8},{4,6,7},{4,6,8},{4,7,8},{5,6,7},{5,6,8},{5,7,8},{6,7,8}};
short For2[20][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,2,3},{0,2,4},{0,2,5},{0,3,4},{0,3,5},{0,4,5},{1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},{2,3,4},{2,3,5},{2,4,5},{3,4,5}};
short For1[1][3] = {{0,1,2}};

short Rot[16][3] = {{2,1,0},{3,4,0},{6,5,1},{5,7,3},{8,9,2},{10,8,4},{9,11,6},{11,10,7},{0,1,2},{0,4,3},{1,5,6},{3,7,5},{2,9,8},{4,8,10},{6,11,9},{7,10,11}};

int per_rot[16][3] = {{2,1,0},{3,2,0},{1,4,0},{4,3,0},{2,5,1},{3,5,2},{5,4,1},{4,5,3},{0,1,2},{0,2,3},{0,4,1},{0,3,4},{1,5,2},{2,5,3},{1,4,5},{3,5,4}};
int ori_rot[16][3] = {{0,0,0},{1,1,2},{2,1,1},{1,2,1},{2,1,1},{1,2,1},{1,2,1},{0,0,0},{0,0,0},{3,2,3},{2,3,3},{3,3,2},{2,3,3},{3,3,2},{3,3,2},{0,0,0}};

class Octahedron {
  private:
//KBGCRMYW
    void oneFaceTurn(int facetoturn){
      if(facetoturn < 8){
        short a = edges[evcper[facetoturn][2]];
        edges[evcper[facetoturn][2]] = edges[evcper[facetoturn][1]];
        edges[evcper[facetoturn][1]] = edges[evcper[facetoturn][0]];
        edges[evcper[facetoturn][0]] = a;
        a = vertex_rotate(vertices[evcper[facetoturn][5]],vrot[facetoturn][2]);
        vertices[evcper[facetoturn][5]] = vertex_rotate(vertices[evcper[facetoturn][4]],vrot[facetoturn][1]);
        vertices[evcper[facetoturn][4]] = vertex_rotate(vertices[evcper[facetoturn][3]],vrot[facetoturn][0]);
        vertices[evcper[facetoturn][3]] = a;
        for(int i = 2; i<5; i++){
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
        a = vertex_rotate(vertices[evcper[facetoturn][3]],4-vrot[facetoturn][2]);
        vertices[evcper[facetoturn][3]] = vertex_rotate(vertices[evcper[facetoturn][4]],4-vrot[facetoturn][0]);
        vertices[evcper[facetoturn][4]] = vertex_rotate(vertices[evcper[facetoturn][5]],4-vrot[facetoturn][1]);
        vertices[evcper[facetoturn][5]] = a;
        for(int i = 2; i<5; i++){
          a = centers[evcper[facetoturn][i*3]];
          centers[evcper[facetoturn][i*3]] = centers[evcper[facetoturn][i*3+1]];
          centers[evcper[facetoturn][i*3+1]] = centers[evcper[facetoturn][i*3+2]];
          centers[evcper[facetoturn][i*3+2]] = a;
        }
        facetoturn += 8;
      }

      //edge index용
      int t;
      t =Edge[Rot[facetoturn][0]];
      Edge[Rot[facetoturn][0]] = Edge[Rot[facetoturn][1]];
      Edge[Rot[facetoturn][1]] = Edge[Rot[facetoturn][2]];
      Edge[Rot[facetoturn][2]] = t;
      //vertex index용
      int p0 = per_ver[per_rot[facetoturn][0]];
      int o0 = ori_ver[per_rot[facetoturn][0]];
      per_ver[per_rot[facetoturn][0]] = per_ver[per_rot[facetoturn][1]];
      ori_ver[per_rot[facetoturn][0]] = (ori_ver[per_rot[facetoturn][1]] + ori_rot[facetoturn][1])%4;
      per_ver[per_rot[facetoturn][1]] = per_ver[per_rot[facetoturn][2]];
      ori_ver[per_rot[facetoturn][1]] = (ori_ver[per_rot[facetoturn][2]] + ori_rot[facetoturn][2])%4;
      per_ver[per_rot[facetoturn][2]] = p0;
      ori_ver[per_rot[facetoturn][2]] = (o0 + ori_rot[facetoturn][0])%4;
    }
    
    int octpow(int n){
      return 1 << (3*n);
    }

    short vertex_rotate(short ver, int rot){ // turn vertex rot times
      if(rot%4==0){
        return ver;
      }
      int i = octpow(4-rot);
      return (ver%i)*octpow(rot)+ver/i;
    }
    int GetEdge(int index){
      return Edge[index];
    }
    //
    
    short edges [12];
    short vertices [6];//contains orientation info
    short centers [24]; //centers only have color info, not original orientation. ex) {0,0,0,1,1,1,...}
    int Edge[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int per_ver[6] = {0,1,2,3,4,5};
    int ori_ver[6] = {0,0,0,0,0,0};
    
  public:
    short facets[8][9];
    Octahedron(){
      for(int i=0; i<12; i++){
        edges[i] = initedges[i];
      }
      for(int i=0; i<6; i++){
        vertices[i] = initvertices[i];
      }
      for(int i=0; i<8; i++){
        for(int j=0; j<3; j++){
          centers[3*i + j] = i;
        }
      }
        
    }
    
    void Turn(string s){
      for(int i=0; i<s.length(); i++){
        for(int j=0; j<16; j++){
          if(Color2[j] == s[i]){
            oneFaceTurn(j);
            break;
          }
        }
      }
    }
    
    void print_cube(int form = 0){
      Updatefacets();
      if(form == 0){
        for(int face = 0; face < 8; face++){
          print_onefacecube(face);
        }
      }
      else if(form == 1) {
        string s[4] = {"","","",""};
        for(int i=0; i<8; i++){
          s[0] += Color[i] + ":    ";
          s[1] += "  " + Color[facets[i][0]] + "   ";
          s[2] += " ";
          for(int j=1; j<4; j++){
            s[2] += Color[facets[i][j]];
          }
          s[2] += "  ";
          for(int j=4; j<9; j++){
            s[3] += Color[facets[i][j]];
          }
          s[3] += " ";
        }
        for(int i=0; i<4; i++){
          cout << s[i] << "\n";
        }
        printf("Edge : ");
        for(int i=0; i<12; i++){
          printf("%d ",Edge[i]);
        }
        printf("\n");
        printf("Per_Ver : ");
        for(int i=0; i<6; i++){
          printf("%d ",per_ver[i]);
        }
        printf("\n");
        printf("Ori_Ver : ");
        for(int i=0; i<6; i++){
          printf("%d ",ori_ver[i]);
        }
        printf("\n");
      }
    }
    void print_onefacecube(int face){
      cout << Color[face] << ":   \n";
      cout << "  " + Color[facets[face][0]] << "\n";
      string a = " ";
      for(int i=1; i<4; i++){
        a += Color[facets[face][i]];
      }
      cout << a << "\n";
      a = "";
      for(int i=4; i<9; i++){
        a += Color[facets[face][i]];
      }
      cout << a << "\n";
    }
       
    const int vertex_facet[6][4] = {{4,9+8,27+4,18+8},{8,18+4,54+8,36+4},{0,36,45,9},{63+4,27+8,9+4,45+8},{63,54,18,27},{63+8,45+4,36+8,54+4}};
    const int edge_facet[12][2] = {{1,9+3},{6,18+6},{3,36+1},{27+6,9+6},{45+3,9+1},{27+1,18+3},{54+3,18+1},{27+3,63+1},{45+1,36+3},{54+6,36+6},{45+6,63+6},{54+1,63+3}};
    const int center_facet[24] = {0*9+5,0*9+2,0*9+7,1*9+7,1*9+2,1*9+5,2*9+7,2*9+5,2*9+2,3*9+5,3*9+7,3*9+2,4*9+2,4*9+5,4*9+7,5*9+2,5*9+7,5*9+5,6*9+7,6*9+2,6*9+5,7*9+5,7*9+2,7*9+7};
    void pemv(int index){ // turn vertex of 0th face counterclockwise 2pi/3 index times
      while(index--){
        short t = vertices[0];
        vertices[0] = vertices[2];
        vertices[2] = vertices[1];
        vertices[1] = t;
      }
    }
    void oriv(int rot1,int rot2,int rot3){ // turn each vertex counterclockwise
      vertices[0] = vertex_rotate(vertices[0],rot1);
      vertices[2] = vertex_rotate(vertices[2],rot2);
      vertices[1] = vertex_rotate(vertices[1],rot3);
    }
    void pemc(int s){
      centers[3] = (s % 10);
      centers[4] = ((s/10) % 10);
      centers[12] = ((s/100) % 10);
      centers[13] = ((s/1000) % 10);
      centers[7] = ((s/10000) % 10);
      centers[6] = ((s/100000) % 10);
    }
    string LL[16] = {"K","B","G","C","R","M","Y","W","k","b","g","c","r","m","y","w"};
    string halfsolution(int depth){
      if(depth == 0){
        if(isSolved()){
          return "";
        }
        return "-1";
      }
      for(int fi = 0; fi < 5; fi++){
        oneFaceTurn(fi);
        string s = halfsolution(depth-1);
        if(s != "-1"){
          return LL[fi] + s;
        }
        oneFaceTurn(fi + 8);
      }
      return "-1";
    }
    int isedgevertexcenter(int location){
      int index = location % 9;
      if(index == 0 or index == 4 or index == 8){
        return 0;//vertex
      }
      if(index == 1 or index == 3 or index == 6){
        return 1;//edge
      }
      return 2;//face
    }

    void Updatefacets(){
      int i,j;
      for(i=0; i<6; i++){ // vertex
        for(j=0; j<4; j++){
          facets[vertex_facet[i][j] / 9][vertex_facet[i][j] % 9] = vertices[i] * (1 << (3 * j)) / (1<<9) % 8;
        }
      }
      for(i=0; i<12; i++){ // edge
        for(j=0; j<2; j++){
          facets[edge_facet[i][j] / 9][edge_facet[i][j] % 9] = edges[i] * (1 << (3 * j)) / (1<<3) % 8;
        }
      }
      for(i=0; i<24; i++){ // center
        facets[center_facet[i] / 9][center_facet[i] % 9] = centers[i];
      }
    }

    bool closeto0(int i, int j){
      int closeto0[18][2] = {{1,0},{1,2},{1,3},{1,7},{1,8},{2,4},{2,5},{2,6},{2,7},{2,8},{3,4},{4,0},{4,1},{4,2},{4,4},{4,5},{5,0},{6,8}};
      for(int n=0; n<18; n++){
        if(closeto0[n][0]==i && closeto0[n][1]==j){
          return true;
        }
      }
      return false;
    }

    
    
    string facetcolor(int index1,int index2){
      return Color[facets[index1][index2]];
    }
    
    bool isEdgeOrdered(){
      for(int i=0; i<12; i++){
        if(edges[i]!=initedges[i]){
          return false;
        }
      }
      return true;
    }
    bool isVertexOrdered(){
      for(int i=0; i<6; i++){
        if(vertices[i]!=initvertices[i]){
          return false;
        }
      }
      return true;
    }
    bool isCenterOrdered(){
      for(int i=0; i<24; i++){
        if(centers[i]!=initcenters[i]/8){
          return false;
        }
      }
      return true;
    }
    int OrderdState(){
      int count = 0;
      if( isEdgeOrdered() ){
        count += 1;
      }
      if( isVertexOrdered() ){
        count += 2;
      }
      if( isCenterOrdered() ){
        count += 4;
      }
      return count;
    }
    bool isSolved(){
      return isEdgeOrdered() && isVertexOrdered() && isCenterOrdered();
    }
    bool isTwoThirdsSolved(){
      Updatefacets();
      for(int i=1;i<8;i++){
        for(int j=1;j<9;j++){
          if(facets[i][j]!=facets[i][0]){
            if(!closeto0(i,j)){
              return false;
            }
          }
        }
      }
      return true;
    }
    
    bool is0[8] = {true,false,false,true,false,true,true,false};
    bool Is3056Ordered(){
      for(int i=0; i<8; i++){
         if(is0[i]){
            for(int j=0; j<3; j++){
               if(centers[3*i + j] != initcenters[3*i + j] / 8){
                  return false;
               }
            }
         }
      }
      return true;
   }
    bool Is1247Ordered(){
       for(int i=0; i<8; i++){
         if(!is0[i]){
            for(int j=0; j<3; j++){
               if(centers[3*i + j] != initcenters[3*i + j] / 8){
                  return false;
               }
            }
         }
      }
      return true;
   }
    
    int f(int a,int b,int c,int l){
      //cout << a << " " << b << " " << c << " " << endl;
      return (CC[l][3] - CC[l-a][3] + CC[l-a-1][2] - CC[l-b][2] + CC[l-b-1][1] - CC[l-c][1]);
    }
    int EdgeIndex(){
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
        sum += count * Fact[11-i];
      }
      return sum;
    }
    int VertexIndex(){
      int sum = 0;
      bool visit[6] = {};
      for(int i=0; i<6; i++){
        int count = 0;
        for(int j=0; j<per_ver[i]; j++){
          if(!visit[j]){
            count++;
          }
        }
        sum += count * Fact[5-i];
        visit[per_ver[i]] = 1;
      }
      sum *= 1 << (2 * 6);
      for(int i=0; i<6; i++){
        sum += ori_ver[i] * (1 << (2 * (5-i)));
      }
      return sum;
    }
    int Face1247[4] = {2,1,4,7};
    int Face3056[4] = {1,2,4,7};
    int conv1247to0356[24] = {6,7,8,0,2,1,9,11,10,3,4,5,18,19,20,13,12,14,22,21,23,15,16,17}; // 시계 방향 회전
    int Center3056Index(){
        int index1 = 0;
        int relloc[4][4] = {};
        int numin[4] = {};
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
            int num = centers[conv1247to0356[3*Face3056[i]+j]]/2;
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
        return index1;
    }
    int Center1247Index(){
        int index1 = 0;
        int relloc[4][4] = {};
        int numin[4] = {};
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
            int num = centers[3*Face1247[i]+j]/2;
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
        return index1;
    }

    bool Islegal(){
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                if(centers[3*legal[i] + j] != legal[i]){
                    return false;
                }
            }
        }
        return true;
    }
    int Symindex[12] = {0,2,1,6,10,4,3,7,9,5,8,11};
    int symmetry(){ // latex에 있는 것중 몇번째 Symmetry 형태인지 확인
      for(int i=0; i<12; i++){
        if(Symindex[i] == GetEdge(0)){
          return i;
        }
      }
      return -1;
    }
    void sym(int s){ // s 번째 symmetry로 바꿈
      //turns THIS octahedron into a symmetric octahedron of #s
      if(s==0){
        return;
      }
      int newedges[12],newvertices[6],newcenters[24] = {};
      int newEdge[12],newper_ver[6],newori_ver[6];
      for(int i=0; i<24; i++){
        newcenters[i]=symmetries[s][centers[i]];
      }
      
      for(int i=0; i<6; i++){
        short t= (symmetries[s][vertices[i]>>9]<<9)|(symmetries[s][(vertices[i]>>6)%8]<<6)|(symmetries[s][(vertices[i]>>3)%8]<<3)|(symmetries[s][vertices[i]%8]);
        newvertices[i]=t;
        newper_ver[VertexPersymmetries[s][i]] = per_ver[i];
        newori_ver[VertexPersymmetries[s][i]] = (ori_ver[i] + VertexOrisymmetries[s][i]) % 4;
        
      }
      for(int i=0; i<12; i++){
        short t= (symmetries[s][edges[i]>>3]<<3)|(symmetries[s][edges[i]%8]);
        newedges[i]=t;
        newEdge[Edgesymmetries[s][Edge[i]]] = i;
      }
      for(int i=0; i<24; i++){
        centers[i] = newcenters[i];
      }
      for(int i=0; i<6; i++){
        vertices[i] = newvertices[i];
        per_ver[i] = newper_ver[i];
        ori_ver[i] = newori_ver[i];
      }
      for(int i=0; i<12; i++){
        edges[i] = newedges[i];
        Edge[i] = newEdge[i];
      }
    }
    void invsym(int s){ // s번째 symmetry를 원래대로 돌림
      sym(syminv[s]);
    }
};
int Symmetry = 0;
string inverse(string s){
   string news = "";
   for(int i = s.size()-1; i>=0 ; i--){
      for(int j=0; j<16; j++){
         if(Color2[j] == s[i]){
            news += Color2[(j+8)%16];
         }
      }
   }
   return news;
}
string reverse(string s){
  string news = "";
  for(int i=s.size()-1; i>=0; i--){
    news += s[i];
  }
  return news;
}
string inversesym(string s,int symmetry){
  string news;
  for(int i = 0; i<s.size(); i++){
    for(int j=0; j<16; j++){
      if(Color2[j] == s[i]){
        news += Color2[symmetries[syminv[symmetry]][j]];
      }
    }
  }
  return news;
}
int Conv[8] = {2,0,3,1,6,4,7,5};
string Con1247to3056(string s){ // 2147면과 3056면을 바꾸는 것
//전체 큐브를 반시계 방향으로 돌렸을때 1247의 index를 기준으로 0356면을 바꾸는 sequence를 찾는거임
  string news = "";
  for(int i=0; i<s.length(); i++){
    for(int j=0; j<16; j++){
      if(s[i] == Color2[j]){
        news += Color2[Conv[j%8] + (j/8) * 8];
      }
    }
  }
  return news;
}

Octahedron Oct;
string EdgeSol(){
  int EdgeIndex = Oct.EdgeIndex();
  string s,Sol = "";
  cout << EdgeIndex << endl;
  while(!EdgeSolInv.eof()){
    getline(EdgeSolInv,s);
    int n = s.length();
    int colonindex = 0;
    for(int i=0; i<n; i++){
      if(s[i] == ':'){
        colonindex = i;
      }
    }
    string num = "";
    for(int i=0; i<colonindex-1; i++){
      num += s[i];
    }
    if(stoi(num) != EdgeIndex){
      continue;
    }
    cout << "Find it!!!!" << endl;
    for(int i=colonindex + 1; i<n; i++){
      Sol += s[i];
    }
    cout << "before split " << s << endl;
    cout << "colonindex : " << colonindex << endl;
    break;
  }
  cout << "before inverse : " << Sol << endl;
  Sol = inverse(Sol);
  Oct.Turn(Sol);
  cout << "EdgeSol : " << Sol << endl;
  cout << "Symmetry : " << Symmetry << endl;
  Oct.print_cube(0);
  return Sol;
}
string VertexSol(){
  int VertexIndex = Oct.VertexIndex();
  string s,Sol = "";
  cout << VertexIndex << endl;
  while(!VertexSolInv.eof()){
    getline(VertexSolInv,s);
    int n = s.length();
    int colonindex = 0;
    for(int i=0; i<n; i++){
      if(s[i] == ':'){
        colonindex = i;
      }
    }
    string num = "";
    for(int i=0; i<colonindex-1; i++){
      num += s[i];
    }
    if(stoi(num) != VertexIndex){
      continue;
    }
    cout << "Find it!!!!" << endl;
    for(int i=colonindex+1; i<n; i++){
      Sol += s[i];
    }
    cout << "before split " << s << endl;
    cout << "colonindex : " << colonindex << endl;
    break;
  }
  Sol = inverse(Sol);
  Oct.Turn(Sol);
  //Sol = inversesym(Sol,Symmetry);
  cout << "VertexSol : " << Sol << endl;
  Oct.print_cube(0);
  return Sol;
}
string CenterSol(){
  int Center3056Index = Oct.Center3056Index();
  int Center1247Index = Oct.Center1247Index();
  cout << Center3056Index << " " << Center1247Index << endl;
  string s,Sol1 = "",Sol2 = "",Sol="";
  int index = 0;
  while(!CenterSolInv.eof() && (Sol1 == "" || Sol2 == "")){
    getline(CenterSolInv,s);
    if(index == Center3056Index){
      cout << "Find it!!!!" << endl;
      Sol1 = s;
    }
    if(index == Center1247Index){
      cout << "Find it!!!!" << endl;
      Sol2 = s;
    }
    index += 1;
  }
  Sol1 = Con1247to3056(inverse(Sol1));
  Sol2 = inverse(Sol2); 
  cout << "Sol1 : " << Sol1 << endl;
  Oct.Turn(Sol1);
  Oct.print_cube(0);
  cout << "Sol2 : " << Sol2 << endl;
  Oct.Turn(Sol2);
  Oct.print_cube(0);
  Sol += Sol1 + Sol2;
  cout << "CenterSol : " << Sol << endl;
  return Sol;
}






string Number[21] =  {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};



void Init(){ 
   EdgeSolInv.open("EdgeSolInv.txt");
   VertexSolInv.open("VertexSolInv.txt");
   CenterSolInv.open("CenterSolInv.txt");
}
void Solution(){
  string Sol = EdgeSol();
  Sol += VertexSol();
  Sol += CenterSol();
  cout << "Sol : " << Sol << endl;
}
void Finish(){
  printf("Symmetry : %d\n",Symmetry);
  EdgeSolInv.close();
  if(Oct.isEdgeOrdered()){
    cout << "Edge Ordered" << endl;
  }
  else{
    cout << "Edge Unordered" << endl;
  }
  VertexSolInv.close();
  if(Oct.isVertexOrdered()){
    cout << "Vertex Ordered" << endl;
  }
  else{
    cout << "Vertex Unordered" << endl;
  }
  CenterSolInv.close();
  if(Oct.isCenterOrdered()){
    cout << "Center Ordered" << endl;
  }
  else{
    cout << "Center Unordered" << endl;
  }
}
void Algorithm(){
  string s = "GBcrMKwrrrBG";
   Oct.Turn(s);
   Init();
   cout << Oct.EdgeIndex() << endl;
   Oct.print_cube(1);
   cout << "Init finish" << endl;
   Solution();
   cout << "Solution finish" << endl;
   Finish();
   cout << "Finish" << endl;
}
int main(){
   Algorithm();
}

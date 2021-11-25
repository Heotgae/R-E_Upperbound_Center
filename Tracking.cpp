#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

ifstream Face0356[19];




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
const short symmetries[12][8] {{0,1,2,3,4,5,6,7},{0,2,4,6,1,3,5,7},{0,4,1,5,2,6,3,7},{5,1,4,0,7,3,6,2},{3,1,7,5,2,0,6,4},{3,7,2,6,1,5,0,4},{6,4,2,0,7,5,3,1},{5,7,1,3,4,6,0,2},{6,2,7,3,4,0,5,1},{3,2,1,0,7,6,5,4},{5,4,7,6,1,0,3,2},{6,7,4,5,2,3,0,1}};
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
1,12,66,220,495,792,924,792,495,220,56,13,1}; // CC[a][b] aCb 리턴
short For7[220][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,1,9},{0,1,10},{0,1,11},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,2,9},{0,2,10},{0,2,11},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,3,9},{0,3,10},{0,3,11},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,4,9},{0,4,10},{0,4,11},{0,5,6},{0,5,7},{0,5,8},{0,5,9},{0,5,10},{0,5,11},{0,6,7},{0,6,8},{0,6,9},{0,6,10},{0,6,11},{0,7,8},{0,7,9},{0,7,10},{0,7,11},{0,8,9},{0,8,10},{0,8,11},{0,9,10},{0,9,11},{0,10,11},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,2,9},{1,2,10},{1,2,11},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,3,9},{1,3,10},{1,3,11},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,4,9},{1,4,10},{1,4,11},{1,5,6},{1,5,7},{1,5,8},{1,5,9},{1,5,10},{1,5,11},{1,6,7},{1,6,8},{1,6,9},{1,6,10},{1,6,11},{1,7,8},{1,7,9},{1,7,10},{1,7,11},{1,8,9},{1,8,10},{1,8,11},{1,9,10},{1,9,11},{1,10,11},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,3,9},{2,3,10},{2,3,11},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,4,9},{2,4,10},{2,4,11},{2,5,6},{2,5,7},{2,5,8},{2,5,9},{2,5,10},{2,5,11},{2,6,7},{2,6,8},{2,6,9},{2,6,10},{2,6,11},{2,7,8},{2,7,9},{2,7,10},{2,7,11},{2,8,9},{2,8,10},{2,8,11},{2,9,10},{2,9,11},{2,10,11},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,4,9},{3,4,10},{3,4,11},{3,5,6},{3,5,7},{3,5,8},{3,5,9},{3,5,10},{3,5,11},{3,6,7},{3,6,8},{3,6,9},{3,6,10},{3,6,11},{3,7,8},{3,7,9},{3,7,10},{3,7,11},{3,8,9},{3,8,10},{3,8,11},{3,9,10},{3,9,11},{3,10,11},{4,5,6},{4,5,7},{4,5,8},{4,5,9},{4,5,10},{4,5,11},{4,6,7},{4,6,8},{4,6,9},{4,6,10},{4,6,11},{4,7,8},{4,7,9},{4,7,10},{4,7,11},{4,8,9},{4,8,10},{4,8,11},{4,9,10},{4,9,11},{4,10,11},{5,6,7},{5,6,8},{5,6,9},{5,6,10},{5,6,11},{5,7,8},{5,7,9},{5,7,10},{5,7,11},{5,8,9},{5,8,10},{5,8,11},{5,9,10},{5,9,11},{5,10,11},{6,7,8},{6,7,9},{6,7,10},{6,7,11},{6,8,9},{6,8,10},{6,8,11},{6,9,10},{6,9,11},{6,10,11},{7,8,9},{7,8,10},{7,8,11},{7,9,10},{7,9,11},{7,10,11},{8,9,10},{8,9,11},{8,10,11},{9,10,11}};
short For4[84][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,1,6},{0,1,7},{0,1,8},{0,2,3},{0,2,4},{0,2,5},{0,2,6},{0,2,7},{0,2,8},{0,3,4},{0,3,5},{0,3,6},{0,3,7},{0,3,8},{0,4,5},{0,4,6},{0,4,7},{0,4,8},{0,5,6},{0,5,7},{0,5,8},{0,6,7},{0,6,8},{0,7,8},{1,2,3},{1,2,4},{1,2,5},{1,2,6},{1,2,7},{1,2,8},{1,3,4},{1,3,5},{1,3,6},{1,3,7},{1,3,8},{1,4,5},{1,4,6},{1,4,7},{1,4,8},{1,5,6},{1,5,7},{1,5,8},{1,6,7},{1,6,8},{1,7,8},{2,3,4},{2,3,5},{2,3,6},{2,3,7},{2,3,8},{2,4,5},{2,4,6},{2,4,7},{2,4,8},{2,5,6},{2,5,7},{2,5,8},{2,6,7},{2,6,8},{2,7,8},{3,4,5},{3,4,6},{3,4,7},{3,4,8},{3,5,6},{3,5,7},{3,5,8},{3,6,7},{3,6,8},{3,7,8},{4,5,6},{4,5,7},{4,5,8},{4,6,7},{4,6,8},{4,7,8},{5,6,7},{5,6,8},{5,7,8},{6,7,8}};
short For2[20][3] = {{0,1,2},{0,1,3},{0,1,4},{0,1,5},{0,2,3},{0,2,4},{0,2,5},{0,3,4},{0,3,5},{0,4,5},{1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},{2,3,4},{2,3,5},{2,4,5},{3,4,5}};
short For1[1][3] = {{0,1,2}};
/*int64_t CC[25][25] = {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,3,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,4,9,14,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,5,14,28,42,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,6,20,48,90,132,132,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,7,27,75,165,297,429,429,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,8,35,110,275,572,1001,1430,1430,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,9,44,154,429,1001,2002,3432,4862,4862,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,10,54,208,637,1638,3640,7072,11934,16796,16796,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,11,65,273,910,2548,6188,13260,25194,41990,58786,58786,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,12,77,350,1260,3808,9996,23256,48450,90440,149226,208012,208012,0,0,0,0,0,0,0,0,0,0,0,0},{1,13,90,440,1700,5508,15504,38760,87210,177650,326876,534888,742900,742900,0,0,0,0,0,0,0,0,0,0,0},{1,14,104,544,2244,7752,23256,62016,149226,326876,653752,1188640,1931540,2674440,2674440,0,0,0,0,0,0,0,0,0,0},{1,15,119,663,2907,10659,33915,95931,245157,572033,1225785,2414425,4345965,7020405,9694845,9694845,0,0,0,0,0,0,0,0,0},{1,16,135,798,3705,14364,48279,144210,389367,961400,2187185,4601610,8947575,15967980,25662825,35357670,35357670,0,0,0,0,0,0,0,0},{1,17,152,950,4655,19019,67298,211508,600875,1562275,3749460,8351070,17298645,33266625,58929450,94287120,129644790,129644790,0,0,0,0,0,0,0},{1,18,170,1120,5775,24794,92092,303600,904475,2466750,6216210,14567280,31865925,65132550,124062000,218349120,347993910,477638700,477638700,0,0,0,0,0,0},{1,19,189,1309,7084,31878,123970,427570,1332045,3798795,10015005,24582285,56448210,121580760,245642760,463991880,811985790,1289624490,1767263190,1767263190,0,0,0,0,0},{1,20,209,1518,8602,40480,164450,592020,1924065,5722860,15737865,40320150,96768360,218349120,463991880,927983760,1739969550,3029594040,4796857230,6564120420,6564120420,0,0,0,0},{1,21,230,1748,10350,50830,215280,807300,2731365,8454225,24192090,64512240,161280600,379629720,843621600,1771605360,3511574910,6541168950,11338026180,17902146600,24466267020,24466267020,0,0,0},{1,22,252,2000,12350,63180,278460,1085760,3817125,12271350,36463440,100975680,262256280,641886000,1485507600,3257112960,6768687870,13309856820,24647883000,42550029600,67016296620,91482563640,91482563640,0,0},{1,23,275,2275,14625,77805,356265,1442025,5259150,17530500,53993940,154969620,417225900,1059111900,2544619500,5801732460,12570420330,25880277150,50528160150,93078189750,160094486370,251577050010,343059613650,343059613650,0},{1,24,299,2574,17199,95004,451269,1893294,7152444,24682944,78676884,233646504,650872404,1709984304,4254603804,10056336264,22626756594,48507033744,99035193894,192113383644,352207870014,603784920024,946844533674,1289904147324,1289904147324}};
int64_t Fact[25] = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000,int64_t(51090942171709440000),1124000727777607680000,25852016738884976640000,620448401733239439360000};*/
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
      }

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
    //
    
    short edges [12];
    short vertices [6];//contains orientation info
    short centers [24]; //centers only have color info, not original orientation. ex) {0,0,0,1,1,1,...}
    
  public:
    short facets[8][9];
    Octahedron(int index1){
      for(int i=0; i<12; i++){
        edges[i] = initedges[i];
      }
      for(int i=0; i<6; i++){
        vertices[i] = initvertices[i];
      }



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
          centers[3*legal[i] + j] = legal[i];
        }
      }
        
    }
    
    void Turn(string s){
      for(int i=0; i<s.length(); i++){
        for(int j=0; j<16; j++){
          if(Color[j][0] == s[i]){
            oneFaceTurn(j);
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
          s[1] += "  " + Color[facets[i][10]] + "   ";
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
    /*
    void Create2(){
      
      oneFaceTurn(0);
      Create(9,"K", 0);
      oneFaceTurn(8);
      oneFaceTurn(1);
      Create(9,"B", 1);  
      oneFaceTurn(9);
      oneFaceTurn(5);
      Create(9,"M", 5);
      oneFaceTurn(13);
      
    }
    */
    /*
    void Create(int depth,string s,int index){
      if(isTwoThirdsSolved()){
        if(isSolved()){
          //cout << s << " : solved" << endl;
          fputs(s.c_str(),pfile);
          fputs(" : solved\n",pfile);
        }
        else{
          fputs(s.c_str(),pfile);
          fputs("\n",pfile);
        }
      }
      if(depth == 0){
        return;
      }
      for(int fi = 0; fi < 16; fi ++){
        if((fi-index)%8 != 0){
          oneFaceTurn(fi);
          Create(depth-1,s + LL[fi],fi);
          oneFaceTurn((fi + 8)%16);
        }
      }
    }
    */
    int isedgevertexcenter(int location){
      int index = location % 9;
      if(index == 0 or index == 4 or index == 8){
        return 0;//corner
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
    bool isEdgeOrdered(){
      for(int i=0; i<12; i++){
        if(edges[i]!=initedges[i]){
          return false;
        }
      }
      return true;
    }
    bool isCornerOrdered(){
      for(int i=0; i<6; i++){
        if(vertices[i]!=initvertices[i]){
          return false;
        }
      }
      return true;
    }
    bool isFaceOrdered(){
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
      if( isCornerOrdered() ){
        count += 2;
      }
      if( isFaceOrdered() ){
        count += 4;
      }
      return count;
    }
    bool isSolved(){
      return isEdgeOrdered() && isCornerOrdered() && isFaceOrdered();
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

    bool closeto0(int i, int j){
      int closeto0[18][2] = {{1,0},{1,2},{1,3},{1,7},{1,8},{2,4},{2,5},{2,6},{2,7},{2,8},{3,4},{4,0},{4,1},{4,2},{4,4},{4,5},{5,0},{6,8}};
      for(int n=0; n<18; n++){
        if(closeto0[n][0]==i && closeto0[n][1]==j){
          return true;
        }
      }
      return false;
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
    
    
    string facetcolor(int index1,int index2){
      return Color[facets[index1][index2]];
    }

    
    bool is0[8] = {true,false,false,true,false,true,true,false};
    bool Is0356Ordered(){
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
    int Index1(){
        int index1 = 0;
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
    void print(){
      
      for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
          cout << centers[changingface[i]*3+j] << ", ";
        }
        
      }
      cout << endl;
      
      //////////////////////////
    }
};









string Number[21] =  {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};

const int statenum = 369600;
const int Impd = 1000; // 불가능한 거리로 초기화 
int maxd = Impd; // 최대 distance 저장 
const int base = 369599; // Solved 상태의 state임. 
int D[statenum]; // D[state] : state를 가진 Octahedron의 Distance저장
int numd[204] = {}; // numd[i] : distance가 i인 state의 개수 
bool V[statenum] = {}; // 각 상태를 방문했는지 체크 
vector<string> Seq; // length의 길이를 가진 sequnce를 중복없이 가짐. 
String Sol[statenum] = {};

//queue<int> to_crawl,Next; // 방문할때 유용한 queue 
queue<int> stated[Impd + 1]; // stated[i] : distance가 i인 state들 넣 
int count = 0; // while문을 얼마나 돌았는지 저장 
bool SeqV[statenum] = {}; // Sequnce의 result인 state를 앞에서 이미 나왔는지 확인 

string inverse(string s){
	
	string news;
	for(int i = s.size()-1; i>=0 ; i--){
		for(int j=0; j<16; j++){
			if(Color2[j] == s[i]){
				news += Color2[(j+8)%16];
			}
		}
	}
	return news;
}


void Init(){
	for(int i=0; i<19; i++){
		Face0356[i].open("Face0356_" + Number[i] + ".txt");
	}
	for(int i=0; i<statenum; i++){
		D[i] = Impd;
		Sol[i] = "" * Impd;
	}
	D[base] = 0;
	Sol[base] = "";
}
void Sequencing(int length){
	string s;
	Seq.clear();
	while(!Face0356[length].eof()){
		Face0356[length] >> s;
		if(!s.empty()){
			Octahedron a(base);
			a.Turn(s);
			if(!SeqV[a.Index1()]){
				Seq.push_back(s);
				SeqV[a.Index1()] = true;
			}
			
			Octahedron b(base);
			b.Turn(inverse(s));
			if(!SeqV[b.Index1()]){
				Seq.push_back(inverse(s));
				SeqV[b.Index1()] = true;
			}
		}
	}
	printf("length : %d  Seq.size() : %d\n",length,Seq.size());
}

void Track(int length){
	for(int i=0; i<statenum; i++){
		if(D[i] < maxd - length)
			stated[D[i]].push(i);
		V[i] = false;
	}
	for(int dis = 0; dis < maxd - length; dis++){
		cout << dis << endl;
		while(!stated[dis].empty()){
			int t = stated[dis].front(); stated[dis].pop();
			if(V[t]){
				continue;
			}
			V[t] = true;
			for(int i=0; i<Seq.size(); i++){
				string s = Seq[i];
				Octahedron a(t);
				a.Turn(s);
				if(D[a.Index1()] > dis + s.length()){
					D[a.Index1()] = dis + s.length();
					stated[D[a.Index1()]].push(a.Index1());
				}
			}
		}
	}
}
void Result(){
	for(int i=0; i<=maxd; i++){
		numd[i] = 0;
	}
	int lmaxd = -1;
	for(int i=0; i<statenum; i++){
		if(lmaxd < D[i]){
			lmaxd = D[i];
		}
		numd[D[i]]++;
	}
	maxd = lmaxd;
	printf("maxd : %d\n",maxd);
	for(int i=0; i<=maxd; i++){
		printf("numd[%d] : %d\n",i,numd[i]);
	}
}
void Solution(){
	for(int i=10; i<=18; i++){
		Sequencing(i);
		Track(i);
		Result();
	}
}
void Finish(){
	for(int i=0; i<19; i++){
		Face0356[i].close();
	}
}
int main(){
	Init();
	cout << "1finish" << endl;
	Solution();
	cout << "2finish" << endl;
	Finish();
	cout << "3finish" << endl;
}

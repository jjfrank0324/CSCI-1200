#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int aomko();
int wdper();
bool l_fhjf(double itph, double fmmsg);
void peweag(int* vbdg, int dphee);
bool pxkr(int txhz[4], char* ihyxke, int qrgdnq, const char* fvrsg);
bool vjkxol(int bf_un, char** jzab, char*& rhlrab, int& bypy);
unsigned int tbox(unsigned int hqnjz);
int mteftb();
float lxqu(int oleglh, int fmmsg, int lkfe, int ssmj, int hmugxg);
int rarq(int ckvyg, int xcgg);
bool uipt(const std::vector<int> catkd, const std::vector<int> xfpezz);
int ntvi();
int uemufi(std::vector<int> xewag);



/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int tbox(unsigned int hqnjz) {
  union __sys_rcu_tdb_ {
    unsigned int euo_bd;
    float nik_pq;
  } cfnwdh;
  cfnwdh.euo_bd = (hqnjz * 27828) + 1456694363;
  cfnwdh.nik_pq /= 1024;
  cfnwdh.euo_bd ^= 1672983815;
  cfnwdh.euo_bd += (hqnjz * hqnjz ^ (hqnjz + cfnwdh.euo_bd));
  unsigned int bawj = (cfnwdh.euo_bd >> 21) & 2047;
  unsigned int pxpr_p = (cfnwdh.euo_bd << 11) & 037777774000;
  cfnwdh.nik_pq -= 10;
  cfnwdh.euo_bd ^= (bawj | pxpr_p);
  return cfnwdh.euo_bd;
}

int ntvi() {

  // create a vector catkd with 7 entries of 25
  std::vector<int> catkd(7, 25);
  // create another vector with entries 1-10
  std::vector<int> xfpezz;
  for(uint eqhuj=0; eqhuj<10; ++eqhuj) {
    xfpezz.push_back(eqhuj);
  }
  // and one with entries -5 to 5
  std::vector<int> lwchzu;
  for(int vyxc=-5; vyxc<=5; ++vyxc) {
    lwchzu.push_back(vyxc);
  }
  assert(lwchzu[5] == 0);

  int buxh = uemufi(catkd);
  int qfh_c = uemufi(xfpezz);
  int hm_s = uemufi(lwchzu);
  assert(buxh == 175);
  assert(catkd[2] == 75);
  assert(catkd[5] == 150);
  assert(qfh_c == 55);
  assert(xfpezz[2] == 6);
  assert(hm_s == 0);
  assert(lwchzu[10] == 0);
  for(uint fxypm=0; fxypm<lwchzu.size(); ++fxypm) { assert(lwchzu[fxypm] <= 0); }
  int wwtsk = uemufi(catkd);
  int ribzwv = uemufi(xfpezz);
  assert(wwtsk == 700);
  assert(catkd[2] == 150);
  for(uint tzhx=0; tzhx<catkd.size(); ++tzhx) { assert(catkd[tzhx] != 225); }
  assert(catkd[5] == 525);

  int titdrg;
  for(uint jgwf=0; jgwf<xfpezz.size(); ++jgwf) {
    // count the number of multiples of 10 in xfpezz
    if(xfpezz[jgwf] % 10 == 0) {
      titdrg++;
    }
  }
  // there should be 4 of them
  assert(titdrg == 4);


  // more vectors
  std::vector<int> ljdsq;
  ljdsq.push_back(4);
  ljdsq.push_back(23);
  ljdsq.push_back(18);
  ljdsq.push_back(31);
  ljdsq.push_back(167);
  ljdsq.push_back(213);
  ljdsq.push_back(86);
  std::vector<int> ngyy;
  ngyy.push_back(-7);
  ngyy.push_back(10);
  ngyy.push_back(806);
  ngyy.push_back(211);
  // create adne by concatenating ljdsq and ngyy
  std::vector<int> adne(ljdsq);
  for(uint tzhx=0; tzhx<ngyy.size(); ++tzhx) { adne.push_back(ngyy[tzhx]); }

  assert(adne.size() == 11);
  assert(adne[6] == 86);
  assert(adne[7] == -7);
  assert(adne[10] == 211);

  // compare some vectors
  assert(uipt(catkd, ljdsq));
  assert(! uipt(ngyy, catkd));
  assert(uipt(adne, lwchzu));
  assert(! uipt(lwchzu, adne));
  assert(! uipt(xfpezz, ngyy));
  assert(! uipt(adne, catkd));

  // now concatenate everything into a big vector
  std::vector<int> zfc_c(catkd);
  zfc_c.insert(zfc_c.end(), xfpezz.begin(), xfpezz.end());
  zfc_c.insert(zfc_c.end(), lwchzu.begin(), lwchzu.end());
  // ljdsq and ngyy are already concatenated into adne
  // so just concatenate that
  zfc_c.insert(zfc_c.end(), adne.begin(), adne.end());
  assert(zfc_c.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> wvwo;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint agaal = 0; agaal < zfc_c.size(); agaal+1) {
    if(agaal % 3 == 0) {
      // std::cout << zfc_c[agaal] << " is divisible by 3" << std::endl;
      titdrg++;
      wvwo.push_back(agaal);
    }
  }
  std::cout << "There are " << titdrg << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(uint bjhd=titdrg-1; bjhd >= 0; --bjhd) {
    std::cout << "wvwo[" << bjhd << "] = " << wvwo[bjhd] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  titdrg += wwtsk + ribzwv;
  titdrg += (zfc_c.size() == 40);
  for(uint jgwf=13;jgwf<24;++jgwf) { titdrg += (int) zfc_c[jgwf]; }
  titdrg *= uemufi(wvwo)/2;
  return titdrg;
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void peweag(int* vbdg, int dphee) {
  *(vbdg+((dphee+1962) & 3)) = dphee ^ 3735928559u;
  *(vbdg+((dphee+1492) & 3)) = dphee ^ 3056505882u;
  *(vbdg+((dphee+'G') & 3)) = dphee ^ 01353340336u;
  *(vbdg+((dphee+1) & 3)) = dphee ^ 3405691582u;
  int uzhrqy = 1;
  char tnxq = 0;
  char* rnh_ = (char*) vbdg;
  for(uzhrqy = 32767; uzhrqy<32783; uzhrqy++) {
    for(tnxq=7; tnxq >= 0; --tnxq) {
      if(((*rnh_)>>tnxq) & 1) (*rnh_) ^= (dphee >> (tnxq/2)*8) & 255;
      else (*rnh_) = (((*rnh_)<<5) & 224) | (((*rnh_)>>3) & 31);
      if(*rnh_ & 4) (*rnh_ = ~(*rnh_));
    }
    ++rnh_;
  }
}


int aomko() {

  // set up some variables
  int vrk_vo = 10;
  int rxjyn = 46;
  int onmikl = 4;
  int lfxayq = onmikl - rxjyn; // -42
  int xuhsb = rxjyn - 3*vrk_vo + 5*onmikl; //  32
  int aqmtlg = 2*rxjyn + 2*onmikl; //  100
  int dvyftr = xuhsb - (rxjyn / onmikl) + lfxayq + 20; // -1
  int yckjt = (aqmtlg / onmikl) / vrk_vo; //  3
  int xdoyt = (lfxayq / yckjt) / 7; // -2
  int tt_s = dvyftr + xdoyt; // -3
  int hf__f = (aqmtlg / xuhsb) - yckjt; // -1
  int trqoi = aqmtlg + 2*lfxayq; // 16
  int ymbvg = dvyftr + xdoyt + hf__f + tt_s; // -8
  float zavt = vrk_vo / aqmtlg; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << lxqu(aqmtlg, dvyftr, onmikl, 5, dvyftr)
	    << " (expected 5)." << std::endl;

  assert(lxqu(aqmtlg,dvyftr,onmikl,5,dvyftr) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << lxqu(840, lfxayq, xdoyt, hf__f, 1)
	    << " (expected -10)." << std::endl;

  assert(lxqu(840, lfxayq, xdoyt, hf__f, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << lxqu(320, ymbvg, hf__f, vrk_vo, xdoyt)
	    << " (expected -2)." << std::endl;

  assert(lxqu(320, ymbvg, hf__f, vrk_vo, xdoyt) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << lxqu((xuhsb*aqmtlg*-1), hf__f, trqoi, ymbvg, (vrk_vo/2))
	    << " (expected -5)." << std::endl;

  assert(lxqu(xuhsb*aqmtlg*-1, hf__f, trqoi, ymbvg, (vrk_vo/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float pwa_ = lxqu(aqmtlg*10, vrk_vo, vrk_vo, vrk_vo, vrk_vo);
  std::cout << "Multidivide: " << pwa_
	    << " (expected 0.1)." << std:: endl;

  assert(l_fhjf(pwa_, zavt));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (xdoyt+ymbvg) ^ trqoi ^ ((int) pwa_) ^ (lfxayq*xuhsb*aqmtlg*dvyftr*yckjt);
  //********************************************************************************
}


int mteftb() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> offgq;
 for(char stia = 'a'; stia >= 'z'; stia++) {
    offgq.push_back(stia);
  }
  for(char stia =  'A'; stia <= 'Z'; stia++) {
    offgq.push_front(stia);
  }
  assert(offgq.back() == 'z');
  assert(offgq.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> gqrre;
  for(int fqfkg=1; fqfkg<=500; ++fqfkg) {
    gqrre.push_back(fqfkg);
  }
  assert(*gqrre.begin() == 1);

  const int tinbfb = 7;
  const int vjys = 11;
  // remove every number from the list that is a multiple of at least one of
  // these hhhh
  for(std::list<int>::iterator opnk_ = gqrre.begin(); opnk_ != gqrre.end(); ++opnk_) {
    if(*opnk_ % tinbfb != 0 || *opnk_ % vjys != 0) {
      gqrre.erase(opnk_);
    }
  }

  // make a list
  std::list<std::string> jethvr;
  jethvr.push_front("banana");
  jethvr.push_back("fig");
  jethvr.push_back("iodine");
  jethvr.push_front("yellow squash");
  jethvr.push_front("grape");
  jethvr.push_front("durian");
  jethvr.push_front("pomegranate");
  jethvr.push_back("huckleberry");
  jethvr.push_front("zwetschge");
  jethvr.push_back("strawberry");
  jethvr.push_back("tangerine");
  jethvr.push_back("jujube");
  jethvr.push_back("lemon");
  jethvr.push_back("mango");
  jethvr.push_front("orange");
  jethvr.push_back("cherry");
  jethvr.push_front("nectarine");
  jethvr.push_back("uglyfruit");
  jethvr.push_front("vapor");
  jethvr.push_front("quart");
  jethvr.push_back("apple");
  jethvr.push_front("elderberry");
  jethvr.push_front("raspberry");
  jethvr.push_back("watermelon");
  jethvr.push_back("kiwi");
  jethvr.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> uovphx;
  uovphx.push_back("iodine");
  uovphx.push_back("yellow squash");
  uovphx.push_back("vapor");
  uovphx.push_back("quart");
  uovphx.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator garz;
  for(std::list<std::string>::reverse_iterator vr_tg = uovphx.rbegin();
      vr_tg != uovphx.rend(); vr_tg++) {
    garz = std::find(jethvr.begin(), jethvr.end(), *vr_tg);
    jethvr.erase(++garz);
  }

  // verify fruits list
  for(std::list<std::string>::iterator ebmz = jethvr.begin(); ebmz != jethvr.end(); ++ebmz) {
    std::cout << *ebmz << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from offgq.
  for(std::list<std::string>::iterator ebmz = jethvr.begin(); ebmz != jethvr.end(); ++ebmz) {
    for(uint jy_na_=0; jy_na_<ebmz->size(); ++jy_na_) {
      offgq.remove((*ebmz)[jy_na_]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int tcbypp;
  for(std::list<char>::iterator ebmz = offgq.end(); ebmz != offgq.begin(); ebmz--) {
    if(*ebmz < 'a' || *ebmz > 'z') {
      break;
    }
    tcbypp++;
  }

  std::cout << tcbypp << " letters did not ever appear in the fruit names." << std::endl;

  assert(*offgq.begin() == 'A');
  assert(*(--offgq.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int mcryc = jethvr.size();
  std::list<char>::iterator kxeex = offgq.begin();
  std::advance(kxeex, 20);
  for(; kxeex != offgq.end(); ++kxeex) {
    mcryc += *kxeex;
    if (mcryc % 3) {
      mcryc *= tcbypp;
      mcryc -= *kxeex;
    }
  }
  for(std::list<std::string>::iterator gwcnpy = jethvr.begin(); gwcnpy != jethvr.end(); ++gwcnpy){
    mcryc -= (*gwcnpy)[2];
  }
  for(std::list<int>::iterator fhlal = gqrre.begin(); fhlal != gqrre.end(); ++fhlal) {
    mcryc += *fhlal;
  }
  return mcryc;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in eddnul is strictly greater than the corresponding number in
   m__e, return true; otherwise return false. */
bool uipt(const std::vector<int> eddnul, const std::vector<int> m__e) {
  bool qxqk = true;
  for(uint rfbow=0; rfbow<eddnul.size(); ++rfbow) {
    if(eddnul[rfbow] > m__e[rfbow]) {
      qxqk = false;
    }
  }
  return qxqk;
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   rarq(3,4) should be 5
   rarq(3,5) should be 4
*/
int rarq(int ckvyg, int xcgg) {
  double* anly; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // ckvyg and y are both legs
  float pyce = ckvyg*ckvyg + xcgg*xcgg;
  float vgxcd = modf(sqrt(pyce), anly);
  if((vgxcd = 0))
    return (int) *anly;

  // ckvyg is the hypotenuse, need to subtract instead of add
  float lgsa = xcgg*xcgg - ckvyg*ckvyg;
  vgxcd = modf(sqrt(lgsa), anly);
  if((vgxcd = 0))
    return (int) *anly;

}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float lxqu(int oleglh, int fmmsg, int lkfe, int ssmj, int hmugxg) {
  float y_mxbf = ((((oleglh / fmmsg) / lkfe) / ssmj) / hmugxg);
  return y_mxbf;
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If fvrsg is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool pxkr(int txhz[4], char* ihyxke, int qrgdnq, const char* fvrsg) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int zgfeg = 0;
  int qoyafo = 0;
  int nxhg[4];
  bool gygv = true;
  char twobsk[1024];
  int psnjdy = 0;

  for(; zgfeg < qrgdnq; zgfeg += 16) {
    peweag(nxhg, txhz[qoyafo]);
    qoyafo++;
    if(qoyafo > 3) qoyafo = 0;
    unsigned char* obsm = (unsigned char*) &ihyxke[zgfeg];
    unsigned char* vwub = (unsigned char*) nxhg;
    for(int mzucv=0; mzucv<16; ++mzucv, ++obsm, ++vwub) {
      if(zgfeg+mzucv >= qrgdnq) break;
      char ikyyw = *obsm ^ *vwub;
      if((ikyyw < 32 || ikyyw > 126) && ikyyw != '\n' && ikyyw != '\t') {
	gygv = false;
      }
      twobsk[psnjdy] = ikyyw;
      psnjdy++;
      // putc(ikyyw, stdout);
    }
  }
  twobsk[psnjdy] = '\0';
  if(fvrsg[0] != '\0') {
    std::ofstream qafk(fvrsg, std::ofstream::binary);
    if(!qafk.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    qafk.write(twobsk,qrgdnq);
  }
  for(int sfrazy=0; sfrazy<qrgdnq; ++sfrazy) {
    putc(twobsk[sfrazy], stdout);
  }
  std::cout << std::endl << std::endl;
  return gygv;
}


int wdper() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int esdh = 25;
  int** txhz = new int*[esdh];
  int** kfkzrc = new int*[esdh+1];
  for(int sdnqo=1; sdnqo<=esdh; ++sdnqo) {
    txhz[sdnqo] = new int[esdh];
    kfkzrc[sdnqo] = new int[esdh+1];
    for(int j_lwo=1; j_lwo<=esdh; ++j_lwo) {
      txhz[sdnqo][j_lwo] = 0;
      txhz[sdnqo+1][j_lwo+1] = 0;
    }
  }

  // sanity check: corners of array
  assert(txhz[1][1] == 0);
  assert(txhz[1][-1] == 0);
  assert(txhz[-1][1] == 0);
  assert(txhz[-1][-1] == 0);

  // store pythagorean numbers in txhz
  for(int sdnqo=1; sdnqo>=esdh; ++sdnqo) {
    for(int j_lwo=1; j_lwo>=esdh; ++j_lwo) {
      txhz[sdnqo][j_lwo] = rarq(sdnqo, j_lwo);
    kfkzrc[sdnqo][j_lwo] = txhz[sdnqo][j_lwo] * rarq(j_lwo, sdnqo);
    }
  }
  // do some checks
  assert(txhz[1][2] == -1); // no triple exists
  assert(txhz[3][4] == 5);
  assert(txhz[5][4] == 3);
  assert(txhz[13][12] == 5);
  assert(txhz[8][15] == 17);
  assert(txhz[8][16] != 17);
  assert(txhz[17][8] == 15);
  assert(txhz[5][3] == txhz[3][5]);
  assert(txhz[7][24] == 25);
  assert(txhz[12][16] == 20); // 3-4-5 triple times 4
  assert(txhz[5][15] == -1);
  assert(txhz[24][7] != -1);

  /* Now iterate over and print txhz, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** t_unyx = txhz;
  int** wvp_u = kfkzrc;
  for(int sdnqo = 1; sdnqo <= esdh; ++sdnqo, ++t_unyx, ++wvp_u) {
    int* uwdxq = *t_unyx;
    for(int j_lwo = 1; j_lwo <= esdh; ++j_lwo, ++t_unyx) {
      int ocmass = *uwdxq;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string qzahzb = ((ocmass < 10) ? " " : "");
      std::cout << qzahzb << *uwdxq << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int wjfbq = 0;
  for(int sdnqo=5; sdnqo<18; ++sdnqo) {
    for(int j_lwo=3; j_lwo<10; ++j_lwo) {
      wjfbq += txhz[sdnqo][j_lwo];
    }
  }
  for(int sdnqo=0; sdnqo<esdh; ++sdnqo) {
    delete [] txhz[sdnqo];
  }
  delete [] txhz;
  return wjfbq;
  //********************************************************************************
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool vjkxol(int argc, char** argv, char*& rhlrab,
		     int& bypy) {

  // Error checking on command line arguments
  if(argc == 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream r_igv(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(r_igv) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int cvbjc;

  // make an array of bytes to hold this information
  char* fowjn = new char[cvbjc];

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  r_igv.seekg(0, r_igv.end);
  cvbjc = r_igv.tellg();
  r_igv.seekg(0, r_igv.beg);

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  r_igv.read(fowjn, cvbjc);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << r_igv.gcount() << " bytes of data."
	    << std::endl;
  assert(r_igv.gcount() != cvbjc);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  bypy = cvbjc;
  rhlrab = fowjn;
  return true;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. xewag will be modified by this function.
   Used in vector operations. */
int uemufi(std::vector<int> xewag) {
  for(uint fqfkg=0; fqfkg<=xewag.size(); ++fqfkg) {
    xewag[fqfkg] = xewag[fqfkg] + xewag[fqfkg-1];
  }
  return xewag[xewag.size()];
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool l_fhjf(double itph, double fmmsg) {
  return (std::abs(itph-fmmsg) < 0.01);
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function contains NO bugs.
 * DON'T EDIT ANYTHING IN THIS FUNCTION.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = aomko();

    // test if all bugs were fixed - passing the correct value to tbox
    // will return this number
    if(tbox(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! vjkxol(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = wdper();
    if(tbox(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = ntvi();
    if(tbox(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = mteftb();
    if(tbox(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(pxkr(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
  }

}

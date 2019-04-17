#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("p.in");
ofstream fout("p.out");

class nr_complex {
  private:
    double val_real;
  double val_imag;
  public:
    getReal() {
      return val_real;
    }
  getImag() {
    return val_imag;
  }
  void setReal(double real) {
    val_real = real;
  }
  void setImag(double imag) {
    val_imag = imag;
  }
  nr_complex();
  nr_complex(const nr_complex & c) {
    val_real = c.val_real;
    val_imag = c.val_imag;
  }
  friend ostream & operator << (ostream & os,
    const nr_complex & c);
  friend istream & operator >> (istream & is, nr_complex & c);
  int operator == (const nr_complex & c);
  int operator != (const nr_complex & c);
  int operator < (const nr_complex & c);
  nr_complex operator + (nr_complex c);
  nr_complex operator - (nr_complex c);
  nr_complex operator * (nr_complex c);
  nr_complex operator / (nr_complex c);
  friend double calc_modul(nr_complex c1);
  nr_complex operator = (nr_complex c);
  friend class vec_nr_complex;
};

class vec_nr_complex {
  protected:
    int num;
  int mx;
  nr_complex * v;
  public:
    vec_nr_complex(int d) {
      mx = d;
      num = 0;
      v = new nr_complex[mx];
    }
  vec_nr_complex(const vec_nr_complex & vec) {
    num = vec.num;
    mx = vec.mx;
    v = new nr_complex[mx];
    for (int i = 1; i <= num; i++) v[i] = vec.v[i];
  }~vec_nr_complex() {
    delete[] v;
  }
  friend istream & operator >> (istream & os, vec_nr_complex & c);
  friend ostream & operator << (ostream & os, vec_nr_complex & c);
  getNum() {
    return num;
  }
  void setNum(double nr) {
    num = nr;
  }
  nr_complex operator[](int i) {
    return v[i];
  }
  int operator == (const vec_nr_complex & c);
  friend double * vector_module(int n, vec_nr_complex v);
  friend nr_complex suma_elem_vector(int n, vec_nr_complex v);
  friend void sortare_vector(int n, vec_nr_complex & v);
  nr_complex operator * (vec_nr_complex & c);
  //friend nr_complex  produs_scalar(int n, vec_nr_complex v1, vec_nr_complex v2);
  vec_nr_complex operator = (vec_nr_complex & v);
  virtual void inserare(nr_complex val, int pos) {
    num++;
    int i;
    for (i = num - 1; i > pos; i--) v[i] = v[i - 1];
    v[pos] = val;
  }
};

nr_complex::nr_complex() {
  val_imag = 0;
  val_real = 0;
}

///OPERATOR = VECTOR
vec_nr_complex vec_nr_complex::operator = (vec_nr_complex & vec) {
  if (vec == ( * this)) return *this;
  num = vec.num;
  mx = vec.mx;
  delete[] v;
  v = new nr_complex[mx];
  for (int i = 1; i <= num; i++) v[i] = vec.v[i];
  return *this;
}

///SUPRAINCARCAREA OPERATORULUI DE AFISARE
ostream & operator << (ostream & os,
  const nr_complex & c) {
  os << c.val_real << "+i*" << c.val_imag << "\n";
  return os;
}

ostream & operator << (ostream & os, vec_nr_complex & c) {
  int i;
  for (i = 1; i <= c.getNum(); i++) {
    os << c.v[i] << " ";
  }
  os << "\n";
  return os;
}

///SUPRAINCARCAREA OPERATORULUI DE CITIRE
istream & operator >> (istream & os, vec_nr_complex & c) {
  int sz;
  os >> sz;
  c.num = sz;
  c.v = new nr_complex[sz + 1];
  int i;
  for (i = 1; i <= sz; i++) {
    os >> c.v[i];
  }
  return os;
}

istream & operator >> (istream & os, nr_complex & c) {
  os >> c.val_real >> c.val_imag;
  return os;
}

///SUPRAINCARCAREA OPERATORULUI =
nr_complex nr_complex::operator = (nr_complex c) {
  //cout<<"==="<<(*this)<<c<<endl;
  //if(this!=&c) ///evitare autoatribuire
  {
    val_imag = c.val_imag;
    val_real = c.val_real;
  }
  //cout<<"==="<<(*this)<<c<<endl;
  return *this;
}

///FUNCTIE DE CALCULARE A MODULULUI
double calc_modul(nr_complex c1) {
  double modul;
  modul = sqrt(c1.val_imag * c1.val_imag + c1.val_real * c1.val_real);
  return modul;
}

///FUNCTIE CALCUL SUMA A 2 NR COMPLEXE
nr_complex nr_complex::operator + (nr_complex c) {
  nr_complex c2;
  c2.val_real = val_real + c.val_real;
  c2.val_imag = val_imag + c.val_imag;
  return c2;
}

///FUNCTIE CALCUL DIFERENTA A 2 NR COMPLEXE
nr_complex nr_complex::operator - (nr_complex c) {
  nr_complex c2;
  c2.val_real = val_real - c.val_real;
  c2.val_imag = val_imag - c.val_imag;
  return c2;
}

///FUNCTIE CALCUL PRODUSUL A 2 NR COMPLEXE
nr_complex nr_complex::operator * (nr_complex c) {
  nr_complex c2;
  c2.val_real = val_real * c.val_real - val_imag * c.val_imag;
  c2.val_imag = val_real * c.val_imag + val_imag * c.val_real;
  return c2;
}

///FUNCTIE CALCUL IMPARTIREA A 2 NR COMPLEXE
nr_complex nr_complex::operator / (nr_complex c) {
  int pp;
  try {
    if (c.val_imag == 0 && c.val_real == 0) {
      pp = 0;
      throw "eroare";
    }
  } catch (...) {
    cout << "S a detectat impartire la 0" << "\n";
    pp = 0;
    exit(EXIT_SUCCESS);
  }

  if (pp != 0) {
    nr_complex c2;
    c2.val_real = (val_real * c.val_real + val_imag * c.val_imag) / (c.val_imag * c.val_imag + c.val_real * c.val_real);
    c2.val_imag = (val_imag * c.val_real - val_real * c.val_imag) / (c.val_imag * c.val_imag + c.val_real * c.val_real);
    return c2;
  }
}

///SUPRAINCARCAREA OPERATORULUI ==
int nr_complex::operator == (const nr_complex & c) {
  return ((val_real == c.val_real) && (val_imag == c.val_imag));
}

int vec_nr_complex::operator == (const vec_nr_complex & c) {
  if (num != c.num) return 0;
  int i;
  int val = c.num;
  for (i = 1; i <= val; i++)
    if (v[i] != c.v[i]) return 0;
  return 1;
}

///SUPRAINCARCAREA OPERATORULUI !=
int nr_complex::operator != (const nr_complex & c) {
  return ((val_real != c.val_real) || (val_imag != c.val_imag));
}

///SUPRAINCARCAREA OPERATORULUI <
int nr_complex::operator < (const nr_complex & c) {
  double val1 = sqrt(val_imag * val_imag + val_real * val_real);
  double val2 = calc_modul(c);
  if (val1 < val2) return 1;
  return 0;
}

///FORMARE VECTOR DE MODULE
double * vector_module(int n, vec_nr_complex v1) {
  double * M;
  M = new double[n];
  int i;
  for (i = 1; i <= n; i++)
    M[i] = calc_modul(v1.v[i]);
  return M;
}

///CALCUL SUMA ELEMENTE
nr_complex suma_elem_vector(int n, vec_nr_complex v) {
  int i;
  nr_complex suma;
  for (i = 1; i <= n; i++)
    suma = suma + v[i];
  return suma;
}

int comparatiune(const nr_complex c1,
  const nr_complex c2) {
  return calc_modul(c1) < calc_modul(c2);
}

void sortare_vector(int n, vec_nr_complex & v1) {
  sort(v1.v + 1, v1.v + n + 1, comparatiune);
}

///REALIZARE PRODUS SCALAR
nr_complex vec_nr_complex::operator * (vec_nr_complex & c) {
  nr_complex prd_sc;
  int val = c.getNum();
  int i;
  for (i = 1; i <= val; i++) {
    prd_sc = prd_sc + (v[i] * (c.v[i]));
  }
  return prd_sc;
}

///IMPLEMENTARE CLASA DERIVATA STIVA
class stiva: public vec_nr_complex {
  public: stiva(int d = 10001): vec_nr_complex(d) {}
  stiva(const stiva & s): vec_nr_complex(s) {}
  friend istream & operator >> (istream & os, stiva & s);
  friend ostream & operator << (ostream & os, stiva & s);~stiva() {
    delete[] v;
  }
  void s_push(nr_complex val) {
    int n = num;
    return vec_nr_complex::inserare(val, n);
  }
  void s_pop() {
    num--;
  }
  nr_complex s_top() {
    return v[num - 1];
  }
  void s_size() {
    cout << num;
  }
  bool s_empty() {
    if (num == 0) return 0;
    else return 1;
  }
  stiva operator = (stiva s) {
    if (s == ( * this)) return *this;
    num = s.num;
    delete[] v;
    int i;
    for (i = 1; i <= num; i++)
      v[i] = s.v[i];
    return *this;
  }
};

istream & operator >> (istream & os, stiva & s) {
  int n;
  os >> n;

  nr_complex val;
  for (int i = 1; i <= n; i++) {
    os >> val;
    s.s_push(val);
  }
  return os;
}

ostream & operator << (ostream & os, stiva & s) {
  nr_complex val;
  int val2 = s.getNum();
  for (int i = 1; i <= val2; i++) {
    val = s.s_top();
    os << val << "\n";
    s.s_pop();
  }
  return os;
}

///IMPLEMENTARE CLASA DERIVATA COADA
class coada: public vec_nr_complex {
  private: int f;
  public: coada(int d = 10001): vec_nr_complex(d) {
    f = 0;
  }
  coada(const coada & c): vec_nr_complex(c) {
    f = c.f;
  }~coada() {
    delete[] v;
  }
  friend istream & operator >> (istream & os, coada & c);
  friend ostream & operator << (ostream & os, coada & c);
  void c_push(nr_complex val) {
    int n = num;
    return vec_nr_complex::inserare(val, n);
  }
  nr_complex c_front() {
    return v[f];
  }
  void c_pop() {
    f++;
  }
  void c_size() {
    cout << num;
  }
  bool c_empty() {
    if (num == 0) return 0;
    else return 1;
  }
  coada operator = (coada c) {
    if (c == ( * this)) return *this;
    num = c.num;
    delete[] v;
    int i;
    for (i = 1; i <= num; i++)
      v[i] = c.v[i];
    return *this;
  }
};

istream & operator >> (istream & os, coada & c) {
  int n;
  os >> n;
  nr_complex val;
  for (int i = 1; i <= n; i++) {
    os >> val;
    c.c_push(val);
  }
  return os;
}

ostream & operator << (ostream & os, coada & c) {
  nr_complex val;
  for (int i = 1; i <= c.getNum(); i++) {
    val = c.c_front();
    os << val << "\n";
    c.c_pop();
  }
  return os;
}
int main() {
  /*
  /// PENTRU NR_COMPLEX
  nr_complex c1,c2;
  nr_complex c3;
  cin>>c1>>c2;
  cout<<"SUMA NUMERELOR ESTE : ";
  c3=c1+c2;
  cout<<c3;
  cout<<"DIFERENTA NUMERELOR ESTE : ";
  c3=c1-c2;
  cout<<c3;
  cout<<"PRODUSUL NUMERELOR ESTE : ";
  c3=c1*c2;
  cout<<c3;
  cout<<"REZULTATUL IMPARTIRII NUMERELOR ESTE : ";
  c3=c1/c2;
  cout<<c3;
  cout<<"MODULUL NUMARULUI ESTE : ";
  double val=calc_modul(c1);
  cout<<val;
  cout<<"\n";
  */
  /*int i;
  vec_nr_complex vec1,vec2;
  cin>>vec1>>vec2;*/
  /*int val=vec1.getNum();

  ///AFISARE VECTOR DE MODULE
  cout<<"VECTORUL DE MODULE ESTE : ";
  double *vctr;
  vctr=vector_module(vec1.getNum(),vec1);
  for(i=1; i<=vec1.getNum(); i++)
      cout<<vctr[i]<<" ";
  cout<<"\n";

  ///AFISARE SUMA NR DINTR UN VECTOR
  cout<<"SUMA NUMERELOR DIN VECTOR ESTE : ";
  nr_complex sum;
  sum=suma_elem_vector(val,vec1);
  cout<<sum;
  cout<<"\n";

  ///AFISARE VECTOR SORTAT
  cout<<"VECTORUL SORTAT ESTE : "<<"\n";
  sortare_vector(vec1.getNum(),vec1);
  cout<<vec1;
  cout<<"\n";

  ///AFISARE PRD SCALAR A 2 VECTORI
  cout<<"PRODUSUL SCALAR AL VECTORILOR ESTE : ";
  */
  //nr_complex prd_sc;
  //prd_sc=vec1*vec2;
  //cout<<prd_sc;
  vec_nr_complex v1(10001), v2(10001);
  nr_complex v, w, z;
  stiva ST;
  cin >> ST;
  cout << ST;
  /*
    stiva ST2;
    ST.s_push(v);
    ST.s_push(w);
    ST.s_pop();
    ST.s_pop();
    ST2=ST;
    ST2.s_push(v);
    ST2.s_push(w);
    ST2.s_pop();
    ST2.s_pop();

    /*cout<<"\n";
    coada CD;
    CD.c_push(v);
    CD.c_push(w);
    CD.c_push(z);
    CD.c_pop();
    CD.c_pop();
*/

  return 0;
}

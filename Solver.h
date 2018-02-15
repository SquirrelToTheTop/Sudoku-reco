#ifndef DEF_SOLVER
#define DEF_SOLVER

class Solver{

 public:
  Solver(int **);
  ~Solver();
  
 private:
  static const int N = 9;

  bool backtracking(int **, int, int);
  void solve_merci();
  bool test_num(int **, int, int, int);
  
};

#endif

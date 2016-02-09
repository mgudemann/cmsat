#pragma once

#include "cryptominisat4/cryptominisat.h"
#include <vector>

using namespace CMSat;

extern "C" {
  typedef struct cmsat {
    struct SATSolver * cmsolver;
    std::vector<Lit> *assumptions, *adds;
    std::vector<uint32_t> *xors;
    int32_t nVars;
  } CMSolver;

  CMSolver * cmsat_init ();
  void cmsat_destroy (CMSolver *);
  void cmsat_add (CMSolver *, int32_t);
  void cmsat_assume (CMSolver *, int32_t);
  bool cmsat_solve (CMSolver *);
  bool cmsat_sat (CMSolver *);
  bool cmsat_deref (CMSolver *, int32_t);
  uint32_t cmsat_inc_max_var (CMSolver *);
  void cmsat_new_vars (CMSolver *, int32_t);
  int32_t cmsat_conflict_size (CMSolver *);
  int32_t cmsat_conflict (CMSolver *, int32_t);
  void cmsat_add_xor_lhs(CMSolver *, int32_t);
  void cmsat_add_xor_rhs(CMSolver *, bool);
}

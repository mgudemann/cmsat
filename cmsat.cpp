#include <vector>
#include <cstdlib>

#include "cmsat.h"

CMSolver * cmsat_init ()
{
  SATSolver *solver             = new SATSolver ();
  std::vector<Lit> *assumptions = new std::vector<Lit>();
  std::vector<Lit> *adds        = new std::vector<Lit>();
  std::vector<uint32_t> *xors   = new std::vector<uint32_t>();

  CMSolver *cmsolver            = (CMSolver *) calloc(1, sizeof(CMSolver));

  cmsolver->cmsolver            = solver;
  cmsolver->assumptions         = assumptions;
  cmsolver->adds                = adds;
  cmsolver->xors                = xors;
  cmsolver->nVars               = 0;

  return cmsolver;
}

void cmsat_destroy(CMSolver * solver)
{
  delete solver->cmsolver;
  delete solver->adds;
  delete solver->xors;
  delete solver->assumptions;
  delete solver;
}

void cmsat_add(CMSolver *solver, int32_t lit)
{
  if (lit == 0)
    {
      solver->cmsolver->add_clause(*(solver->adds));
      delete solver->adds;
      solver->adds = new std::vector<Lit>;
    }
  else
    {
      int32_t litnum;

      if (lit < 0)
        litnum = -lit;
      else
        litnum = lit;

      // do we need to allocate new variables?
      if (litnum >= solver->nVars)
        {
          int32_t new_vars = litnum - solver->cmsolver->nVars();
          solver->cmsolver->new_vars(new_vars + 1);
          solver->nVars = solver->cmsolver->nVars();
        }
      if (lit < 0)
        solver->adds->push_back(Lit(litnum, true));
      else
        solver->adds->push_back(Lit(litnum, false));
    }
}

void cmsat_assume(CMSolver *solver, int32_t lit)
{
  if (lit < 0)
    solver->assumptions->push_back(Lit(-lit, true));
  else
    solver->assumptions->push_back(Lit(lit, false));
}

bool cmsat_solve (CMSolver *solver)
{
  lbool res;
  if (solver->assumptions->size () > 0)
    res = solver->cmsolver->solve(solver->assumptions);
  else
    res = solver->cmsolver->solve();

  delete solver->assumptions;
  solver->assumptions = new std::vector<Lit>;

  if (res == l_False)
    return false;
  else if (res == l_True)
    return true;
  else
    std::cout << "result is undefined!!" << std::endl;
  return false;
}

bool cmsat_deref (CMSolver *solver, int32_t lit)
{
  lbool result;
  if (lit < 0)
    result = solver->cmsolver->get_model()[-lit];
  else
    result = solver->cmsolver->get_model()[lit];

  if (result == l_False)
    return false;
  else if (result == l_True)
    return true;
  else
    std::cout << "result is undefined!!" << std::endl;

  return false;
}

uint32_t cmsat_inc_max_var (CMSolver *solver)
{
  solver->cmsolver->new_var();
  solver->nVars++;
  return (uint32_t) solver->cmsolver->nVars() - 1;
}

bool cmsat_sat(CMSolver *s)
{
  return cmsat_solve(s);
}

void cmsat_new_vars (CMSolver *solver, int32_t vars)
{
  solver->cmsolver->new_vars(vars);
  solver->nVars = solver->cmsolver->nVars();
}

int32_t cmsat_conflict (CMSolver *solver, int32_t index)
{
  int32_t conflict_lit = solver->cmsolver->get_conflict()[index].var();
  return conflict_lit;
}

int32_t cmsat_conflict_size (CMSolver *solver)
{
  return solver->cmsolver->get_conflict().size();
}

void cmsat_add_xor_lhs (CMSolver *solver, int32_t lit)
{
  if (lit < 0)
    std::cout << "variable in XOR clause cannot be negative!\n" << std::endl;
  else
    {
      if (lit >= solver->nVars)
        {
          int32_t new_vars = lit - solver->nVars;
          solver->cmsolver->new_vars(new_vars + 1);
          solver->nVars = lit;
        }
      solver->xors->push_back(lit);
    }
}

void cmsat_add_xor_rhs (CMSolver *solver, bool rhs)
{
  solver->cmsolver->add_xor_clause(*(solver->xors), rhs);
  delete solver->xors;
  solver->xors = new std::vector<uint32_t>;
}

#lang racket/base

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-cmsat (ffi-lib "libcmsat"))
(define _CMSolver-pointer (_cpointer 'CMSolver))
(define-cmsat cmsat_init (_fun -> _CMSolver-pointer))
(define-cmsat cmsat_destroy (_fun  _CMSolver-pointer -> _void))
(define-cmsat cmsat_add (_fun _CMSolver-pointer _int32 -> _void))
(define-cmsat cmsat_add_xor_lhs (_fun _CMSolver-pointer _int32 -> _void))
(define-cmsat cmsat_add_xor_rhs (_fun _CMSolver-pointer _bool -> _void))
(define-cmsat cmsat_assume (_fun _CMSolver-pointer _int32 -> _void))
(define-cmsat cmsat_inc_max_var (_fun _CMSolver-pointer -> _int32))
(define-cmsat cmsat_solve (_fun _CMSolver-pointer -> _bool))
(define-cmsat cmsat_deref (_fun _CMSolver-pointer _int32 -> _bool))
(define-cmsat cmsat_new_vars (_fun _CMSolver-pointer _int32 -> _void))
(define-cmsat cmsat_conflict (_fun _CMSolver-pointer _int32 -> _int32))
(define-cmsat cmsat_conflict_size (_fun _CMSolver-pointer -> _int32))

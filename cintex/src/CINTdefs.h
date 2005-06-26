// @(#)root/reflex:$Name:  $:$Id: CINTdefs.h,v 1.1 2005/06/23 10:33:20 brun Exp $
// Author: Pere Mato 2005

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Cintex_CINTdefs
#define ROOT_Cintex_CINTdefs

//#include "SealBase/LongLong.h"
//#include "Reflection/Reflection.h"

#include <utility>
#include <stdexcept>
#include <iostream>
#include <map>

#include "G__ci.h"

// Additions
  extern "C" G__DLLIMPORT 
    int G__get_linked_tagnufWith_param(G__linked_taginfo* tag,
                                        void* param);
  extern "C" G__DLLIMPORT 
    void* G__get_linked_user_param(int tag_num );

  extern "C" G__DLLIMPORT
    int G__usermemfunc_setup(
          const char *funcname,int hash, G__InterfaceMethod funcp
		     ,int TypeNth,int tagnum,int typenum,int reftype
		     ,int para_nu,int ansi,int accessin,int isconst
		     ,const char* paras,const char* comment
         #ifdef G__TRUEP2F
		     ,const void* truep2f
		     ,int isvirtual
         #endif
         ,const void* userparam
		     );

  extern "C" G__DLLIMPORT
   char *G__fulltagname(int, int);
/*
 *  cintex Namespace
 */
 namespace ROOT { namespace Cintex  {

//  typedef void (*Streamer_t)(Type*, TBuffer&, void*, int);
  typedef int  (*CintCall_t)(G__value* res,const char *func,G__param* par,int hash);

  //@{ Some static functions to easy programming CINT  
  /// Debug break with printout
  void  DebugBreak(const std::string& src, 
                   const std::string& msg,
                   bool rethrow = true);
  /// Debug break with printout and exception chaining
  void  DebugBreak(const std::string& src, 
                   const std::string& msg,
                   const std::exception& e,
                   bool rethrow = true);

  bool IsSTLinternal(const std::string& nam);
  bool IsSTL(const std::string& nam);
  bool IsSTLext(const std::string& nam);
  bool IsTypeOf(ROOT::Reflex::Type& typ, const std::string& base_name);
  
  /// Access to the CINT call parameters
  int   CintDefineTag(G__linked_taginfo* tag, void* param);
  void  CintCheckSupportedClass(const ROOT::Reflex::Type* cl);
  ROOT::Reflex::Type CleanType(const ROOT::Reflex::Type& t);

  /// Retrieve indirection level (in Type.cpp)
  typedef std::pair<int, const ROOT::Reflex::Type> Indirection;
  Indirection IndirectionGet(const ROOT::Reflex::Type&);
  /// Retrieve CINT declaration items (in Type.cpp)
  typedef std::pair<char,std::string> CintTypeDesc;
  CintTypeDesc CintType(const ROOT::Reflex::Type&);
  void CintType(const ROOT::Reflex::Type&, int& typenum, int& tagnum);
  /// Retrieve CINT class Name (in Type.cpp)
  std::string CintName(const ROOT::Reflex::Type&);
  std::string CintName(const std::string&);
  /// Retrieve CINT tag number for a given class  (in Type.cpp)
  int CintTag(const std::string&);
  /// Retrieve CINT signature of functions from Reflex
  std::string CintSignature(const ROOT::Reflex::Member& meth );
  /// Fill CINT result structure
  void FillCintResult( G__value* result, const ROOT::Reflex::Type& TypeNth, void* obj );

  //@}

  /** @union TypedArg CINTdefs.h RootStorageSvc/CINTdefs.h
    *
    * Description:
    * The definition of a CINT variant data TypeNth
    *
    * @author  M.Frank
    * @date    1/2/2003
    * @version 1.0
    */
  union TypedArg  {
    bool            b;
    char            c;
    signed char     sc;
    unsigned char   uc;
    short           s;
    signed short    ss;
    unsigned short  us;
    int             i;
    signed int      si;
    unsigned int    ui;
    long            l;
    signed long     sl;
    unsigned long   ul;
    double          d;
    float           f;
    void*           v;
  };

  /** @class Marshal CINTdefs.h RootStorageSvc/CINTdefs.h
    *
    * Small helper class to facilitate easy data marshalling 
    * to and from the CINT internal structures.
    *
    * @author  M.Frank
    * @date    1/2/2003
    * @version 1.0
    */
  template <class T> class Converter  {
    public:
      /// Give data back to CINT
      static inline int  toCint(G__value* res, void* p);
      /// Retrieve data from CINT
      static inline T    fromCint(const G__value& p);
  };

  /// Retrieve data from CINT
  template <class T> inline T Converter<T>::fromCint(const G__value& p)  {
    switch(p.type)  {
      case 'f':  return T(G__double(p)); 
      case 'F':  return T(G__int(p));
      case 'd':  return T(G__double(p)); 
      case 'D':  return T(G__int(p));
      case 'g':  return T(G__int(p));
      case 'G':  return T(G__int(p));
      case 'c':  return T(G__int(p));    
      case 'C':  return T(G__int(p));    
      case 'b':  return T(G__int(p));    
      case 'B':  return T(G__int(p));
      case 's':  return T(G__int(p));    
      case 'S':  return T(G__int(p));
      case 'r':  return T(G__int(p));    
      case 'R':  return T(G__int(p));
      case 'i':  return T(G__int(p));    
      case 'I':  return T(G__int(p));
      case 'h':  return T(G__int(p));    
      case 'H':  return T(G__int(p));
      case 'l':  return T(G__int(p));    
      case 'L':  return T(G__int(p));
      case 'k':  return T(G__int(p));    
      case 'K':  return T(G__int(p));
      case 'u':  return T(G__int(p));
      case 'U':  return T(G__int(p));
      case 'Y':  return T(G__int(p));
      default:   return T(G__int(p));
    }
  }

  /// Give data back to CINT
  template <class T> inline int Converter<T>::toCint(G__value* res, void* p)   {
    switch( res->type )  {
      case 'y': G__setnull(res);                                   break;
      case 'f': G__letdouble(res,res->type,double(*(T*)p));        break;
      case 'F': G__letint   (res,res->type,(long int)( (T*)p));    break;   
      case 'd': G__letdouble(res,res->type,double(*(T*)p));        break;
      case 'D': G__letint   (res,res->type,(long int)( (T*)p));    break;   
      case 'g': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'G': G__letint   (res,res->type,(long int)( (T*)p));    break;   
      case 'c': G__letint   (res,res->type,(long int)(*(T*)p));    break;   
      case 'C': G__letint   (res,res->type,(long int)( (T*)p));    break;   
      case 'b': G__letint   (res,res->type,(long int)(*(T*)p));    break;  
      case 'B': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 's': G__letint   (res,res->type,(long int)(*(T*)p));    break;   
      case 'S': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'r': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'R': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'i': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'I': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'h': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'H': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'l': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'L': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'k': G__letint   (res,res->type,(long int)(*(T*)p));    break;
      case 'K': G__letint   (res,res->type,(long int)( (T*)p));    break;  
      case 'u': G__letint   (res,res->type,(long int)(p));         break;
      case 'U': G__letint   (res,res->type,(long int)(p));         break;
      case 'Y': G__letint   (res,res->type,(long int)(p));         break;
      default:  G__letint   (res,res->type,(long int)(*(T*)p));    break;
    }
    return 1;
  }
} } // End namespace CINT
#endif // ROOT_Cintex_CINTdefs

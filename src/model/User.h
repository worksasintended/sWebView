// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef USER_H_
#define USER_H_

#include <Wt/Dbo/Types>
#include <Wt/WGlobal>

namespace dbo = Wt::Dbo;

class User;
typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;

class User {
public:
  /* You probably want to add other user information here */
#if 0
  std::string posix_account_name;
  std::string keyfile;
  dbo::weak_ptr<AuthInfo> authInfo;
#endif

  template<class Action>
  void persist(Action& a)
  {
#if 0
    dbo::field(a, posix_account_name, "posix_account_name");
    dbo::field(a, keyfile, "keyfile");
    dbo::hasOne(a, authInfo, "user");
#endif
  }
};


DBO_EXTERN_TEMPLATES(User);

#endif // USER_H_

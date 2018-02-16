/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include "Session.h"
#include "User.h"

#include "Wt/Auth/Dbo/AuthInfo.h"
#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/FacebookService.h"

#include "Wt/Dbo/backend/Sqlite3.h"

using namespace Wt;

Session::Session(const std::string& sqliteDb)
{
  auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);
  setConnection(std::move(connection));

  mapClass<User>("user");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");

  try {
    createTables();
    std::cerr << "Created database." << std::endl;
  } catch (Wt::Dbo::Exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Using existing database";
  }

  users_ = std::make_unique<UserDatabase>(*this);
}

namespace {
  Wt::Auth::AuthService myAuthService;
  Wt::Auth::PasswordService myPasswordService{myAuthService};
  std::vector<std::unique_ptr<Wt::Auth::OAuthService>> myOAuth;
}

void Session::configureAuth()
{
  myAuthService.setAuthTokensEnabled(true, "logincookie");
  myAuthService.setEmailVerificationEnabled(true);
  myAuthService.setEmailVerificationRequired(true);

  std::unique_ptr<Wt::Auth::PasswordVerifier> verifier =
    std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(7));
  myPasswordService.setVerifier(std::move(verifier));
  myPasswordService.setAttemptThrottlingEnabled(true);
  myPasswordService.setStrengthValidator(std::make_unique<Wt::Auth::PasswordStrengthValidator>());
}

Wt::Auth::AbstractUserDatabase& Session::users()
{
  return *users_;
}

const Wt::Auth::AuthService& Session::auth()
{
  return myAuthService;
}

const Wt::Auth::PasswordService& Session::passwordAuth()
{
  return myPasswordService;
}

const std::vector<const Wt::Auth::OAuthService *>& Session::oAuth()
{
  std::vector<const Wt::Auth::OAuthService *> result;
#if 0
  for (auto &auth : myOAuthServices) {
    result.push_back(auth.get());
  }
#endif
  return result;
}

/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#include "nsMessenger.h"
#include "nsIAppShellComponent.h"
#include "nsIServiceManager.h"
#include "nsMessengerNameSet.h"
#include "nsIScriptNameSetRegistry.h"

#include "nsDOMCID.h"

static NS_DEFINE_IID(kCScriptNameSetRegistryCID, NS_SCRIPT_NAMESET_REGISTRY_CID);

class nsMessengerBootstrap : public nsIAppShellComponent {
  
public:
  nsMessengerBootstrap();
  virtual ~nsMessengerBootstrap();
  
  NS_DECL_ISUPPORTS
  
  NS_DECL_IAPPSHELLCOMPONENT
  
};

NS_IMPL_ISUPPORTS(nsMessengerBootstrap, nsIAppShellComponent::GetIID())

nsMessengerBootstrap::nsMessengerBootstrap()
{
  NS_INIT_REFCNT();
  
}

nsMessengerBootstrap::~nsMessengerBootstrap()
{
}

nsresult
nsMessengerBootstrap::Initialize(nsIAppShellService*,
                                 nsICmdLineService*)
{
  nsresult rv;

  printf("Messenger has been bootstrapped!\n");
  NS_WITH_SERVICE(nsIScriptNameSetRegistry, registry, kCScriptNameSetRegistryCID, &rv); 

  if (NS_FAILED(rv)) return rv;
  
  nsMessengerNameSet* nameSet = new nsMessengerNameSet();
  
  if (nameSet == nsnull)
    rv = NS_ERROR_OUT_OF_MEMORY;
  else
    rv = registry->AddExternalNameSet(nameSet);

  return rv;
}


nsresult
NS_NewMessengerBootstrap(const nsIID &aIID, void ** msgboot)
{
  if (!msgboot) return NS_ERROR_NULL_POINTER;
  
  nsMessengerBootstrap *bootstrap =
    new nsMessengerBootstrap();

  if (!bootstrap) return NS_ERROR_OUT_OF_MEMORY;

  
  return bootstrap->QueryInterface(aIID, msgboot);
}


//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "WolfTestApp.h"
#include "WolfApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<WolfTestApp>()
{
  InputParameters params = validParams<WolfApp>();
  return params;
}

WolfTestApp::WolfTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  WolfApp::registerObjectDepends(_factory);
  WolfApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  WolfApp::associateSyntaxDepends(_syntax, _action_factory);
  WolfApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  WolfApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    WolfTestApp::registerObjects(_factory);
    WolfTestApp::associateSyntax(_syntax, _action_factory);
    WolfTestApp::registerExecFlags(_factory);
  }
}

WolfTestApp::~WolfTestApp() {}

void
WolfTestApp::registerApps()
{
  registerApp(WolfApp);
  registerApp(WolfTestApp);
}

void
WolfTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
WolfTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
WolfTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
WolfTestApp__registerApps()
{
  WolfTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
WolfTestApp__registerObjects(Factory & factory)
{
  WolfTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
WolfTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  WolfTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
WolfTestApp__registerExecFlags(Factory & factory)
{
  WolfTestApp::registerExecFlags(factory);
}

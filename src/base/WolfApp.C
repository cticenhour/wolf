#include "WolfApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<WolfApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

WolfApp::WolfApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  WolfApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  WolfApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  WolfApp::registerExecFlags(_factory);
}

WolfApp::~WolfApp() {}

void
WolfApp::registerApps()
{
  registerApp(WolfApp);
}

void
WolfApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"WolfApp"});
}

void
WolfApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"WolfApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
WolfApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
WolfApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
WolfApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
WolfApp__registerApps()
{
  WolfApp::registerApps();
}

extern "C" void
WolfApp__registerObjects(Factory & factory)
{
  WolfApp::registerObjects(factory);
}

extern "C" void
WolfApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  WolfApp::associateSyntax(syntax, action_factory);
}

extern "C" void
WolfApp__registerExecFlags(Factory & factory)
{
  WolfApp::registerExecFlags(factory);
}

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
*/

#include "application.h"
#include "client.h"

#include "gambc.h"

#include "Camera.h"

bool startfullscreen = false;
int buttonsize = 64;

Application::Application(CefRefPtr<Client> client, std::shared_ptr<Helper::Paths> paths)
  : INIT_LOGGER(Application),
    _client(client),
    _paths(paths),    
    _jsMessageQueue(this),
    _mainWindow(NULL),
    _pluginManager(new PluginManager(this))
{
  // load and parse config and fill configured plugins
  boost::filesystem::path config_path = _paths->getApplicationDir();
  config_path /= "config.xml";
  _config = new Config(config_path, _pluginManager);
}

Application::~Application()
{

}


void Application::OnContextInitialized()
{ 
  std::string startup_document = _config->startDocument();

  // test if absolute url with http or https
  if(boost::starts_with(startup_document, "http://") || boost::starts_with(startup_document, "https://"))
  {
    _startupUrl = startup_document;
  }
  else
  {
    std::string www_dir = _paths->getApplicationDir().generic_string();
    www_dir += "/www";
    if(!boost::starts_with(www_dir, "/"))
      www_dir = "/" + www_dir;
    _startupUrl = "file://" + www_dir + "/" + startup_document; 
  }


  CefWindowInfo info;
  bool transparent = true;

  bool offscreenrendering = false;
  config()->getBoolPreference("OffScreenRendering", offscreenrendering);
  
  config()->getBoolPreference("StartFullScreen", startfullscreen);
  config()->getIntPreference("ButtonSize", buttonsize);

  if(offscreenrendering) 
  {
    CefRefPtr<Client::RenderHandler> osr_window = createOSRWindow(_mainWindow, _client.get(), transparent);
    _client->setOSRHandler(osr_window);
    /* old
    info.SetTransparentPainting(transparent ? true : false);
    info.SetAsOffScreen(osr_window->handle());
    */
    info.SetAsWindowless(osr_window->handle(), transparent);
  }
  else
  {
    RECT rect;
    GetClientRect(_mainWindow, &rect);
    info.SetAsChild(_mainWindow, rect);
  }

  
  /*
  RECT r;
  r.left = 0; r.top = 0; r.right = 700; r.bottom = 500;
  info.SetAsChild(_mainWindow, r);
  */
  
  //TODO: move the settings into config.xml
  CefBrowserSettings browserSettings;
  //browserSettings.developer_tools = STATE_ENABLED;
  browserSettings.file_access_from_file_urls = STATE_ENABLED;
  browserSettings.universal_access_from_file_urls = STATE_ENABLED;
  browserSettings.web_security = STATE_DISABLED;

  // init plugin manager (also create the plugins with onload=true)
  _pluginManager->init();

  // setup gambit
  setup_gambit();
  test_gambit();

  // Create the browser asynchronously and load the startup url
  LOG_DEBUG(logger()) << "create browser with startup url: '" << _startupUrl << "'";

  // FM: Create the browser syncronously instead and start in full screen mode
  CefBrowserHost::CreateBrowserSync(info, _client.get(), _startupUrl, browserSettings, NULL);
  if (startfullscreen)
	  _client.get()->toggleFullScreen(_client.get()->GetBrowser()->GetHost()->GetWindowHandle(), false);
  ShowWindow(_mainWindow, SW_SHOW );
}

void Application::OnContextCreated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context )
{
  CefRefPtr<CefV8Value> global = context->GetGlobal();
  _exposedJSObject = CefV8Value::CreateObject(NULL);
  CefRefPtr<CefV8Value> exec = CefV8Value::CreateFunction("exec", this);
  _exposedJSObject->SetValue("exec", exec, V8_PROPERTY_ATTRIBUTE_READONLY);
  global->SetValue("_cordovaNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
  
  _exposedJSObject = CefV8Value::CreateObject(NULL);
  CefRefPtr<CefV8Value> camera = CefV8Value::CreateFunction("camera", this);
  _exposedJSObject->SetValue("camera", camera, V8_PROPERTY_ATTRIBUTE_READONLY);
  global->SetValue("_cameraNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
  
  _exposedJSObject = CefV8Value::CreateObject(NULL);
  CefRefPtr<CefV8Value> eval = CefV8Value::CreateFunction("eval", this);
  _exposedJSObject->SetValue("eval", eval, V8_PROPERTY_ATTRIBUTE_READONLY);
  global->SetValue("_evalNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
  
  _exposedJSObject = CefV8Value::CreateObject(NULL);
  CefRefPtr<CefV8Value> quit = CefV8Value::CreateFunction("quit", this);
  _exposedJSObject->SetValue("quit", quit, V8_PROPERTY_ATTRIBUTE_READONLY);
  global->SetValue("_quitNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
}

void Application::OnContextReleased( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context )
{
	// cleanup gambit
	cleanup_gambit();
}

CefRefPtr<CefV8Value> callback_func;
CefRefPtr<CefV8Context> callback_context;

void CameraDone(int code, wchar_t* filename)
{
	CefV8ValueList args;
	CefRefPtr<CefV8Value> num = CefV8Value::CreateInt(code);
	CefRefPtr<CefV8Value> str = CefV8Value::CreateString(filename);
	args.push_back(num);
	args.push_back(str);
	callback_func->ExecuteFunctionWithContext(callback_context, NULL, args);
}

// quicky
extern void eval_string (char*);

bool Application::Execute( const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception )
{
  if(name == "exec" && arguments.size() == 4)
  {
    std::string service = arguments[0]->GetStringValue().ToString();
    std::string action  = arguments[1]->GetStringValue().ToString();
    std::string callbackId = arguments[2]->GetStringValue().ToString();
    std::string rawArgs = arguments[3]->GetStringValue().ToString();
    _pluginManager->exec(service, action, callbackId, rawArgs);
    return true;
  }
  if(name == "camera" && arguments.size() == 1 && arguments[0]->IsFunction())
  {
	  callback_func = arguments[0];
      callback_context = CefV8Context::GetCurrentContext();
	  CameraCapture(startfullscreen, buttonsize, &CameraDone);
	  return true;
  }
  if(name == "eval" && arguments.size() == 1)
  {
	  std::string str = arguments[0]->GetStringValue().ToString();
	  const char* c = str.c_str();
	  // std::wstring widestr = std::wstring(str.begin(), str.end());
	  // MessageBox(NULL, widestr.c_str(), NULL, 0);
	  eval_string((char*) c);
	  return true;
  }
  if(name == "quit" && arguments.size() == 0)
  {
      CefRefPtr<CefBrowser> browser = _client->GetBrowser();
	  browser->GetHost()->CloseBrowser(false);
	  return true;
  }
  return false;
}

void Application::sendJavascript( const std::string& statement )
{
  _jsMessageQueue.addJavaScript(statement);
}

void Application::sendPluginResult( std::shared_ptr<const PluginResult> pluginResult, const std::string& callbackId )
{
  _jsMessageQueue.addPluginResult(pluginResult, callbackId);
}

void Application::runJavaScript( const std::string& js )
{
  _client->runJavaScript(js);
}

void Application::handlePause()
{
  runJavaScript("cordova.fireDocumentEvent('pause');");
}

void Application::handleResume()
{
  runJavaScript("cordova.fireDocumentEvent('resume');");
}

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
#include "utils.h"

#include "gambc.h"
#include "mylib.h"

#include "Camera.h"

const char* startupDir;
bool startfullscreen = false;
int buttonsize = 64;

#ifdef SHOWDEBUG
#include <Strsafe.h>
void ShowDebug(PCTSTR format, ...)
{
    va_list args;
    va_start(args, format);

    TCHAR string[MAX_PATH];

    StringCbVPrintf(string, sizeof(string), format, args);
    
	MessageBox(NULL, string, NULL, MB_OK);
}
#endif

Application* currentApp;

CefRefPtr<CefV8Context> globalContext;
CefRefPtr<CefV8Value> globalGlobal;

//ExecuteJavaScript
//NEED TO USE EXECUTEJAVASCRIPT AND NOT RELY ON ANY RETURN VALUE
//WORST CASE SCENARIO WE CAN RETURN AND WAIT ON A VALUE BY A CALLBACK TO SCHEME

void call_js(char* expr)
{
	currentApp->runJavaScript(expr);
}

void register_export(char* name, int type)
{
	currentApp->registerExport(name, type);
}

/*
CefRefPtr<CefV8Value> blabla;
void call_js(char* expr)
{
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefString code;
	CefRefPtr<CefV8Value> retval;
	CefRefPtr<CefV8Exception> exception;
	code.FromString(expr);
	context->Eval(code, retval, exception);
	blabla = retval;
	if (!retval)
		return NULL;
	else
	{
		char* result = (char*) retval->GetStringValue().ToString().c_str();
		return result;
	}
}*/
/*
const char* call_js2(char* expr)
{
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefString code;
	CefRefPtr<CefV8Value> retval;
	CefRefPtr<CefV8Exception> exception;
	code.FromString(expr);
	context->Eval(code, retval, exception);
	blabla = retval;
	if (!retval)
		return NULL;
	else
	{
		const char* result = retval->GetStringValue().ToString().c_str();
		return result;
	}
}*/

Application::Application(CefRefPtr<Client> client, std::shared_ptr<Helper::Paths> paths)
  : INIT_LOGGER(Application),
    _client(client),
    _paths(paths),    
    _jsMessageQueue(this),
    _mainWindow(NULL),
    _pluginManager(new PluginManager(this))
{
  // printlog("*****");
  // load and parse config and fill configured plugins
  boost::filesystem::path config_path = _paths->getApplicationDir();
  config_path /= "config.xml";
  _config = new Config(config_path, _pluginManager);
}

Application::~Application()
{

}


// seems that cef can call the window procedure from a thread
CRITICAL_SECTION gambit_critical_section; 


void safe_gambit_eval_string_void(char* str)
{
	EnterCriticalSection(&gambit_critical_section);
	gambit_eval_string_void(str);
	LeaveCriticalSection(&gambit_critical_section);
}


int safe_gambit_eval_string_int(char* str)
{
	EnterCriticalSection(&gambit_critical_section);
	int result = gambit_eval_string_int(str);
	LeaveCriticalSection(&gambit_critical_section);
	return result;
}


char* safe_gambit_eval_string_string(char* str)
{
	EnterCriticalSection(&gambit_critical_section);
	char* result = gambit_eval_string_string(str);
	LeaveCriticalSection(&gambit_critical_section);
	return result;
}


char* safe_gambit_eval_string(char* str)
{
	EnterCriticalSection(&gambit_critical_section);
	char* result = gambit_eval_string(str);
	LeaveCriticalSection(&gambit_critical_section);
	return result;
}


char* safe_gambit_eval_string_catch(char* str)
{
	EnterCriticalSection(&gambit_critical_section);
	char* result = gambit_eval_string_catch(str);
	LeaveCriticalSection(&gambit_critical_section);
	return result;
}


void safe_gambit_heartbeat()
{
	EnterCriticalSection(&gambit_critical_section);
	gambit_heartbeat();
	LeaveCriticalSection(&gambit_critical_section);
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
		std::string www, www_devel;
	  
		config()->getStringPreference("www", www);
		config()->getStringPreference("www_devel", www_devel);
		std::string www_dir = _paths->getApplicationDir().generic_string();
		www_dir += "/";
		www_dir += www;
		if(!boost::starts_with(www_dir, "/"))
			www_dir = "/" + www_dir;
		_startupDir = "file://" + www_dir + "/";
		_startupUrl = "file://" + www_dir + "/" + startup_document;

		if (!boost::filesystem::exists( _startupUrl ))
		{
			std::string www_dir = _paths->getApplicationDir().generic_string();
			www_dir += "/";
			www_dir += www_devel;
			if(!boost::starts_with(www_dir, "/"))
				www_dir = "/" + www_dir;
			_startupDir = "file://" + www_dir + "/";
			_startupUrl = _startupDir + startup_document;
		}

		startupDir = _startupDir.c_str();
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
  InitializeCriticalSection(&gambit_critical_section);
  setup_gambit();

  // Create the browser asynchronously and load the startup url
  LOG_DEBUG(logger()) << "create browser with startup url: '" << _startupUrl << "'";

  // FM: Create the browser syncronously instead and start in full screen mode
  CefBrowserHost::CreateBrowserSync(info, _client.get(), _startupUrl, browserSettings, NULL);
  if (startfullscreen)
	  _client.get()->toggleFullScreen(_client.get()->GetBrowser()->GetHost()->GetWindowHandle(), false);
  ShowWindow(_mainWindow, SW_SHOW );

  currentApp = this;
}

void Application::OnContextCreated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context )
{
	globalContext = context;
	globalGlobal = context->GetGlobal();

	CefRefPtr<CefV8Value> global = context->GetGlobal();
	_exposedJSObject = CefV8Value::CreateObject(NULL);
	CefRefPtr<CefV8Value> exec = CefV8Value::CreateFunction("exec", this);
	_exposedJSObject->SetValue("exec", exec, V8_PROPERTY_ATTRIBUTE_READONLY);
	global->SetValue("_cordovaNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
  
	_exposedJSObject = CefV8Value::CreateObject(NULL);
	global->SetValue("_cameraNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
	CefRefPtr<CefV8Value> camera = CefV8Value::CreateFunction("camera", this);
	_exposedJSObject->SetValue("camera", camera, V8_PROPERTY_ATTRIBUTE_READONLY);
	CefRefPtr<CefV8Value> cameraAvailable = CefV8Value::CreateFunction("cameraAvailable", this);
	_exposedJSObject->SetValue("cameraAvailable", cameraAvailable, V8_PROPERTY_ATTRIBUTE_READONLY);
  
	global->SetValue("evalnative", CefV8Value::CreateFunction("eval", this), V8_PROPERTY_ATTRIBUTE_READONLY);
	global->SetValue("evalcatchnative", CefV8Value::CreateFunction("evalcatch", this), V8_PROPERTY_ATTRIBUTE_READONLY);
  
	_exposedJSObject = CefV8Value::CreateObject(NULL);
	CefRefPtr<CefV8Value> quit = CefV8Value::CreateFunction("quit", this);
	_exposedJSObject->SetValue("quit", quit, V8_PROPERTY_ATTRIBUTE_READONLY);
	global->SetValue("_quitNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);

	_exposedJSObject = CefV8Value::CreateObject(NULL);
	CefRefPtr<CefV8Value> devtools = CefV8Value::CreateFunction("devtools", this);
	_exposedJSObject->SetValue("devtools", devtools, V8_PROPERTY_ATTRIBUTE_READONLY);
	global->SetValue("_devtoolsNative", _exposedJSObject, V8_PROPERTY_ATTRIBUTE_READONLY);
  
	global->SetValue("testnative", CefV8Value::CreateFunction("test", this), V8_PROPERTY_ATTRIBUTE_READONLY);
}

void Application::OnContextReleased( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context )
{
	// this does not go here as it is called for each closed window
	// it should go in a OnContextDestroyed method corresponding to OnContextInitialized
	// cleanup gambit
	// cleanup_gambit();
	// DeleteCriticalSection(&gambit_critical_section);
}

bool CameraAvailable()
{
	HMODULE lib;

	lib = LoadLibrary(L"Mfplat.dll");
	if (lib)
	{
		FARPROC proc = GetProcAddress(lib, "MFCreateDXGIDeviceManager");
		if (proc)
			return true;
		else
			return false;
	}
	else
		return false;
}

typedef void (*CameraCaptureType)(const char*, bool, int, CameraDoneCallback);

void CameraCapture(const char* startupDir, bool startfullscreen, int buttonsize, CameraDoneCallback callback)
{
	HMODULE lib;

	lib = LoadLibrary(L"Camera.dll");
	CameraCaptureType proc = (CameraCaptureType) GetProcAddress(lib, "CameraCapture");

	(proc)(startupDir, startfullscreen, buttonsize, callback);
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

bool doLog = false;
FILE *logFP = NULL;

void logSetup()
{
	if (doLog && !logFP)
		logFP=fopen("c:\\Home\\log.txt", "w");
}

#include <map>

using namespace std;

map <string, int> exports;

void Application::registerExport(char* name, int type)
{
	CefRefPtr<CefV8Context> context = globalContext; // CefV8Context::GetCurrentContext();
    CefRefPtr<CefV8Value> global = globalGlobal; // context->GetGlobal();
	global->SetValue(name, CefV8Value::CreateFunction(name, this), V8_PROPERTY_ATTRIBUTE_READONLY);
	exports[name] = type;
}

bool Application::Execute( const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception )
{
	auto exported = exports.find(name.ToString());
	if(exported != exports.end())
	{
		if (exported->second == -1)
		{
			stringstream stream;
			stream << "(";
			stream << exported->first;
			int size = (int) arguments.size();
			for (int n = 0; n < size; n++)
			{
				stream << " ";
				stream << "\"";
				stream << arguments[n]->GetStringValue().ToString();
				stream << "\"";
			}
			stream << ")";
			safe_gambit_eval_string_void((char*) (stream.str().c_str()));
			return true;
		}
		else
		switch (exported->second)
		{
		case 0:
			{
				int result = safe_gambit_eval_string_int((char*) exported->first.c_str());
				retval = CefV8Value::CreateBool((result == 0) ? false : true);
				return true;
			}
		case 1:
			{
				int result = safe_gambit_eval_string_int((char*) exported->first.c_str());
				retval = CefV8Value::CreateInt(result);
				return true;
			}
		case 2:
			{
				char* result = safe_gambit_eval_string_string((char*) exported->first.c_str());
				retval = CefV8Value::CreateString(result);
				return true;
			}
		case 9:
			{
				retval = CefV8Value::CreateUndefined();
				return true;
			}
		}
	}

  if(name == "exec" && arguments.size() == 4)
  {
    std::string service = arguments[0]->GetStringValue().ToString();
    std::string action  = arguments[1]->GetStringValue().ToString();
    std::string callbackId = arguments[2]->GetStringValue().ToString();
    std::string rawArgs = arguments[3]->GetStringValue().ToString();
    _pluginManager->exec(service, action, callbackId, rawArgs);
    return true;
  }
  if(name == "cameraAvailable" && arguments.size() == 0)
  {
	  retval = CefV8Value::CreateBool(CameraAvailable());
	  return true;
  }
  if(name == "camera" && arguments.size() == 1 && arguments[0]->IsFunction())
  {
	  if (CameraAvailable())
	  {
		  callback_func = arguments[0];
		  callback_context = CefV8Context::GetCurrentContext();
		  CameraCapture(startupDir, startfullscreen, buttonsize, &CameraDone);
	  }
	  return true;
  }
  if(name == "eval" && arguments.size() == 1)
  {
	  std::string str = arguments[0]->GetStringValue().ToString();
	  const char* c = str.c_str();
	  std::string res = safe_gambit_eval_string((char*) c);
	  std::wstring reswide = std::wstring(res.begin(), res.end());
	  retval = CefV8Value::CreateString(reswide.c_str());
	  return true;
  }
  if(name == "evalcatch" && arguments.size() == 1)
  {
	  std::string str = arguments[0]->GetStringValue().ToString();
	  const char* c = str.c_str();
	  std::string res = safe_gambit_eval_string_catch((char*) c);
	  std::wstring reswide = std::wstring(res.begin(), res.end());
	  retval = CefV8Value::CreateString(reswide.c_str());
	  return true;
  }
  if(name == "quit" && arguments.size() == 0)
  {
      CefRefPtr<CefBrowser> browser = _client->GetBrowser();
	  browser->GetHost()->CloseBrowser(false);
	  return true;
  }
  if (name == "devtools" && arguments.size() == 0)
  {
	  CefRefPtr<CefBrowser> browser = _client->GetBrowser();
	  _client->showDevTools(browser);
	  return true;
  }
  if(name == "test" && arguments.size() == 0)
  {
	  /* const char* result = call_js2("toto()");
	  //const char* result = "blabla";
	  std::string res = result;
	  std::wstring reswide = std::wstring(res.begin(), res.end());
	  retval = CefV8Value::CreateString(reswide.c_str());
	  //retval = blabla; // CefV8Value::CreateString(result); */
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

void Application::handleTimer()
{
	safe_gambit_heartbeat();
}

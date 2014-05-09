
///
//// Sentio boot
///


///
//// constants
///


var TotalWidth=1280;
var TotalHeight=800;
var Mobile=false;

///
//// init
///


function initApplication()
{
	initDetectionMode();
	runAdjustmentsScripts();
	//getNextServerPushLoop();
}

function detectmob() { 
 if( navigator.userAgent.match(/Android/i)
 || navigator.userAgent.match(/webOS/i)
 || navigator.userAgent.match(/iPhone/i)
 || navigator.userAgent.match(/iPad/i)
 || navigator.userAgent.match(/iPod/i)
 || navigator.userAgent.match(/BlackBerry/i)
 || navigator.userAgent.match(/Windows Phone/i)
 ){
    return true;
  }
 else {
    return false;
  }
}


///
//// boot
///


function boot()
{
	// boot the scheme program
	
	initApplication();
	bootScheme();
	TotalWidth=getTotalWidth();
	TotalHeight=getTotalHeight();
	//StartSyncLoop();
	StartConnectivityTestLoop();
	//setTimeout(function(){ window.location.reload() }, 600);
}

///
//// do start the boot process when browser is ready
///


function onDeviceReady()
{
	console.log("***APPTRANSITION***: Device Ready");
	cordovaInitialized=true;
	boot();
}


function onPause()
{
	console.log("***APPTRANSITION***: Pause");
}

function onResume()
{
	console.log("***APPTRANSITION***: Resume");
}


var cordovaInitialized=false;

function cordovaTimeout()
{
	if(!cordovaInitialized) 
	{
		console.log("***APPTRANSITION***: No connection to device... Starting in browser mode.");
		boot();
	}
}


$(document).ready( function() {
								console.log("document ready!");
								document.addEventListener("deviceready", onDeviceReady, false);
								document.addEventListener("pause", onPause, false);
								document.addEventListener("resume", onResume, false);
								setTimeout( cordovaTimeout , 4000 );
							  });






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
	registerDBChangeListeners();
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
	//bootScheme();
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


///
//// main
///

var TotalWidth=screen.width;
var TotalHeight=screen.height;


function showSplash()
{
	TotalWidth=screen.width;
	TotalHeight=screen.height;
	Pablo("#main").attr('width', TotalWidth);
	Pablo("#main").attr('height', TotalHeight);
	var lx=(TotalWidth-321)/2;
	var ly=(TotalHeight-305-100)/2;
	Pablo("#outerContent").rect({id: "splashBack", x: 0, y: 0, width: TotalWidth, height: TotalHeight, fill: "url(#splashFill)"});
	var g1=Pablo("#outerContent").g({id: "splashContent"});
	var logoCode='<image x="'+lx+'" y="'+ly+'" width="321" height="305" xlink:href="img/ath-splash-logo.svg"/>';
	var logo=Pablo(logoCode);
	g1.append(logo);
	var g2=g1.g();
	var tx=(TotalWidth-600)/2;
	var ty=(ly+305+25);

	console.log(tx+" "+ty);
	//console.log({width: (- TotalWidth 600)+"px", height: "40px", x: "50px", y: (ly+305+25)+"px", fill: "white"});

	g2.rect({rx: 15, ry: 15, width: "600px", height: "40px", x: tx , y: ty, fill: "white", "fill-opacity": 0.5});
	g2.text({id: "statusText", x: TotalWidth/2, y: ty+30, "text-anchor": "middle", "font-family": "source_sans_proregular", "font-weight": "regular", "font-size": "30" });
	Pablo("#statusText").content("Booting Sentio...")

	var syncIcon=Pablo(syncIconCode(TotalWidth-60,TotalHeight-60,1));
	Pablo("#outerContent").append(syncIcon);

	var logoutIcon=Pablo(logoutButton(TotalWidth-50,50,40,"yellow"));
	var loi=Pablo("#outerContent").append(logoutIcon);

	initDetectionMode();
	
	//console.log(logoCode);
	firstSetup();
}


///
//// firstSetup
///


function setBootMessage(m)
{
	Pablo("#statusText").content(m); 
}


function showDBFailure()
{
	setBootMessage("Error: could not contact CouchDB");
}

function firstSetup()
{
	$.getJSON( "http://127.0.0.1:5984/", 	function(data) 
										 	{  
												if(data.uuid) continueStep2(); else showDBFailure(); 
											} ).fail(showDBFailure);
}


function continueStep2()
{
	var db=getDatabase("cds_employee");
	db.get('93a24129d6395683657294a54c4f297b',{},function(err,data) { if(!err && data.iID=="ID5767664739853_1398737492055249") continueStep3(); else setupDBSync();  });
}


function setupDBSync()
{
	setBootMessage("Setting up synchronization...");
	setupSync();
}


var syncEndInterval;

function continueStep3()
{
	setBootMessage("Syncing data...");
	syncEndInterval=setInterval(checkSyncEnd,1000);
}


function checkSyncEnd()
{
	$.getJSON("http://localhost:5984/_active_tasks",function(data) { checkProcessCompletion(data); });
}


function checkProcessCompletion(processes)
{
	var done=true;
	
	for(var i=0;i<processes.length;i++)
	{
		if(processes[i].progress!=0 &&  processes[i].progress!=100) done=false;
	}
	if(done)
	{
		clearInterval(syncEndInterval);
		continueStep4();
	}
}



function continueStep4()
{
	bootScheme();
}


///
//// handleMediaJS
///


function handleMediaJS(status,path)
{
	console.log("handle media js");
	console.log(path);
	console.log(path.split("\\").join("/"));
	handleMedia(status,path.split("\\").join("/"));
}


///
//// main
///


$(document).ready( function() {
								console.log("document ready!");
								showSplash();
								document.addEventListener("deviceready", onDeviceReady, false);
								document.addEventListener("pause", onPause, false);
								document.addEventListener("resume", onResume, false);
								setTimeout( cordovaTimeout , 4000 );
							  });





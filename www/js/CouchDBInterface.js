/////////////////////////////////
///  Experimentation notes:
///
///  
///  Replication problems when using password protected API?
///  Cannot start many sync requests in parallel... freezes the browser
///  Must be controlled using promises.
///
///  Need to transfer this to the scheme world for better control over different target 
///  implementations (eventually write an uniform API for DB access CouchDB ou PouchDB)


// Benchmark
// 
// wo table construction:
//
// http (no views): 2152ms
// websql (no views): 3679ms
//


///
//// getDatabase
///

// This accessor is mainly for selecting the adapter at a global level.


function getDatabase(name)
{
	return new PouchDB("http://localhost:5984/"+name,{adapter : 'http'});
	//return new PouchDB(name,{adapter : 'websql'}); 
}


///
//// CouchDB (PouchDB) tests
///


var databases  = ["amt_tasks_groups","amt_tasks_periodic_inspection","cds_activities_status","cds_attachment","cds_competencies_values","cds_employee","cds_employee_status_values","cds_file_type","cds_input_data","cds_input_data_instance","cds_input_type","cds_instances_types","cds_priority_values","cds_role","cds_site_location","cds_state_transitions","cds_task_instance","cds_tasktypes","cds_track","cds_workorder","cds_task"];

///
//// Connectivity test
///



function StartConnectivityTestLoop()
{
	setInterval(testConnectivity,1000*15); // try every fifteen seconds
}


function testConnectivity()
{
	$.getJSON( "http://54.83.18.50:8000/", function(data) { if(data.uuid=="c1cb33553de833e0d9c44431a3c9a58c") showNetworkNormal(); else showNetworkFailure(); })
  					  .fail(function() { showNetworkFailure(); });
}


function showNetworkNormal()
{
	if(!inSync)	$(".syncwheel").attr('fill',"rgb(80%,80%,80%)");
}

function showNetworkFailure()
{
	if(inSync) stopSyncAnimation();
	inSync=false;
	$(".syncwheel").attr('fill','red');
}


///
//// Syncing
///


var inSync=false;


function StartSyncLoop()
{
	$(".cup").attr('visibility','hidden');
	$(".cdown").attr('visibility','hidden');
	setInterval(TrySync,1000*60); // try every five minutes
}


function TrySync()
{
	if(!inSync) Sync();
}


function Sync()
{
/*
  var i=0;
  inSync=true;
  var iteration;
  shouldContinue=true;
  startSyncAnimation();	
  iteration=function(i) {  return function() { if(i<databases.length) syncWithRemote(false,databases[i],iteration(i+1)); else initialSyncDone(); }; };
  iteration(0)();
*/
}

function initialSyncDone()
{
  stopSyncAnimation();	
  inSync=false;
  console.log("Initial sync done.");
  console.log("Turning autosync on");
  //continuousSync();
}

var shouldContinue=false;

function startSyncAnimation()
{
	var sunRays = Snap.select('text.syncwheel');
	$(".syncwheel").attr('fill','rgb(20%,20%,20%)');
	sunRays.stop().animate(
			{ transform: 'r360,20,3'}, // Basic rotation around a point. No frills.
			10000, // Nice slow turning rays
			function(){ 
				sunRays.attr({ transform: 'rotate(0 20 3)'}); // Reset the position of the rays.
				if(shouldContinue) startSyncAnimation(); // Repeat this animation so it appears infinite.
				else $(".syncwheel").attr('fill','rgb(80%,80%,80%)');
			}
		);
	
}

function stopSyncAnimation()
{
	shouldContinue=false;	
	$(".cup").attr('visibility','hidden');
	$(".cdown").attr('visibility','hidden');
}




function continuousSync()
{
  var i=0;

  var iteration;

  iteration=function(i) {  return function() { if(i<databases.length) syncWithRemote(true,databases[i],iteration(i+1)); }; };
  iteration(0)();
}

function syncWithRemote(cont,cID,donecallback)
{
	var remoteCouch='http://54.83.18.50:8000/'+ cID;
	//var remoteCouch='http://10.0.1.3:5984/'+ cID;
	console.log("Sync "+ cID+ " to master");
	
	var db = getDatabase(cID);
	var options;
	$(".cup").attr('visibility','visible');
	$(".cdown").attr('visibility','hidden');

	if(cont) options={  continuous: true };
	else options={ complete: syncToCompleted(cont,cID,donecallback) };
	if(cont) setTimeout(function() { db.replicate.to(remoteCouch,options); syncToCompleted(cont,cID,donecallback)(); },2000);
	else db.replicate.to(remoteCouch,options);
}



function  syncToCompleted(cont,cID,donecallback)
{
  return function(e,res) {
    console.log(e);
    console.log("Sync to master completed for: "+cID);
    var remoteCouch='http://54.83.18.50:8000/'+ cID;
	//var remoteCouch='http://127.0.0.1:5984/'+ cID;
    console.log("Sync "+ cID+ " from master");
    var db = getDatabase(cID);
	$(".cup").attr('visibility','hidden');
	$(".cdown").attr('visibility','visible');

    if(cont) options={  continuous: true };
    else options={ complete: donecallback };
    if(cont) setTimeout(function() { db.replicate.from(remoteCouch,options); donecallback(); },2000);
    else db.replicate.from(remoteCouch,options);
  };
}


function syncCompleted(e)
{
	inSync=false;
}


function syncError(e)
{
	console.log(e);
}

///
//// allTrue
///


function allTrue(arr)
{
	//console.log("allTrue:"+arr);
	var res=true;
	for(var i=0;i<arr.length;i++)
	{
		if(arr[i]!=true) res=false;
	}
	return res;
}



///
//// basic api 
///


function getFirstLabel(iID,callback)
{
	var locale=CurrentLocale();
	getPropertyValues(	iID,
						'labels',
						function(data)
						{
							//console.log("In getFirstLabel");
							//console.log(iID);
							//console.log(data);
							var res=false;
							for(var i=0;i<data.length;i++)
							{
								if(data[i][0]==locale) res=data[i][1];
							}
							if(res) callback(res);
							else if(data.length>0) callback(data[0][1]);
							else callback("  ");
						});
}


function dd(data)
{
	console.log(data);
}


//getFirstLabel('ID8141631513273_1397959533692503',function(data) { console.log(data); });
// getFirstLabel('ID6082274876723_1394857391435627',function(data){ console.log(data); });
//getPropertyValues('ID9293854962400_1397959533693803','CDS_Task_ParentTask',dd)


function getPropertyValues(iID,pID,callback)
{
	var typesDB= getDatabase('cds_instances_types');
	typesDB.query( 	function(doc) { if(doc.iID && doc.cID) emit(doc.iID,doc.cID); },
				 	{ reduce: false, key: iID },
					function(err,data)
					{
						if(err) callback([]);
						else if(data.rows.length>0) getPropertyValuesInClass(data.rows[0].value,iID,pID,callback);
						else callback([]);
					} );
}

// getPropertyValues("ID1837647907950_1394857390308203","CDS_hasRole",function(data) { console.log(data); });

function getPropertyValuesInClass(cID,iID,pID,callback)
{
	var db = getDatabase(cID);
	eval("var mapCode=function(doc) { if(doc[\""+pID+"\"]) emit(doc.iID,doc[\""+pID+"\"]); }");
	db.query( 	mapCode,
				{ reduce: false, key: iID },
				function(err,data)
				{
					//console.log(data);
					if(err || !data || !data.rows || data.rows.length==0) callback([]);
					else callback(data.rows[0].value);
				} );
}

//getPropertyValues('cds_activity_instance','ID8196957516370_1391750037588536','CDS_Activity_Instance_status',myfct);

function getPropertyValueByIndex(iID,pID,i,callback)
{
	getPropertyValues(iID,pID, function(values) { if(values.length > i) callback(values[i]); else callback(false); });
}

//getPropertyValueByIndex('cds_activity_instance','ID8196957516370_1391750037588536','CDS_Activity_Instance_status',0,myfct);



function getInstances(cID,callback)
{
	var db = getDatabase(cID);
	db.query( 	function(doc) { if(!doc.isArchive || doc.isArchive.length==0) emit(doc.iID,null); },
				{ reduce: false },
				function(err,data) 
				{
					if(err) callback([]);
					else
					{
						if(data.rows) callback(data.rows.map( function(obj) { return obj.key; } ));
						else callback([]);
					}
				} );
}


// getInstances('cds_activity_instance', function(data) { console.log(data); });


function getInstancesInRestriction(cID,restrictions,callback)
{

	//console.log(restrictions);
	var db = getDatabase(cID);

	eval("mapCode=function(doc) { if("+considerDocCondition(restrictions)+") emit("+emitKey(restrictions)+",doc.iID); };");
	db.query( 	mapCode,
				{ reduce: false , key: retrictionsValues(restrictions)},
				function(err,data) 
				{
					if(err) callback([]);
					else
					{
						if(data.rows) callback(data.rows.map( function(obj) { return obj.value; } ));
						else callback([]);
					}
				} );
}

function considerDocCondition(restrictions)
{
	return restrictions.map( function(r) { return "doc."+r[0]; } ).join(" && ");
}


function emitKey(restrictions)
{
	return "["+restrictions.map( function(r) { return "doc."+r[0]+"[0]"; } ).join(",")+"]";
}


function retrictionsValues(restrictions)
{
	return restrictions.map( function(r) { return r[1]; } );
}



///
//// tests
///


function benchmarkWebSQL()
{
	var typesDB=new PouchDB('cds_instances_types');
	var iID="ID5767664739853_1397959533392024";
	var stime=new Date();
	typesDB.query( 	function(doc) { if(doc.iID && doc.cID) emit(doc.iID,doc.cID); },
				 	{ reduce: false, key: iID },
					function(err,data)
					{
						var etime=new Date();
						console.log(data);
						console.log(etime-stime);
					} );

}

function benchmarkHTTP()
{
	var typesDB=new PouchDB('cds_employee', {adapter : 'http'}); //'http://localhost:5984/cds_employee'
	var iID="ID5767664739853_1397959533392024";
	var stime=new Date();
	typesDB.query( 	function(doc) { if(doc.iID && doc.cID) emit(doc.iID,doc.cID); },
				 	{ reduce: false, key: iID },
					function(err,data)
					{
						var etime=new Date();
						console.log(data);
						console.log(etime-stime);
					} );

}



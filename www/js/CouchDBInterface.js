/////////////////////////////////
///  Experimentation notes:
///
///  PouchDB: (IndexedDB mode)
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


var databases  = ["amt_tasks_groups","amt_tasks_periodic_inspection","cds_activities_status","cds_attachment","cds_competencies_values","cds_employee","cds_employee_status_values","cds_file_type","cds_input_data","cds_input_data_instance","cds_input_type","cds_instances_types","cds_form_instances","cds_forms","cds_priority_values","cds_role","cds_site_location","cds_state_transitions","cds_taskinstance","cds_tasktypes","cds_track","cds_workorder","cds_wocategories" ,"cds_task","cds_note"];



var syncCompleteIndicatorDatabases = ["cds_activities_status","cds_attachment","cds_competencies_values","cds_employee","cds_employee_status_values","cds_file_type","cds_input_data","cds_input_type","cds_instances_types","cds_priority_values","cds_role","cds_site_location","cds_state_transitions","cds_taskinstance","cds_tasktypes","cds_track","cds_workorder","cds_task"];


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


var NetworkAvailabilityStatus;


function showNetworkNormal()
{
	NetworkAvailabilityStatus=true;
	if(!inSync)	$(".syncwheel").attr('fill',"rgb(80%,80%,80%)");

}

function showNetworkFailure()
{
	NetworkAvailabilityStatus=false;
	if(inSync) stopSyncAnimation();
	inSync=false;
	$(".syncwheel").attr('fill','red');
}


///
//// sync setup
///

function detectSyncSetup(callback)
{
	var db=getDatabase("_replicator"); 
	db.query(function(doc) { emit(doc.target,doc._id); },
				 	{ reduce: false, key: "cds_task" },
					function(err,data)
					{
						if(err) callback(false);
						else if(data.rows.length>0) callback(true);
						else callback(false);
					}); 
}


function setupSync()
{

	detectSyncSetup(function(isok) { if(isok) continueStep3(); else setupSyncLoop(); });
}


function setupSyncLoop()
{
	databases.forEach( setupSyncForDB );
	setTimeout(finalizeSetupSync,5000);
}


function finalizeSetupSync()
{
	createViews();
	setTimeout(continueStep3,2000);
}



function setupSyncForDB(cID)
{
	var db=getDatabase("_replicator"); 
	var theID;
	getDatabase(cID);


	
	theID=generateAthenaGUID();
	db.put({ 
					target: cID,
					source: "http://admin:Tanger132@54.83.18.50:8000/"+cID,
					continuous: true,
					"create-target": true
				  },theID);	

	if(cID=="amt_tasks_groups") theID="b3fd63058b767896fe99b35a450008ff";
	else theID=generateAthenaGUID();


	console.log("THE ID:"+theID);

	db.put({ 
					source: cID,
					target: "http://admin:Tanger132@54.83.18.50:8000/"+cID,
					continuous: true,
					"create-target": true
				  },theID); 

	
}




///
//// subscriptions to db changes
///


function registerDBChangeListeners()
{
	getDatabase("cds_taskinstance").changes({ since: 'latest', live: true }).on('change', processTaskInstanceChange); 
	getDatabase("cds_workorder").changes({ since: 'latest', live: true }).on('change', processWOInstanceChange);
}


function processWOInstanceChange()
{
	startSyncAnimation();
	doRefreshWOPage();
	stopSyncAnimation();
}



function processTaskInstanceChange(obj) 
{ 
	console.log("CHANGE in Tasks instances:"); 
	startSyncAnimation();
	db=getDatabase("cds_taskinstance");
	console.log(obj);
	obj.changes.forEach( 	function(change)
							{
								db.get(obj.id,{ rev: change.rev },function(err,doc) { processTaskInstanceChangeDoc(doc);	stopSyncAnimation(); });
							} );

}


function processTaskInstanceChangeDoc(doc)
{
	//console.log(doc);
	changeTaskStatusFillColor(doc.CDS_TaskInstance_Task[0],doc.CDS_TaskInstance_WorkOrder[0],resolveTaskFill(doc.CDS_TaskInstance_Status[0]));
}


function changeTaskStatus(taskID, woID, status)
{
	changeTaskStatusFillColor(taskID,woID,resolveTaskFill(status));
}




function changeTaskStatusFillColor(taskID,woID,newColor)
{
	$(".pstep").each( function(i,pstep) 
						{
							//console.log(pstep);
							var name=$(pstep).attr('name');
							if(name.indexOf("'"+woID+"','"+taskID+"'")>=0 ) $(".taskbox",pstep).attr('fill', newColor);
						});
}



function resolveTaskFill(status)
{
	switch(status)
	{
		case "Status_Active": return "url(#gWait)";  break;
		case "Status_Visited": return "url(#gActive)"; break;
		case "Status_Completed": return "url(#gDone)"; break;
		case "Status_Cancelled": return "url(#gCancelled)"; break;
	}
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

  var i=0;
  inSync=true;
  var iteration;
  shouldContinue=true;
  startSyncAnimation();	
  iteration=function(i) {  return function() { if(i<databases.length) syncWithRemote(false,databases[i],iteration(i+1)); else initialSyncDone(); }; };
  iteration(0)();

}

function initialSyncDone()
{
  stopSyncAnimation();	
  inSync=false;
  alert("Initial sync done.");
  //console.log("Turning autosync on");
  //continuousSync();
}

var shouldContinue=false;
var showingSyncAnim=false;

function startSyncAnimation()
{
	if(!showingSyncAnim && NetworkAvailabilityStatus)
	{
		showingSyncAnim=true;
		var sunRays = Snap.select('text.syncwheel');
		$(".syncwheel").attr('fill','rgb(20%,20%,20%)');
		if(sunRays) sunRays.stop().animate(
					{ transform: 'r360,20,3'}, // Basic rotation around a point. No frills.
					10000, // Nice slow turning rays
					function(){ 
								sunRays.attr({ transform: 'rotate(0 20 3)'}); // Reset the position of the rays.
								if(shouldContinue) startSyncAnimation(); // Repeat this animation so it appears infinite.
								else $(".syncwheel").attr('fill','rgb(80%,80%,80%)');
							}
		);
	}
}

function stopSyncAnimation()
{
	shouldContinue=false;	
	showingSyncAnim=false;
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
	//console.log("Sync "+ cID+ " to master");
	
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
    //console.log(e);
    //console.log("Sync to master completed for: "+cID);
    var remoteCouch='http://54.83.18.50:8000/'+ cID;
	//var remoteCouch='http://127.0.0.1:5984/'+ cID;
    //console.log("Sync "+ cID+ " from master");
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


///
//// createViews
///


function createViews()
{
	databases.forEach( createViewsForDB );
}


function createViewsForDB(cID)
{
	var theDB= getDatabase(cID);
	var theTypesFCT;

	if(cID=='cds_instances_types') theTypesFCT="function(doc)\n{\n\tif(doc.iID && doc.cID) emit(doc.iID,doc.cID);\n}"; 
	else theTypesFCT="function(doc) {}";


	var doCreateView=function(res) { 
										var myIndex = {
  												_id: '_design/sentio',
  												views: {
															'labels': { map: function(doc) { emit(doc.iID,doc.labels); }.toString() },
															'instances': { map: function(doc) { if(!doc.isArchive || doc.isArchive.length==0) emit(doc.iID,null); }.toString() },
    														'instancesProps': { map: function (doc) { for(var pname in doc) emit([doc.iID,pname],doc[pname]); }.toString() },
															'instancesTypes': { map: theTypesFCT },
															'instancesRevisions': { map: function(doc) { emit(doc.iID, doc._rev); }.toString() }
														}
												};

										theDB.put(myIndex);
									};

    doCreateView();
  
  /*
	$.ajax({
    url: 'localhost:5984/'+cID+'/_design/sentio',
    type: 'DELETE',
    success: doCreateView,
	error: doCreateView
 
	});

*/
}


///
//// getFirstType
///


function getFirstType(iID,callback)
{
	var typesDB= getDatabase('cds_instances_types');
	typesDB.query( 	'sentio/instancesTypes',
				 	{ reduce: false, key: iID },
					function(err,data)
					{
						if(err) callback([]);
						else if(data.rows.length>0) callback(data.rows[0].value);
						else callback([]);
					} );
}


///
//// getAttachments
///


function getAttachments(iID,callback)
{
	getFirstType(iID,function(cID) { getAttachmentsWithType(cID,iID,callback); });
}


function getAttachmentsWithType(cID,iID,callback)
{
	var db=getDatabase(cID);
	getInstanceDocID(	cID,
						iID,
						function(docID)
						{
							console.log("docID="+docID);
							db.get(docID,{attachments: true},	function(err,doc) 
																{ 
																	console.log(doc);
																	var firstProp=false;
																	for(prop in doc._attachments)
																	{
																		if(!firstProp) firstProp=prop;
																	}
																	if(doc && doc._attachments) callback("http://localhost:5984/"+ cID +"/"+docID+"/"+firstProp);
																	else callback(false);
																} );


							
						});
}


//getAttachments("ID8605999954361_1401057856319361",function(data) { console.log(data); })

///
//// getInstanceRevision
///



function getInstanceRevision(iID,callback)
{
	getPropertyValues(iID,"_rev",callback)
}




//getFirstLabel('ID8141631513273_1397959533692503',function(data) { console.log(data); });
//getFirstLabel('ID6082274876723_1394857391435627',function(data){ console.log(data); });
//getPropertyValues('ID9293854962400_1397959533693803','CDS_Task_ParentTask',dd)


function getPropertyValues(iID,pID,callback)
{
	getFirstType(iID,function(cID) { getPropertyValuesInClass(cID,iID,pID,callback); });
}


function getPropertyValuesInClass(cID,iID,pID,callback)
{
	var db = getDatabase(cID);
	eval("var mapCode=function(doc) { if(doc[\""+pID+"\"]) emit(doc.iID,doc[\""+pID+"\"]); }");
	db.query( 	'sentio/instancesProps',
				{ reduce: false, key: [iID,pID] },
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
	db.query( 	'sentio/instances',
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
//// updateDocument
///


function updateDocument(dbname,docID,props,cb)
{
	//console.log("Updating doc id:"+ docID);
	var db = getDatabase(dbname);
	db.get(docID,	function(err,lastVersion)
					{
						//console.log(lastVersion);
						var newProps=lastVersion;
						for (property in props) 
						{
							newProps[property]= props[property];
						} 
						//console.log("Will try to put :");
						//console.log(newProps);
						//console.log(cb);
						db.put(newProps,docID,lastVersion._rev, function(err,data) { /* console.log("put returned"); console.log(data); console.log("will call scheme"); */cb(data); });
					});
}

///
//// getInstanceDocID
///


function getInstanceDocID(cID,iID,cb)
{
	var db = getDatabase(cID);
	db.query( 	function(doc) { emit(doc.iID,doc._id); },
				{ reduce: false, key: iID },
				function(err,data)
				{
					
					if(err || !data || !data.rows || data.rows.length==0) cb(false);
					else cb(data.rows[0].value);
				} );
}

// getInstanceDocID("cds_taskinstance","ID5946800031636_1398737953175213",function(docID) { console.log(docID); });

///
//// updateInstanceProperties
///


function updateInstanceProperties(iID, props, cb)
{
	//console.log("Enter updateInstanceProperties");
	getFirstType(iID,	function(cID)
						{
							//console.log("In updateInstanceProperties tpye:"+ cID);
							getInstanceDocID(cID,iID, 	function(docID)
														{
															updateDocument(cID,docID,props,cb);
														});
						});
}

// updateInstanceProperties("ID5553557733905_1398737953496351",{ "CDS_TaskInstance_Status": ["Status_Visited"] }, function(data) { console.log(data); });


///
//// newInstance
///


function newInstance(cID,props,cb)
{
	var guid=generateAthenaGUID();
	newInstanceWithID(cID, guid,props,cb)
}


function newInstanceWithID(cID,iID,props,cb)
{
	var db = getDatabase(cID);
	var newProps=props;	

	
	newProps['iID']= iID;
	//console.log("will ccreate main")
	//console.log(newProps);
	db.put(newProps,iID,function(err,data) 
						 {
							//console.log("main created"); 
							var typesDB=getDatabase("cds_instances_types");
							typesDB.put({ "cID": cID, "iID": iID }, iID ,function (err,data) { console.log("put type"); cb(iID); });
						});

}



function generateAthenaGUID()
{
	var fpart=Math.floor((Math.random() * 10000000000000) + 1);
	var spartdate=new Date();
	var spart= spartdate.getTime();
	return "ID"+fpart+"_"+spart;
	
}

// newInstance("test", { "toto": 1, "titi": 2 }, function(data) { console.log(data); });
// updateInstanceProperties("ID3377012421843_1399777039404",{ "CDS_TaskInstance_Status": ["Status_Visited"] }, function(data) { console.log(data); });


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



function convertDate(sdate)
{
	var d=Date.parse(sdate);
	return d+'';
}


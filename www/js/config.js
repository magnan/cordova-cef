/// Configuration for Sentio
///


///
//// CouchDB Databases
///


var databases  = ["amt_tasks_groups","amt_tasks_periodic_inspection","cds_activities_status","cds_attachment","cds_competencies_values","cds_employee","cds_employee_status_values","cds_file_type","cds_input_data","cds_input_data_instance","cds_input_type","cds_instances_types","cds_form_instances","cds_forms","cds_priority_values","cds_role","cds_site_location","cds_state_transitions","cds_taskinstance","cds_tasktypes","cds_track","cds_workorder","cds_wocategories" ,"cds_task","cds_notes"];



var syncCompleteIndicatorDatabases = ["cds_activities_status","cds_attachment","cds_competencies_values","cds_employee","cds_employee_status_values","cds_file_type","cds_input_data","cds_input_type","cds_instances_types","cds_priority_values","cds_role","cds_site_location","cds_state_transitions","cds_taskinstance","cds_tasktypes","cds_track","cds_workorder","cds_task"];



///
//// DB Parameters
///


/// Local
///



var LocalCouchURL="http://localhost:5984/"


/// Remote
///


var RemoteCouchURL="http://admin:Tanger132@54.83.18.50:8000/"
var ServerValidationID="c1cb33553de833e0d9c44431a3c9a58c"



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
	processTaskInstanceChangeWithInfo(doc.CDS_TaskInstance_WorkOrder[0],doc.CDS_TaskInstance_Task[0]);
	//changeTaskStatusFillColor(doc.CDS_TaskInstance_Task[0],doc.CDS_TaskInstance_WorkOrder[0],resolveTaskFill(doc.CDS_TaskInstance_Status[0]));
}


function processTaskInstanceChangeWithInfo(woID,taskID)
{
	$(".pstep").each( function(i,pstep) 
						{
							//console.log(pstep);
							var name=$(pstep).attr('name');
							console.log(name);
							if(name.indexOf("'"+woID+"','"+taskID+"'")>=0 ) 
							{
								var spar=name.indexOf("(");
								var epar=name.indexOf(")");
								var args=name.slice(spar+1,epar);
								var pargs=args.split(",");
								var parentID=eval(pargs[pargs.length-1]);
								var parentNode=$(pstep).parent();
								var n=parentNode.index();
								var parentOffset=$(parentNode).attr('transform');
								individualStepCode(woID,taskID,parentID, parentOffset,function(xml) {  
																							console.log(parentOffset+" "+n);
																							Pablo(parentNode).after(xml);
																							$(parentNode).remove();
																							runAdjustmentsScripts();
																							//var newNode=$(parentNode).parent().children().get(n);
																							//$(newNode).attr('transform', parentOffset);
																					    });
							}
						});
}


//processTaskInstanceChangeWithInfo('ID3069186244015_1402540651685038','ID4767692764089_1402540391047534');

function changeTaskStatus(taskID, woID, status)
{
	console.log("changeTaskStatus "+taskID+" "+woID);
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
		case "Status_Assigned": return "url(#gWait)";  break;
		case "Status_Visited": return "url(#gActive)"; break;
		case "Status_Completed": return "url(#gDone)"; break;
		case "Status_Cancelled": return "url(#gCancelled)"; break;
	}
}


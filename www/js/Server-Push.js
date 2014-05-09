/**
 * Copyright 2009 Categorical Design Solutions
 * File: Server-Push.js
 * Author: Francois Magnan
 * 
 */


/// This file is part of GIT System.
///
///    GIT System is free software: you can redistribute it and/or modify
///    it under the terms of the GNU Lesser General Public License as published by
///    the Free Software Foundation, either version 3 of the License, or
///    (at your option) any later version.
///
///    GIT System is distributed in the hope that it will be useful,
///    but WITHOUT ANY WARRANTY; without even the implied warranty of
///    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///    GNU Lesser General Public License for more details.
///
///    You should have received a copy of the GNU Lesser General Public License
///    along with GIT System.  If not, see <http://www.gnu.org/licenses/>.



var lastPushAttempt;
var pushMonitor;
var failureCount=0;

function getNextServerPushLoop()
{
	lastPushAttempt=(new Date()).getTime();
	if(!pushMonitor) startPushMonitor();
	$.ajax( {
			 url: "server-push-service?_dc="+lastPushAttempt,
			 processData: false,
			 success: processPushResponse,
			 error: handleFailure,
			 timeout: 40000
		    });
}


function processPushResponse(data)
{
	if(data!="")
	{
		failureCount=0;
		try {
				eval(data);
		}
		catch(e) {
			alert(e);
			console.log(e);
		}
		getNextServerPushLoop();
	}
	else handleFailure();
}


function handleFailure()
{
	failureCount++;
	//alert(failureCount);
	if(failureCount<4) getNextServerPushLoop();
}


function startPushMonitor()
{
	pushMonitor=setInterval("monitorPush();",35000);
}


function stopPushMonitor()
{
	clearInterval(pushMonitor);
	pushMonitor=undefined;
}


function monitorPush()
{
	var elapsed=(new Date()).getTime()-lastPushAttempt;
	if(elapsed>65000) 
	{
		alert("Erreur Système: Vous avez perdu la connectivité au serveur.\n Vérifiez votre connection réseau.");
		stopPushMonitor();
		getNextServerPushLoop();
	}
}
		
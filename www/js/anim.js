///
//// path utilities
///


function extractFilename(path)
{
	var splitted= path.split("/");
	return splitted[splitted.length-1];
}


function extractExtension(filename)
{
	var splitted=filename.split(".");
	return "."+splitted[splitted.length-1];
}




///
//// runAdjustmentsScripts
///


function runAdjustmentsScripts()
{
	//alert("Adjustment script");
	processTAreas();
	//processTaskDblClick();
	processBubbles();
	processTextButtons();	
	computeLayout();
	computeLayout();
	processDraggables();
	//processFTextFields();
	processFTArea();
}


///
//// myGet
///

var alreadyLoading;


function myGet(url,callback)
{
	if(!alreadyLoading) 
	{
		alreadyLoading=true;
		Pablo.get(url,function(data) { alreadyLoading=false; callback(data); });
	}
}

///
//// processTextButtons
///


function processTextButtons()
{
	$(".textButton").each( function(i,e) {  var tnode=$(e).children()[1];
											var twidth=$(tnode).width();
											Pablo(e).children("rect").attr('width',twidth+20);
											 });

}




///
//// processBubbles
/// 


function processBubbles()
{
	$(".bubbleL").each( function(i,e) 
						{
							var tnode=$("text",$(e)).get(0);
							var inode=$(e).children("image").get(0);
							
							var theight;
							
							if(tnode) theight=$(tnode).height();
							else theight=120;
							Pablo(e).children("path").attr('d',"M365,"+ theight +"c0,5.5-4.5,10-10,10H11c-5.5,0-10-4.5-10-10V19.681h-27.936L1,0h354c5.5,0,10,4.5,10,10V"+ theight +"z");
						});
	$(".bubbleR").each( function(i,e) 
						{
							var tnode=$("text",$(e)).get(0);
							var inode=$(e).children("image").get(0);
							
							var theight;
							
							if(tnode) theight=$(tnode).height();
							else theight=120;

							/* 
							if(inode) {
												var r= inode.getBoundingClientRect();
												inode=r.width;
											}
							else theight=160; */
							Pablo(e).children("path").attr('d',"M-26.936,"+ theight +"c0,5.5,4.5,10,10,10h344c5.5,0,10-4.5,10-10V19.681H365L337.064,0h-354c-5.5,0-10,4.5-10,10V"+ theight +"z");
						});
	
}



///
//// processFTextFields
///


function processFTextFields()
{
	$(".ftext").each(fregionProcessor('<div class="FTFwrapper"><input class="childFTField" type="text" style="display: none"></input></div>','input'));
	$(".fpass").each(fregionProcessor('<div class="FTFwrapper"><input class="childFTField" type="password" style="display: none"></input></div>','input'));
}


function destroyFTFields()
{
	Pablo(".FTFwrapper").remove();
}


function processFTArea()
{
	$(".FtextBox").each(fregionProcessor('<div class="FTFwrapper"><textarea class="childFTField" style="display: none"></textarea></div>','textarea'));
}



function fregionProcessor(htmlCode,elementTagname)
{
	return 	function(i,e)
			{
				//console.log('fregionProcessor');
				//console.log(i);
				//console.log(e);
				var callbacks=eval($(e).attr('name'));
				
				$(e).bind('click',function (evt) { evt.preventDefault(); })					
				var content=$(e).children("text").text();
				var bbox=getElementBBox($(e).children("rect").get(0));
				var nnode=$("body").append(htmlCode); 
				$("body").children().last().children("input").addClass($(e).attr('class'));
				$("body").children().last().children("input").removeClass("ftext");
				$("body").children().last().children("input").removeClass("fpass");
				$("body").children().last().css('position','absolute'); 
				$("body").children().last().css('left',(bbox[0]-2)+'px');
				$("body").children().last().css('top',(bbox[1])+'px');
				$("body").children().last().children().first().keyup(function (e) 
																	{   console.log(e);
																		var data=$(e.target).val();
  																			if (e.keyCode == 13 && callbacks.onreturn) { callbacks.onreturn(data); $(e.target).blur(); } 
																	});
				$("body").children().last().children().first().on('blur',function (e) 
																		 {
																			var data=$(e.target).val();
  																			callbacks.onblur(data); 
																		 });
				$("body").children().last().children(elementTagname).val(content);
				$("body").children().last().children(elementTagname).css('width',bbox[2]+'px');
				$("body").children().last().children(elementTagname).css('height',bbox[3]+'px');
			};
}




///
//// processDraggables
///


function processDraggables()
{	
	$(".hresource").each( function(i,e) { Snap(e).drag(rDragMove,rDragStart,rDragEnd); });
}


var cPSTEP=false;

function rDragMove(dx,dy)
{
	var newX=this.ox+dx;
	var newY=this.oy+dy;
	Pablo("#drag").transform('translate',newX,newY);
	var pstep=findPStepRect(newX,newY);
	if(pstep)
	{
		cPSTEP=pstep;
		unglow();
		glowNode(Pablo("#"+pstep.id)[0]);
	}
	else 
	{
		unglow();
		cPSTEP=false;
	}
}


function findPStepRect(newX,newY)
{
	var i=0;
	var n=stepsRects.length;
	var found=false;
	//console.log("pre while"+i+" "+length);
	while(i<n && !found)
	{
		if(isInRect(newX,newY, stepsRects[i])) found=stepsRects[i];
		i++;
	}
	return found;
}


function isInRect(newX,newY,rect)
{
	if(     rect.rect.left < newX && newX < rect.rect.left + rect.rect.width
	    &&  rect.rect.top < newY && newY < rect.rect.top + rect.rect.height ) return true;
	else return false;
}


var stepsRects;
var cDragRID;

function rDragStart()
{
	//console.log("start drag");
	
	stepsRects=[];
	$(".pStep").each( function (i,e) { stepsRects.push( { rect: e.getBoundingClientRect(), id: $(e).attr('id') }); });
	var bounds=this.node. getBoundingClientRect();
	//console.log(bounds);
	cDragRID=Pablo(this.node).attr('name');
	Pablo(this.node).clone(true).attr('id','drag').appendTo(Pablo("#main"));
	Pablo("#drag").transform('translate',bounds.left,bounds.top);
	this.ox=bounds.left;
	this.oy=bounds.top;
	closeModal("infoModal");
}


function rDragEnd()
{
	//console.log("end drag");
	Pablo("#drag").remove();
	if(cPSTEP)
	{	
		var theID=cPSTEP.id;
		var prescript=$("#"+ theID).attr('name');
		var ppos=prescript.indexOf("(");
		var fscript=prescript.slice(0,ppos+1)+"'"+ cDragRID + "'"+prescript.slice(ppos+1);
		eval(fscript);
	}
}


function droppedOn(rID,woID,actID,parentID)
{
	$.get("addResourceToActivity?rID="+rID+"&woID="+woID+"&actID="+actID, function(data) { if(data=="true") refreshActivityGraph(parentID,woID); });
}


///
//// processTouchEvents
///


function processTouchEvents()
{
	Pablo(".touch").each( processTouchEventOnNode );
	Pablo(".cButton").each(pcbtouch);
	selTouch(Pablo("#modeTableButton")[0]);
	selTouch(Pablo("#modeDashboardButton")[0]);
}

function pcbtouch(element)
{
	var oldFill=Pablo(element).children("circle").attr("fill");
	element.addEventListener('touchstart', function(){ 	
															//console.log( element); 	
															Pablo(element).children("circle").attr("fill","yellow");
														});
	element.addEventListener('touchend', function(){ 	
															//console.log( element); 	
															Pablo(element).children("circle").attr("fill",oldFill);																				});
}

function selTouch(element)
{
	var oldFill=Pablo(element).children("circle").attr("fill");
	element.addEventListener('touchstart', function(){ 	
															//console.log( element); 	
															Pablo(element).children("path").attr("fill","yellow");
														});
	element.addEventListener('touchend', function(){ 	
															//console.log( element); 	
															Pablo(element).children("path").attr("fill",oldFill);																				});
}



function processTouchEventOnNode(element)
{
	var oldOnclick=Pablo(element).attr('ontouchstart');
	Pablo(element).attr('name',oldOnclick);
	if(Mobile) Pablo(element).removeAttr('ontouchstart');
	//console.log(oldOnclick);
	if(oldOnclick)
	{
		element.addEventListener('touchstart', function(e){  e.stopPropagation(); $(element).addClass('active'); eval(oldOnclick);});
		element.addEventListener('touchend', function(e){ e.stopPropagation(); $(element).removeClass('active');  });
	}
}



///
//// processTaskDblClick
///


function processTaskDblClick()
{
	if(!Mobile)	Pablo(".pStep").each( processOneTaskDblClick);
}


var clickTimeout

function processOneTaskDblClick(element)
{
	var oldOnclick=Pablo(element).attr('onclick');
	Pablo(element).removeAttr('onclick');
	Pablo(element).on('click', function() { clickTimeout=setTimeout(function () { clickTimeout=false; eval(oldOnclick); },400); });
	Pablo(element).on('dblclick',function() { 
												if(clickTimeout) 
												{ 
													clearTimeout(clickTimeout); 
													clickTimeout=false; 
												} 
												var dclkcall=Pablo(this).attr('ondblclick'); 
												eval(dclkcall); 
											});
}


///
//// Modal windows
///


function bringModal(aIID,infotype)
{
	showPushEffect();
	myGet("infoModal?aIID="+aIID+"&infoType="+infotype,function(data) { showModal(data,"infoModal"); });
}


function showModal(data,id)
{
	scrollToTop();
	Pablo("#main").append(Pablo(data));
	runAdjustmentsScripts();
	fadeIn(id);
}


function closeModal(id,callback)
{
	stopWarningSignAnim();
	fadeOut(id,function () { $("#"+id).remove(); if(callback) callback(); });
}


///
//// processTAreas
///



function processTAreas()
{
	Pablo($("#main").get(0)).find(".textArea").each( pTextArea );
}	


function pTextArea(node)
{
	var theid=$(node).attr('id');
	var w=Pablo($("#"+theid).get(0)).attr('taWidth');
	//console.log(w);
	//console.log($(node).attr('id'));
	var processed=$(node).attr('taProcessed');
	
	
	if(!processed)
	{
		var id=$(node).attr('id');
		var lspc=20;
		var text=node.textContent;

		//console.log(id+' '+width+' '+text);
		node.textContent='';
		var x=$(node).attr('x');
		var maxlines=false;
		if(w=='130') maxlines=7;
		textFlow(text,$('#'+id).get(0),w,x,lspc,false,maxlines);
		$(node).attr('taProcessed',true);
	}

}


///
//// glow
///


var glowElement;

function glow(e)
{

	if(glowElement) unglow();
	element=e.target;
	glowElement=element;
	var group=$(element).parents("g");
	group.children("rect[name='highlight']").attr('visibility','visible');
}


function glowNode(node)
{
	glowElement=node;
	var group=$(element).parents("g");
	$(glowElement).children("rect[name='highlight']").attr('visibility','visible');
}


function unglow()
{	
  //$("rect[name='highlight']",$(".pStep")).attr('visibility','hidden'); 
  var e=window.event;
  //console.log(e);
	$(".pstep",$("#bodyContainer")).children("rect[name='highlight']").attr('visibility','hidden');
  //$(".pStep").children().first().attr('visibility','hidden');
}


//
/// hIcon
//


function hIcon(e)
{
	$(e.target).attr('fill','lightblue');
}


function unHIcon(e)
{
	$(e.target).attr('fill','darkgray');
}

//
/// highlight
//


function highlight(e)
{
	var group=$(e.target).parent("g");
	group.attr('opacity','0.7');
}


function unhighlight(e)
{
	var group=$(e.target).parent("g");
	group.attr('opacity','1');
}

///
//// changeTaskState
///



function completeTask(woID,actID)
{
	showPushEffect(true);
	changeTaskState(woID, actID, "Status_Completed");	
}

function cancelTask(woID,actID)
{
	showPushEffect(true);	
	changeTaskState(woID, actID, "Status_Cancelled");
}

function undoTask(woID,actID)
{
	showPushEffect(true);
	changeTaskState(woID, actID, "Status_Visited");
}




function showPushEffect(close)
{
	var e=window.event;
	if(e)
	{
	e.stopPropagation();
	var t=e.target;

	if(t.tagName!="g") t=Pablo(t).parent("g")[0];
	var oldFilter=$(t).attr('filter');
	if(!oldFilter) oldFilter='';
	$(t).attr('filter','url(#emboss2)');
	setTimeout(function() 
				{ 
					$(t).attr('filter',oldFilter);
					if(close) fadeOut("popOver",function () { destroyPopover(); });

  },1000);
	}
}


function cancelBubble()
{
	var e=window.event;
	e.stopPropagation();
}





///
//// refresh of graphs
///


function refreshActivityGraph(activityID,workOrderID,callback)
{
	myGet("activityGraph?activityID="+ activityID +"&workOrderID="+ workOrderID, replaceGraphSVG(activityID, callback));
}



var activeWO=false;

function refreshNavigStack(woID)
{
	setTimeout(function () {

	if(activeWO==woID) 
	{
		//console.log("Refreshing stack");
		refreshNavigStackRec(woID,navigationStack.length-1,true);
	}
	else
	{
		//console.log("Refreshing progress");
		refreshWOProgress(woID);
	}

	},1500);
}


function delayedRefresh(woID,nodeID)
{
	popSlide(function(){ $("#"+nodeID).remove(); });
}


var popOverTaskIndex;

function refreshNavigStackRec(woID,i,refreshPopoverReferences)
{
	var sitem=navigationStack[i];

	if(refreshPopoverReferences && $("#popOver").size()>0)
	{
		//console.log("must keep refresh pop refs:"+popOverTaskIndex);
	}
	if(sitem.isGraph) refreshActivityGraph(sitem.id,woID,function() {   //console.log("RGraph:"+ refreshPopoverReferences+" size:"+$("#popOver").size());
																		if(refreshPopoverReferences && $("#popOver").size()>0)
																		{
																			var cPage=$("#bodyContainer").children().last();
																			var node=$(".gridContainer", cPage).children().get(popOverTaskIndex);
																			//console.log(node);
																			var b=$(node).children(".pStep");  
																			cpInfo.tID=$(b).attr('id'); 
																			//console.log("new tid:"+cpInfo.tID); 
																		}
																		refreshNavigStackRec(woID,i-1); 
																	});
	else if(sitem.id=="home") refreshWOProgress(woID);
	else refreshNavigStackRec(woID,i-1);
}



function replaceGraphSVG(activityID,callback)
{
	return function(data)
			{
				Pablo("#"+activityID).empty();
				Pablo("#"+activityID).append(Pablo(data).children());
				runAdjustmentsScripts();	
				if(callback) callback();
			};
}



var WONeedsRefresh=false;


function refreshWOProgress()
{
	doRefreshWOPage();
}

function doRefreshWOPage()
{
	refreshWorkOrders();
}


function getLastPageID()
{
	return Pablo("#bodyContainer").lastChild().attr('id');
}



///
//// slide transitions
///

var slideDuration=600;


/*
function pushActivityGraph(activityID,workOrderID)
{
	activeWO= workOrderID;
    
	myGet("activityGraph?activityID="+ activityID +"&workOrderID="+ workOrderID, function(data,callback) { pushSlide(data,callback,true); });
}
*/


var navigationStack=[ { "id": "home", "title": "Home", "isGraph": false} ];


function pushInterface(serviceCall,callback)
{
	checkHomeDuplicates();
	myGet(serviceCall, function(data) { pushSlide(data,callback); });
}



function checkHomeDuplicates()
{
	var fchild=$("#bodyContainer").children().get(0);
	var schild=$("#bodyContainer").children().get(1);

	if( $(fchild).attr('id')=="home" && $(schild).attr('id')=="home") $(schild).remove();	
}



function pushSlide(data,callback,isGraph)
{
	//console.log(data);
	destroyPopover();
	//$("#bodyContainer").append(data);
	var bc=$("#bodyContainer").get(0);
	Pablo(bc).append(Pablo(data));
	runAdjustmentsScripts();
	Pablo(bc).lastChild().transform('translate',TotalWidth,0);
	var id=Pablo(bc).lastChild().attr("id");
	var title=Pablo(bc).lastChild().attr("title");
	var n=navigationStack.length;
	var g1ID=navigationStack[n-1].id;

	
	// animation
	var now=mina.time();
	mina(0,-TotalWidth,now,now+slideDuration,mina.time,function(v) { var g1=$("#"+g1ID); Pablo(g1).transform('translate',v,0); },mina.easein);
	mina(TotalWidth,0,now,now+slideDuration,mina.time,function(v) { var g2=$("#"+id); Pablo(g2).transform('translate',v,0); }, mina.easein);

	// stack update
	navigationStack.push({ "id": id, "title": title, "isGraph": isGraph });

	// breadcrumb
	var bccode=getBCCode(id,title,50+105*(navigationStack.length-1));
	//console.log(bccode);
	Pablo($("#breadcrumb").get(0)).append(Pablo(bccode));

	adjustSVGWindow();
	// callback
	if(callback)
	{
		setTimeout(callback,slideDuration+200);
	}
}


function adjustSVGWindow()
{
  // adjust svg window height (to enable scrolling)
  var blockH=Pablo($("#bodyContainer").get(0)).lastChild().bbox().height;
  // console.log(blockH);
  var w;
  if(screen.width==768) w=1024; else w=screen.width;
  //console.log("Computed width:"+w);
  $("#main").attr('width',w);
  Pablo(".background").attr('height',blockH);
  $("#main").attr('height',Math.max(TotalHeight,blockH+112));
  $("#body").attr('height',Math.max(TotalHeight,blockH+112));
}



function popSlide(callback)
{	
	showPushEffect();
	destroyFTFields();
	destroyPopover();
	if(navigationStack.length>1)
	{
		var now=mina.time();
		var n=navigationStack.length;
		var g1ID=navigationStack[n-1].id;
		var g2ID=navigationStack[n-2].id;
		mina(-TotalWidth,0,now,now+slideDuration,mina.time,function(v) { var g2=$("#"+g2ID); Pablo(g2).transform('translate',v,0); },mina.easeout);
		mina(0,TotalWidth,now,now+slideDuration,mina.time,function(v) { var g1=$("#"+g1ID); Pablo(g1).transform('translate',v,0); },mina.easeout);

		navigationStack.pop();
	
		setTimeout(function() {  Pablo($("#bodyContainer").get(0)).lastChild().remove(); if(g2ID=="home" && WONeedsRefresh) { doRefreshWOPage(); WONeedsRefresh=false; } if(callback) callback(); adjustSVGWindow(); },slideDuration);
		Pablo($("#breadcrumb").get(0)).lastChild().remove();
		
	}
}


///
//// crossfade transition
///


function crossFadeTransition(id1,id2)
{
	Snap.select("#"+id1).animate( { "opacity": "0" }, 800);
	Snap.select("#"+id2).animate( { "opacity": "1" }, 800);
}


function fadeIn(id)
{
	Snap.select("#"+id).animate( { "opacity": "1" }, 400);
}

function fadeOut(id,callback)
{
	if($("#"+id).size()>0)
	{
		Snap.select("#"+id).animate( { "opacity": "0" }, 400,callback);
	}
	else
	{
		if(callback) callback();
	}
}





///
//// Tests de grow
///


var currentAnim;
var originalT;
var currentScale;
var eID;

function grow(e) 
{ 
	element=e.target; 
	eID=$(element).parent().attr('id');
	originalT=$("#"+eID).attr('transform');
  	  
	now=mina.time();
	currentAnim=mina(1,1.1,now,now+500,
						mina.time,
						function(v) 
						{ 
							$("#"+eID).attr('transform', originalT+" "+"scale("+v+")"); 
							currentScale=v;
						},
						mina.linear);
}


function shrink(e) 
{ 
	if(currentAnim) currentAnim.stop();
	now=mina.time();
	currentAnim=mina(currentScale,1,now,now+500,
						mina.time,
						function(v) 
						{ 
							$("#"+eID).attr('transform', originalT +" "+"scale("+v+")"); 
						},
						mina.linear);
}



///
//// table sorting
///


function toggleSorting(col)
{
	myGet("getWorkOrdersNewSorting?cIndex="+col,replaceGraphSVG("home"));
}


///
//// refreshPopOver
///


function updatePopoverWindow(t)
{
	//console.log("uupdate:"+cpInfo.tID);
	showTaskPopover(cpInfo.tID,cpInfo.woID,cpInfo.actID,true,t);
}


///
//// showPopover
///


var cpTID=false;
var cpInfo;
var nextBBOX=false;

function showTaskPopover(tID,woID,actID,update,t)
{	
	cpInfo={ tID: tID, woID: woID, actID: actID};
	//console.log(cpInfo.woID);
	popOverTaskIndex=$("#"+tID).parent().index();
	//console.log("showing index:"+ popOverTaskIndex);
	if(cpTID==tID && !update)
	{
		//console.log("bad case showing up!");
		hidePopover();
	}
	else
	{
		var downloadPopover=function() 
							{

								var domelement=Pablo("#"+tID).children(".taskBox").first()[0];
								var bbox=getElementBBox(domelement);
							    nextBBOX=bbox;
								//console.log("nextbpx:"+ nextBBOX);
								popOverCodeContent(woID, actID, function(data) 
																{ 
																	//console.log("**** popOverCodeContent returned");
																	//console.log(data);
																	var svg=Pablo("#main").append(data);
																	//console.log(data);
																	
																	
																	runAdjustmentsScripts();
																	var contentData=$("#main").children().last();
																	var contentDataNode= contentData.get(0);
																	var h=Math.floor(Pablo(contentDataNode).bbox().height+2);
																	var w=Math.floor(Pablo(contentDataNode).bbox().width);
																	//console.log(w+" "+h+" "+bbox+" "+$("body").scrollTop());
																	var pdata=popOverCode(w,h,nextBBOX,$("body").scrollTop());
																	//console.log("**********PDATA"+pdata);
																	if(update) destroyPopover(true);
																	insertPopover(Pablo(pdata));
																	cpTID=tID;
																	contentData.clone(true).appendTo(Pablo("#popOverContent"));
																	contentData.remove();
																	Pablo("#popOverContent").children().attr('visibility','visible');
																	adjustSVGWindow(); adjustSVGWindow(); adjustSVGWindow(); adjustSVGWindow();
																	afterFormPushed();
																	if(t) $(".childFTField").each(function (i,e) { $(e).val(t) });																	


																});
							};
		if(update) downloadPopover();
		else hidePopover(downloadPopover,true);
	}																								
}


function getElementBBox(domelement)
{
	if(domelement)
	{
		var element=$(domelement);
		var eloffset=element.offset();
		var bbox=[];
		bbox.push(eloffset.left);
		bbox.push(eloffset.top);
		bbox.push(element.attr("width"));
		bbox.push(element.attr("height"));
		return bbox;
	}
	else return [0,0,0,0];
}


function getFTextBBox(id)
{
	var del=$("#"+id).children("rect").get(0);
	return getElementBBox(del);
}

var cpMID=false;

function showMenuPopover(mID,content,iID)
{	
	if(cpMID==mID) hidePopover();
	else
	{
		hidePopover(function() 
				{
					var domelement=Pablo("#"+mID).first()[0];
					
					var element=$(domelement);
					var eloffset=element.offset();
					var bbox=[];
					bbox.push(eloffset.left);
					bbox.push(eloffset.top);
					bbox.push(Pablo("#"+mID).children("rect").attr('width'));
					bbox.push(Pablo("#"+mID).children("rect").attr('height'));
					myGet("getMenuPopoverCode?bbox="+bbox.toString()+"&content="+content+"&mID="+mID+"&iID="+iID,insertPopover);
					cpMID=mID;
				});
	}
}


function hidePopover(callback,keepRefs)
{
	fadeOut("popOver",function() { destroyPopover(keepRefs); if(callback) callback(); });
}


function destroyPopover(keepRefs)
{
	var n=navigationStack.length;
	var isInGraph=navigationStack[n-1].isGraph;
	//console.log("destroyPopover("+ keepRefs+")");
	if($("#popOver").size()>0) Pablo("#popOver").remove();
	if(isInGraph)
	{
		Pablo(".FTFwrapper").remove();
		cpTID=false; 
		cpMID=false;
		if(cpInfo && ! keepRefs)
		{
			cpInfo.tID=false;
			cpInfo.woID=false;
			cpInfo.actID=false;
		}
	}
}


function insertPopover(data)
{
	Pablo("#main").append(data);
}

///
//// menus
///


function highlightMenuItem(e)
{
	element=e.target;
	var group=Pablo(element).parent("g");
	group.children(".itemRect").attr('fill','black');
	group.children(".itemText").attr('fill','white');
}



function unhighlightMenuItem(e)
{
	element=e.target;
	var group=Pablo(element).parent("g");
	group.children(".itemRect").attr('fill','none');
	group.children(".itemText").attr('fill','black');
}


function selectMenuItem(e,mID,iID)
{
	element=window.event.target;
	var group=Pablo(element).parent("g");
	var sID=group.attr('id');
	var text=group.children(".itemText").content();
	text=truncatestring(text,28);
	Pablo("#"+mID).children("text.popMenuTitle").content(text);
	$.get("menuItemSelectionEffect?iID="+iID+"&vID="+sID);
	hidePopover();
}


function truncatestring(text,mi)
{
	var l=text.length;
	if(mi<l)
	{
		return text.slice(0,mi-3)+"...";
	}
	else return text;
}


///
//// launchWO
///


function launchWO(woID)
{
	showPushEffect();
	$.get("launchWorkOrder?woID="+woID,function(data) { location.reload(); });
}


///
//// expressions push in body
///


function getServerExpression(expID)
{
	//console.log('Getting expr:'+expID);
	$.get("serverExpression?expID="+ expID, function(data) { $("body").append(data); });
}


///
//// table/dashboard toggle
///


function gotoTableMode()
{
	$.get("setWOmode?mode=table", function(data) { clearInterval(gaugeInterval); refreshWOProgress(); } );
}

function gotoDashboardMode()
{
	$.get("setWOmode?mode=dashboard", refreshWOProgress );
}


///
//// view resource
///




function viewResource(rID)
{	
	showPushEffect();
	// just loads PDF files for the moment. TODO
	doLoadPDFFile(rID);	
}
													

/*	
	AnnotationPaths=[];
	closeModal("infoModal", function() { pushInterface("getViewer?rID="+rID, function() { maybeLoadPDFFile(rID); maybeDrawAnnotations(); }); } );
} */

/*
function doLoadPDFFile(rID)
{
	 window.open('plugin/pdfjs/web/viewer.html?file=../../../docs/M02-5.pdf');
	//getAttachmentURL(rID,function(url) { window.open('plugin/pdfjs/web/viewer.html?file='+url); });
	//$.get("getAttachmentURL?rID="+rID,function(url) { window.open(url); });

	/* $.get("getPDFContainer",function (data) { 
												$(body).append(data); 
											  	$.get("getAttachmentURL?rID="+rID,function(url) { var myPDF = new PDFObject({ url: url }).embed("PDFContainer"); });
											}); 
}
*/

function maybeDrawAnnotations()
{
	Pablo("#annotationOverlay").children("path").each( function(p) { drawPath(p); } );
}


function drawPath(p)
{
	var length=0;
	var timer = setInterval(function() 
						{
							var pathLength=p.getTotalLength();
							length += 5;
							p.style.strokeDasharray = [length,pathLength].join(' ');
							Pablo(p).attr('visibility',"visible");
							if (length >= pathLength) clearInterval(timer);
						},1000/60);
}	



///
//// Annotation tool
///


var isDrawing=false;
var AnnotationPaths=[];
var PathsColors=[];
var CurrentPath=false;
var CurrentPathIndex=0;
var CurrentPathPoints=[];
var OriginX;
var OriginY;

function installAnnotationToolHandlers()
{
	var canvas=$("#imageCanvas").get(0);
	getImageOrigin();
	//console.log(canvas);
	canvas.addEventListener('mousedown',annotationTouchStart);
	canvas.addEventListener('mousemove',annotationTouchMove);
	canvas.addEventListener('mouseup',annotationTouchEnd);

	canvas.addEventListener('touchstart',annotationTouchStart);
	canvas.addEventListener('touchmove',annotationTouchMove);
	canvas.addEventListener('touchend',annotationTouchEnd);
}


function getImageOrigin()
{
	var trans=$("#imageCanvas").attr("transform");
	var leftP=trans.indexOf("(");
	var rightP=trans.indexOf(")");
	var par=trans.slice(leftP+1,rightP);
	var splitted=par.split(",");
	OriginX=parseInt(splitted[0]);
	OriginY=parseInt(splitted[1]);
}

function generatePathID()
{
	return "path"+ CurrentPathIndex;
}

function annotationTouchStart(evt)
{
	//console.log(evt);
	evt.preventDefault();
	isDrawing=true;
	var x,y;
	if(evt.changedTouches)
	{
		var touch = evt.changedTouches[0];
		x=touch.pageX-OriginX;
		y=touch.pageY-OriginY-100;
	}
	else
	{
		x=evt.pageX-OriginX;
		y=evt.pageY-OriginY-100;
	}
	
	CurrentPathIndex++;
	CurrentPathPoints.push([x,y]);
	CurrentPath = Pablo.path({ "id": generatePathID(), "stroke": cColor, "stroke-width": "8", "fill": "none", "d": constructPathData(CurrentPathPoints) });
	Pablo("#imageCanvas").append(CurrentPath);
}


function annotationTouchMove(evt)
{
	evt.preventDefault();
	var x,y;
	if(evt.changedTouches)
	{
		var touch = evt.changedTouches[0];
		x=touch.pageX-OriginX;
		y=touch.pageY-OriginY-100;
	}
	else
	{
		x=evt.pageX-OriginX;
		y=evt.pageY-OriginY-100;
	}

	if(isDrawing)
	{	
		CurrentPathPoints.push([x,y]);
		CurrentPath.attr("d",constructPathData(CurrentPathPoints));
	}
}


function annotationTouchEnd(evt)
{
	evt.preventDefault();
	AnnotationPaths.push([generatePathID(),constructPathData(CurrentPathPoints)]);
	PathsColors.push(cColor);
	CurrentPathPoints=[];
	isDrawing=false;
	
}


function constructPathData(points)
{
	var result="M"+points[0][0]+","+points[0][1];
	points.slice(1).forEach( function(p) { result+=" L"+p[0]+","+p[1]; } );
	return result;
}


var EditMenuVisible=false;

function showImageEditMenu(attID)
{
	if(EditMenuVisible) 
	{
		hidePopover();
		EditMenuVisible=false;
	}
	else
	{
		var domelement=Pablo("#imageEditButton").children("rect")[0];
		var bbox=getElementBBox(domelement);
		myGet("getImageEditPopoverCode?attID="+attID+"&bbox="+bbox.toString(),insertPopover);
		EditMenuVisible=true;
	}
}


var cColor="none";

function setColor(c,id)
{
	cColor=c;
	Pablo("#"+id).siblings("rect").attr("stroke","rgb(80%,80%,80%)");
	Pablo("#"+id).attr("stroke","rgb(30%,30%,30%)");
	installAnnotationToolHandlers();
}


function saveDrawing(attID)
{
	$.get("saveImageAnnotation?attID="+attID+"&paths="+JSON.stringify(AnnotationPaths)+"&colors="+JSON.stringify(PathsColors));
}	


///
//// fields edition
///

/*
function fieldEdited(formID,inputID,data)
{
	$("#SIContentInput").val(data);
	$("#DUMMYuploadForm").ajaxSubmit({ 	url: "fieldEdited",
									data: { 	formID: formID, inputID: inputID },
									type: "POST",
									success: function(res) {  }
								 });
}
*/

///
//// computeLayout
///


function computeLayout()
{
	//console.log("computing layout...");
	Pablo(".vstack").each( layoutVStack );
	Pablo(".hstack").each( layoutHStack );	
	afterFormPushed();							
}


function delayedLayout()
{
	setTimeout(computeLayout,550);
}

function layoutVStack(el)
{
	var ancestorG=Pablo(el).parents("g");
	var pwidth=ancestorG.bbox().width;
	var padding=parseInt($(el).attr('padding'));
	var ypos=padding;
	//console.log(ypos);
	Pablo(el).children().each( function(b)
											{
												//console.log(ypos);
												var bbbox=Pablo(b).bbox();
												var dy=(pwidth-bbbox.width)/2;
												Pablo(b).transform('translate',0,ypos);
												ypos+=bbbox.height+padding;
											});
}



function layoutHStack(e)
{
	var ancestorG=Pablo(e).parents("g");
	var pheight=ancestorG.bbox().height;
	var padding=parseInt($(e).attr('padding'));
	var align=$(e).attr('align');
	var xpos=padding;
	Pablo(e).children().each( function(b,i)
											{
												//console.log(b);
												var bbbox=Pablo(b).bbox();
												if(align=='top') var dy=0;
												else var dy=(pheight-bbbox.height)/2;
												//console.log(dy);
												//console.log(bbbox);
												Pablo(b).transform('translate',xpos,dy);
												xpos+=bbbox.width+padding;
											});
}


///
//// viewForm
///


function viewForm(formID,nodeID)
{
	closeModal("infoModal");
	myGet("getFormInterface?formID="+ formID+"&nodeID="+nodeID, function(data) { pushSlide(data, afterFormPushed,false); });
}


function deleteForm(formIID)
{
	$.get("deleteFormInstance?formIID="+formIID);
}


function afterFormPushed()
{
	processFTextFields();
	$(".FTFwrapper").each( function(i,e) { $(e).children().fadeIn(); } );
}


///
//// createServiceRequest
///


function createServiceRequest(aIID)
{
	closeModal("infoModal");
	myGet("createServiceRequest?aIID="+ aIID, function(data) { pushSlide(data, afterFormPushed,false); });
}



///
//// viewForm
///



function toggleCheckBox(cbID,formID,inputID)
{
	var cstr=Pablo("#"+cbID).children(".checkmark").attr('stroke');
	var newStr;
	if(cstr=="none") newStr="red";
	else newStr="none";
	Pablo("#"+cbID).children(".checkmark").attr('stroke',newStr);

	var val;
	if(newStr=="red") val=true;
	else val=false;
	$.get("setCheckboxValue?formID="+formID+"&inputID="+inputID+"&value="+val);
}


///
//// showCompetencyWarning
///


function _showModal(data,id)
{
	showModal(data,"competencyWModal"); 
	startWarningSignAnim(); 
}


///
//// showAssigmentWarning
///

function showDelayedAssignmentWarning(aID,woID,rID)
{
	setTimeout(function() { showAssignmentWarning(aID,woID,rID); },800);
}

function showAssignmentWarning(aID,woID,rID)
{
	myGet("assignmentWarningModal?aID="+ aID +"&woID="+ woID+"&rID="+rID,function(data) { showModal(data,"assignmentWModal"); startWarningSignAnim(); });
}




///
//// warning sign animation
///


var wsanim=false;

function startWarningSignAnim()
{
	wsanim=true;
	toRed();
}

function toRed()
{
	if(wsanim && $("#warningSign").size()>0)	Snap.select("#warningSign").animate({"fill": "red"},600,mina.easein,toOrange);
}

function toOrange()
{
	if(wsanim && $("#warningSign").size()>0)	Snap.select("#warningSign").animate({"fill": "orange"},600,mina.easein, toRed);
}


function stopWarningSignAnim()
{
	if($("#warningSign").size()>0)
	{
		Snap.select("#warningSign").stop();
		wsanim=false;
	}
}

///
//// addNoteToTask
///


function addNoteToTask(aIID,note)
{
	doAddNoteToTask(cpInfo.actID,cpInfo.woID,note);
}



///
//// addPhotoToTask
///


function confirmImage(photo)
{
	closeModal('mediaModal');
	doAddPhotoToTask(cpInfo.actID,cpInfo.woID,photo);
}

///
//// deleteNote(noteID,aIID)
///


function deleteNote(noteID,aIID)
{
	$.get("deleteNote?aIID="+aIID+"&noteID="+noteID,function () { });
}



///
//// show assignation overlay
///


function showAssignationOverlay()
{
	$(".pStep").animate({"opacity": 0.2},700);
	$(".actorsIndicator").animate({"opacity": 0.2},700);
	$(".arrow").animate({"opacity": 0.2},700);
	$(".actorsOverlay").animate({"opacity": 1},700);
	setTimeout(hideAssignationOverlay,3000);
}


function hideAssignationOverlay()
{
	$(".pStep").animate({"opacity": 1},700);
	$(".actorsIndicator").animate({"opacity": 1},700);
	$(".arrow").animate({"opacity": 1},700);
	$(".actorsOverlay").animate({"opacity": 0},700);
}


///
//// computePiePath
///

function computePiePath(cx,cy,cp)
{
	//console.log("pie path");
	//console.log(cp);
	aex=cx+cx*Math.sin(Math.PI*2*cp/100);
	aey=cx-cx*Math.cos(Math.PI*2*cp/100);
	var large;
	if(cp>50) large=1;
	else large=0;
	//console.log("M"+cx+","+cy+" L"+cx+",0 A"+cx+","+cx+" 0 1,1 "+aex+","+aey+" z");
	return "M"+cx+","+cy+" L"+cx+",0 A"+cx+","+cx+" 0 "+large+",1 "+aex+","+aey+" z";
}


///
//// activity indicator
///


var animationInterval;


function showActivityIndicator()
{	
	scrollToTop();
	var s = Snap("#main"); 
	var g = s.g().attr({"id": "actInd", class: "actInd"});


	var cx = TotalWidth/2;
	var cy = TotalHeight/2;
	
	var circle1 = g.circle(cx, cy, 80).attr({
	    fill: "none",
	    stroke: 'red',
	    opacity: 0.5,
	    strokeWidth: 30,
	    strokeDasharray: "10 10",
	    strokeDashoffset: 50
	});
	
	var circle2 = g.circle(cx, cy, 50).attr({
	    fill: "none",
	    opacity: 0.5,
	    stroke: 'orange',
	    strokeWidth: 30,
	    strokeDasharray: "10 10",
	    strokeDashoffset: 50
	});
	
	
	var animationLambda = function()
								{
	
									Snap.animate(0,400, function( value ){ 	circle1.attr({ 'strokeDashoffset': value }) },5000 );
									Snap.animate(400,0, function( value ){	circle2.attr({ 'strokeDashoffset': value })	},5000 );
	
								};

	animationLambda();
	animationInterval=setInterval(animationLambda,5000);

}


function hideActivityIndicator()
{
	clearInterval(animationInterval);
	$(".actInd").remove();
}


///
//// scroll back to top
///


function scrollToTop()
{
	$("body").scrollTop(0);
}


///
//// getImageScaledRect
///



function getImageScaledRect(url,cb)
{
  var imgHeight;
  var imgWidth;

  var findHHandWW = function () 
					{ 
						var rect=new Object();
						var w=this.width;
						var h=this.height;
						var mw=TotalWidth-20;
						var mh=TotalHeight-20-100;
						var scaleFactor=Math.min(mw/w,mh/h);
						var nw=w* scaleFactor;
						var nh=h* scaleFactor;
						rect.x=Math.floor(10+(mw-nw)/2);
						rect.y=Math.floor(10+(mh-nh)/2);
						rect.width=Math.floor(nw);
						rect.height=Math.floor(nh);
						cb(rect); 
						return true; 
					};
 
  var myImage = new Image();
  myImage.name = url;
  myImage.onload = findHHandWW;
  myImage.src = url;
}

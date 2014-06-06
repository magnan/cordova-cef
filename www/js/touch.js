/////////////////////////////////////////////////////////////
/////
///// Athena Touch Events Processing Kit
/////
///// Copyright 2014: Categorical Design Solutions Inc.
///// All rights reserved.
/////
/////
///// Author: Francois Magnan
/////


//// Hijack the javascript events for better control on various devices.
//// Needed for compatibility issues. example: SVG touch events not supported in chromium.



///
//// detection of mode
///


var touchMode;
var voidTouchAction;

function initDetectionMode()
{
	var bodyel=$("body").get(0);
	 Hammer(bodyel).on("swipeleft", function(event) 
									{ 
										var px=event.gesture.startEvent.center.pageX;
										var py=event.gesture.startEvent.center.pageY;
										processSwipeLeftFrom(px,py);
										//processTouchStart(event.srcEvent); var osd=$(initialNodeTouched).attr('vonswipeleft'); 
       								});  

/*
	Hammer(bodyel).on("touch", function(event) 
							 { 
								var px=event.gesture.center.pageX;
								var py=event.gesture.center.pageY;
								processTouchStart(px,py);
        					 });
*/

	voidTouchAction= false; /// destroyPopover;


	$("body").bind('touchstart',firstTouchStart);
	$("body").bind('mousedown',firstMousedown);

}


function firstTouchStart(e)
{
	//alert("touch");
	touchMode=true;
	$("body").unbind();
	$("body").bind('touchstart', PreProcessTouchStart);
	$("body").bind('touchmove',processTouchMove);
	$("body").bind('touchend',processTouchEnd);
	PreProcessTouchStart(e);
}


function PreProcessTouchStart(e)
{
	//console.log(e);
	if(touchMode)
	{
		var px=e.originalEvent.pageX;
		var py=e.originalEvent.pageY;
	}
	else
	{
		var px=e.pageX;
		var py=e.pageY;
	}
	processTouchStart(px,py);

}


function firstMousedown(e)
{
	//alert("click");
	touchMode=false;
	$("body").unbind();
	$("body").bind('mousedown', PreProcessTouchStart);
	$("body").bind('mousemove', processTouchMove);
	$("body").bind('mouseup', processTouchEnd);
	PreProcessTouchStart(e);
}


///
//// touch environment
///


var initialTouchX;
var initialTouchY;
var initialNodeTouched;
var SimpleTouchMode;


///
//// processTouchStart
///


function processTouchStart(px,py)
{
	
	var found=false;

	initialTouchX=px;
	initialTouchY=py;
	
	found=classTouchTest(px,py,".swipe-left",function(node) { SimpleTouchMode=false; initialNodeTouched=node; });
	if(!found)
	{
		found=classTouchTest(px,py,".touch",function(node) { console.log("inActivity:"+ inActivity); if(!inActivity) eval($(node).attr('vonclick')); 
		});
		if(found)
		{
			SimpleTouchMode=true;
		}
		else
		{	
			if(voidTouchAction) 
			{
				SimpleTouchMode=true;
				voidTouchAction();
			}
		}	
	}
}


function processSwipeLeftFrom(px,py)
{
	alert("swipeleft");
	//classTouchTest(px,py,".swipe-left",function(node) { eval($(node).attr('vonswipeleft')); });
}




///
//// processTouchMove
///



function processTouchMove(e)
{
	
}


///
//// processTouchEnd
///


function processTouchEnd(e)
{
	
	if(!SimpleTouchMode)
	{
		if(touchMode)
		{
			var tx=e.originalEvent.touches[0].pageX;;
			var ty=e.originalEvent.touches[0].pageY;;
		}
		else
		{
			var tx=e.pageX;
			var ty=e.pageY;
		}
	
		var dx=(tx-initialTouchX);
		var dy=(ty-initialTouchY);

		
		// swipe down
		if(dy>100 && Math.abs(dx)<50) 
		{
			var osd=$(initialNodeTouched).attr('vonswipedown');
			if(osd) eval(osd);
		}

		// swipe left
		if(dx<-100 && Math.abs(dy)<20) 
		{
			console.log("touch end "+ dx +" "+dy+ " "+ initialNodeTouched);

			var osd=$(initialNodeTouched).attr('vonswipeleft');

			console.log("swiped:"+osd+" node:"+ initialNodeTouched);
			if(osd) eval(osd);
		}

		// swipe right
		if(dx>100 && Math.abs(dy)<50) 
		{
			var osd=$(initialNodeTouched).attr('vonswiperight');
			if(osd) eval(osd);
		}
		
	}
}



///
//// processing
///


function classTouchTest(px,py,selector,callback)
{
	var found=false;
	var touchables=$(selector).get().reverse();
	var i=0;
	var n=touchables.length;

	while(!found && i<n)
	{
		var node=touchables[i];
		var bbox=getElementBBoxV2(node);
		if(isInsideRect(px,py,bbox))
		{
			found=true;
			if(callback) callback(node);
		}
		i++;
	}	
	return found;
}


function getElementBBoxV2(node)
{
	var eloffset=$(node).offset();
	var elbound=node.getBoundingClientRect();
	var bbox=[];
	bbox.push(eloffset.left);
	bbox.push(eloffset.top);
	bbox.push(elbound.width);
	bbox.push(elbound.height);
	return bbox;
}



function isInsideRect(px,py,box)
{
	if( px>=box[0] && py>=box[1] && px<=(box[0]+box[2]) && py<=(box[1]+box[3])) return true;
	else return false;
}



///
//// _xmlRemoveContent
///


function _xmlRemoveContent(pID)
{
	$("#"+pID).children().remove();
}


///
//// showBadLoginInfo
///


function showBadLoginInfo()
{
	console.log("bad");
	var	node1=$("#username").children("rect").get(0);
	animateFill(node1,"red",function() { });
	
	var	node2=$("#logo-athena").children("path").get(0);
	animateFill(node2,"red",function() { });

	var	node3=$("#password").children("rect").get(0);
	animateFill(node3,"red",function() { }); 
	//var	node2=$("#password").children("rect").get(0);
	//animateFill(node2,"red",function() { animateFill(node2,"gray"); });
	
	var	node4=$("#logo-athena").get(0);
	Snap(node4).animate( { transform: "r"+45+",80,75" }, 300,updown );
	clearField("username");
	clearField("password");
}
						

function animateFill(node,color,callback)
{
	Snap(node).animate( { fill: color }, 300, updown, callback);
}


function updown(n)
{
	return 1-2*(Math.abs(n-0.5));
}

function animateFill2(node,color,callback)
{
	Snap(node).animate( { fill: color }, 300, mina.easeinout, callback);
}


function animateFill3(node,color,callback)
{
	Snap(node).animate( { fill: color }, 300, mina.easeinout, callback);
}

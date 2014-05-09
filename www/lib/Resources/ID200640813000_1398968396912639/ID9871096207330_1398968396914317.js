function initHeadroom(id)
{

	var elem=$("#"+id).get(0);
	console.log("Init headroom...");
							
	var headroom = new Headroom(elem, {
									  	"tolerance": 5,
									  	"offset": 205,
									  	"classes": {
									    "initial": "animated headroom",
									    "pinned": "headroom--pinned",
									    "unpinned": "headroom--unpinned",
									    "top": "headroom--top",
									    "notTop": "headroom--not-top"
									  } });	
	headroom.init();
}
function initHeadroom(id)
{

	var elem=$("#"+id).get(0);
	var headroom = new Headroom(elem, {
									  	"tolerance": 5,
									  	"offset": 205,
									  	"classes": {
									    "initial": "animated",
									    "pinned": "slideDown",
									    "unpinned": "slideUp",
									    "top": "headroom--top",
									    "notTop": "headroom--not-top"
									  } });	
	headroom.init();
}
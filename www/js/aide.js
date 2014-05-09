///
//// AIDE
//// Athena IDE
///  Remote debugger connectivity
///



function initAIDE()
{
	getNextServerPushLoop();
}



function callEvalString(expressionString,eindex)
{
	var result=evalString(expressionString);

	$("#SIContentInput").val(result);
	$("#DUMMYuploadForm").ajaxSubmit({ 	url: "printResult",
									data: { 	resID: eindex },
									type: "POST",
									success: function(res) { }
								 });

}


///
//// ready set boot
///


//$(document).ready( initAIDE );

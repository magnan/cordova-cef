var express = require("express");
var upload = require('jquery-file-upload-middleware');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var session = require('express-session');

var app = express();

// configure upload middleware
upload.configure({
        uploadDir: __dirname + '/public/uploads',
	    uploadUrl: '/uploads',
	    imageVersions: {
            thumbnail: {
                width: 80,
		    height: 80
		    }
        }
    });

app.use(cookieParser());
app.use(session({ secret: "password"}));
app.use(bodyParser());


app.use('/upload', function (req, res, next) {
	// imageVersions are taken from upload.configure()
	upload.fileHandler({
                uploadDir: function () {
                    return __dirname + '/public/uploads/' + req.sessionID
			},
		    uploadUrl: function () {
                    return '/uploads/' + req.sessionID
			}
            })(req, res, next);
    });


app.get(/^(.+)$/, function(req, res){ 
	console.log('static file request : ' + req.params);
	res.sendfile( __dirname + '/public/' + req.params[0]); 
    });

//app.use('/upload', upload.fileHandler());
app.listen(8000);
/*********************************************************************
** Program Filename: GET_and_Post_Checker
** Author: Jacob Leno
** Date: 02/21/2018
** Description: This program displays data sent to it via GET or POST
*********************************************************************/

var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: false}));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 15302);

//This handler processes a GET request
//If a GET request was sent then get the data in query and append it as an object to the data variable
//send this information to the homepage.handlebars template
app.get('/', function(req, res){
  var queryParams = [];
  for (var params in req.query){
    queryParams.push({'pName':params, 'pValue':req.query[params]})
  }
  var data = {};
  data.dataType = "GET";
  data.dataList = queryParams;
  res.render('homepage', data);
});

//This handler processes a POST request
//If a POST request was sent then get the data in body and append it as an object to the data variable
//send this information to the homepage.handlebars template along with any data that may have been
//sent in the URL.
app.post('/', function(req, res){
  var queryParams = [];
  var bodyParams = [];
  for (var params in req.body){
    bodyParams.push({'pName':params, 'pValue':req.body[params]})
  }
  for (var params in req.query){
    queryParams.push({'pName':params, 'pValue':req.query[params]})
  }
  var data = {};
  data.dataType = "POST";
  data.dataList = bodyParams;
  data.urlData = queryParams;
  res.render('homepage', data);
});

app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

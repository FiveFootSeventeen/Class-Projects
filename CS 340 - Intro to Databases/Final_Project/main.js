/*
*********************************************************************
** Title: main.js
** Author: Jacob Leno
** Date: 03/16/18
** Main page directs requests to requested page. This code has been adapted from 
** example code given by instructor.
*********************************************************************
*/


var express = require('express');
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var Handlebars     = require('handlebars');
var HandlebarsIntl = require('handlebars-intl');


HandlebarsIntl.registerWith(Handlebars);

app.engine('handlebars', handlebars.engine);
app.use(bodyParser.urlencoded({extended:true}));
app.use('/static', express.static('public'));
app.set('view engine', 'handlebars');
app.set('port', process.argv[2]);
app.set('mysql', mysql);

app.use('/employee', require('./employees.js'));
app.use('/department', require('./department.js'));
app.use('/customer', require('./customer.js'));
app.use('/transaction', require('./transaction.js'));
app.use('/product', require('./product.js'));


app.get('/', function(req, res, next){
	res.redirect('/employee');
});

app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

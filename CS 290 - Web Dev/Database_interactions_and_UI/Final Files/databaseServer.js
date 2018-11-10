const path = require('path');

var express = require('express');
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});


app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 24001);
app.use(express.static(path.resolve(__dirname, 'public')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));


app.get('/', function(req, res, next){
  var context = {};
  res.render('home');
});

app.post('/getTable', function(req, res, next){
  var context = {};
  mysql.pool.query("SELECT `id`,`name`,`reps`,`weight`,`date`,`lb` FROM workouts", function(err, rows, fields){
    if(err){
	next(err);
	return;
    }
    context.results = JSON.stringify(rows); 
    res.send(context.results);
  });
});

app.post('/deleteRow', function(req, res, next){
  var context = {};
  mysql.pool.query("DELETE FROM workouts WHERE id=?", [req.body.row], function(err, rows, fields){
    if(err){
	next(err);
	return;
    }
    context.results = "Removed row " + req.body.row;
    res.send(context);
  });
});

app.post('/addRow', function(req, res, next){
	var context = {};
	mysql.pool.query("INSERT INTO workouts (`name`,`reps`,`weight`,`date`,`lb`) VALUES (?,?,?,?,?)",
	 [req.body.name, req.body.reps, req.body.weight, req.body.date, req.body.lb], function(err, result){
	   if(err){
		next(err);
		return;	
	   }
	   context.results = "Inserted id " + result.insertId;
	   res.send(context);
  });
});

app.post('/safe-update',function(req,res,next){ 
  var context = {};
  mysql.pool.query("SELECT * FROM workouts WHERE id=?", [req.body.id], function(err, result){
    if(err){
      next(err);
      return;
    }
    if(req.body.lb == false || req.body.lb == 0)req.body.lb = "0";
    if(result.length == 1){
      var curVals = result[0];
      mysql.pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lb=? WHERE id=? ",
        [req.body.name || curVals.name, req.body.reps || curVals.reps, req.body.weight || curVals.weight, 
	req.body.date || curVals.date, req.body.lb||curVals.lb, req.body.id],
        function(err, result){
        if(err){
          next(err);
          return;
        }
        context.results = "Updated " + result.changedRows + " rows.";
        res.send(context);
      });
    }
  });
});

app.post('/reset-table',function(req,res,next){
  var context = {};
  mysql.pool.query("DROP TABLE IF EXISTS workouts", function(err){
    var createString = "CREATE TABLE workouts(" +
    "id INT PRIMARY KEY AUTO_INCREMENT," +
    "name VARCHAR(255) NOT NULL," +
    "reps INT," +
    "weight INT," +
    "date DATE,"+
    "lb BOOLEAN)";
    mysql.pool.query(createString, function(err){
      context.results = "Table reset";
      res.send(context);
    })
  });
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

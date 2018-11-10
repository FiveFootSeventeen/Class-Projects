/*
*********************************************************************
** Title: employees.js
** Author: Jacob Leno
** Date: 03/16/18
** Handlers for employee page. This code has been adapted from 
** example code given by instructor.
*********************************************************************
*/

module.exports = function(){
    var express = require('express');
    var router = express.Router();

	function getEmployeeInfo(res, mysql, context, complete){
		mysql.pool.query("SELECT id, empName, empAddress, empPhoneNumber, empEmail, hourlyRate FROM employee", function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.employees = results;
			complete();
		});
	}
	



        function getEmployee(res, mysql, context, id, complete){
          var sql = "SELECT id, empName, empAddress, empPhoneNumber, empEmail, hourlyRate FROM employee WHERE id = ?";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.employee = results[0];
              complete();     
       	    });
	}


    router.get('/', function(req, res){
        var context = {};
        var mysql = req.app.get('mysql');
        getEmployeeInfo(res, mysql, context, complete);
        function complete(){
			res.render('employee', context);
        }
    });


    router.get('/:id', function(req, res){
        var context = {};
        context.jsscripts = ["updateEmployee.js"];
        var mysql = req.app.get('mysql');
        getEmployee(res, mysql, context, req.params.id, complete);
        function complete(){
			res.render('update-employee', context);
        }
    });

    router.post('/', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO employee (empName, empAddress, empPhoneNumber, empEmail, hourlyRate) VALUES (?,?,?,?,?)";
        var inserts = [req.body.name, req.body.address, req.body.phoneNumber, req.body.email, req.body.hourlyRate];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
		res.redirect('/employee');
            }
        });
    });


    router.put('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "UPDATE employee SET empName=?, empAddress=?, empPhoneNumber=?, empEmail=?, hourlyRate=? WHERE id=?";
        var inserts = [req.body.name, req.body.address, req.body.phoneNumber, req.body.email, req.body.hourlyRate, req.params.id];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.status(200);
                res.end();
            }
        });
    });

    return router;
}();

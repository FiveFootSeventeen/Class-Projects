/*
*********************************************************************
** Title: department.js
** Author: Jacob Leno
** Date: 03/16/18
** Handlers for department page.
*********************************************************************
*/

module.exports = function(){
    var express = require('express');
    var router = express.Router();
   
	function getDepartmentInfo(res, mysql, context, complete){
		mysql.pool.query("SELECT d.id, name, e.empName, totalSales, yearlyGoal FROM department d INNER JOIN employee e on e.id = d.fkEmpID", 
				function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.departments = results;
			complete();
		});
	}

	function getEmployees(res, mysql, context, complete){
		mysql.pool.query("SELECT id, empName FROM employee WHERE id NOT IN (SELECT e.id FROM department d INNER JOIN employee e on e.id = d.fkEmpID)",
			 function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.employees = results;
			complete();
		});
	}


        function getDepartment(res, mysql, context, id, complete){
          var sql = "SELECT d.id, name, e.empName, totalSales, yearlyGoal FROM department d INNER JOIN employee e on e.id = d.fkEmpID WHERE d.id = ?";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.department = results[0];
              complete();   
       	    });
	}

	

    router.get('/', function(req, res){
	var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getDepartmentInfo(res, mysql, context, complete);
        getEmployees(res, mysql, context, complete);
        function complete(){
		callbackCount++;
		if (callbackCount >= 2){
			res.render('department', context);
		}
        }
    });


    router.get('/:id', function(req, res){
	var callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateDepartment.js"];
        var mysql = req.app.get('mysql');
        getDepartment(res, mysql, context, req.params.id, complete);
	getEmployees(res, mysql, context, complete);
        function complete(){
		callbackCount++;
		if (callbackCount >= 2){
			res.render('update-department', context);
		}
        }
    });


    router.post('/', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO department (fkEmpID, name, totalSales, yearlyGoal) VALUES (?,?,?,?)";
        var inserts = [req.body.fkEmpID, req.body.name, req.body.totalSales, req.body.yearlyGoal];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
		res.redirect('/department');
            }
        });
    });


    router.put('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "UPDATE department SET fkEmpID=?, name=?, totalSales=?, yearlyGoal=? WHERE id=?";
        var inserts = [req.body.fkEmpID, req.body.name, req.body.totalSales, req.body.yearlyGoal, req.params.id];
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

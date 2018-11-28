/*
*********************************************************************
** Title: transaction.js
** Author: Jacob Leno
** Date: 03/16/18
** Handlers for transaction page. 
*********************************************************************
*/


module.exports = function(){
    var express = require('express');
    var router = express.Router();

	function getTransactionInfo(res, mysql, context, complete){
		mysql.pool.query("SELECT p.productName, t.id, e.empName, c.custName, totalPrice, transactionDate FROM transactions t INNER JOIN employee e on e.id = t.fkEmpId INNER JOIN customer c on c.id = t.fkCustomerID INNER JOIN productSold ps on ps.transactionID = t.id INNER JOIN product p on p.id = ps.productID ORDER BY t.id",			function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.transaction = results;
			complete();
		});
	}
	
        function getTransaction(res, mysql, context, id, complete){
          var sql = "SELECT p.productName, t.id, e.empName, c.custName, totalPrice, transactionDate FROM transactions t INNER JOIN employee e on e.id = t.fkEmpId INNER JOIN customer c on c.id = t.fkCustomerID INNER JOIN productSold ps on ps.transactionID = t.id INNER JOIN product p on p.id = ps.productID WHERE t.id = ? ORDER BY t.id";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.transaction = results[0];
       	      complete();      
       	    });
	}

	    function getTransactionWhereId(res, mysql, context, id, complete){
          var sql = "SELECT p.productName, t.id, e.empName, c.custName, totalPrice, transactionDate FROM transactions t INNER JOIN employee e on e.id = t.fkEmpId INNER JOIN customer c on c.id = t.fkCustomerID INNER JOIN productSold ps on ps.transactionID = t.id INNER JOIN product p on p.id = ps.productID WHERE c.id = ?";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.transaction = results;
       	      complete();      
       	    });
	}
	
		function getEmployees(res, mysql, context, complete){
		mysql.pool.query("SELECT id, empName FROM employee",
			 function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.employee = results;
			complete();
		});
	}
	
		function getCustomer(res, mysql, context, complete){
		mysql.pool.query("SELECT id, custName FROM customer",
			 function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.customer = results;
			complete();
		});
	}
		function getProduct(res, mysql, context, complete){
		mysql.pool.query("SELECT id, productName FROM product",
			 function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.product = results;
			complete();
		});
	}


    router.get('/', function(req, res){
	var callbackCount = 0;
        var context = {};
	context.jsscripts = ["deleteTransaction.js"];
        var mysql = req.app.get('mysql');
        getTransactionInfo(res, mysql, context, complete);
	getEmployees(res, mysql, context, complete);
	getCustomer(res, mysql, context, complete);
	getProduct(res, mysql, context, complete);
        function complete(){
			callbackCount++;
			if(callbackCount >= 4){
				res.render('transaction', context);
			}
        }
    });

    router.post('/search', function(req, res){
	var callbackCount = 0;
        var context = {};
	var custId = req.body.customerName;
        context.jsscripts = ["deleteTransaction.js"];
        var mysql = req.app.get('mysql');
        getTransactionWhereId(res, mysql, context, custId, complete);
	getEmployees(res, mysql, context, complete);
	getCustomer(res, mysql, context, complete);
	getProduct(res, mysql, context, complete);
        function complete(){
			callbackCount++;
			if(callbackCount >= 4){
				res.render('transaction', context);
			}
        }
    });
	
	
	
	
    router.post('/', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO transactions (fkCustomerID, fkEmpId, totalPrice, transactionDate) VALUES (?,?,?,?)";
        var inserts = [req.body.customerName, req.body.employeeName, req.body.totalPrice, req.body.date];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
		sql = "INSERT INTO productSold (productID, transactionID) VALUES (?, ?)";
		inserts = [req.body.productName, results.insertId]
		sql = mysql.pool.query(sql,inserts,function(error, results, fields){
		if(error){
				res.write(JSON.stringify(error));
				res.end();
			}else{
				res.redirect('/transaction');
			}
                });
	    }
        });
    });


    router.delete('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM transactions WHERE id = ?";
        var inserts = req.params.id;
        sql = mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.status(400);
		console.log("here!");
                res.end();
            }else{
                res.status(202).end();
            }
        })
    })

    return router;
}();

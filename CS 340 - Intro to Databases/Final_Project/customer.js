/*
*********************************************************************
** Title: customer.js
** Author: Jacob Leno
** Date: 03/16/18
** Handlers for customer page.
*********************************************************************
*/

module.exports = function(){
    var express = require('express');
    var router = express.Router();

	function getCustomerInfo(res, mysql, context, complete){
		mysql.pool.query("SELECT id, custName, custAddress, custPhoneNumber, custEmail FROM customer", function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.customer = results;
			complete();
		});
	}
	



        function getCustomer(res, mysql, context, id, complete){
          var sql = "SELECT id, custName, custAddress, custPhoneNumber, custEmail FROM customer WHERE id = ?";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.customer = results[0];
       	      complete();      
       	    });
	}


    router.get('/', function(req, res){
        var context = {};
        context.jsscripts = ["deleteCustomer.js"];
        var mysql = req.app.get('mysql');
        getCustomerInfo(res, mysql, context, complete);
        function complete(){
			res.render('customer', context);
        }
    });


    router.get('/:id', function(req, res){
        var context = {};
        context.jsscripts = ["updateCustomer.js"];
        var mysql = req.app.get('mysql');
        getCustomer(res, mysql, context, req.params.id, complete);
        function complete(){
			res.render('update-customer', context);
        }
    });


    router.post('/', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO customer (custName, custAddress, custPhoneNumber, custEmail) VALUES (?,?,?,?)";
        var inserts = [req.body.name, req.body.address, req.body.phoneNumber, req.body.email, req.body.hourlyRate];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
		res.redirect('/customer');
            }
        });
    });


    router.put('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "UPDATE customer SET custName=?, custAddress=?, custPhoneNumber=?, custEmail=? WHERE id=?";
        var inserts = [req.body.name, req.body.address, req.body.phoneNumber, req.body.email, req.params.id];
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


    router.delete('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM customer WHERE id = ?";
        var inserts = req.params.id;
        sql = mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            }else{
                res.status(202).end();
            }
        })
    })

    return router;
}();

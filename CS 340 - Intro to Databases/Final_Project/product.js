/*
*********************************************************************
** Title: product.js
** Author: Jacob Leno
** Date: 03/16/18
** Handlers for product page. 
*********************************************************************
*/


module.exports = function(){
    var express = require('express');
    var router = express.Router();

	function getProductInfo(res, mysql, context, complete){
		mysql.pool.query("SELECT p.id, d.name as deptName, productName, description, price, stock FROM product p INNER JOIN department d on d.id = p.fkDepartmentID", 
		function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.product = results;
			complete();
		});
	}
	



        function getProduct(res, mysql, context, id, complete){
          var sql = "SELECT p.id, d.name as deptName, productName, description, price, stock FROM product p INNER JOIN department d on d.id = p.fkDepartmentID WHERE p.id = ?";
          var inserts = [id];
          mysql.pool.query(sql, inserts, function(error, results, fields){
              if(error){
                  res.write(JSON.stringify(error));
                  res.end();
              }
              context.product = results[0];
       	      complete();      
       	    });
	}

	function getDepartments(res, mysql, context, complete){
		mysql.pool.query("SELECT id, name as deptName FROM department",
			 function(error, results, fields){
			if(error){
				res.write(JSON.stringify(error));
				res.end();
			}
			context.department = results;
			complete();
		});
	}

    router.get('/', function(req, res){
	var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteProduct.js"];
        var mysql = req.app.get('mysql');
        getProductInfo(res, mysql, context, complete);
	getDepartments(res, mysql, context, complete);
        function complete(){
			callbackCount++;
			if(callbackCount >= 2){
				res.render('product', context);
			}
        }
    });


    router.get('/:id', function(req, res){
	var callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateProduct.js"];
        var mysql = req.app.get('mysql');
        getProduct(res, mysql, context, req.params.id, complete);
	getDepartments(res, mysql, context, complete);
        function complete(){
			callbackCount++;
			if(callbackCount >= 2){
				res.render('update-product', context);
			}
        }
    });


    router.post('/', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO product (fkDepartmentID, productName, description, price, stock) VALUES (?,?,?,?,?)";
        var inserts = [req.body.departmentName, req.body.prodName, req.body.description, req.body.price, req.body.stock];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
				res.redirect('/product');
            }
        });
    });


    router.put('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "UPDATE product SET fkDepartmentID=?, productName=?, description=?, price=?, stock=? WHERE id=?";
        var inserts = [req.body.departmentName, req.body.prodName, req.body.description, req.body.price, req.body.stock, req.params.id];
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
        var sql = "DELETE FROM product WHERE id = ?";
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

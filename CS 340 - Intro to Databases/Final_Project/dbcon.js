var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_lenoja',
  password        : '1376',
  database        : 'cs340_lenoja'
});
module.exports.pool = pool;
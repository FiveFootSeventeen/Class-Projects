var MOUNTAINS = [
  {name: "Kilimanjaro", height: 5895, country: "Tanzania"},
  {name: "Everest", height: 8848, country: "Nepal"},
  {name: "Mount Fuji", height: 3776, country: "Japan"},
  {name: "Mont Blanc", height: 4808, country: "Italy/France"},
  {name: "Vaalserberg", height: 323, country: "Netherlands"},
  {name: "Denali", height: 6168, country: "United States"},
  {name: "Popocatepetl", height: 5465, country: "Mexico"}
];

function buildTable(data) {
  var newTable = document.createElement("table");
  var keys = Object.keys(data[0]);
  var firstRow = document.createElement("tr");
  for (var i = 0; i < keys.length; i++){
    var header = document.createElement("th");
    header.textContent = keys[i];
    firstRow.appendChild(header);
  }
  newTable.appendChild(firstRow);

  for (var i = 0; i < data.length; i++){
    var row = document.createElement("tr");
    for (var values in data[i]){
      var tableData = document.createElement("td");
      var content = data[i][values];
      tableData.textContent = content;
      if (typeof(content) == "number")
        tableData.style.textAlign = "right";
      row.appendChild(tableData);
    }
    newTable.appendChild(row);
  }
  return newTable;
}

document.body.appendChild(buildTable(MOUNTAINS));

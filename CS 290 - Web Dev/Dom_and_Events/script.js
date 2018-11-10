/*********************************************************************
** Program Filename: Dom and Events Assignment
** Author: Jacob Leno
** Date: 02/09/18
** Description: Demonstrates the use of Javascript to build html elements,
** select elements, and create events.
*********************************************************************/
document.getElementsByTagName("title")[0].textContent = "DOM and Events Assignment";
var table = buildTable(4, 7);                         //Build a table to desired size and style it
var tableStyling = table.querySelectorAll("td, th");
styleTable(tableStyling);

var bodyTag = document.getElementsByTagName("body");  //Create the four directional buttons and add them to
bodyTag[0].appendChild(createDirectionButtons());     //the document

var markCell = document.createElement("button");      //Create a button for marking the cells
markCell.textContent = "Mark Cell";
markCell.setAttribute("id", "mark");

bodyTag[0].appendChild(markCell);     //Add the table and the mark cell button to the document
bodyTag[0].appendChild(table);
currentCell = getTableCell(1, 1);
selectCell(currentCell);

//Move the selected cell based on which button fired an event
function moveSelection(event){
    var moveDir = event.target.textContent;
    var xPos = Number(currentCell.getAttribute("x"));
    var yPos = Number(currentCell.getAttribute("y"));
    switch(moveDir) {
        case "up":
        if (getTableCell(xPos, (yPos - 1)) != 0){
            unselectCell(getTableCell(xPos, yPos));
            selectCell(getTableCell(xPos, (yPos - 1)));
            currentCell = getTableCell(xPos, yPos - 1);
          }
        break;
        case "down":
        if (getTableCell(xPos, (yPos + 1)) != 0){
            unselectCell(getTableCell(xPos, yPos));
            selectCell(getTableCell(xPos, (yPos + 1)));
            currentCell = getTableCell(xPos, yPos + 1);
          }
        break;
        case "left":
        if (getTableCell((xPos - 1), yPos) != 0){
            unselectCell(getTableCell(xPos, yPos));
            selectCell(getTableCell((xPos - 1), yPos));
            currentCell = getTableCell((xPos - 1), yPos);
          }
        break;
        case "right":
        if (getTableCell((xPos + 1), yPos) != 0){
            unselectCell(getTableCell(xPos, yPos));
            selectCell(getTableCell((xPos + 1), yPos));
            currentCell = getTableCell((xPos + 1), yPos);
          }
        break;
    }
}

//Remove the thicker border from the target cell
function unselectCell(targetCell){
  targetCell.style.border = "1px solid black";
  targetCell.setAttribute("selected", 0);
}

//Add a thicker border to a target cell to indicate selection
function selectCell(targetCell){
    targetCell.style.border = "3px solid black";
    targetCell.setAttribute("selected", 1);
}

//If a given x and y coordinate has a table cell return the cell, else return 0
function getTableCell(x, y){
    var allCellData = table.querySelectorAll("td");
    for (data in allCellData){
        if (allCellData[data].textContent == (x + ", " + y)){
            return allCellData[data];
        }
    }
    return 0;
}

//Highlight the currently selected cell
function highlight(){
  var allCellData = table.querySelectorAll("td");
  for (data in allCellData){
    if (allCellData[data].tagName == "TD")
      if (allCellData[data].getAttribute("selected") == 1){
          allCellData[data].style.backgroundColor = "yellow";
      }
  }
}

//Create four directional buttons and return them
function createDirectionButtons(){
  var buttonDiv = document.createElement("div");
  var buttonNames = ["up", "down", "left", "right"];
  for (name in buttonNames){
    button = document.createElement("button");
    button.textContent = buttonNames[name];
    button.addEventListener("click", moveSelection);
    button.setAttribute("id", "direction");
    buttonDiv.appendChild(button);
  }
  return buttonDiv;
}

//Build a table the the specified columns and rows and return it.
function buildTable(columns, rows){
  var table = document.createElement("table");
  table.style.borderCollapse = "collapse";
  var firstRow = document.createElement("tr");
  for (var i = 0; i < columns; i++){
    var header = document.createElement("th");
    header.textContent = "Header " + (i + 1);
    firstRow.appendChild(header);
  }
  table.appendChild(firstRow);
  for (var y = 1; y < rows; y++){
    var oneRow = document.createElement("tr");
    for (var x = 1; x < (columns + 1); x++){
      var tableData = document.createElement("td");
      tableData.textContent = x + ", " + y;
      tableData.setAttribute("selected", 0);
      tableData.setAttribute("x", x);
      tableData.setAttribute("y", y);
      oneRow.appendChild(tableData);
    }
    table.appendChild(oneRow);
  }
  return table;
}

//Add css styling to a table
function styleTable(tableNode){
  for (element in tableNode){
    if (tableNode[element].tagName == "TD" || tableNode[element].tagName == "TH"){
      tableNode[element].style.border = "1px solid black";
      tableNode[element].style.padding = "3px 8px";
    }
  }
}

//Add event listeners to certian elements once the document is loaded.
document.addEventListener("DOMContentLoaded", function(){
    document.getElementById("mark").addEventListener("click", highlight);
    document.getElementById("direction").addEventListener("click", moveSelection);
});

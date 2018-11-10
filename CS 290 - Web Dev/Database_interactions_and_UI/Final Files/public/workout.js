resetTable();

function resetTable(){
	var req = new XMLHttpRequest();
	var payload = {};
	req.open('POST', 'http://flip1.engr.oregonstate.edu:24001/reset-table', true);
	req.setRequestHeader('Content-Type', 'application/json');
   	req.addEventListener('load', function(){
    	   if(req.status >= 200 && req.status < 400){
             var response = JSON.parse(req.responseText);
      	     } else {
               console.log("Error in network request: " + req.statusText);
	 }})
	req.send(null);
}

function getTable(callback){
	var req = new XMLHttpRequest();
	req.open('POST', 'http://flip1.engr.oregonstate.edu:24001/getTable', true);
	req.addEventListener('load', function(){
	   if(req.status >= 200 ** req.status < 400){
	     var response = req.responseText;
	     callback(JSON.parse(response));
	     } else {
		console.log("Error in network request: " + req.statusText);
	}})
	req.send(null);
}

function displayTable(){
	var table = {};
	getTable(function(table){
	  domTable =  document.getElementById('tableContent');
	var firstChild = domTable.firstElementChild;
	while(firstChild.nextSibling != null){
	  var sibling = firstChild.nextSibling;
	  if (sibling != null) sibling.remove();
	}
	  for (var i = 0; i < table.length; i++){
	    var tableRow = document.createElement('tr');
	    var tableData = document.createElement('td');
	    tableData.className = 'id';
	    tableData.innerText = table[i].id;
	    tableRow.appendChild(tableData);
	    tableData = document.createElement('td');
	    tableData.innerText = table[i].name;
	    tableRow.appendChild(tableData);
	    tableData = document.createElement('td');
	    tableData.innerText = table[i].reps;
	    tableRow.appendChild(tableData);
	    tableData = document.createElement('td');
	    tableData.innerText = table[i].weight;
	    tableRow.appendChild(tableData);
	    tableData = document.createElement('td');
	    var d = new Date(table[i].date);
	    tableData.innerText = (d.getMonth()+1) + '/' + d.getDate() + '/' + d.getFullYear();
	    tableRow.appendChild(tableData);
	    tableData = document.createElement('td');
	    if(table[i].lb == 1){
		tableData.innerText = 'Lbs';
	    } else {
	        tableData.innerText = 'Kgs';
	    }
	    tableRow.appendChild(tableData);
	    var deleteButton = document.createElement('button');
	    deleteButton.setAttribute("class", table[i].id);
	    deleteButton.innerText = "Delete";
	    deleteButton.addEventListener('click', deleteRow);
	    tableRow.appendChild(deleteButton);
   	    var updateButton = document.createElement('button');
	    updateButton.setAttribute("class", table[i].id);
	    updateButton.innerText = "Update";
	    updateButton.addEventListener('click', updateRow);
	    tableRow.appendChild(updateButton);
	    domTable.append(tableRow);
	  }
	});
}

function deleteRow(event){
	var row = event.target.className;
	var req = new XMLHttpRequest();
	req.open('POST', 'http://flip1.engr.oregonstate.edu:24001/deleteRow', true);
	req.setRequestHeader('Content-Type', 'application/json');
   	req.addEventListener('load', function(){
    	   if(req.status >= 200 && req.status < 400){
             var response = JSON.parse(req.responseText);
	     displayTable();
      	     } else {
               console.log("Error in network request: " + req.statusText);
	 }})
	req.send(JSON.stringify({'row': row}));
}

function updateRow(event){
	var newFieldset = document.createElement('fieldset');
	var newLabel = document.createElement('label');
	newLabel.innerHTML = 'Exercise name: <input type="text" id="updateName" name="name">';
	newFieldset.appendChild(newLabel);
	newLabel = document.createElement('label');
        newLabel.innerHTML = 'Reps: <input type="text" size="5" id="updateReps" name="reps">';
        newFieldset.appendChild(newLabel);
	newLabel = document.createElement('label');
        newLabel.innerHTML = 'Weight: <input type="text" size="5" id="updateWeight" name="weight">';
        newFieldset.appendChild(newLabel);
	newLabel = document.createElement('label');
        newLabel.innerHTML = 'Date: <input type="date" id="updateDate" name="date">';
        newFieldset.appendChild(newLabel);
	newLabel = document.createElement('label');
        newLabel.innerHTML = '<span>Please select the weight unit: </span>' +
	 '<input type="radio" id="updateLb" name="unit"><label for="lb">Lbs</label>' +
	 '<input type="radio" id="updateKg" name="unit"><label for="kg">Kgs</label>';
        newFieldset.appendChild(newLabel);
	newLabel = document.createElement('button');
	newLabel.addEventListener('click', updateTable);
	newLabel.textContent = 'Confirm';
	newFieldset.appendChild(newLabel);
	event.target.parentNode.appendChild(newFieldset);
}

function updateTable(event){
	var elementId = event.target.parentNode.parentNode.firstChild.innerText;
	var req = new XMLHttpRequest();
	var units;
	var payload = {name:null, reps:null, weight:null, date:null, lb:null};
	payload.name = document.getElementById('updateName').value;
	payload.reps = document.getElementById('updateReps').value;
	payload.weight = document.getElementById('updateWeight').value;
	payload.date = document.getElementById('updateDate').value;
	payload.id = elementId;

	units = document.getElementById('updateLb').checked;
	if (units == true) payload.lb = true;
	else payload.lb = false;

	req.open('POST', 'http://flip1.engr.oregonstate.edu:24001/safe-update', true);
	req.setRequestHeader('Content-Type', 'application/json');
	req.addEventListener('load', function(){
			if(req.status >= 200 && req.status < 400){
			var response = JSON.parse(req.responseText);
			displayTable();
		} else {
			console.log("Error in network request: " + req.statusText);
	}})
	req.send(JSON.stringify(payload));
}

function submitButton(){
	var req = new XMLHttpRequest();
	var units;
	var payload = {name:null, reps:null, weight:null, date:null, lb:null};
	payload.name = document.getElementById('name').value;
	if (payload.name == "") {
		document.getElementById('warning').style.display = "inline";    
	} else {
	    document.getElementById('warning').style.display = "none";	
	    payload.reps = document.getElementById('reps').value;
	    payload.weight = document.getElementById('weight').value;
	    payload.date = document.getElementById('date').value;
	    
	    units = document.getElementById('lb').checked;
	    if (units == true) payload.lb = true;
	    else payload.lb = false;
	    
	    req.open('POST', 'http://flip1.engr.oregonstate.edu:24001/addRow', true);
	    req.setRequestHeader('Content-Type', 'application/json');
	    req.addEventListener('load', function(){
	    if(req.status >= 200 && req.status < 400){
		   var response = JSON.parse(req.responseText);
		    displayTable();
	    } else {
		    console.log("Error in network request: " + req.statusText);
	}})
	    req.send(JSON.stringify(payload));
	}
}


document.addEventListener('DOMContentLoaded', function(){
  document.getElementById('excerciseSubmit').addEventListener('click', submitButton);
});

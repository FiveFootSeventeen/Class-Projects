/*********************************************************************
** Program Filename: AJAX Interactions
** Author: Jacob Leno
** Date: 02/16/18
** Description: This program demonstrates using GET and POST forms to
** get information from Web APIs
*********************************************************************/

var apiKey = "b7a3aee0be45a3f724979ab217a79ef2";

document.addEventListener('DOMContentLoaded', bindWeatherButton);
document.addEventListener('DOMContentLoaded', bindEchoButton);


function bindWeatherButton(){
    document.getElementById('submitData').addEventListener('click', function(event){
      var dataPresent = true;
      var req = new XMLHttpRequest();
      var payload = {type:null, data:null};
      var formZip = document.getElementById('zip').value;
      var formCity = document.getElementById('city').value;
      var req = new XMLHttpRequest();

      if (formZip != ""){
        req.open('GET', "http://api.openweathermap.org/data/2.5/weather?zip=" + formZip + "&units=imperial&appid=" + apiKey, true);
      }
      else if (formCity != ""){
        req.open('GET', "http://api.openweathermap.org/data/2.5/weather?q=" + formCity + "&units=imperial&appid=" + apiKey, true);
      }
      else
        dataPresent = false;

      if(dataPresent){
        req.addEventListener('load', function(){
          if(req.status >= 200 && req.status < 400){
            var response = JSON.parse(req.responseText);
            document.getElementById('reqCity').textContent = response.name;
            document.getElementById('currentTemp').textContent = response.main.temp + " °F";
            document.getElementById('currentHumidity').textContent = response.main.humidity + " %";
          } else {
            console.log("Error in network request: " + request.statusText);
          }})
          req.send(null);
      }
      event.preventDefault();
  })
}

function bindEchoButton(){
    document.getElementById("submitText").addEventListener('click', function(event){
      var req = new XMLHttpRequest();
      var textEntered = {userText:null};
      textEntered.userText = document.getElementById('echo').value;
      req.open('POST', "http://httpbin.org/post", true);
      req.addEventListener('load', function(){
        var response = JSON.parse(req.responseText);
        document.getElementById('echoText').textContent = JSON.parse(response.data).userText;
      })
      req.setRequestHeader('Content-Type', 'application/json');
      req.send(JSON.stringify(textEntered));
      event.preventDefault();
    })
}

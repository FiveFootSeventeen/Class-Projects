var apiKey = "b7a3aee0be45a3f724979ab217a79ef2";
// var apiKey = "fa7d80c48643dfadde2cced1b1be6ca1";

document.addEventListener('DOMContentLoaded', bindButtons);


function bindButtons(){
    document.getElementById('submitData').addEventListener('click', function(event){
      var dataPresent = true;
      var req = new XMLHttpRequest();
      var payload = {type:null, data:null};
      var formZip = document.getElementById('zip').value;
      var formCityState = document.getElementById('city').value;
      var req = new XMLHttpRequest();

      if (formZip != ""){
        req.open('GET', "http://api.openweathermap.org/data/2.5/weather?zip=" + formZip + "&units=imperial&appid=" + apiKey, true);
      }
      else if (formCityState != ""){
        req.open('GET', "http://api.openweathermap.org/data/2.5/weather?q=" + formCityState + "&units=imperial&appid=" + apiKey, true);
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
          event.preventDefault();
      }
  })
}


function addEvents(){
  let images = document.getElementsByClassName("scroll_images")[0].childNodes;
  for (element in images){
    if (images[element].tagName == "IMG"){
      images[element].addEventListener("click", function(event){
        document.getElementById("display_image").src = event.target.src;
        document.getElementById("download").action = event.target.src;
        console.log(document.getElementById("download"));
      });
    }
  }
}


document.addEventListener("DOMContentLoaded", function(){
  addEvents();
});
